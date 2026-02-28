#include <effect/EffectCreateUtil.h>
#include <effect/EffectObj.h>
#include <effect/FollowEffect.h>
#include <effect/PtclMgr.h>
#include <game_info/CourseInfo.h>
#include <map/Bg.h>
#include <map/BgGlobal.h>
#include <map/LayerID.h>

bool EffectCreateUtil::createEffect(EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    FollowEffect effect;
    return effect.createEffect(id, p_trans, p_angle, p_scale);
}

bool EffectCreateUtil::createEffect(EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale)
{
    FollowEffect effect;
    return effect.createEffect(id, mtx, mtx_has_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return createEffect(id, p_trans, p_angle, p_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return createEffect(id, mtx, mtx_has_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, EffectObj* p_effect, EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return p_effect->createEffect(id, p_trans, p_angle, p_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, EffectObj* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return p_effect->createEffect(id, mtx, mtx_has_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Vector3f* p_trans, const Angle3* p_angle, const sead::Vector3f* p_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return p_effect->createEffect(id, p_trans, p_angle, p_scale);
}

bool EffectCreateUtil::createPlayerEffect(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale)
{
    PtclMgr::PlayerNoSetter setter(player_no);
    return p_effect->createEffect(id, mtx, mtx_has_scale);
}

bool EffectCreateUtil::isCreateAboveLayer0(const sead::Vector3f& effect_pos)
{
    if (CourseInfo::instance() != nullptr && BgGlobal::instance() != nullptr)
    {
        if (BgGlobal::instance()->getBgUnit(CourseInfo::instance()->getFileNo(), cLayerID_Layer0) == nullptr)
            return true;

        if (Bg::instance() != nullptr && Bg::instance()->getUnitHitType(effect_pos.x, effect_pos.y, cLayerID_Layer0) == BgUnitCode::cHitType_None)
            return true;
    }

    return false;
}
