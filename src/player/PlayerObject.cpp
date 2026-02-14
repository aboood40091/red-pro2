#include <actor/ActorMgr.h>
#include <actor/Profile.h>
#include <event/EventDown.h>
#include <event/EventPlayerChange.h>
#include <game/CourseTask.h>
#include <graphics/LightType.h>
#include <input/InputMgr.h>
#include <map/LayerID.h>
#include <map_obj/BalloonChibiYoshi.h>
#include <player/PlayerHIO_Character.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <player/Yoshi.h>
#include <utility/MathUtil.h>

static const PlayerTallType cTallType[] = {
    cTallType_Small,    // cPlayerMode_Small
    cTallType_Normal,   // cPlayerMode_Normal
    cTallType_Normal,   // cPlayerMode_Fire
    cTallType_Mini,     // cPlayerMode_Mini
    cTallType_Normal,   // cPlayerMode_Propeller
    cTallType_Normal,   // cPlayerMode_Penguin
    cTallType_Normal,   // cPlayerMode_Ice
    cTallType_Normal,   // cPlayerMode_Squirrel
    cTallType_Normal,   // cPlayerMode_PSquirrel
};
static_assert(sizeof(cTallType) / sizeof(PlayerTallType) == cPlayerMode_Num);

static const ActorCreateInfo cActorCreateInfo_PlayerObject = { 0, 0, { 0, 16, 12, 16 } };
static const Profile cProfile_PlayerObject(TActorFactory<PlayerObject>, ProfileInfo::cProfileID_PlayerObject, "プレイヤーオブジェクト", &cActorCreateInfo_PlayerObject);

