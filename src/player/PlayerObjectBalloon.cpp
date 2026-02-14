#include <event/EventGoalActorStop.h>
#include <event/EventMgr.h>
#include <game/AreaTask.h>
#include <game/BalloonMgr.h>
#include <game/CourseTask.h>
#include <input/InputMgr.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scene/Scene.h>
#include <sound/SndSceneMgr.h>

bool PlayerObject::isNotBalloonCourse()
{
    const FieldPlayerData* p_player_data = CourseTask::instance()->getPlayerData(mPlayerNo);
    if (p_player_data->is_entry && !(p_player_data->life_cnt > 0))
        return true;
    return false;
}

void PlayerObject::initializeState_Balloon()
{
    PlayerMgr::instance()->setPauseDisable(mPlayerNo);
    mpModelBaseMgr->setDrawType(PlayerModelBaseMgr::cDrawType_InBalloon);
    clearJumpActionInfo();
    releaseCarryActor();
    endStar();
    mFlag.setBit(2);
    mInvincibilityTimer = 0;
    mBalloonControllerConnectStatus = 1;
    if (InputMgr::instance()->isPlayerControllerConnected(mPlayerNo))
    {
        mBalloonControllerConnectStatus = 1; // Again...?
        mModelMgr.setAnm(PlayerAnmID::balloon_wait, 0.0f);
    }
    else
    {
        mBalloonControllerConnectStatus = 0;
        mModelMgr.setAnm(PlayerAnmID::balloon_wait_disconnect, 0.0f);
    }
    onStatus(cStatus_IgnoreBgCross);
    onStatus(cStatus_NoEntryReactCc);
    onStatus(cStatus_NoSwimAction);
    onStatus(cStatus_Invisible);
    onStatus(cStatus_NoPropelRoll);
    onStatus(cStatus_ControlledState);
    onStatus(cStatus_RideBalloon);
    mAccelY = 0.0f;
    mMaxFallSpeed = cMaxFallSpeed;
    mAccelF = 0.0f;
    mSpeed.y = 0.0f;
    mSpeedF = 0.0f;
    mAction = mChangeStateParam;
    switch (mAction)
    {
    default:
        break;
    case 3:
        if (!PlayerMgr::instance()->getGameData()->getPlayerData(mPlayerNo).is_connected)
            mAction = 1;
        // fallthrough
    case 0:
    case 1:
    case 6:
        onStatus(cStatus_OutOfPlay);
        if (mAction == 1 || mAction == 6)
            mActionTimer = 0;
        else
        {
            bool time_short = false;
            if (CourseTask::instance()->getGameMode() == FieldGameMode::cCoinBattle)
                time_short = true;
            else
            {
                mActionTimer = 150;
                if (CourseTask::instance()->getGameMode() == FieldGameMode::cBoostRush && PlayerMgr::instance()->getNum() == 0)
                    time_short = true;
            }
            if (time_short)
                mActionTimer = 30;
        }
        if (isNotBalloonCourse())
            mAction = 5;
        break;
    case 4:
        startSound("SE_PLY_BALLOON_SELF");
        break;
    }
    PlayerMgr::instance()->decNum(mPlayerNo);
    if (!CourseTask::instance()->isMiniGame() && PlayerMgr::instance()->getNum() == 0)
    {
        onStatus(cStatus_RideBalloonAll);
        mBalloonCheckAllFadeTimer = 210;
        PlayerMgr::instance()->setAllBalloon();
    }
    mModelMgr.setCapMode(PlayerModelBase::cCapMode_Normal);
    mEffectScale = 1.0f;
    if (mMode != cPlayerMode_Small && mMode != cPlayerMode_Mini)
        mEffectScale = 0.9f;
    setScrollMode(cScrollMode_1);
    setZPosition(8000.0f);
    mOrchestra.init(mPlayerNo);
}

