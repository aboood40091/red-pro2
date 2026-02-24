#include <collision/ActorBoxBgCollision.h>
#include <collision/BgCollisionCheckResult.h>
#include <event/EventDemoNextGotoBlock.h>
#include <event/EventMgr.h>
#include <game/BalloonMgr.h>
#include <game/CourseTask.h>
#include <game/SubjectMgr.h>
#include <game_info/CourseInfo.h>
#include <map/CourseData.h>
#include <map/Next.h>
#include <map_obj/MaskMgr.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerModelBaseMgr.h>
#include <player/PlayerObject.h>
#include <scroll/BgScrollMgr.h>
#include <system/MainGame.h>
#include <utility/Mtx.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

#define GLOBAL_FLOAT_TYPE(NAME, VALUE)  \
    namespace {                         \
                                        \
    struct NAME                         \
    {                                   \
        f32 value;                      \
                                        \
        NAME()                          \
            : value(VALUE)              \
        {                               \
        }                               \
    };                                  \
                                        \
    }                                   \
    static const NAME c##NAME;

GLOBAL_FLOAT_TYPE(DokanUDCheckMaxDistance, 12.0f)
GLOBAL_FLOAT_TYPE(DokanUDMameCheckMinDistance, 6.0f);

void PlayerBase::stopOutDokanOther()
{
    if (mDokanType == cDokanType_Normal && PlayerMgr::instance()->isEnableStopOutDokanOther(mPlayerNo))
    {
        PlayerDemoMgr::instance()->stopOther();
        BalloonMgr::instance()->onDemo();
    }
}

void PlayerBase::initDemoOutDokanUD(DokanDir dir)
{
    mDokanDir = dir;
    changeState(StateID_Walk, cAnmBlend_Disable);
    setDokanWaitAnm(true);
    if (mDokanType == cDokanType_ForwardPipe)
    {
        if (dir == cDokanDir_ButtonUp)
            mDokanMoveYOffset = 0.0f;
        else
            mDokanMoveYOffset = -34.0f;
    }
    else
    {
        if (dir == cDokanDir_ButtonUp)
            mDokanMoveYOffset = 2.0f;
        else
        {
            if (mActorType == cActorType_Yoshi)
                mDokanMoveYOffset = -16.0f;
            else
                mDokanMoveYOffset = -10.0f;
        }
    }
    mDokanMoveXThreshold = 0.0f;
    initDemoOutDokan();
    stopOutDokanOther();
}

void PlayerBase::initializeState_DemoOutDokanU()
{
    initDemoOutDokanUD(cDokanDir_ButtonUp);
}

bool PlayerBase::demo_dokan_move_x(f32 step, f32 threshold)
{
    sead::Mathf::chase(&mPos.x, mDokanPos.x, step);
    return sead::Mathf::abs(mPos.x - mDokanPos.x) <= threshold;
}

void PlayerBase::setDokanSE()
{
    startSound(
        isNowBgCross(cBgCross_IsUnderwater)
            ? "SE_PLY_WATER_DOKAN_IN_OUT"
            : "SE_PLY_DOKAN_IN_OUT"
    );
}

bool PlayerBase::demo_dokan_move_y(f32 step, f32 offset)
{
    return sead::Mathf::chase(&mPos.y, mDokanPos.y + offset, step);
}

void PlayerBase::executeDemoOutDokanUD()
{
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoOutDokanAction_MoveSubAxis:
        {
            bool facing_correct_dir = true;
            if (!setOutDokanAngle())
                facing_correct_dir = false;
            if (demo_dokan_move_x(1.0f, mDokanMoveXThreshold) && facing_correct_dir)
            {
                mDemoAction = cDemoOutDokanAction_MoveMainAxis;
                resetLight();
                setDokanSE();
                mDemoActionTimer = 180;
            }
        }
        break;
    case cDemoOutDokanAction_MoveMainAxis:
        {
            if (demo_dokan_move_y(0.75f, mDokanMoveYOffset))
            {
                if (mDemoActionTimer != 0)
                {
                    PlayerMask& mask = MaskMgr::instance()->getPlayerMask(mPlayerNo);
                    if (mask.getCaveMaskDiameter() != 0.0f)
                        return;
                }
                if (CourseTask::instance()->getGamesceneUnkBool())
                    return;
                switch (mDokanType)
                {
                case cDokanType_ForwardPipe:
                    // Stripped code?
                    break;
                default:
                    changeNextScene(1);
                    mDemoAction = cDemoOutDokanAction_End;
                    break;
                }
            }
        }
        break;
    case cDemoOutDokanAction_End:
        break;
    }
}

