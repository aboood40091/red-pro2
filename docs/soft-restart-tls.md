# Soft restart and HeapMgr TLS

The product path now uses a hard app relaunch for language/mod restart.

This note keeps the soft-restart investigation for guest TLS / AX / sound-info races.

Status: the soft-restart host path is deleted (commit `a2b90d8`), so the requirements below are historical.
`runtime/src/core/soft_restart.cpp` is gone, and `kill_all_for_reboot`, `reset_for_reboot`, `gx2_reset_for_reboot`, `clear_sync_objects`, and `retire_service_cpu` survive with no callers.
The guest-side findings below still hold and are what a future soft restart must plan around.

`0x02A0D584` is `sead::HeapMgr::setCurrentHeap` (swap the thread’s current heap).
`0x02A0D554` is `getCurrentHeap`.
`CourseTask.h` once tagged `0x02A0D584` as `GamesceneFactory_release`; that name is a different helper whose real PC is still unknown.

Both HeapMgr helpers load a Cafe thread-specific slot id from `*(0x101E80A0) + 0x20`, then call `OSGetThreadSpecific`.
The sead `Thread` object keeps the current heap at `+0x6C`.

Many game `sInstance` pointers sit in MEM2 between RPX sections (about `0x101CB7C8`–`0x101E93BF`), including the HeapMgr TLS root at `0x101E80A0`.
That range is inside `.data` (`0x101C30C0`–`0x101E93B4`), except the last `0xB` bytes, and `.data` is PROGBITS.
So a section reload does rewrite it, and the port's `load_rpx` zeroes the whole MEM2 span before it copies the sections back.
Cold boot is fine because anonymous guest memory starts zeroed.

A soft restart must:

1. Stop every previous guest host thread before clearing `g_reboot_kill` (busy threads exit via `ppc_preempt`; Linux must not detach still-running threads).
2. Clear that MEM2 span (and MEM1 / FG) before the guest runs again.
3. Drop host-side Cafe sync mirrors (mutex / event / queue / sleep queue / rendezvous) and cancel armed alarms so callbacks do not run against the wiped image.
4. Any host wait that can outlive a preempt (frame-heap spin, GX2 fence `render_sync`) must observe the reboot flag and exit via `GuestExit` rather than `pthread_kill`/`pthread_exit`, which skips C++ unlock of `g_exec_mutex` and deadlocks the next boot.
5. Realign GX2 `g_flip_count` with `g_swap_count` (same `g_count_offset`) after a reboot.
   A soft restart that drains flips with a timeout can leave flip behind swap; the guest then waits forever for a flip that never catches up.
6. Stop and join the AX `frame_thread` before wiping MEM2.
   That host service thread is exempt from reboot `GuestExit` and can still `guest_call` into guest audio after game threads are killed.
   Clear AX app/aux/final-mix callbacks and set `g_running` false during prepare (do not join there: the frame thread may be waiting on a guest core the preparer still holds).
   Join after guest threads have exited, before MEM2 wipe / the next `AXInit`; never run two frame threads.
7. Tear down AX `make_service_cpu` HostThreads and do not reset the host bump allocator.
   `make_service_cpu` allocates the guest OSThread and stack with `host_alloc` and registers `service=true` in `g_threads`.
   Soft restart joins the AX `std::thread`, then that thread must `retire_service_cpu` (unregister and delete its HostThread).
   The host bump allocator must keep its high-water mark across soft restart so the long-lived alarm service HostThread is not overwritten when the next boot calls `host_alloc`.