bool PlayerObject::checkAllBalloonFade()
{
    if (!isStatus(cStatus_Down))
    {
        Scene::instance()->getFaderInfo() = Scene::FaderInfo::make(3, 2);
        AreaTask::instance()->requestCourseOut_Down();
        onStatus(cStatus_Down);
        return true;
    }
    return false;
}

void PlayerObject::executeState_Balloon()
{
    if (mBalloonControllerConnectStatus == 0)
    {
        if (InputMgr::instance()->isPlayerControllerConnected(mPlayerNo))
        {
            mBalloonControllerConnectStatus = 1;
            mModelMgr.setAnm(PlayerAnmID::balloon_wait, 0.0f);
        }
    }
    else
    {
        if (!InputMgr::instance()->isPlayerControllerConnected(mPlayerNo))
        {
            mBalloonControllerConnectStatus = 0;
            mModelMgr.setAnm(PlayerAnmID::balloon_wait_disconnect, 0.0f);
        }
    }
    offStatus(cStatus_252);
    EventGoalActorStop* p_goal_stop_event = PlayerDemoMgr::instance()->getGoalStopEvent();
    if (p_goal_stop_event != nullptr)
    {
        if (EventMgr::instance()->isActive(p_goal_stop_event) || p_goal_stop_event->isRequested())
            onStatus(cStatus_252);
    }
    if (isStatus(cStatus_RideBalloonAll))
    {
        if (InputMgr::instance()->isInputEnabled())
            SndSceneMgr::instance()->moveMissFin();
        if (mBalloonCheckAllFadeTimer == 0)
            checkAllBalloonFade();
    }
    if (isStatus(cStatus_RideBalloonCheckAllFade))
    {
        if (mBalloonCheckAllFadeTimer == 0)
            checkAllBalloonFade();
    }
    mAngle.y() = 0;
    switch (mAction)
    {
    default:
        break;
    case 3:
        {
            if (InputMgr::instance()->isInputEnabled()) // TODO: Assembly here is weird
            {
                mAction = 0;
                mActionTimer = GAME_RANDOM.getU32(5) * 30;
            }
        }
        break;
    case 0:
    case 1:
    case 6:
        if (mActionTimer == 0)
        {
            if (!isNotBalloonCourse())
            {
                onStatus(cStatus_156);
                offStatus(cStatus_OutOfPlay);
                if (isStatus(cStatus_RideBalloonContVoiceReq))
                    startVoiceSound(CONTINUE_COURSE);
                offStatus(cStatus_RideBalloonContVoiceReq);
                s32 type = 0;
                if (mAction == 0)
                    type = 0;
                else if (mAction == 1)
                    type = 2;
                else if (mAction == 6)
                    type = 0;
                BalloonMgr::instance()->createRevivalBallon(mPos, type, mPlayerNo);
                mAction = 2;
            }
            else
            {
                mAction = 5;
            }
        }
        break;
    case 4:
        onStatus(cStatus_156);
        mAction = 2;
        BalloonMgr::instance()->createRevivalBallon(mPos, 1, mPlayerNo);
        break;
    case 2:
        onStatus(cStatus_Invisible);
        break;
    case 5:
        if (!PlayerMgr::instance()->isDisableOrchestra())
            mOrchestra.update();
        if (!isNotBalloonCourse())
        {
            if (!isTotten())
                startVoiceSound(CONTINUE_COURSE);
            else
                onStatus(cStatus_RideBalloonContVoiceReq);
            mAction = 0;
            mActionTimer = 60;
        }
        break;
    }
}