void PlayerBase::executeState_DemoOutDokanU()
{
    executeDemoOutDokanUD();
}

void PlayerBase::endDemoOutDokan()
{
    offStatus(cStatus_NoPropelRoll);
    offStatus(cStatus_210);
    offStatus(cStatus_FaderPosSet);
    offStatus(cStatus_133);
}

void PlayerBase::finalizeState_DemoOutDokanU()
{
    endDemoOutDokan();
}

void PlayerBase::initializeState_DemoOutDokanD()
{
    initDemoOutDokanUD(cDokanDir_ButtonDown);
}

void PlayerBase::executeState_DemoOutDokanD()
{
    executeDemoOutDokanUD();
}

void PlayerBase::finalizeState_DemoOutDokanD()
{
    endDemoOutDokan();
}

void PlayerBase::initDemoOutDokanLR(DokanDir dir)
{
    mDokanDir = dir;
    mIsDokanSwim = false;
    if (isStatus(cStatus_Swim))
    {
        if (!isCarry())
            mIsDokanSwim = true;
    }
    bool adjust_pos = false;
    if (mIsDokanSwim)
    {
        mpModelBaseMgr->setAnm(PlayerAnmID::swim_pipe);
        adjust_pos = true;
    }
    else
    {
        mpModelBaseMgr->setAnm(PlayerAnmID::low_walk_start);
    }
    if (adjust_pos || isTotten())
    {
        if (dir == cDokanDir_ButtonRight)
            mDokanPos.x += 8.0f;
        else
            mDokanPos.x -= 8.0f;
    }
    onStatus(cStatus_NoPropelRoll);
    initDemoOutDokan();
    stopOutDokanOther();
}

void PlayerBase::initializeState_DemoOutDokanR()
{
    initDemoOutDokanLR(cDokanDir_ButtonRight);
}

f32 PlayerBase::getWaterDokanCenterOffset(f32 pos_y)
{
    f32 character_center_offset = 16.0f;
    if (mActorType == cActorType_Player && sead::DynamicCast<PlayerObject>(this) != nullptr)
    {
        static const f32 c_character_center_offset_table[cPlayerCharacter_NumStory] = {
            12.0f,  // Mario
            15.0f,  // Luigi
            13.0f,  // Yellow Toad
            13.0f,  // Blue Toad
            // They did not set the value for Nabbit here...
        };
        character_center_offset = c_character_center_offset_table[mCharacter];
    }
    f32 center_offset = sead::Mathf::clampMax(getCenterY() - mPos.y, character_center_offset);
    return (pos_y + 16.0f) - center_offset;
}

void PlayerBase::executeDemoOutDokanLR()
{
    f32 water_dokan_center_offset = 0.0f;
    if (!mIsDokanSwim)
    {
        if (mpModelBaseMgr->isAnmStop())
            mpModelBaseMgr->setAnm(PlayerAnmID::low_walk);
    }
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoOutDokanAction_MoveSubAxis:
        {
            Angle angle = getMukiAngle();
            if (addCalcAngleY(angle, cAddCalcAngleYFrameNum_Default) == 0)
            {
                if (mIsDokanSwim)
                    water_dokan_center_offset = getWaterDokanCenterOffset(mDokanPos.y) - mDokanPos.y;
                if (demo_dokan_move_y(0.75f, water_dokan_center_offset))
                {
                    mDemoAction = cDemoOutDokanAction_MoveMainAxis;
                    resetLight();
                    setDokanSE();
                }
            }
        }
        break;
    case cDemoOutDokanAction_MoveMainAxis:
        {
            if (demo_dokan_move_x(0.75f, 0.0f))
            {
                switch (mDokanType)
                {
                case cDokanType_ForwardPipe:
                    // Stripped code?
                    break;
                default:
                    changeNextScene(1);
                    mDemoAction = cDemoOutDokanAction_End;
                    break;
                }
            }
        }
        break;
    case cDemoOutDokanAction_End:
        break;
    }
}

