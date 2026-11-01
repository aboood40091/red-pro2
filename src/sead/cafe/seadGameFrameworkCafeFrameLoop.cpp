#include <cafe/base/PPCArch.h>
#include <gx2/context.h>
#include <gx2/event.h>
#include <gx2/swap.h>

namespace sead {

class GameFrameworkCafe;
class TaskMgr;
class DualScreenMethodTreeMgr;

void DualScreenMethodTreeMgr_drawTop_(DualScreenMethodTreeMgr* self);
void DualScreenMethodTreeMgr_drawBtm_(DualScreenMethodTreeMgr* self);

namespace {

constexpr u32 kGraphicsInstanceLo = 0x101F0000u;
constexpr u32 kGraphicsLockSlot = 0x101F8000u;

using DispatchFn = void (*)(GameFrameworkCafe*);

DispatchFn loadDispatch_(GameFrameworkCafe* self, u32 slot_offset)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    u32 table = *reinterpret_cast<u32*>(bytes + 0x24);
    u32 fn = *reinterpret_cast<u32*>(table + slot_offset);
    return reinterpret_cast<DispatchFn>(fn);
}

void invokeDispatch_(GameFrameworkCafe* self, u32 slot_offset)
{
    loadDispatch_(self, slot_offset)(self);
}

bool shouldRunHalfFrameSwap_(GameFrameworkCafe* self)
{
    u32 flag = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x6C);
    if ((flag & 1) == 0)
        return true;
    if ((flag & 2) != 0)
        return false;
    return true;
}

using SwapFn = void (*)(GameFrameworkCafe*, s32);

constexpr u32 kLayerMgrInitFlag = 0x101F9BE4u;
constexpr u32 kLayerMgrInitWord = 0x101FBFCu;
constexpr u32 kLayerMgrInitValue = 0x10190688u;

using DrawSlotFn = void (*)(GameFrameworkCafe*, s32);

DrawSlotFn loadDrawSlot_(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    u32 table = *reinterpret_cast<u32*>(bytes + 0x24);
    return reinterpret_cast<DrawSlotFn>(*reinterpret_cast<u32*>(table + 0xF4));
}

void initLayerMgrDrawOnce_(DualScreenMethodTreeMgr* mgr)
{
    (void)mgr;
    u32* flag = reinterpret_cast<u32*>(kLayerMgrInitFlag);
    if (*flag != 0)
        return;
    *flag = 1;
    *reinterpret_cast<u32*>(kLayerMgrInitWord) = kLayerMgrInitValue;
}

DualScreenMethodTreeMgr* prepareMethodTreeForDraw_(DualScreenMethodTreeMgr* mgr)
{
    if (mgr == nullptr)
        return nullptr;

    u8* bytes = reinterpret_cast<u8*>(mgr);
    void* cs = *reinterpret_cast<void**>(bytes + 0x3C);
    if (cs == nullptr)
        return mgr;

    u32 vtable = *reinterpret_cast<u32*>(cs);
    using PreDrawFn = s32 (*)(DualScreenMethodTreeMgr*);
    PreDrawFn pre = reinterpret_cast<PreDrawFn>(*reinterpret_cast<u32*>(vtable + 0xC));
    if (pre(mgr) == 0)
        return nullptr;
    return mgr;
}

void* loadGraphicsContextState_()
{
    void* graphics = *reinterpret_cast<void**>(kGraphicsInstanceLo);
    return *reinterpret_cast<void**>(static_cast<u8*>(graphics) + 0x134);
}

using FrameBufferBindFn = void (*)();

void bindFrameBuffer_(void* frame_buffer)
{
    if (frame_buffer == nullptr)
        return;

    u8* fb = static_cast<u8*>(frame_buffer);
    void* inner = *reinterpret_cast<void**>(fb + 0x18);
    u32 vtable = *reinterpret_cast<u32*>(inner);
    FrameBufferBindFn bind =
        reinterpret_cast<FrameBufferBindFn>(*reinterpret_cast<u32*>(vtable + 0x3C));
    bind();
}

using CopyToDisplayFn = void (*)(void*, u32);

