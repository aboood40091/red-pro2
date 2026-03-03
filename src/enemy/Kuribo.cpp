#include <actor/ActorMgr.h>
#include <actor/ActorStatus.h>
#include <actor/Profile.h>
#include <ami/AmiUtil.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/BalloonHangActor.h>
#include <enemy/Kuribo.h>
#include <game/CourseTask.h>
#include <graphics/Renderer.h>
#include <graphics/TexturePatternAnimation.h>
#include <input/InputMgr.h>
#include <map/Bg.h>
#include <player/PlayerMgr.h>
#include <scroll/BgScrollMgr.h>
#include <utility/MathUtil.h>

// TODO: Ordering of these in .bss is different

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

static const Profile cProfile_Kuribo(TActorFactory<Kuribo>, ProfileInfo::cProfileID_Kuribo, "クリボー", &KuriboBase::cActorCreateInfo, Profile::cFlag_DrawCullCheck | Profile::cFlag_Unk4);
static const Profile cProfile_Kakibo(TActorFactory<Kuribo>, ProfileInfo::cProfileID_Kakibo, "カキボー", &KuriboBase::cActorCreateInfo, Profile::cFlag_DrawCullCheck | Profile::cFlag_Unk4);

const f32 Kuribo::cWalkSpeed[cDirType_NumX] = { Kuribo::getWalkSpeed(), -Kuribo::getWalkSpeed() };

CREATE_STATE_ID(Kuribo, KakiboWalk)
CREATE_STATE_ID(Kuribo, KakiboTurn)

CREATE_STATE_VIRTUAL_ID_OVERRIDE(Kuribo, KuriboBase, Touch)

CREATE_STATE_ID(Kuribo, Down)
CREATE_STATE_ID(Kuribo, Auto_Walk)
CREATE_STATE_ID(Kuribo, Dokan_Down)
CREATE_STATE_ID(Kuribo, BlockAppear)
CREATE_STATE_ID(Kuribo, Born_Split1)
CREATE_STATE_ID(Kuribo, Born_Split2)
CREATE_STATE_ID(Kuribo, EatOut_Ready)
CREATE_STATE_ID(Kuribo, BalloonHang)
CREATE_STATE_ID(Kuribo, KameckIce)

const sead::SafeString Kuribo::cModelName[cModelType_Num] = {
    "kuribo",
    "kakibo"
};

static const ActorBgCollisionCheck::Sensor cBcSensorFoot = { -4.0f, 4.0f,  0.0f };
static const ActorBgCollisionCheck::Sensor cBcSensorHead = {  0.0f, 0.0f, 16.0f };
static const ActorBgCollisionCheck::Sensor cBcSensorWall = {  3.0f, 8.0f,  8.0f };

Kuribo::Kuribo(const ActorCreateParam& param)
    : KuriboBase(param)
    , mKuriboType(0)
    , mKakiboAnm(0)
    , _1a96(0)
    , _1a97(0)
    , mIsKakiboWalk1(false)
    , mWakiTargetPos(0.0f, 0.0f, 0.0f)
    , mWakiDir(cWakiDir_Up)
    , mKakiboBgmHoldTimer(0)
    , mIsFunsui(false)
    , mPreFunsuiSpeedX(0.0f)
    , mGroundDistance(0.0f)
    , mpBalloon(nullptr)
{
}

void Kuribo::setKakiboAnm(KakiboAnmID anm_id)
{
    if (mIsKakiboWalk1)
    {
        if (mpBlendModel->getCurSklAnim()->getFrameCtrl().isEndFrame() || mpBlendModel->getCurSklAnim()->getFrameCtrl().isStop())
        {
            mIsKakiboWalk1 = false;
            mKakiboAnm = cKakiboAnmID_Walk;
        }
    }
    if (mKakiboAnm != anm_id)
    {
        switch (anm_id)
        {
        default:
            break;
        case cKakiboAnmID_Walk0:
            if (!mIsKakiboWalk1)
            {
                mCalcRatio.set(10.0f);

                mpBlendModel->getCurSklAnim()->play(mpModelResource, "walk0");
                mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
                mpBlendModel->getCurSklAnim()->getFrameCtrl().setFrame(0.0f);
                mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(2.0f);
                mWalkAnmRate = 2.0f;

                mpTexAnim->play(mpModelResource, "walk0");
                mpTexAnim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
                mpTexAnim->getFrameCtrl().setFrame(0.0f);
                mpTexAnim->getFrameCtrl().setRate(2.0f);

                mKakiboAnm = anm_id;
            }
            break;
        case cKakiboAnmID_Walk1:
            mCalcRatio.set(10.0f);

            mpBlendModel->getCurSklAnim()->play(mpModelResource, "walk1");
            mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpBlendModel->getCurSklAnim()->getFrameCtrl().setFrame(0.0f);
            mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(2.0f);
            mWalkAnmRate = 2.0f;

            mpTexAnim->play(mpModelResource, "walk1");
            mpTexAnim->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
            mpTexAnim->getFrameCtrl().setFrame(0.0f);
            mpTexAnim->getFrameCtrl().setRate(2.0f);

            mKakiboAnm = anm_id;

            mIsKakiboWalk1 = true;
            break;
        }
    }
}

