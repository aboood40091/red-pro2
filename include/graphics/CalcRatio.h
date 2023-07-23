#pragma once

#include <basis/seadTypes.h>

class CalcRatio
{
public:
    CalcRatio();

    void set(f32 duration);
    void reset();

    void calc();

    f32 ratioA() const
    {
        return mRatioA;
    }

    f32 ratioB() const
    {
        return mRatioB;
    }

    bool isActive() const
    {
        return mIsActive;
    }

private:
    void reset_();

    static bool isZero_(f32 v);

private:
    f32     mRatioA;    // Source
    f32     mRatioB;    // Target
    f32     mCounter;
    f32     mInvDuration;
    bool    mIsActive;
};
static_assert(sizeof(CalcRatio) == 0x14);
