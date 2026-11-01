# Frame loop and timing

NSMBU runs a fixed 60 Hz logic step tied to GX2 vsync.
It does not scale gameplay by wall-clock delta time.

`ApplicationFramework` (headers) and `GameFrame` (this tree's WIP rename) are the same RPX class.
Size is `0x398`.
Ctor is `0x029C4DC0`-family; it sets `mCalcPassCount = 1` and `mSkippedCalcCount = 0`.

## sead loop

`sead::GameFrameworkCafe::runImpl_` waits for the root task, stamps `mLastFrameBegin`, then `mainLoop_`.
`mainLoop_` forever calls `procFrame_`.

Addresses (USA v1.3.0): `runImpl_` `0x02A02EB4`, `mainLoop_` `0x02A02F48`, `procFrame_` `0x02A031A0`, base `procDraw_` `0x02A0358C`, `waitForNextFrame_` `0x02A03748`, base `swapBuffer_` `0x02A03798`.

Decompiled bodies live in `vendor/decomp/src/sead/cafe/seadGameFrameworkCafeFrameLoop.cpp` and `vendor/decomp/src/sead/seadMethodTreeNode.cpp` / `seadDualScreenMethodTreeMgr.cpp`.
Base `procDraw_` calls `GameFrameworkCafe_drawTvScreen_` (`0x02A032C8`), `GameFrameworkCafe_drawDrcScreen_` (`0x02A03394`), TV/DRC copy helpers `sub_02A03464` / `sub_02A034F8`, and framebuffer bind `sub_02A058F0` in that same file.
`TaskMgr::afterCalc` (`0x02A01730`) is in `vendor/decomp/src/sead/seadTaskMgrAfterCalc.cpp`.
`gpuMesureEnd_` (`0x02A02F74`) is in `seadGameFrameworkCafeFrameLoop.cpp`.
Base `swapBuffer_` (`0x02A03798`) is in the same file.
`CourseCameraUpdater::execute` in this tree was once tagged at `0x02A031A0`; that PC is `GameFrameworkCafe::procFrame_`, not course camera code.

The overridable steps are a static dispatch table at `0x10185280`, held at `this+0x24`, not a vtable.
Slots: `+0xD4` `procDraw_`, `+0xDC` `procCalc_`, `+0xE4` `waitForNextFrame_`, `+0xEC` `swapBuffer_`.

Each `procFrame_`:

1. `sead::Graphics::lockDrawContext` (`0x02A07A54`).
2. `sead::TaskMgr::afterCalc` (`0x02A0183C`, a `b` thunk onto `0x02A01730`) for the previous frame.
3. `procDraw_` (TV then DRC method trees, or the game override).
4. `procCalc_` (task beforeCalc + DualScreen method-tree calc, or the game override).
5. `procReset_`.
6. `swapBuffer_` → `GX2SwapScanBuffers` when display state is Show, then `GX2DrawDone`.
7. `sead::GameFrameworkCafe::gpuMesureEnd_` (`0x02A02F74`).
8. `sead::Graphics::unlockDrawContext` (`0x02A07AF8`).
9. Store `mFrameSpan = mLastFrameBegin.diffToNow()` and stamp `mLastFrameBegin` again.
10. `waitForNextFrame_`.

Step 1/8 are confirmed by body: both read the Cafe thread-specific slot id at `*(0x101E80A0)+0x20`, then `OSGetThreadSpecific`.
`lockDrawContext` compares the result against `+0x10`, bumps the `+0x14` refcount, and otherwise locks the `CriticalSection` at `+0x18` before the `lockDrawContextImpl` virtual (`vtable+0x8C`).
`unlockDrawContext` decrements `+0x14` and, at zero, clears `+0x10`, runs `unlockDrawContextImpl` (`vtable+0x90`), and unlocks `+0x18`.
Prepare Thread takes this same lock while it builds a course, and the boot, save, and level loads take it while the screen is black.
A present cap that spends the whole slot inside `procFrame_` leaves that thread waiting on the lock, so the black screen does not move on.
Step 2 is confirmed by body: it calls `MethodTreeNode::call` (`0x029FF618`) on `TaskMgr+0x14C` (`mCalcDestructionTreeNode`), then walks the destroyable list invoking `vtable+0x30`.
Step 7 is confirmed by body: `DCInvalidateRange(mGpuCounters, 0x20)`, then `mDrawOrder` at `+0xC0` selects the TV/DRC `GX2GPUTimeToCPUTime` pairs.

`procDraw_`, `procCalc_`, `procReset_`, `swapBuffer_`, and `waitForNextFrame_` are dispatch-table slots `+0xD4`, `+0xDC`, `+0x6C`, `+0xEC`, and `+0xE4`.
The `procReset_` name is inferred: the `+0x6C` body drains a callback list and clears one byte.
`mFrameSpan` is `+0x70` (a 64-bit stamp) and `mLastFrameBegin` is `+0x78`.
`mFrameSpan` is written at `0x02A03260` from `diffToNow(this+0x78)` before the new stamp at `0x02A03278`.
`calcFps` has no reader in USA v1.3.0: neither the sead framework code nor the app overrides load `+0x70` or `+0x74` from the framework object.

`waitForNextFrame_` runs only when `CreateArg::wait_vblank` is non-zero (default `1`).
It loops `GX2WaitForVsync` + `GX2GetSwapStatus` until `flipCount >= swapCount`.
`initializeGraphicsSystem` also calls `GX2SetSwapInterval(wait_vblank)`.
So one guest frame is one TV vsync by default (~60 Hz).

`mFlag` is `+0x6C`, and bit 0 is a half-frame mode in sead:
with bit 0 set, alternate `procFrame_` calls skip `swapBuffer_` and the `0x02A02F74` updater (the `xori` at `0x02A03298` toggles bit 1).
Base `procDraw_` (`0x02A0358C`) and base `swapBuffer_` test the same pair and skip the screen draws.
The app `procDraw_` override (`0x029C4FE4`) does not test it.
The ctor zeroes `+0x6C`, and no writer of bit 0 was found, so NSMBU leaves that flag clear in normal play.

## ApplicationFramework overrides

Addresses (USA v1.3.0):

- `swapBuffer_` `0x029C53F8` (app override), base `0x02A03798`
- `procDraw_` `0x029C4FE4`
- `calc_` `0x029C5104`
- `procCalc_` `0x029C52CC`

`procCalc_` (`mCalcPassCount` at `+0x38C`, `mSkippedCalcCount` at `+0x390`):

- If `mCalcPassCount > 0`: clear render mgr, run `GameFrameworkCafe::procCalc_` once, then call the app calc method-tree root (`getRootMethodTreeNode(1)`) an extra `mCalcPassCount - 1` times, then `LayerMgr::calcDL` and `calc_`.
- If `mCalcPassCount <= 0`: count skips in `mSkippedCalcCount` until `skipped + 1 >= -mCalcPassCount`, then run one full calc and reset the skip counter.
  Default is `1` (one calc per frame).
  No in-tree writer of a non-default value was found yet; the fields are the stock multi-step / skip hooks.
- `calcDL` and `calc_` are skipped when `LayerMgr::sInstance` (`*(0x101D2BE4)`) is null.

`calc_` waits on `GX2DrawDone`, copies the TV/DRC framebuffers to display buffers, flushes, and runs `LayerMgr::calcParallelExec`.
Hold / in-between port passes call only this path so the task tree does not advance.

`procDraw_` draws the TV then the DRC method tree.
The app override (`0x029C4FE4`) calls `DualScreenMethodTreeMgr::drawTop` (`0x029FD944` → `mTopRootDrawNode.call()`, node `+0x13C`), then `drawBtm` (`0x029FD94C` → `mBtmRootDrawNode.call()`, node `+0x28C`).
It also calls dispatch-table slot `+0xAC` (`0x029C5734`) once after each of those two calls, but that body is `li r3, 0; blr` — a no-op stub.
The base table `0x101906D4` puts the "a pure virtual function was called" panic (`0x02AFA5E8`) in that slot, so the app override only silences it; it does not exec a method tree.
`GX2SetContextState` (`0x029C50E4`, on `*(0x101F8000)+0x134`) and `GX2Flush` (`0x029C50E8`) run after both draws, not between them.
The base `procDraw_` (`0x02A0358C`) calls `0x02A032C8` / `0x02A03394` instead.
The port's 30 fps-style "no draw" comment on the hook refers to skip/hold paths that return before the original body, not to a native 30 Hz title rate.
NSMBU's native rate is 60 steps/s.

### Method-tree layout

`this+0x1C` is the `sead::DualScreenMethodTreeMgr` (ctor `0x029FC8BC`, size `0x3E4`, vtable `0x1018FEB8`).
It is `sead::MethodTreeMgr` (`0x40`: vtable + `CriticalSection`) followed by eleven `sead::MethodTreeNode` (`0x54` each), then the two `Screen` fields.
Node names come from the ctor's `INamable` setup and are `.rodata` strings at `0x1018FDE0`–`0x1018FEA4`:

- `+0x040` `sead::RootCalc`
- `+0x094` `sead::SysCalc`
- `+0x0E8` `sead::AppCalc`
- `+0x13C` `sead::TopRootDraw`
- `+0x190` `sead::TopSysDraw`
- `+0x1E4` `sead::TopAppDraw`
- `+0x238` `sead::TopAppDrawFinal`
- `+0x28C` `sead::BtmRootDraw`
- `+0x2E0` `sead::BtmSysDraw`
- `+0x334` `sead::BtmAppDraw`
- `+0x388` `sead::BtmAppDrawFinal`

`0x029FF490` is `appendChild`.
Tree: `RootCalc` ← {`SysCalc`, `AppCalc`}; `TopRootDraw` ← {`TopAppDraw`, `TopAppDrawFinal`, `TopSysDraw`}; `BtmRootDraw` ← {`BtmAppDraw`, `BtmAppDrawFinal`, `BtmSysDraw`}.
`0x029FF618` is `MethodTreeNode::call`: it locks `node+0x3C`, runs the recursive walk `0x029FF588` (skip when `mPauseFlag` `+0x44` bit 0 is set, else invoke the `+0x2C` delegate, then recurse), and unlocks.
`0x029FD93C` is `calc` → `RootCalc.call()` at `+0x40`.

`swapBuffer_` adds first-swap TV/DRC enable and ProcUI / HBM handling on top of `GameFrameworkCafe::swapBuffer_` (`0x02A03798`).
The first-swap flag is the byte `+0x388`, and the ProcUI result is kept at `+0x394`.
A `3` from `ProcUIProcessMessages` runs `ProcUIShutdown` and exits through `__PPCExit`.

## Per-step animation, not delta time

`FrameCtrl::play` (`0x024DEF04`) does `mFrame += mRate` once per call.
`mFrame` is at `+0x10` and `mRate` at `+0x14`.
Rates are authored in frames per logic step (often `1.0f`).
Player, enemy, and layout code assume one step equals one sixtieth of a second.

## Port hooks (reference)

The recomp port hooks `0x029C52CC` / `0x029C4FE4` / `0x029C5104` to insert draw-only holds between logic steps.
That is host presentation work; the guest engine still has no delta-time sim.
A 30 fps present calls `procCalc_` once per logic step.
Each call clears, runs the task tree, builds one display list, and waits in `calc_` (`GX2DrawDone`) before the next clear.
`mCalcPassCount` above 1 only repeats the app calc node, so both steps' draw objects land in one picture.
A second clear in the same call, without that wait, frees a list the render thread is still reading.

See also `map-shadow-interp.md` for why the world map skips `procDraw_` on the present after a hold calc.

`ModelG3d::calc` (`0x024F301C`) fills the skeleton uniform block before `ModelG3d::calcGPU` (`0x024F30DC`).
The block sits at skeleton+`0x18`.
Its data pointer is the word at +`0x18` and its size is the word at +`0x1C`.
`0x02AAAD18` writes that block from the world matrices at skeleton+`0x10`, multiplied by the matrix at `0x101B7750`.
Skinned draws load it with `LoadVertexUniforms` (`0x02AB4C44`) from skeleton+`0x18`.

`ModelG3d::calcGPU` runs while `LayerMgr::calcDL` records the display list, after `procDraw_` has already queued the previous picture.
Writing the uniform block there changes the next picture only.
A hold present repeats that list and does not call `calcGPU` again.
The port records the world matrices at the end of a logic `calcGPU`.
Before and after the course `procDraw_` it writes this present's matrices, calls `0x02AAAD18` and `0x02AA56F4`, copies the exact world matrices back, and writes this present's camera projection.
The display list keeps the uniform-block address.
The port then waits for the render thread to copy that picture before `procCalc_` replaces it.
An in-between present uses the halfway pose and the halfway projection for that copy.
A hold does not call `calcGPU`, so the port rebuilds `ModelEnvView` from that projection before the copy.
Each player's head is a separate model at `PlayerModel+0x11C`.
`PlayerMgr` stores the four actors at `+0x20`.
It has one bone and no skeleton uniform.
`calcGPU` does not run for it, so the port records its world matrix at the end of the logic step.
The draw is rigid.
Shape byte `+0x16` is 0, and the matrix uniform is the shape block written by `0x02AA56F4`.
On an in-between present the port blends that world matrix and uploads the shape block.
Rebuilding the head with `calcMdl` from the face bone leaves the head on the current logic step.
The model uniform otherwise keeps the full camera step while the bone is only halfway.
A second `LayerMgr::calcDL` (`0x024E0F84`) crashes in the layer builder (`0x02509488`, null+4).

`getBoneNum` (`0x024F4820`) reads the bone count from the u16 at `*(*(model+0x40))+8`.
World matrices are the pointer at `*(model+0x40)+0x10`, one `0x30`-byte matrix per bone.
Bone visibility is the bit array at `ModelG3d+0x2C`.
The bone index shifted right by 5 selects the word, and the low 5 bits select the bit from the least significant bit.
A set bit is visible.
Shapes are the array at `ModelG3d+0x44`, count in the u16 at `+0x3C`, stride `0x28`.
The shape object is the first word of each entry, and its bone index is the u16 at `+0x10`.
