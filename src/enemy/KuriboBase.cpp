#include <ami/AmiUtil.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BgCollisionCheckResult.h>
#include <collision/RyusaBgHitCheckCallback.h>
#include <effect/EffectCreateUtil.h>
#include <enemy/KuriboBase.h>
#include <game/CourseTask.h>
#include <graphics/BlendModel.h>
#include <graphics/SkeletalAnimation.h>
#include <graphics/TexturePatternAnimation.h>
#include <input/InputMgr.h>
#include <map/Bg.h>
#include <map/LayerID.h>
#include <player/PlayerBase.h>
#include <utility/Mtx.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

CREATE_STATE_VIRTUAL_ID_BASE(KuriboBase, Walk)
CREATE_STATE_VIRTUAL_ID_BASE(KuriboBase, Turn)
CREATE_STATE_VIRTUAL_ID_BASE(KuriboBase, Touch)
CREATE_STATE_VIRTUAL_ID_BASE(KuriboBase, TrplnJump)
CREATE_STATE_VIRTUAL_ID_OVERRIDE(KuriboBase, Enemy, DieOther)
CREATE_STATE_VIRTUAL_ID_OVERRIDE(KuriboBase, Enemy, DieFall)

static const sead::SafeString cModelName = "kuribo";

static const sead::SafeString cWalkAnm[] = {
    "walk"
};

KuriboBase::KuriboBase(const ActorCreateParam& param)
    : Enemy(param)
    , mpModelResource(nullptr)
    , mpBlendModel(nullptr)
    , mpTexAnim(nullptr)
    , mCalcRatio(11)
    , mpParentMiddleKuribo(nullptr)
    , mWalkAnmRate(1.0f)
    , mZOffset(0.0f)
    , mKakiboHaScale(1.0f)
    , mKakiboHaAngleZ(0)
    , mHasLanded(true)
    , mForceLanded(false)
    , mAllowDrcTouchInAir(false)
    , mBlockHitImmune(false)
    , mIsDrcTouch(false)
    , mIsKakibo(false)
    , mModelType(cModelType_Normal)
    , mSubstate(0)
    , mDisableScreenOutCheck(false)
    , mEnemyHitRevX(0.0f)
    , mEatData(mActorUniqueID)
    , mChibiYoshiEatData(mActorUniqueID)
    , mBoyoMgr(this)
{
}

ActorBase::Result KuriboBase::create_()
{
    mCollisionCheck.set(this, cCcData_Normal);
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);

    mCollisionCheckDrcTouch.set(this, cCcData_DrcTouch);
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheckDrcTouch);

    mSpeedMax.y = -4.0f;

    mDirection = getPlayerDirLR();
    mAngle.y() = cBaseAngleY[mDirection];

    mFumiProc.fumi_check._8 = 0;

    mZOffset = 0.0f;

    initialize();

    mBoyoMgr.initialize();

    return cResult_Success;
}

void KuriboBase::setCcLine_()
{
    f32 width = mCollisionCheck.getHalfSizeX() + 3.0f;
    f32 center_x = mPos.x + mCollisionCheck.getCenterOffsetX();
    f32 center_y = mPos.y + mCollisionCheck.getCenterOffsetY();

    BgUnitCode::Type type_right = BgUnitCode::getType(Bg::instance()->getBgCheckData(center_x + width, center_y, mLayer));
    BgUnitCode::TypeInfo type_info_right = Bg::instance()->getUnitTypeInfo(center_x + width, center_y, mLayer);

    BgUnitCode::Type type_left = BgUnitCode::getType(Bg::instance()->getBgCheckData(center_x - width, center_y, mLayer));
    BgUnitCode::TypeInfo type_info_left = Bg::instance()->getUnitTypeInfo(center_x - width, center_y, mLayer);

    if (((type_right & BgUnitCode::cType_Vine) && type_info_right >= BgUnitCode::cTypeInfo_Vine_Wire) ||
        ((type_left  & BgUnitCode::cType_Vine) && type_info_left  >= BgUnitCode::cTypeInfo_Vine_Wire))
    {
        if (mCollisionMask.isOn(cCcLineKind_0))
            mCollisionCheck.setLine(sead::BitFlag8(cCcLineKind_0));
        else
            mCollisionCheck.setLine(sead::BitFlag8(cCcLineKind_1));
    }
    else
    {
        mCollisionCheck.setLine(sead::BitFlag8(cCcLineKind_0 | cCcLineKind_1));
    }
}