void PlayerBase::executeState_DemoOutDokanR()
{
    executeDemoOutDokanLR();
}

void PlayerBase::finalizeState_DemoOutDokanR()
{
    endDemoOutDokan();
}

void PlayerBase::initializeState_DemoOutDokanL()
{
    initDemoOutDokanLR(cDokanDir_ButtonLeft);
}

void PlayerBase::executeState_DemoOutDokanL()
{
    executeDemoOutDokanLR();
}

void PlayerBase::finalizeState_DemoOutDokanL()
{
    endDemoOutDokan();
}

void PlayerBase::initDemoOutDokanRoll()
{
    mDokanPosMoveDelta.set(0.0f, 0.0f);
    mDokanType = cDokanType_Normal;
    switch (mDokanDir)
    {
    default:
        break;
    case cDokanDir_ButtonUp:
        mDokanPos.set(
            mDokanFaderPos.x,
            mDokanFaderPos.y,
            mPos.z
        );
        break;
    case cDokanDir_ButtonDown:
        mDokanPos.set(
            mDokanFaderPos.x,
            mPos.y,
            mPos.z
        );
        break;
    case cDokanDir_ButtonLeft:
        mDokanPos.set(
            mDokanFaderPos.x - 16.0f,
            mPos.y,
            mPos.z
        );
        break;
    case cDokanDir_ButtonRight:
        mDokanPos.set(
            mDokanFaderPos.x + 16.0f,
            mPos.y,
            mPos.z
        );
        break;
    }
}

void PlayerBase::calcDokanMoveDiff(sead::Vector2f* p_diff)
{
    mpDokanBgCollision->entryBcFoot(&mBgCheckPlayer);

    const sead::Vector2f& diff = mpDokanBgCollision->addDokanMoveDiff(mDokanPos);

    mDokanPos.x += diff.x;
    mDokanPos.y += diff.y;

    if (p_diff != NULL)
        *p_diff = diff;
}

void PlayerBase::initializeState_DemoOutDokanRollUD()
{
    initDemoOutDokanUD(mDokanDir);
    initDemoOutDokanRoll();
    calcDokanMoveDiff();
}

void PlayerBase::executeState_DemoOutDokanRollUD()
{
    calcDokanMoveDiff();
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoOutDokanAction_MoveSubAxis:
        {
            bool facing_correct_dir = true;
            if (!setOutDokanAngle())
                facing_correct_dir = false;
            sead::Vector3f delta = mDokanPos - mPos;
            if (delta.length() > 1.0f)
            {
                delta.normalize();
                mPos += delta * 1.0f;
            }
            else
            {
                mPos = mDokanPos;
                if (facing_correct_dir)
                {
                    mDemoAction = cDemoOutDokanAction_MoveMainAxis;
                    resetLight();
                    setDokanSE();
                }
            }
        }
        break;
    case cDemoOutDokanAction_MoveMainAxis:
        {
            if (mDokanDir == cDokanDir_ButtonUp)
            {
                Angle angle = mpDokanBgCollision->getAngle();
                if (mDirection == cDirType_Left)
                    angle = -angle;
                mAngle.x().addCalcAngle(angle, 1.0f / 4, 0x10000000, 0x01000000);
            }
            f32 move_delta_y = 0.0f;
            if (mDokanDir == cDokanDir_ButtonUp)
                move_delta_y = mDokanMoveYOffset + -32.0f;
            else if (mDokanDir == cDokanDir_ButtonDown)
                move_delta_y = -34.0f;
            bool is_move_end = sead::Mathf::chase(&mDokanPosMoveDelta.y, move_delta_y, 0.75f);
            Mtxf mtx;
            mtx.makeT(mDokanPos.x, mDokanPos.y, mPos.z);
            mtx.ZrotM(mpDokanBgCollision->getAngle());
            mtx.multTranslationLocal(sead::Vector3f(0.0f, mDokanPosMoveDelta.y, 0.0f));
            mtx.getTranslation(mPos);
            if (is_move_end)
            {
                changeNextScene(1);
                mDemoAction = cDemoOutDokanAction_End;
                onStatus(cStatus_Invisible);
            }
        }
        break;
    case cDemoOutDokanAction_End:
        break;
    }
}

