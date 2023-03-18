#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

class Quake
{
    SEAD_SINGLETON_DISPOSER(Quake)

public:
    Quake();

    const sead::Vector2f& getOffset() const { return mOffset; }

private:
    u32             _10[(0x4C - 0x10) / sizeof(u32)];
    sead::Vector2f  mOffset;
    u32             _54;
};
static_assert(sizeof(Quake) == 0x58);
