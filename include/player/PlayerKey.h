#pragma once

#include <basis/seadTypes.h>

class PlayerKey
{
public:
    bool isDownPressed() const;
    bool isUpPressed() const;

    bool isRightHeld() const;
    bool isLeftHeld() const;
    bool isDownHeld() const;
    bool isUpHeld() const;

    bool isOnlyDownHeld() const;

    bool isOnlyUpHeld() const
    {
        return isUpHeld() && !isRightHeld() && !isLeftHeld() && !isDownHeld();
    }

private:
    u8  _0[0x94];
};
static_assert(sizeof(PlayerKey) == 0x94);
