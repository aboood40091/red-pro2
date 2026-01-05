#include <collision/BgCollisionCheckResult.h>
#include <game/CourseTask.h>
#include <input/InputMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerDemoMgr.h>
#include <scene/Scene.h>
#include <utility/MathUtil.h>

void PlayerBase::setCreate(const sead::Vector3f& pos, NextGotoType next_goto_type, s32 dir)
{
    if (CourseTask::instance() && CourseTask::instance()->getGameMode() == FieldGameMode::cCoinEdit)
        return;

    mAngle.y() = getMukiAngle();
    mNextGotoType = next_goto_type;
    changeDemoState(StateID_DemoCreate, 0);
}

void PlayerBase::reset()
{
    mSpeedF = 0.0f;
    mSpeed.set(0.0f, 0.0f, 0.0f);
    mAccelY = 0.0f;

    onStatus(cStatus_6);
    {
        changeState(StateID_None, 0);
        changeDemoState(StateID_DemoReset, 0);
    }
    offStatus(cStatus_6);

    resetDrawType();
    mExecuteFreezeTimer = 0;
}

void PlayerBase::resetBg()
{
    mStatus.reset();
    mNowBgCross.reset();
    mOldBgCross.reset();
    _205c = 0;
    _2060 = 0;
    _2064 = 0;
    _2068 = 0;
    _206c = 0;
    _2070 = 0;
    mIsBgDamageEnable = false;
    mDamageBgTypeInfo = BgUnitCode::TypeInfo_Damage();
    _2190 = 0.0f;
    offStatus(cStatus_FaderPosSet); // But... mStatus is reset just above?
    clearBgAndSakaAngle();
}

void PlayerBase::setPosAndDir(const sead::Vector3f& pos, s32 dir)
{
    mPos = pos;
    mPosPrev = pos;
    mPosPrev2 = pos;
    mMaskPos = pos;
    mFaderPos = pos;
    setZPosition();
    setAreaNo_();

    mDirection = dir;
}

void PlayerBase::stopCreateOther()
{
    if (mNextGotoType == cNextGotoType_Vine ||
        mNextGotoType == cNextGotoType_ShiroBoss ||
        mNextGotoType == cNextGotoType_FinalBoss)
    {
        return;
    }
    PlayerDemoMgr::instance()->stopOther();
}

typedef void (PlayerBase::*CreateActionProc)(NextGotoType);
static CreateActionProc sCreateActionProc[] = {
    &PlayerBase::initialNormal,         // cNextGotoType_Normal
    &PlayerBase::initialNormal,         // cNextGotoType_CheckPoint
    &PlayerBase::initialDoor,           // cNextGotoType_Door
    &PlayerBase::initialDokan,          // cNextGotoType_DokanD
    &PlayerBase::initialDokan,          // cNextGotoType_DokanU
    &PlayerBase::initialDokan,          // cNextGotoType_DokanR
    &PlayerBase::initialDokan,          // cNextGotoType_DokanL
    &PlayerBase::initialFall,           // cNextGotoType_Fall
    &PlayerBase::initialHipAttack,      // cNextGotoType_HipAttack
    &PlayerBase::initialSlip,           // cNextGotoType_Slip
    &PlayerBase::initialUnk10,          // cNextGotoType_10
    &PlayerBase::initialNormal,         // cNextGotoType_Normal_11
    &PlayerBase::initialNormal,         // cNextGotoType_Normal_12
    &PlayerBase::initialNormal,         // cNextGotoType_Normal_13
    &PlayerBase::initialDoor,           // cNextGotoType_Door_14
    &PlayerBase::initialDoor,           // cNextGotoType_DoorBoss
    &PlayerBase::initialDokan,          // cNextGotoType_DokanD_Mame
    &PlayerBase::initialDokan,          // cNextGotoType_DokanU_Mame
    &PlayerBase::initialDokan,          // cNextGotoType_DokanR_Mame
    &PlayerBase::initialDokan,          // cNextGotoType_DokanL_Mame
    &PlayerBase::initialJump,           // cNextGotoType_JumpL
    &PlayerBase::initialVine,           // cNextGotoType_Vine
    &PlayerBase::initialJump,           // cNextGotoType_JumpR
    &PlayerBase::initialShiroBoss,      // cNextGotoType_ShiroBoss
    &PlayerBase::initialFinalBoss,      // cNextGotoType_FinalBoss
    &PlayerBase::initialNormal,         // cNextGotoType_Ambush
    &PlayerBase::initialNormal,         // cNextGotoType_Normal_26
    &PlayerBase::initialUnk27,          // cNextGotoType_27
    &PlayerBase::initialBoxingKoopaJr,  // cNextGotoType_BoxingKoopaJr
    &PlayerBase::initialNormal,         // cNextGotoType_Credits_P1
    &PlayerBase::initialNormal,         // cNextGotoType_Credits_P2
    &PlayerBase::initialNormal,         // cNextGotoType_Credits_P3
    &PlayerBase::initialNormal,         // cNextGotoType_Credits_P4
    &PlayerBase::initialTitle,          // cNextGotoType_Title
    &PlayerBase::initialNormal          // cNextGotoType_Ambush_ChibiYoshi
};
static_assert((sizeof(sCreateActionProc) / sizeof(CreateActionProc)) == cNextGotoType_Num);

