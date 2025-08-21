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

