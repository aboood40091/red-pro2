#include <enemy/Enemy.h>
#include <game/AreaTask.h>
#include <game/CourseTask.h>
#include <game/SubjectMgr.h>
#include <map/LayerID.h>
#include <map_obj/ActorCoinMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerMgr.h>
#include <player/PlayerModelBaseMgr.h>
#include <scroll/BgScrollMgr.h>
#include <utility/MathUtil.h>

const f32 PlayerBase::cFireShootFrame = 4.0f;

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

PlayerBase::PlayerBase(const ActorCreateParam& param)
    : Actor(param)
    , mExecuteFreezeTimer(0)
    , mpModelBaseMgr(nullptr)
    , _284(0.0f, 0.0f, 0.0f)
    , mMaskPosInterpSrcType(0)
    , mMaskPosInterpTimer(0)
    , mMaskPos(mPos)
    , _2a4(0)
    , mPlayerKey()
    , mAudioObj()
    , mAttentionLookat(mActorUniqueID)
    , mStatus()
    , mCenterOffsetY(16.0f)
    , _4b8(cDirType_Right)
    , mFrameEndPosDelta(0.0f, 0.0f, 0.0f)
    , _4c8(0.0f, 0.0f, 0.0f)
    , mpSpeedData_Normal(nullptr)
    , mpSpeedData_Star(nullptr)
    , mpGravityData(nullptr)
    , mNoGravityTimer(0)
    , _4e4(0.0f)
    , _4e8(false)
    , mNextFrameSpeed(0.0f, 0.0f, 0.0f)
    , mPriority(0)
    , mTreadCnt(0)
    , mComboCnt(0)
    , mCharacter(cPlayerCharacter_Mario)
    , mMode(cPlayerMode_Small)
    , mBgCheckPlayer()
    , mBcSensorHead()
    , mBcSensorFoot()
    , mBcSensorWall()
    , mNowBgCross()
    , mOldBgCross()
    , mOldBgCrossFoot()
    , _1b0c(mPos.y)
    , mKaniPosY(0.0f)
    , mSakaType(ActorBgCollisionCheck::SakaType(0))
    , mSpeedSakaAngle()
    , mSpeedSakaAnglePrev()
    , mBaseSakaAngle()
    , mBaseSakaAnglePrev()
    , _1b28(0.0f, 0.0f, 0.0f)
    , mBgAttr(cBgAttr_Rock)
    , mWallAngle()
    , mWaterSurfacePosY(0.0f)
    , mWaterSurfacePosYPrev(0.0f)
    , mWaterType(cWaterType_None)
    , mWaterDepthType(0)
    , mAirWaterHitPos(0.0f, 0.0f, 0.0f)
    , mAirWaterHitAngle()
    , mSinkSandSurfacePosY(0.0f)
    , mBgSpeed(0.0f, 0.0f)
    , mBgSpeedPrev(0.0f, 0.0f)
    , mSandSinkRate(0.0f)
    , mDispSideLimitPad(16.0f)
    , mIsBgDamageEnable(false)
    , mDamageBgTypeInfo()
    , mBgPressIDBuffer()
    , mLineSpinLiftID()
    , _1b9c(0)
    , mNoHitObjBgTimer(0)
    , mAirDriftSpeedFStart(0.0f)
    , mAirDriftSpeedF(0.0f)
    , mAirDriftSpeedFDecelStep(0.0f)
    , mAddBgSpeedF(0.0f)
    , _1bb4(0)
    , mCollisionCheck2_React()
    , mCollisionCheck3_React()
    , mCollisionCheck4_Attack()
    , mCollisionCheck5_Attack()
    , mDrcTouchCallback()
    , _205c(0)
    , _2060(0)
    , _2064(0)
    , _2068(0)
    , _206c(0)
    , _2070(0)
    , mCcPlayerRevSpeedFScale(0.0f)
    , mCcPlayerRevSpeedFStart(0.0f)
    , mCcPlayerRevSpeedF(0.0f)
    , _2080(0.0f)
    , _2084(0)
    , _2085(0)
    , mNoHitPlayerTimer(0)
    , mNoHitPlayerID()
    , mReductionMode(cReductionMode_None)
    , mReductionStep(0)
    , mReductionScale(0.0f)
    , _209c(0)
    , _20a0(0)
    , _20a4()
    , _20ac()
    , mDemoStateMgr(*this)
    , mChangeDemoStateParam(0)
    , mDemoTypeFlag()
    , mDemoMode(0)
    , mDemoAction(0)
    , mDemoWaitTimer(0)
    , _20ec(0)
    , mPlayerJumpDaiID(0)
    , mDstNextGotoID(0)
    , mNextGotoType(cNextGotoType_Normal)
    , mNextGotoDelay(cNextGotoBlockDelay_None)
    , _2100()
    , _2108()
    , mFaderPos(mPos)
    , mIsLastPlayer(false)
    , _2120(0.0f)
    , _2124(0.0f)
    , _2128(-1)
    , _212c(-1)
    , mGoalBasePosY(0.0f)
    , _2134(0)
    , _2138(0)
    , _213c()
    , _2148(0)
    , _214c(0)
    , mDokanDir(cDokanDir_Up)
    , mDokanPos()
    , mDokanPosPrev()
    , mDokanPosMoveDelta()
    , mDokanType(cDokanType_Invalid)
    , _2178(0.0f)
    , _217c(0.0f)
    , mDokanInTimerL(0)
    , mDokanInTimerR(0)
    , mpDokanBgCollision(nullptr)
    , mIsDokanSwim(false)
    , _2190(0.0f)
    , _2194(0)
    , _2198(false)
    , mStateMgr(*this)
    , mpChangeStateJmpInf(nullptr)
    , mChangeStateParam(0)
    , mAction(0)
    , mActionTimer(0)
    , mStunMode(0)
    , mRideActorID()
    , _21d8(0)
    , _21dc(0)
    , _21e0(0)
    , _21e4(0)
    , _21e8(0)
    , mFunsuiType(cFunsuiType_Sand)
    , mFunsuiPos(0.0f, 0.0f)
    , mJumpDaiSpeedFReserve(0.0f)
    , mRidePlayerPosDelta(0.0f, 0.0f, 0.0f)
    , _2208()
    , mHipdropEffectStep(0)
    , mRideNatPosY(0.0f)
    , mFrameEndFollowMameKuribo(0)
    , mFollowMameKuribo(0)
    , mPenguinSlideCooldown(0)
    , mAnimePlayStep(0)
    , mEffectObjCommon()
    , mSlipSmokeEffect()
    , _22fc()
    , mFootEffect()
    , mHipAttackDropEffect()
    , mHipdropEffect()
    , mHipdropPos()
    , mHipdropExEffect()
    , _2498()
    , _2500()
    , mTurnBrakeEffect()
    , mTurnBrakeSmokeEffect()
    , mTurnBrakeBgAttr(cBgAttr_Rock)
    , mIsTurnBrakeEffectEnable(false)
    , mIsTurnBrakeSmokeEffectEnable(false)
    , _25f0(0)
    , _25f4()
    , _265c(0)
    , _2660(0)
    , mWaterEffect()
    , mChallengeStateMgr(*this)
    , _2748(0)
    , _274c(false)
{
    mOldBgCrossFoot.fill(FALSE);
    _20a4.fill(0);
    _20ac.fill(0.0f);

    mBcSensorHead.p1 = 0.0f;
    mBcSensorHead.p2 = 0.0f;
    mBcSensorHead.center_offset = 0.0f;

    mBcSensorFoot.p1 = 0.0f;
    mBcSensorFoot.p2 = 0.0f;
    mBcSensorFoot.center_offset = 0.0f;

    mBcSensorWall.p1 = 0.0f;
    mBcSensorWall.p2 = 0.0f;
    mBcSensorWall.center_offset = 0.0f;

    mBgCheckPlayer.set(this, nullptr, nullptr, nullptr);

    changeState(StateID_Walk, 0);
    changeDemoState(StateID_DemoNone, 0);
    changeChallengeState(StateID_ChallengeState1);
}

