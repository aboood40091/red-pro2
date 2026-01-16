#include <player/PlayerBase.h>
#include <player/PlayerHIO_Air.h>
#include <scroll/BgScrollMgr.h>

ActorBgCollisionCheck::SakaType PlayerBase::getSakaType(s32 dir)
{
    s32 saka_type = mSakaType;
    if (isSaka() && BgUnitCode::getSlipAttr(mBgCheckPlayer.getBgCheckData(cDirType_Down)) == BgUnitCode::cSlipAttr_SakaLowPow)
    {
        if (getSakaUpDown(dir) == cSakaUpDown_Downhill)
        {
            saka_type--;
            if (saka_type < 0)
                saka_type = 0;
        }
    }
    return static_cast<ActorBgCollisionCheck::SakaType>(saka_type);
}

static const f32 cSakaMaxSpeedRatio[ActorBgCollisionCheck::cSakaType_Num][PlayerBase::cSakaUpDown_Num] = {
    //  Downhill    Uphill
    {   1.0000f,    1.0000f   },    // cSakaType_None
    {   1.2500f,    0.6875f   },    // cSakaType_Gentle
    {   1.2500f,    0.6875f   },    // cSakaType_Moderate
    {   1.4400f,    0.5000f   },    // cSakaType_Steep
    {   1.6200f,    0.3000f   }     // cSakaType_VerySteep
};

static const f32 cSakaStopAccele[ActorBgCollisionCheck::cSakaType_Num][PlayerBase::cSakaUpDown_Num] = {
    //  Downhill    Uphill
    {   0.0350f,    0.0350f   },    // cSakaType_None
    {   0.0315f,    0.0460f   },    // cSakaType_Gentle
    {   0.0280f,    0.0600f   },    // cSakaType_Moderate
    {   0.0210f,    0.1230f   },    // cSakaType_Steep
    {   0.0140f,    0.1750f   }     // cSakaType_VerySteep
};

static const f32 cSakaMoveAccele[ActorBgCollisionCheck::cSakaType_Num][PlayerBase::cSakaUpDown_Num] = {
    //  Downhill    Uphill
    {   0.1000f,    0.0300f   },    // cSakaType_None
    {   0.0400f,    0.0300f   },    // cSakaType_Gentle
    {   0.0500f,    0.0450f   },    // cSakaType_Moderate
    {   0.0700f,    0.1200f   },    // cSakaType_Steep
    {   0.1700f,    0.1700f   }     // cSakaType_VerySteep
};

static const f32 cSakaSlipOffSpeed[ActorBgCollisionCheck::cSakaType_Num] = {
    0.0f,   // cSakaType_None
    0.0f,   // cSakaType_Gentle
    0.2f,   // cSakaType_Moderate
    0.4f,   // cSakaType_Steep
    0.4f    // cSakaType_VerySteep
};

f32 PlayerBase::getSakaMaxSpeedRatio(s32 dir)
{
    if (isSaka())
        return cSakaMaxSpeedRatio[getSakaType(dir)][getSakaUpDown(dir)];
    else
        return 1.0000f;
}

f32 PlayerBase::getSakaStopAccele(s32 dir)
{
    if (isSaka())
        return cSakaStopAccele[getSakaType(dir)][getSakaUpDown(dir)];
    else
        return 0.0350f;
}

float PlayerBase::getSakaMoveAccele(s32 dir)
{
    if (isSaka())
        return cSakaMoveAccele[getSakaType(dir)][getSakaUpDown(dir)];
    else
        return 0.0300f;
}

float PlayerBase::getIceSakaSlipOffSpeed()
{
    return cSakaSlipOffSpeed[mSakaType] * cDirSpeed[mBgCheckPlayer.getSakaDir()];
}

void PlayerBase::maxFallSpeedSet()
{
    mFallSpeedMax = cMaxFallSpeed;
}

void PlayerBase::setUnkJumpGravity()
{
    setJumpGravity(cPlayerUnkJumpGravityData.thresholds, cPlayerUnkJumpGravityData.normal_gravity);
}

void PlayerBase::setButtonJumpGravity()
{
    PlayerGravityHIO* p_gravity_data = getGravityData();
    setJumpGravity(p_gravity_data->jump_data.thresholds, p_gravity_data->jump_data.button_gravity);
}

