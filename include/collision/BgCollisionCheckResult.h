#pragma once

#include <prim/seadBitFlag.h>

class BgCollision;

struct BgCollisionCheckResult
{
    sead::BitFlag8  hit_direction_flag;
    f32             _4;
    f32             _8;
    u32             _c;
    u32             _10;
    u32             _14;
    u32             _18;
    u32             _1c;
    BgCollision*    p_bg_collision;
};
static_assert(sizeof(BgCollisionCheckResult) == 0x24);