void Kuribo::createBodyModel_()
{
    mpModelResource = ModelResourceMgr::instance()->getResource(cModelName[mModelType]);
    mpBlendModel = createModel(mpModelResource, cModelName[mModelType], mIsKakibo);
    mpTexAnim = mpBlendModel->getTexAnim(0);
    mpTexAnim->play(mpModelResource, "walk");
    if (mIsKakibo)
        setKakiboAnm(cKakiboAnmID_Walk0);
}

bool Kuribo::checkGroundCreate_()
{
    const BgCollisionCheckParam param = {
        0,                              // _0
        false,                          // ignore_quicksand
        mLayer,                         // layer
        mCollisionMask,                 // collision_mask
        cBgCollisionCheckType_Solid,    // type
        nullptr                         // callback
    };
    sead::Vector2f p0(mPos.x, mPos.y);
    sead::Vector2f p1(mPos.x, mPos.y - 500.0f);
    BasicBgCollisionCheck bg_check(param);
    BgCollisionCheckResultArea res;
    bool ret = bg_check.checkArea(&res, p0, p1, 1 << cDirType_Down);
    if (ret)
        mGroundDistance = mPos.y - res.hit_pos.y;
    return ret;
}

void Kuribo::initialize()
{
    if (getProfileID() == ProfileInfo::cProfileID_Kakibo)
    {
        mIsKakibo = true;
        mModelType = cModelType_Kakibo;
    }
    else
    {
        mModelType = cModelType_Normal;
    }
    createBodyModel_();

    mScale.set(1.0f, 1.0f, 1.0f);

    mBgCheckObj.set(this, &cBcSensorFoot, &cBcSensorHead, &cBcSensorWall);
    mBgCheckObj.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_17);

    mCollisionCheckDrcTouch.setDrcTouchCallback(&mDrcTouchCallback);
    resetCcDrcTouch();

    mVisibleAreaOffset.set(0.0f, 8.0f);
    mVisibleAreaSize.set(16.0f, 16.0f);

    mCenterOffset.set(0.0f, 8.0f, 0.0f);
    mSize.set(16.0f, 16.0f);

    mpEatData = &mEatData;
    mEatData.setEatType(EatData::cEatType_Drink);

    mpChibiYoshiEatData = &mChibiYoshiEatData;
    mChibiYoshiEatData.setEatType(ChibiYoshiEatData::cEatType_Drink);

    mpChibiYoshiAwaData = &mChibiYoshiAwaData;
    mChibiYoshiAwaData.setAwaType(ChibiYoshiAwaData::cAwaType_Catch);

    mKuriboType = mParam0 & 0xF;

    u8 line = (mParam0 >> 16 & 1) ? cCcLineKind_1 : cCcLineKind_0;

    switch (mKuriboType)
    {
    case 1: // Down
        if (!(PlayerMgr::instance()->getNum() > 1))
        {
            mBcSensorFootDown.p1 = 0.0f;
            mBcSensorFootDown.p2 = 0.0f;
            mBcSensorFootDown.center_offset = 0.0f;
            mBgCheckObj.set(this, &mBcSensorFootDown, nullptr, &cBcSensorWall);
        }
        mEnFlag.set(cEnFlag_16);
        changeState(StateID_Down);
        break;
    case 2: // Auto_Walk
        mWakiDir = WakiDir(mParam0 >> 4 & 3);
        mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Enemy);
        mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_ChibiYoshi);
        mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Tama);
        mEnFlag.set(cEnFlag_16);
        changeState(StateID_Auto_Walk);
        break;
    case 3: // BlockAppear
        mPos.z = AmiUtil::getZpos(sead::BitFlag8(line));
        changeState(StateID_BlockAppear);
        break;
    case 4: // Born_Split1
        if (getParent<Actor>() != nullptr)
            mpParentMiddleKuribo = getParent<MiddleKuribo>();
        mPos.z = AmiUtil::getZpos(sead::BitFlag8(line));
        mPos.z += (s32)(GAME_RANDOM.getU32(10) - 5) * 16.0f;
        mDisableScreenOutCheck = mParam0 >> 12 & 1;
        changeState(StateID_Born_Split1);
        break;
    case 5: // Born_Split2
        if (getParent<Actor>() != nullptr)
            mpParentMiddleKuribo = getParent<MiddleKuribo>();
        mPos.z = AmiUtil::getZpos(sead::BitFlag8(line));
        mPos.z += (s32)(GAME_RANDOM.getU32(10) - 5) * 16.0f;
        mDisableScreenOutCheck = mParam0 >> 12 & 1;
        changeState(StateID_Born_Split2);
        break;
    case 6: // EatOut_Ready
        mPos.z = AmiUtil::getZpos(sead::BitFlag8(line));
        changeState(StateID_EatOut_Ready);
        break;
    case 7: // BalloonHang
        mPos.z = 2300.0f;
        changeState(StateID_BalloonHang);
        break;
    case 8: // KameckIce
        if (!(PlayerMgr::instance()->getNum() > 1))
        {
            mBcSensorFootDown.p1 = 0.0f;
            mBcSensorFootDown.p2 = 0.0f;
            mBcSensorFootDown.center_offset = 0.0f;
            mBgCheckObj.set(this, &mBcSensorFootDown, nullptr, &cBcSensorWall);
        }
        mEnFlag.set(cEnFlag_16);
        changeState(StateID_KameckIce);
        break;
    // case 0:
    default:
        if (checkGroundCreate_())
            snapToGround_(mGroundDistance + 16.0f, cBcSensorFoot, false, true);
        mPos.z = AmiUtil::getZpos(sead::BitFlag8(line));
        if (mIsKakibo)
            changeState(StateID_KakiboWalk);
        else
            changeState(StateID_Walk);
        break;
    }

    if (mKuriboType == 2)
    {
        u32 z_order = mParam0 >> 24 & 0xF;
        mZOffset = z_order * 16.0f;
    }

    calcModelBase_();

    mWaterCalcType = cWaterCalcType_EnablePreCheck;

    if (!mIsKakibo)
        ActorStatus::instance()->incKuribo();
    else
        ActorStatus::instance()->incKakibo();
}

