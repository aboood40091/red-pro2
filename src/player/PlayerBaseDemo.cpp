#include <event/EventMgr.h>
#include <event/EventStartCoinBattle.h>
#include <game/CourseTimer.h>
#include <game_info/CourseInfo.h>
#include <input/InputMgr.h>
#include <map/Next.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scene/Scene.h>
#include <scroll/BgScrollMgr.h>
#include <system/RDashMgr.h>
#include <utility/MathUtil.h>

CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoCreate)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoNone)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoReset)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoStartCoinBattle)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoGoal)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoStartWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanU)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanD)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanR)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanL)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanRollUD)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDokanRollLR)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoInDokanU)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoInDokanD)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoInDokanR)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoInDokanL)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoOutDoor)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoInDoor)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoNextGotoBlock)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoDown)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoControl)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoSubjectClearLand)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoSubjectClearAir)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, DemoShadowFail)

void PlayerBase::offDemo()
{
    if (mPlayerNo >= 0 && isStatus(cStatus_208))
    {
        PlayerMgr::instance()->setPauseEnable(mPlayerNo);
        CourseTimer::instance()->offStopTimer(mPlayerNo);
        offStatus(cStatus_DemoMode);
        offStatus(cStatus_208);
    }
}

void PlayerBase::initializeState_DemoNone()
{
    mDemoActionTimer = 15;
    PlayerDemoMgr::instance()->clearDemoNo(mPlayerNo);
    offDemo();
    onStatus(cStatus_191);
    if (mChangeDemoStateParam == 1)
        offStatus(cStatus_DemoControlReq);
    else
        PlayerDemoMgr::instance()->playOther();
    offStatus(cStatus_Invisible);
}

void PlayerBase::executeState_DemoNone()
{
    if (isStatus(cStatus_191) && InputMgr::instance()->isInputEnabled())
    {
        offDemo();
        offStatus(cStatus_191);
    }

    // if (checkTimeOut())
    //     return;

    if (isNowBgCross(cBgCross_IsFoot) || isStatus(cStatus_Swim) || isStatus(cStatus_37))
    {
        if (mPlayerKey.buttonRight())
            mDokanInTimerR = sead::Mathi::clampMax(mDokanInTimerR + 1, 100);
        else
            mDokanInTimerR = 0;

        if (mPlayerKey.buttonLeft())
            mDokanInTimerL = sead::Mathi::clampMax(mDokanInTimerL + 1, 100);
        else
            mDokanInTimerL = 0;
    }
    else
    {
        mDokanInTimerR = 0;
        mDokanInTimerL = 0;
    }

    if (mDemoActionTimer == 0 && isEnableDokanInStatus())
        onStatus(cStatus_EnableDokanIn);

    setDokanIn(cDokanDir_FaceUp) || setDokanIn(cDokanDir_FaceDown) ||
    setDokanIn(cDokanDir_FaceLeft) || setDokanIn(cDokanDir_FaceRight);
}

void PlayerBase::finalizeState_DemoNone()
{
}

void PlayerBase::initializeState_DemoReset()
{
}

void PlayerBase::executeState_DemoReset()
{
}

void PlayerBase::finalizeState_DemoReset()
{
}

void PlayerBase::initializeState_DemoStartCoinBattle()
{
    mPlayerKey.onStatus(PlayerKey::cStatus_NoInput);
}

void PlayerBase::onDemo()
{
    if (mPlayerNo >= 0)
    {
        PlayerMgr::instance()->setPauseDisable(mPlayerNo);
        CourseTimer::instance()->onStopTimer(mPlayerNo);
        onStatus(cStatus_DemoMode);
        onStatus(cStatus_208);
    }
}

void PlayerBase::changeDemoState(const StateID& state_id, s32 param)
{
    onDemo();
    mChangeDemoStateParam = param;
    mDemoSubAction = 0;
    mDemoAction = 0;
    offDemoType(cDemoType_1);
    offDemoType(cDemoType_3);
    offDemoType(cDemoType_4);
    mDemoStateMgr.changeState(state_id);
}

void PlayerBase::executeState_DemoStartCoinBattle()
{
    EventStartCoinBattle* p_event = sead::DynamicCast<EventStartCoinBattle>(EventMgr::instance()->getCurrentEvent());
    if (p_event == nullptr)
        changeDemoState(StateID_DemoNone, 0);
}