PlayerBase::~PlayerBase()
{
    PlayerBase::releaseCcData();
}

ActorBase::Result PlayerBase::create_()
{
    mHipdropExEffect.createModel();

    sead::Matrixf mtx;
    mtx.makeRTIdx(mAngle, mPos);
    mtx.multScaleLocal(mScale);

    mpModelBaseMgr->calc(mtx);

    return cResult_Success;
}

bool PlayerBase::preExecute_()
{
    getPos2D() += mNextFrameSpeed;
    mNextFrameSpeed.set(0.0f, 0.0f, 0.0f);

    offStatus(cStatus_1);

    if (!Actor::preExecute_())
        return false;

    if (isStatus(cStatus_2))
        return false;

    mBgCheckPlayer.atFrameStart();

    onStatus(cStatus_1);

    offStatus(cStatus_270);
    offStatus(cStatus_71);
    offStatus(cStatus_134);
    offStatus(cStatus_138);
    offStatus(cStatus_141);

    if (isStatus(cStatus_256))
    {
        onStatus(cStatus_255);
        offStatus(cStatus_256);
    }

    offStatus(cStatus_117);
    if (isStatus(cStatus_118))
    {
        onStatus(cStatus_117);
        offStatus(cStatus_118);
    }

    offStatus(cStatus_EnableDokanIn);

    if (mSpeed.y <= 0.0f)
        offStatus(cStatus_10);

    MathUtil::calcTimer(&_2a4);

    return true;
}

