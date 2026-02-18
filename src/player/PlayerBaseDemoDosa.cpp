#include <actor/AttentionMgr.h>
#include <input/SysControllerWrapper.h>
#include <player/PlayerBase.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerModelBaseMgr.h>

void PlayerBase::initializeState_DemoControl()
{
    onDemoType(cDemoType_4);

    if (isStatus(cStatus_DemoOnLandStop))
        offStatus(cStatus_DemoOnLandStop);

    mPlayerKey.onStatus(PlayerKey::cStatus_Demo);

    onStatus(cStatus_DemoControl);
    offStatus(cStatus_DemoControlReq);
    offStatus(cStatus_240);
    offStatus(cStatus_149);
    onStatus(cStatus_64);
    offStatus(cStatus_DemoMode);

    initializeDemoControl(false);

    mDemoSubAction = mChangeDemoStateParam;
    if (mDemoSubAction == cDemoControlSubAction_4)
    {
        mDemoActionTimer = 60;
        onStatus(cStatus_NoEntryReactCc);
    }
}

void PlayerBase::executeState_DemoControl()
{
    offStatus(cStatus_239);

    switch (mDemoSubAction)
    {
    default:
        break;
    case cDemoControlSubAction_Walk:
        {
            onStatus(cStatus_239);
            if (isNowBgCross(cBgCross_IsFoot))
            {
                if (*mStateMgr.getStateID() != StateID_Walk)
                {
                    if (*mStateMgr.getStateID() != StateID_Turn)
                        changeState(StateID_Walk, cAnmBlend_Enable);
                }
            }
            else
            {
                if (*mStateMgr.getStateID() != StateID_Fall)
                    changeState(StateID_Fall, cAnmBlend_Enable);
            }
            if (sead::Mathf::abs(mPos.x - _2100.x) < _2108.x)
            {
                mDemoSubAction = cDemoControlSubAction_Wait;
                mPos.x = _2100.x;
                mSpeedF = 0.0f;
            }
            else if (mPos.x < _2100.x)
            {
                mPlayerKey.onDemoTrigger(PlayerKey::cKey_Right);
                mSpeedF = _2108.x;
            }
            else
            {
                mPlayerKey.onDemoTrigger(PlayerKey::cKey_Left);
                mSpeedF = -_2108.x;
            }
        }
        break;
    case cDemoControlSubAction_4:
        if (mDemoActionTimer == 0)
            changeDemoState(StateID_DemoNone, 0);
        break;
    }
}

void PlayerBase::finalizeState_DemoControl()
{
    mPlayerKey.offStatus(PlayerKey::cStatus_Demo);
    offStatus(cStatus_DemoControl);
    offStatus(cStatus_NoSlipSaka);
    offStatus(cStatus_239);
    offStatus(cStatus_240);
    offStatus(cStatus_64);
    if (mDemoSubAction == cDemoControlSubAction_4)
        offStatus(cStatus_NoEntryReactCc);
}

void PlayerBase::setControlDemoPos(const sead::Vector3f& pos)
{
    if (!isStatus(cStatus_DemoControl))
        return;

    mPos = pos;
    mPosPrev = pos;
    mPosPrev2 = pos;

    mSpeedF = 0.0f;
    mSpeed.y = 0.0f;

    offNowBgCross(cBgCross_IsUnderwater);
    checkWater();
    if (!isNowBgCross(cBgCross_IsUnderwater))
    {
        onNowBgCross(cBgCross_IsFoot);
        if (*mStateMgr.getStateID() != StateID_Walk)
            changeState(StateID_Walk, cAnmBlend_Disable);
    }
}

void PlayerBase::setControlDemoDir(s32 dir)
{
    if (!isStatus(cStatus_DemoControl))
        return;

    mDirection = dir;

    if (!isNowBgCross(cBgCross_IsUnderwater))
    {
        onNowBgCross(cBgCross_IsFoot);
        if (*mStateMgr.getStateID() != StateID_Walk)
            changeState(StateID_Walk, cAnmBlend_Enable);
    }
}