PlayerObject::PlayerObject(const ActorCreateParam& param)
    : PlayerBase(param)
    , mModelMgr(getParamPlayerModelType(mParam0), PlayerModelBase::cSceneType_Course, getParamPlayerNo(mParam0))
    , _2760()
    , mModePrev(cPlayerMode_Small)
    , mModeNext(cPlayerMode_Small)
    , _2774(0.0f, 0.0f)
    , mStarTimer(0)
    , mStarCnt(0)
    , mCarryActorID(0)
    , mCarryStep(cCarryStep_None)
    , mCarryStepPrev(cCarryStep_None)
    , mCarryStepTimer(0.0f)
    , mCarryStepLength(0.0f)
    , mInvalidKeyTimer()
    , mInvalidKeyTimerType()
    , _27b0()
    , _27b8()
    , _27c0(mPos)
    , _27cc(0)
    , mScrollMode(cScrollMode_1)
    , mPropelParts()
    , mLight()
    , _2998(0)
    , _299c(0)
    , _29a0(0)
    , mpEventPlayerChange(new EventPlayerChange(getParamPlayerNo(mParam0)))
    , mChangeMgr()
    , _29d0(0.0f)
    , _29d4(0)
    , mpEventDown(new EventDown(getParamPlayerNo(mParam0)))
    , _29dc(0)
    , mPlayerEatDieNow(false)
    , _29e0(0.0f, 0.0f, 0.0f)
    , mEffectScale(1.0f)
    , mDokanCannonType(cDokanCannonType_ShootUp)
    , mDemoInBossMoveTarget(0.0f, 0.0f)
    , mPMusaTransformStep(0)
    , _2a00(cDirType_Right)
    , _2a04(false)
    , _2a08(0)
    , _2a0c(0)
    , _2a10(0)
    , _2a14(0)
    , mWhichJump(0)
    , _2a1c(0)
    , _2a20(0)
    , _2a24(0)
    , _2a28(0)
    , mSpinRotStep()
    , mMissSpinAngle()
    , _2a34(0)
    , _2a38(0)
    , _2a3c(0.0f)
    , _2a40(0)
    , _2a44(0)
    , _2a48(0.0f)
    , mWallSlideDir(cDirType_Right)
    , mLiftUpActorID()
    , _2a54(0.0f)
    , mLiftUpOffsetRatio(1.0f)
    , _2a5c(0)
    , mLiftUpCounter(0)
    , mLiftUpOffsetScale(0.0f)
    , _2a68(0)
    , _2a6c(0)
    , _2a70(0)
    , _2a74(0)
    , _2a78(0)
    , _2a7c(0)
    , _2a80(0)
    , _2a84(0)
    , mBalloonHelpVoiceTimer(0)
    , mBalloonCheckAllFadeTimer(0)
    , mBalloonControllerConnectStatus(0)
    , _2a94(0)
    , _2a98(0.0f, 0.0f, 0.0f)
    , mCannonType(0)
    , _2aa8(0)
    , _2aac(0.0f, 0.0f, 0.0f)
    , _2ab8(0.0f)
    , _2abc(0.0f)
    , _2ac0(0)
    , _2ac4()
    , _2ac8(0)
    , _2acc(0)
    , _2ad0()
    , _2b38(0)
    , _2b3c(0.0f, 0.0f)
    , _2b44(0)
    , _2b48(0)
    , _2b4c(0)
    , _2b50(0)
    , _2b54(0)
    , _2b58(0)
    , _2b5c(0.0f)
    , _2b60(0.0f, 0.0f)
    , _2b68(0)
    , _2b6c(0.0f)
    , _2b70(0.0f)
    , _2b74(0)
    , _2b78(0)
    , mPropelActionSubTimer(0)
    , mPropelFlyTime(false)
    , _2b80(0)
    , _2b84(0)
    , mPropelFallSpinEffect()
    , _2bf0()
    , _2c58()
    , mSpinHipAttackEffect()
    , _2cc4(0)
    , _2cc8(0)
    , mPlyIceActorID()
    , mQuakeMode()
    , mQuakeRumbleTimer(0)
    , _2cd8(0.0f)
    , _2cdc(false)
    , _2ce0(0)
    , _2ce4(0)
    , mPenguinSwimFlag()
    , mTarzanRopeBgType(0)
    , _2cf0(0.0f)
    , _2cf4(0)
    , _2cf8(0)
    , _2cfc(0)
    , mRopeAngleNow()
    , mRopeAngleDiffNow()
    , mRopeAngleOld()
    , mRopeAngleDiffOld()
    , _2d10(0)
    , mMameWallWalkSpeed(0.0f)
    , _2d18(0.0f, 0.0f)
    , _2d20()
    , _2d24()
    , _2d28(0)
    , mKaniPosY(0.0f)
    , _2d30(false)
    , mMusaJumpStep(0)
    , _2d38(0.0f)
    , _2d3c(0.0f)
    , _2d40()
    , _2d44()
    , mMusaStartWallSlide(false)
    , mMusaCanDoJump(false)
    , _2d4a(0)
    , _2d4c(0)
    , _2d50()
    , mMusaFlyStep(0)
    , mEatData(mActorUniqueID)
    , mEatPosOffset(0.0f, 0.0f)
    , _2d84(false)
    , mEatPosReserve(0.0f, 0.0f)
    , _2d90(cDirType_Left)
    , mPlayerHangChildActorID()
    , mPlayerHangParentActorID()
    , _2d9c(0)
    , mJrCrownMtx()
    , _2dd0(0)
    , mQuakeTimer(0)
    , mQuakeEffectFlag(false)
    , mItemGetEffect1()
    , mItemGetEffect2()
    , mPowerUpEffect()
    , mSwimEffect()
    , mPaddleSwimEffectL()
    , mPaddleSwimEffectR()
    , _2fd4()
    , _303c()
    , mSpinJumpEffect()
    , mMissSpinJumpEffect()
    , _3124()
    , mMusaFlyEffect()
    , mMusaFlyUpEffectIndex(0)
    , mMusaFlyUpEffectDoubleBuffer()
    , mStarEffectStep(0)
    , mStarEffect()
    , mPMusaEffectStep(0)
    , mPMusaEffect()
    , mPMusaFlyEffectStep(0)
    , mPMusaFlyEffect()
    , _340c(0)
    , _3410(0)
    , _3414()
    , mOrchestra()
    , _3490(0)
    , _3494(0)
    , _3498()
    , _34a4()
    , mIdleCounter(0)
    , _34ac(0)
    , _34b0()
    , _34c4(false)
    , _34c5(false)
    , mJumpAnmRate(0.0f)
    , mJumpTimerF(0.0f)
    , mJumpAnmID(PlayerAnmID::cInvalid)
    , _34d4(10)
{
    mInvalidKeyTimer.fill(0);
    mInvalidKeyTimerType.fill(cInvalidKeyTimerType_Normal);
    _34b0.fill(0);
    _3498.fill(0);

    mCharacter = getParamPlayerCharacter(mParam0);
    mDirection = getParamPlayerFacingDir(mParam0);
    mMode = getParamPlayerMode(mParam0);
    mPlayerNo = getParamPlayerNo(mParam0);

    mPlayerKey.setPlayerNo(mPlayerNo);

    mpModelBaseMgr = &mModelMgr;

    setKind(cActorType_Player);

    const FieldPlayerData* p_player_data = CourseTask::instance()->getPlayerData(mPlayerNo);
    if (p_player_data != nullptr)
        mModelMgr.setMiiCapVisible(p_player_data->mii_cap_visible);

    mPriority = mPlayerNo;
}