bool PlayerBase::execute_()
{
    MathUtil::calcTimer(&mExecuteFreezeTimer);
    if (mExecuteFreezeTimer != 0)
        bgCheck(true);
    else
    {
        mPlayerKey.update();
        setZPosition();
        releaseCcData();
        executeMain();
        mPlayerKey.updateEnd();
        mAudioObj.calc(getCenterPos());
    }
    executeLastPlayer();
    vf19C();
    return true;
}

void PlayerBase::clearFollowMameKuribo()
{
    offStatus(cStatus_FollowMameKuribo);
    mFrameEndFollowMameKuribo = mFollowMameKuribo;
    mFollowMameKuribo = 0;
}

static inline sead::Vector3f CalcMaskPosSpeed(const sead::Vector3f& dst_pos, const sead::Vector3f& mask_pos, s32 time)
{
    if (time < 1)
        time = 1;

    sead::Vector3f speed = dst_pos;
    speed -= mask_pos;
    speed /= time;
    return speed;
}

void PlayerBase::calcMaskPos()
{
    MathUtil::calcTimer(&mMaskPosInterpTimer);

    sead::Vector3f base_pos = mPos;

    switch (mMaskPosInterpSrcType)
    {
    default:
        {
            sead::Vector3f speed = CalcMaskPosSpeed(base_pos, mMaskPos, mMaskPosInterpTimer);
            mMaskPos += speed;
        }
        break;
    case 0:
        {
            sead::Vector3f speed = CalcMaskPosSpeed(base_pos, mMaskPos, mMaskPosInterpTimer);
            mMaskPos += speed;
        }
        break;
    case 1:
        {
            sead::Vector3f ankle_l;
            mpModelBaseMgr->getJointPos(&ankle_l, "ankle_l1");
            sead::Vector3f ankle_r;
            mpModelBaseMgr->getJointPos(&ankle_r, "ankle_r1");

            sead::Vector3f ankle_pos = base_pos;
            ankle_pos.y = (ankle_l.y + ankle_r.y) * 0.5f;

            sead::Vector3f speed = CalcMaskPosSpeed(ankle_pos, mMaskPos, mMaskPosInterpTimer);
            mMaskPos += speed;
        }
        break;
    }
}

void PlayerBase::postExecute_(MainState state)
{
    mFrameEndPosDelta = mPos - mPosPrev;

    if (state == cState_Success)
    {
        offStatus(cStatus_46);
        offStatus(cStatus_47);
        offStatus(cStatus_178);
        offStatus(cStatus_RideNat);
        offStatus(cStatus_136);
        offStatus(cStatus_137);
        offStatus(cStatus_282);
        offStatus(cStatus_130);
        offStatus(cStatus_148);
        offStatus(cStatus_151);
        offStatus(cStatus_152);
        offStatus(cStatus_105);
        offStatus(cStatus_106);
        offStatus(cStatus_93);
        offStatus(cStatus_63);
        offStatus(cStatus_255);

        if (!isStatus(cStatus_250))
            mBgCheckPlayer.clearBg();
        offStatus(cStatus_250);

        if (isStatus(cStatus_153) && isStatus(cStatus_DispOut))
            onStatus(cStatus_2);

        clearFollowMameKuribo();
        clearCcPlayerRev();
        clearCcData();

        if (!isStatus(cStatus_FaderPosSet))
            mFaderPos = mPos;

        calcMaskPos();
    }

    Actor::postExecute_(state);
}

bool PlayerBase::preDraw_()
{
    if (isStatus(cStatus_123))
    {
        offStatus(cStatus_Invisible);
        offStatus(cStatus_123);
    }

    if (isStatus(cStatus_Invisible))
        return false;

    if (!Actor::preDraw_())
        return false;

    return true;
}

void PlayerBase::blockHitInit_()
{
    if (isStatus(cStatus_60))
        return;

    bouncePlayer1(Enemy::cFumiJumpSpeed + 3.628f, mSpeedF, true, cBounceType_Normal, cJumpSe_None);
}

void PlayerBase::setDrawTypeInDistantView()
{
    mpModelBaseMgr->setDrawType(PlayerModelBaseMgr::cDrawType_InDistantView);
}