void Kuribo::calcModel()
{
    resetCcDrcTouch();
    calcModelBase_();
    mIsDrcTouch = false;
}

void Kuribo::drawModel()
{
    Renderer::instance()->drawModel(mpBlendModel);
}

ActorBase::Result Kuribo::doDelete_()
{
    if (!mIsKakibo)
    {
        ActorStatus::instance()->decKuribo();
        ActorStatus::instance()->validateKuriboNum();
    }
    else
    {
        ActorStatus::instance()->decKakibo();
        ActorStatus::instance()->validateKakiboNum();
    }
    return cResult_Success;
}

void Kuribo::setTurnByEnemyHit(Actor* actor_self, Actor* actor_other)
{
    if (mDirection == cDirType_Left && mEnemyHitRevX > 0.0f || mDirection == cDirType_Right && mEnemyHitRevX < 0.0f)
    {
        if (!isState(StateID_Turn) &&
            !isState(StateID_KakiboTurn) &&
            !isState(StateID_Touch) &&
            !isState(StateID_Born_Split1) &&
            !isState(StateID_Born_Split2) &&
            !isState(StateID_Down))
        {
            if (mIsKakibo)
            {
                mIsKakiboWalk1 = false;
                setKakiboAnm(cKakiboAnmID_Walk0);
                changeState(StateID_KakiboTurn);
            }
            else
            {
                changeState(StateID_Turn);
            }
        }
        else if (isState(StateID_Born_Split1) || isState(StateID_Born_Split2))
        {
            mSpeed.x = 0.0f;
        }
    }
}

void Kuribo::setWalkSpeed()
{
    mSpeed.x = cWalkSpeed[mDirection];
}

void Kuribo::setFrozenAnm()
{
    mpBlendModel->getCurSklAnim()->play(mpModelResource, "frozen");
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setFrame(0.0f);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(0.0f);

    mpTexAnim->getFrameCtrl().setRate(0.0f);
}

