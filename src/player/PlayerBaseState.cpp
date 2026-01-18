#include <actor/ActorMgr.h>
#include <game/SubjectMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>
#include <utility/MathUtil.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, None)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Walk)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Jump)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Fall)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Land)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Crouch)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SitJump)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Slip)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Turn)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, HipAttack)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Funsui)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Cloud)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Cloud2)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, Swim)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, JumpDai)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, PlayerJumpDai)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, WaitJump)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, AnimePlay)

void PlayerBase::initializeState_None()
{
}

void PlayerBase::executeState_None()
{
}

void PlayerBase::finalizeState_None()
{
}

void PlayerBase::initializeState_Walk()
{
}

void PlayerBase::executeState_Walk()
{
    if (mSpeedF != 0.0f)
    {
        if (!(isNowBgCross(cBgCross_IsSlideSlope) && !mPlayerKey.buttonWalk()))
            offStatus(cStatus_SlideSlope);
    }
    else
    {
        if (isNowBgCross(cBgCross_IsSlideSlope) && !mPlayerKey.buttonWalk())
            onStatus(cStatus_SlideSlope);
    }
}

void PlayerBase::finalizeState_Walk()
{
    offStatus(cStatus_SlideSlope);
}

void PlayerBase::initializeState_Crouch()
{
}

void PlayerBase::executeState_Crouch()
{
}

void PlayerBase::finalizeState_Crouch()
{
}

void PlayerBase::initializeState_Turn()
{
}

void PlayerBase::executeState_Turn()
{
}

void PlayerBase::finalizeState_Turn()
{
}

void PlayerBase::initializeState_Funsui()
{
    onStatus(cStatus_58);
    // onStatus(cStatus_248);
    onStatus(cStatus_255);
    mAccelY = 0.0f;
    mSpeedF *= 0.7f;
    mSpeed.y = 0.1f;

    mFunsuiPos.x = mPos.x;
    mFunsuiPos.y = mPos.y;
    mAction = cFunsuiAction_Ascend;

    if (mPlayerNo >= 0)
    {
        Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_PlayerImpact);
        mActionTimer = 8;
    }
}

Angle PlayerBase::getMukiAngle(s32 dir)
{
    if (dir == cDirType_Right)
        return  0x30000000; //  67.5 degrees
    else
        return -0x30000000; // -67.5 degrees
}

bool PlayerBase::turnAngle()
{
    Angle target = getMukiAngle();
    Angle step = 0x20000000; // 45 degrees

    return mAngle.y().chaseRest(target, step);
}

void PlayerBase::executeState_Funsui()
{
    static const f32 c_funsui_walk_target_speeds[] = { 0.35f, 0.5f };
    static_assert(sizeof(c_funsui_walk_target_speeds) / sizeof(f32) == cFunsuiType_Num);

    if (mPlayerNo >= 0 && mActionTimer == 0)
    {
        Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_PlayerRepeat);
        mActionTimer = 8;
    }

    turnAngle();

    switch (mAction)
    {
    default:
        break;
    case cFunsuiAction_Ascend:
        mSpeed.y = 0.1f;
        sead::Mathf::chase(&mPos.x, mFunsuiPos.x, 3.0f);
        sead::Mathf::chase(&mPos.y, mFunsuiPos.y, 3.0f);
        break;
    case cFunsuiAction_Release:
        gravitySet();
        maxFallSpeedSet();
        if (mSpeed.y <= 0.0f || isNowBgCross(cBgCross_IsHead))
        {
            releaseFunsuiAction();
            return;
        }
        break;
    }

    f32 base_speed = c_funsui_walk_target_speeds[mFunsuiType];
    f32 target_speed = 0.0f;

    s32 walk_dir;
    if (mPlayerKey.buttonWalk(&walk_dir))
        target_speed = base_speed * cDirSpeed[walk_dir];

    mSpeedFMax = target_speed;

    if (sead::Mathf::abs(mSpeedF) > base_speed)
        mAccelF = 0.1f;
    else
        mAccelF = 0.04f;
}

void PlayerBase::finalizeState_Funsui()
{
    offStatus(cStatus_58);
    offStatus(cStatus_248);
    offStatus(cStatus_255);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);
}