void PlayerBase::resetDrawType()
{
    mpModelBaseMgr->setDrawType(PlayerModelBaseMgr::cDrawType_Normal);
}

bool PlayerBase::isKinopio() const
{
    switch (mCharacter)
    {
    case cPlayerCharacter_YellowToad:
    case cPlayerCharacter_BlueToad:
        return true;
    default:
        return false;
    }
}

bool PlayerBase::isTotten() const
{
    return mCharacter == cPlayerCharacter_Nabbit;
}

bool PlayerBase::isMameAction()
{
    if (mMode == cPlayerMode_Mini && !isLiftUpExceptMame())
        return true;
    else
        return false;
}

PlayerModelBase* PlayerBase::getModel()
{
    return mpModelBaseMgr->getModelBase();
}

sead::Vector3f* PlayerBase::getHeadTopPosP()
{
    return getModel()->getHeadTopPosP();
}

sead::Vector3f* PlayerBase::getHeadPosP()
{
    return mpModelBaseMgr->getHeadPosP();
}

bool PlayerBase::vf154()
{
    if (isStatus(cStatus_210))
        return false;

    if (isStatus(cStatus_122))
        return false;

    if (isStatus(cStatus_280))
        return false;

    if (_2a4 == 0 && isStatus(cStatus_SceneChangeNext))
        return false;

    return true;
}

void PlayerBase::setMaskPosInterpType(s32 src_type)
{
    mMaskPosInterpSrcType = src_type;
    mMaskPosInterpTimer = 3;
}

void PlayerBase::dokanAdjustMaskPos(sead::Vector3f& mask_pos)
{
    if (!isStatus(cStatus_210))
        return;

    switch (mDokanDir)
    {
    case cDokanDir_Up:
        {
            f32 y = mask_pos.y;
            if (y > mDokanPosPrev.y)
                y = mDokanPosPrev.y;
            mask_pos.y = y;
        }
        break;
    case cDokanDir_Down:
        {
            f32 y = mask_pos.y;
            if (y < mDokanPosPrev.y)
                y = mDokanPosPrev.y;
            mask_pos.y = y;
        }
        break;
    case cDokanDir_Left:
        {
            f32 x = mask_pos.x;
            if (x < mDokanPosPrev.x)
                x = mDokanPosPrev.x;
            mask_pos.x = x;
        }
        break;
    case cDokanDir_Right:
        {
            f32 x = mask_pos.x;
            if (x > mDokanPosPrev.x)
                x = mDokanPosPrev.x;
            mask_pos.x = x;
        }
        break;
    }
}

bool PlayerBase::checkRideActor(PlayerBase* p_player_other)
{
    if (mRideActorID == p_player_other->getActorUniqueID())
        return true;

    if (p_player_other->mRideActorID == getActorUniqueID())
        return true;

    return false;
}

void PlayerBase::setRideNat(f32 value)
{
    onStatus(cStatus_RideNat);
    mRideNatPosY = value;
}

void PlayerBase::updateRideNat()
{
    if (isStatus(cStatus_RideNat) && mSpeed.y <= 0.0f)
    {
        if (!isStatus(cStatus_RideNatDone) && mPos.y <= mRideNatPosY)
            onStatus(cStatus_RideNatDone);
    }
    else
    {
        offStatus(cStatus_RideNatDone);
    }
}

void PlayerBase::onFollowMameKuribo()
{
    onStatus(cStatus_FollowMameKuribo);
    mFollowMameKuribo++;
}

s32 PlayerBase::getFollowMameKuribo()
{
    return mFrameEndFollowMameKuribo;
}

#define FOLLOW_MAME_KURIBO_TYPE_NUM 5

s32 PlayerBase::getFollowMameKuriboSpeedType()
{
    return sead::Mathi::clamp2(0, getFollowMameKuribo() - 1, FOLLOW_MAME_KURIBO_TYPE_NUM - 1);
}

f32 PlayerBase::getFollowMameKuriboSpeedScaleX()
{
    if (!isStatus(cStatus_FollowMameKuribo))
        return 1.0;

    static const f32 ratios[] = {
        0.60f,
        0.55f,
        0.50f,
        0.45f,
        0.40f
    };
    static_assert((sizeof(ratios) / sizeof(f32)) == FOLLOW_MAME_KURIBO_TYPE_NUM);

    return ratios[getFollowMameKuriboSpeedType()];
}