void PlayerBase::finalizeState_DemoStartCoinBattle()
{
    mPlayerKey.offStatus(PlayerKey::cStatus_NoInput);
}

void PlayerBase::initializeState_DemoOutDoor()
{
}

void PlayerBase::executeState_DemoOutDoor()
{
}

void PlayerBase::finalizeState_DemoOutDoor()
{
}

void PlayerBase::initializeState_DemoInDoor()
{
}

void PlayerBase::executeState_DemoInDoor()
{
}

void PlayerBase::finalizeState_DemoInDoor()
{
}

void PlayerBase::initializeState_DemoNextGotoBlock()
{
    if (isStatus(cStatus_58))
        PlayerMgr::instance()->onNextGotoBlock(mPlayerNo);

    mDstNextGotoID = mChangeDemoStateParam;
    onDemoType(cDemoType_3);
    mPlayerKey.onStatus(PlayerKey::cStatus_Demo);
    onStatus(cStatus_242);
    onStatus(cStatus_NoEntryReactCc);
    initializeDemoControl();
}

bool PlayerBase::isDemo5Any()
{
    for (s32 i = 0; i < 4; i++)
    {
        PlayerObject* p_player_obj = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player_obj != nullptr && p_player_obj->isDemoType(cDemoType_5))
            return true;
    }
    return false;
}

void PlayerBase::setFaderPos(const sead::Vector3f& pos)
{
    const BgScrollMgr& bg_scroll_mgr = *BgScrollMgr::instance();

    sead::Vector3f fader_pos = pos;
    fader_pos.x = sead::Mathf::clamp2(bg_scroll_mgr.getScreenLeft(), fader_pos.x, bg_scroll_mgr.getScreenRight());
    fader_pos.y = sead::Mathf::clamp2(bg_scroll_mgr.getScreenBottom(), fader_pos.y, bg_scroll_mgr.getScreenTop());
    MathUtil::getGlbPosToLyt(fader_pos);

    Scene::instance()->getFadeCenter().set(
        fader_pos.x,
        fader_pos.y,
        0.0f
    );

    mFaderPos = pos;
    onStatus(cStatus_FaderPosSet);
}

void PlayerBase::changeNextScene(s32)
{
    onStatus(cStatus_SceneChangeNext);
    PlayerDemoMgr::instance()->setCourseOutList(mPlayerNo);

    if (PlayerDemoMgr::instance()->getCourseOutList(0) == mPlayerNo)
    {
        Next::instance()->requestChangeScene();
        PlayerDemoMgr::instance()->setCourseOutPlayerNo(mPlayerNo);
    }
}

void PlayerBase::executeState_DemoNextGotoBlock()
{
    if (mDemoAction == cDemoNextGotoBlockAction_Walk && mDemoActionTimer == 0)
    {
        mDemoAction = cDemoNextGotoBlockAction_SceneChange;

        bool scene_already_changed = false;
        u8 file_no;

        if (isDemo5Any())
            scene_already_changed = true;
        else
        {
            file_no = CourseInfo::instance()->getFileNo();
            if (Next::instance()->isDifferentChangeSceneNextDat(file_no, mDstNextGotoID))
                scene_already_changed = true;
        }

        if (scene_already_changed)
        {
            onStatus(cStatus_SceneChangeNext);
        }
        else
        {
            sead::Vector3f fader_pos = mPos;
            if (mNextGotoDelay == cNextGotoBlockDelay_Short)
                fader_pos.y += 8.0f;
            setFaderPos(fader_pos);
            Next::instance()->setChangeSceneNextDat(file_no, mDstNextGotoID);
            changeNextScene(0);
        }
    }
}

void PlayerBase::finalizeState_DemoNextGotoBlock()
{
    mPlayerKey.offStatus(PlayerKey::cStatus_Demo);
    offStatus(cStatus_242);
    offStatus(cStatus_NoEntryReactCc);
    offStatus(cStatus_243);
}

