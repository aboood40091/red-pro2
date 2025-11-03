#include <actor/ActorCollision.h>
#include <collision/ActorBgCollisionCheck.h>
#include <collision/BgCollision.h>
#include <collision/BgCollisionCheckResult.h>
#include <game/CourseTask.h>
#include <game/Quake.h>
#include <layout/GamesceneBase.h>
#include <player/PlayerDemoMgr.h>

ActorCollision::ActorCollision(const ActorCreateParam& param)
    : Actor(param)
    , mBgCheckObj()
    , mJumpSpeedF(0.0f)
    , mJumpAccelF(0.0f)
    , mpWaterCheckPos(&mPos)
    , mUseWaterTypeOverride(false)
    , mWaterTypeOverride(cWaterType_None)
    , _1774(1.0f)
    , mBgSpeed(0.0f, 0.0f)
    , mBgSpeedPrev(0.0f, 0.0f)
    , mWaterSpeedMaxY(1.5f)
    , mWaterFallSpeedMax(-1.5f)
    , mWaterGravity(-0.0625f)
    , mCheckWaterNeeded(false)
    , mIsInQuicksand(false)
    , mIsSubmerged(false)
    , mNoWaterCalc(false)
    , mWaterCalcType(cWaterCalcType_Normal)
    , mNoLavaSplashTimer(0)
    , mIsWaterFunsui(false)
    , mIsOnGround(false)
    , mJumpFrame(0)
{
}

void ActorCollision::clampWaterSpeedY_()
{
    if (mSpeed.y < mWaterFallSpeedMax)
        mSpeed.y = mWaterFallSpeedMax;

    else if (mSpeed.y > mWaterSpeedMaxY)
        mSpeed.y = mWaterSpeedMaxY;
}

void ActorCollision::enterWater_()
{
    clampWaterSpeedY_();
    mIsSubmerged = true;
}

WaterType ActorCollision::checkEnterWater_(f32* p_surface_pos_y, const sead::Vector3f& check_pos)
{
    f32 surface_pos_y = check_pos.y;
    WaterType water_type = ActorBgCollisionCheck::checkWater(&surface_pos_y, check_pos, mLayer);
    const f32 splash_pos_z = 6500.0f;

    switch (water_type)
    {
    default:
        mIsSubmerged = false;
        break;
    case cWaterType_Water:
        if (!mIsSubmerged)
        {
            enterWater_();
            waterSplashEffect(sead::Vector3f(mPos.x, surface_pos_y, splash_pos_z));
        }
        break;
    case cWaterType_AirWater:
        if (!mIsSubmerged)
        {
            enterWater_();
            waterSplashEffect(sead::Vector3f(mPos.x, surface_pos_y, splash_pos_z));
        }
        break;
    case cWaterType_Lava:
        if (!mIsSubmerged)
        {
            mIsSubmerged = true;
            if (mNoLavaSplashTimer == 0)
                yoganSplashEffect(sead::Vector3f(mPos.x, surface_pos_y, splash_pos_z));
        }
        break;
    case cWaterType_LavaWave:
        if (!mIsSubmerged)
        {
            mIsSubmerged = true;
            if (mNoLavaSplashTimer == 0)
                yoganWaveSplashEffect(sead::Vector3f(mPos.x, surface_pos_y, splash_pos_z));
        }
        break;
    case cWaterType_Poison:
        if (!mIsSubmerged)
        {
            mIsSubmerged = true;
            poisonSplashEffect(sead::Vector3f(mPos.x, surface_pos_y, splash_pos_z));
        }
        break;
    }

    if (mIsSubmerged)
        if (p_surface_pos_y != nullptr)
            *p_surface_pos_y = surface_pos_y;

    return water_type;
}

