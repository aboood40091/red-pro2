#include <actor/ActorMgr.h>
#include <map_obj/BalloonChibiYoshi.h>
#include <map_obj/BubbleChibiYoshi.h>
#include <map_obj/LightChibiYoshi.h>
#include <player/PlayerHIO_ChibiYoshi.h>
#include <player/PlayerObject.h>
#include <system/RDashMgr.h>
#include <utility/MathUtil.h>

static const Angle cBalloonChibiYoshiFlyRotStep = 0xAF00000; // ~15.381 degrees
static const Angle cBalloonChibiYoshiFlyRotStopMaxStep = 0x640000; // ~0.55 degrees

void PlayerObject::initializeState_Cloud2()
{
    PlayerBase::initializeState_Cloud2();
}

void PlayerObject::setCloud2StateMove()
{
    mModelMgr.setAnm(PlayerAnmID::wait, 0.0f);
    mAction = cCloudAction_Move;
}

void PlayerObject::setCloud2StateFireCreate()
{
    mModelMgr.setAnm(PlayerAnmID::fire_at, 0.0f);
    mModelMgr.setFrame(0.0f);
    mAngle.y() = getMukiAngle();
    mAction = cCloudAction_FireCreate;
    _2a00 = mDirection;
}

bool PlayerObject::checkCloud2StateCrouch()
{
    if (!mPlayerKey.buttonCrouch())
        return false;

    if (isCarry())
        return false;

    onStatus(cStatus_121);
    mModelMgr.setAnm(PlayerAnmID::stoop_start, 0.0f);
    mAction = cCloudAction_Crouch;
    return true;
}

void PlayerObject::executeState_Cloud2()
{
    if (updateCloudMove())
        return;

    switch (mAction)
    {
    default:
        break;
    case cCloudAction_Idle:
    case cCloudAction_FireCreateEnd:
    case cCloudAction_ThrowEnd:
        if (mModelMgr.isAnmStop())
        {
            finalizeThrowCommonBase();
            setCloud2StateMove();
        }
        // fallthrough
    case cCloudAction_Move:
        if (!setRideOffPlayerJump(PLAYER_JUMP_SPEED - 0.2f, 0.0f))
        {
            if (checkSetFireBall())
            {
                setCloud2StateFireCreate();
            }
            else if (checkEnableThrow())
            {
                initializeThrowCommonBase();
                mAngle.y() = getMukiAngle();
                mAction = cCloudAction_Throw;
            }
            else
            {
                checkCloud2StateCrouch();
            }
        }
        break;
    case cCloudAction_Crouch:
        if (mModelMgr.isAnmStop())
            mModelMgr.setAnm(PlayerAnmID::stoop, 0.0f);
        if (!mPlayerKey.buttonCrouch())
        {
            mModelMgr.setAnm(PlayerAnmID::wait, 10.0f, 0.0f);
            mActionTimer = 10;
            offStatus(cStatus_121);
            mAction = cCloudAction_CrouchEnd;
        }
        break;
    case cCloudAction_CrouchEnd:
        if (checkSetFireBall())
            setCloud2StateFireCreate();
        if (mActionTimer == 0)
            setCloud2StateMove();
        break;
    case cCloudAction_FireCreate:
        if (mModelMgr.checkFrame(4.0f))
        {
            createFireBall();
            mAction = cCloudAction_FireCreateEnd;
        }
        break;
    case cCloudAction_Throw:
        if (mModelMgr.checkFrame(5.0f))
        {
            mAction = cCloudAction_ThrowEnd;
            setThrowActor();
        }
        break;
    }
}

void PlayerObject::finalizeState_Cloud2()
{
    PlayerBase::finalizeState_Cloud2();
    if (mAction == cCloudAction_Throw)
        releaseCarryActor();
    else if (mAction == cCloudAction_FireCreate)
        createFireBall();
}

void PlayerObject::setBalloonChibiYoshiFlyAnm(s32 anm_id, f32 blend_duration)
{
    PlayerObject* p_player_hang_child = sead::DynamicCast<PlayerObject>(ActorMgr::instance()->getActorPtr(mPlayerHangChildActorID));
    if (p_player_hang_child != nullptr)
    {
        if (anm_id != PlayerAnmID::PL_spin_jump && anm_id == PlayerAnmID::spin_jump3)
            p_player_hang_child->setPlayerHangChildAnm(PlayerAnmID::hang2_rot, blend_duration);
        else
            p_player_hang_child->setPlayerHangChildAnm(PlayerAnmID::hang2_wait, blend_duration);

        if (anm_id != PlayerAnmID::PL_spin_jump)
            return;
    }
    mModelMgr.setAnm(anm_id, blend_duration, 0.0f);
}