void KuriboBase::setLayerPos_()
{
    if (disallowDrcTouchOnGround() || vf54C())
        return;

    if (mLayer == cLayerID_Layer1)
    {
        sead::BitFlag8 line((mParam0 >> 16 & 1) ? cCcLineKind_1 : cCcLineKind_0);
        mPos.z = AmiUtil::getZpos(line) + mZOffset;
    }
    else
    {
        mPos.z = -2500.0f;
    }
}

bool KuriboBase::checkRyusa_()
{
    if (mBgCheckObj.checkFoot())
    {
        const sead::Vector3f& center_pos = getCenterPos();

        RyusaBgHitCheckCallback callback;
        const BgCollisionCheckParam param = {
            0,                              // _0
            false,                          // ignore_quicksand
            mLayer,                         // layer
            mCollisionMask,                 // collision_mask
            cBgCollisionCheckType_Solid,    // type
            &callback                       // callback
        };
        BasicBgCollisionCheck bg_check(param);
        const sead::Vector2f check_pos(
            center_pos.x,
            center_pos.y
        );
        if (bg_check.checkPointActor(nullptr, check_pos))
            return true;
    }
    return false;
}

bool KuriboBase::checkGround_()
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
    sead::Vector2f p1 = p0;
    p1.y -= 4.0f;
    BasicBgCollisionCheck bg_check(param);
    return bg_check.checkArea(nullptr, p0, p1, 1 << cDirType_Down);
}

void KuriboBase::landonEffect_()
{
    if (!mHasLanded)
    {
        sead::Vector3f pos(
            mPos.x,
            mPos.y,
            4500.0f
        );
        if (mBgCheckObj.checkFoot())
        {
            pos.z = getEffectZPos();
            mHasLanded = true;
            switch (BgUnitCode::getAttr(mBgCheckObj.getBgCheckData(cDirType_Down)))
            {
            default:
                EffectCreateUtil::createEffect(RP_Cmn_LandingSmoke_08, &pos);
                break;
            case BgUnitCode::cNuma:
            case BgUnitCode::cSand:
                EffectCreateUtil::createEffect(RP_Cmn_LandingSand_04, &pos);
                break;
            case BgUnitCode::cIce:
                EffectCreateUtil::createEffect(RP_Cmn_LandingIce_04, &pos);
                break;
            case BgUnitCode::cSnow:
                EffectCreateUtil::createEffect(RP_Cmn_LandingSnow_04, &pos);
                break;
            case BgUnitCode::cWater:
                EffectCreateUtil::createEffect(RP_Cmn_LandingPillarWtr_04, &pos);
                break;
            case BgUnitCode::cNone:
                EffectCreateUtil::createEffect(RP_Cmn_LandingSmoke_08, &pos);
                break;
            }
        }
        else
        {
            sead::Vector3f check_pos = pos;
            check_pos.y -= 2.0f;
            WaterType water_type = ActorBgCollisionCheck::checkWater(&pos.y, check_pos, mLayer);
            if (water_type != cWaterType_None)
            {
                mHasLanded = true;
                pos.z = 6500.0f;
                switch (water_type)
                {
                default:
                    break;
                case cWaterType_Water:
                    splashEffect_(pos, RP_Cmn_WaterSplash_04, 6, "SE_OBJ_CMN_SPLASH");
                    break;
                case cWaterType_Lava:
                case cWaterType_LavaWave:
                    splashEffect_(pos, RP_Cmn_LavaSplash_04, 16, "SE_OBJ_CMN_SPLASH_LAVA");
                    break;
                case cWaterType_Poison:
                    splashEffect_(pos, RP_Cmn_PoisonSplash_04, 23, "SE_OBJ_CMN_SPLASH_POISON");
                    break;
                }
            }
            else
            {
                if (mForceLanded)
                {
                    mHasLanded = true;
                    sead::Vector3f pos(
                        mPos.x,
                        mPos.y,
                        4500.0f
                    );
                    EffectCreateUtil::createEffect(RP_Cmn_LandingSmoke_08, &pos);
                }
            }
        }
    }
    else if (!mBgCheckObj.checkFoot() && !checkGround_())
    {
        mHasLanded = false;

        sead::Vector3f check_pos = mPos;
        check_pos.y -= 2.0f;
        WaterType water_type = ActorBgCollisionCheck::checkWater(nullptr, check_pos, mLayer);
        if (water_type != cWaterType_None)
        {
            mHasLanded = true;
            if (mForceLanded)
            {
                mForceLanded = false;
                mHasLanded = false;
            }
        }
        else
        {
            if (mForceLanded)
                mHasLanded = true;
        }
    }
}

