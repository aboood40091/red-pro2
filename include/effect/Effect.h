#pragma once

#include <effect/EffectID.h>

#include <gfx/seadColor.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <ptcl/seadPtclSystem.h>

class Effect
{
    // NSMBW: mEf::effect_c

public:
    Effect()
    {
        clear();
    }

    void clear();

    bool createEffect(EffectID id);
    bool createEffect(EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);  // Defined in FollowEffect.cpp... ?
    bool createEffect(EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                           // ^^^

    bool changeEffect(EffectID id);

    bool isAlive() const;

    void fade();
    void fadeAndKill();
    void kill();

    u32 getUserData() const;

    void setColor(const sead::Color4f& color);
    void setAlpha(f32 alpha);
    void setDirectionalVel(f32 vel);
    void setEmitterScale(const sead::Vector3f& scale);
    void setParticleScale(const sead::Vector2f& scale);
    void setEmissionParticleScale(const sead::Vector2f& scale);
    void setRandomSeed(u32 seed);

    void update();

    void follow(const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
    void follow(const sead::Matrixf& mtx, bool mtx_has_scale);

    void setStopCalc(bool stop_calc);
    void setVisible(bool visible, s32 emitter_controller_index);

public:
    nw::eft::EmitterSet* getEmitterSet();
    void* getShaderParam() const { return mpShaderParam; }

protected:
    sead::Matrixf   mMtx;
    bool            mMtxHasScale;
    nw::eft::Handle mHandle;
    void*           mpShaderParam;
};
static_assert(sizeof(Effect) == 0x40);
