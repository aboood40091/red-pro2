#pragma once

#include <basis/seadTypes.h>

struct BgCollisionCheckResult;

class BgHitCheckCallback
{
public:
    virtual bool vf0C() { return true; }
    virtual bool hit(const BgCollisionCheckResult& hit_res) = 0;
};
static_assert(sizeof(BgHitCheckCallback) == 4);
