#pragma once

#include <collision/ActorBgCollisionCheck.h>

class ActorBgCollisionObjCheck : public ActorBgCollisionCheck
{
    SEAD_RTTI_OVERRIDE(ActorBgCollisionObjCheck, ActorBgCollisionCheck)

public:
    ActorBgCollisionObjCheck();

    u32 vf3C() override;
    u32 vf44() override;
    u32 vf4C() override;
};
static_assert(sizeof(ActorBgCollisionObjCheck) == sizeof(ActorBgCollisionCheck));
