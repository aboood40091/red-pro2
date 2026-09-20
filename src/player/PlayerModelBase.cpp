#include <graphics/AnimModel.h>
#include <graphics/Renderer.h>
#include <graphics/SkeletalAnimation.h>
#include <input/InputMgr.h>
#include <player/PlayerHIO_Anm.h>
#include <player/PlayerModelBase.h>
#include <system/RDashMgr.h>

#include <random/seadGlobalRandom.h>

const sead::SafeString PlayerModelBase::cJumpAnmVarDt[] = {
    "jump", "jump_b", "jump_c"
};

const sead::SafeString PlayerModelBase::c2JumpAnmVarDt[] = {
    "2jmp_c_1", "2jump1", "2jmp_b_1"
};

const sead::SafeString PlayerModelBase::c2JumpedAnmVarDt[] = {
    "2jmp_c_2", "2jump2", "2jmp_b_2"
};

PlayerModelBase::PlayerModelBase(const sead::SafeString& model_res_key, const sead::SafeString& anm_res_key)
    : sead::IDisposer()
    , mpModelRes(ModelResourceMgr::instance()->getResource(model_res_key))
    , mpAnmRes(ModelResourceMgr::instance()->getResource(anm_res_key))
    , mpModel(nullptr)
    , mAnm(PlayerAnmID::cInvalid)
    , mBodyAnm(PlayerAnmID::cInvalid)
    , mRideAnm(PlayerAnmID::cInvalid)
    , mpLinkPlayer(nullptr)
    , mHeadTopPos(0.0f, 0.0f, 0.0f)
    , mHeadPos(0.0f, 0.0f, 0.0f)
    , mType(cType_Mario)
    , mSceneType(cSceneType_Course)
    , mTexAnmType(cTexAnmType_WaitStatic)
    , mDefaultExpressionTimer(0)
    , mOffsetY(0.0f)
    , mStoopOffsetCurrent(0.0f)
    , mStoopOffsetTarget(0.0f)
    , mStoopOffsetBlendFramesRemaining(0.0f)
    , mFlag()
    , mJumpIndex(0)
    , mJumpIndexPrev(0)
    , mFaceAngleOverride()
    , mFaceAngleOverrideFlag()
    , mCarryStateChanged(false)
{
    mAnmFlag.fill(0);
    mMtxSrt.makeIdentity();
    mMtxSr.makeIdentity();
}

PlayerModelBase::~PlayerModelBase()
{
}

bool PlayerModelBase::isCourseSelectScene()
{
    return mSceneType == cSceneType_CourseSelect;
}

u32 PlayerModelBase::rndInt(u32 max)
{
    if (mSceneType == cSceneType_Course)
        return GAME_RANDOM.getU32(max);
    else
        return sead::GlobalRandom::instance()->getU32(max);
}

f32 PlayerModelBase::getAnmRate(s32 anm_id)
{
    return PlayerHIO_Anm::cData[anm_id].rate;
}

f32 PlayerModelBase::getAnmBlendDuration(s32 anm_id)
{
    return PlayerHIO_Anm::cData[anm_id].blend_duration;
}

