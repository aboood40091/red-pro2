#pragma once

#include <collision/BgHitCheckCallback.h>

class ActorBgCollisionCheck;

class ActorBgHitCheckCallback : public BgHitCheckCallback
{
public:
    bool hit(const BgCollisionCheckResult& hit_res) override;

protected:
    ActorBgCollisionCheck*  mpBgCollisionCheck;
};
static_assert(sizeof(ActorBgHitCheckCallback) == 8);