bool Kuribo::checkGroundKakibo_(f32 check_dist)
{
    const f32 c_check_dist[cDirType_NumX] = { check_dist, -check_dist };

    Angle angle = mBgCheckObj.getSakaBaseAngle();

    f32 sin_v, cos_v;
    sead::Mathf::sinCosIdx(&sin_v, &cos_v, angle);

    sead::Vector2f check_vec(
        c_check_dist[mDirection] * cos_v,
        c_check_dist[mDirection] * sin_v
    );

    sead::Vector2f p0(
        mPos.x + check_vec.x,
        mPos.y + 10.0f + check_vec.y
    );
    sead::Vector2f p1 = p0;
    p1.y -= 16.0f;

    const BgCollisionCheckParam param = {
        0,                              // _0
        false,                          // ignore_quicksand
        mLayer,                         // layer
        mCollisionMask,                 // collision_mask
        cBgCollisionCheckType_Solid,    // type
        nullptr                         // callback
    };
    BasicBgCollisionCheck bg_check(param);
    return bg_check.checkArea(nullptr, p0, p1, 1 << cDirType_Down);
}

bool Kuribo::checkKakiboTurnSaka_()
{
    if (!mBgCheckObj.checkFoot())
        return false;

    if (checkGroundKakibo_(30.0f)) // 1. Check for ground explicitly in the world down direction
        return false;

    // 2. Check for ground down relative to the surface

    static const f32 c_check_dist_A[cDirType_NumX] = { 36.0f, -36.0f };
    static const f32 c_check_dist_B = 4.0f;

    Angle angle_A = mBgCheckObj.getSakaBaseAngle();                 // Surface tangent angle (i.e., along the surface)
    Angle angle_B = angle_A - s32(sead::Mathi::cQuarterRoundIdx);   // Surface inner normal angle (i.e., down, relative to the surface)

    f32 sin_A, cos_A;
    sead::Mathf::sinCosIdx(&sin_A, &cos_A, angle_A);

    f32 sin_B, cos_B;
    sead::Mathf::sinCosIdx(&sin_B, &cos_B, angle_B);

    sead::Vector2f check_vec_A(
        c_check_dist_A[mDirection] * cos_A,
        c_check_dist_A[mDirection] * sin_A
    );

    sead::Vector2f check_vec_B(
        c_check_dist_B * cos_B,
        c_check_dist_B * sin_B
    );

    sead::Vector2f check_vec = check_vec_A + check_vec_B;

    sead::Vector2f p0(
        mPos.x + check_vec.x,
        mPos.y + check_vec.y
    );
    sead::Vector2f p1;

    sead::Vector2f check_vec_C(
        c_check_dist_A[1 - mDirection] * cos_A,
        c_check_dist_A[1 - mDirection] * sin_A
    );

    p1.setAdd(p0, check_vec_C); // They should've just done p1 = mPos + check_vec_B, but whatever

    const BgCollisionCheckParam param = {
        0,                              // _0
        false,                          // ignore_quicksand
        mLayer,                         // layer
        mCollisionMask,                 // collision_mask
        cBgCollisionCheckType_Solid,    // type
        nullptr                         // callback
    };
    BasicBgCollisionCheck bg_check(param);
    return !bg_check.checkArea(nullptr, p0, p1, 1 << cDirType_Down);
}