void PlayerBase::initializeState_Cloud()
{
    SubjectMgr::instance()->setCloudOn();
    startSound("SE_PLY_RIDE_CLOUD");
    onStatus(cStatus_119);
    onStatus(cStatus_200);
    mAccelY = 0.0f;
    mSpeed.y = 0.1f;
    mSpeedF = 0.0f;
    mSpeedFMax = 0.0f;
    mpModelBaseMgr->setAnm(PlayerAnmID::jumped);
}

void PlayerBase::executeState_Cloud()
{
}

void PlayerBase::cancelCloudOn()
{
    mRideActorID.invalidate();
}

void PlayerBase::finalizeState_Cloud()
{
    mAngle.x() = 0;
    cancelCloudOn();
    offStatus(cStatus_119);
    offStatus(cStatus_121);
    offStatus(cStatus_200);
}

void PlayerBase::initializeState_Cloud2()
{
    onStatus(cStatus_143);
    mAccelY = 0.0f;
    mSpeed.y = 0.0f;
    mSpeedF = 0.0f;
    mSpeedFMax = 0.0f;
    mpModelBaseMgr->setAnm(PlayerAnmID::jumped);
}

void PlayerBase::executeState_Cloud2()
{
}

void PlayerBase::finalizeState_Cloud2()
{
    mRideActorID.invalidate();
    offStatus(cStatus_143);
}

void PlayerBase::initializeState_Swim()
{
}

void PlayerBase::executeState_Swim()
{
}

void PlayerBase::finalizeState_Swim()
{
}

void PlayerBase::executeState()
{
    MathUtil::calcTimer(&mActionTimer);
    mStateMgr.executeState();
}

void PlayerBase::changeStateImpl(const StateID& state_id, s32 param, const JumpInf* p_jmp_inf)
{
    if (isStatus(cStatus_DemoScript))
        return;

    SubjectMgr::instance()->onPlChangeState();

    clearComboCount();
    mAction = 0;
    mActionTimer = 0;
    mStunMode = 0;
    _4e8 = false;
    offStatus(cStatus_196);
    offStatus(cStatus_197);
    offStatus(cStatus_199);
    offStatus(cStatus_35);
    offStatus(cStatus_10);
    mChangeStateParam = param;
    mpChangeStateJmpInf = p_jmp_inf;
    mStateMgr.changeState(state_id);
    throwCarryActor();
}

void PlayerBase::changeState(const StateID& state_id, s32 param)
{
    changeStateImpl(state_id, param, nullptr);
}

void PlayerBase::changeState(const StateID& state_id, const JumpInf& jmp_inf)
{
    changeStateImpl(state_id, 0, &jmp_inf);
}

void PlayerBase::walkAction_SetAnm(AnmBlend blend)
{
    setWalkActionAnm(blend);
}

void PlayerBase::walkAction_Move()
{
    AnmBlend blend = cAnmBlend_Enable;
    if (mSpeedF == 0.0f)
    {
        if (_21d8 != 0 || isNowBgCross(cBgCross_15))
        {
            if (mPlayerKey.buttonWalk())
                blend = cAnmBlend_Disable;
            else
            {
                walkActionInit_Wait(cAnmBlend_Enable);
                return;
            }
        }
        else
        {
            if (isNowBgCross(cBgCross_IsWall))
            {
                if (mMode == cPlayerMode_Mini && getSakaUpDown() == cSakaUpDown_Uphill) // Mini Mario wall climb
                    blend = cAnmBlend_Disable;
                else
                {
                    walkActionInit_Wait(cAnmBlend_Enable);
                    return;
                }
            }
            if (isNowBgCross(cBgCross_OnSakaUnderRoof) || !mPlayerKey.buttonWalk())
            {
                walkActionInit_Wait(cAnmBlend_Enable);
                return;
            }
        }
    }
    else
    {
        if (isNowBgCross(cBgCross_OnRide))
            _21d8 = 3;
    }
    setWalkActionAnm(blend);
    setRunFootEffect();
}