void PlayerObject::setScrollMode(ScrollMode mode)
{
    mScrollMode = mode;
}

void PlayerObject::setSoundPlyMode()
{
    mAudioObj.setPlyMode(GameAudio::getPlyMode(mMode));
}

ActorBase::Result PlayerObject::create_()
{
    PlayerMgr::instance()->setPlayer(mPlayerNo, this);

    mModeNext = mMode;
    mModePrev = mMode;
    setPlayerMode(mMode, true);

    mSpeedMax.set(0.0f, 0.0f, 0.0f);
    mMaxFallSpeed = cMaxFallSpeed;
    mAccelY = getGravityData()->gravity;

    mScale.set(1.0f, 1.0f, 1.0f);

    mpEatData = &mEatData;

    setScrollMode(cScrollMode_0);

    initCcData();
    initBcData();

    if (PlayerMgr::instance()->isCourseInStar(mPlayerNo))
        setStar();

    setCharacterVoice();
    setSoundPlyMode();
    mAudioObj.setOutputLine(GameAudio::getRemotePlayer(mPlayerNo));

    mPropelParts.create(this);

    PlayerBase::create_();
    return cResult_Success;
}

ActorBase::Result PlayerObject::doDelete_()
{
    if (PlayerMgr::instance() != nullptr)
        PlayerMgr::instance()->resetPlayer(mPlayerNo);
    return cResult_Success;
}

bool PlayerObject::preDraw_()
{
    if (!PlayerBase::preDraw_())
        return false;

    if (CourseTask::instance() != nullptr && CourseTask::instance()->getGameMode() == FieldGameMode::cCoinEdit)
        return false;

    return true;
}

bool PlayerObject::draw_()
{
    if (isStatus(cStatus_HideTemporarily))
        offStatus(cStatus_HideTemporarily);
    else
    {
        mModelMgr.draw();
        mHipdropExEffect.drawModel();
    }
    return true;
}

bool PlayerObject::preExecute_()
{
    if (!PlayerBase::preExecute_())
        return false;

    if (CourseTask::instance() != nullptr && CourseTask::instance()->getGameMode() == FieldGameMode::cCoinEdit)
        return false;

    setThrowPlayer();
    return true;
}

void PlayerObject::calcScroll()
{
    sead::Vector3f pos = mPos;

    PlayerObject* p_ride_player = getRidePlayer();
    if (p_ride_player != nullptr)
        pos.x = p_ride_player->getPos().x;

    Yoshi* p_eat_yoshi = getEatYoshi();
    if (p_eat_yoshi != nullptr)
        pos.x = p_eat_yoshi->getPos().x;

    switch (mScrollMode)
    {
    default:
        break;
    case cScrollMode_1:
    case cScrollMode_3:
        _27c0 = pos;
        break;
    case cScrollMode_0:
    case cScrollMode_2:
    case cScrollMode_4:
    case cScrollMode_5:
    case cScrollMode_6:
        if (_27cc != 0)
        {
            bool chasing = false;
            if (!sead::Mathf::chase(&_27c0.x, pos.x, 3.0f))
                chasing = true;
            if (!sead::Mathf::chase(&_27c0.y, pos.y, 3.0f))
                chasing = true;
            if (!chasing)
                _27cc = 0;
        }
        else
        {
            f32 x_max = 6.0f;
            f32 y_max = 6.0f;
            if (mScrollMode == cScrollMode_4)
                y_max = 8.0f;
            MathUtil::addCalc(&_27c0.x, pos.x, 0.25f, x_max, 0.1f);
            MathUtil::addCalc(&_27c0.y, pos.y, 0.25f, y_max, 0.1f);
        }
        if (isStatus(cStatus_130))
            setScrollMode(cScrollMode_5);
        else if (mScrollMode == cScrollMode_5)
            setScrollMode(cScrollMode_0);
        break;
    }
}

void PlayerObject::postExecute_(MainState state)
{
    if (state == cState_Success)
    {
        calcLiftUpOffsetScale();
        calcScroll();
    }
    PlayerBase::postExecute_(state);
}