bool Kuribo::checkGroundKakiboTurn()
{
    sead::Vector2f p0_R(
        mPos.x + 1.5f,
        mPos.y + 4.0f
    );
    sead::Vector2f p1_R(
        p0_R.x,
        p0_R.y - 6.0f
    );
    sead::Vector2f p0_L(
        mPos.x - 1.5f,
        p0_R.y
    );
    sead::Vector2f p1_L(
        p0_L.x,
        p1_R.y
    );

    if (BgUnitCode::getType(Bg::instance()->getBgCheckData(mPos.x + cWalkSpeed[mDirection], mPos.y - 2.0f, mLayer)) != BgUnitCode::cType_Kani)
    {
        const BgCollisionCheckParam param = {
            0,                              // _0
            false,                          // ignore_quicksand
            mLayer,                         // layer
            mCollisionMask,                 // collision_mask
            cBgCollisionCheckType_Solid,    // type
            nullptr                         // callback
        };

        BasicBgCollisionCheck bg_check_R(param);
        BasicBgCollisionCheck bg_check_L(param);

        BgCollisionCheckResultArea res_R;
        BgCollisionCheckResultArea res_L;

        bool hit_R = bg_check_R.checkArea(&res_R, p0_R, p1_R, 1 << cDirType_Down);
        bool hit_L = bg_check_L.checkArea(&res_L, p0_L, p1_L, 1 << cDirType_Down);

        if (mDirection == cDirType_Right)
        {
            if (hit_R)
            {
                if (MathUtil::absAngle(res_R.hit_angle) > 0x2D160000) // 63.4021 degrees
                {
                    if (!checkKakiboTurnSaka_())
                        return true;
                    return false;
                }
            }
        }
        else
        {
            if (hit_L)
            {
                if (MathUtil::absAngle(res_L.hit_angle) > 0x2D160000) // 63.4021 degrees
                {
                    if (!checkKakiboTurnSaka_())
                        return true;
                    return false;
                }
            }
        }
        if (hit_R && !hit_L || !hit_R && hit_L)
        {
            if ((mDirection == cDirType_Right && hit_R) || (mDirection == cDirType_Left && hit_L))
                return true;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void Kuribo::down()
{
    mBgCheckObj.checkBg();

    switch (_1a96)
    {
    default:
        break;
    case 0:
        if (mPos.y - 16.0f <= BgScrollMgr::instance()->getScreenTop())
            _1a96 = 1;
        break;
    case 1:
        if (mBgCheckObj.checkFoot())
            _1a96 = 2;
        else
            _1a96 = 3;
        break;
    case 2:
        if (!mBgCheckObj.checkFoot())
            _1a96 = 3;
        break;
    case 3:
        if (mBgCheckObj.checkFoot())
        {
            mAngle.x() = 0;
            mSpeed.y = 0.0f;
            if (mIsKakibo)
                changeState(StateID_KakiboWalk);
            else
                changeState(StateID_Walk);
        }
        break;
    }
}

void Kuribo::vsEnemyHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (isState(StateID_BalloonHang))
        return;

    KuriboBase::vsEnemyHitCheck_Normal(cc_self, cc_other);
}

bool Kuribo::hitCallback_HipAttk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_self = cc_self->getOwner();
    if (actor_self != nullptr)
    {
        Kuribo* p_kuribo_self = static_cast<Kuribo*>(actor_self);
        if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
            CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
    }

    bool ret = true;
    if (_1a97 == 0)
        ret = KuriboBase::hitCallback_HipAttk(cc_self, cc_other);
    return ret;
}

bool Kuribo::hitCallback_Spin(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_self = cc_self->getOwner();
    if (actor_self != nullptr)
    {
        Kuribo* p_kuribo_self = static_cast<Kuribo*>(actor_self);
        if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
            CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
    }

    return KuriboBase::hitCallback_Spin(cc_self, cc_other);
}

bool Kuribo::createIceActor()
{
    sead::Vector3f pos(
        mPos.x,
        mPos.y - 2.0f,
        mPos.z
    );
    IceInfo info = { 0, pos, sead::Vector3f(1.2f, 1.2f, 1.2f), nullptr };
    return mIceMgr.createIce(info);
}

void Kuribo::returnState_Ice()
{
    if (isMainState(StateID_Born_Split1) || isMainState(StateID_Born_Split2))
    {
        mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Player);
        _1a97 = 0;
        mDirection = InvDirX(mDirection);
        mAngle.y() = cBaseAngleY[mDirection];
        mSpeed.y = 0.0f;
        setWalkState();
    }
    else if (isMainState(StateID_BalloonHang))
    {
        mDirection = getPlayerDirLR();
        mAngle.y() = cBaseAngleY[mDirection];
        mSpeed.y = 0.0f;
        setWalkState();
    }
    else if (isMainState(StateID_Touch))
    {
        mSpeed.y = 0.0f;
        setWalkState();
    }
    else
    {
        KuriboBase::returnState_Ice();
    }
}

void Kuribo::balloonCollCheck(ActorCollisionCheck* cc_other)
{
    if (cc_other->getKind() == ActorCollisionCheck::cKind_Enemy)
        return;

    if (!isState(StateID_BalloonHang))
        return;

    BalloonHangActor* p_balloon = sead::DynamicCast<BalloonHangActor>(ActorMgr::instance()->getActorPtr(mBalloonID));
    if (p_balloon != nullptr)
        p_balloon->detachChild();
}

void Kuribo::onDrcTouch()
{
    mIsDrcTouch = true;
    mBoyoMgr.begin();
    if (mIsKakibo)
        mKakiboBgmHoldTimer = 30;
    if (mBgCheckObj.checkFoot() || mForceLanded)
    {
        if (!disallowDrcTouchOnGround() && !isState(StateID_Touch))
            changeState(StateID_Touch);
    }
    else
    {
        if (mAllowDrcTouchInAir)
            changeState(StateID_Touch);
    }
}

void Kuribo::resetCcDrcTouch()
{
    mCollisionCheckDrcTouch.setHalfSize(10.0f, 12.0f);
    mCollisionCheckDrcTouch.setCenterOffset(0.0f, 12.0f);
}