u8 KuriboBase::checkBgIn_()
{
    bool press_up_down = false;
    if (mBgCheckObj.checkFoot() && mBgCheckObj.checkHead())
        press_up_down = true;

    const sead::Vector3f& center_pos = getCenterPos();

    const BgCollisionCheckParam param = {
        0,                              // _0
        false,                          // ignore_quicksand
        mLayer,                         // layer
        mCollisionMask,                 // collision_mask
        cBgCollisionCheckType_Solid,    // type
        nullptr                         // callback
    };
    const sead::Vector2f check_pos(
        center_pos.x,
        center_pos.y
    );
    BasicBgCollisionCheck bg_check(param);
    bool bg_in = bg_check.checkPoint(nullptr, check_pos);

    s32 type = 0;
    if (press_up_down && bg_in)
        type = 1;

    return type;
}

void KuriboBase::setDeathInfo_Hasami_()
{
    u8 dir = mPos.x - mPosPrev.x < 0.0f ? cDirType_Left : cDirType_Right;

    hitdamageEffect(sead::Vector3f(mPos.x, mPos.y, 0.0f));
    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

    ENEMY_MAKE_DEATH_INFO_ARG_FALL(arg);
    arg.speed.x = cDieFallInitSpeedX[dir];
    arg.speed.y = cDieFallInitSpeedY;
    arg.max_fall_speed = cDieFallMaxFallSpeed;
    arg.gravity = cDieFallGravity;
    arg.direction = dir;
    mDeathInfo.kill(arg);
}

bool KuriboBase::execute_()
{
    mIsOnGround = mBgCheckObj.checkFoot();
    executeState();
    if (!mManualDeletedFlag)
    {
        setCcLine_();
        if (!isWakidashi() && !isState(StateID_Ice))
        {
            setLayerPos_();
            if (!checkRyusa_() && !isState(StateID_TrplnJump))
                landonEffect_();
            if (hasamareBgCheck_() || checkBgIn_())
                setDeathInfo_Hasami_();
        }
    }
    mBoyoMgr.execute();
    calcMdl_Normal();
    if (!disallowDrcTouchOnGround() && !mDisableScreenOutCheck)
        screenOutCheck(0);
    calcJumpSpeedF_();
    return true;
}

bool KuriboBase::draw_()
{
    drawModel();
    return true;
}

ActorBase::Result KuriboBase::doDelete_()
{
    return cResult_Success;
}

void KuriboBase::calcMdl_Base()
{
    calcModel();
}

void KuriboBase::normal_collcheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    KuriboBase* p_kuribo_self = cc_self->getOwner<KuriboBase>();
    if (p_kuribo_self != nullptr)
        p_kuribo_self->vf53C(*cc_other);

    Enemy::normal_collcheck(cc_self, cc_other);
}