void PlayerObject::calcModelWaitFlag()
{
    mModelMgr.offWait();
    mModelMgr.offRideCloudWait();
    mModelMgr.offRideLiftWait();

    if (PlayerMgr::instance()->isDemoWaitFlgDisable(mPlayerNo))
        return;

    PlayerObject* p_ride_player = getRidePlayer(); // The player we are currently riding, or nullptr if we aren't riding anything
    if (p_ride_player != nullptr)
    {
        if (mModelMgr.getAnmID() != PlayerAnmID::stoop_start &&
            mModelMgr.getAnmID() != PlayerAnmID::stoop &&
            mModelMgr.getAnmID() != PlayerAnmID::fire_at2)
        {
            PlayerModelBaseMgr* p_ride_model_mgr = p_ride_player->mpModelBaseMgr;
            if (p_ride_model_mgr != nullptr)
            {
                switch (p_ride_model_mgr->getAnmID())
                {
                default:
                    break;
                case PlayerAnmID::carryP_walk:
                    if (p_ride_player->mDirection == cDirType_Right)
                        mModelMgr.onWaitL();
                    else
                        mModelMgr.onWaitR();
                    break;
                case PlayerAnmID::waitL:
                case PlayerAnmID::slope_waitL:
                    mModelMgr.onWaitL();
                    break;
                case PlayerAnmID::waitR:
                case PlayerAnmID::slope_waitR:
                    mModelMgr.onWaitR();
                    break;
                }
            }
        }
    }
    else
    {
        if (!isCarry())
        {
            switch (mModelMgr.getAnmID())
            {
            default:
                break;
            case PlayerAnmID::waitL:
            case PlayerAnmID::slope_waitL:
                mModelMgr.onWaitL();
                break;
            case PlayerAnmID::waitR:
            case PlayerAnmID::slope_waitR:
                mModelMgr.onWaitR();
                break;
            case PlayerAnmID::wait:
                if (isStatus(cStatus_RideCloud))
                {
                    if (mAngle.y() >= 0)
                        mModelMgr.onWaitL();
                    else
                        mModelMgr.onWaitR();
                    mModelMgr.onRideCloudWait();
                }
                break;
            }
        }
    }
    if (mModelMgr.isWaitL() || mModelMgr.isWaitR())
    {
        if (p_ride_player != nullptr)
        {
            if (p_ride_player->isRideMove())
                mModelMgr.onRideLiftWait();
        }
        else
        {
            if (isRideMove())
                mModelMgr.onRideLiftWait();
        }
    }
}

Angle PlayerObject::getModelAngleY()
{
    Angle angle = mAngle.y();
    angle += getMissSpinAngle();
    return angle;
}

void PlayerObject::getModelScaleBase(sead::Vector3f* p_scale)
{
    if (p_scale != nullptr)
        *p_scale = mScale * mEffectScale;
}

void PlayerObject::getModelScale(sead::Vector3f* p_scale)
{
    if (p_scale != nullptr)
    {
        sead::Vector3f base_scale;
        getModelScaleBase(&base_scale);
        sead::Vector3f reduction_scale;
        getReductionModelScale(&reduction_scale);
        p_scale->set(
            base_scale.x * reduction_scale.x,
            base_scale.y * reduction_scale.y,
            base_scale.z * reduction_scale.z
        );
    }
}

void PlayerObject::calcModel_()
{
    setModelDark();

    if (isNowBgCross(cBgCross_IsOnHDokan))
        mModelMgr.onOnHDokan();
     else
        mModelMgr.offOnHDokan();

    calcModelWaitFlag();

    Yoshi* p_ride_yoshi = getRideYoshi();
    if (p_ride_yoshi != nullptr)
    {
        calcModelRideYoshi();
        return;
    }

    if (isStatus(cStatus_RideJrCrown))
    {
        mModelMgr.calc(mJrCrownMtx);
        return;
    }

    if (!isStatus(cStatus_RidePlayer) && !isStatus(cStatus_RideBalloon))
    {
        sead::Vector3f model_pos(
            mPos.x + _2774.x,
            mPos.y + _2774.y + _29d0,
            mPos.z
        );
        Angle model_angle_x = mAngle.x();
        Angle model_angle_y = getModelAngleY();
        Angle model_angle_z = mAngle.z();
        sead::Vector3f model_scale;
        getModelScale(&model_scale);

        f32 model_center_y = 8.0f;
        switch (mModelMgr.getAnmID())
        {
        default:
            break;
        case PlayerAnmID::tree_start:
        case PlayerAnmID::tree_wait:
        case PlayerAnmID::tree_climb:
        case PlayerAnmID::tree_pose:
        case PlayerAnmID::rope_swing:
            model_center_y = getBcAreaCenterY();
            break;
        case PlayerAnmID::shoot:
            model_center_y = 5.0f;
            break;
        }
        model_center_y = model_center_y * model_scale.y * mModelMgr.getBaseScale();

        model_pos.y += model_center_y;

        sead::Matrixf model_mtx;
        model_mtx.makeRzxyTIdx(Angle3(model_angle_x, model_angle_y, model_angle_z), model_pos);
        model_mtx.multTranslationLocal(sead::Vector3f(0.0f, -model_center_y, 0.0f));
        model_mtx.multScaleLocal(model_scale);

        mModelMgr.calc(model_mtx);
    }
}

