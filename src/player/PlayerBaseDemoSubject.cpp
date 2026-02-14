#include <game/AreaTask.h>
#include <game/CourseTask.h>
#include <game/SubjectMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <utility/MathUtil.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectCoinEndWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClearGoalWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClear)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClearWait)

void PlayerBase::initializeState_DemoSubjectClearLand()
{
    setWaitActionAnm(cAnmBlend_Enable);
    mDemoActionTimer = 60;
    mDemoAction = 0;
}

void PlayerBase::setSubjectClearCourseOut()
{
    sead::Vector3f fader_pos(mPos.x, mPos.y + 8.0f, mPos.z);
    setFaderPos(fader_pos);
    AreaTask::instance()->requestCourseOut_Subject();
}

void PlayerBase::executeState_DemoSubjectClearLand()
{
    mAngle.y().chaseRest(0, 0x08000000);
    switch (mDemoAction)
    {
    default:
        break;
    case 0:
        if (mDemoActionTimer == 0)
        {
            initDemoKimePose();
            mDemoAction = 1;
        }
        break;
    case 1:
        if (execDemoKimePose(cCourseClearType_Normal))
        {
            mDemoAction = 2;
            mDemoActionTimer = 60;
        }
        break;
    case 2:
        if (mDemoActionTimer == 0)
        {
            setSubjectClearCourseOut();
            mDemoAction = 3;
        }
        break;
    case 3:
        break;
    }
}

void PlayerBase::finalizeState_DemoSubjectClearLand()
{
    offStatus(cStatus_223);
}

void PlayerBase::initializeState_DemoSubjectClearAir()
{
    onStatus(cStatus_DisableAnm);
    mDemoActionTimer = 180;
    mDemoAction = 0;
}

void PlayerBase::executeState_DemoSubjectClearAir()
{
    if (mDemoAction == 0 && mDemoActionTimer == 0)
    {
        setSubjectClearCourseOut();
        mDemoAction = 3;
    }
}

void PlayerBase::finalizeState_DemoSubjectClearAir()
{
    offStatus(cStatus_DisableAnm);
}

void PlayerBase::initializeState_DemoShadowFail()
{
}

void PlayerBase::executeState_DemoShadowFail()
{
}

void PlayerBase::finalizeState_DemoShadowFail()
{
}

void PlayerBase::initializeState_SubjectWait()
{
}

bool PlayerBase::isSubjectDone()
{
    if (CourseTask::instance()->getGameMode() == FieldGameMode::cChallenge)
    {
        SubjectMgr::Mode mode = SubjectMgr::instance()->getMode();
        if (mode == SubjectMgr::cMode_Clear || mode == SubjectMgr::cMode_Fail)
            return true;
    }
    return false;
}

void PlayerBase::changeSubjectState(const StateID& state_id)
{
    mSubjectStateMgr.changeState(state_id);
}

void PlayerBase::subjectClearRequest()
{
    if (SubjectMgr::instance()->isSkipClearWait())
        PlayerDemoMgr::instance()->setSubjectClear();
    else
        changeSubjectState(StateID_SubjectClearWait);
}

void PlayerBase::trySetSubjectCoinClear()
{
    if (PlayerDemoMgr::instance()->isGoalDemoMode())
        changeSubjectState(StateID_SubjectClearGoalWait);
    else if (isNowBgCross(cBgCross_IsFoot))
        subjectClearRequest();
}

void PlayerBase::executeState_SubjectWait()
{
    if (!isSubjectDone())
        return;

    SubjectMgr::Mode mode = SubjectMgr::instance()->getMode();
    mIsSubjectClear = mode == SubjectMgr::cMode_Clear;
    switch (SubjectMgr::instance()->getFinishType())
    {
    default:
        break;
    case 0:
        changeSubjectState(StateID_SubjectCoinEndWait);
        trySetSubjectCoinClear();
        break;
    case 1:
        changeSubjectState(StateID_SubjectClearGoalWait);
        break;
    case 2:
        if (mode != SubjectMgr::cMode_Fail)
        {
            changeSubjectState(StateID_SubjectCoinEndWait);
            trySetSubjectCoinClear();
        }
        break;
    case 3:
        if (PlayerDemoMgr::instance()->isGoalDemoMode())
            changeSubjectState(StateID_SubjectClearGoalWait);
        else if (mode == SubjectMgr::cMode_Fail)
            subjectClearRequest();
        break;
    case 4:
        subjectClearRequest();
        break;
    case 5:
        break;
    }
}