void KuriboBase::vsEnemyHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_other = cc_other->getOwner();
    if (actor_other != nullptr && actor_other->getProfileID() != ProfileInfo::cProfileID_Maruta)
    {
        if (actor_other->getActorType() == cActorType_Enemy)
            mEnemyHitRevX = cc_self->getRevisionX(ActorCollisionCheck::cKind_Enemy);
        else if (actor_other->getActorType() == cActorType_ChibiYoshi)
            mEnemyHitRevX = cc_self->getRevisionX(ActorCollisionCheck::cKind_ChibiYoshi);
        setTurnByEnemyHit(cc_self->getOwner(), actor_other);
    }
}

void KuriboBase::vsPlayerHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_other = cc_other->getOwner();
    FumiType fumi_type = fumiCheck(cc_self, cc_other, cFumiSeType_Normal);
    if (fumi_type == cFumiType_Fumi)
    {
        reactFumiProc(actor_other);
        Actor* actor_self = cc_self->getOwner();
        if (actor_self != nullptr)
        {
            KuriboBase* p_kuribo_self = static_cast<KuriboBase*>(actor_self);
            if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
                CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
        }
    }
    else if (fumi_type == cFumiType_MameFumi)
    {
        return;
    }
    else if (fumi_type == cFumiType_SpinFumi)
    {
        reactSpinFumiProc(actor_other);
        Actor* actor_self = cc_self->getOwner();
        if (actor_self != nullptr)
        {
            KuriboBase* p_kuribo_self = static_cast<KuriboBase*>(actor_self);
            if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
                CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
        }
    }
    else
    {
        Enemy::vsPlayerHitCheck_Normal(cc_self, cc_other);
    }
}

void KuriboBase::vsYoshiHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    PlayerBase* p_player_other = cc_other->getOwner<PlayerBase>();
    Actor* actor_self = cc_self->getOwner();
    switch (fumiCheck(cc_self, cc_other, cFumiSeType_Normal))
    {
    case cFumiType_Fumi:
        reactYoshiFumiProc(p_player_other);
        if (actor_self != nullptr)
        {
            KuriboBase* p_kuribo_self = static_cast<KuriboBase*>(actor_self);
            if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
                CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
        }
        break;
    case cFumiType_Hit:
        Enemy::vsPlayerHitCheck_Normal(cc_self, cc_other);
        break;
    }
}

void KuriboBase::hitYoshiEat(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_self = cc_self->getOwner();
    if (actor_self != nullptr)
    {
        KuriboBase* p_kuribo_self = sead::DynamicCast<KuriboBase>(actor_self);
        if (p_kuribo_self != nullptr)
            if (p_kuribo_self->mpParentMiddleKuribo != nullptr)
                p_kuribo_self->mpParentMiddleKuribo->_1b0c++;
    }
    Enemy::hitYoshiEat(cc_self, cc_other);
}

bool KuriboBase::hitCallback_YoshiHipAttk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_self = cc_self->getOwner();
    if (actor_self != nullptr)
    {
        KuriboBase* p_kuribo_self = sead::DynamicCast<KuriboBase>(actor_self);
        if (p_kuribo_self != nullptr)
        {
            if (p_kuribo_self->mpParentMiddleKuribo != nullptr)
                p_kuribo_self->mpParentMiddleKuribo->_1b0c++;

            if (p_kuribo_self->getProfileID() == ProfileInfo::cProfileID_Kuribo && !p_kuribo_self->mIsKakibo)
                CourseTask::instance()->getGameData()->getStatsData().incKuriboFumi();
        }
    }
    return Enemy::hitCallback_YoshiHipAttk(cc_self, cc_other);
}

void KuriboBase::vsChibiYoshiHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    vsEnemyHitCheck_Normal(cc_self, cc_other);
}

