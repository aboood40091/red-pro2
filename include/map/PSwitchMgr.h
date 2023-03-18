#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

class PSwitchMgr
{
    SEAD_SINGLETON_DISPOSER(PSwitchMgr)

public:
    enum SwType
    {
        cSwType_Num = 3
    };

private:
    struct Unk1
    {
        u32 _0;
        u32 _4;
        u8  flag;
    };
    static_assert(sizeof(Unk1) == 0xC);

    struct Unk2
    {
        u64 _0;
        f32 _8;
        f32 _c;
        u8  _10;
        u8  _11;
        u32 _12[(0x18 - 0x12) / sizeof(u32)];
    };
    static_assert(sizeof(Unk2) == 0x18);

public:
    // duration: 0 = permanent, N = 10 * N sec
    void set(u8 event, u8 duration, bool activate, bool timed_reverse = false, bool = false, u32 = 0, u32 = 0);

    bool isActivated(u8 event) const
    {
        return mEventFlag & (1ULL << event);
    }

private:
    u64                                 mEventFlag;
    sead::SafeArray<Unk1, 64>           _18;
    sead::SafeArray<Unk2, 64>           _318;
    u32                                 _918[(0x91C - 0x918) / sizeof(u32)];
    u32                                 mMoveFlag;
    sead::SafeArray<u32, cSwType_Num>   _920;
    sead::SafeArray<s32, cSwType_Num>   mTimer;
    u32                                 _938[(0x940 - 0x938) / sizeof(u32)];
};
static_assert(sizeof(PSwitchMgr) == 0x940);