void PlayerBase::calcSpeedOnIceLift()
{
    if (mMode != cPlayerMode_Penguin &&
        isNowBgCross(cBgCross_OnRide) && isNowBgCross(cBgCross_IsIce) &&
        sead::Mathf::abs(mPosDelta.x) > 1.0f)
    {
        s32 drift_dir = cDirType_Right;
        if (mPosDelta.x < 0.0f)
            drift_dir = cDirType_Left;

        f32 speed;

        static const f32 c_ice_lift_speed_mult_move[] = { 0.5f, 0.8f };
        static const f32 c_ice_lift_speed_mult_no_move[] = { 0.3f, 1.0f };

        if (mPlayerKey.buttonWalk())
            speed = mSpeedF * c_ice_lift_speed_mult_move[drift_dir];
        else
            speed = mSpeedF * c_ice_lift_speed_mult_no_move[drift_dir];

        f32 new_speed = sead::Mathf::abs(speed);
        if (new_speed < 0.3f)
            new_speed = 0.3f;
        else if (new_speed > 1.5f)
            new_speed = 1.5f;

        if (speed < 0.0f)
            new_speed = -new_speed;

        mSpeedF = new_speed;
    }
}

void PlayerBase::calcAccOnIceLift()
{
    if (isNowBgCross(cBgCross_OnRide) && isNowBgCross(cBgCross_IsIce) &&
        !mPlayerKey.buttonWalk() &&
        sead::Mathf::abs(mPosDelta.x) > 1.0f)
    {
        mAccelF *= 3.0f;
    }
}

bool PlayerBase::checkTurn()
{
    if (!isCarry() && !isStatus(cStatus_239) && sead::Mathf::abs(mSpeedF) >= 2.5f)
    {
        bool turn = false;
        if (!isNowBgCross(cBgCross_IsIce))
            turn = true;
        else if (mSpeedF < 0.0f && mPlayerKey.buttonRight() && mDirection == cDirType_Right)
            turn = true;
        else if (mSpeedF > 0.0f && mPlayerKey.buttonLeft() && mDirection == cDirType_Left)
            turn = true;
        if (turn)
        {
            changeState(StateID_Turn, 0);
            return true;
        }
    }
    return false;
}

void PlayerBase::setTurnEnd()
{
    mAngle.y() = getMukiAngle();
    changeState(StateID_Walk, 0);
}

void PlayerBase::setCrouchActionAnm()
{
    switch (mChangeStateParam)
    {
    default:
        break;
    case 0:
        if (!isNowBgCross(cBgCross_IsUnderwater))
            mpModelBaseMgr->setAnm(PlayerAnmID::stoop_start);
        else
            mpModelBaseMgr->setAnm(PlayerAnmID::stoop_start, 0.1f, 3.0f, 0.0f);
        startSound("SE_PLY_QUAT", 1);
        break;
    case 1:
        mpModelBaseMgr->setAnm(PlayerAnmID::stoop);
        break;
    case 2:
        mpModelBaseMgr->setAnm(PlayerAnmID::Sjumped);
        break;
    }
}

void PlayerBase::setCrouchWallSpeed()
{
    s32 walk_dir;
    if (mPlayerKey.buttonWalk(&walk_dir))
    {
        if (walk_dir == cDirType_Left)
        {
            if (isOldBgCross(cBgCross_IsWallTouchL))
                mSpeedF = -0.7f;
        }
        else if (walk_dir == cDirType_Right)
        {
            if (isOldBgCross(cBgCross_IsWallTouchR))
                mSpeedF = 0.7f;
        }
    }
}

void PlayerBase::setCrouchSmokeEffect()
{
    if (sead::Mathf::abs(mSpeedF) > 0.1f)
    {
        if (!isNowBgCross(cBgCross_IsUnderwater))
            setSlipSmokeEffect();

        setSlipSE();
    }
}

bool PlayerBase::setCancelCrouch()
{
    if (checkStandUpRoof())
        return false;

    if (mpModelBaseMgr->getAnmID() != PlayerAnmID::stoop_start)
    {
        mpModelBaseMgr->setAnm(PlayerAnmID::stoop_start);
        mpModelBaseMgr->setFrame(mpModelBaseMgr->getFrameEnd() - 1.0f);
    }

    if (!isNowBgCross(cBgCross_IsUnderwater))
        mpModelBaseMgr->setRate(-1.0f);
    else
        mpModelBaseMgr->setRate(-0.1f);

    changeState(StateID_Walk, 1);
    return true;
}

