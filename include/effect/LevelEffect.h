#pragma once

#include <effect/EffectLevelBase.h>

class LevelEffect : public EffectLevelBase
{
    // NSMBW: dEf::dLevelEffect_c

public:
    LevelEffect()
        : EffectLevelBase()
    {
    }

    virtual ~LevelEffect()
    {
    }

    SEAD_RTTI_OVERRIDE(LevelEffect, EffectLevelBase)
};
static_assert(sizeof(LevelEffect) == sizeof(EffectLevelBase));