void PlayerBase::setNormalJumpGravity()
{
    if (mSpeed.y <= 1.5f)
        mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);

    PlayerGravityHIO* p_gravity_data = getGravityData();
    setJumpGravity(p_gravity_data->jump_data.thresholds, p_gravity_data->jump_data.normal_gravity);
}

void PlayerBase::setJumpGravity()
{
    if (mNoGravityTimer != 0 || isStatus(cStatus_10))
        mAccelY = 0.0f;
    else if (isStatus(cStatus_35))
        setUnkJumpGravity();
    else if (mPlayerKey.buttonJump())
        setButtonJumpGravity();
    else
        setNormalJumpGravity();
}

void PlayerBase::gravitySet()
{
    if (isStatus(cStatus_197))
        return;

    if (isNowBgCross(cBgCross_IsFoot))
        mAccelY = getGravityData()->gravity;
    else
        setJumpGravity();
}

bool PlayerBase::setSandMoveSpeed()
{
    if (!isStatus(cStatus_135) && isOnSinkSand())
    {
        s32 walk_dir;
        if (mPlayerKey.buttonWalk(&walk_dir))
        {
            if (isStatus(cStatus_69))
                mSpeedFMax = cDirSpeed[walk_dir];
            else
                mSpeedFMax = 0.5f * cDirSpeed[walk_dir];
        }
        else
        {
            mSpeedFMax = 0.0f;
        }
        if (mSpeedF * mSpeedFMax < 0.0f)
            mSpeedF = 0.0f;
        else if (sead::Mathf::abs(mSpeedF) > sead::Mathf::abs(mSpeedFMax))
            mSpeedF = mSpeedFMax;
        return true;
    }
    return false;
}

PlayerBase::PowerChangeType PlayerBase::getPowerChangeType(bool penguin_slide)
{
    if (penguin_slide || !isStatus(cStatus_205))
    {
        if (isNowBgCross(cBgCross_IsIce))
            return cPowerChangeType_Ice;

        if (isNowBgCross(cBgCross_IsIceLowSlip) || isNowBgCross(cBgCross_IsSnow))
            return cPowerChangeType_Snow;
    }
    return cPowerChangeType_Normal;
}

void PlayerBase::moveSpeedSet()
{
    if (setSandMoveSpeed())
        return;

    if (isStatus(cStatus_195))
        return;

    s32 walk_dir;
    if (mPlayerKey.buttonWalk(&walk_dir))
    {
        if (_4e8)
        {
            mSpeedFMax = cDirSpeed[walk_dir];
            return;
        }
        f32 max_run_speed_lo = getSpeedData()->max_run_speed_lo * cDirSpeed[walk_dir];
        f32 max_run_speed_hi = getSpeedData()->max_run_speed_hi * cDirSpeed[walk_dir];
        if (!isNowBgCross(cBgCross_IsFoot))
        {
            f32 base_speed = sead::Mathf::abs(mSpeedF);
            f32 speed = base_speed * cDirSpeed[walk_dir];
            if (base_speed >= sead::Mathf::abs(max_run_speed_hi) || mPlayerKey.buttonDush())
                mSpeedFMax = max_run_speed_hi;
            else if (base_speed > sead::Mathf::abs(max_run_speed_lo))
                mSpeedFMax = speed;
            else
                mSpeedFMax = max_run_speed_lo;
        }
        else
        {
            if (mPlayerKey.buttonDush())
                mSpeedFMax = max_run_speed_hi * getSakaMaxSpeedRatio(walk_dir);
            else
                mSpeedFMax = max_run_speed_lo * getSakaMaxSpeedRatio(walk_dir);
        }
    }
    else
    {
        mSpeedFMax = 0.0f;
        if (checkSakaReverse())
            mSpeedF = 0.0f;
        else if (!isStatus(cStatus_DemoControl))
        {
            if (getPowerChangeType(false) == cPowerChangeType_Ice)
                mSpeedFMax = getIceSakaSlipOffSpeed();
            if (isStatus(cStatus_259))
                mSpeedFMax = getIceSakaSlipOffSpeed();
        }
    }

    if (isNowBgCross(cBgCross_IsFoot))
        return;

    if (isStatus(cStatus_147))
        return;

    if (sead::Mathf::abs(mSpeedF) > getSpeedData()->max_run_speed_hi)
    {
        if (mSpeedF < 0.0f)
            mSpeedF = -getSpeedData()->max_run_speed_hi;
        else
            mSpeedF = getSpeedData()->max_run_speed_hi;
    }
}