bool KuriboBase::hitCallback_ChibiYoshiUnk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* actor_self = cc_self->getOwner();
    if (actor_self != nullptr)
    {
        KuriboBase* p_kuribo_self = sead::DynamicCast<KuriboBase>(actor_self);
        if (p_kuribo_self != nullptr)
            if (p_kuribo_self->mpParentMiddleKuribo != nullptr)
                p_kuribo_self->mpParentMiddleKuribo->_1b0c++;
    }
    return Enemy::hitCallback_ChibiYoshiUnk(cc_self, cc_other);
}

void KuriboBase::setAwaHit(Actor* p_awa)
{
    if (mpParentMiddleKuribo != nullptr)
        mpParentMiddleKuribo->_1b0c++;

    Enemy::setAwaHit(p_awa);
}

void KuriboBase::calcModelBase_(BlendModel* p_blend_model)
{
    {
        sead::Vector3f pos = mPos;
        Angle3 angle = mAngle;

        Mtxf mtx;
        mtx.makeT(pos);

        mtx.YrotM(angle.y());

        mtx.multTranslationLocal(sead::Vector3f(0.0f, mCenterOffset.y, 0.0f));
        mtx.XrotM(angle.x());
        mtx.multTranslationLocal(sead::Vector3f(0.0f, -mCenterOffset.y, 0.0f));

        mtx.ZrotM(angle.z());

        p_blend_model->getModel()->setMtxRT(mtx);

        if (!isState(StateID_Ice))
        {
            p_blend_model->playAnmFrameCtrl();
            p_blend_model->getModel()->setScale(mBoyoMgr.getScale());
        }
        else
        {
            p_blend_model->getModel()->setScale(mScale);
        }
    }

    if (mModelType == cModelType_Normal)
        p_blend_model->calcBlend();
    else if (mModelType == cModelType_Kakibo)
        mCalcRatio.calc();

    p_blend_model->getModel()->calcAnm();

    if (mModelType == cModelType_Kakibo)
    {
        // 1
        {
            sead::Vector3f scale(0.0f, 0.0f, 0.0f);
            s32 bone_index = p_blend_model->getModel()->searchBoneIndex("ha_1");
            Mtxf mtx;
            p_blend_model->getModel()->getBoneLocalMatrix(bone_index, &mtx, &scale);
            mtx.ZrotM(-mKakiboHaAngleZ);
            scale *= mKakiboHaScale;
            p_blend_model->getModel()->setBoneLocalMatrix(bone_index, mtx, scale);
        }
        // 2
        {
            sead::Vector3f scale(0.0f, 0.0f, 0.0f);
            s32 bone_index = p_blend_model->getModel()->searchBoneIndex("ha_2");
            Mtxf mtx;
            p_blend_model->getModel()->getBoneLocalMatrix(bone_index, &mtx, &scale);
            mtx.ZrotM(-mKakiboHaAngleZ);
            scale *= mKakiboHaScale;
            p_blend_model->getModel()->setBoneLocalMatrix(bone_index, mtx, scale);
        }
        // 3
        {
            sead::Vector3f scale(0.0f, 0.0f, 0.0f);
            s32 bone_index = p_blend_model->getModel()->searchBoneIndex("ha_3");
            Mtxf mtx;
            p_blend_model->getModel()->getBoneLocalMatrix(bone_index, &mtx, &scale);
            mtx.ZrotM(-mKakiboHaAngleZ);
            scale *= mKakiboHaScale;
            p_blend_model->getModel()->setBoneLocalMatrix(bone_index, mtx, scale);
        }
        // 4
        {
            sead::Vector3f scale(0.0f, 0.0f, 0.0f);
            s32 bone_index = p_blend_model->getModel()->searchBoneIndex("ha_4");
            Mtxf mtx;
            p_blend_model->getModel()->getBoneLocalMatrix(bone_index, &mtx, &scale);
            mtx.ZrotM(-mKakiboHaAngleZ);
            scale *= mKakiboHaScale;
            p_blend_model->getModel()->setBoneLocalMatrix(bone_index, mtx, scale);
        }
        mCalcRatio.applyTo(p_blend_model->getModel());
    }

    p_blend_model->getModel()->calcMdl();
}