bool PlayerBase::executeDemoState()
{
    offStatus(cStatus_265);

    MathUtil::calcTimer(&mDemoActionTimer);
    MathUtil::calcTimer(&_20ec);

    bool is_demo_mode_old = isStatus(cStatus_DemoMode);

    mDemoStateMgr.executeState();

    checkDemoControl();

    EventStartCoinBattle* p_event = sead::DynamicCast<EventStartCoinBattle>(EventMgr::instance()->getCurrentEvent());
    if (p_event != nullptr && *mDemoStateMgr.getStateID() == StateID_DemoNone)
        changeDemoState(StateID_DemoStartCoinBattle, 0);

    if (isStatus(cStatus_DemoMode) || is_demo_mode_old)
    {
        if (isStatus(cStatus_265))
            onStatus(cStatus_263);

        clearBgSpeed();

        return true;
    }
    else
    {
        return false;
    }
}

void PlayerBase::onDemoType(DemoType type)
{
    mDemoTypeFlag.setBit(type);
}

void PlayerBase::offDemoType(DemoType type)
{
    mDemoTypeFlag.resetBit(type);
}

void PlayerBase::offDemoMode()
{
    mDemoTypeFlag.makeAllZero();
}

bool PlayerBase::isDemoMode() const
{
    return !mDemoTypeFlag.isZero();
}

bool PlayerBase::isDemoType(DemoType type)
{
    return mDemoTypeFlag.isOnBit(type);
}

bool PlayerBase::isDemoAll()
{
    return isDemoMode();
}

bool PlayerBase::isDemo()
{
    if (isDemoMode() && !isDemoType(cDemoType_4))
        return true;
    else
        return false;
}

void PlayerBase::setShadowkunCatchDemo()
{
    onDemoType(cDemoType_ShadowkunCatch);
    onStatus(cStatus_ShadowkunCatch);
}

bool PlayerBase::isDisableDokanInDemo()
{
    if (isDemo5Any())
        return true;

    return isDemoMode();
}

bool PlayerBase::isDemo3Any()
{
    for (s32 i = 0; i < 4; i++)
    {
        PlayerObject* p_player_obj = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player_obj != nullptr && p_player_obj->isDemoType(cDemoType_3))
            return true;
    }
    return false;
}

bool PlayerBase::isDisableGoalDemo()
{
    if (isDemo3Any())
        return true;

    return isDemoMode();
}

bool PlayerBase::isSceneChangeWaitDone()
{
    if (isStatus(cStatus_SceneChangeNext))
        return true;

    if (isStatus(cStatus_280))
        return true;

    if (isWaitFrameCountMax())
        return true;

    return false;
}

bool PlayerBase::isDispOutCheckOn()
{
    if (isDemoType(cDemoType_1))
        return false;

    if (isStatus(cStatus_OutOfPlay))
        return false;

    if (isStatus(cStatus_Stunned))
        return false;

    if (isStatus(cStatus_RideBalloon))
        return false;

    if (isStatus(cStatus_227))
        return false;

    if (isStatus(cStatus_242))
        return false;

    if (isStatus(cStatus_153))
        return false;

    return true;
}

void PlayerBase::changeNormalAction()
{
    bgCheck(false);
    offZPosSetNone();
    changeState(StateID_Walk, cAnmBlend_Enable);
    changeDemoState(StateID_DemoNone, 0);
}

bool PlayerBase::setNextGotoBlockDemo(s32 dst_next_goto_no, s32 wait_timer, NextGotoBlockDelay delay, bool unk_rdash)
{
    if (isDemo() || isStatus(cStatus_RideBalloon))
        return false;

    if (*mDemoStateMgr.getStateID() == StateID_DemoNextGotoBlock)
        return true;

    mNextGotoDelay = delay;
    changeDemoState(StateID_DemoNextGotoBlock, dst_next_goto_no);
    mDemoActionTimer = wait_timer;

    if (RDashMgr::instance()->isNSLU() && unk_rdash)
        onStatus(cStatus_243);

    if (mNextGotoDelay == cNextGotoBlockDelay_Normal)
    {
        offStatus(cStatus_DemoMode);
        if (!isStatus(cStatus_PenguinSlide))
            changeState(StateID_Fall, cAnmBlend_Enable);
    }

    if (isStatus(cStatus_RidePlayer))
        changeState(StateID_Fall, cAnmBlend_Enable);

    return true;
}
