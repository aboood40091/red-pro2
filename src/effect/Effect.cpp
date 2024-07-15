#include <effect/Effect.h>
#include <effect/PtclMgr.h>
#include <effect/PtclParam.h>

void Effect::reset_()
{
    mMtx.makeIdentity();
    mMtxHasScale = false;
    mHandle.Invalidate();
    mpParam = nullptr;
}

nw::eft::EmitterSet* Effect::getEmitterSet_()
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mHandle.GetEmitterSet();
        if (set->IsAlive())
            return set;
    }
    return nullptr;
}

bool Effect::createEffect_(EffectID id)
{
    if (PtclMgr::instance() && PtclMgr::instance()->createEmitterSet(&mHandle, sead::Matrixf::ident, id))
    {
        mpParam = PtclMgr::instance()->getParam(id);
        if (mpParam != nullptr && mpParam->isDefault())
            mpParam = nullptr;
        return true;
    }
    return false;
}

bool Effect::createEffect(EffectID id)
{
    if (isAlive())
        return false;

    reset_();
    return createEffect_(id);
}

bool Effect::isAlive() const
{
    if (mHandle.IsValid())
        return mHandle.GetEmitterSet()->IsAlive();

    return false;
}

void Effect::fade()
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mHandle.GetEmitterSet();
        if (set->IsAlive())
            set->Fade();
    }
}

void Effect::fadeAndKill()
{
    fade();
    mHandle.Invalidate();
}

void Effect::kill()
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mHandle.GetEmitterSet();
        if (set->IsAlive())
            set->Kill();
        mHandle.Invalidate();
    }
}

s32 Effect::getGroupID() const
{
    if (mHandle.IsValid())
        return mHandle.GetEmitterSet()->GetRuntimeUserData();

    return -1;
}

void Effect::setColor(const sead::Color4f& color)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetColor(reinterpret_cast<const nw::ut::FloatColor&>(color.r));
}

void Effect::setAlpha(f32 alpha)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetAlpha(alpha);
}

void Effect::setDirectionalVel(f32 vel)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetDirectionalVel(vel);
}

void Effect::setEmitterScale(const sead::Vector3f& scale)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetEmitterScale(reinterpret_cast<const nw::math::VEC3&>(scale.x));
}

void Effect::setParticleScale(const sead::Vector2f& scale)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetParticleScale(scale.x, scale.y);
}

void Effect::setEmissionParticleScale(const sead::Vector2f& scale)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetEmissionParticleScale(reinterpret_cast<const nw::math::VEC2&>(scale.x));
}

void Effect::setRandomSeed(u32 seed)
{
    nw::eft::EmitterSet* set = getEmitterSet_();
    if (set != nullptr)
        set->SetRandomSeed(seed);
}

void Effect::updateMtx_()
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mHandle.GetEmitterSet();
        if (set->IsAlive())
        {
            if (mMtxHasScale)
                set->SetMtx(reinterpret_cast<const nw::math::MTX34&>(mMtx.a[0]));
            else
                set->SetMtxFast(reinterpret_cast<const nw::math::MTX34&>(mMtx.a[0]));
        }
        else
        {
            mHandle.Invalidate();
        }
    }
}

bool Effect::follow(const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    if (mHandle.IsValid())
    {
        mMtx.makeIdentity();
        mMtxHasScale = false;

        if (p_angle != nullptr)
        {
            mMtx.makeRzxyIdx(*p_angle);
        }

        sead::Vector3f scale;
        if (p_scale != nullptr)
            scale = *p_scale;
        else
            scale.set(1.0f, 1.0f, 1.0f);
        if (mpParam != nullptr)
            scale *= mpParam->scale;

        if (scale.x != 1.0f || scale.y != 1.0f || scale.z != 1.0f)
        {
            mMtx.scaleBases(scale);
            mMtxHasScale = true;
        }

        sead::Vector3f translate;
        if (p_trans != nullptr)
            translate = *p_trans;
        else
            translate.set(0.0f, 0.0f, 0.0f);
        if (mpParam != nullptr)
        {
            translate.x += mpParam->transX;
            translate.y += mpParam->transY;
            translate.z += mpParam->transZ;
        }

        mMtx.setTranslation(translate);

        updateMtx_();
        return true;
    }

    return false;
}

bool Effect::follow(const sead::Matrixf& mtx, bool mtx_has_scale)
{
    if (mHandle.IsValid())
    {
        mMtx = mtx;
        mMtxHasScale = mtx_has_scale;

        if (mpParam != nullptr)
        {
            if (mpParam->scale != 1.0f)
            {
                mMtx.scaleBases(mpParam->scale);
                mMtxHasScale = true;
            }

            mMtx.multTranslationWorld(mpParam->transX, mpParam->transY, mpParam->transZ);
        }

        updateMtx_();
        return true;
    }

    return false;
}

void Effect::setStopCalc(bool stop_calc)
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterSet* set = mHandle.GetEmitterSet();
        if (set->IsAlive())
            set->SetStopCalc(stop_calc);
    }
}

void Effect::setVisible(bool visible, s32 emitter_controller_index)
{
    if (mHandle.IsValid())
    {
        nw::eft::EmitterController* controller = mHandle.GetEmitterSet()->GetEmitterController(emitter_controller_index);
        if (controller != nullptr)
            controller->SetVisible(visible);
    }
}