void PlayerBase::finalizeState_DemoOutDokanRollUD()
{
    endDemoOutDokan();
}

void PlayerBase::initializeState_DemoOutDokanRollLR()
{
    initDemoOutDokanLR(mDokanDir);
    initDemoOutDokanRoll();
    sead::Vector2f diff;
    calcDokanMoveDiff(&diff);
    getPos2D() += diff;
}

void PlayerBase::executeState_DemoOutDokanRollLR()
{
    sead::Vector2f diff;
    calcDokanMoveDiff(&diff);
    getPos2D() += diff;
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoOutDokanAction_MoveSubAxis:
        {
            Angle angle = getMukiAngle();
            if (addCalcAngleY(angle, cAddCalcAngleYFrameNum_Default) == 0)
            {
                if (demo_dokan_move_y(0.75f, 0.0f))
                {
                    mDemoAction = cDemoOutDokanAction_MoveMainAxis;
                    resetLight();
                    setDokanSE();
                }
            }
        }
        break;
    case cDemoOutDokanAction_MoveMainAxis:
        {
            if (demo_dokan_move_x(0.75f, 0.0f))
            {
                changeNextScene(1);
                mDemoAction = cDemoOutDokanAction_End;
                onStatus(cStatus_Invisible);
            }
        }
        break;
    case cDemoOutDokanAction_End:
        break;
    }
}

void PlayerBase::finalizeState_DemoOutDokanRollLR()
{
    endDemoOutDokan();
}

void PlayerBase::initDemoInDokanUD_(DokanDir dir)
{
    setDokanWaitAnm(false);
    mDokanFaderPos = mPos;
    onStatus(cStatus_NoPropelRoll);
    if (dir == cDokanDir_FaceUp)
    {
        if (mChangeDemoStateParam == 2)
            mDokanFaderPos.y += 16.0f;
        else
            mDokanFaderPos.y += 32.0f;
        mDokanPos = mDokanFaderPos;
    }
    else
    {
        mDokanPos.set(mPos.x, mPos.y - vf584(), mPos.z);
        mPos.y += 2.0f;
    }
    mAngle.y() = getMukiAngle();
    initDemoInDokan(dir);
}

void PlayerBase::initializeState_DemoInDokanU()
{
    initDemoInDokanUD_(cDokanDir_ButtonUp);
}

bool PlayerBase::dokanMoveOut()
{
    onStatus(cStatus_265);

    if (isStatus(cStatus_NoPropelRoll) && (mDokanDir == cDokanDir_ButtonLeft || mDokanDir == cDokanDir_ButtonRight) && sead::Mathf::abs(mPos.x - mDokanPos.x) <= 20.0f)
        offStatus(cStatus_NoPropelRoll);

    if (isStatus(cStatus_133) && sead::Mathf::abs(mPos.x - mDokanPos.x) <= 20.0f && sead::Mathf::abs(mPos.y - mDokanPos.y) <= 20.0f)
        offStatus(cStatus_133);

    if (demo_dokan_move_x(0.75f, 0.0f) &&
        demo_dokan_move_y(0.75f, 0.0f))
    {
        return true;
    }
    return false;
}

