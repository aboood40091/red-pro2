#include <effect/EffectCreateUtil.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>
#include <utility/MathUtil.h>

void PlayerBase::setHipAttackEffect()
{
    mHipAttackEffectPos.set(
        mPos.x,
        mPos.y,
        getEffectZPos()
    );
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        &mHipAttackEffect,
        getHipDropEffectID(),
        &mHipAttackEffectPos
    );
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        getHipDropSurfaceEffectID(),
        &mHipAttackEffectPos
    );
}

bool PlayerBase::updateHipAttackEffect()
{
    if (!mHipAttackEffect.isAlive())
        return false;

    mHipAttackEffect.follow(&mHipAttackEffectPos);
    return true;
}

void PlayerBase::setHipAttackDropEffect()
{
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        &mHipAttackDropEffect,
        getHipDropBlurEffectID(),
        &mPos
    );
}

void PlayerBase::setSlipSmokeEffect()
{
    if (mBgAttr == cBgAttr_Water1)
    {
        // setSlipOnWaterEffect(&mSlipSmokeEffect);
    }
    else
    {
        sead::Vector3f effect_pos;
        mpModelBaseMgr->getJointPos(&effect_pos, "skl_root");
        effect_pos.z = getEffectZPos();
        EffectCreateUtil::createPlayerEffect(
            mPlayerNo,
            &mSlipSmokeEffect,
            getSlipSmokeEffectID(),
            &effect_pos
        );
    }
}

void PlayerBase::fadeOutTurnEffect()
{
    if (mIsTurnBrakeEffectEnable)
    {
        mTurnBrakeEffect.followFade();
        mIsTurnBrakeEffectEnable = false;
    }
    if (mIsTurnBrakeSmokeEffectEnable)
    {
        mTurnBrakeSmokeEffect.followFade();
        mIsTurnBrakeSmokeEffectEnable = false;
    }
}

void PlayerBase::setTurnSmokeEffect(bool with_brake)
{
    sead::Vector3f effect_pos;
    mpModelBaseMgr->getJointPos(&effect_pos, "skl_root");
    if (mBgAttr == cBgAttr_Water1)
    {
        if (mPos.y < mWaterSurfacePosY - 4.0f)
        {
            fadeOutTurnEffect();
            return;
        }
        effect_pos.y = mWaterSurfacePosY;
    }
    effect_pos.z = getEffectZPos();
    Angle3 effect_angle;
    if (_25f0 == 1)
    {
        effect_angle.y() = sead::Mathi::cQuarterRoundIdx;
        effect_angle.z() = mBgCheckPlayer.getSakaBaseAngle();
    }
    else
    {
        effect_angle.y() = sead::Mathi::neg(sead::Mathi::cQuarterRoundIdx);
        effect_angle.z() = mBgCheckPlayer.getSakaBaseAngle();
    }
    if (with_brake)
    {
        if (mIsTurnBrakeEffectEnable && mTurnBrakeBgAttr == mBgAttr)
        {
            mTurnBrakeEffect.follow(&effect_pos, &effect_angle);
        }
        else
        {
            EffectCreateUtil::createPlayerEffect(
                mPlayerNo,
                &mTurnBrakeEffect,
                getTurnBrakeEffectID(),
                &effect_pos,
                &effect_angle
            );
            mIsTurnBrakeEffectEnable = true;
        }
    }
    else
    {
        mTurnBrakeEffect.followFade();
        mIsTurnBrakeEffectEnable = false;
    }
    if (mIsTurnBrakeSmokeEffectEnable && mTurnBrakeBgAttr == mBgAttr)
    {
        mTurnBrakeSmokeEffect.follow(&effect_pos, &effect_angle);
    }
    else
    {
        EffectCreateUtil::createPlayerEffect(
            mPlayerNo,
            &mTurnBrakeSmokeEffect,
            getTurnBrakeSmokeEffectID(),
            &effect_pos,
            &effect_angle
        );
        mIsTurnBrakeSmokeEffectEnable = true;
    }
    mTurnBrakeBgAttr = mBgAttr;
}

void PlayerBase::setRunFootEffect()
{
    if (isOnSinkSand())
        return;

    if (!isStatus(cStatus_136))
        return;

    f32 max_run_speed_hi = getSpeedData()->max_run_speed_hi;

    EffectID effect_id = cEffectID_None;
    if (sead::Mathf::abs(mSpeedF) < max_run_speed_hi)
        effect_id = getRunSmokeEffectID();
    else
        effect_id = getDashSmokeEffectID();
    if (effect_id == cEffectID_None)
        return;

    sead::Vector3f effect_pos(
        mPos.x,
        mPos.y,
        getEffectZPos()
    );
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        &mFootEffect,
        effect_id,
        &effect_pos
    );
}

void PlayerBase::setLandSmokeEffectLight()
{
    sead::Vector3f effect_pos(
        mPos.x,
        mPos.y,
        getEffectZPos()
    );
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        getLandingSmokeEffectID(),
        &effect_pos
    );
}

void PlayerBase::setStartJumpEffect(bool with_smoke)
{
    if (!isNowBgCross(cBgCross_IsFoot))
        return;

    if (isOnSinkSand())
    {
        // setSandJumpEffect();
        onStatus(cStatus_SinkSandSurfJump);
    }
    else
    {
        // if (!setSandFunsuiLandEffect())
            if (with_smoke)
                setLandSmokeEffectLight();
    }
}

void PlayerBase::setLandJumpEffect(/* bool with_smoke */)
{
    setLandSE();
    // if (!setSandFunsuiLandEffect())
    //     if (with_smoke)
            setLandSmokeEffectLight();
}

void PlayerBase::endWaterFunsuiEffect()
{
    if (mWaterFunsuiEffectStep == 2)
        mWaterFunsuiEffect.cleanup();

    mWaterFunsuiEffectStep = 1;
    mWaterFunsuiEffectTimer = 10;
}

void PlayerBase::updateWaterFunsuiEffect()
{
    if (mWaterFunsuiEffectStep == 0)
        return;

    MathUtil::calcTimer(&mWaterFunsuiEffectTimer);
}

void PlayerBase::setWaterInEffect(const sead::Vector3f& pos, bool deep)
{
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        &(mWaterEffect[0]),
        getWaterSplashEffectID(isStatus(cStatus_48)),
        &pos
    );
}

void PlayerBase::setWaterOutEffect(const sead::Vector3f& pos, bool deep)
{
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        &(mWaterEffect[2]),
        getWaterSplashSEffectID(),
        &pos
    );
}

void PlayerBase::updateWaterEffect()
{
    for (s32 i = 0; i < 3; ++i)
    {
        if (mWaterEffect[i].isAlive())
        {
            sead::Vector3f effect_pos;
            mWaterEffect[i].getMtx().getTranslation(effect_pos);
            f32 surface_y;
            ActorBgCollisionCheck::checkWater(&surface_y, effect_pos, mLayer);
            mWaterEffect[i].follow(&effect_pos);
        }
    }
}

void PlayerBase::setHipDropExEffect()
{
    if (mHipAttackEffectStep == 2)
        return;

    mHipAttackEffect.kill();
    EffectCreateUtil::createPlayerEffect(
        mPlayerNo,
        getHipDropExEffectID(),
        &mHipAttackEffectPos
    );
    mHipdropExEffect.set(mHipAttackEffectPos);
}

void PlayerBase::setSandEffect()
{
}

void PlayerBase::setVsPlHipAttackEffect()
{
}