void Kuribo::calcDrcTouch()
{
    if (mIsKakibo)
        calcKakiboHa_();
}

void Kuribo::initializeState_KakiboWalk()
{
    setKakiboAnm(checkKakiboTurnSaka_() ? cKakiboAnmID_Walk1 : cKakiboAnmID_Walk0);
    setWalkSpeed();
    mAccelY = cDefaultGravity;
    mSpeedMax.set(0.0f, cMaxSpeedY, 0.0f);
}

void Kuribo::executeState_KakiboWalk()
{
    calcSpeedY_();
    posMove_();
    bgCheck_();
    mAngle.y().chaseRest(cBaseAngleY[mDirection], cTurnSpeed);
    if (mBgCheckObj.checkFoot())
    {
        mSpeed.y = 0.0f;
        if (!checkGroundKakiboTurn())
        {
            if (!mIsKakiboWalk1)
                setKakiboAnm(cKakiboAnmID_Walk1);
            changeState(StateID_KakiboTurn);
            return;
        }
        if (InputMgr::instance()->isBgmAccentSign(1 << 0))
            mKakiboBgmHoldTimer = 10;
        calcKakiboHa_();
    }
    if (mBgCheckObj.checkWall(mDirection))
        changeState(StateID_KakiboTurn);
    if (!checkKakiboTurnSaka_())
        setKakiboAnm(cKakiboAnmID_Walk0);
    else
        setKakiboAnm(cKakiboAnmID_Walk1);
}

void Kuribo::finalizeState_KakiboWalk()
{
}

void Kuribo::initializeState_KakiboTurn()
{
    mSpeed.x = 0.0f;
    mDirection = InvDirX(mDirection);
}

void Kuribo::executeState_KakiboTurn()
{
    calcSpeedY_();
    posMove_();
    bgCheck_();
    if (mBgCheckObj.checkFoot())
    {
        if (InputMgr::instance()->isBgmAccentSign(1 << 0))
            mKakiboBgmHoldTimer = 10;
        calcKakiboHa_();
    }
    if (mAngle.y().chaseRest(cBaseAngleY[mDirection], cTurnSpeed))
    {
        changeState(StateID_KakiboWalk);
        return;
    }
    if (!checkKakiboTurnSaka_())
        setKakiboAnm(cKakiboAnmID_Walk0);
    else
        setKakiboAnm(cKakiboAnmID_Walk1);
}

void Kuribo::finalizeState_KakiboTurn()
{
}

void Kuribo::initializeState_Touch()
{
    KuriboBase::initializeState_Touch();
    if (mIsKakibo)
    {
        mIsKakiboWalk1 = false;
        setKakiboAnm(cKakiboAnmID_Walk0);
    }
}

void Kuribo::executeState_Touch()
{
    KuriboBase::executeState_Touch();
}

void Kuribo::finalizeState_Touch()
{
}

void Kuribo::initializeState_Down()
{
    mSpeed.set(0.0f, 0.0f, 0.0f);
    mSpeedMax.set(0.0f, cMaxSpeedY, 0.0f);
    _1a96 = 0;
}

void Kuribo::executeState_Down()
{
    mAngle.x() += 0x8000000;
    calcSpeedY_();
    posMove_();
    if (!(PlayerMgr::instance()->getNum() > 1))
        down();
}

void Kuribo::finalizeState_Down()
{
}

void Kuribo::initializeState_Auto_Walk()
{
    if (mIsKakibo)
        setKakiboAnm(cKakiboAnmID_Walk0);
    else
        setWalkAnm();

    static const f32 c_auto_walk_speed_x[cWakiDir_Num] = {
        0.0f, 0.0f, -0.5f, 0.5f
    };
    static const f32 c_auto_walk_speed_y[cWakiDir_Num] = {
        0.5f, -0.5f, 0.0f, 0.0f
    };
    static const f32 c_auto_walk_target_offset_x[cWakiDir_Num] = {
        0.0f, 0.0f, -16.0f, 16.0f
    };
    static const f32 c_auto_walk_target_offset_y[cWakiDir_Num] = {
        16.0f, -16.0f, 0.0f, 0.0f
    };

    mSpeed.x = c_auto_walk_speed_x[mWakiDir];
    mSpeed.y = c_auto_walk_speed_y[mWakiDir];
    mSpeed.z = 0.0f;

    mWakiTargetPos.x = mPos.x + c_auto_walk_target_offset_x[mWakiDir];
    mWakiTargetPos.y = mPos.y + c_auto_walk_target_offset_y[mWakiDir];

    if (mWakiDir == cWakiDir_Left)
        mDirection = cDirType_Left;
    else if (mWakiDir == cWakiDir_Right)
        mDirection = cDirType_Right;
    else
        mDirection = getPlayerDirLR();
    mAngle.y() = cBaseAngleY[mDirection];
}