void ActorCollision::calcWater_()
{
    if (mNoWaterCalc)
        return;

    bool pre_check = false;

    switch (mWaterCalcType)
    {
    case cWaterCalcType_EnablePreCheck:
        if (!mCheckWaterNeeded)
            pre_check = true;
        break;
    case cWaterCalcType_ForceOut:
        mCheckWaterNeeded = false;
        mIsSubmerged = false;
        break;
    default:
        break;
    }

    if (pre_check)
    {
        mCheckWaterNeeded = true;
        WaterType water_type = mUseWaterTypeOverride ? mWaterTypeOverride : ActorBgCollisionCheck::checkWater(nullptr, *mpWaterCheckPos, mLayer);
        if (water_type != cWaterType_None)
            enterWater_();
    }
    else if (mCheckWaterNeeded)
    {
        f32 surface_pos_y;
        WaterType water_type = checkEnterWater_(&surface_pos_y, *mpWaterCheckPos);
        if (water_type == cWaterType_Lava || water_type == cWaterType_LavaWave)
        {
            if (smokeDamageEnable_Yogan_(surface_pos_y))
            {
                setSmokeDamage_(nullptr);
                mCheckWaterNeeded = false;
                mIsSubmerged = false;
            }
        }
        else if (water_type == cWaterType_Poison)
        {
            if (smokeDamageEnable_Poison_(surface_pos_y))
            {
                setSmokeDamage_(nullptr);
                mCheckWaterNeeded = false;
                mIsSubmerged = false;
            }
        }
    }

    if (mNoLavaSplashTimer > 0)
        mNoLavaSplashTimer--;

    mWaterCalcType = cWaterCalcType_Normal;
}

void ActorCollision::postCreate_(MainState state)
{
    calcWater_();
    Actor::postCreate_(state);
}

void ActorCollision::calcBgSpeed_()
{
    mBgSpeedPrev = mBgSpeed;
    mIsInQuicksand = false;

    if (mBgCheckObj.checkFoot())
    {
        if (mBgCheckObj.isQuicksand())
            mIsInQuicksand = true;

        mBgSpeed = mBgCheckObj.getBgSpeed();
    }
    else
    {
        mBgSpeed.set(0.0f, 0.0f);
    }
}

bool ActorCollision::preExecute_()
{
    if (!Actor::preExecute_())
        return false;

    mBgCheckObj.atFrameStart();
    calcBgSpeed_();

    if (!mManualDeletedFlag && vf13C())
    {
        if (Quake::instance()->getFlag() & (1 << 1))
            vf144(0);
        else if (Quake::instance()->getFlag() & (1 << 2))
            vf144(1);
      //else if (Quake::instance()->getFlag() & (1 << 0)) // Present in NSMB2, but removed from NSMBU
      //    vf144(2);
    }

    return true;
}

void ActorCollision::postExecute_(MainState state)
{
    calcWater_();
    mUseWaterTypeOverride = false;

    Actor::postExecute_(state);
}

ActorBase::Result ActorCollision::doDelete_()
{
    mBgCheckObj.clearBg();

    return Actor::doDelete_();
}

bool ActorCollision::vf13C()
{
    return false;
}

void ActorCollision::vf144(s32 param)
{
    switch (param)
    {
    case 0:
        break;
    case 1:
        break;
  //case 2: // Present in NSMB2, but removed from NSMBU
  //    break;
    }
}

void ActorCollision::setSmokeDamage_(Actor* p_actor)
{
    if (p_actor != nullptr)
    {
    }
}

bool ActorCollision::bgCheckFoot_() const
{
    return mBgCheckObj.checkFoot();
}

bool ActorCollision::bgCheckWall_() const
{
    s32 direction = cDirType_Right;
    if (mSpeed.x < 0.0f)
        direction = cDirType_Left;

    return mBgCheckObj.checkWall(direction);
}