bool PlayerBase::setCrouchJump()
{
    if (mPlayerKey.triggerJump())
    {
        changeState(StateID_SitJump, 0);
        return true;
    }
    return false;
}

bool PlayerBase::checkSitJumpRoof()
{
    if (isNowBgCross(cBgCross_IsHead) && (isNowBgCross(cBgCross_IsWallTouchL) || isNowBgCross(cBgCross_IsWallTouchR)))
    {
        mSpeed.y = 0.0f;

        s32 walk_dir;
        if (mPlayerKey.buttonWalk(&walk_dir))
        {
            mPos.x += cDirSpeed[walk_dir];
            mPosPrev = mPos;
            mPosPrev2 = mPos;
            mSpeedF = 0.7f * cDirSpeed[walk_dir];
        }

        return true;
    }
    return false;
}

bool PlayerBase::setFunsui(FunsuiType type)
{
    if (isStatus(cStatus_107))
        return false;

    if (isStatus(cStatus_207))
        return false;

    if (*mStateMgr.getStateID() == StateID_Funsui)
        return false;

    if (isDemoAll())
        return false;

    mFunsuiType = type;
    changeState(StateID_Funsui, 0);
    return true;
}

bool PlayerBase::updateFunsuiPos(f32 x, f32 y)
{
    if (*mStateMgr.getStateID() == StateID_Funsui)
    {
        mFunsuiPos.x = x;
        mFunsuiPos.y = y;
        return true;
    }
    return false;
}

bool PlayerBase::releaseFunsui(f32 speed_y)
{
    if (*mStateMgr.getStateID() == StateID_Funsui)
    {
        if (mFunsuiType == cFunsuiType_Water)
            mpModelBaseMgr->setAnm(PlayerAnmID::jump);
        mSpeed.y = speed_y;
        mAction = cFunsuiAction_Release;
        mPlayerKey.onStatus(PlayerKey::cStatus_NoJump);
        offStatus(cStatus_248);
    }
    return true;
}

bool PlayerBase::setCloudOn(Actor* p_cloud_actor)
{
    if (!isNowBgCross(cBgCross_IsFoot) &&
        !isStatus(cStatus_247) &&
        !isStatus(cStatus_76) &&
        p_cloud_actor->getPos().y + getCloudOffsetY() + 6.0f >= mPos.y &&
        mSpeed.y < 0.0f &&
        !mRideActorID.isValid())
    {
        mRideActorID = p_cloud_actor->getActorUniqueID();
        changeState(StateID_Cloud, 0);
        return true;
    }
    return false;
}

void PlayerBase::getCloudPos(sead::Vector3f& pos)
{
    pos.set(mPos.x, mPos.y - getCloudOffsetY(), mPos.z);
}

Actor* PlayerBase::getCloud()
{
    if (isStatus(cStatus_119))
        return sead::DynamicCast<Actor>(ActorMgr::instance()->getActorPtr(mRideActorID));

    return nullptr;
}

bool PlayerBase::updateCloudMove()
{
    Actor* p_cloud_actor = getCloud();
    if (p_cloud_actor == nullptr)
    {
        setFallAction();
        return true;
    }

    if (mPlayerKey.triggerJump())
    {
        changeState(StateID_Jump, 0);
        return true;
    }

    onStatus(cStatus_255);

    mPos = p_cloud_actor->getPos();
    mPos.y += getCloudOffsetY();

    mSpeed.y = 0.0f;

    if (!isStatus(cStatus_69))
    {
        mAngle = p_cloud_actor->getAngle();
        mDirection = p_cloud_actor->getDirection();
    }

    return false;
}

Angle PlayerBase::addCalcAngleY(const Angle& target, f32 rate)
{
    mAngle.y().addCalcAngle(target, rate, 0x20000000, 0x4000000);
    return mAngle.y() - target;
}

Angle PlayerBase::getBesideMukiAngle(s32 dir)
{
    static const Angle c_beside_muki_angle[] = {
         0x40b60b60, //  91 degrees
        -0x40b60b60, // -91 degrees
    };
    return c_beside_muki_angle[dir];
}

bool PlayerBase::turnBesideAngle(s32 dir)
{
    Angle target = getBesideMukiAngle(dir);
    Angle step = 0x20000000; // 45 degrees

    return mAngle.y().chaseRest(target, step);
}
