# NSMBU recompiler notes

This tree is New Super Mario Bros. U.
NSMBU logic stays at 60 steps a second.
The notes below are the crash fixes that still match this port.

## Fixed: 1-1 crash at guest address 4 (shader ALU jump table)

- **Signature.** SIGSEGV at guest address 4 during 1-1 after about 7000 frames.
  Last log line is often `[dispatch] pc=027EBB64 …` (unknown indirect branch).
- **Cause.** `bctr` at 027EBB5C jumps into a 16-entry branch island at 027EBB60 inside the shader ALU
  dispatcher.
  The recompiler lowered that `bctr` to `ppc_dispatch`, but only function entries are in the dispatch table,
  not interior jump-table slots.
  Unknown-branch diagnostics then called `ld32(r12+4)` with `r12=0`, which faulted at guest address 4 before
  `fatal()` could run.
- **Fix.** `tools/recomp/analyze.py` discovers these branch islands.
  `tools/recomp/recomp.py` lowers them to `switch (c->ctr)` and registers interior slots on the owning
  function.
  `ppc_dispatch` logging only peeks guest memory at `ea >= 0x10000`.

## Fixed: intermittent boot crash (agl shader archive setup)

**Cause: a late GX2CopySurface write from the render thread into freed and reused guest memory.**
Fixed on fix-boot-race: GX2CopySurface now waits for the render thread (`render_sync`) before it returns.
This is likely also the root cause of the Android (Snapdragon 8 Gen 3) boot crash that PR #31 works around
by pinning all threads to one core: with one core the render thread runs late every time.

- **Signature.** SIGBUS at guest address 4 about 0.5 s after `[thread] start "Prepare Thread"`.
  - Call path: Prepare Thread 0274A7A4 → 0203EE2C → 0203EA88 → 027B59F4 → 02786520 (agl shader program
    setup for `agl_resource_cafe_dev.sarc`).
  - The crash is in 027B90AC, called from 02786520's second loop (lr 02786700). It reads
    `*(*(prog+0x7c)+4)` with program 0's +0x7c = 0. Program array 21EFE28C (56 × 0x84, object 226FE868).
  - The first archive setup (027B8904) had filled +0x7c correctly (21F13190). The value was lost afterwards.
- **Writer.** `gfx::copy_surface_impl`'s CPU re-tile path on the "GX2 render" thread wrote
  21EFE300..21EFE4FF. Found with a write-protect watch (`NSMBU_BOOTDBG_PROT=1`) and confirmed with `NSMBU_COPYDBG=1`.
- **Cause.** agl's tile-mode conversion 027B5EEC (called from the Prepare Thread) does five things:
  1. allocates a temporary surface from the heap (here at 21EFE300, 0x200 bytes);
  2. calls `GX2CopySurface` (linear source → temporary, call site lr 027B5FD4);
  3. immediately calls `OSBlockMove`, copying the temporary back over the source;
  4. calls `DCFlushRangeNoSync`;
  5. frees the temporary.

  So the game treats the copy as finished when GX2CopySurface returns. The port only queued it for the render
  thread. When that thread ran late, the copy landed after the heap had reused the temporary's memory for the
  program array. It zeroed program 0's +0x7c whenever it landed between the array setup and the second loop.
  The port also lost the copy's result: the game had already read the temporary.
- **Fix.** `HLE(gx2, GX2CopySurface)` calls `render_sync` after queueing the copy, unless a display list is
  being recorded (display lists run when called). This applies to both backends.
  - Cost: about 50 syncs at boot (agl resource setup), in the first 5 s. None in steady gameplay
    (`NSMBU_SYNC_STATS=1`, site "CopySurface").
  - The per-sync ms cost is to be measured on an idle machine (TODO.md).
- **Evidence (h6, 2026-10-06, strictly one boot at a time, load average 6 to 8 on 16 cores).**
  - Stressed with `NSMBU_GX2_DELAY_COPY` (the render thread stalls before each copy):
    - unfixed, 15 or 30 ms: 14 of 14 boots crash with the identical signature;
    - unfixed, 45 ms: 0 of 4 (the write then lands after the second loop's read);
    - fixed, 15 or 30 ms: 0 of 28.
  - Not stressed: unfixed 0 of 30, fixed 0 of 60. With one instance on a lightly loaded machine the natural
    rate is too low to tell the two apart. Earlier rates were about 1 in 12 with 8 instances and 1 in 15 to
    1 in 88 with 2, and on Android with all threads on one core every boot crashed.
- **Debug aids (all off by default).**
  - `NSMBU_GX2_DELAY_COPY=ms` (gx2_core.cpp): the regression repro.
  - `NSMBU_COPYDBG=1`: logs each GX2CopySurface issue (thread, lr, images) and each CPU-path execution (range,
    time).