void PlayerBase::setCreateAction_(NextGotoType next_goto_type)
{
    (this->*sCreateActionProc[next_goto_type])(next_goto_type);
}

void PlayerBase::executeDemoCreate()
{
    changeState(StateID_Walk, 0);
    mIsLastPlayer = false;
    s32 demo_index = PlayerDemoMgr::instance()->searchDemoNo(mPlayerNo);
    s32 demo_num = PlayerDemoMgr::instance()->getNumDemoNo();
    if (demo_index == demo_num - 1)
        mIsLastPlayer = true;
    setCreateAction_(mNextGotoType);
}

void PlayerBase::initialNormal(NextGotoType)
{
    changeState(StateID_Walk, 0);
    changeDemoState(StateID_DemoStartWait, 0);
}

void PlayerBase::initialDoor(NextGotoType)
{
}

void PlayerBase::initialDokan(NextGotoType next_goto_type)
{
    switch (next_goto_type)
    {
    default:
        break;
    case cNextGotoType_DokanD:
        changeDemoState(StateID_DemoInDokanD, 0);
        break;
    case cNextGotoType_DokanU:
        changeDemoState(StateID_DemoInDokanU, 0);
        break;
    case cNextGotoType_DokanR:
        changeDemoState(StateID_DemoInDokanR, 0);
        break;
    case cNextGotoType_DokanL:
        changeDemoState(StateID_DemoInDokanL, 0);
        break;
    case cNextGotoType_DokanD_Mame:
        changeDemoState(StateID_DemoInDokanD, 2);
        break;
    case cNextGotoType_DokanU_Mame:
        changeDemoState(StateID_DemoInDokanU, 2);
        break;
    case cNextGotoType_DokanR_Mame:
        changeDemoState(StateID_DemoInDokanR, 2);
        break;
    case cNextGotoType_DokanL_Mame:
        changeDemoState(StateID_DemoInDokanL, 2);
        break;
    }
}

void PlayerBase::initialFall(NextGotoType)
{
    changeState(StateID_Fall, 1);
    changeDemoState(StateID_DemoWait, 2);
}

void PlayerBase::initialHipAttack(NextGotoType)
{
    changeState(StateID_HipAttack, 0);
    changeDemoState(StateID_DemoWait, 0);
}

void PlayerBase::initialSlip(NextGotoType)
{
    onStatus(cStatus_102);
    setSlipAction();
    changeDemoState(StateID_DemoWait, 1);
}

void PlayerBase::initialJump(NextGotoType)
{
}

void PlayerBase::initialVine(NextGotoType)
{
}

void PlayerBase::initialShiroBoss(NextGotoType)
{
}

void PlayerBase::initialFinalBoss(NextGotoType)
{
}