void PlayerObject::executeLastPlayer()
{
    if (isStatus(cStatus_RideYoshi))
        setYoshiBackPos();

    if (isStatus(cStatus_RideJrCrown))
        setJrCrownPos();

    if (isStatus(cStatus_41))
        setPlayerJumoDaiPos();

    calcModel_();
}

void PlayerObject::calcModelRidePlayer()
{
    setPlayerHandPos();

    Angle model_angle_y = getModelAngleY();

    sead::Vector3f model_pos(
        mPos.x,
        mPos.y,
        mPos.z
    );
    Angle model_angle_x = mAngle.x();
    Angle model_angle_z = mAngle.z();

    PlayerObject* p_ride_player = getRidePlayer();
    if (p_ride_player != nullptr)
    {
        if (mMode == cPlayerMode_Mini)
            model_pos.y += GetCarryMiniPlayerAddYOffs(p_ride_player->mCharacter, p_ride_player->mMode);
        else if (mMode == cPlayerMode_Small)
            model_pos.y += GetCarrySmallPlayerAddYOffs(p_ride_player->mCharacter, p_ride_player->mMode);
    }

    sead::Matrixf model_mtx;
    model_mtx.makeRzxyTIdx(Angle3(model_angle_x, model_angle_y, model_angle_z), model_pos);

    sead::Vector3f model_scale;
    getModelScale(&model_scale);

    model_mtx.multScaleLocal(model_scale);

    mModelMgr.calc(model_mtx);
}

void PlayerObject::executeLastAll()
{
    if (!isStatus(cStatus_ActiveThisFrame))
        return;

    executeSubjectState();

    setSpinLiftUpReserve();
    clearSpinLiftUpReserve();

    setSpinAction();
    offStatus(cStatus_149);
    offStatus(cStatus_150);

    if (isStatus(cStatus_RidePlayer))
    {
        calcModelRidePlayer();
        checkRidePlayerRoofRidePress();
    }

    calcHeadAttentionAngle();

    mModelMgr.calc2();

    updateSpinJumpEffect();
    updateMissSpinJumpEffect();

    sead::Matrixf head_propel_joint_mtx;
    mModelMgr.getHeadPropelJointMtx(&head_propel_joint_mtx);
    mPropelParts.setSpinEffect(head_propel_joint_mtx);

    updateMusaEffect();

    if (isStarLight())
    {
        sead::Vector3f star_effect_pos;
        mModelMgr.getJointPos(&star_effect_pos, "skl_root");
        mLight.update(cLightType_InvincibilityStar, &star_effect_pos);
    }
}

void PlayerObject::setPlayerNo(s8 player_no)
{
    if (0 <= player_no && player_no < 4)
    {
    }
}

void PlayerObject::setPlayerData_()
{
    mVisibleAreaOffset.set(0.0f, 20.0f);
    mVisibleAreaSize.set(15.0f, 22.0f);
}

void PlayerObject::setCenterOffset()
{
    const f32 height[] = {
        16.0f,  // cPlayerMode_Small
        31.0f,  // cPlayerMode_Normal
        31.0f,  // cPlayerMode_Fire
         6.0f,  // cPlayerMode_Mini
        31.0f,  // cPlayerMode_Propeller
        31.0f,  // cPlayerMode_Penguin
        31.0f,  // cPlayerMode_Ice
        31.0f,  // cPlayerMode_Squirrel
        31.0f,  // cPlayerMode_PSquirrel

    };
    static_assert(sizeof(height) / sizeof(f32) == cPlayerMode_Num);

    mHeight = height[mMode];

    if (mModelMgr.isAnmFlag(PlayerModelBase::cAnmFlagType_Main, PlayerModelBase::cAnmFlagBit_Sit))
        mCenterOffset.set(0.0f, mHeight * 0.25f, 0.0f);
    else
    {
        f32 center_offset_y = mHeight * 0.5f;
        if (mModelMgr.isAnmFlag(PlayerModelBase::cAnmFlagType_Main, PlayerModelBase::cAnmFlagBit_2))
            center_offset_y = -center_offset_y;
        mCenterOffset.set(0.0f, center_offset_y, 0.0f);
    }

    f32 target = 16.0f;
    if (mMode == cPlayerMode_Mini)
        target = 8.0f;
    sead::Mathf::chase(&mDispSideLimitPad, target, 0.1f);
}