void PlayerBase::simpleMoveSpeedSet()
{
    if (setSandMoveSpeed())
        return;

    s32 walk_dir;
    if (mPlayerKey.buttonWalk(&walk_dir))
    {
        if (_4e8)
        {
            mSpeedFMax = cDirSpeed[walk_dir];
            return;
        }
        if (mPlayerKey.buttonDush())
            mSpeedFMax = getSpeedData()->max_run_speed_hi * cDirSpeed[walk_dir];
        else
            mSpeedFMax = getSpeedData()->max_run_speed_lo * cDirSpeed[walk_dir];
    }
    else
    {
        mSpeedFMax = 0.0f;
    }
}

void PlayerBase::icePowerChange(bool b)
{
    PowerChangeType power_change_type = getPowerChangeType(false);
    if (power_change_type == cPowerChangeType_Ice || (power_change_type == cPowerChangeType_Snow && b))
    {
        if (mSpeedFMax != 0.0f)
        {
            if (mSpeedF * mSpeedFMax < 0.0f)
                mAccelF *= 0.375f;
            else
            {
                if (!b)
                {
                    if (isSaka())
                        mAccelF *= 0.375f;
                    else if (sead::Mathf::abs(mSpeedF) < 0.5f)
                        mAccelF *= 0.25f;
                }
            }
        }
        else
        {
            if (!isSaka() && sead::Mathf::abs(mSpeedF) < 0.5f)
                mAccelF = 0.004;
            else
                mAccelF *= 0.375f;
        }
    }
}

static const f32 cSakaMoveAcceleRatio[PlayerBase::cSakaUpDown_Num] = {
    1.1f,   // cSakaUpDown_Downhill
    0.9f    // cSakaUpDown_Uphill
};

void PlayerBase::slipPowerSet()
{
    if (isSaka())
    {
        s32 dir = cDirType_Right;
        if (mSpeedF < 0.0f)
            dir = cDirType_Left;
        mAccelF = getSakaMoveAccele(dir);
        s32 walk_dir;
        if (mPlayerKey.buttonWalk(&walk_dir))
            mAccelF *= cSakaMoveAcceleRatio[getSakaUpDown(walk_dir)];
    }
    else
    {
        if (isStatus(cStatus_74))
            mAccelF = 0.05f;
        else
            mAccelF = 0.09f;
    }
    icePowerChange(true);
}

void PlayerBase::getPowerSpeedData(PlayerPowerSpeedData& out_data)
{
    switch (getPowerChangeType(false))
    {
    case cPowerChangeType_Ice:
        out_data = getSpeedData()->power_data_ice;
        break;
    case cPowerChangeType_Snow:
        out_data = getSpeedData()->power_data_snow;
        break;
    default:
        out_data = getSpeedData()->power_data_normal;
        break;
    }
}

void PlayerBase::normalPowerSet()
{
    if (sead::Mathf::abs(mSpeedF) > getSpeedData()->max_run_speed_hi)
        mAccelF = 0.75f;
    else
    {
        PlayerPowerSpeedData power_speed_data;
        getPowerSpeedData(power_speed_data);

        s32 walk_dir;
        if (!mPlayerKey.buttonWalk(&walk_dir))
        {
            if (isSaka())
            {
                s32 dir = cDirType_Right;
                if (mSpeedF < 0.0f)
                    dir = cDirType_Left;
                mAccelF = getSakaStopAccele(dir);
            }
            else if (mSpeedF * cDirSpeed[mDirection] < 0.0f)
            {
                mAccelF = power_speed_data.stop_turn_decel;
            }
            else
            {
                if (sead::Mathf::abs(mSpeedF) < getSpeedData()->max_run_speed_lo)
                    mAccelF = power_speed_data.stop_x_accel;
                else
                    mAccelF = power_speed_data.x_accel_def;
            }
            if (isStatus(cStatus_148))
                mAccelF *= cTurnPowerUpRate;

            icePowerChange(false);
        }
        else
        {
            if (mSpeedF * cDirSpeed[mDirection] < 0.0f)
            {
                mAccelF = power_speed_data.turn_decel;
                if (isStatus(cStatus_148))
                    mAccelF *= cTurnPowerUpRate;
            }
            else if (isSaka())
            {
                s32 dir = cDirType_Right;
                if (mSpeedF < 0.0f)
                    dir = cDirType_Left;
                mAccelF = getSakaMoveAccele(dir) * cSakaMoveAcceleRatio[getSakaUpDown(walk_dir)];
                icePowerChange(false);
            }
            else
            {
                f32 base_speed = sead::Mathf::abs(mSpeedF);
                f32 base_max_speed = sead::Mathf::abs(mSpeedFMax);
                if (base_speed < 0.5f) // Stage 0
                    mAccelF = power_speed_data.x_accel_stage0;
                else if (base_speed < getSpeedData()->max_run_speed_lo) // Stage 1
                {
                    if (mPlayerKey.buttonDush())
                        mAccelF = power_speed_data.x_accel_stage1_dush;
                    else
                        mAccelF = power_speed_data.x_accel_stage1;
                }
                else if (base_speed < getSpeedData()->max_run_speed_md) // Stage 2
                {
                    if (base_max_speed < getSpeedData()->max_run_speed_md)
                        mAccelF = power_speed_data.x_accel_def;
                    else
                        mAccelF = power_speed_data.x_accel_stage2;
                }
                else // Stage 3
                {
                    if (base_max_speed < getSpeedData()->max_run_speed_md)
                        mAccelF = power_speed_data.x_accel_def;
                    else
                        mAccelF = power_speed_data.x_accel_stage3;
                }
            }
        }
    }
}