void PlayerModelBase::setAnm(s32 anm_id, f32 rate, f32 blend_duration, f32 frame)
{
    if (!mCarryStateChanged && mAnm == anm_id)
    {
        setRate(rate);
        if (frame != 0.0f)
            setFrame(frame);
        return;
    }

    s32 prev_anm_id = mAnm;
    mRideAnm = PlayerAnmID::cInvalid;
    mAnm = anm_id;

    const PlayerAnmData& anm_data = PlayerHIO_Anm::cData[anm_id];

    mAnmFlag[cAnmFlagType_Main] = anm_data.flag;
    mAnmFlag[cAnmFlagType_Body] = anm_data.flag;

    ModelResource* p_anm_res = mpAnmRes;
    sead::FixedSafeString<32> anm_name(anm_data.normal);
    setPersonalAnm(&p_anm_res, &anm_name, anm_id, false);

    FrameCtrl::PlayMode play_mode = anm_data.play_mode;

    if (frame == 0.0f &&
        isAnmFlagBit(cAnmFlagBit_6) &&
        prev_anm_id != PlayerAnmID::cInvalid && (PlayerHIO_Anm::cData[prev_anm_id].flag & 1 << cAnmFlagBit_6))
    {
        frame = getFrame();
    }

    if (isCarry())
    {
        if (isLiftUp())
            setLinkAnm(anm_id, rate, blend_duration, frame);

        if (!isCarryAnm() || isBubbleChibiYoshiShake())
        {
            setFootAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
            setCarryBodyAnm(blend_duration, false);
            return;
        }
    }

    if ((mFlag.isOn(cFlag_Bit5) || mFlag.isOn(cFlag_Bit6)) &&
        mBodyAnm != PlayerAnmID::cInvalid && !isBodyAnmFlagBit(cAnmFlagBit_5))
    {
        setFootAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, 0.0f);
        setBodyAnm(mBodyAnm, getBodyRate(), getBodyFrame());
    }
    else if (isSlopeBodyAnm())
    {
        setFootAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
        setSlopeBodyAnm(blend_duration);
    }
    else
    {
        setFootAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
        mBodyAnm = PlayerAnmID::cInvalid;
        setBodyAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
        setAnmBind();
        setTexAnmType(anm_data.tex_anm_type);
    }
}

void PlayerModelBase::setRate(f32 rate)
{
    setRateDirect(rate);
    if (!isBodyAnmOn())
        setBodyRate(rate);
}

void PlayerModelBase::setFrame(f32 frame)
{
    setFrameDirect(frame);
    if (!isBodyAnmOn())
        setBodyFrame(frame);
}

f32 PlayerModelBase::getFrame()
{
    return getFrameImpl(cSklAnm_Main);
}

bool PlayerModelBase::isCarry()
{
    return isLiftUp() || mFlag.isOn(cFlag_IsCarry);
}

bool PlayerModelBase::isLiftUp()
{
    return mFlag.isOn(cFlag_IsLiftUp) || mFlag.isOn(cFlag_IsBalloonChibiYoshiFly);
}

void PlayerModelBase::setLinkAnm(s32 anm_id, f32 rate, f32 blend_duration, f32 frame)
{
    if (mpLinkPlayer == nullptr)
        return;

    if (mpLinkPlayer->mFlag.isOn(cFlag_Bit9))
        return;

    if (isCarryAnm() || isSwimAnm() || isDirAnm())
        mpLinkPlayer->releaseBodyAnm(blend_duration);
    else
    {
        mpLinkPlayer->mJumpIndex = mJumpIndex;
        mpLinkPlayer->setBodyAnm(anm_id, rate, frame, blend_duration);
    }
}

f32 PlayerModelBase::getBodyRate()
{
    return getRateImpl(cSklAnm_Body);
}

f32 PlayerModelBase::getRateImpl(s32 skl_anm_idx)
{
    return mpModel->getSklAnim(skl_anm_idx)->getFrameCtrl().getRate();
}

void PlayerModelBase::setSlopeBodyAnm(f32 blend_duration)
{
    s32 anm_id = mAnm == PlayerAnmID::slope_waitR ? PlayerAnmID::slope_waitR2 : PlayerAnmID::slope_waitL2;
    setBodyAnm(anm_id, PlayerHIO_Anm::cData[anm_id].rate, 0.0f, blend_duration);
}

void PlayerModelBase::setBodyAnm(s32 anm_id, f32 rate, f32 frame, f32 blend_duration)
{
    mBodyAnm = anm_id;

    const PlayerAnmData& anm_data = PlayerHIO_Anm::cData[anm_id];

    mAnmFlag[cAnmFlagType_Body] = anm_data.flag;

    ModelResource* p_anm_res = mpAnmRes;
    sead::FixedSafeString<32> anm_name(anm_data.normal);
    setPersonalAnm(&p_anm_res, &anm_name, mBodyAnm, true);

    FrameCtrl::PlayMode play_mode = anm_data.play_mode;

    setBodyAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
    setAnmBind();
    setTexAnmType(anm_data.tex_anm_type);
}

void PlayerModelBase::copyLinkAnm(f32 blend_duration)
{
    setLinkAnm(mAnm, getRate(), blend_duration, getFrame());
}

