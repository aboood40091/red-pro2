#include <game/CourseCameraUpdater.h>
#include <game/CourseCameraProjectionCtrl.h>

#include <state/StateID.h>

namespace {

constexpr u32 kGfxLockWordAddr = 0x101E8000u;

void enterGfxLock_(u32 lock_word);
void leaveGfxLock_(u32 lock_word);
void updateSubObject_(void* sub);
void interpCamera_(CourseCameraUpdater* updater);
void readVecPair_(void* pair_at_78, u32* out_r3, u32* out_r4);
void getSystemTime_(u32* out_r3, u32* out_r4);

}

const StateID* CourseCameraUpdater::getStateID() const
{
    return nullptr;
}

void CourseCameraUpdater::execute()
{
    u32 lock_word = *reinterpret_cast<u32*>(kGfxLockWordAddr);
    enterGfxLock_(lock_word);

    updateSubObject_(mpSub);

    CourseCameraProjectionCtrl* ctrl = mpProjCtrl;

    ctrl->fn_D4_(this);
    ctrl->fn_DC_(this);
    ctrl->fn_6C_(this);

    u32 flags = mFlags;
    u32 run_interp = 1;
    if ((flags & 1) != 0 && (flags & 2) != 0)
        run_interp = 0;

    if (run_interp != 0)
    {
        ctrl->fn_EC_(this);
        interpCamera_(this);
    }

    lock_word = *reinterpret_cast<u32*>(kGfxLockWordAddr);
    leaveGfxLock_(lock_word);

    u32 pair_hi;
    u32 pair_lo;
    readVecPair_(reinterpret_cast<u8*>(this) + 0x78, &pair_hi, &pair_lo);
    mField70 = pair_hi;
    mField74 = pair_lo;

    u32 time_hi;
    u32 time_lo;
    getSystemTime_(&time_hi, &time_lo);
    mTimePart1 = time_lo;
    mTimePart0 = time_hi;

    if (mStep == 1)
        mStep = 2;

    flags = mFlags;
    if ((flags & 1) != 0)
        mFlags = flags ^ 2;

    ctrl->fn_E4_(this);
}

namespace {

void enterGfxLock_(u32 lock_word)
{
}

void leaveGfxLock_(u32 lock_word)
{
}

void updateSubObject_(void* sub)
{
}

void interpCamera_(CourseCameraUpdater* updater)
{
}

void readVecPair_(void* pair_at_78, u32* out_r3, u32* out_r4)
{
}

void getSystemTime_(u32* out_r3, u32* out_r4)
{
}

}
