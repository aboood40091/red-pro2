#include <effect/EffectDisposable.h>
#include <effect/PtclMgr.h>

bool EffectDisposable::createEffect(EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    if (PtclMgr::instance() != nullptr)
    {
        if (mNode.isLinked())
        {
            if (mEffectID == id)
                return follow(p_trans, p_angle, p_scale);

            cleanup();
        }

        if (Effect::createEffect(id))
        {
            mEffectID = id;
            return follow(p_trans, p_angle, p_scale);
        }
    }

    return false;
}

bool EffectDisposable::createEffect(EffectID id, const sead::Matrixf* p_mtx, bool mtx_has_scale)
{
    if (PtclMgr::instance() != nullptr)
    {
        if (mNode.isLinked())
        {
            if (mEffectID == id)
                return follow(p_mtx, mtx_has_scale);

            cleanup();
        }

        if (Effect::createEffect(id))
        {
            mEffectID = id;
            return follow(p_mtx, mtx_has_scale);
        }
    }

    return false;
}

bool EffectDisposable::follow(const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    if (PtclMgr::instance() != nullptr && Effect::follow(p_trans, p_angle, p_scale))
    {
        if (!mNode.isLinked())
            PtclMgr::instance()->mEffects.pushBack(&mNode);

        mIsActive = true;
        return true;
    }

    return false;
}

bool EffectDisposable::follow(const sead::Matrixf& mtx, bool mtx_has_scale)
{
    if (PtclMgr::instance() != nullptr && Effect::follow(mtx, mtx_has_scale))
    {
        if (!mNode.isLinked())
            PtclMgr::instance()->mEffects.pushBack(&mNode);

        mIsActive = true;
        return true;
    }

    return false;
}