void PlayerObject::initializeState_BalloonChibiYoshiFly()
{
    onStatus(cStatus_CanSetSpeedChibiYoshi);
    onStatus(cStatus_142);
    onStatus(cStatus_157);
    onStatus(cStatus_168);
    onStatus(cStatus_BalloonChibiYoshiFly);
    setScrollMode(cScrollMode_6);
    _2a78 = 0;
    switch (mChangeStateParam)
    {
    default:
        break;
    case 0:
        mAction = cBalloonChibiYoshiFlyAction_Fly;
        mSpeed.y = cBalloonChibiYoshiFlyInitSpeedY;
        mSpinRotStep = cBalloonChibiYoshiFlyRotStep;
        _2a6c = 10;
        _2a78 = 20;
        mLiftUpOffsetRatio = 0.5f;
        break;
    case 1:
        mAction = cBalloonChibiYoshiFlyAction_FlyForceFall;
        mSpeed.y = cBalloonChibiYoshiFlyInitSpeedY;
        mSpinRotStep = cBalloonChibiYoshiFlyRotStep;
        _2a6c = 10;
        _2a78 = 20;
        mLiftUpOffsetRatio = 0.5f;
        offStatus(cStatus_142);
        break;
    case 2:
        mAction = cBalloonChibiYoshiFlyAction_Fly;
        f32 speed_y = mSpeed.y * cBalloonChibiYoshiFlySmallInitSpeedYDecel;
        if (speed_y > cBalloonChibiYoshiFlyInitSpeedYMax)
            speed_y = cBalloonChibiYoshiFlyInitSpeedYMax;
        mSpeed.y = speed_y;
        mLiftUpOffsetRatio = 1.0f;
        break;
    }
    if (isStatus(cStatus_142))
        mModelMgr.onBalloonChibiYoshiFly();
    setBalloonChibiYoshiFlyAnm(PlayerAnmID::spin_jump3, 5.0f);
}

bool PlayerObject::isEnableBalloonChibiYoshiFlySpin()
{
    return isStatus(cStatus_CanFlyBalloonChibiYoshi);
}

void PlayerObject::executeState_BalloonChibiYoshiFly()
{
    MathUtil::calcTimer(&_2a6c);
    MathUtil::calcTimer(&mBalloonChibiYoshiFlyAscendGravityTimer);
    sead::Mathf::chase(&mLiftUpOffsetRatio, 1.0f, 0.05f);

    if (checkCarryThrow())
        return;

    if (_2a6c == 0)
        mSpinRotStep.addCalcAngle(0, 1.0f, cBalloonChibiYoshiFlyRotStopMaxStep);
    else if (isNowBgCross(cBgCross_IsHead))
        _2a6c = _2a78;

    if (mSpinRotStep != 0)
        mAngle.y() += mSpinRotStep;
    else
    {
        Angle target = getMukiAngle();
        Angle step = 0x4000000; // 5.625 degrees
        mAngle.y().chaseRest(target, step);
    }

    bool landed = false;
    if (isNowBgCross(cBgCross_IsFoot) && _2a78 == 0)
        landed = true;

    if ((RDashMgr::instance()->isNSLU() && mBgCheckPlayer.checkFoot() && isNowBgCross(cBgCross_IsHead)) ||
        landed)
    {
        setLandJumpEffect();
        mModelMgr.setAnm(PlayerAnmID::jumped, 0.0f);
        changeState(StateID_Land, 0);
        return;
    }

    if (_2a78 == 0 && !isEnableBalloonChibiYoshiFlySpin())
    {
        changeState(StateID_Fall, cAnmBlend_Enable);
        return;
    }

    if (isStatus(cStatus_142) &&
        isEnableBalloonChibiYoshiFlySpin() &&
        mPlayerKey.triggerShakeJump() &&
        mActionTimer == 0 &&
        mSpeed.y < cBalloonChibiYoshiFlySpinTrigSpeedY)
    {
        onStatus(cStatus_141);
        mActionTimer = cBalloonChibiYoshiFlyAscendMinTime;
        mBalloonChibiYoshiFlyAscendGravityTimer = cBalloonChibiYoshiFlyAscendGravityTime;
        mSpeed.y += cBalloonChibiYoshiFlySpinAddSpeedY;
        if (mSpeed.y >= cBalloonChibiYoshiFlySpinSpeedYMax)
            mSpeed.y = cBalloonChibiYoshiFlySpinSpeedYMax;
        setBalloonChibiYoshiFlyAnm(PlayerAnmID::spin_jump3, 5.0f);
        mAction = cBalloonChibiYoshiFlyAction_Fly;
        mSpinRotStep = cBalloonChibiYoshiFlyRotStep;
        _2a6c = 10;
    }

    DirType walk_dir;
    if (!mPlayerKey.buttonWalk(&walk_dir))
    {
        mAccelF = cBalloonChibiYoshiFlyAccelF;
        f32 max_speed_F = sead::Mathf::abs(mSpeedF);
        if (max_speed_F > cBalloonChibiYoshiFlyMaxSpeedF)
            max_speed_F = cBalloonChibiYoshiFlyMaxSpeedF;
        mMaxSpeedF = max_speed_F * cDirSpeed[mDirection];
    }
    else
    {
        mAccelF = cBalloonChibiYoshiFlyAccelF;
        mMaxSpeedF = cBalloonChibiYoshiFlyMaxSpeedF * cDirSpeed[walk_dir];
    }
    mMaxFallSpeed = cBalloonChibiYoshiFlyMaxFallSpeed;

    switch (mAction)
    {
    case cBalloonChibiYoshiFlyAction_Fall:
        mAccelY = cBalloonChibiYoshiFlyDescendGravity;
        break;
    default:
        break;
    case cBalloonChibiYoshiFlyAction_Fly:
        if (mBalloonChibiYoshiFlyAscendGravityTimer == 0)
            mAccelY = cBalloonChibiYoshiFlyAscendEndGravity;
        else
            mAccelY = cBalloonChibiYoshiFlyAscendGravity[0];
        if (mActionTimer == 0 && mSpeed.y < cBalloonChibiYoshiFlyDescendStartSpeedY)
        {
            mAction = cBalloonChibiYoshiFlyAction_Fall;
            setBalloonChibiYoshiFlyAnm(PlayerAnmID::PL_spin_jump, 30.0f);
        }
        break;
    case cBalloonChibiYoshiFlyAction_FlyForceFall:
        mAction = cBalloonChibiYoshiFlyAction_Fall;
        break;
    }
}