f32 PlayerBase::getFollowMameKuriboSpeedScaleY()
{
    if (!isStatus(cStatus_FollowMameKuribo))
        return 1.0;

    static const f32 ratios[] = {
        0.84f,
        0.81f,
        0.78f,
        0.75f,
        0.72f
    };
    static_assert((sizeof(ratios) / sizeof(f32)) == FOLLOW_MAME_KURIBO_TYPE_NUM);

    return ratios[getFollowMameKuriboSpeedType()];
}

void PlayerBase::reduceCoinNum_(s32 coin_num)
{
    FieldGameData* p_game_data = CourseTask::instance()->getGameData();
    if (p_game_data != nullptr)
        p_game_data->setPlayerCoinNum(
            mPlayerNo,
            p_game_data->getPlayerCoinNum(mPlayerNo) - coin_num
        );
}

s32 PlayerBase::adjustCoinReductionNumCB_(s32 coin_num)
{
    const FieldGameData* p_game_data = CourseTask::instance()->getGameData();

    if (CourseTask::instance()->getGameMode() == FieldGameMode::cCoinBattle)
    {
        s32 coin_num_self = 0;
        if (p_game_data != nullptr)
            coin_num_self = p_game_data->getPlayerCoinNum(mPlayerNo);

        if (coin_num > coin_num_self)
            coin_num = coin_num_self;

        return coin_num;
    }
    else
    {
        return 0;
    }
}

void PlayerBase::coinJumpOnStampCB(s32 coin_num)
{
    coin_num = adjustCoinReductionNumCB_(coin_num);
    if (coin_num == 0)
        return;

    reduceCoinNum_(coin_num);

    ActorCoinMgr::CoinJumpArg arg;
    arg.pos = getCenterPos();
    arg.dir = mDirection;
    arg.count = coin_num;
    arg.layer = cLayerID_Layer1;
    arg.spawn_height = 0;
    arg._13 = 0;
    arg.spacing_decrease = 0;
    arg._15 = 0;
    arg.curve_type = 0;
    ActorCoinMgr::instance()->spawnCoinJump(arg, true, mPlayerNo);
}

static inline s32 GetBaseDamageCoinNumCB(s32 type, s32 diff_from_min)
{
    s32 coin_num = 0;
    if (type == 0)
    {
        if (diff_from_min >= 50)
            coin_num = 10;
        else if (diff_from_min >= 30)
            coin_num = 5;
        else if (diff_from_min >= 10)
            coin_num = 3;
        else if (diff_from_min > 0)
            coin_num = 1;
    }
    else
    {
        if (diff_from_min >= 50)
            coin_num = 20;
        else if (diff_from_min >= 30)
            coin_num = 10;
        else if (diff_from_min >= 10)
            coin_num = 5;
        else if (diff_from_min > 0)
            coin_num = 2;
        else
            coin_num = 1;
    }
    return coin_num;
}

void PlayerBase::coinFunsuiOnDamageCB(s32 type, Actor* p_eat_die_actor)
{
    const FieldGameData* p_game_data = CourseTask::instance()->getGameData();

    if (CourseTask::instance()->getGameMode() != FieldGameMode::cCoinBattle)
        return;

    s32 coin_num_self = 0;
    if (p_game_data != nullptr)
        coin_num_self = p_game_data->getPlayerCoinNum(mPlayerNo);

    s32 diff_from_min = coin_num_self - PlayerMgr::instance()->getCoinNumMin();

    s32 coin_num = adjustCoinReductionNumCB_(GetBaseDamageCoinNumCB(type, diff_from_min));
    if (coin_num == 0)
        return;

    reduceCoinNum_(coin_num);

    sead::Vector3f funsui_pos = getCenterPos();
    s32 funsui_angle_type = 0; // Angle = value * 22.5 + 45 degrees
    f32 screen_left = BgScrollMgr::instance()->getScreenLeft() - 16.0f;
    f32 screen_right = BgScrollMgr::instance()->getScreenRight() + 16.0f;
    if (type == 2)
    {
        if (funsui_pos.x < screen_left)
            funsui_angle_type = 2;
        else
            funsui_angle_type = 1;

        if (funsui_pos.x > screen_right)
            funsui_angle_type = 3;
    }
    {
        f32 x = funsui_pos.x;
        if (x < screen_left)
            x = screen_left;
        else if (x > screen_right)
            x = screen_right;
        funsui_pos.x = x;
    }
    f32 screen_bottom = BgScrollMgr::instance()->getScreenBottom() - 16.0f;
    {
        f32 y = funsui_pos.y;
        if (y < screen_bottom)
            y = screen_bottom;
        funsui_pos.y = y;
    }
    ActorCoinMgr::instance()->spawnCoinSpringFunsui(funsui_pos, mPlayerNo, coin_num, funsui_angle_type, p_eat_die_actor);
}