void PlayerBase::finalizeState_SubjectWait()
{
}

void PlayerBase::initializeState_SubjectCoinEndWait()
{
    onStatus(cStatus_186);
}

void PlayerBase::executeState_SubjectCoinEndWait()
{
    trySetSubjectCoinClear();
}

void PlayerBase::finalizeState_SubjectCoinEndWait()
{
}

void PlayerBase::initializeState_SubjectClearGoalWait()
{
}

void PlayerBase::executeState_SubjectClearGoalWait()
{
    if (!isStatus(cStatus_185))
        return;

    PlayerDemoMgr::instance()->setSubjectClear();
}

void PlayerBase::finalizeState_SubjectClearGoalWait()
{
}

void PlayerBase::initializeState_SubjectClear()
{
    onStatus(cStatus_183);
    if (mIsSubjectClear)
    {
        bool unk = isStatus(cStatus_Swim);
        changeState(StateID_None, 0);
        CourseTask::instance()->setSubjectClear();
        PlayerMgr::instance()->setSubjectClear();
        if (unk)
        {
            _214c = 120;
            onStatus(cStatus_104);
            onStatus(cStatus_187);
        }
        if (isNowBgCross(cBgCross_IsFoot))
            changeDemoState(StateID_DemoSubjectClearLand, 0);
        else
            changeDemoState(StateID_DemoSubjectClearAir, 0);
    }
    else
    {
        setSubjectFail();
    }
}

void PlayerBase::executeState_SubjectClear()
{
    if (isStatus(cStatus_187) && _214c == 0)
    {
        offStatus(cStatus_187);
        setSubjectClearCourseOut();
    }
}

void PlayerBase::finalizeState_SubjectClear()
{
    offStatus(cStatus_183);
    offStatus(cStatus_186);
}

void PlayerBase::initializeState_SubjectClearWait()
{
    mSubjectClearWaitTimer = 10;
    startControlDemo(true);
    checkDemoControl();
    onStatus(cStatus_NoEntryReactCc);
}

void PlayerBase::executeState_SubjectClearWait()
{
    if (PlayerDemoMgr::instance()->isGoalDemoMode())
        changeSubjectState(StateID_SubjectClearGoalWait);
    else if (mSubjectClearWaitTimer == 0)
        PlayerDemoMgr::instance()->setSubjectClear();
}

void PlayerBase::finalizeState_SubjectClearWait()
{
    offStatus(cStatus_NoEntryReactCc);
}

void PlayerBase::executeSubjectState()
{
    MathUtil::calcTimer(&mSubjectClearWaitTimer);
    mSubjectStateMgr.executeState();
}

void PlayerBase::setDownFinishSubjectCoin()
{
    if (SubjectMgr::instance()->isSubjectCoin())
    {
        SubjectMgr::instance()->setFinishSubjectCoin(CourseTask::instance()->getGameData()->getCoinNum());
        mIsSubjectClear = SubjectMgr::instance()->getMode() == SubjectMgr::cMode_Clear;
    }
    else
    {
        mIsSubjectClear = false;
    }
}

void PlayerBase::setDownFinishSubject()
{
    if (CourseTask::instance()->getGameMode() != FieldGameMode::cChallenge)
        return;

    if (mIsSubjectClear)
    {
        onStatus(cStatus_184);
        CourseTask::instance()->setSubjectClear();
        PlayerMgr::instance()->setSubjectClear();
    }
    else
    {
        CourseTask::instance()->setSubjectFail();
    }
}

bool PlayerBase::setFumiSubjectCoinEndClear()
{
    if (*mSubjectStateMgr.getStateID() == StateID_SubjectCoinEndWait)
    {
        subjectClearRequest();
        return true;
    }
    return false;
}