void PlayerObject::finalizeState_BalloonChibiYoshiFly()
{
    offStatus(cStatus_CanSetSpeedChibiYoshi);
    offStatus(cStatus_142);
    offStatus(cStatus_157);
    offStatus(cStatus_168);
    offStatus(cStatus_BalloonChibiYoshiFly);
    setScrollMode(cScrollMode_0);
    mSpinRotStep = 0;
}

bool PlayerObject::setBalloonChibiYoshiFly()
{
    BalloonChibiYoshi* p_balloon_chibi_yoshi = sead::DynamicCast<BalloonChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
    if (p_balloon_chibi_yoshi != nullptr)
    {
        if (isNowBgCross(cBgCross_IsFoot) || isStatus(cStatus_RideCloud))
        {
            if (checkChibiYoshiLiftUpBlocked() || !p_balloon_chibi_yoshi->setShakeAction(this))
                changeState(StateID_BalloonChibiYoshiFly, 1);
            else
                changeState(StateID_BalloonChibiYoshiFly, 0);
            return true;
        }
        else
        {
            if (p_balloon_chibi_yoshi->setShakeAction(this))
            {
                changeState(StateID_BalloonChibiYoshiFly, 0);
                return true;
            }
        }
    }
    return false;
}

bool PlayerObject::setBalloonChibiYoshiFlySmall(f32 speed_y, f32 speed_F)
{
    BalloonChibiYoshi* p_balloon_chibi_yoshi = sead::DynamicCast<BalloonChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
    if (p_balloon_chibi_yoshi != nullptr)
    {
        if (p_balloon_chibi_yoshi->isBalloonFly())
        {
            mSpeed.y = speed_y;
            mSpeedF = speed_F;
            changeState(StateID_BalloonChibiYoshiFly, 2);
            return true;
        }
    }
    return false;
}

void PlayerObject::updateBalloonChibiYoshiFly()
{
    offStatus(cStatus_CanFlyBalloonChibiYoshi);
    BalloonChibiYoshi* p_balloon_chibi_yoshi = sead::DynamicCast<BalloonChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
    if (p_balloon_chibi_yoshi != nullptr)
    {
        if (p_balloon_chibi_yoshi->isBalloonFly())
        {
            if (!isStatus(cStatus_BalloonChibiYoshiFly))
                p_balloon_chibi_yoshi->setBalloonFlyEnd();
            else
                onStatus(cStatus_CanFlyBalloonChibiYoshi);
        }
    }
    if (!isStatus(cStatus_CanFlyBalloonChibiYoshi))
    {
        if (mModelMgr.isLiftUp())
        {
            mModelMgr.offBalloonChibiYoshiFly();
            mModelMgr.releaseBodyAnm(0.0f);
        }
    }
}