void PlayerBase::calcTimerProc()
{
    MathUtil::calcTimer(&_205c);
    if (_205c < 60)
    {
        if (_205c & 4)
            onStatus(cStatus_HideTemporarily);
    }
    else
    {
        if (_205c & 8)
            onStatus(cStatus_HideTemporarily);
    }

    MathUtil::calcTimer(&_2060);
    MathUtil::calcTimer(&_2064);
    MathUtil::calcTimer(&_2068);
    MathUtil::calcTimer(&_206c);
    MathUtil::calcTimer(&_2070);
    MathUtil::calcTimer(&mNoGravityTimer);
    MathUtil::calcTimer(&_2134);
    MathUtil::calcTimer(&_209c);
    MathUtil::calcTimer(&_20a0);
    MathUtil::calcTimer(&_21e0);
    MathUtil::calcTimer(&_21e8);
    MathUtil::calcTimer(&_21d8);
    MathUtil::calcTimer(&_214c);
    MathUtil::calcTimer(&_1bb4);
    MathUtil::calcTimer(&mPenguinSlideCooldown);

    updateNoHitPlayer();
    calcNoHitObjBgTimer();
}

void PlayerBase::startQuakeShock(Quake::ShockType shock_type)
{
    Quake::instance()->shockMotor(mPlayerNo, shock_type);
}

void PlayerBase::startPatternRumble(const char* pattern)
{
    Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_4);
}

const PlayerModelBase* PlayerBase::getModel() const
{
    return mpModelBaseMgr->getModelBase();
}

void PlayerBase::getAnkleCenterPos(sead::Vector3f* p_pos)
{
    sead::Vector3f ankle_l;
    mpModelBaseMgr->getJointPos(&ankle_l, "ankle_l1");

    mpModelBaseMgr->getJointPos(p_pos, "ankle_r1");

    p_pos->x = (ankle_l.x + p_pos->x) * 0.5f;
    p_pos->y = (ankle_l.y + p_pos->y) * 0.5f;
    p_pos->z = (ankle_l.z + p_pos->z) * 0.5f;
}

f32 PlayerBase::getThrowSpeed()
{
    f32 throw_speed = mAddSpeedF;
    if (isNowBgCross(cBgCross_IsFoot))
        throw_speed = mPosDelta.x;
    return throw_speed;
}

f32 PlayerBase::getThrowLoopPosX(f32 x)
{
    if (AreaTask::instance()->getLoopType() == 0)
        return x;

    f32 area_w = AreaTask::instance()->getBound().getSizeX();
    if (sead::Mathf::abs(x - mPos.x) <= area_w * 0.5f)
        return x;

    if (x < mPos.x)
        return x + area_w;
    else
        return x - area_w;
}

void PlayerBase::calcAirDriftSpeedF()
{
    if (!isNowBgCross(cBgCross_IsFoot))
        sead::Mathf::chase(&mAirDriftSpeedF, 0.0f, mAirDriftSpeedFDecelStep);
    
    else
    {
        mAirDriftSpeedF = 0.0f;
        mAirDriftSpeedFStart = 0.0f;
    }
}

void PlayerBase::posMoveAnglePenguin(const sead::Vector3f& speed)
{
    sead::Vector2f saka_move_speed(0.0f, speed.y);
    if (isNowBgCross(cBgCross_IsHead) && speed.y > 0.0f)
    {
        Angle angle = mBgCheckPlayer.getHeadSakaAngle(mDirection);
        if (angle > 0)
            saka_move_speed.x = speed.y * sead::Mathf::sinIdx(angle);
        saka_move_speed.y = speed.y * sead::Mathf::abs(sead::Mathf::cosIdx(angle));
    }
    if (isNowBgCross(cBgCross_IsFoot) && speed.y < 0.0f)
    {
        Angle angle = mBgCheckPlayer.getSakaAngle(mDirection);
        if (angle < 0)
        {
            if (sead::Mathf::abs(speed.x) > 0.0f)
                if (speed.x > 0.0f)
                    saka_move_speed.x = speed.y * sead::Mathf::sinIdx(angle);
                else
                    saka_move_speed.x = -speed.y * sead::Mathf::sinIdx(angle);
            saka_move_speed.y = speed.y * sead::Mathf::abs(sead::Mathf::cosIdx(angle));
        }
    }

    Angle saka_angle;
    if (isNowBgCross(cBgCross_IsHead))
        saka_angle = mBgCheckPlayer.getHeadSakaBaseAngle();
    else
        saka_angle = mBgCheckPlayer.getSakaBaseAngle();
    f32 saka_sin_v, saka_cos_v;
    sead::Mathf::sinCosIdx(&saka_sin_v, &saka_cos_v, saka_angle);
    saka_cos_v = sead::Mathf::abs(saka_cos_v);

    sead::Vector2f delta(
        speed.x * saka_cos_v,
        speed.x * saka_sin_v
    );
    if (delta.y < 0.0f)
        delta.y = 0.0f;

    delta += saka_move_speed;
    posMove_(delta, speed.z);
}

