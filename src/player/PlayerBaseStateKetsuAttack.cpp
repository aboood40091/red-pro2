#include <game_info/CourseInfo.h>
#include <player/PlayerBase.h>
#include <player/PlayerMgr.h>
#include <player/PlayerModelBaseMgr.h>

void PlayerBase::setHipAttack_Ready_()
{
    mAction = cHipAction_Ready;
    mpModelBaseMgr->setAnm(PlayerAnmID::hipsr, 0.0f);
    mSpeed.y = 1.0f;
}

void PlayerBase::initializeState_HipAttack()
{
    mAngle.y() = getMukiAngle();
    mSpeedF = 0.0f;
    mMaxSpeedF = 0.0f;
    mAccelY = 0.0f;
    setHipAttack_Ready_();
    onStatus(cStatus_196);
    onStatus(cStatus_200);
    onStatus(cStatus_NoSwimAction);
    onStatus(cStatus_206);
}

void PlayerBase::updateHipAttackOnEnemy()
{
    if (isStatus(cStatus_HipAttackOnEnemy))
    {
        offStatus(cStatus_HipAttackOnEnemy);
        mPos.x = mHipAttackOnEnemyPos.x;
        mPos.y = mHipAttackOnEnemyPos.y;
    }
}

void PlayerBase::executeState_HipAttack()
{
    static void (PlayerBase::*s_hip_action_proc[])() = {
        &PlayerBase::HipAction_Ready,
        &PlayerBase::HipAction_AttackStart,
        &PlayerBase::HipAction_AttackFall,
        &PlayerBase::HipAction_Ground,
        &PlayerBase::HipAction_StandNormal,
        &PlayerBase::HipAction_StandNormalEnd,
        &PlayerBase::HipAction_ToStoop
    };
    static_assert(sizeof(s_hip_action_proc) / sizeof(s_hip_action_proc[0]) == cHipAction_Num);

    offStatus(cStatus_49);
    if (isStatus(cStatus_48))
        setCcAtHipAttack();

    if (isNowBgCross(cBgCross_IsCompletelyUnderwater))
        offStatus(cStatus_NoSwimAction);

    if (mAction >= cHipAction_StandNormal)
        if (checkJumpTrigger())
            return;

    (this->*s_hip_action_proc[mAction])();
    updateHipAttackOnEnemy();
}

void PlayerBase::finalizeState_HipAttack()
{
    mMaxFallSpeed = cMaxFallSpeed;
    offStatus(cStatus_48);
    offStatus(cStatus_49);
    offStatus(cStatus_50);
    offStatus(cStatus_51);
    offStatus(cStatus_HipAttackOnEnemy);
    offStatus(cStatus_56);
    offStatus(cStatus_160);
    offStatus(cStatus_165);
    offStatus(cStatus_196);
    offStatus(cStatus_200);
    offStatus(cStatus_NoSwimAction);
    offStatus(cStatus_206);
    offStatus(cStatus_NoBgCrossUpdate);
    offStatus(cStatus_NoEntryReactCc);
}

void PlayerBase::setHipAttack_AttackStartBase()
{
    mAction = cHipAction_AttackStart;
    mpModelBaseMgr->setAnm(PlayerAnmID::hipat, 0.0f);
    if (isTotten())
        mpModelBaseMgr->setFrame(mpModelBaseMgr->getFrameEnd() - 1.0f);
    mActionTimer = 5;
    mSpeed.y = 0.0f;
}

void PlayerBase::setHipAttack_AttackFall()
{
    mAction = cHipAction_AttackFall;
    mAccelF = 0.1f;
    mMaxSpeedF = 0.0f;
    mAccelY = getGravityData()->gravity;
    mMaxFallSpeed = -6.0f;
    mSpeed.y = -6.0f;
    onStatus(cStatus_48);
    mActionTimer = 5;
}

void PlayerBase::setHipAttack_StandNormal()
{
    mActionTimer = 20;
    mAction = cHipAction_StandNormal;
    mpModelBaseMgr->setAnm(PlayerAnmID::hiped, 0.0f);
    onStatus(cStatus_50);
    offStatus(cStatus_48);
    onStatus(cStatus_160);
    onStatus(cStatus_165);
    mAccelY = getGravityData()->gravity;
    mMaxFallSpeed = -6.0f;
    mSpeed.y = 0.0f;
}

void PlayerBase::setHipAttack_StandNormalEndBase()
{
    mAction = cHipAction_StandNormalEnd;
    mpModelBaseMgr->setAnm(PlayerAnmID::sliped, 0.0f);
    offStatus(cStatus_50);
    offStatus(cStatus_56);
}

void PlayerBase::setHipAttack_ToStoop()
{
    mAction = cHipAction_ToStoop;
    mpModelBaseMgr->setAnm(PlayerAnmID::hip_to_stoop, 0.0f);
    offStatus(cStatus_50);
    offStatus(cStatus_56);
}

void PlayerBase::HipAction_Ready()
{
    if (mpModelBaseMgr->isAnmStop())
        setHipAttack_AttackStart();
}

void PlayerBase::HipAction_AttackStart()
{
    if (mActionTimer == 0)
        setHipAttack_AttackFall();
}

