#include <ami/AmiUtil.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BgCollisionCheckResult.h>
#include <collision/RyusaBgHitCheckCallback.h>
#include <effect/EffectCreateUtil.h>
#include <enemy/KuriboBase.h>
#include <map/Bg.h>
#include <map/LayerID.h>

static const ActorCollisionCheck::CollisionData cCcData_Normal = {
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

static const ActorCollisionCheck::CollisionData cCcData_DrcTouch = {
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

KuriboBase::KuriboBase(const ActorCreateParam& param)
    : Enemy(param)
    , mpModelResource(nullptr)
    , mpBlendModel(nullptr)
    , mpTexAnim(nullptr)
    , mCalcRatio(11)
    , mpParentMiddleKuribo(nullptr)
    , mWalkAnmRate(1.0f)
    , mZOffset(0.0f)
    , _1a00(1.0f)
    , _1a04(0)
    , _1a08(true)
    , _1a09(false)
    , mAllowDrcTouchInAir(false)
    , _1a0b(0)
    , _1a0c(0)
    , mIsKakibo(false)
    , mType(0)
    , _1a0f(0)
    , _1a10(0)
    , _1a14(0.0f)
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

    mDirection = directionToPlayerH(mPos);
    mAngle.y() = cBaseAngleY[mDirection];

    _1868 = 0;

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
    if (!_1a08)
    {
        sead::Vector3f pos(
            mPos.x,
            mPos.y,
            4500.0f
        );
        if (mBgCheckObj.checkFoot())
        {
            pos.z = getEffectZPos();
            _1a08 = true;
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
                _1a08 = true;
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
                if (_1a09)
                {
                    _1a08 = true;
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
        _1a08 = false;

        sead::Vector3f check_pos = mPos;
        check_pos.y -= 2.0f;
        WaterType water_type = ActorBgCollisionCheck::checkWater(nullptr, check_pos, mLayer);
        if (water_type != cWaterType_None)
        {
            _1a08 = true;
            if (_1a09)
            {
                _1a09 = false;
                _1a08 = false;
            }
        }
        else
        {
            if (_1a09)
                _1a08 = true;
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
    mStateMgr.executeState();
    if (!mManualDeletedFlag)
    {
        setCcLine_();
        if (!isWakidashi() && *mStateMgr.getStateID() != StateID_Ice)
        {
            setLayerPos_();
            if (!checkRyusa_() && *mStateMgr.getStateID() != StateID_TrplnJump)
                landonEffect_();
            if (hasamareBgCheck_() || checkBgIn_())
                setDeathInfo_Hasami_();
        }
    }
    mBoyoMgr.execute();
    calcMdl_Normal();
    if (!disallowDrcTouchOnGround() && !_1a10)
        screenOutCheck(0);
    calcJumpSpeedF_();
    return true;
}
