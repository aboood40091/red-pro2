#include <graphics/JointBlendModelCalcRatio.h>

#include <math/seadMathCalcCommon.h>

JointBlendModelCalcRatio::JointBlendModelCalcRatio()
    : mRatioA(1.0f)
    , mRatioB(0.0f)
    , mCounter(0.0f)
    , mInvDuration(0.0f)
    , mIsActive(false)
{
}

bool JointBlendModelCalcRatio::isZero_(f32 v)
{
    return sead::Mathf::abs(v) < 0.001f;
}

void JointBlendModelCalcRatio::set(f32 duration)
{
    if (isZero_(duration))
    {
        reset();
        return;
    }

    mRatioA         = 1.0f;
    mRatioB         = 0.0f;
    mCounter        = 0.0f;
    mInvDuration    = 1.0f / duration;

    mIsActive = true;
}

void JointBlendModelCalcRatio::reset_()
{
    mRatioA         = 0.0f;
    mRatioB         = 1.0f;
    mCounter        = 1.0f;
    mInvDuration    = 0.0f;
}

void JointBlendModelCalcRatio::reset()
{
    reset_();
    mIsActive = false;
}

void JointBlendModelCalcRatio::calc()
{
    if (isZero_(mRatioA))
        return;

    mCounter += mInvDuration;
    if (mCounter >= 1.0f)
    {
        reset();
        return;
    }

    mIsActive = true;

    mRatioA -= mInvDuration;
    mRatioB += mInvDuration;
}
