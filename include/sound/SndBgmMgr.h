#pragma once

#include <heap/seadDisposer.h>

class SndBgmMgr
{
    SEAD_SINGLETON_DISPOSER(SndBgmMgr)

public:
    SndBgmMgr();
    ~SndBgmMgr();

    bool isGameBgm(s32 id);
    const char* getGameBgmID(s32 id);
    const char* getGameControlBgmID(s32 id);

    bool shouldHurryUp();

    // ...

private:
    s32         mStreamID;
    const char* mBgmID;
    const char* mControlBgmID;
    u32         mSoundType; // nw::snd::SoundArchive::SoundType
    u32         _20;
    u32         _24;
    u8          _28;
    u8          _29;
    u8          _2A;
    u8          _2B;
    u32         _2C;
    u32         _30;
    u32         _34;
    const char* _38;
    const char* _3c;
    f32         _40;
    f32         _44;
    u8          _48;
    u8          _49;
    u8          _4A;
    u8          _4B;
    u32         _4C;
    u32         _50;
    u32         _54;
    const char* _58;
    u32         _5C;
    s32         _60;
    u32         _64;
    u32         _68;
    u32         _6C;
    f32         _70;

    static const u32 cGameBgmNum = 29;

    struct Bgm
    {
        const char* name;
        u32 _4;
    };
    static_assert(sizeof(Bgm) == 8);

    static const Bgm cGameBgm_Normal[cGameBgmNum + 1];
    static const Bgm cGameBgm_Fast[cGameBgmNum + 1];

    static const Bgm cGameControlBgm_Normal[cGameBgmNum + 1];
    static const Bgm cGameControlBgm_Fast[cGameBgmNum + 1];
};
static_assert(sizeof(SndBgmMgr) == 0x74);