ActorCollision::BgCheckFlag ActorCollision::bgCheck_()
{
    mBgCheckObj.checkBg();

    BgCheckFlag flag = cBgCheckFlag_None;

    if (bgCheckFoot_())
    {
        flag |= cBgCheckFlag_Foot;
        mSpeed.y = 0.0f;
    }

    if (mBgCheckObj.checkHead())
        flag |= cBgCheckFlag_Head;

    if (bgCheckWall_())
        flag |= cBgCheckFlag_Wall;

    return flag;
}

void ActorCollision::clampMoveDistance_(BgCollision& bg_collision)
{
    if (getPos2D().squaredDistance(mPosPrev) > sead::MathCalcCommon<u16>::maxNumber())
    {
        mPosPrev = mPos;
        mPosPrev2 = mPos;
        bg_collision.update();
    }
}

bool ActorCollision::isHitBgCollision_(const BgCollision& bg_collision) const
{
    for (
        BgCollision::BcList::Node* p_node = bg_collision.getBcListFoot().front()
        ; p_node != nullptr
        ; p_node = p_node->next
    )
    {
        if (p_node->obj->getOwner() != nullptr)
            return true;
    }

    for (
        BgCollision::BcList::Node* p_node = bg_collision.getBcListHead().front()
        ; p_node != nullptr
        ; p_node = p_node->next
    )
    {
        if (p_node->obj->getSensorFlag(cDirType_Up).isOnBit(ActorBgCollisionCheck::SensorFlag::cBit_21) && p_node->obj->getOwner() != nullptr)
            return true;
    }

    for (
        BgCollision::BcList::Node* p_node = bg_collision.getBcListWallR().front()
        ; p_node != nullptr
        ; p_node = p_node->next
    )
    {
        if (p_node->obj->getSensorFlag(cDirType_Left).isOnBit(ActorBgCollisionCheck::SensorFlag::cBit_18) && p_node->obj->getOwner() != nullptr)    // Nintendo uses Left here and not Right
            return true;
    }

    for (
        BgCollision::BcList::Node* p_node = bg_collision.getBcListWallL().front()
        ; p_node != nullptr
        ; p_node = p_node->next
    )
    {
        if (p_node->obj->getSensorFlag(cDirType_Right).isOnBit(ActorBgCollisionCheck::SensorFlag::cBit_18) && p_node->obj->getOwner() != nullptr)   // Nintendo uses Right here and not Left
            return true;
    }

    return false;
}

void ActorCollision::calcSpeedY_()
{
    f32 speed_max_y = mSpeedMax.y;

    if (mIsSubmerged)
    {
        if (speed_max_y < mWaterFallSpeedMax)
            speed_max_y = mWaterFallSpeedMax;
        else if (speed_max_y > mWaterSpeedMaxY)
            speed_max_y = mWaterSpeedMaxY;
        Actor::calcSpeedY_(mWaterGravity, speed_max_y);
    }
    else
    {
        Actor::calcSpeedY_(mAccelY, speed_max_y);
    }
}

void ActorCollision::calcFallSpeed_()
{
    f32 fall_speed_max = mFallSpeedMax;

    if (mIsSubmerged)
    {
        if (fall_speed_max < mWaterFallSpeedMax)
            fall_speed_max = mWaterFallSpeedMax;
        else if (fall_speed_max > mWaterSpeedMaxY)
            fall_speed_max = mWaterSpeedMaxY;
        Actor::calcFallSpeed_(mWaterGravity, fall_speed_max);
    }
    else
    {
        Actor::calcFallSpeed_(mAccelY, fall_speed_max);
    }
}

f32 ActorCollision::chaseZero_(f32 value, f32 step) const
{
    if (value < 0.0f)
    {
        value += step;
        if (value > 0.0f)
            value = 0.0f;
    }
    else if (value > 0.0f)
    {
        value -= step;
        if (value < 0.0f)
            value = 0.0f;
    }
    return value;
}

