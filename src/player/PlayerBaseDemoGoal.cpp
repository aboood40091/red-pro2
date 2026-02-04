#include <collision/BgCollisionCheckResult.h>
#include <game/CoinBattleScoreMgr.h>
#include <game/CourseTask.h>
#include <game/CourseTimer.h>
#include <layout/GamesceneBase.h>
#include <player/PlayerBase.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerModelBaseMgr.h>
#include <system/MainGame.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

void PlayerBase::setDemoGoalMode(s32 demo_action, s32 demo_sub_action)
{
    mDemoAction = demo_action;
    mDemoSubAction = demo_sub_action;
}

void PlayerBase::initializeState_DemoGoal()
{
    onStatus(cStatus_212);
    onStatus(cStatus_DemoScript);
    if (mChangeDemoStateParam == 0)
    {
        setGoalPoleCatchVoice();
        onStatus(cStatus_247);
    }
    clearJumpActionInfo();
    endStar();
    setDemoGoalMode(cDemoGoalAction_Pole, 0);
    mpModelBaseMgr->setAnm(PlayerAnmID::goal_start);
    mAngle.x() = 0;
    setZPositionDirect(2900.0f);
    mSpeed.x = 0.0f;
    mSpeedF = 0.0f;
    mSpeed.y = 0.0f;
    mAccelY = 0.0f;
    mMaxFallSpeed = -4.0f;
}

void PlayerBase::executeDemoGoal_Pole()
{
    switch (mDemoSubAction)
    {
    default:
        break;
    case 0: // Start
        if (mMode == cPlayerMode_Mini)
        {
            setZPositionDirect(2905.0f);
            mPos.x = PlayerDemoMgr::instance()->getGoalPos().x + -3.0f * sead::Mathf::sinIdx(mAngle.y());
        }
        else
        {
            setZPositionDirect(2900.0f);
            mPos.x = PlayerDemoMgr::instance()->getGoalPos().x;
        }
        if (addCalcAngleY(-0x40000000, cAddCalcAngleYFrameNum_Default) == 0 && mpModelBaseMgr->isAnmStop())
        {
            mDemoSubAction = 1;
            mpModelBaseMgr->setAnm(PlayerAnmID::goal_wait);
            onStatus(cStatus_213);
        }
        break;
    case 1: // Wait
        {
            bool done = false;
            if (isStatus(cStatus_214))
            {
                s32 below_player_no = PlayerDemoMgr::instance()->getPoleBelowPlayer(mPlayerNo);
                if (below_player_no == -1)
                    done = true;
                else
                {
                    PlayerBase* p_below_player = PlayerMgr::instance()->getCtrlPlayer(below_player_no);
                    if (p_below_player == nullptr)
                        done = true;
                    else
                    {
                        if (mPos.y > p_below_player->mPos.y + p_below_player->mHeight * 0.7f)
                            done = true;
                        else
                        {
                            if (p_below_player->isStatus(cStatus_215))
                                done = true;                            
                        }
                    }
                }
            }
            if (done)
            {
                mDemoSubAction = 2;
                offStatus(cStatus_213);
                PlayerDemoMgr::instance()->setPoleDown();
                mSpeed.y = -1.9f;
            }
        }
        break;
    case 2: // Down
        mPos.y += mSpeed.y;
        if (mPos.y < mGoalBasePosY)
        {
            mPos.y = mGoalBasePosY;
            onStatus(cStatus_215);
            mSpeed.y = 0.0f;
            mDemoSubAction = 3;
            mpModelBaseMgr->setAnm(PlayerAnmID::goal_pose);
        }
        break;
    case 3: // Hang flag start
    case 4: // Hung flag wait
        if (isStatus(cStatus_216))
        {
            if (mDemoSubAction == 3)
            {
                mDemoSubAction = 5;
                mpModelBaseMgr->setAnm(PlayerAnmID::goal_hangflag_st);
            }
            else
            {
                mDemoSubAction = 6;
            }
        }
        if (isStatus(cStatus_217))
        {
            offStatus(cStatus_217);
            mpModelBaseMgr->setAnm(PlayerAnmID::goal_pose, 1.0f, 5.0f, 0.0f);
        }
        if (isStatus(cStatus_218))
        {
            setDemoGoalMode(cDemoGoalAction_MultiJump, 0);
        }
        break;
    case 5: // Hang flag start wait
        if (mpModelBaseMgr->isAnmStop())
            mDemoSubAction = 6;
        break;
    case 6: // Hang flag
        mDemoSubAction = 7;
        mpModelBaseMgr->reset();
        mpModelBaseMgr->setAnm(PlayerAnmID::goal_hangflag);
        PlayerDemoMgr::instance()->onHangFlag();
        // fallthrough
    case 7: // Hang flag wait
        if (mpModelBaseMgr->checkFrame(7.0f))
            PlayerDemoMgr::instance()->offHangFlag();
        if (mpModelBaseMgr->isAnmStop())
        {
            PlayerDemoMgr::instance()->offUnkGoalFlag3();
            mDemoSubAction = 4;
            offStatus(cStatus_216);
        }
        break;
    }
}