8. SoundStartable sound-info table (`AudAudioPlayer+0x20` / SoundStartable `+0x1C`):
   - Layout: `sead::AudioPlayer` vtable at `+0`, `nw::snd::SoundArchivePlayer` / SoundStartable at `+4`.
   - Count at SoundStartable `+0x18` (`player+0x1C`); table pointer at `+0x1C` (`player+0x20`); entry stride 120 (`0x78`).
   - GetSoundInfo is `0x02ADB9C0`: `table + id*120`.
   - Ctor `0x02ADAA34` zeroes count/table; shutdown `0x02ADB714` clears them.
   - Setup carves the table from the player buffer in `0x02ADAE50` (`stwu` at `02ADAEC4` / count at `02ADAECC`), reached from SoundArchivePlayer Setup `0x02ADB338` ← `0x02ADB530` ← `0x02ADB634` ← AudioPlayerCafe buffer setup `0x029E6C38` / `0x029E8324`.
     The `bl 0x02ADB338` at `0x02ADB580` is in `0x02ADB530`, a wrapper layer the earlier chain skipped.
   - `AudAudioPlayer::initialize` (`0x029B21A0`) is a no-op: it branches to `0x029E6EA0`, which is `blr`, and nothing calls it (`0x029B21A0` appears only as a method-table slot at `.rodata 0x1017C1BC`).
     `SndAudioMgr::loadData` (`0x029B7548`), `startSound` (`0x029B5434`), and `startSoundImpl` (`0x029B6B10`) do not install the table: a call-graph sweep from each finds no path to the Setup chain.
   - `startSound` has a single static caller, `SndAudioMgr::startSystemSe` (`0x029B54C0`), which is reached from gameplay.
   - The `bctrl` at `0x029B5460` in `startSound` is `startSoundImpl`, and the interface table is `0x1017C814`.
     `startSound` loads `*(this+0x3D0)` into `r12`, loads `0x24(r12)` into `r0`, then `bctrl` with `r3 = this`, `r4 = handle`, `r5 = label`.
     The ctor `0x029B393C` allocates `0x3D4` bytes and materialises `0x1017C814` as `lis r0, 0x1018` + `addic r0, r0, -0x37ec`, then stores it at `+0x3D0`.
     Entries are 8 bytes with the function pointer at `+4`: `+0x04` = `0`, `+0x0C` = `initialize` (`0x029B41AC`), `+0x14` = `calc` (`0x029B4FFC`), `+0x1C` = the deleted `vf1C` (the panic `0x02AFA5E8`), `+0x24` = `startSoundImpl` (`0x029B6B10`).
     That is exactly the virtual order in `include/sound/SndAudioMgr.h`, which already records `vtbl Address: 0x1017C814`.
     An earlier note wrote the table as `0x1018C814`; the correct address is `0x1017C814`.
     `src/sound/SndAudioMgr.cpp` is the decompiled `startSound` and `startSystemSe`.
     `src/audio/seadAudioPlayerCafeInit.cpp` decompiles bootstrap slot **`0x029E8324`** and buffer setup **`0x029E6C38`** (SoundStartable at child **`+4`**, Setup via **`0x02ADB634`**).
     `src/nw/snd/SoundArchivePlayerArchive.cpp` decompiles archive slice resolve **`0x029E779C`**.
     `src/nw/snd/SoundArchivePlayerBuffer.cpp` decompiles buffer sizing **`0x02ADABBC`** / **`0x02ADAD00`** and archive read helpers **`0x02AD6968`**–**`0x02AD6CF0`**.
     `src/nw/snd/SoundArchivePlayerCarve.cpp` decompiles sound-info table carve **`0x02ADAE50`**.
     `src/nw/snd/SoundArchivePlayerSetup.cpp` decompiles **`0x02ADB470`**, **`0x02ADB530`**, **`0x02ADB338`**, and **`0x02ADB634`** (Setup sub-steps **`0x02ADAF9C`** onward remain forward-declared).
     `AudAudioMgr` is not polymorphic (its ctor `0x029B1AAC` sets no vptr), so `+0x3D0` is the only method table `SndAudioMgr` has.
     Bootstrap order (USA v1.3.0, static sweep):
     - **`0x029E8324`** is the first `{0, fn}` slot in **`.rodata 0x1017C284`**.
       The same PC also appears at **`0x1018DA04+0x18`**.
       **`0x1017C1A4`** is **`AudAudioPlayer`**'s vtable.
       **`initialize`** `0x029B21A0` is a no-op branch to **`0x029E6EA0`** (`blr`).
     - No **`.text` `bl`** targets **`0x029E8324`** (only rodata pointers at **`0x1017C284`** and **`0x1018DA1C`**).
       Entry matches **`0x029E8324` / `0x029E81D0`**: load child at **`+0x18`**, **`lwz` at `0xC(vtable)`**, **`bctrl`** (see **`0x029E837C`**, **`0x029E8228`**).
     - Up-stack **`AudAudioPlayer`** hook **`0x029B23C0`** calls **`0x029E81BC`**.
       The sound-info table is carved only after **`0x029E8324` → `0x029E6C38` → … → `0x02ADB338`** (Setup).
     - **`SndAudioMgr::startSound` (`0x029B5434`)** has one **`bl`**, from **`startSystemSe`** at **`0x029B5520`** (gameplay SE path).
     - **Conclusion:** disassembly fixes **Setup before any static `startSound` call site**, but not runtime order vs table-dispatched init on a soft restart (AX / **`startSoundImpl`** / wiped MEM2).
       Treat “SE before Setup” as **not shown**.
       Cold boot still relies on boot-time **`AudAudioPlayer`** construction before course gameplay SE.
   - The runtime skip hooks on `0x029B3C5C` / `0x029B7448` no longer exist, so they cannot be papering over a null table today.
   - Soft restart with real audio can leave the table null through early boot while startSound / isSndPlaying / AX app-frame callbacks already run; cold boot and soft restart with `NSMBU_NO_AUDIO=1` (AX waits for Audio* threads to park before starting the frame thread) succeed.
     The `NO_AUDIO` park wait is the only path that waits; the normal path starts the frame thread without it.
   - Host fix: join AX frame thread, `retire_service_cpu`, keep `g_host_top` across soft restart.
     None of this ever landed: `frame_thread` is started detached (`runtime/src/ax/ax.cpp:603`) and is never joined, `retire_service_cpu` has no caller, and the deleted `do_reboot` called `mem::reset_allocators()`, which reset `g_host_top`.
   - Do not start the AX frame thread from `AXInit`; start it when SoundArchivePlayer Setup (`0x02ADB338`) returns.
     Starting AX earlier races callbacks into Setup (table pointer is stored before Setup finishes) and after soft restart can prevent Setup from running at all.
     This gate never landed either: `AXInit` still starts the thread, and no Setup-done flag exists.
   - Gate sound-info walks / `startSoundImpl` on that Setup-done flag; defer the sound-info write (`0x029B7448`) until replayed after Setup; do not skip `SndAudioMgr::calc`.

Otherwise Prepare Thread can call `setCurrentHeap` while a leftover thread shares its OSThread (TLS wiped) and fault at guest `0x6C`, the next GX2 path stalls forever after a forced stop or a stale flip wait, or sound init after a language soft restart faults at `0x8EC` / later in `startSoundImpl` with a null player.