f32 PlayerModelBase::getRate()
{
    return getRateImpl(cSklAnm_Main);
}

void PlayerModelBase::setRideAnm(s32 anm_id, f32 rate, f32 blend_duration, f32 frame)
{
    s32 prev_anm_id = mRideAnm;
    mAnm = PlayerAnmID::cInvalid;
    mRideAnm = anm_id;

    const PlayerAnmData& anm_data = PlayerHIO_Anm::cData[anm_id];

    if (anm_id == prev_anm_id)
    {
        setRate(rate);
        if (frame != 0.0f)
            setFrame(frame);
        return;
    }

    mAnmFlag[cAnmFlagType_Main] = 0;
    mAnmFlag[cAnmFlagType_Body] = 0;

    ModelResource* p_anm_res = mpAnmRes;
    sead::FixedSafeString<32> anm_name(anm_data.normal);
    if (!anm_data.ride.isEmpty())
    {
        anm_name = anm_data.ride;
        setPersonalRideAnm(&p_anm_res, &anm_name, anm_id);
    }

    FrameCtrl::PlayMode play_mode = anm_data.play_mode;

    setFootAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
    mBodyAnm = PlayerAnmID::cInvalid;
    setBodyAnmImpl(p_anm_res, anm_name, play_mode, rate, frame, blend_duration);
    setAnmBind();
    setTexAnmType(anm_data.tex_anm_type);
}

bool PlayerModelBase::getJumpAnmName(sead::BufferedSafeString* p_anm_name, s32 anm_id, bool body)
{
    static_assert(sizeof(cJumpAnmVarDt) / sizeof(sead::SafeString) == cJumpMax);
    static_assert(sizeof(c2JumpAnmVarDt) / sizeof(sead::SafeString) == cJumpMax);
    static_assert(sizeof(c2JumpedAnmVarDt) / sizeof(sead::SafeString) == cJumpMax);

    bool is_jump_anm = false;
    if (body)
    {
        if (isJumpBodyAnm())
            is_jump_anm = true;
    }
    else
    {
        if (isJumpAnm())
            is_jump_anm = true;
    }
    if (is_jump_anm)
    {
        switch (anm_id)
        {
        default:
            break;
        case PlayerAnmID::jump:
            p_anm_name->copy(cJumpAnmVarDt[mJumpIndex]);
            break;
        case PlayerAnmID::_2jmp_c_1:
            p_anm_name->copy(c2JumpAnmVarDt[mJumpIndex]);
            break;
        case PlayerAnmID::_2jmp_c_2:
            p_anm_name->copy(c2JumpedAnmVarDt[mJumpIndex]);
            break;
        }
        return true;
    }
    else
    {
        mJumpIndexPrev = mJumpIndex;
        mJumpIndex = 0;
        return false;
    }
}

void PlayerModelBase::setJumpAnmRand(RndType rnd_type)
{
    switch (rnd_type)
    {
    default:
        break;
    case cRndType_Uniform:
        mJumpIndex = rndInt(cJumpMax);
        break;
    case cRndType_RightSkew:
        {
            s32 rnd = rndInt(10);
            if (rnd < 6)
                mJumpIndex = 0;
            else if (rnd < 9)
                mJumpIndex = 1;
            else
                mJumpIndex = 2;
        }
        break;
    }
    if (!(0 <= mJumpIndex && mJumpIndex < cJumpMax))
        mJumpIndex = 0;
}

f32 PlayerModelBase::getRateDirect()
{
    return getRateImpl(cSklAnm_Main);
}

void PlayerModelBase::setRateDirect(f32 rate)
{
    setRateImpl(cSklAnm_Main, rate);
}

void PlayerModelBase::setRateImpl(s32 skl_anm_idx, f32 rate)
{
    SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(skl_anm_idx);
    f32 rate_prev = p_skl_anm->getFrameCtrl().getRate();
    p_skl_anm->getFrameCtrl().setRate(rate);
    if (rate_prev * rate <= 0.0f)
    {
        f32 frame = p_skl_anm->getFrameCtrl().getFrame();
        p_skl_anm->getFrameCtrl().reset();
        p_skl_anm->getFrameCtrl().setFrame(frame);
    }
}

