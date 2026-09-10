#include <actor/ActorMgr.h>
#include <map_obj/BalloonChibiYoshi.h>
#include <map_obj/BubbleChibiYoshi.h>
#include <map_obj/PropBlock.h>
#include <player/PlayerObject.h>

bool PlayerObject::isCarry()
{
    return mCarryActorID.isValid();
}

bool PlayerObject::checkCarryActor(PlayerObject* p_player)
{
    if (mCarryActorID == p_player->mActorUniqueID &&
        p_player->mRideActorID == mActorUniqueID)
    {
        return true;
    }
    return false;
}

void PlayerObject::calcLiftUpOffsetScale()
{
    f32 target = 0.0f;
    if (isCarry() && mModelMgr.isLiftUp() && !isStatus(cStatus_58))
        target = 1.0f;
    sead::Mathf::chase(&mLiftUpOffsetScale, target, 0.1f);
}

void PlayerObject::calcCarryStep()
{
    if (mCarryStepTimer)
        mCarryStepTimer--;

    mCarryStepPrev = mCarryStep;

    f32 carry_step_length = 0.0f;
    CarryStep carry_step = cCarryStep_None;
    if (isCarry())
    {
        if (mModelMgr.isLiftUp())
        {
            carry_step_length = 10.0f;
            carry_step = cCarryStep_LiftUp;
        }
        else if (mModelMgr.isCarryLongAnm())
        {
            carry_step_length = 5.0f;
            carry_step = cCarryStep_CarryLong;
        }
        else
        {
            carry_step = cCarryStep_Carry;
        }
    }
    if (mCarryStep != carry_step)
    {
        mCarryStep = carry_step;
        mCarryStepTimer = carry_step_length;
        mCarryStepLength = carry_step_length;
    }
}

f32 PlayerObject::getCarryStepRatio()
{
    if (mCarryStepLength == 0.0f)
        return 0.0f;

    return sead::Mathf::clamp2(0.0f, mCarryStepTimer / mCarryStepLength, 1.0f);
}

void PlayerObject::getCarryPos(sead::Vector3f* p_pos)
{
    sead::Vector3f wrist_l;
    mpModelBaseMgr->getJointPos(&wrist_l, "wrist_l1");
    sead::Vector3f wrist_r;
    mpModelBaseMgr->getJointPos(&wrist_r, "wrist_r1");

    sead::Vector3f pos = (wrist_l + wrist_r) * 0.5f;
    if (mLiftUpOffsetScale)
        pos.y += ((mPos.y + getLiftUpOffset()) - pos.y) * mLiftUpOffsetScale;
    *p_pos = pos;
}

bool PlayerObject::getCarryMtx(sead::Matrixf* p_mtx)
{
    sead::Vector3f pos;
    getCarryPos(&pos);
    p_mtx->makeT(pos);
    p_mtx->setMul(*p_mtx, getModel()->getMtxSr());
    return isCarry();
}

bool PlayerObject::isLiftUp()
{
    if (isCarry() &&
        (mCarryType == cCarryType_LiftUp || mCarryType == cCarryType_LiftUp_2))
    {
        return true;
    }
    return false;
}

bool PlayerObject::isCarryMamePlayer()
{
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr && p_carry_player->mMode == cPlayerMode_Mini)
        return true;
    return false;
}

PlayerObject* PlayerObject::getCarryPlayer() const
{
    return sead::DynamicCast<PlayerObject>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

bool PlayerObject::isLiftUpExceptMame()
{
    if (isLiftUp() && !isCarryMamePlayer())
        return true;
    return false;
}

Actor* PlayerObject::getCarryPropelActor()
{
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr && p_carry_player->mMode == cPlayerMode_Propeller)
        return p_carry_player;
    return getCarryPropelBlock();
}

const Actor* PlayerObject::getCarryPropelActor() const
{
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr && p_carry_player->mMode == cPlayerMode_Propeller)
        return p_carry_player;
    return getCarryPropelBlock();
}

PropBlock* PlayerObject::getCarryPropelBlock()
{
    return sead::DynamicCast<PropBlock>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

const PropBlock* PlayerObject::getCarryPropelBlock() const
{
    return sead::DynamicCast<PropBlock>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

const BalloonChibiYoshi* PlayerObject::getCarryBalloonChibiYoshi() const
{
    return sead::DynamicCast<BalloonChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

const BubbleChibiYoshi* PlayerObject::getCarryBubbleChibiYoshi() const
{
    return sead::DynamicCast<BubbleChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

const ChibiYoshiBase* PlayerObject::getCarryChibiYoshi() const
{
    return sead::DynamicCast<ChibiYoshiBase>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

ChibiYoshiBase* PlayerObject::getCarryChibiYoshi()
{
    return sead::DynamicCast<ChibiYoshiBase>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

CarryObjBase* PlayerObject::getCarryHardBlock()
{
    return sead::DynamicCast<CarryObjBase>(ActorMgr::instance()->getActorPtr(mCarryActorID));
}

void PlayerObject::setCarryBase(ActorUniqueID actor_id, CarryType type)
{
    mCarryActorID = actor_id;
    mCarryType = type;
    mModelMgr.onCarry();
    mModelMgr.setCarryBodyAnm(3.0f, false);
}

void PlayerObject::setLiftUpBase(ActorUniqueID actor_id, CarryType type)
{
    mCarryActorID = actor_id;
    mCarryType = type;
    changeState(StateID_LiftUp, 0);
    Actor* p_carry_actor = sead::DynamicCast<Actor>(ActorMgr::instance()->getActorPtr(mCarryActorID));
    if (p_carry_actor != nullptr)
        p_carry_actor->setSpinLiftUpActor(this);
}

void PlayerObject::clearSpinLiftUpReserve()
{
    mLiftUpActorID.invalidate();
    mLiftUpReserveSpeed = -256.0f;
}

void PlayerObject::checkSpinLiftUpReserve(ActorCollisionCheck* p_cc)
{
    Actor* p_carry_actor = p_cc->getOwner();
    if (p_carry_actor != nullptr && p_carry_actor->isSpinLiftUpEnable())
    {
        if (setCarry(p_carry_actor, cCarryType_LiftUp))
        {
            f32 speed = (p_cc->getCenterPosX() - mPos.x) * cDirSpeed[mDirection];
            if ((mLiftUpReserveSpeed < 0.0f && speed >= mLiftUpReserveSpeed) ||
                (mLiftUpReserveSpeed >= 0.0f && speed >= 0.0f && mLiftUpReserveSpeed > speed))
            {
                mLiftUpActorID = p_carry_actor->getActorUniqueID();
                mLiftUpReserveSpeed = speed;
            }
        }
    }
}
