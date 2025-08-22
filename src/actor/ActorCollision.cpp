#include <actor/ActorCollision.h>
#include <game/Quake.h>

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

    if (mBgCheckObj.getOutput().checkFoot())
    {
        if (mBgCheckObj.getOutput().isQuicksand())
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

    if (!mIsNoRespawn && vf13C())
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
    mBgCheckObj.reset();

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
    return mBgCheckObj.getOutput().checkFoot();
}