void Kuribo::executeState_Auto_Walk()
{
    posMove_();
    if (mWakiDir == cWakiDir_Up)
    {
        if (sead::Mathf::abs(mPos.y - mWakiTargetPos.y) <= 4.0f)
            mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Tama);
        if (mPos.y < mWakiTargetPos.y)
            return;
        mPos.y = mWakiTargetPos.y;
    }
    else if (mWakiDir == cWakiDir_Down)
    {
        if (sead::Mathf::abs(mPos.y - mWakiTargetPos.y) <= 4.0f)
            mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Tama);
        if (mPos.y > mWakiTargetPos.y)
            return;
        mPos.y = mWakiTargetPos.y;
    }
    else if (mWakiDir == cWakiDir_Left)
    {
        if (sead::Mathf::abs(mPos.x - mWakiTargetPos.x) <= 4.0f)
            mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Tama);
        if (mPos.x > mWakiTargetPos.x)
            return;
        mPos.x = mWakiTargetPos.x;
    }
    else // cWakiDir_Right
    {
        if (sead::Mathf::abs(mPos.x - mWakiTargetPos.x) <= 4.0f)
            mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Tama);
        if (mPos.x < mWakiTargetPos.x)
            return;
        mPos.x = mWakiTargetPos.x;
    }
    mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Enemy);
    mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_ChibiYoshi);
    u32 z_order = mParam0 >> 24 & 0xF;
    mPos.z = -2500.0f + 16.0f * z_order;
    if (mWakiDir == cWakiDir_Down)
        changeState(StateID_Dokan_Down);
    else
    {
        mEnFlag.reset(cEnFlag_16);
        if (mIsKakibo)
            changeState(StateID_KakiboWalk);
        else
            changeState(StateID_Walk);
    }
}

void Kuribo::finalizeState_Auto_Walk()
{
}

void Kuribo::initializeState_Dokan_Down()
{
    mSpeed.set(0.0f, 0.0f, 0.0f);
    mSpeedMax.set(0.0f, cMaxSpeedY, 0.0f);
    if (mIsKakibo)
        setKakiboAnm(cKakiboAnmID_Walk0);
    else
        setWalkAnm();
}

void Kuribo::executeState_Dokan_Down()
{
    calcSpeedY_();
    posMove_();
    bgCheck_();
    if (mBgCheckObj.checkFoot())
    {
        mPos.z = -2500.0f;
        mEnFlag.reset(cEnFlag_16);
        if (mIsKakibo)
            changeState(StateID_KakiboWalk);
        else
            changeState(StateID_Walk);
    }
}

void Kuribo::finalizeState_Dokan_Down()
{
}

void Kuribo::initializeState_BlockAppear()
{
    _186c = 40;
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
}

void Kuribo::executeState_BlockAppear()
{
    if (_186c == 0)
    {
        if (mIsKakibo)
            changeState(StateID_KakiboWalk);
        else
            changeState(StateID_Walk);
    }
}

void Kuribo::finalizeState_BlockAppear()
{
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheckDrcTouch);
}

void Kuribo::initializeState_Born_Split1()
{
    static const sead::Vector2f c_born_split1_speed[cDirType_NumX] = {
        sead::Vector2f(0.5f, 3.0f),
        sead::Vector2f(-0.5f, 3.0f)
    };

    mpBlendModel->setAnm("walk", 2.0f);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(4.0f);
    mWalkAnmRate = 4.0f;

    u32 split_dir = mParam0 >> 24 & 0xF;
    mSpeed.x = c_born_split1_speed[split_dir].x;
    mSpeed.y = c_born_split1_speed[split_dir].y;
    mSpeed.z = 0.0f;

    mDirection = mSpeed.x < 0.0f ? cDirType_Left : cDirType_Right;
    mAngle.y() = cBaseAngleY[InvDirX(mDirection)];

    mAccelF = 0.0f;
    mSpeedMax.x = mSpeed.x;

    mBlockHitImmune = true;
    _1a97 = 1;

    u32 z_order = mParam0 >> 24 & 0xF;
    mPos.z += z_order * 16.0f;

    mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Player);

    mSubstate = 1;
}

