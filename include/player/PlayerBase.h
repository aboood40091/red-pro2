#pragma once

#include <actor/Actor.h>
#include <player/PlayerKey.h>

class PlayerBase : public Actor
{
public:
    const PlayerKey& getPlayerKey() const
    {
        return mPlayerKey;
    }

protected:
    u8          _27c[0x2A8 - 0x27C];
    PlayerKey   mPlayerKey;
    // ...
};
