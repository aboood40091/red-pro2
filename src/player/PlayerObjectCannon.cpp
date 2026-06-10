#include <map_obj/ChibiYoshiBase.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

void PlayerObject::setCannonJumpCommon(const sead::Vector3f& pos, const sead::Vector2f& speed)
{
    mPos.x = pos.x;
    mPos.y = pos.y - mHeight * 0.5f - 2.0f;
    mPosPrev = mPos;
    mPosPrev2 = mPos;

    endDemoDokanCannon();

    mSpeedF = speed.x;
    mMaxSpeedF = speed.x;
    mSpeed.y = speed.y;
    mDirection = speed.x > 0.0f ? cDirType_Right : cDirType_Left;
}

bool PlayerObject::setCannonJump(const sead::Vector3f& pos, const sead::Vector2f& speed, s32 jump_time)
{
    setCannonJumpCommon(pos, speed);
    Actor* p_actor_chibi_yoshi = getCarryChibiYoshi();
    if (p_actor_chibi_yoshi != nullptr)
    {
        ChibiYoshiBase* p_chibi_yoshi = sead::DynamicCast<ChibiYoshiBase>(p_actor_chibi_yoshi);
        if (p_chibi_yoshi != nullptr)
            p_chibi_yoshi->setCannonJump(pos, speed, jump_time);
    }
    mCannonJumpSoundType = cCannonJumpSoundType_Normal;
    changeState(StateID_CannonJump, jump_time);
    return true;
}

bool PlayerObject::setDemoBossCannonWarp(const sead::Vector3f& pos, const sead::Vector2f& speed, CannonJumpSoundType jump_sound_type)
{
    setCannonJumpCommon(pos, speed);
    mCannonJumpSoundType = jump_sound_type;
    changeDemoState(StateID_DemoBossCannonWarp, 0);
    return true;
}

void PlayerObject::initCannonJump()
{
    onStatus(cStatus_CannonShot);
    onStatus(cStatus_147);
    onStatus(cStatus_NoBgCrossUpdate);
    onStatus(cStatus_NoEntryReactCc);
    mNowBgCross.reset();
    Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_5);
    startVoiceSound(mCannonJumpSoundType == cCannonJumpSoundType_Normal ? CANNON_SHOT_S : CANNON_SHOT);
    mModelMgr.setAnm(PlayerAnmID::shoot);
    mAngle.y() = getMukiAngle();
    mAngle.x() = sead::Mathf::atan2Idx(-mSpeed.y, sead::Mathf::abs(mSpeedF));
}

void PlayerObject::finCannonJump()
{
    offStatus(cStatus_CannonShot);
    offStatus(cStatus_147);
    offStatus(cStatus_NoBgCrossUpdate);
    offStatus(cStatus_NoEntryReactCc);
    mAngle.x() = 0;
}

void PlayerObject::initializeState_CannonJump()
{
    initCannonJump();
    PlayerMgr::instance()->setCannonJump(mPlayerNo);
    onStatus(cStatus_CannonJump);
    if (isStatus(cStatus_154))
        onStatus(cStatus_153);
    mPlayerKey.onStatus(PlayerKey::cStatus_NoCross);
    mPlayerKey.onStatus(PlayerKey::cStatus_NoJump);
    mCannonJumpTimer = mChangeStateParam;
    mCannonJumpStartPos = mPos;
}

void PlayerObject::finalizeState_CannonJump()
{
    finCannonJump();
    PlayerMgr::instance()->resetCannonJump(mPlayerNo);
    offStatus(cStatus_CannonJump);
    offStatus(cStatus_153);
    offStatus(cStatus_154);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoCross);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);
    f32 max_speed_F = getSpeedData()->max_run_speed_hi;
    mSpeedF = sead::Mathf::clamp2(-max_speed_F, mSpeedF, max_speed_F);
}