void PlayerBase::executeDemoInDokan()
{
    switch (mDemoAction)
    {
    default:
        break;
    case cDemoInDokanAction_CheckTurn:
        if (PlayerDemoMgr::instance()->checkDemoNo(&mPlayerNo))
        {
            offStatus(cStatus_Invisible);
            if (PlayerDemoMgr::instance()->isUnderwaterKoopaJrDemo())
            {
                mDemoAction = cDemoInDokanAction_WaitNextTurn_UnderwaterKoopaJrDemo;
                if (PlayerDemoMgr::instance()->getCourseOutPlayerNo() == mPlayerNo)
                    mDemoActionTimer = 0;
                else
                    mDemoActionTimer = 10;
            }
            else
            {
                mDemoAction = cDemoInDokanAction_WaitNextTurn;
                mDemoActionTimer = 40;
            }
            if (ActorBgCollisionCheck::checkWater(nullptr, mDokanPos, mLayer))
                onNowBgCross(cBgCross_IsUnderwater);
            if (isNowBgCross(cBgCross_IsUnderwater))
            {
                if (*mDemoStateMgr.getStateID() == StateID_DemoOutDokanL || // Typo by Nintendo!!! Should be "StateID_DemoInDokanL"
                    *mDemoStateMgr.getStateID() == StateID_DemoOutDokanR)   // Typo by Nintendo!!! Should be "StateID_DemoInDokanR"
                {
                    mpModelBaseMgr->setAnm(PlayerAnmID::swim_pipe);
                    if (mChangeDemoStateParam != 1)
                    {
                        mPos.y = getWaterDokanCenterOffset(mPos.y);
                        mDokanPos.y = mPos.y;
                    }
                }
            }
            setDokanSE();
        }
        break;
    case cDemoInDokanAction_WaitNextTurn:
        if (mDemoActionTimer == 0)
        {
            PlayerDemoMgr::instance()->turnNextDemoNo();
            mDemoAction = cDemoInDokanAction_Move;
        }
        if (dokanMoveOut())
        {
            PlayerDemoMgr::instance()->turnNextDemoNo();
            mDemoAction = cDemoInDokanAction_End;
        }
        break;
    case cDemoInDokanAction_Move:
        if (dokanMoveOut())
            mDemoAction = cDemoInDokanAction_End;
        break;
    case cDemoInDokanAction_WaitNextTurn_UnderwaterKoopaJrDemo:
        if (mDemoActionTimer == 0 && dokanMoveOut())
        {
            PlayerDemoMgr::instance()->turnNextDemoNo();
            mDemoAction = cDemoInDokanAction_End;
        }
        break;
    case cDemoInDokanAction_End:
        {
            bool facing_correct_dir = true;
            if (!mPlayerKey.buttonWalk())
            {
                Angle angle = getMukiAngle();
                if (!mAngle.y().chaseRest(angle, 0x08000000))
                    facing_correct_dir = false;
            }
            if (facing_correct_dir)
            {
                changeNormalAction();
                if (isNowBgCross(cBgCross_IsUnderwater))
                    onOldBgCross(cBgCross_IsUnderwater);
            }
        }
        break;
    }
}

void PlayerBase::executeState_DemoInDokanU()
{
    executeDemoInDokan();
}

void PlayerBase::endDemoInDokan()
{
    offStatus(cStatus_NoPropelRoll);
    offStatus(cStatus_210);
    offStatus(cStatus_FaderPosSet);
    offStatus(cStatus_CanWaterWalk);
    mInvincibilityTimer = 0;
    _2060 = 0;
    offStatus(cStatus_133);

    if (mIsLastPlayer)
        BgScrollMgr::instance()->postDemoIn();
}

void PlayerBase::finalizeState_DemoInDokanU()
{
    endDemoInDokan();
}

void PlayerBase::initializeState_DemoInDokanD()
{
    initDemoInDokanUD_(cDokanDir_ButtonDown);
}

void PlayerBase::executeState_DemoInDokanD()
{
    executeDemoInDokan();
}

void PlayerBase::finalizeState_DemoInDokanD()
{
    endDemoInDokan();
}

void PlayerBase::initDemoInDokanLR(DokanDir dir)
{
    mpModelBaseMgr->setAnm(PlayerAnmID::low_walk);
    onStatus(cStatus_NoPropelRoll);
    mDirection = (dir == cDokanDir_FaceLeft) ? cDirType_Left : cDirType_Right;
    mAngle.y() = getMukiAngle();
    initDemoInDokan(dir);
}

void PlayerBase::initializeState_DemoInDokanR()
{
    initDemoInDokanLR(cDokanDir_ButtonRight);
}

