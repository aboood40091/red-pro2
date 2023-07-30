#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>

class Actor;
struct BgCollisionCheckParam;
struct BgCollisionCheckResult;

class BasicBgCollisionCheck
{
public:
    BasicBgCollisionCheck();
    BasicBgCollisionCheck(const BgCollisionCheckParam& param);

    bool check(BgCollisionCheckResult* p_res, const sead::Vector2f& p0, const sead::Vector2f& p1, u32);

private:
    u8                  _0;
    u8                  _1;
    u8                  mLayer;
    sead::BitFlag8      mCollisionMask;
    u32                 _4;
    Actor*              mpActor;
    BgHitCheckCallback* mpCallback;
    u32                 _10[(0x48 - 0x10) / sizeof(u32)]; // sead::FixedRingBuffer<Actor*, 10>
    u32                 _48;
};
static_assert(sizeof(BasicBgCollisionCheck) == 0x4C);