f32 PlayerBase::getDemoGoalLandPos()
{
    f32 pos = mGoalBaseLandPos + PlayerDemoMgr::instance()->getGoalDemoNum() * 16.0f;
    if (PlayerDemoMgr::instance()->getGoalDemoNum() > 1)
        pos -= mGoalDemoOrder * 32.0f;
    return pos;
}

#define GOAL_JUMP_GRAVITY -0.28f
#define GOAL_JUMP_MAX_FALL_SPEED -4.0f

s32 PlayerBase::calcGoalLandNumFrame(f32 pos, f32 land_pos, f32 jump_speed)
{
    s32 num = 0;
    while (true)
    {
        jump_speed += GOAL_JUMP_GRAVITY;
        if (jump_speed < GOAL_JUMP_MAX_FALL_SPEED)
            jump_speed = GOAL_JUMP_MAX_FALL_SPEED;
        pos += jump_speed;
        if (jump_speed < 0.0f && pos <= land_pos)
            break;
        num++;
    }
    return num;
}

void PlayerBase::initGoalJump_(const sead::Vector3f& land_pos, f32 jump_speed)
{
    s32 frame_num = calcGoalLandNumFrame(mPos.y, land_pos.y, jump_speed);
    mGoalLandPos = land_pos;
    mGoalLandTimer = frame_num;
    mSpeed.y = jump_speed;
    mAccelY = GOAL_JUMP_GRAVITY;
}

void PlayerBase::initGoalMultiJump()
{
    sead::Vector3f land_pos(
        getDemoGoalLandPos(),
        mPos.y,
        mPos.z
    );
    BgCollisionCheckResultArea res;
    if (mBgCheckPlayer.checkGround(land_pos, 256.0f, &res))
        land_pos.y = res.hit_pos.y;

    f32 jump_speed = cJumpSpeed + 1.3f;
    if (PlayerDemoMgr::instance()->getGoalDemoNum() > 1)
        jump_speed = cJumpSpeed + 1.5f;

    initGoalJump_(land_pos, jump_speed);
}

bool PlayerBase::calcGoalJump()
{
    if (mGoalLandTimer != 0)
    {
        sead::Mathf::chase(&mPos.x, mGoalLandPos.x, (mGoalLandPos.x - mPos.x) / mGoalLandTimer);
        mGoalLandTimer--;
    }
    mAccelY = GOAL_JUMP_GRAVITY;
    mSpeed.y = sead::Mathf::clampMin(mSpeed.y + mAccelY, GOAL_JUMP_MAX_FALL_SPEED);
    mPos.y += mSpeed.y;
    if (mSpeed.y < 0.0f && isNowBgCross(cBgCross_IsFoot))
    {
        mPos = mGoalLandPos;
        return true;
    }
    return false;
}