void PlayerBase::executeState_DemoInDokanR()
{
    executeDemoInDokan();
}

void PlayerBase::finalizeState_DemoInDokanR()
{
    endDemoInDokan();
}

void PlayerBase::initializeState_DemoInDokanL()
{
    initDemoInDokanLR(cDokanDir_ButtonLeft);
}

void PlayerBase::executeState_DemoInDokanL()
{
    executeDemoInDokan();
}

void PlayerBase::finalizeState_DemoInDokanL()
{
    endDemoInDokan();
}

bool PlayerBase::setDokanInNextGoto(s32 dst_next_goto_no)
{
    mDstNextGotoID = dst_next_goto_no;
    u8 file_no = CourseInfo::instance()->getFileNo();
    const NextGoto* p_next_goto = CourseData::instance()->getFile(file_no)->getNextGoto(mDstNextGotoID);
    mDokanType = cDokanType_Normal;
    if ((p_next_goto->flag & (1 << 1)) != 0)
        mDokanType = cDokanType_ForwardPipe;
    switch (mDokanType)
    {
    default:
        break;
    case cDokanType_Normal:
        if (!(Next::instance()->isDifferentChangeSceneNextDat(file_no, mDstNextGotoID) ||
              sead::DynamicCast<EventDemoNextGotoBlock>(EventMgr::instance()->getCurrentEvent()) != nullptr))
        {
            return true;
        }
        break;
    case cDokanType_ForwardPipe:
        // Stripped code?
        return true;
    }
    return false;
}

void PlayerBase::setObjDokanIn(ActorBoxBgCollision* p_bg_collision, const sead::Vector3f& pos, s32 dst_next_goto_no, DokanDir dir)
{
    mpDokanBgCollision = p_bg_collision;
    mDokanFaderPos = pos;
    mDokanDir = dir;
    if (setDokanInNextGoto(dst_next_goto_no))
    {
        Next::instance()->setChangeSceneNextDat(
            CourseInfo::instance()->getFileNo(),
            mDstNextGotoID
        );
        static const StateID* cDokanInActionRoll[] = {
            &StateID_DemoOutDokanRollUD,
            &StateID_DemoOutDokanRollUD,
            &StateID_DemoOutDokanRollLR,
            &StateID_DemoOutDokanRollLR,
        };
        if (u32(mDokanDir) <= cDokanDir_ButtonRight)
            changeDemoState(*cDokanInActionRoll[u32(mDokanDir)], 0);
    }
}

PlayerBase::CheckBgDokanInUDRes PlayerBase::checkBgDokanInUD(sead::Vector3f* p_pos, DokanDir dir)
{
    f32 check_y = 0.0f;
    switch (dir)
    {
    case cDokanDir_ButtonUp:
        check_y = -6.0f;
        break;
    case cDokanDir_ButtonDown:
        check_y = 6.0f;
        break;
    }

    f32 check_x = 8.0f;

    const sead::Vector3f& d = mPos - *p_pos;
    if (d.x > 0.0f)
        check_x = -check_x;

    const sead::Vector2f p0(
        p_pos->x - check_x,
        p_pos->y + check_y
    );
    const sead::Vector2f p1(
        p_pos->x + check_x,
        p0.y
    );

    mBgCheckPlayer.initBgCheck();
    BgCollisionCheckResultArea res;
    if (mBgCheckPlayer.getBgCheck().checkArea(&res, p0, p1))
    {
        f32 distance = res.hit_pos.distance(p0);
        if (distance < cDokanUDCheckMaxDistance.value)
        {
            if (mMode == cPlayerMode_Mini && distance > cDokanUDMameCheckMinDistance.value)
            {
                if (p_pos->x < mPos.x)
                    p_pos->x += 3.0f;
                else
                    p_pos->x -= 3.0f;
                return cCheckBgDokanInUDRes_ClearMame;
            }
            else
            {
                return cCheckBgDokanInUDRes_Blocked;
            }
        }
    }

    return cCheckBgDokanInUDRes_Clear;
}