void PlayerBase::grandPowerSet()
{
    if (isOnSinkSand())
        mAccelF = getSpeedData()->power_data_normal.x_accel_stage0;
    else
    {
        if (isStatus(cStatus_73))
            slipPowerSet(true);
        else
            slipPowerSet(false);
    }
}

void PlayerBase::airPowerSet()
{
    bool is_star = isStar();
    bool is_luigi_phys = isEnableRDashLuigiPhysics();
    const PlayerAirHIO& air_data = cPlayerAirData[is_luigi_phys][is_star];
    if (_4e8 && sead::Mathf::abs(mSpeedF) > 1.0f)
        mAccelF = 0.2f;
    else
    {
        s32 walk_dir;
        if (mPlayerKey.buttonWalk(&walk_dir))
        {
            if (mSpeedF * cDirSpeed[walk_dir] < 0.0f)
                mAccelF = air_data.turn_decel;
            else
            {
                f32 base_speed = sead::Mathf::abs(mSpeedF);
                if (base_speed < 0.5f) // Stage 0
                {
                    mAccelF = air_data.x_accel_stage0;
                }
                else if (base_speed < getSpeedData()->max_run_speed_lo) // Stage 1
                {
                    if (mPlayerKey.buttonDush())
                        mAccelF = air_data.x_accel_stage1_dush;
                    else
                        mAccelF = air_data.x_accel_stage1;
                }
                else if (base_speed < getSpeedData()->max_run_speed_md) // Stage 2
                {
                    mAccelF = air_data.x_accel_stage2;
                }
                else // Stage 3
                {
                    mAccelF = air_data.x_accel_stage3;
                }
            }
        }
        else
        {
            mAccelF = air_data.x_accel_def;
        }
    }
}

void PlayerBase::powerSet()
{
    if (isNowBgCross(cBgCross_IsFoot))
        grandPowerSet();
    else
        airPowerSet();
}

void PlayerBase::getPowerTurnData(PlayerPowerTurnData& out_data)
{
    bool is_star = isStar();
    bool is_luigi_phys = isEnableRDashLuigiPhysics();
    switch (getPowerChangeType(false))
    {
    default:
        break;
    case cPowerChangeType_Normal:
        out_data = cPlayerTurnData[is_luigi_phys].power_turn_normal[is_star];
        break;
    case cPowerChangeType_Ice:
        out_data = cPlayerTurnData[is_luigi_phys].power_turn_ice[is_star];
        break;
    case cPowerChangeType_Snow:
        out_data = cPlayerTurnData[is_luigi_phys].power_turn_snow[is_star];
        break;
    }
}

void PlayerBase::setJumpAirDrift()
{
    const BgScrollMgr& bg_scroll_mgr = *BgScrollMgr::instance();
    const f32 center_prev = (bg_scroll_mgr.getScreenRectPrev().getMin().x + bg_scroll_mgr.getScreenRectPrev().getMax().x) * 0.5f;
    const f32 center_now = bg_scroll_mgr.getScreenCenterX();
    const f32 delta = center_now - center_prev;
    if (sead::Mathf::abs(delta) > 0.5f)
        initAirDriftSpeedF(delta * 0.6f, 60.0f);
}