void ActorCollision::posMoveCalcJump_()
{
    if (mJumpFrame != 1)
        return;

    if (mBgCheckObj.checkFoot())
    {
        mJumpSpeedF = 0.0f;
        mJumpFrame = 0;
    }
    else
    {
        mJumpSpeedF = chaseZero_(mJumpSpeedF, mJumpAccelF);
        if (mJumpSpeedF == 0.0f)
            mJumpFrame = 0;
    }
}

void ActorCollision::posMove_()
{
    f32 saka_sin_v, saka_cos_v;
    sead::Mathf::sinCosIdx(&saka_sin_v, &saka_cos_v, mBgCheckObj.getSakaBaseAngle());

    f32 speed_x = mSpeed.x * saka_cos_v;
    if (mIsSubmerged || mIsInQuicksand)
        speed_x *= 0.5f;
    speed_x += mBgSpeed.x;

    f32 speed_y = mSpeed.x * saka_sin_v + mSpeed.y + mBgSpeed.y;

    posMoveCalcJump_();
    speed_x += mJumpSpeedF;

    mPos.x += speed_x;
    mPos.y += speed_y;
}

bool ActorCollision::isJump_() const
{
    if (mJumpFrame == 0 && mIsOnGround && !mBgCheckObj.checkFoot())
        return true;

    return false;
}

void ActorCollision::calcJumpSpeedF_()
{
    if (isJump_())
    {
        mJumpFrame += 1;
        mJumpSpeedF = mPosDelta.x + mBgSpeedPrev.x;
    }
}

WaterType ActorCollision::checkWater_(f32* p_surface_pos_y)
{
    mUseWaterTypeOverride = true;
    mWaterTypeOverride = ActorBgCollisionCheck::checkWater(p_surface_pos_y, *mpWaterCheckPos, mLayer);
    return mWaterTypeOverride;
}

bool ActorCollision::isEnablePress_()
{
    if (!mManualDeletedFlag &&
        (isEnablePressUD_(mBgCheckObj) || isEnablePressLR_(mBgCheckObj)))
    {
        return true;
    }
    return false;
}

void ActorCollision::snapToGroundImpl_(f32 y_check_distance, const ActorBgCollisionCheck::Sensor& foot_sensor, bool extended, bool force)
{
    mBgCheckObj.initBgCheck();
    sead::Vector2f p0, p1;
    BgCollisionCheckResultArea res;

    if (!force)
    {
        if (PlayerDemoMgr::instance() != nullptr && PlayerDemoMgr::instance()->isPlayerGameStop())
            return;
    }

    p0 = mPos;
    p1.x = p0.x;
    if (extended)
    {
        p0.y += y_check_distance;
        p1.y = p0.y - y_check_distance * 2;
    }
    else
    {
        p1.y = p0.y - y_check_distance;
    }

    if (mBgCheckObj.getBgCheck().checkArea(&res, p0, p1))
    {
        getPos2D() = res.hit_pos;
        mPos.y -= foot_sensor.center_offset;
        mBgCheckObj.getOutput().setFoot();
    }
}

void ActorCollision::checkSnapToGround_(f32 y_check_distance, const ActorBgCollisionCheck::Sensor& foot_sensor)
{
    if (mParam1 & 1)
    {
        // TODO: Non-matching, figure out exactly what they were trying to do with mParam1
        bool extended = mParam1 <= 1 ? false : true;
        bool force = mParam1 <= 2 ? true : false;
        snapToGroundImpl_(y_check_distance, foot_sensor, extended, force);
    }
}

void ActorCollision::snapToGround_(f32 y_check_distance, const ActorBgCollisionCheck::Sensor& foot_sensor, bool extended, bool force)
{
    snapToGroundImpl_(y_check_distance, foot_sensor, extended, force);
}

void ActorCollision::registerInGamescene_()
{
    GamesceneBase* p_gamescene = CourseTask::instance()->getGamescene();
    if (p_gamescene != nullptr)
        p_gamescene->registerActor(mActorUniqueID);
}
