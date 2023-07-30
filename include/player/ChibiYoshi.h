#pragma once

#include <actor/ActorCollision.h>

class ChibiYoshi : public ActorCollision
{
    SEAD_RTTI_OVERRIDE(ChibiYoshi, ActorCollision)

public:
    u32 _17a0[(0x1A78 - 0x17A0) / sizeof(u32)];
    u32 _1a78;
    u32 _1a7c[(0x1F48 - 0x1A7C) / sizeof(u32)];
};
static_assert(sizeof(ChibiYoshi) == 0x1F48);