void PlayerBase::posMoveAnglePlayer(const sead::Vector3f& speed)
{
    sead::Vector3f base_speed(speed);
    if ((base_speed.x > 0.0f && isNowBgCross(cBgCross_IsWallTouchR)) ||
        (base_speed.x < 0.0f && isNowBgCross(cBgCross_IsWallTouchL)))
    {
        if (sead::Mathf::abs(base_speed.x) > 2.5f)
            base_speed.x = base_speed.x > 0.0f ? 2.5f : -2.5f;
    }

    if (isStatus(cStatus_98) || isStatus(cStatus_97))
    {
        posMoveAnglePenguin(base_speed);
        return;
    }

    Angle wall_move_angle = 0;
    if (isStatus(cStatus_36))
        wall_move_angle = mWallAngle + (s32)sead::Mathi::cQuarterRoundIdx;
    f32 wall_move_sin_v, wall_move_cos_v;
    sead::Mathf::sinCosIdx(&wall_move_sin_v, &wall_move_cos_v, wall_move_angle);
    wall_move_cos_v = sead::Mathf::abs(wall_move_cos_v);

    sead::Vector2f wall_move_speed(
        -(base_speed.y * wall_move_sin_v),
          base_speed.y * wall_move_cos_v
    );

    Angle saka_angle;
    if (isNowBgCross(cBgCross_IsHead))
        saka_angle = mBgCheckPlayer.getHeadSakaBaseAngle();
    else
        saka_angle = mBgCheckPlayer.getSakaBaseAngle();
    f32 saka_sin_v, saka_cos_v;
    sead::Mathf::sinCosIdx(&saka_sin_v, &saka_cos_v, saka_angle);
    saka_cos_v = sead::Mathf::abs(saka_cos_v);

    sead::Vector3f delta(
        base_speed.x * saka_cos_v + wall_move_speed.x,
        base_speed.x * saka_sin_v + wall_move_speed.y,
        base_speed.z
    );
    posMove_(delta);
}

void PlayerBase::calcPlayerSpeedXY()
{
    if (_209c != 0)
    {
        if (isNowBgCross(cBgCross_IsFoot))
        {
            mSpeed.y += mAccelY;
            mPos.y += mSpeed.y;
        }
        return;
    }

    f32 speed_rev = 0.0f;
    bool cc_rev = calcCcPlayerRev(&speed_rev);

    f32 target_speedF = mSpeedFMax;
    f32 scale_accelF = 1.0f;

    if (isStatus(cStatus_FollowMameKuribo))
        target_speedF *= getFollowMameKuriboSpeedScaleX();

    if (cc_rev)
    {
        if (target_speedF < -0.5f)
            target_speedF = -0.5f;
        else if (target_speedF > 0.5f)
            target_speedF = 0.5f;

        scale_accelF = (sead::Mathf::abs(target_speedF) < sead::Mathf::abs(mSpeedF)) ? 1.0f : 1.8f;
    }

    calcSpeedF_(mAccelF * scale_accelF, target_speedF);
  //calcWindSpeed(); // Removed in NSMBU

    f32 speedF = mSpeedF;
    if (!isStatus(cStatus_147))
    {
        if (speedF < -5.0f)
            speedF = -5.0f;
        else if (speedF > 5.0f)
            speedF = 5.0f;
    }
    mSpeed.x = speedF;

    if (mSpeed.x * speed_rev >= 0.0f)
    {
        sead::Vector3f wall_check_pos(
            mPos.x + mSpeed.x + speed_rev,
            mPos.y + mCenterOffsetY * 0.5f,
            mPos.z
        );
        f32 hit_pos_x;
        if (mBgCheckPlayer.checkWall(wall_check_pos, mSpeed.x + speed_rev, &hit_pos_x))
            speed_rev = 0.0f;
    }

    f32 speed_x = speed_rev;

    f32 base_add_speedF = mAddSpeedF;
    if (base_add_speedF != 0.0f)
    {
        if (!isNowBgCross(cBgCross_IsFoot))
        {
            speed_x += base_add_speedF;
            if (isStatus(cStatus_11) && _1bb4 == 0)
            {
                MathUtil::addCalc(&base_add_speedF, 0.0f, 0.1f, 0.1f, 0.01f);
                mAddSpeedF = base_add_speedF;
            }
        }
        else
        {
            if (getPowerChangeType(false) != 1)
            {
                f32 add_speedF = base_add_speedF;
                if (add_speedF * mSpeedF >= 0.0f)
                    add_speedF *= isStatus(cStatus_131) ? 0.0f : 0.15f;
                mSpeedF += add_speedF;
            }
            mAddSpeedF = 0.0f;
            offStatus(cStatus_11);
            _1bb4 = 120;
        }
    }

    calcAirDriftSpeedF();
    speed_x += mAirDriftSpeedF;

    setSandEffect();

    getPos2D() += mBgSpeed;

    if (isNowBgCross(cBgCross_IsFoot) && isStatus(cStatus_244))
        mSpeedF = 0.0f;

    _4c8 = mSpeed;
    mSpeed.y += mAccelY;

    f32 fall_speed_max = mFallSpeedMax; // Negative
    if (isNowBgCross(cBgCross_IsSlightlyInsideSinkSand) || isNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand))
        fall_speed_max = 0.0f;

    if (mSpeed.y < fall_speed_max)
        mSpeed.y = fall_speed_max;

    sead::Vector3f speed(
        mSpeed.x + speed_x,
        mSpeed.y,
        mSpeed.z
    );
    posMoveAnglePlayer(speed);
}