void PlayerObject::setSpeedData()
{
    s32 index;
    if (isEnableRDashLuigiPhysics())
    {
        if (mMode == cPlayerMode_Mini)
            index = 1 * 2 + 0;
        else
            index = 1 * 2 + 1;
    }
    else
    {
        if (mMode == cPlayerMode_Mini)
            index = 0 * 2 + 0;
        else
            index = 0 * 2 + 1;
    }
    mpSpeedData_Normal = &(sPlayerSpeedData[index * 2 + 0]);
    mpSpeedData_Star = &(sPlayerSpeedData[index * 2 + 1]);
}

void PlayerObject::setModeGravity()
{
    mpGravityData = getGravityData();
}

void PlayerObject::setPlayerModeImpl(PlayerMode mode, bool temporary)
{
    mModePrev = mMode;

    mMode = mode;
    mModelMgr.setPlayerMode(mMode);

    setPlayerData_();
    setCenterOffset();
    setSpeedData();
    mAccelF = getSpeedData()->power_data_normal.x_accel_stage1;
    setModeGravity();

    offStatus(cStatus_Penguin);
    switch (mMode)
    {
    default:
        break;
    case cPlayerMode_Propeller:
        resetPropelFukidashi();
        resetPropelFlyTime();
        break;
    case cPlayerMode_Penguin:
        onStatus(cStatus_Penguin);
        break;
    case cPlayerMode_Squirrel:
    case cPlayerMode_PSquirrel:
        mMusaCanDoJump = true;
        break;
    }

    mBgCheckPlayer.offMame();
    if (mMode == cPlayerMode_Mini)
        mBgCheckPlayer.onMame();

    setSoundPlyMode();

    if (!temporary)
        CourseTask::instance()->getPlayerData(mPlayerNo)->player_mode = mMode;
}

const PlayerGravityHIO* PlayerObject::getGravityData()
{
    s32 index = 0 * 2 + 0;
    if (isEnableRDashLuigiPhysics() && isEnableRDashLuigiGravity())
    {
        index = 1 * 2 + 0;
        if (isMameAction())
            index = 1 * 2 + 1;
    }
    else
    {
        if (isMameAction())
            index = 0 * 2 + 1;
    }
    return &(cPlayerGravityData[index]);
}

PlayerTallType PlayerObject::getTallType(PlayerMode mode)
{
    return cTallType[mode];
}

void PlayerObject::setZPosition()
{
    if (isStatus(cStatus_ZPosSetNone))
        return;

    if (mCollisionMask.isOn(cCcLineKind_0) && mLayer == cLayerID_Layer1)
        mPos.z =  3000.0f - (mPriority * 32);
    else
        mPos.z = -1800.0f - (mPriority * 32);
}

void PlayerObject::setZPosition(f32 z)
{
    onStatus(cStatus_ZPosSetNone);
    mPos.z = z - (mPriority * 32);
}

void PlayerObject::setZPositionDirect(f32 z)
{
    onStatus(cStatus_ZPosSetNone);
    mPos.z = z;
}

void PlayerObject::offZPosSetNone()
{
    offStatus(cStatus_ZPosSetNone);
}

void PlayerObject::setCharacterVoice()
{
    if (mCharacter == cPlayerCharacter_Mii)
        mAudioObj.setVoice(SndObjctPly::getMiiCharacterVoice(CourseTask::instance()->getPlayerData(mPlayerNo)->mii_slot));
    else
    {
        static const PlayerCharacterVoice cVoice[] = {
            cVoice_Mario,
            cVoice_Luigi,
            cVoice_YellowToad,
            cVoice_BlueToad,
            cVoice_Nabbit,
            cVoice_MiiMale2
        };
        static_assert(sizeof(cVoice) / sizeof(PlayerCharacterVoice) == cPlayerCharacter_NumGame);

        mAudioObj.setVoice(cVoice[mCharacter]);
    }
}

void PlayerObject::getMaskPos(sead::Vector3f& pos)
{
    sead::Vector3f mask_pos(
        mMaskPos.x,
        mMaskPos.y + mHeight * 0.5f,
        mMaskPos.z
    );
    dokanAdjustMaskPos(mask_pos);
    pos = mask_pos;
}

