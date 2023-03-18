#pragma once

#include <effect/Effect.h>

#include <container/seadTList.h>
#include <heap/seadDisposer.h>

class EffectLevelBase : public sead::IDisposer, public Effect, public sead::TListNode<EffectLevelBase*>
{
    // NSMBW: mEf::levelEffect_c

public:
    bool createEffect(EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
    bool createEffect(EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);

    bool follow(const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
    bool follow(const sead::Matrixf& mtx, bool mtx_has_scale);

    void cleanup();

public:
    EffectLevelBase();

    virtual ~EffectLevelBase()
    {
        cleanup();
    }

    SEAD_RTTI_BASE(EffectLevelBase)

public:
    EffectID getEffectID() const
    {
        return mEffectID;
    }

    bool isActive() const
    {
        return mIsActive;
    }

protected:
    EffectID    mEffectID;
    bool        mIsActive;
};
static_assert(sizeof(EffectLevelBase) == 0x68);