void PlayerBase::initAirDriftSpeedF(f32 start_val, f32 len_frames)
{
    if (!(start_val * mSpeedF >= 0.0f))
        return;

    f32 val_mag = sead::Mathf::abs(start_val);
    if (val_mag < 1.0f)
    {
        if (val_mag <= 0.1f)
            return;

        start_val = (start_val > 0.0f) ? 1.0f : -1.0f;
    }

    mAirDriftSpeedF = start_val;
    mAirDriftSpeedFStart = 0.0f;
    mPos.x += start_val;
    mAirDriftSpeedFDecelStep = sead::Mathf::abs(start_val / len_frames);
}

bool PlayerBase::setJump(u8 param, JumpSe jump_se_type)
{
    if (!isNowBgCross(cBgCross_IsUnderwater) && !isStatus(cStatus_146))
    {
        if ((mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Main) >> PlayerModelBase::cAnmFlagBit_0 & 1) && checkStandUpRoof())
            return setCrouchJump();

        if (mPlayerKey.triggerJump())
        {
            JumpInf jmp_inf;
            jmp_inf.speed_y = 0.0f;
            jmp_inf.jump_se_type = jump_se_type;
            jmp_inf._8 = param;
            changeState(StateID_Jump, jmp_inf);
            return true;
        }
    }
    return false;
}

bool PlayerBase::setDelayHelpJump()
{
    if (mPlayerKey.triggerJump() && sead::Mathf::abs(mSpeedF) > 1.3f && checkOldBgCrossFoot(2))
    {
        if (setJump(1, cJumpSe_Normal))
            return true;
    }
    return false;
}

bool PlayerBase::checkJumpTrigger()
{
    if (isNowBgCross(cBgCross_IsFoot) && !isNowBgCross(cBgCross_IsKani))
    {
        if (setJump(1, cJumpSe_Normal))
            return true;
    }
    return false;
}

void PlayerBase::clearTreadCount()
{
    SubjectMgr::instance()->onPlFumiCntClr();
    mTreadCnt = 0;
}

s8 PlayerBase::calcTreadCount(s32 max)
{
    if (mTreadCnt < max)
        mTreadCnt++;
    return mTreadCnt;
}

s8 PlayerBase::calcComboCount(s32 max)
{
    if (mComboCnt < max)
        mComboCnt++;
    return mComboCnt;
}

const f32 PlayerBase::cDirSpeed[] = { 1.0f, -1.0f };
const f32 PlayerBase::cJumpSpeed = 3.628f;
const f32 PlayerBase::cUnkZero = 0.0f;
const f32 PlayerBase::cWaterNumaJumpSpeed = 0.75f;
const f32 PlayerBase::cMaxFallSpeed = -4.0f;
const f32 PlayerBase::cMaxFallSpeed_Foot = -2.0f;
const f32 PlayerBase::cTurnPowerUpRate = 3.0;
const f32 PlayerBase::cWaterCancelCrouchAnmSpeed = 0.1f;
