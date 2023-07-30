#pragma once

#include <prim/seadBitFlag.h>

class BgHitCheckCallback;

struct BgCollisionCheckParam
{
    u8                  _0;
    u8                  _1;
    u8                  layer;
    sead::BitFlag8      collision_mask;
    u32                 _4;
    BgHitCheckCallback* callback;
};
