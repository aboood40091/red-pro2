#include <cafe/base/PPCArch.h>
#include <gx2/event.h>
#include <gx2/swap.h>

namespace sead {

class GameFrameworkCafe;
class TaskMgr;

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

bool shouldRunSwapAndGpuMeasure_(GameFrameworkCafe* self)
{
    u32 flag = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x6C);
    if ((flag & 1) == 0)
        return true;
    if ((flag & 2) != 0)
        return false;
    return true;
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

    if (shouldRunSwapAndGpuMeasure_(self))
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