void PlayerObject::executeState_CannonJump()
{
    switch (mAction)
    {
    default:
        break;
    case 0:
        {
            setCcAtCannon();
            if (mCannonJumpTimer != 0)
            {
                mAccelF = 0.0f;
                mAccelY = 0.0f;
            }
            else
            {
                mAccelY = -0.5f;
                if (sead::Mathf::abs(mSpeedF) >= 1.0f)
                    mAccelF = 0.03f;
                else
                    mAccelF = 0.0f;
            }
            maxFallSpeedSet();
            sead::Vector3f dist = mCannonJumpStartPos - mPos;
            dist.z = 0.0f;
            if (dist.length() >= 8.0f)
            {
                if (!isStatus(cStatus_154))
                    offStatus(cStatus_NoBgCrossUpdate);
                offZPosSetNone();
            }
            mAngle.x() = sead::Mathf::atan2Idx(-mSpeed.y, sead::Mathf::abs(mSpeedF));
            if (isNowBgCross(cBgCross_IsHead) ||
                mSpeedF != 0.0f && (isNowBgCross(cBgCross_IsWallTouchL) || isNowBgCross(cBgCross_IsWallTouchR)))
            {
                mSpeed.y = 0.0f;
                changeState(StateID_Fall, cAnmBlend_Enable);
            }
            else
            {
                if (mSpeed.y <= 0.0f && sead::Mathf::abs(mSpeedF) < 0.1f)
                    changeState(StateID_Fall, cAnmBlend_Enable);
                if (isNowBgCross(cBgCross_IsFoot))
                {
                    mModelMgr.setAnm(PlayerAnmID::shoot_slip);
                    mAction = 1;
                    mAngle.x() = 0;
                    offStatus(cStatus_CannonShot);
                }
            }
        }
        break;
    case 1:
        if (mSpeedF != 0.0f)
            setCcAtCannon();
        gravitySet();
        maxFallSpeedSet();
        mMaxSpeedF = 0.0f;
        powerSet();
        if (isNowBgCross(cBgCross_IsFoot))
        {
            setCrouchSmokeEffect();
            if (!(sead::Mathf::abs(mSpeedF) < 1.0f && checkJumpTrigger()) && sead::Mathf::abs(mSpeedF) <= 0.1f)
            {
                mModelMgr.setAnm(PlayerAnmID::shoot_slip_end);
                mAction = 2;
                mSpeedF = 0.0f;
            }
        }
        else
        {
            mAction = 0;
            mModelMgr.setAnm(PlayerAnmID::shoot);
        }
        break;
    case 2:
        {
            bool fall = true;
            bool walk = false;
            if (isNowBgCross(cBgCross_IsFoot))
            {
                fall = false;
                if (!checkJumpTrigger())
                    walk = true;
            }
            if (fall)
                changeState(StateID_Fall, cAnmBlend_Enable);
            else if (walk && mModelMgr.isAnmStop())
                changeState(StateID_Walk, cAnmBlend_Enable);
        }
        break;
    }
}

bool PlayerObject::setCannonWarpPos(const sead::Vector3f& pos)
{
    if (isStatus(cStatus_CannonWarp))
    {
        mPos = pos;
        mPosPrev = pos;
        mPosPrev2 = pos;
        return true;
    }
    return false;
}

bool PlayerObject::setCannonWarpSpeed(const sead::Vector2f& speed)
{
    if (isStatus(cStatus_CannonWarp))
    {
        mSpeedF = speed.x;
        mMaxSpeedF = mSpeedF;
        mSpeed.y = speed.y;
        return true;
    }
    return false;
}

bool PlayerObject::setCannonWarpScale(f32 scale)
{
    if (isStatus(cStatus_CannonWarp))
    {
        mScale.set(scale, scale, scale);
        return true;
    }
    return false;
}

bool PlayerObject::setCannonWarpAngleX(Angle angle_x)
{
    if (isStatus(cStatus_CannonWarp))
    {
        mAngle.x() = angle_x;
        return true;
    }
    return false;
}

void PlayerObject::initializeState_DemoBossCannonWarp()
{
    initCannonJump();
    onStatus(cStatus_CannonWarp);
    mAccelF = 0.0f;
    mAccelY = 0.0f;
    mCannonJumpStartPos = mPos;
}

void PlayerObject::finalizeState_DemoBossCannonWarp()
{
    finCannonJump();
    mScale.set(1.0f, 1.0f, 1.0f);
    offStatus(cStatus_CannonWarp);
}

void PlayerObject::executeState_DemoBossCannonWarp()
{
    mSpeed.x = mSpeedF;
    mPos += mSpeed;
}
