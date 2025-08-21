#include <actor/ActorCollision.h>

ActorCollision::ActorCollision(const ActorCreateParam& param)
    : Actor(param)
    , mBgCheckObj()
    , mJumpSpeedF(0.0f)
    , mJumpAccelF(0.0f)
    , mpWaterCheckPos(&mPos)
    , mUseWaterTypeOverride(false)
    , mWaterTypeOverride(cWaterType_None)
    , _1774(1.0f)
    , _1778(0.0f, 0.0f)
    , _1780(0.0f, 0.0f)
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