void KuriboBase::setTurnByPlayerHit(Actor*)
{
    mDirection = getPlayerDirLR();
    if (isState(StateID_Turn))
        changeState(StateID_Walk);
    mAngle.y() = cBaseAngleY[mDirection];
    setWalkSpeed();
    calcModelBase_();
}

void KuriboBase::reactFumiProc(Actor* p_player)
{
    setDeathInfo_FumiOther(p_player, mSpeed);
}

void KuriboBase::yoganSplashEffect(const sead::Vector3f& pos)
{
    sead::Vector3f effect_pos = pos;
    effect_pos.z = 6500.0f;
    if (mBgCheckObj.checkFoot() || checkGround_())
        splashEffect_(effect_pos, RP_Cmn_LavaSplash_04, 16, "SE_OBJ_CMN_SPLASH_LAVA");
}

void KuriboBase::initializeState_Walk()
{
    if (!isOldState(StateID_Turn) && !vf554())
        setWalkAnm();
    setWalkSpeed();
    mAccelY = cDefaultGravity;
    mSpeedMax.set(0.0f, -4.0f, 0.0f);
}

void KuriboBase::executeState_Walk()
{
    calcSpeedY_();
    posMove_();
    bgCheck_();
    mAngle.y().chaseRest(cBaseAngleY[mDirection], 0x2000000);
    walkEffect();
    if (mBgCheckObj.checkFoot())
    {
        mSpeed.y = 0.0f;
        if (mBgCheckObj.isOnTrampoline())
            changeState(StateID_TrplnJump);
        else
        {
            if (isBgmSync() && InputMgr::instance()->isBgmAccentSign(1 << 0))
                mSpeed.y = 2.0f;
        }
    }
    if (mBgCheckObj.checkWall(mDirection))
        changeState(StateID_Turn);
}

void KuriboBase::finalizeState_Walk()
{
}

void KuriboBase::initializeState_Turn()
{
    if (!isOldState(StateID_TrplnJump))
    {
        mDirection = InvDirX(mDirection);
        mSpeed.x = 0.0f;
    }
}

void KuriboBase::executeState_Turn()
{
    calcSpeedY_();
    posMove_();
    bgCheck_();
    if (mBgCheckObj.checkFoot())
    {
        mSpeed.y = 0.0f;
        if (mBgCheckObj.isOnTrampoline())
            changeState(StateID_TrplnJump);
        else
        {
            if (isBgmSync() && InputMgr::instance()->isBgmAccentSign(1 << 0))
                mSpeed.y = 2.0f;
        }
    }
    if (mAngle.y().chaseRest(cBaseAngleY[mDirection], 0x2000000))
        changeState(StateID_Walk);
}

void KuriboBase::finalizeState_Turn()
{
}

void KuriboBase::initializeState_Touch()
{
    const f32 c_speed[cDirType_NumX] = { -0.5f, 0.5f };
    mSpeed.x = c_speed[mDirection];
    mSpeedMax.x = mSpeed.x;
    mSpeed.y = 3.0f;
    mAllowDrcTouchInAir = false;
    mSubstate = 1;
}

void KuriboBase::executeState_Touch()
{
    calcSpeedX_();
    calcSpeedY_();
    posMove_();
    mAngle.y().chaseRest(cBaseAngleY[mDirection], 0x2000000);
    mBgCheckObj.checkBg();
    if (mBgCheckObj.checkHead())
        mSpeed.y *= -1.0f;
    if (mBgCheckObj.checkWall(cDirType_Right) || mBgCheckObj.checkWall(cDirType_Left))
        mSpeed.x = 0.0f;
    if (mSpeed.y <= mSpeedMax.y && mForceLanded)
    {
        vf5F4();
        return;
    }
    switch (mSubstate)
    {
    default:
        break;
    case 1:
        if (mSpeed.y < 0.0f && mBgCheckObj.checkFoot())
        {
            mSubstate = 2;
            mAllowDrcTouchInAir = true;
            mSpeed.y *= -0.75f;
        }
        break;
    case 2:
        if (mSpeed.y < 0.0f && mBgCheckObj.checkFoot())
        {
            mSubstate = 3;
            mSpeed.y *= -0.75f;
        }
        break;
    case 3:
        if (mBgCheckObj.checkFoot())
        {
            mSubstate = 4;
            mAccelF = sead::Mathf::abs(mSpeed.x) / 10;
            _186c = 10;
            mSpeed.y = 0.0f;
            mSpeedMax.x = 0.0f;
        }
        break;
    case 4:
        if (mBgCheckObj.checkFoot())
            mSpeed.y = 0.0f;
        if (_186c == 0)
            vf5F4();
        break;
    }
    vf5EC();
}