void PlayerBase::executeDemoGoal_MultiJump()
{
    switch (mDemoSubAction)
    {
    default:
        break;
    case 0:
        offStatus(cStatus_247);
        mAngle.y() = sead::Mathi::cQuarterRoundIdx;
        mDemoSubAction = 1;
        mpModelBaseMgr->setAnm(PlayerAnmID::goal_jump);
        initGoalMultiJump();
        break;
    case 1:
        if (calcGoalJump())
        {
            mDemoSubAction = 2;
            mpModelBaseMgr->setAnm(PlayerAnmID::goal_jump_ed);
            setLandJumpEffect();
        }
        break;
    case 2:
        if (mpModelBaseMgr->isAnmStop())
        {
            mpModelBaseMgr->setAnm(PlayerAnmID::stamp);
            mDemoSubAction = 3;
            mDemoActionTimer = 5;
        }
        break;
    case 3:
        if (mDemoActionTimer == 0)
        {
            onStatus(cStatus_219);
            mDemoSubAction = 4;
        }
        break;
    case 4:
        if (PlayerDemoMgr::instance()->isUnkGoalFlag7() && addCalcAngleY(0, cAddCalcAngleYFrameNum_Default) == 0)
        {
            mDemoActionTimer = 7;
            mDemoSubAction = 5;
        }
        break;
    case 5:
        if (mDemoActionTimer == 0)
        {
            onStatus(cStatus_220);
            setDemoGoalMode(cDemoGoalAction_Wait, 0);
        }
        break;
    }
}

void PlayerBase::initDemoKimePose()
{
    onStatus(cStatus_222);
    onStatus(cStatus_223);
    _2148 = 0;
}

void PlayerBase::executeDemoGoal_Wait()
{
    if (isStatus(cStatus_221))
    {
        offStatus(cStatus_221);
        setDemoGoalMode(cDemoGoalAction_KimePose, 0);
        initDemoKimePose();
    }

    if (isStatus(cStatus_224))
    {
        s32 next_action = PlayerDemoMgr::instance()->isGoalDemoItem() ? cDemoGoalAction_Item : cDemoGoalAction_PreRun;
        setDemoGoalMode(next_action, 0);
    }
}

void PlayerBase::executeDemoGoal_KimePose()
{
    if (execDemoKimePose(cCourseClearType_Normal))
        setDemoGoalMode(cDemoGoalAction_Wait, 0);
}

void PlayerBase::executeState_DemoGoal()
{
    switch (mDemoAction)
    {
    case cDemoGoalAction_Pole:
        executeDemoGoal_Pole();
        break;
    case cDemoGoalAction_MultiJump:
        executeDemoGoal_MultiJump();
        break;
    case cDemoGoalAction_Wait:
        executeDemoGoal_Wait();
        break;
    case cDemoGoalAction_KimePose:
        executeDemoGoal_KimePose();
        break;
    case cDemoGoalAction_RideOffJump:
        executeDemoGoal_RideOffJump();
        break;
    case cDemoGoalAction_Run:
        executeDemoGoal_Run();
        break;
    case cDemoGoalAction_PreRun:
        executeDemoGoal_PreRun();
        break;
    case cDemoGoalAction_Item:
        executeDemoGoal_Item();
        break;
    default:
        break;
    }
    bgCheck(false);
}

void PlayerBase::finalizeState_DemoGoal()
{
    offStatus(cStatus_212);
    offStatus(cStatus_213);
    offStatus(cStatus_214);
    offStatus(cStatus_215);
    offStatus(cStatus_216);
    offStatus(cStatus_218);
    offStatus(cStatus_219);
    offStatus(cStatus_220);
    offStatus(cStatus_223);
    offStatus(cStatus_224);
    offStatus(cStatus_225);
    offStatus(cStatus_226);
    offStatus(cStatus_247);
}

bool PlayerBase::isEnableGoalCollision()
{
    if (mGoalYoshiSpitOutTimer != 0)
        return false;

    if (isStatus(cStatus_122))
        return false;

    return true;
}

bool PlayerBase::isEnableGoal()
{
    if (!isEnableGoalCollision())
        return false;

    if (isDisableGoalDemo())
        return false;

    return true;
}

#define GOAL_POLE_MAX_HEIGHT 136.0f

s32 PlayerBase::calcGoalBonusCoinNum()
{
    return CoinBattleScoreMgr::instance()->calcGoalBonusCoinNum(mGoalPoleHeight / GOAL_POLE_MAX_HEIGHT);
}

bool PlayerBase::isGoalRingLand()
{
    if (isStatus(cStatus_84))
        return true;

    if (isBossDemoLand())
        return true;

    return false;
}