void PlayerBase::getDokanInLRWallBgPointData(ActorBgCollisionCheck::Sensor* p_sensor)
{
    ActorBgCollisionCheck::Sensor tmp_sensor;
    getDokanWallBgPointData(&tmp_sensor);
    if (mDirection == cDirType_Left)
        tmp_sensor.center_offset = -tmp_sensor.center_offset;
    const ActorBgCollisionCheck::Sensor* p_effective_sensor = mBgCheckPlayer.getSensorEffective(mDirection);
    if (p_effective_sensor != nullptr)
        tmp_sensor.center_offset = p_effective_sensor->center_offset;
    *p_sensor = tmp_sensor;
}

bool PlayerBase::checkButtonDokanIn(DokanDir dir)
{
    if (isStatus(cStatus_IgnoreBgCross))
        return false;

    if (!isStatus(cStatus_EnableDokanIn))
        return false;

    s32 dokan_in_lr_target = isStatus(cStatus_37) ? 1 : 10;
    switch (dir)
    {
    default:
        break;
    case cDokanDir_FaceUp:
        if (mPlayerKey.buttonDown() || isStatus(cStatus_38))
            return true;
        break;
    case cDokanDir_FaceDown:
        if (mPlayerKey.buttonUp() || isStatus(cStatus_37))
            return true;
        break;
    case cDokanDir_FaceLeft:
        if (mDirection == cDirType_Right && mDokanInTimerR >= dokan_in_lr_target)
            return true;
        break;
    case cDokanDir_FaceRight:
        if (mDirection == cDirType_Left && mDokanInTimerL >= dokan_in_lr_target)
            return true;
        break;
    }
    return false;
}

bool PlayerBase::isEnableDokanInStatusBase()
{
    if (MainGame::instance()->isShadowkunQuest() || SubjectMgr::instance()->isDisableAreaExit())
        return false;

    if (isDisableDokanInDemo())
        return false;

    if (isStatus(cStatus_DispOut) || isStatus(cStatus_Quake) || isStatus(cStatus_RideBalloon))
        return false;

    return true;
}

bool PlayerBase::checkBgDokanIn(sead::Vector3f* p_pos, s32* p_dst_next_goto_no, DokanDir dir)
{
    switch (dir)
    {
    default:
        break;
    case cDokanDir_FaceUp:
        if (mBgCheckPlayer.checkDokanDown(p_pos, p_dst_next_goto_no))
        {
            if (mBgCheckPlayer.isMameDokan())
            {
                if (isEnableMameDokanIn())
                    return true;
            }
            else
            {
                if (checkBgDokanInUD(p_pos, cDokanDir_FaceUp) != cCheckBgDokanInUDRes_Blocked)
                    return true;
            }
        }
        break;
    case cDokanDir_FaceDown:
        if (mBgCheckPlayer.checkDokanUp(p_pos, p_dst_next_goto_no))
        {
            p_pos->y -= 16.0f;
            if (mBgCheckPlayer.isMameDokan())
            {
                if (isEnableMameDokanIn())
                    return true;
            }
            else
            {
                if (checkBgDokanInUD(p_pos, cDokanDir_FaceDown) != cCheckBgDokanInUDRes_Blocked)
                    return true;
            }
        }
        break;
    case cDokanDir_FaceLeft:
    case cDokanDir_FaceRight:
        {
            ActorBgCollisionCheck::Sensor sensor;
            getDokanInLRWallBgPointData(&sensor);
            if (mBgCheckPlayer.checkDokanLR(p_pos, p_dst_next_goto_no, mDirection, sensor))
            {
                if (mBgCheckPlayer.isMameDokan())
                {
                    if (isEnableMameDokanIn())
                        return true;
                }
                else
                {
                    return true;
                }
            }
        }
        break;
    }
    return false;
}