void PlayerBase::setControlDemoWait()
{
    if (!isStatus(cStatus_DemoControl))
        return;

    if (!isNowBgCross(cBgCross_IsUnderwater))
    {
        mPlayerKey.offDemoTrigger(PlayerKey::cKey_Right);
        mPlayerKey.offDemoTrigger(PlayerKey::cKey_Left);
        mDemoSubAction = cDemoControlSubAction_Wait;
        onNowBgCross(cBgCross_IsFoot);
        changeState(StateID_Walk, cAnmBlend_Enable);
    }
}

bool PlayerBase::isControlDemoWait()
{
    if (isStatus(cStatus_DemoControl))
    {
        if (mDemoSubAction == cDemoControlSubAction_Wait)
            return true;
    }
    return false;
}

void PlayerBase::setControlDemoWalk(f32 target_pos_x, f32 speed)
{
    if (!isStatus(cStatus_DemoControl))
        return;

    _2100.x = target_pos_x;
    _2108.x = sead::Mathf::abs(speed);
    mDemoSubAction = cDemoControlSubAction_Walk;

    if (_2108.x > getSpeedData()->max_run_speed_hi)
        _2108.x = getSpeedData()->max_run_speed_hi;
}

bool PlayerBase::isControlDemoWalk()
{
    if (isStatus(cStatus_DemoControl))
    {
        if (mDemoSubAction == cDemoControlSubAction_Walk)
            return true;
    }
    return false;
}

void PlayerBase::setControlDemoAnm(s32 anm_id, bool loop)
{
    if (!isStatus(cStatus_DemoControl))
        return;

    mDemoSubAction = cDemoControlSubAction_Anm;
    changeState(StateID_AnimePlay, cAnimePlayType_Normal);

    mpModelBaseMgr->setAnm(anm_id);

    if (loop)
        onStatus(cStatus_DemoAnmLoop);
    else
        offStatus(cStatus_DemoAnmLoop);
}

// bool PlayerBase::isControlDemoAnm(s32 anm_id)
// {
//     if (isStatus(cStatus_DemoControl))
//     {
//         if (mDemoSubAction == cDemoControlSubAction_Anm && anm_id == mpModelBaseMgr->getAnmID())
//             return true;
//     }
//     return false;
// }

void PlayerBase::setControlDemoAnmSeq(AnimePlayType type)
{
    if (!isStatus(cStatus_DemoControl))
        return;

    mDemoSubAction = cDemoControlSubAction_AnmSeq;
    changeState(StateID_AnimePlay, type);
}

bool PlayerBase::isControlDemoAnmSeq(AnimePlayType type)
{
    if (isStatus(cStatus_DemoControl))
    {
        if (mDemoSubAction == cDemoControlSubAction_AnmSeq && mAnimePlayType == type && isStatus(cStatus_ControlledState))
            return true;
    }
    return false;
}

bool PlayerBase::isDemoLand()
{
    if (!isNowBgCross(cBgCross_IsFoot))
        return false;

    if (isStatus(cStatus_40))
        return false;

    if (isStatus(cStatus_IgnoreBgCross))
        return false;

    return true;
}

bool PlayerBase::isBossDemoLand()
{
    return isDemoLand();
}

bool PlayerBase::isEnemyStageClearDemoLand()
{
    if (!isDemoLand())
        return false;

    if (isNowBgCross(cBgCross_IsChikuwaActor))
        return false;

    return true;
}

bool PlayerBase::startControlDemo(bool status)
{
    if (isStatus(cStatus_DemoControl))
        return false;

    if (!PlayerMgr::instance()->isPlayerActive(mPlayerNo))
        return false;

    onStatus(cStatus_DemoControlReq);
    if (status)
        onStatus(cStatus_NoSlipSaka);
    else
        offStatus(cStatus_NoSlipSaka);
    offStatus(cStatus_237);
    offStatus(cStatus_149);
    return true;
}

