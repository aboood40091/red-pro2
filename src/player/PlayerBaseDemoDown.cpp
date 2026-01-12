#include <effect/EffectCreateUtil.h>
#include <map/Bg.h>
#include <player/PlayerBase.h>

void PlayerBase::initializeState_DemoDown()
{
}

void PlayerBase::executeState_DemoDown()
{
}

void PlayerBase::finalizeState_DemoDown()
{
}

bool PlayerBase::isFlyDamageType(DamageType type)
{
    switch (type)
    {
    case cDamageType_HitKnock:
    case cDamageType_Knock:
    case cDamageType_Knock2:
    case cDamageType_SmallKnock:
    case cDamageType_SmallKnock2:
    case cDamageType_SmallKnock3:
        return true;
    default:
        return false;
    }
}

void PlayerBase::setYoganDamageEffect()
{
    sead::Vector3f effect_pos(mPos.x, mWaterSurfacePosY, 6500.0f);
    bool big = isStatus(cStatus_48);
    EffectID effect_id;
    if (mWaterType == cWaterType_LavaWave)
        effect_id = getLavaWaveSplashEffectID(big);
    else
        effect_id = getLavaSplashEffectID(big);
    EffectCreateUtil::createPlayerEffect(mPlayerNo, effect_id, &effect_pos);
    sead::Vector2f wave_pos(mPos.x, mWaterSurfacePosY);
    Bg::instance()->setWaterInWave(wave_pos, 13);
    startSound("SE_PLY_SPLASH_LAVA");
}

void PlayerBase::setPoisonDamageEffect()
{
    sead::Vector3f effect_pos(mPos.x, mWaterSurfacePosY, 6500.0f);
    bool big = isStatus(cStatus_48);
    EffectID effect_id = getPoisonSplashEffectID(big);
    EffectCreateUtil::createPlayerEffect(mPlayerNo, effect_id, &effect_pos);
    sead::Vector2f wave_pos(mPos.x, mWaterSurfacePosY);
    Bg::instance()->setWaterInWave(wave_pos, 20);
    startSound("SE_PLY_SPLASH_POISON");
}
