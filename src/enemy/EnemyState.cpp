#include <actor/ActorMgr.h>
#include <actor/ChibiYoshiEatData.h>
#include <actor/EatData.h>
#include <enemy/Enemy.h>

void Enemy::changeState(const StateID& state_id)
{
    if (mStateMgr.isSubState())
    {
        mStateMgr.returnState();
        mStateMgr.replaceState(state_id);
    }
    else
    {
        ActorMultiState::changeState(state_id);
    }
}

bool Enemy::createIceActor()
{
    IceInfo info = { 0, mPos, sead::Vector3f(1.0f, 1.0f, 1.0f), nullptr };
    return mIceMgr.createIce(info);
}

void Enemy::setIceAnm()
{
}

void Enemy::returnAnm_Ice()
{
}

void Enemy::returnState_Ice()
{
    mStateMgr.returnState();
}

void Enemy::initializeState_Ice()
{
    mIceMgr.initialize();
    createIceActor();
    mBgCheckObj.clearBg();
    setIceAnm();
    removeCollisionCheck();
    mIceMgr.setIce(true);
    mNoWaterCalc = true;
}

void Enemy::finalizeState_Ice()
{
    mIceMgr.setIce(false);
    mNoWaterCalc = false;
}

void Enemy::executeState_Ice()
{
    IceMgr::DestroyMode destroy_mode = mIceMgr.getDestroyMode();
    if (destroy_mode != IceMgr::cDestroyMode_None)
    {
        mIceMgr.breakEffect();
        if (mIceMgr.isDrcBreakSound())
            GameAudio::getAudioObjMap()->startSound("SE_OBJ_PNGN_ICE_BREAK", mPos, nw::snd::OUTPUT_LINE_MAIN | nw::snd::OUTPUT_LINE_DRC);
        else
            GameAudio::getAudioObjMap()->startSound("SE_OBJ_PNGN_ICE_BREAK", mPos);
        if (destroy_mode == IceMgr::cDestroyMode_Break)
            setDeathInfo_IceBreak();
        else if (destroy_mode == IceMgr::cDestroyMode_Vanish)
            setDeathInfo_IceVanish();
    }
    else
    {
        if (mIceMgr.manageProc() == IceMgr::cProc_Return)
        {
            if (mIceMgr.isYoganDive())
                mNoLavaSplashTimer = 4;
            returnAnm_Ice();
            returnState_Ice();
            reviveCollisionCheck();
        }
    }
}

void Enemy::initializeState_EatIn()
{
    mBgCheckObj.clearBg();
}

void Enemy::finalizeState_EatIn()
{
}

void Enemy::executeState_EatIn()
{
    EatData* p_eat_data = mpEatData;
    if (p_eat_data == nullptr)
        return;

    if (p_eat_data->getState() == EatData::cState_EatMouth)
        changeState(StateID_EatNow);
    else
    {
        ActorBase* p_eat_actor = ActorMgr::instance()->getActorPtr(p_eat_data->getYoshiID());
        if (p_eat_actor != nullptr)
            p_eat_data->calcEatInScale(sead::DynamicCast<Actor>(p_eat_actor));
    }
}

void Enemy::initializeState_EatNow()
{
}

void Enemy::finalizeState_EatNow()
{
}

void Enemy::executeState_EatNow()
{
}

void Enemy::initializeState_EatOut()
{
}

void Enemy::finalizeState_EatOut()
{
}

void Enemy::executeState_EatOut()
{
}

void Enemy::initializeState_ChibiEatIn()
{
    mBgCheckObj.clearBg();
}

void Enemy::finalizeState_ChibiEatIn()
{
}

void Enemy::executeState_ChibiEatIn()
{
    ChibiYoshiEatData* p_eat_data = mpChibiYoshiEatData;
    if (p_eat_data == nullptr)
        return;

    if (p_eat_data->getState() == ChibiYoshiEatData::cState_EatMouth)
        changeState(StateID_ChibiEatNow);
}

void Enemy::initializeState_ChibiEatNow()
{
}

void Enemy::finalizeState_ChibiEatNow()
{
}

void Enemy::executeState_ChibiEatNow()
{
}

void Enemy::initializeState_ChibiEatOut()
{
}

void Enemy::finalizeState_ChibiEatOut()
{
}

void Enemy::executeState_ChibiEatOut()
{
}

void Enemy::initializeState_EnemyUnk1()
{
}

void Enemy::finalizeState_EnemyUnk1()
{
}

void Enemy::executeState_EnemyUnk1()
{
}

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

CREATE_STATE_VIRTUAL_ID_BASE(Enemy, Ice)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, EatIn)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, EatNow)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, EatOut)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, ChibiEatIn)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, ChibiEatNow)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, ChibiEatOut)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, EnemyUnk1)