void invokeCopyToDisplay_(void* copy_object, u32 copy_arg)
{
    u8* object = static_cast<u8*>(copy_object);
    void* inner = *reinterpret_cast<void**>(object + 0x18);
    u32 vtable = *reinterpret_cast<u32*>(inner);
    CopyToDisplayFn copy =
        reinterpret_cast<CopyToDisplayFn>(*reinterpret_cast<u32*>(vtable + 0x24));
    copy(copy_object, copy_arg);
}

// Address: 0x02A058F0
void sub_02A058F0(void* frame_buffer)
{
    bindFrameBuffer_(frame_buffer);
}

// Address: 0x02A03464
void sub_02A03464(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    void* pending = *reinterpret_cast<void**>(bytes + 0x360);
    if (pending != nullptr)
    {
        invokeCopyToDisplay_(pending, *reinterpret_cast<u32*>(bytes + 0x358));
        *reinterpret_cast<void**>(bytes + 0x360) = nullptr;
        GX2SetContextState(loadGraphicsContextState_());
        return;
    }

    void* tv_buffer = *reinterpret_cast<void**>(bytes + 0x80);
    if (tv_buffer != nullptr)
        invokeCopyToDisplay_(tv_buffer, *reinterpret_cast<u32*>(bytes + 0x358));

    GX2SetContextState(loadGraphicsContextState_());
}

// Address: 0x02A034F8
void sub_02A034F8(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    void* pending = *reinterpret_cast<void**>(bytes + 0x364);
    if (pending != nullptr)
    {
        invokeCopyToDisplay_(pending, *reinterpret_cast<u32*>(bytes + 0x35C));
        *reinterpret_cast<void**>(bytes + 0x364) = nullptr;
        GX2SetContextState(loadGraphicsContextState_());
        return;
    }

    void* drc_buffer = *reinterpret_cast<void**>(bytes + 0x84);
    if (drc_buffer != nullptr)
        invokeCopyToDisplay_(drc_buffer, *reinterpret_cast<u32*>(bytes + 0x35C));

    GX2SetContextState(loadGraphicsContextState_());
}

// Address: 0x02A032C8
void GameFrameworkCafe_drawTvScreen_(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    DualScreenMethodTreeMgr* tree =
        reinterpret_cast<DualScreenMethodTreeMgr*>(bytes + 0x1C);
    initLayerMgrDrawOnce_(tree);
    DualScreenMethodTreeMgr* mgr = prepareMethodTreeForDraw_(tree);

    u32* gpu_counters = static_cast<u32*>(*reinterpret_cast<void**>(bytes + 0x370));
    GX2SampleTopGPUCycle(gpu_counters);

    void* tv_buffer = *reinterpret_cast<void**>(bytes + 0x80);
    if (tv_buffer != nullptr)
        sub_02A058F0(tv_buffer);

    loadDrawSlot_(self)(self, 6);

    if (mgr != nullptr)
        DualScreenMethodTreeMgr_drawTop_(mgr);

    GX2SampleBottomGPUCycle(gpu_counters + 2);
}

// Address: 0x02A03394
void GameFrameworkCafe_drawDrcScreen_(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    DualScreenMethodTreeMgr* tree =
        reinterpret_cast<DualScreenMethodTreeMgr*>(bytes + 0x1C);
    initLayerMgrDrawOnce_(tree);
    DualScreenMethodTreeMgr* mgr = prepareMethodTreeForDraw_(tree);

    u32* gpu_counters = static_cast<u32*>(*reinterpret_cast<void**>(bytes + 0x370));
    GX2SampleTopGPUCycle(gpu_counters + 4);

    void* drc_buffer = *reinterpret_cast<void**>(bytes + 0x84);
    if (drc_buffer != nullptr)
        sub_02A058F0(drc_buffer);

    loadDrawSlot_(self)(self, 9);

    if (mgr != nullptr)
        DualScreenMethodTreeMgr_drawBtm_(mgr);

    GX2SampleBottomGPUCycle(gpu_counters + 6);
}