void PlayerBase::setGoalDemoBase(const sead::Vector2f& pos, f32 walk_target_pos_x, bool secret_exit)
{
    if (isDisableGoalDemo())
        return;

    if (PlayerDemoMgr::instance()->isUnkGoalFlag6())
        return;

    onDemoType(cDemoType_5);

    PlayerDemoMgr::instance()->setGoalPos(pos);
    PlayerDemoMgr::instance()->setGoalWalkTargetPosX(walk_target_pos_x);
    mPos.x = pos.x;

    changeState(StateID_None, 0);
    changeDemoState(StateID_DemoGoal, 0);

    f32 height = mPos.y - pos.y;
    if (height < 0.0f)
        height = 0.0f;
    else if (height > GOAL_POLE_MAX_HEIGHT)
        height = GOAL_POLE_MAX_HEIGHT;
    mGoalPoleHeight = height;

    s32 bonus_coin_num = calcGoalBonusCoinNum();
    CoinBattleScoreMgr::instance()->incCoin(bonus_coin_num, mPlayerNo);

    mGoalBaseLandPos = pos.x + 80.0f;

    mGoalDemoNo = PlayerDemoMgr::instance()->setGoalDemoList(mPlayerNo);
    if (mGoalDemoNo ==  0)
    {
        CourseTimer::instance()->onFreezeFrame();
        CourseTask::instance()->getGamescene()->vf3C();
        PlayerDemoMgr::instance()->setDemoMode(PlayerDemoMgr::cMode_Goal);
        PlayerDemoMgr::instance()->setCourseOutPlayerNo(mPlayerNo);
        PlayerDemoMgr::instance()->setSecretExit(secret_exit);

        sead::Vector3f hanabi_pos(
            walk_target_pos_x - 112.0f,
            pos.y + 122.0f,
            4500.0f
        );
        BgCollisionCheckResultArea res;
        if (mBgCheckPlayer.checkGround(hanabi_pos, 128.0f, &res))
            hanabi_pos.y = res.hit_pos.y + 112.0f;
        PlayerDemoMgr::instance()->setHanabiPos(hanabi_pos);
    }
    if (PlayerMgr::instance()->getNumInGame() == mGoalDemoNo + 1)
    {
        if (mGoalDemoNo != 0)
            GameAudio::setClapSE();
        PlayerDemoMgr::instance()->stopBgmGoalDemo();
    }
}

void PlayerBase::vf534()
{
    onStatus(cStatus_227);
    mPlayerKey.onStatus(PlayerKey::cStatus_NoInput);
}

bool PlayerBase::setHideNotGoalPlayerBase()
{
    if (!isStatus(cStatus_212))
    {
        if (!isStatus(cStatus_280))
        {
            mSpeedF = 0.0f;
            mSpeed.y = 0.0f;
            setFallAction();
        }
        vf534();
        return true;
    }
    return false;
}

void PlayerBase::startGoalDemoVoice(CourseClearType course_clear_type)
{
    s32 demo_num =
        course_clear_type == cCourseClearType_Normal
            ? PlayerDemoMgr::instance()->getGoalDemoNum()
            : PlayerDemoMgr::instance()->getControlDemoPlayerNum();

    if (MainGame::instance()->isOtehon())
    {
        if (demo_num >= 2)
            startVoiceSound(CLEAR_MULTI);
        else
            startVoiceSound(CLEAR_HELPED);
    }
    else
    {
        if (course_clear_type == cCourseClearType_LastBoss)
            startVoiceSound(CLEAR_LAST_BOSS);
        else
        {
            if (demo_num >= 2)
                startVoiceSound(CLEAR_MULTI);
            else
            {
                if (course_clear_type == cCourseClearType_Normal)
                {
                    if (PlayerDemoMgr::instance()->isNormalExit())
                        startVoiceSound(CLEAR_NORMAL);
                    else
                        startVoiceSound(CLEAR_ANOTHER);
                }
                else
                {
                    startVoiceSound(CLEAR_BOSS);
                }
            }
        }
    }
}

bool PlayerBase::vf51C_Base(u32)
{
    onStatus(cStatus_188);
    setFallAction();
    f32 speed = mSpeedF;
    if (speed < -1.5f)
        speed = -1.5f;
    else if (speed > 1.5f)
        speed = 1.5f;
    mSpeedF = speed;
    mAccelF = 0.0f;
    mMaxSpeedF = 0.0f;
    return startControlDemo(false);
}