void KuriboBase::finalizeState_Touch()
{
    mAllowDrcTouchInAir = false;
}

void KuriboBase::initializeState_TrplnJump()
{
    setWalkSpeed();
    mSpeed.y = 5.5f;
}

void KuriboBase::executeState_TrplnJump()
{
    calcSpeedY_();
    posMove_();
    bool turned = mAngle.y().chaseRest(cBaseAngleY[mDirection], 0x2000000);
    bgCheck_();
    if (mBgCheckObj.checkWall(mDirection))
    {
        mSpeed.x *= -1.0f;
        mDirection = InvDirX(mDirection);
    }
    if (mBgCheckObj.checkFoot())
    {
        mSpeed.y = 0.0f;
        if (mBgCheckObj.isOnTrampoline())
            initializeState_TrplnJump();
        else if (turned)
            changeState(StateID_Walk);
        else
            changeState(StateID_Turn);
    }
}

void KuriboBase::finalizeState_TrplnJump()
{
}

void KuriboBase::initializeState_DieOther()
{
    if (mModelType == cModelType_Normal)
        mpBlendModel->setAnm(mpModelResource, "damage", 2.0f);
    else if (mModelType == cModelType_Kakibo)
    {
        mCalcRatio.set(2.0f);
        mpBlendModel->getCurSklAnim()->play(mpModelResource, "damage");
    }
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(1.0f);
    mSpeed.set(0.0f, 0.0f, 0.0f);
    mAccelY = cDefaultGravity;
    removeCollisionCheck();
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
    mKakiboHaScale = 1.0f;
    mKakiboHaAngleZ = 0;
    mAngle.y() = 0;
    _186c = 30;
    if (mpParentMiddleKuribo != nullptr)
        mpParentMiddleKuribo->_1b0c++;
}

void KuriboBase::executeState_DieOther()
{
    if (_186c == 0)
        deleteRequest();
    mBgCheckObj.checkBg();
}

void KuriboBase::finalizeState_DieOther()
{
    Enemy::finalizeState_DieOther();
}

void KuriboBase::initializeState_DieFall()
{
    Enemy::initializeState_DieFall();
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
    if (mpParentMiddleKuribo != nullptr)
        mpParentMiddleKuribo->_1b0c++;
    mKakiboHaScale = 1.0f;
    mKakiboHaAngleZ = 0;
    mHasLanded = false;
}

void KuriboBase::executeState_DieFall()
{
    Enemy::executeState_DieFall();
    landonEffect_();
}

void KuriboBase::finalizeState_DieFall()
{
    Enemy::finalizeState_DieFall();
}

BlendModel* KuriboBase::createModel(ModelResource* p_mdl_res, const sead::SafeString& name, bool not_set_walk_anm)
{
    BlendModel* p_blend_model = BlendModel::create(p_mdl_res, name, 2, 1, 0, 0, 0);
    if (!not_set_walk_anm)
        p_blend_model->setAnm(p_mdl_res, cWalkAnm[0], 0.0f);
    return p_blend_model;
}