bool PlayerBase::isEnableControlDemoKoopaSwitch()
{
    return true;
}

bool PlayerBase::startControlDemoKoopaSwitch()
{
    if (startControlDemo(true))
    {
        mSpeed.y = 0.0f;
        mSpeedF = 0.0f;
        setFallAction();
        return true;
    }
    return false;
}

void PlayerBase::endControlDemo()
{
    if (!isStatus(cStatus_DemoControl))
        return;

    changeNormalAction();
}

bool PlayerBase::isUnkDemoLand()
{
    if (!isDemoLand())
    {
        if (!(isNowBgCross(cBgCross_IsUnderwater) && isStatus(cStatus_89)))
            return false;
    }
    else
    {
        if (isStatus(cStatus_241) && isNowBgCross(cBgCross_IsChikuwaActor))
            return false;
    }
    return true;
}

void PlayerBase::checkDemoControl()
{
    if (!isStatus(cStatus_DemoControlReq))
        return;

    if (*mDemoStateMgr.getStateID() != StateID_DemoNone)
        return;

    bool change_state = false;
    if (isStatus(cStatus_NoSlipSaka))
    {
        if (isStatus(cStatus_240))
            mSpeedF *= 0.98f;

        if (isUnkDemoLand())
        {
            mSpeedF = 0.0f;
            change_state = true;
        }
    }
    else
    {
        change_state = true;
    }
    if (change_state)
        changeDemoState(StateID_DemoControl, 0);

    if (isStatus(cStatus_237) && isStatus(cStatus_73))
    {
        mSpeedF = 0.0f;
        changeState(StateID_Walk, cAnmBlend_Disable);
    }
}

void PlayerBase::initializeState_AnimePlay()
{
    mAnimePlayType = AnimePlayType(mChangeStateParam);
    if (mAnimePlayType != cAnimePlayType_Normal)
        onStatus(cStatus_ControlledState);
}

void PlayerBase::DemoAnmNormal()
{
    if (isStatus(cStatus_57))
        addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    else
        turnAngle();

    if (!isStatus(cStatus_DemoAnmLoop) && mpModelBaseMgr->isAnmStop())
        setControlDemoWait();
}

void PlayerBase::DemoAnmBossSetUp()
{
    turnAngle();
    if (mAction == cAnimePlayAction_Start)
    {
        mpModelBaseMgr->setAnm(PlayerAnmID::waitL3);
        mAction = cAnimePlayAction_End;
        offStatus(cStatus_ControlledState);
    }
}

void PlayerBase::DemoAnmBossGlad()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mActionTimer = 15;
        mAction = cAnimePlayAction_Glad_KimeStart;
        onStatus(cStatus_155);
        // fallthrough
    case cAnimePlayAction_Glad_KimeStart:
        if (mActionTimer == 0)
        {
            initDemoKimePose();
            mAction = cAnimePlayAction_Glad_PutOnCap;
        }
        break;
    case cAnimePlayAction_Glad_PutOnCap:
        if (updateDemoKimePose(cClearType_Boss))
            mAction = cAnimePlayAction_Glad_KimeWait;
        break;
    case cAnimePlayAction_Glad_KimeWait:
        if (!PlayerDemoMgr::instance()->isGoalDemoKimeWait())
        {
            mActionTimer = 20;
            mAction = cAnimePlayAction_Glad_Wait;
        }
        break;
    case cAnimePlayAction_Glad_Wait:
        if (mActionTimer == 0)
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::wait, 5.0f, 0.0f);
            mAction = cAnimePlayAction_End;
            offStatus(cStatus_ControlledState);
        }
        break;
    }
}