void PlayerBase::initialUnk10(NextGotoType)
{
}

void PlayerBase::initialUnk27(NextGotoType next_goto_type)
{
    initialNormal(next_goto_type);
}

void PlayerBase::initialBoxingKoopaJr(NextGotoType)
{
}

void PlayerBase::initialTitle(NextGotoType)
{
}

void PlayerBase::initializeState_DemoCreate()
{
    stopCreateOther();
}

void PlayerBase::executeState_DemoCreate()
{
    sead::Vector3f fader_pos(mPos.x, mPos.y + 16.0f, mPos.z);
    MathUtil::getGlbPosToLyt(fader_pos);
    Scene::instance()->getFadeCenter().set(
        fader_pos.x,
        fader_pos.y,
        0.0f
    );
    executeDemoCreate();
}

void PlayerBase::finalizeState_DemoCreate()
{
}

void PlayerBase::initializeState_DemoStartWait()
{
    if (isNowBgCross(cBgCross_IsUnderwater))
        return;

    BgCollisionCheckResultArea res;
    if (mBgCheckPlayer.checkGround(mPos, 8.0f, &res))
    {
        mPos.y = res.hit_pos.y;
        mPosPrev = mPos;
        mPosPrev2 = mPos;
        if (checkOnHDokan(res.bg_check_data))
            onNowBgCross(cBgCross_IsOnHDokan);
    }
}

void PlayerBase::executeState_DemoStartWait()
{
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoStartWaitAction_Wait:
        if (InputMgr::instance()->isInputEnabled())
        {
            PlayerDemoMgr::instance()->playOther();
            mDemoAction = cDemoStartWaitAction_Move;
        }
        break;
    case cDemoStartWaitAction_Move:
        mSpeed.y = cMaxFallSpeed_Foot;
        mPos.y += mSpeed.y;
        bgCheck(false);
        changeDemoState(StateID_DemoNone, 0);
        break;
    }
}

void PlayerBase::finalizeState_DemoStartWait()
{
}

void PlayerBase::initializeState_DemoWait()
{
    mPlayerKey.onStatus(PlayerKey::cStatus_NoInput);
    mDemoActionTimer = 0;
    switch (mChangeDemoStateParam)
    {
    default:
        break;
    case 0:
    case 1:
        PlayerDemoMgr::instance()->setDemoMode(PlayerDemoMgr::cMode_Wait);
        mDemoAction = cDemoWaitAction_WaitTurn;
        break;
    case 2:
        mDemoAction = cDemoWaitAction_WaitSingle;
        break;
    }
}

void PlayerBase::executeState_DemoWait()
{
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoWaitAction_WaitTurn:
        {
            PlayerDemoMgr& demo_mgr = *PlayerDemoMgr::instance();
            if (demo_mgr.isEnableCheckDemoNo() && demo_mgr.getNextDemoNo() == mPlayerNo)
            {
                mDemoAction = cDemoWaitAction_Move;
                if (demo_mgr.getCourseOutPlayerNo() != mPlayerNo)
                    mDemoActionTimer = 10;
            }
        }
        break;
    case cDemoWaitAction_Move:
        if (mDemoActionTimer == 0)
        {
            PlayerDemoMgr::instance()->turnNextDemoNo();
            switch (mChangeDemoStateParam)
            {
            default:
                break;
            case 0:
                changeDemoState(StateID_DemoNone, 0);
                onDemo();
                bgCheck(false);
                break;
            case 1:
                changeDemoState(StateID_DemoControl, 4);
                break;
            case 2:
                changeDemoState(StateID_DemoNone, 0);
                mSpeed.y = cMaxFallSpeed_Foot;
                bgCheck(false);
                break;
            }
        }
        break;
    case cDemoWaitAction_WaitSingle:
        if (InputMgr::instance()->isInputEnabled())
            changeDemoState(StateID_DemoNone, 0);
        break;
    }
}

void PlayerBase::finalizeState_DemoWait()
{
    mPlayerKey.offStatus(PlayerKey::cStatus_NoInput);
}