void PlayerBase::setHipAttackSE()
{
    if (mMode == cPlayerMode_Mini)
    {
        switch (mBgAttr)
        {
        case cBgAttr_Water1:
            startSound("SE_PLY_HPDP_SPLASH");
            break;
        case cBgAttr_Water2:
            startSound("SE_PLY_HIP_ATTACK_WATER");
            break;
        default:
            startSound("SE_PLY_HIP_ATTACK_M");
            break;
        }
    }
    else
    {
        switch (mBgAttr)
        {
        case cBgAttr_SandFunsui:
        case cBgAttr_Leaf:
            startSound("SE_PLY_HIP_ATTACK_SOFT");
            break;
        case cBgAttr_Water1:
            startSound("SE_PLY_HPDP_SPLASH");
            break;
        case cBgAttr_Water2:
            startSound("SE_PLY_HIP_ATTACK_WATER");
            break;
        default:
            startSound("SE_PLY_HIP_ATTACK");
            break;
        }
    }
}

void PlayerBase::HipAction_AttackFall()
{
    setHipBlockBreak();
    setHipAttackDropEffect();

    if (mActionTimer == 0 || isNowBgCross(cBgCross_IsFoot))
    {
        offStatus(cStatus_NoBgCrossUpdate);
        offStatus(cStatus_NoEntryReactCc);
    }

    if (!isNowBgCross(cBgCross_IsFoot))
    {
        if (isNowBgCross(cBgCross_IsUnderwater))
            mMaxFallSpeed = -3.0f;
        else
            mMaxFallSpeed = -6.0f;

        mAccelY = getGravityData()->gravity;

        s32 walk_dir;
        if (mPlayerKey.buttonWalk(&walk_dir))
            mMaxSpeedF = cDirSpeed[walk_dir] * 0.3f;

        if (mPlayerKey.buttonDown() && mSpeed.y < 0.0f)
            setHipBlockBreak();

        if (!isStatus(cStatus_HipAttackOnEnemy) && mPlayerKey.buttonUp())
            changeState(StateID_Fall, cAnmBlend_Enable);
    }
    else
    {
        if (!mPlayerKey.buttonDown())
            offStatus(cStatus_56);

        if (!mRideActorID.isValid())
        {
            setHipAttackEffect();
            mHipAttackEffectStep = 1;
            setHipAttackSE();
        }

        s32 quake_type = 0;
        if (mMode == cPlayerMode_Mini)
            quake_type = 2;
        bool quake_ext = true;
        if (isStatus(cStatus_51))
            quake_ext = false;
        PlayerMgr::instance()->setHipAttackQuake(quake_type, mPlayerNo, quake_ext);

        onStatus(cStatus_49);
        offStatus(cStatus_158);

        if (setHipAttackToKaniHangAction())
        {
        }
        else if (!isNowBgCross(cBgCross_75) && isSlipSaka())
        {
            if (!isNowBgCross(cBgCross_IsWater))
            {
                if (mSakaType >= ActorBgCollisionCheck::cSakaType_Moderate)
                    mSpeedF = getSlipMaxSpeedF();
                else
                    mSpeedF = getSlipMaxSpeedF() * 0.5f;
            }
            setSlipAction();
        }
        else
        {
            mMaxSpeedF = 0.0f;
            mSpeedF = 0.0f;
            mSpeed.y = 0.0f;
            mAccelY = 0.0f;
            mAction = cHipAction_Ground;
            mPos.y -= 0.1f;
            onStatus(cStatus_51);
        }
    }
}

void PlayerBase::HipAction_Ground()
{
    if (!mPlayerKey.buttonDown() && !isNowBgCross(cBgCross_IsFoot))
        changeState(StateID_Fall, cAnmBlend_Enable);
    else
        setHipAttack_StandNormal();
}

void PlayerBase::HipAction_StandNormal()
{
    if (mpModelBaseMgr->getAnmID() != PlayerAnmID::hiped)
        mpModelBaseMgr->setAnm(PlayerAnmID::hiped, 0.0f);

    if (isNowBgCross(cBgCross_IsFoot))
    {
        if (mpModelBaseMgr->isAnmStop())
        {
            if (!mPlayerKey.buttonDown())
            {
                offStatus(cStatus_206);
                setHipAttack_StandNormalEnd();
            }
            else
            {
                setHipBlockBreak();
                if (!CourseInfo::instance()->isTitle())
                {
                    if (isNowBgCross(cBgCross_67))
                        mActionTimer = 15;
                    else if (mActionTimer == 0)
                    {
                        offStatus(cStatus_206);
                        setHipAttack_ToStoop();
                    }
                }
            }
        }
        else
        {
            if (isSlipSaka())
            {
                mSpeedF = getSlipMaxSpeedF();
                setSlipAction();
            }
            else
            {
                turnAngle();
            }
        }
    }
    else
    {
        if (mPlayerKey.buttonCrouch())
            setHipAttack_AttackFall();
    }
}

void PlayerBase::HipAction_StandNormalEnd()
{
    if (!checkCrouch())
    {
        if (checkStandUpRoof())
            changeState(StateID_Crouch, 1);
        else
        {
            if (mpModelBaseMgr->isAnmStop())
                changeState(StateID_Walk, cAnmBlend_Enable);
            else
                turnAngle();
        }
    }
}

void PlayerBase::HipAction_ToStoop()
{
    if (mpModelBaseMgr->isAnmStop())
        changeState(StateID_Crouch, 1);
    else
        turnAngle();
}

void PlayerBase::setHipAttackOnEnemyBase(const sead::Vector3f& target_pos)
{
    onStatus(cStatus_HipAttackOnEnemy);
    mHipAttackOnEnemyPos = target_pos;
}

void PlayerBase::updateHipDropExEffect()
{
    if (mHipAttackEffectStep == 1)
    {
        if (!updateHipAttackEffect())
            mHipAttackEffectStep = 0;
    }
    mHipdropExEffect.calcModel();
}