// Address: 0x02A0358C
void GameFrameworkCafe_procDraw_(GameFrameworkCafe* self)
{
    if (!shouldRunHalfFrameSwap_(self))
        return;

    u8* bytes = reinterpret_cast<u8*>(self);
    u32 draw_order = *reinterpret_cast<u32*>(bytes + 0xC0);

    if (draw_order == 0)
        GameFrameworkCafe_drawTvScreen_(self);
    else
        GameFrameworkCafe_drawDrcScreen_(self);

    if (bytes[0x36C] != 0)
        goto L_03614;

    if (draw_order == 0)
        sub_02A03464(self);
    else
        sub_02A034F8(self);

    if (draw_order == 0)
        goto L_03624;
    goto L_03638;

L_03614:
    if (draw_order == 0)
        goto L_03624;

    GameFrameworkCafe_drawTvScreen_(self);
    if (*reinterpret_cast<u32*>(bytes + 0x368) != 0)
        goto L_036a0;
    goto L_03648;

L_03624:
    GameFrameworkCafe_drawDrcScreen_(self);
    if (*reinterpret_cast<u32*>(bytes + 0x368) != 0)
        goto L_036a0;
    goto L_03648;

L_03638:
    GameFrameworkCafe_drawTvScreen_(self);
    if (*reinterpret_cast<u32*>(bytes + 0x368) != 0)
        goto L_036a0;
    goto L_03648;

L_03648:
    if (bytes[0x36C] == 0)
        goto L_03680;

    if (draw_order == 0)
        sub_02A03464(self);
    else
        sub_02A034F8(self);

    if (draw_order == 0)
        goto L_03690;

    sub_02A03464(self);
    goto L_036a0;

L_03680:
    if (draw_order == 0)
        goto L_03690;

    sub_02A034F8(self);
    goto L_036a0;

L_03690:
    sub_02A034F8(self);

L_036a0:
    GX2Flush();
}

void toggleHalfFramePhase_(GameFrameworkCafe* self)
{
    u32 flag = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x6C);
    if ((flag & 1) == 0)
        return;
    u32 toggled = flag ^ 2;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x6C) = toggled;
}

// Address: 0x02A07A54
void sub_02A07A54(void* lock);

// Address: 0x02A07AF8
void sub_02A07AF8(void* lock);

// Address: 0x02A0183C
void TaskMgr_afterCalc_thunk_(TaskMgr* task_mgr);

// Address: 0x02A1A31C
void sub_02A1A31C(u64* stamp, u32* out_hi, u32* out_lo);

} // namespace

// Address: 0x02A02F74
void GameFrameworkCafe_gpuMesureEnd_(GameFrameworkCafe* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    void* gpu_counters = *reinterpret_cast<void**>(bytes + 0x370);
    DCInvalidateRange(gpu_counters, 0x20);

    u32 draw_order = *reinterpret_cast<u32*>(bytes + 0xC0);
    u32 index = (draw_order != 0) ? 2u : 1u;
    u32 tv_index = (index == 0) ? 1u : 3u;
    u32 drc_index = (index == 0) ? 2u : 1u;

    u32* counter_pairs = static_cast<u32*>(gpu_counters);
    u32 pair_base = index << 3;

    u32 gpu_begin = counter_pairs[pair_base / 4];
    u32 gpu_end = counter_pairs[pair_base / 4 + 1];
    u32 cpu_end = *reinterpret_cast<u32*>(bytes + 0x7C);
    u32 cpu_begin = *reinterpret_cast<u32*>(bytes + 0x78);

    u32 converted_end = static_cast<u32>(GX2GPUTimeToCPUTime(gpu_begin, gpu_end));
    u32 delta_hi = cpu_begin - converted_end;
    u32 delta_lo = cpu_end - converted_end;

    u32 tv_pair = tv_index << 3;
    u32 tv_gpu_begin = counter_pairs[tv_pair / 4];
    u32 tv_gpu_end = counter_pairs[tv_pair / 4 + 1];
    u32 tv_cpu = static_cast<u32>(GX2GPUTimeToCPUTime(tv_gpu_begin, tv_gpu_end));

    u32 drc_pair = drc_index << 3;
    u32 drc_gpu_begin = counter_pairs[drc_pair / 4];
    u32 drc_gpu_end = counter_pairs[drc_pair / 4 + 1];
    u32 drc_cpu = static_cast<u32>(GX2GPUTimeToCPUTime(drc_gpu_begin, drc_gpu_end));

    (void)delta_hi;
    (void)delta_lo;
    (void)tv_cpu;
    (void)drc_cpu;
}