void PlayerObject::finalizeState_Balloon()
{
    mpModelBaseMgr->setDrawType(PlayerModelBaseMgr::cDrawType_Normal);
    offStatus(cStatus_RideBalloon); // 53
    offStatus(cStatus_RideBalloonSetVisible); // 54
    offStatus(cStatus_RideBalloonContVoiceReq);
    offStatus(cStatus_156); // 95
    offStatus(cStatus_IgnoreBgCross); // 7E
    offStatus(cStatus_NoEntryReactCc); // 7A
    offStatus(cStatus_NoSwimAction); // AA
    offStatus(cStatus_Invisible); // BB
    offStatus(cStatus_OutOfPlay); // 04
    offStatus(cStatus_NoPropelRoll); // 2A
    offStatus(cStatus_252); // 81
    mFlag.resetBit(2);
    PlayerMgr::instance()->addNum(mPlayerNo);
    mEffectScale = 1.0f;
    setScrollMode(cScrollMode_0);
    mInvincibilityTimer = 127;
    offZPosSetNone();
    PlayerMgr::instance()->setPauseEnable(mPlayerNo);
}

bool PlayerObject::setBalloonInCreate()
{
    if (PlayerMgr::instance()->isCreateBalloon(mPlayerNo))
    {
        changeDemoState(StateID_DemoNone, 1);
        offStatus(cStatus_ControlledState);
        changeState(StateID_Balloon, 3);
        return true;
    }
    return false;
}

bool PlayerObject::setBalloonInDamage()
{
    if (isStatus(cStatus_RideBalloon))
        return false;
    changeDemoState(StateID_DemoNone, 1);
    setPlayerModeForce(cPlayerMode_Small);
    if (*mStateMgr.getStateID() != StateID_Balloon)
        changeState(StateID_Balloon, 0);
    return true;
}

bool PlayerObject::setBalloonDispOutBase()
{
    if (PlayerMgr::instance()->getNum() == 0)
        return false;
    if (PlayerMgr::instance()->getEntryNum() == 1)
        return false;
    if (isStatus(cStatus_RideBalloon))
        return false;
    changeDemoState(StateID_DemoNone, 1);
    if (*mStateMgr.getStateID() != StateID_Balloon)
        changeState(StateID_Balloon, 6);
    return true;
}

bool PlayerObject::setBalloonButtonA()
{
    if (!mPlayerKey.triggerA())
        return false;
    if (PlayerMgr::instance()->getEntryNum() == 1)
        return false;
    if (!(EventMgr::instance() != nullptr && !EventMgr::instance()->isActive()))
        return false;
    if (isDemoAll())
        return false;
    if (isStatus(cStatus_280))
        return false;
    if (isStatus(cStatus_Quake))
        return false;
    if (isStatus(cStatus_RideBalloon))
        return false;
    if (isNotBalloonCourse())
        return false;
    if (!BalloonMgr::instance()->isEnableRevivalBallon())
        return false;
    if (CourseTask::instance()->isMiniGame())
        return false;
    if (!PlayerMgr::instance()->isNormalCourse())
        return false;
    if (getFollowMameKuribo() != 0)
    {
        startSound("SE_EMY_MAMEKURIBO_CLINGING_NOW");
        return false;
    }
    changeDemoState(StateID_DemoNone, 1);
    if (*mStateMgr.getStateID() != StateID_Balloon)
        changeState(StateID_Balloon, 4);
    return true;
}

bool PlayerObject::setBalloonInDispOutBase(s32 type, bool by_yoshi)
{
    if (!isDispOutCheckOn())
        return false;
    if ((type == 1 || type == 0) &&
        isDemoAll() &&
        !isStatus(cStatus_129))
    {
        return false;
    }
    if (getCarryPlayer() != nullptr)
        getCarryPlayer()->setBalloonInDispOut(type);
    if (type == 1 || type == 0)
    {
        if (isStatus(cStatus_DispOut))
            setFallDownDemo();
        else
            setPressBgDamage(cDamageType_Kill, false);
        startVoiceSound(SCROLL_OUT);
        Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_4);
    }
    else
    {
        setFallDownDemo();
    }
    return true;
}

bool PlayerObject::setBalloonInDispOutByYoshi(s32 type)
{
    return setBalloonInDispOutBase(type, true);
}

