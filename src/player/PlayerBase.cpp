#include <enemy/Enemy.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>
#include <utility/Timer.h>

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
    , _4e0(0)
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
    , _1b10(0.0f)
    , mSakaType(ActorBgCollisionCheck::SakaType(0))
    , mSakaAngle()
    , _1b1c()
    , _1b20()
    , _1b24()
    , _1b28(0.0f, 0.0f, 0.0f)
    , mBgAttr(cBgAttr_Rock)
    , _1b38()
    , mWaterTopPosY(0.0f)
    , mWaterTopPosY2(0.0f)
    , mWaterType(cWaterType_None)
    , mWaterDepthType(0)
    , mAirWaterHitPos(0.0f, 0.0f, 0.0f)
    , mAirWaterHitAngle()
    , mSinkSandSurfacePosY(0.0f)
    , _1b60(0.0f, 0.0f)
    , _1b68(0.0f, 0.0f)
    , _1b70(0.0f)
    , _1b74(16.0f)
    , _1b78(0)
    , _1b7c(0)
    , mBgPressIDBuffer()
    , mLineSpinLiftID()
    , _1b9c(0)
    , mNoHitObjBgTimer(0)
    , _1ba4(0.0f)
    , _1ba8(0.0f)
    , _1bac(0.0f)
    , _1bb0(0.0f)
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
    , _2074(0.0f)
    , _2078(0.0f)
    , _207c(0.0f)
    , _2080(0.0f)
    , _2084(0)
    , _2085(0)
    , mNoHitPlayerTimer(0)
    , mNoHitPlayerID()
    , _2090(0)
    , _2094(0)
    , _2098(0.0f)
    , _209c(0)
    , _20a0(0)
    , _20a4()
    , _20ac()
    , mDemoStateMgr(*this)
    , mChangeDemoStateParam(0)
    , mDemoTypeFlag()
    , mDemoMode(0)
    , mDemoAction(0)
    , _20e8(0)
    , _20ec(0)
    , mPlayerJumpDaiID(0)
    , mDstNextGotoID(0)
    , mNextGotoType(0)
    , _20fc(0)
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
    , _2180(0)
    , _2184(0)
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
    , mRideNat(0.0f)
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

    offStatus(cStatus_171);

    if (mSpeed.y <= 0.0f)
        offStatus(cStatus_10);

    CalcTimer<s32>(&_2a4);

    return true;
}

bool PlayerBase::execute_()
{
    CalcTimer<s32>(&mExecuteFreezeTimer);
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
    mFrameEndFollowMameKuribo = mFollowMameKuribo;
    mFollowMameKuribo = 0;
    offStatus(cStatus_174);
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
    CalcTimer<s32>(&mMaskPosInterpTimer);

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
        offStatus(cStatus_128);
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
            mBgCheckPlayer.reset();
        offStatus(cStatus_250);

        if (isStatus(cStatus_153) && isStatus(cStatus_7))
            onStatus(cStatus_2);

        clearFollowMameKuribo();
        clearCcPlayerRev();
        clearCcData();

        if (!isStatus(cStatus_9))
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