// Address: 0x02A03798
void GameFrameworkCafe_swapBuffer_(GameFrameworkCafe* self)
{
    if (!shouldRunHalfFrameSwap_(self))
        return;

    u8* bytes = reinterpret_cast<u8*>(self);
    SwapFn swap_fn = reinterpret_cast<SwapFn>(*reinterpret_cast<u32*>(bytes + 0x368));
    if (swap_fn == nullptr)
        return;

    swap_fn(self, 0);
    GX2DrawDone();

    if (bytes[0x36C] == 0)
    {
        if (*reinterpret_cast<u32*>(bytes + 0xC0) == 0)
            sub_02A03464(self);
        else
            sub_02A034F8(self);
    }
    else
    {
        if (*reinterpret_cast<u32*>(bytes + 0xC0) != 0)
            sub_02A034F8(self);
        else
            sub_02A034F8(self);
    }

    GX2Flush();
    swap_fn(self, 1);

    if (*reinterpret_cast<u32*>(bytes + 0x28) == 2)
        GX2SwapScanBuffers();

    GX2DrawDone();
}

// Address: 0x02A02EB4
void GameFrameworkCafe_runImpl_(GameFrameworkCafe* self)
{
    invokeDispatch_(self, 0xB4);

    u32 time_hi;
    u32 time_lo;
    OSGetSystemTime(&time_hi, &time_lo);
    u8* bytes = reinterpret_cast<u8*>(self);
    *reinterpret_cast<u32*>(bytes + 0x78) = time_hi;
    *reinterpret_cast<u32*>(bytes + 0x7C) = time_lo;

    invokeDispatch_(self, 0xC4);
}

// Address: 0x02A02F48
void GameFrameworkCafe_mainLoop_(GameFrameworkCafe* self)
{
    for (;;)
        invokeDispatch_(self, 0xCC);
}

// Address: 0x02A031A0
void GameFrameworkCafe_procFrame_(GameFrameworkCafe* self)
{
    void* lock = *reinterpret_cast<void**>(kGraphicsLockSlot);
    sub_02A07A54(lock);

    TaskMgr* task_mgr = *reinterpret_cast<TaskMgr**>(reinterpret_cast<u8*>(self) + 0x18);
    TaskMgr_afterCalc_thunk_(task_mgr);

    invokeDispatch_(self, 0xD4);
    invokeDispatch_(self, 0xDC);
    invokeDispatch_(self, 0x6C);

    if (shouldRunHalfFrameSwap_(self))
    {
        invokeDispatch_(self, 0xEC);
        GameFrameworkCafe_gpuMesureEnd_(self);
    }

    lock = *reinterpret_cast<void**>(kGraphicsInstanceLo);
    sub_02A07AF8(lock);

    u32 span_hi;
    u32 span_lo;
    u8* bytes = reinterpret_cast<u8*>(self);
    sub_02A1A31C(reinterpret_cast<u64*>(bytes + 0x78), &span_hi, &span_lo);
    *reinterpret_cast<u32*>(bytes + 0x70) = span_hi;
    *reinterpret_cast<u32*>(bytes + 0x74) = span_lo;

    u32 time_hi;
    u32 time_lo;
    OSGetSystemTime(&time_hi, &time_lo);
    *reinterpret_cast<u32*>(bytes + 0x7C) = time_lo;

    u32* state = reinterpret_cast<u32*>(bytes + 0x28);
    if (*state == 1)
        *state = 2;

    *reinterpret_cast<u32*>(bytes + 0x78) = time_hi;

    toggleHalfFramePhase_(self);
    invokeDispatch_(self, 0xE4);
}

// Address: 0x02A03748
void GameFrameworkCafe_waitForNextFrame_(GameFrameworkCafe* self)
{
    u32 wait_vblank = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x48);
    if (wait_vblank == 0)
        return;

    for (;;)
    {
        GX2WaitForVsync();
        u32 flip_count;
        u32 swap_count;
        u32 pad;
        u32 pad2;
        GX2GetSwapStatus(&flip_count, &swap_count, &pad, &pad2);
        if (flip_count >= swap_count)
            break;
    }
}

} // namespace sead