void PlayerBase::setDokanInPos(sead::Vector3f pos, DokanDir dir)
{
    f32 dokan_in_lr_offset_x = 16.0f;
    switch (dir)
    {
    default:
        break;
    case cDokanDir_FaceUp:
        mDokanFaderPos = pos;
        mDokanPos = pos;
        if (mBgCheckPlayer.isMameDokan())
            mDokanPos.y -= 16.0f;
        else
            mDokanPos.y -= 32.0f;
        break;
    case cDokanDir_FaceDown:
        mDokanFaderPos = pos;
        mDokanPos = pos;
        break;
    case cDokanDir_FaceLeft:
    case cDokanDir_FaceRight:
        mDokanFaderPos = pos;
        if (mDirection == cDirType_Left)
            mDokanFaderPos.x += 16.0f;
        mDokanFaderPos.y += 16.0f;
        if (mBgCheckPlayer.isMameDokan())
            dokan_in_lr_offset_x = 8.0f;
        if (mDirection == cDirType_Left)
            dokan_in_lr_offset_x = -dokan_in_lr_offset_x;
        mDokanPos.set(
            mDokanFaderPos.x + dokan_in_lr_offset_x,
            pos.y,
            pos.z
        );
        break;
    }
}

bool PlayerBase::setDemoOutDokanAction(s32 dst_next_goto_no, DokanDir dir)
{
    if (setDokanInNextGoto(dst_next_goto_no))
    {
        static const StateID* cDokanInAction[] = {
            &StateID_DemoOutDokanU,
            &StateID_DemoOutDokanD,
            &StateID_DemoOutDokanL,
            &StateID_DemoOutDokanR,
        };
        switch (mDokanType)
        {
        default:
            break;
        case cDokanType_Normal:
            Next::instance()->setChangeSceneNextDat(
                CourseInfo::instance()->getFileNo(),
                mDstNextGotoID
            );
            changeState(StateID_None, 0);
            changeDemoState(*cDokanInAction[u32(dir)], 0);
            return true;
        case cDokanType_ForwardPipe:
            changeState(StateID_None, 0);
            changeDemoState(*cDokanInAction[u32(dir)], 0);
            return true;
        }
    }
    return false;
}

bool PlayerBase::setDokanIn(DokanDir dir)
{
    if (checkButtonDokanIn(dir))
    {
        sead::Vector3f dokan_in_pos;
        s32 dst_next_goto_no;
        if (checkBgDokanIn(&dokan_in_pos, &dst_next_goto_no, dir))
        {
            setDokanInPos(dokan_in_pos, dir);
            if (setDemoOutDokanAction(dst_next_goto_no, dir))
                return true;
        }
    }
    return false;
}

void PlayerBase::setDokanWaitAnm(bool move_in)
{
    if (move_in)
        mpModelBaseMgr->setAnm(PlayerAnmID::wait, 0.0f, 5.0f, 85.0f);
    else
        mpModelBaseMgr->setAnm(PlayerAnmID::wait);
}

void PlayerBase::initDemoOutDokanBase()
{
    onDemoType(cDemoType_3);
    mAngle.x() = 0;
    mSpeed.set(0.0f, 0.0f, 0.0f);
    mSpeedF = 0.0f;
    mMaxSpeedF = 0.0f;
    setZPosition(-1800.0f);
    onStatus(cStatus_210);
    if (!isStatus(cStatus_129))
        setFaderPos(mDokanFaderPos);
    mBgAttr = cBgAttr_Rock;
}

void PlayerBase::initDemoInDokanBase(DokanDir dir)
{
    onDemoType(cDemoType_3);
    mDokanDir = dir;
    resetLight();
    onStatus(cStatus_210);
    mSpeedF = 0.0f;
    mSpeed.y = 0.0f;
    setZPosition(-1800.0f);
    mInvincibilityTimer = mChangeDemoStateParam == 1 ? 0 : 35;
    mDemoAction = cDemoInDokanAction_CheckTurn;
    PlayerDemoMgr::instance()->setDemoMode(PlayerDemoMgr::cMode_Wait);
    setFaderPos(mDokanFaderPos);
    mBgAttr = cBgAttr_Rock;
}

f32 PlayerBase::getDokanCannonMoveXStep() const
{
    return 1.0f;
}

f32 PlayerBase::getDokanCannonMoveXThreshold() const
{
    return 0.0f;
}

f32 PlayerBase::getDokanCannonMoveYStep() const
{
    return 0.75f;
}

f32 PlayerBase::getDokanWaitAnmFixFrame() const
{
    return 85.0f;
}