void PlayerObject::setPlayerHangChild(PlayerObject* p_player)
{
    mPlayerHangChildActorID = p_player->getActorUniqueID();

    PlayerObject* p_player_hang_parent = sead::DynamicCast<PlayerObject>(ActorMgr::instance()->getActorPtr(mPlayerHangParentActorID));
    if (p_player_hang_parent != nullptr)
        mModelMgr.setAnm(PlayerAnmID::hang2_wait, 5.0f, 0.0f);
    else
        mModelMgr.setAnm(PlayerAnmID::PL_spin_jump, 30.0f, 0.0f);
}

void PlayerObject::releasePlayerHangChild()
{
    mPlayerHangChildActorID.invalidate();
}

bool PlayerObject::isPlayerHangChild()
{
    return mPlayerHangChildActorID.isValid();
}

void PlayerObject::setBubbleChibiYoshiShakeAnm(f32 blend_duration)
{
    mModelMgr.onBubbleChibiYoshiShake();
    mModelMgr.setCarryBodyAnm(blend_duration, true);
    mIsBubbleChibiYoshiShake = false;
}

bool PlayerObject::setBubbleChibiYoshiShake()
{
    if (!mModelMgr.isBubbleChibiYoshiShake() && _2a84 == 0)
        setBubbleChibiYoshiShakeAnm(0.0f);
    return true;
}

void PlayerObject::updateBubbleChibiYoshiShake()
{
    MathUtil::calcTimer(&_2a80);

    if (!isEnableSpinAction())
    {
        mIsBubbleChibiYoshiShake = false;
        _2a80 = 0;
        _2a84 = 0;
        mModelMgr.offBubbleChibiYoshiShake();
        return;
    }

    switch (_2a84)
    {
    default:
        break;
    case 0:
        if (mModelMgr.isBubbleChibiYoshiShake())
        {
            if (mModelMgr.checkBodyFrame(10.0f))
            {
                _2a80 = 12;
                _2a84 = 1;
            }
        }
        break;
    case 1:
        if (mPlayerKey.triggerShakeJump())
            mIsBubbleChibiYoshiShake = true;
        if (_2a80 == 0)
        {
            if (mIsBubbleChibiYoshiShake)
            {
                setBubbleChibiYoshiShakeAnm(3.0f);
                _2a84 = 2;
            }
            else
            {
                _2a84 = 0;
            }
        }
        break;
    case 2:
        if (mModelMgr.isBubbleChibiYoshiShake())
        {
            if (mPlayerKey.triggerShakeJump())
                mIsBubbleChibiYoshiShake = true;
            if (mModelMgr.isBodyAnmStop())
            {
                if (mIsBubbleChibiYoshiShake)
                    setBubbleChibiYoshiShakeAnm(0.0f);
                else
                    _2a84 = 0;
            }
        }
        else
        {
            _2a84 = 0;
        }
        break;
    }

    if (mModelMgr.isBubbleChibiYoshiShake())
    {
        if (mModelMgr.checkBodyFrame(2.0f))
        {
            BubbleChibiYoshi* p_bubble_chibi_yoshi = sead::DynamicCast<BubbleChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
            if (p_bubble_chibi_yoshi != nullptr)
                p_bubble_chibi_yoshi->setShakeAction(this);
        }
        if (mModelMgr.isBodyAnmStop())
        {
            mModelMgr.offBubbleChibiYoshiShake();
            mModelMgr.setCarryBodyAnm(5.0f, true);
        }
    }
}

bool PlayerObject::setLightChibiYoshiShake()
{
    LightChibiYoshi* p_light_chibi_yoshi = sead::DynamicCast<LightChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
    if (p_light_chibi_yoshi != nullptr)
    {
        if (p_light_chibi_yoshi->setShakeAction(this))
            return true;
    }
    return false;
}

void PlayerObject::setChibiYoshiSpeed(f32 speed_y, f32 speed_F)
{
    if (!isStatus(cStatus_CanSetSpeedChibiYoshi))
        return;

    mSpeedF = speed_F;
    mSpeed.y = speed_y;
}