bool PlayerObject::setBalloonInNextgoto()
{
    if (PlayerMgr::instance()->getNum() == 0)
        return false;
    if (PlayerMgr::instance()->getEntryNum() == 1)
        return false;
    if (isStatus(cStatus_RideBalloon))
        return false;
    changeDemoState(StateID_DemoNone, 0);
    if (*mStateMgr.getStateID() != StateID_Balloon)
        changeState(StateID_Balloon, 1);
    return true;
}

bool PlayerObject::setBalloonInDispOut(s32 type)
{
    if (type == 3 && isStatus(cStatus_254))
        return false;
    if (PlayerMgr::instance()->getCannonJumpTimer() != 0)
        return setBalloonDispOut();
    return setBalloonInDispOutBase(type, false);
}

bool PlayerObject::setBalloonDispOut()
{
    if (!isDispOutCheckOn())
        return false;
    if (getCarryPlayer() != nullptr)
        getCarryPlayer()->setBalloonDispOut();
    setBalloonDispOutBase();
    return true;
}

void PlayerObject::setBreakBalloonJump(Angle angle)
{
    offStatus(cStatus_ControlledState);
    startVoiceSound(HUKKATSU);
    startSound("SE_PLY_BALLOON_BRAKE");
    Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_4);
    _21e0 = 30;
    _2064 = 30;
    _2068 = 30;
    _206c = 30;
    if (isNowBgCross(cBgCross_IsUnderwater))
    {
        changeState(StateID_Swim, 0);
        f32 sin_v, cos_v;
        sead::Mathf::sinCosIdx(&sin_v, &cos_v, angle);
        f32 speed_y = 2 * cos_v;
        f32 speed_F = 2 * sin_v;
        setSwimSpeed(speed_y, speed_F);
    }
    else
    {
        f32 sin_v, cos_v;
        sead::Mathf::sinCosIdx(&sin_v, &cos_v, angle);
        f32 speed_F = 4.0f * sin_v;
        f32 speed_y = cJumpSpeed * cos_v;
        bouncePlayer1(
            sead::Mathf::clampMin(speed_y, 0.0f),
            speed_F,
            true, cBounceType_1, cJumpSe_None
        );
        setHopAirDrift();
    }
}

void PlayerObject::setDrawBalloonInPlayer(sead::Vector3f& pos)
{
    static const f32 c_balloon_offset_y[] = {
         0.0f,  // cPlayerMode_Small
        -4.0f,  // cPlayerMode_Normal
        -4.0f,  // cPlayerMode_Fire
         4.0f,  // cPlayerMode_Mini
        -5.0f,  // cPlayerMode_Propeller
        -2.0f,  // cPlayerMode_Penguin
        -4.0f,  // cPlayerMode_Ice
        -4.0f,  // cPlayerMode_Squirrel
        -4.0f   // cPlayerMode_PSquirrel
    };
    static_assert(sizeof(c_balloon_offset_y) / sizeof(f32) == cPlayerMode_Num);
    f32 offset_y = c_balloon_offset_y[mMode];
    if (isKinopio() && (mMode == cPlayerMode_Squirrel || mMode == cPlayerMode_PSquirrel))
        offset_y += 2.0f;
    if (isStatus(cStatus_RideBalloon))
    {
        pos.y += offset_y;
        mPos = pos;
        mPosPrev = pos;
        mPosPrev2 = pos;
        calcModelBalloon();
    }
}

void PlayerObject::setDrawBalloonInPlayerEnable()
{
    if (isStatus(cStatus_RideBalloon))
        onStatus(cStatus_RideBalloonSetVisible);
}

void PlayerObject::setBalloonHelpVoice()
{
    if (!isStatus(cStatus_RideBalloon))
        return;
    if (mAction != 2)
        return;
    if (isStatus(cStatus_DispOut))
        return;
    if (mBalloonHelpVoiceTimer == 0)
    {
        startVoiceSound(BALLOON_HELP__RC);
        mBalloonHelpVoiceTimer = 120;
    }
}

void PlayerObject::setBalloonCheckAllFade()
{
    onStatus(cStatus_RideBalloonCheckAllFade);
    mBalloonCheckAllFadeTimer = 120;
}