void KuriboBase::setWalkAnm()
{
    mpBlendModel->setAnm(mpModelResource, "walk", 2.0f);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    mpBlendModel->getCurSklAnim()->getFrameCtrl().setRate(2.0f);
    mWalkAnmRate = 2.0f;
    if (mModelType == cModelType_Normal)
        mpTexAnim->play(mpModelResource, "walk");
    mpTexAnim->getFrameCtrl().setRate(1.0f);
    if (mModelType == cModelType_Normal)
        mpTexAnim->getFrameCtrl().setFrame(GAME_RANDOM.getU32(180));
    else
    {
        mpTexAnim->getFrameCtrl().setRate(2.0f);
        mpTexAnim->getFrameCtrl().setFrame(0.0f);
    }
}

void KuriboBase::reviveCollisionCheck()
{
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheckDrcTouch);
}

void KuriboBase::removeCollisionCheck()
{
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
    ActorCollisionCheckMgr::instance()->release(mCollisionCheckDrcTouch);
}

bool KuriboBase::setDamage(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    PlayerBase* p_player_other = cc_other->getOwner<PlayerBase>();
    if (p_player_other != nullptr)
    {
        if (p_player_other->setNormalDamage(cc_self))
        {
            setTurnByPlayerHit(p_player_other);
            return true;
        }
    }
    return false;
}

void KuriboBase::allEnemyDeathEffSet()
{
    sead::Vector3f effect_pos;
    effect_pos.setAdd(mPos, mCenterOffset);
    EffectCreateUtil::createEffect(RP_Cmn_EnemyBurst_00, &effect_pos);
}

bool KuriboBase::DrcTouchCB::ccSetTouchNormal(ActorCollisionCheck* p_cc, const sead::Vector2f& pos)
{
    KuriboBase* p_kuribo_self = p_cc->getOwner<KuriboBase>();
    if (p_kuribo_self != nullptr)
        p_kuribo_self->onDrcTouch();
    return true;
}

void KuriboBase::DrcTouchCB::ccOnTouch(ActorCollisionCheck* p_cc, const sead::Vector2f& pos)
{
    if (p_cc->getOwner()->getProfileID() == ProfileInfo::cProfileID_PataKuribo)
        return;
    ActorCollisionDrcTouchCallback::ccOnTouch(p_cc, pos);
}

const f32 KuriboBase::cPataTurnMaxSpeedX = 1.0f;
const f32 KuriboBase::cPataWalkMaxSpeedY = -4.0f;

const ActorCreateInfo KuriboBase::cActorCreateInfo = { 8, -16, { 0, 8, 8, 8 }, { 0, 0, 0, 0 }, ActorCreateInfo::cFlag_Unknown };

const ActorCollisionCheck::CollisionData KuriboBase::cCcData_Normal = {
    { 0.0f, 8.0f },
    { 8.0f, 8.0f },
    ActorCollisionCheck::cShapeType_Box,
    ActorCollisionCheck::cKind_Enemy,
    ActorCollisionCheck::cAttack_None,
    ActorCollisionCheck::TargetKind(
        ActorCollisionCheck::cTargetKind_Player |
        ActorCollisionCheck::cTargetKind_Enemy |
        ActorCollisionCheck::cTargetKind_Item |
        ActorCollisionCheck::cTargetKind_Tama |
        ActorCollisionCheck::cTargetKind_ChibiYoshi |
        ActorCollisionCheck::cTargetKind_Unk10 |
        ActorCollisionCheck::cTargetKind_DrcTouch
    ),
    ActorCollisionCheck::cDamageFrom_All,
    ActorCollisionCheck::cStatus_None,
    KuriboBase::normal_collcheck
};

const ActorCollisionCheck::CollisionData KuriboBase::cCcData_DrcTouch = {
    { 0.0f, 8.0f },
    { 8.0f, 8.0f },
    ActorCollisionCheck::cShapeType_Box,
    ActorCollisionCheck::cKind_Enemy,
    ActorCollisionCheck::cAttack_None,
    ActorCollisionCheck::cTargetKind_DrcTouch,
    ActorCollisionCheck::cDamageFrom_None,
    ActorCollisionCheck::cStatus_None,
    nullptr
};