void PlayerModelBase::setBodyRate(f32 rate)
{
    setRateImpl(cSklAnm_Body, rate);
}

bool PlayerModelBase::isAnmStop()
{
    return isAnmStopImpl(cSklAnm_Main);
}

bool PlayerModelBase::isAnmStopImpl(s32 skl_anm_idx)
{
    return mpModel->getSklAnim(skl_anm_idx)->getFrameCtrl().isStop();
}

bool PlayerModelBase::isBodyAnmStop()
{
    return isAnmStopImpl(cSklAnm_Body);
}

f32 PlayerModelBase::getBodyFrame()
{
    return getFrameImpl(cSklAnm_Body);
}

f32 PlayerModelBase::getFrameImpl(s32 skl_anm_idx)
{
    return mpModel->getSklAnim(skl_anm_idx)->getFrameCtrl().getFrame();
}

void PlayerModelBase::setFrameDirect(f32 frame)
{
    setFrameImpl(cSklAnm_Main, frame);
}

void PlayerModelBase::setFrameImpl(s32 skl_anm_idx, f32 frame)
{
    SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(skl_anm_idx);
    p_skl_anm->getFrameCtrl().reset();
    p_skl_anm->getFrameCtrl().setFrame(frame);
}

void PlayerModelBase::setBodyFrame(f32 frame)
{
    setFrameImpl(cSklAnm_Body, frame);
}

bool PlayerModelBase::checkFrame(f32 frame)
{
    return checkFrameImpl(cSklAnm_Main, frame);
}

bool PlayerModelBase::checkFrameImpl(s32 skl_anm_idx, f32 frame)
{
    return mpModel->getSklAnim(skl_anm_idx)->getFrameCtrl().checkFrame(frame);
}

bool PlayerModelBase::checkBodyFrame(f32 frame)
{
    return checkFrameImpl(cSklAnm_Body, frame);
}

bool PlayerModelBase::isAnmLoopFrame()
{
    return isAnmLoopFrameImpl(cSklAnm_Main);
}

bool PlayerModelBase::isAnmLoopFrameImpl(s32 skl_anm_idx)
{
    return mpModel->getSklAnim(skl_anm_idx)->getFrameCtrl().isLoopFrame();
}

bool PlayerModelBase::isBodyAnmLoopFrame()
{
    return isAnmLoopFrameImpl(cSklAnm_Body);
}

f32 PlayerModelBase::getFrameEnd()
{
    return mpModel->getSklAnim(cSklAnm_Main)->getFrameCtrl().getFrameEnd();
}

bool PlayerModelBase::isBodyAnmOn()
{
    if (mBodyAnm == PlayerAnmID::cInvalid)
        return false;
    if (mBodyAnm == mAnm)
        return false;
    return true;
}

void PlayerModelBase::getJointMtx(sead::Matrixf* p_mtx, const sead::SafeString& name)
{
    const Model* p_model = mpModel->getModel();
    s32 index = p_model->searchBoneIndex(name);
    if (index == -1)
        p_model->getBoneWorldMatrix(0, p_mtx);
    else
        getJointMtx(p_mtx, index);
}

void PlayerModelBase::getJointMtx(sead::Matrixf* p_mtx, s32 index)
{
    mpModel->getModel()->getBoneWorldMatrix(index, p_mtx);
}

void PlayerModelBase::getJointPos(sead::Vector3f* p_pos, const sead::SafeString& name)
{
    sead::Matrixf mtx;
    getJointMtx(&mtx, name);
    mtx.getTranslation(*p_pos);
}

void PlayerModelBase::getJointPos(sead::Vector3f* p_pos, s32 index)
{
    sead::Matrixf mtx;
    getJointMtx(&mtx, index);
    mtx.getTranslation(*p_pos);
}

