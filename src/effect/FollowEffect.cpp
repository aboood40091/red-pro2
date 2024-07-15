#include <effect/FollowEffect.h>


bool FollowEffect::createEffect(EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    fadeAndKill();

    if (Effect::createEffect(id))
        return follow(p_trans, p_angle, p_scale);

    return false;
}

bool FollowEffect::createEffect(EffectID id, const sead::Matrixf* p_mtx, bool mtx_has_scale)
{
    fadeAndKill();

    if (Effect::createEffect(id))
        return follow(p_mtx, mtx_has_scale);

    return false;
}