void PlayerObject::getMaskCaveCheckPos(sead::Vector3f* p_pos, f32* p_y_offset)
{
    if (p_pos != nullptr && p_y_offset != nullptr)
    {
        sead::Vector3f mask_pos = mMaskPos;
        if (mMode == cPlayerMode_Small || mMode == cPlayerMode_Mini)
        {
            if (isStatus(cStatus_RideYoshi))
                mask_pos.y += 8.0f;
            else
                mask_pos.y += mHeight * 0.5f;
        }
        else
        {
            mask_pos.y += getHeadBgPointData()->center_offset * 0.5f;
        }
        dokanAdjustMaskPos(mask_pos);
        f32 y_offset = sead::Mathf::abs(mask_pos.y - mPos.y) * 0.5f;
        if (y_offset > 4.0f)
            y_offset = 4.0f;
        *p_pos = mask_pos;
        *p_y_offset = y_offset;
    }
}

bool PlayerObject::vf154()
{
    Yoshi* p_ride_yoshi = getRideYoshi();
    if (p_ride_yoshi != nullptr && p_ride_yoshi->isStatus(cStatus_210))
        return false;

    return PlayerBase::vf154();
}

void PlayerObject::setInvalidKeyTimer_LR(s32 time, InvalidKeyTimerType type)
{
    mInvalidKeyTimer[1] = time;
    mInvalidKeyTimerType[1] = type;
    mPlayerKey.onStatus(PlayerKey::cStatus_NoCross);
}

void PlayerObject::calcInvalidKeyTimer()
{
    for (s32 i = 0; i < cInvalidKeyType_Num; i++)
    {
        if (mInvalidKeyTimer[i] == 0)
            continue;

        switch (mInvalidKeyTimerType[i])
        {
        default:
            break;
        case cInvalidKeyTimerType_ResetOnGround:
            if (isNowBgCross(cBgCross_IsFoot))
                mInvalidKeyTimer[i] = 0;
            break;
        case cInvalidKeyTimerType_ResetOnDescendOrGround:
            if (mSpeed.y <= 0.0f || isNowBgCross(cBgCross_IsFoot))
                mInvalidKeyTimer[i] = 0;
            break;
        }

        MathUtil::calcTimer(&(mInvalidKeyTimer[i]));
        if (mInvalidKeyTimer[i] == 0)
        {
            switch (i)
            {
            default:
                break;
            case cInvalidKeyType_All:
                mPlayerKey.offStatus(PlayerKey::cStatus_NoInput);
                break;
            case cInvalidKeyType_LR:
                mPlayerKey.offStatus(PlayerKey::cStatus_NoCross);
                break;
            case cInvalidKeyType_Shake:
                mPlayerKey.offStatus(PlayerKey::cStatus_NoShakeJump);
                break;
            }
        }
    }
}

void PlayerObject::selectAction()
{
    if (isStatus(cStatus_18) && setSpinActionReq())
        return;

    if (isDemo() || isStatus(cStatus_RideBalloon))
        return;

    if (setShadowkunHouseReadAction())
        return;

    if (setBalloonButtonA())
        return;

    if (setQuakeAction())
        return;

    if (setVineAction())
        return;

    if (setPoleAction())
        return;

    if (setHangAction())
        return;

    if (setKaniHangAction())
        return;

    if (checkWallJump())
        return;

    if (setTarzanRopeAction())
        return;

    if (setSpinActionReq())
        return;

    if (setFireBallAction())
        return;

    if (setSwimAction())
        return;
}

void PlayerObject::startQuakeShock(Quake::ShockType shock_type)
{
    PlayerBase::startQuakeShock(shock_type);
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
        p_carry_player->startQuakeShock(shock_type);
}

void PlayerObject::startPatternRumble(const char* pattern)
{
    PlayerBase::startPatternRumble(pattern);
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
        p_carry_player->startPatternRumble(pattern);
}

void PlayerObject::calcModelBalloon()
{
    if (isStatus(cStatus_RideBalloon))
    {
        Angle model_angle_y = getModelAngleY();

        const sead::Vector3f& model_pos = mPos;
        Angle model_angle_x = mAngle.x();
        Angle model_angle_z = mAngle.z();

        sead::Matrixf model_mtx;
        model_mtx.makeRzxyTIdx(Angle3(model_angle_x, model_angle_y, model_angle_z), model_pos);

        sead::Vector3f model_scale;
        getModelScale(&model_scale);

        model_mtx.multScaleLocal(model_scale);

        mModelMgr.calc(model_mtx);
    }
}

bool PlayerObject::isFaceRot()
{
    return mModelMgr.isFaceRot();
}

void PlayerObject::setClampFaceRot()
{
    mModelMgr.setClampFaceRot();
}

bool PlayerObject::bouncePlayer1(f32 speed_y, f32 speed_F, bool enable_LR, BounceType bounce_type, JumpSe jump_se_type)
{
    if (mMode != cPlayerMode_Mini)
        if (isClimb())
            return false;

    if (isStatus(cStatus_186))
        return false;

    return bouncePlayer2(speed_y, speed_F, enable_LR, bounce_type, jump_se_type);
}

