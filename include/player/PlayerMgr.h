#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

class Player;
class Yoshi;

class PlayerMgr
{
    SEAD_SINGLETON_DISPOSER(PlayerMgr)

public:
    Player* getPlayer(s32 player_no)
    {
        return mPlayer[player_no];
    }

private:
    u32                         _10;
    u32                         _14;
    u32                         _18;
    u32                         _1C;
    sead::SafeArray<Player*, 4> mPlayer;
    Player**                    mppPlayer;
    u32                         _34;
    u32                         _38;
    u32                         _3C;
    u16                         _40;
    u16                         mPlayerFlag;
    Yoshi**                     mppYoshi;
    u32                         mYoshiRelated1;
    u32                         mYoshiRelated2;
    s32                         mActiveYoshiNumMaybe;
    u32                         _54[(0xD0 - 0x54) / sizeof(u32)];
};
static_assert(sizeof(PlayerMgr) == 0xD0);