void PlayerBase::DemoAnmBossAttention()
{
    f32 lookat_pos_x = getLookatPos().x;
    f32 lookat_pos_y = getLookatPos().y;
    const AttentionLookat* p_lookat = AttentionMgr::instance()->search(*this, sead::Vector2f(lookat_pos_x, lookat_pos_y));
    if (p_lookat != nullptr)
        mDirection = p_lookat->getPos().x > mPos.x ? cDirType_Right : cDirType_Left;

    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mpModelBaseMgr->setAnm(mDirection == cDirType_Right ? PlayerAnmID::waitL__2 : PlayerAnmID::waitR__2);
        mAction = cAnimePlayAction_BossAttention_Turn;
        break;
    case cAnimePlayAction_BossAttention_Turn:
        {
            Angle target = getMukiAngle();
            Angle step = /* sead::Mathf::deg2idx(10) */ 0x071C71C7;
            if (mAngle.y().chaseRest(target, step))
            {
                mAction = cAnimePlayAction_End;
                offStatus(cStatus_ControlledState);
            }
        }
        break;
    }
}

void PlayerBase::DemoAnmBossKeyGet()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mActionTimer = 15;
        mAction = cAnimePlayAction_BossKeyGet_Cheer;
        // fallthrough
    case cAnimePlayAction_BossKeyGet_Cheer:
        if (mActionTimer == 0)
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::boss_key_get, 0.0f);
            startKimePoseVoice(cClearType_Boss);
            mAction = cAnimePlayAction_End;
            offStatus(cStatus_ControlledState);
        }
        break;
    }
}

void PlayerBase::DemoAnmLastBoss2Glad()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mActionTimer = 15;
        mAction = cAnimePlayAction_Glad_KimeStart;
        // fallthrough
    case cAnimePlayAction_Glad_KimeStart:
        if (mActionTimer == 0)
        {
            initDemoKimePose();
            mAction = cAnimePlayAction_Glad_PutOnCap;
        }
        break;
    case cAnimePlayAction_Glad_PutOnCap:
        if (updateDemoKimePose(cClearType_LastBoss))
            mAction = cAnimePlayAction_Glad_KimeWait;
        break;
    case cAnimePlayAction_Glad_KimeWait:
        if (!PlayerDemoMgr::instance()->isGoalDemoKimeWait())
        {
            mActionTimer = 20;
            mAction = cAnimePlayAction_Glad_Wait;
        }
        break;
    case cAnimePlayAction_Glad_Wait:
        if (mActionTimer == 0)
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::wait, 5.0f, 0.0f);
            mAction = cAnimePlayAction_End;
            offStatus(cStatus_ControlledState);
        }
        break;
    }
}

void PlayerBase::DemoAnmLastBoss1Glad()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mActionTimer = 15;
        mAction = cAnimePlayAction_Glad_KimeStart;
        onStatus(cStatus_155);
        // fallthrough
    case cAnimePlayAction_Glad_KimeStart:
        if (mActionTimer == 0)
        {
            initDemoKimePose();
            mAction = cAnimePlayAction_Glad_PutOnCap;
        }
        break;
    case cAnimePlayAction_Glad_PutOnCap:
        if (updateDemoKimePose(cClearType_Fanfare))
            mAction = cAnimePlayAction_Glad_KimeWait;
        break;
    case cAnimePlayAction_Glad_KimeWait:
        if (!PlayerDemoMgr::instance()->isGoalDemoKimeWait())
        {
            mActionTimer = 20;
            mAction = cAnimePlayAction_Glad_Wait;
        }
        break;
    case cAnimePlayAction_Glad_Wait:
        if (mActionTimer == 0)
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::wait, 5.0f, 0.0f);
            mAction = cAnimePlayAction_End;
            offStatus(cStatus_ControlledState);
        }
        break;
    }
}