void Kuribo::executeState_Born_Split2()
{
    calcSpeedX_();
    calcSpeedY_();
    posMove_();
    mBgCheckObj.checkBg();
    if (mBgCheckObj.checkHead())
        mSpeed.y *= -1.0f;
    if (mBgCheckObj.checkWall(cDirType_Right) || mBgCheckObj.checkWall(cDirType_Left))
        mSpeed.x *= -1.0f;
    switch (mSubstate)
    {
    default:
        break;
    case 1:
        if (mSpeed.y < 0.0f)
        {
            mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Player);
            _1a97 = 0;
            if (mBgCheckObj.checkFoot())
            {
                mSubstate = 2;
                mBlockHitImmune = false;
                mSpeed.y *= -0.75f;
            }
        }
        break;
    case 2:
        if (mBgCheckObj.checkFoot())
        {
            mSubstate = 3;
            mAccelF = sead::Mathf::abs(mSpeed.x) / 10;
            _186c = 10;
            mSpeed.y = 0.0f;
            mSpeedMax.x = 0.0f;
        }
        break;
    case 3:
        if (mBgCheckObj.checkFoot())
            mSpeed.y = 0.0f;
        if (_186c == 0)
        {
            mSubstate = 4;
            mDirection = InvDirX(mDirection);
        }
        break;
    case 4:
        if (mBgCheckObj.checkFoot())
            mSpeed.y = 0.0f;
        if (mAngle.y().chaseRest(cBaseAngleY[mDirection], cTurnSpeed * 2))
            changeState(StateID_Walk);
        break;
    }
}

void Kuribo::executeState_Born_Split1()
{
    executeState_Born_Split2();
}

void Kuribo::finalizeState_Born_Split1()
{
    mBlockHitImmune = false;
}

void Kuribo::initializeState_Born_Split2()
{
    static const sead::Vector2f c_born_split2_speed[2 * cDirType_NumX] = {
        sead::Vector2f(0.5f, 5.0f),
        sead::Vector2f(-0.5f, 5.0f),
        sead::Vector2f(1.0f, 4.0f),
        sead::Vector2f(-1.0f, 4.0f)
    };

    mpBlendModel->setAnm("walk", 2.0f);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(4.0f);
    mWalkAnmRate = 4.0f;

    u32 split_dir = mParam0 >> 24 & 0xF;
    mSpeed.x = c_born_split2_speed[split_dir].x;
    mSpeed.y = c_born_split2_speed[split_dir].y;
    mSpeed.z = 0.0f;

    mDirection = mSpeed.x < 0.0f ? cDirType_Left : cDirType_Right;
    mAngle.y() = cBaseAngleY[InvDirX(mDirection)];

    mAccelF = 0.0f;
    mSpeedMax.x = mSpeed.x;

    mBlockHitImmune = true;
    _1a97 = 1;

    u32 z_order = mParam0 >> 24 & 0xF;
    mPos.z += z_order * 16.0f;

    mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Player);

    mSubstate = 1;
}

void Kuribo::finalizeState_Born_Split2()
{
    mBlockHitImmune = false;
}

void Kuribo::initializeState_EatOut_Ready()
{
    mEatData.setState(2);
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
}

void Kuribo::executeState_EatOut_Ready()
{
    if (mEatData.getYoshiID().isValid())
    {
        mEatData.setState(4);
        ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
        ActorCollisionCheckMgr::instance()->entry(mCollisionCheckDrcTouch);
        mNoHitPlayerTimer[mParam0 >> 20 & 3] = 16;
        changeState(StateID_EatOut);
    }
}

void Kuribo::finalizeState_EatOut_Ready()
{
}

void Kuribo::initializeState_BalloonHang()
{
    mpBalloon = getParent<BalloonHangActor>();
    mBalloonID = mpBalloon->getActorUniqueID();
    mAngle.y() = 0;
}

void Kuribo::executeState_BalloonHang()
{
    if (mpBalloon->isDetach())
    {
        mDirection = getPlayerDirLR();
        mAngle.y() = cBaseAngleY[mDirection];
        if (mIsKakibo)
            changeState(StateID_KakiboWalk);
        else
            changeState(StateID_Walk);
    }
    else
    {
        sead::Vector2f hang_pos;
        mpBalloon->getHangPos(hang_pos);
        mPos.x = hang_pos.x;
        mPos.y = hang_pos.y;
    }
}

void Kuribo::finalizeState_BalloonHang()
{
}

void Kuribo::initializeState_KameckIce()
{
    setFrozenAnm();
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
}

void Kuribo::executeState_KameckIce()
{
}

void Kuribo::finalizeState_KameckIce()
{
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheckDrcTouch);
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
}