bool PlayerObject::bouncePlayer2(f32 speed_y, f32 speed_F, bool enable_LR, BounceType bounce_type, JumpSe jump_se_type)
{
    if (isDemo())
        return false;

    if (isStatus(cStatus_ControlledState) && isStatus(cStatus_RideBalloon))
        return false;

    if (setSwimSpeed(speed_y * 0.5f, speed_F * 0.5f))
        return true;

    clearJumpActionInfo();

    if (setBalloonChibiYoshiFlySmall(speed_y, speed_F))
        return true;

    if (isStatus(cStatus_45))
        changeState(StateID_KaniJump, 0);
    else
    {
        mSpeedF = speed_F;

        bool fall = false;
        if (speed_y <= 0.0f)
        {
            if (isStatus(cStatus_CheckBg))
            {
                if (isOldBgCross(cBgCross_IsFoot))
                    fall = true;
            }
            else
            {
                if (isNowBgCross(cBgCross_IsFoot))
                    fall = false;
            }
        }
        if (!fall)
        {
            bool spin_jump = false;
            bool sit_jump = false;
            if (isStatus(cStatus_Spin) && isStatus(cStatus_Jump))
                spin_jump = true;
            else if (isStatus(cStatus_SitJump))
                sit_jump = true;
            if (speed_y != 0.0f)
            {
                JumpInf jump_inf;
                jump_inf.speed_y = speed_y;
                jump_inf.jump_se_type = jump_se_type;
                jump_inf._8 = 1;
                changeState(StateID_Jump, jump_inf);
            }
            else
            {
                mSpeed.y = speed_y;
                changeState(StateID_Fall, cAnmBlend_Enable);
            }
            onStatus(cStatus_204);
            onStatus(cStatus_147);
            if (spin_jump)
                changeState(StateID_SpinJump, makeSpinJumpParam(2, jump_se_type));
            else if (sit_jump)
                changeState(StateID_SitJump, 1);
        }
    }

    if (!enable_LR)
    {
        mPlayerKey.onStatus(PlayerKey::cStatus_NoCross);
        onStatus(cStatus_199);
    }

    switch (bounce_type)
    {
    default:
        break;
    case cBounceType_1:
        mPlayerKey.onStatus(PlayerKey::cStatus_ForceJump);
        break;
    case cBounceType_2:
        mPlayerKey.onStatus(PlayerKey::cStatus_NoJump);
        break;
    }

    return true;
}

bool PlayerObject::bouncePlayerSpin(f32 speed_y, f32 speed_F)
{
    if (isDemo())
        return false;

    if (isNowBgCross(cBgCross_IsUnderwater))
        return false;

    checkSinkSand();

    SpinActionMode mode = getSpinActionMode();
    if (isOnSinkSand())
        mode = cSpinActionMode_Normal;

    switch (mode)
    {
    default:
        mSpeed.y = speed_y;
        mSpeedF = speed_F;
        changeState(StateID_SpinJump, makeSpinJumpParam(2, cJumpSe_Normal));
        break;
    case cSpinActionMode_Propel:
        mSpeedF = speed_F;
        changeState(StateID_Propel, 2);
        break;
    case cSpinActionMode_ChibiYoshiBalloon:
        {
            BalloonChibiYoshi* p_cy_balloon = sead::DynamicCast<BalloonChibiYoshi>(ActorMgr::instance()->getActorPtr(mCarryActorID));
            if (p_cy_balloon != nullptr)
            {
                p_cy_balloon->setSpin(this);
                changeState(StateID_BalloonChibiYoshiFly, 0);
            }
        }
        break;
    case cSpinActionMode_ChibiYoshiBubble:
        _2a24 = 0;
        setChibiYoshiBubbleSpin();
        bouncePlayer1(speed_y, speed_F, true, cBounceType_1, cJumpSe_None);
        break;
    case cSpinActionMode_Musa:
        mSpeed.y = cPlayerMusaSpinJumpSpeed;
        changeState(StateID_SpinJump, makeSpinJumpParam(2, cJumpSe_Normal));
        break;
    case cSpinActionMode_Normal:
        mSpeed.y = speed_y;
        mSpeedF = speed_F;
        changeState(StateID_SpinJump, makeSpinJumpParam(2, cJumpSe_Normal));
        break;
    }

    return true;
}

bool PlayerObject::isEnableZoom()
{
    if (isDemoType(cDemoType_3))
        return false;

    if (!InputMgr::instance()->isInputEnabled())
        return false;

    if (_34d4 != 0)
        return false;

    return true;
}