void PlayerBase::DemoAnmTitleSlip()
{
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        offStatus(cStatus_ControlledState);
        mpModelBaseMgr->setAnm(PlayerAnmID::ice_slipF);
        mAction = cAnimePlayAction_TitleSlip_Move;
        // fallthrough
    case cAnimePlayAction_TitleSlip_Move:
        calcSpeedF_(0.07f, 0.0f);
        if (mPos.x > _2100.x)
            mPos.x = _2100.x;
        if (mpModelBaseMgr->isAnmStop() && mSpeedF == 0.0f)
        {
            mPos.x = _2100.x;
            mSpeedF = 0.0f;
            setControlDemoWait();
        }
        break;
    }
}

void PlayerBase::DemoAnmEndingGlad()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    switch (mAction)
    {
    default:
        break;
    case cAnimePlayAction_Start:
        mActionTimer = 15;
        mAction = cAnimePlayAction_Glad_KimeStart;
        onStatus(cStatus_155);
        // fallthrough
    case cAnimePlayAction_Glad_KimeStart:
        if (mActionTimer == 0)
        {
            initDemoKimePose();
            mAction = cAnimePlayAction_Glad_PutOnCap;
        }
        break;
    case cAnimePlayAction_Glad_PutOnCap:
        if (updateDemoKimePose(cClearType_Fanfare))
            mAction = cAnimePlayAction_Glad_KimeWait;
        break;
    case cAnimePlayAction_Glad_KimeWait:
        if (!PlayerDemoMgr::instance()->isGoalDemoKimeWait())
        {
            mActionTimer = 20;
            mAction = cAnimePlayAction_Glad_Wait;
        }
        break;
    case cAnimePlayAction_Glad_Wait:
        if (mActionTimer == 0)
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::dm_glad4_wait, 5.0f, 0.0f);
            mAction = cAnimePlayAction_End;
            offStatus(cStatus_ControlledState);
        }
        break;
    }
}

void PlayerBase::DemoAnmEndingGladWait()
{
    addCalcAngleY(0, cAddCalcAngleYFrameNum_Default);
    if (mAction == cAnimePlayAction_Start)
    {
        onStatus(cStatus_155);
        mpModelBaseMgr->setAnm(PlayerAnmID::dm_glad4_wait, 5.0f, 0.0f);
        mAction = cAnimePlayAction_End;
    }
}

void PlayerBase::executeState_AnimePlay()
{
    mAccelY = getGravityData()->gravity;
    maxFallSpeedSet();
    moveSpeedSet();
    powerSet();
    if (isStatus(cStatus_ControlledState) || !checkWalkNextAction())
    {
        switch (mAnimePlayType)
        {
        default:
            break;
        case cAnimePlayType_Normal:
            DemoAnmNormal();
            break;
        case cAnimePlayType_BossSetUp:
            DemoAnmBossSetUp();
            break;
        case cAnimePlayType_BossGlad:
            DemoAnmBossGlad();
            break;
        case cAnimePlayType_BossAttention:
            DemoAnmBossAttention();
            break;
        case cAnimePlayType_BossKeyGet:
            DemoAnmBossKeyGet();
            break;
        case cAnimePlayType_LastBoss2Glad:
            DemoAnmLastBoss2Glad();
            break;
        case cAnimePlayType_LastBoss1Glad:
            DemoAnmLastBoss1Glad();
            break;
        case cAnimePlayType_TitleSlip:
            DemoAnmTitleSlip();
            break;
        case cAnimePlayType_EndingGlad:
            DemoAnmEndingGlad();
            break;
        case cAnimePlayType_EndingGladWait:
            DemoAnmEndingGladWait();
            break;
        case cAnimePlayType_TottenItem:
            DemoAnmTottenItem();
            break;
        }
    }
}

void PlayerBase::finalizeState_AnimePlay()
{
    offStatus(cStatus_155);
    offStatus(cStatus_ControlledState);
    offStatus(cStatus_57);
    offStatus(cStatus_DemoAnmLoop);
}

void PlayerBase::DemoAnmTottenItem()
{
}
