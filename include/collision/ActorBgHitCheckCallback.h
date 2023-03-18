#pragma once

#include <collision/BgHitCheckCallback.h>

class ActorBgHitCheckCallback : public BgHitCheckCallback
{
public:
    bool hit(const BgCollisionCheckResult& hit_res) override;
};
static_assert(sizeof(ActorBgHitCheckCallback) == sizeof(BgHitCheckCallback));