void PlayerModelBase::calc(const sead::Matrixf& mtx)
{
    f32 target;
    switch (mAnm)
    {
    case PlayerAnmID::door_walk:
        target = 1.0f;
        break;
    case PlayerAnmID::low_walk_start:
    case PlayerAnmID::low_walk:
        target = 4.0f;
        break;
    default:
        target = -0.2f;
        break;
    }
    target += mStoopOffsetCurrent;
    if (isOnHDokan())
    {
        if (RDashMgr::instance()->isNSLU())
            target += -1.5f;
        else
            target += -1.0f;
    }
    sead::Mathf::chase(&mOffsetY, target, 1.0f);

    mMtxSrt = mtx;
    mMtxSrt.multTranslationWorld(0.0f, mOffsetY, 0.0f);
    mMtxSrt.scaleBases(getBaseScale());

    mMtxSr = mMtxSrt;
    mMtxSr.setTranslation(sead::Vector3f::zero);

    calcImpl();
}

void PlayerModelBase::calc2()
{
    calc2Impl();
}

void PlayerModelBase::draw()
{
    Renderer::instance()->drawModel(mpModel->getModel());
}

void PlayerModelBase::calcStoopOffset()
{
    sead::Mathf::chase(&mStoopOffsetBlendFramesRemaining, 0.0f, 1.0f);
    if (mStoopOffsetBlendFramesRemaining)
        sead::Mathf::chase(&mStoopOffsetCurrent, mStoopOffsetTarget, sead::Mathf::abs(mStoopOffsetCurrent - mStoopOffsetTarget) / mStoopOffsetBlendFramesRemaining);
    else
        mStoopOffsetCurrent = mStoopOffsetTarget;
}

void PlayerModelBase::reset()
{
    mAnm = PlayerAnmID::cInvalid;
    mTexAnmType = cTexAnmType_WaitStatic;
}

bool PlayerModelBase::isFootStepTiming()
{
    switch (mAnm)
    {
    default:
        break;
    case PlayerAnmID::walk:
    case PlayerAnmID::run:
    case PlayerAnmID::b_dash:
    case PlayerAnmID::b_dash2:
    case PlayerAnmID::carry_walk:
    case PlayerAnmID::carryP_walk:
    case PlayerAnmID::M_run:
    case PlayerAnmID::M_b_dash:
        if (checkFrame(4.0f) || checkFrame(34.0f))
            return true;
        break;
    case PlayerAnmID::door_walk:
        if (checkFrame(3.0f) || checkFrame(18.0f))
            return true;
        break;
    case PlayerAnmID::low_walk:
        if (checkFrame(0.0f) || checkFrame(30.0f))
            return true;
        break;
    case PlayerAnmID::run__YB_RFjump:
        if (checkFrame(0.0f) || checkFrame(15.0f) || checkFrame(30.0f) || checkFrame(45.0f))
            return true;
        break;
    }
    return false;
}

void PlayerModelBase::cancelCarry()
{
    offCarry();
    offLiftUp();
    offBalloonChibiYoshiFly();
    offBubbleChibiYoshiShake();
}

void PlayerModelBase::offCarry()
{
    if (mFlag.isOn(cFlag_IsCarry))
    {
        mCarryStateChanged = true;
        mFlag.reset(cFlag_IsCarry);
    }
}

void PlayerModelBase::offLiftUp()
{
    if (mFlag.isOn(cFlag_IsLiftUp))
    {
        mCarryStateChanged = true;
        mFlag.reset(cFlag_IsLiftUp);
    }
}

void PlayerModelBase::offBalloonChibiYoshiFly()
{
    if (mFlag.isOn(cFlag_IsBalloonChibiYoshiFly))
    {
        mCarryStateChanged = true;
        mFlag.reset(cFlag_IsBalloonChibiYoshiFly);
    }
}

void PlayerModelBase::onCarry()
{
    if (!mFlag.isOn(cFlag_IsCarry))
    {
        mCarryStateChanged = true;
        mFlag.set(cFlag_IsCarry);
    }
}

void PlayerModelBase::onLiftUp()
{
    if (!mFlag.isOn(cFlag_IsLiftUp))
    {
        mCarryStateChanged = true;
        mFlag.set(cFlag_IsLiftUp);
    }
}

void PlayerModelBase::onBalloonChibiYoshiFly()
{
    if (!mFlag.isOn(cFlag_IsBalloonChibiYoshiFly))
    {
        mCarryStateChanged = true;
        mFlag.set(cFlag_IsBalloonChibiYoshiFly);
    }
}
