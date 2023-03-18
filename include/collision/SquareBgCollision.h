#pragma once

#include <collision/LoopRideLineBgCollision.h>
#include <collision/LoopRideLineBgCollisionUtil.h>

#include <container/seadSafeArray.h>

class SquareBgCollision : public LoopRideLineBgCollision
{
    SEAD_RTTI_OVERRIDE(SquareBgCollision, LoopRideLineBgCollision)

public:
    SquareBgCollision()
        : LoopRideLineBgCollision(4, mPointArray, mRideLineArray1, mRideLineArray2)
    {
        for (int i = 0; i < 4; i++)
        {
            mPointArray[i].x = 0.0f;
            mPointArray[i].y = 0.0f;
        }

        for (int i = 0; i < 4; i++)
        {
            mRideLineArray1[i].arg = mArg;
            mRideLineArray2[i].arg = mArg;
        }
    }

    virtual ~SquareBgCollision()
    {
    }

    bool vf54(u8*, sead::Vector2f*) override;

    void setCommon(const FollowArg& follow_arg, const SquareInitArg& init_arg)
    {
        LoopRideLineBgCollisionUtil::setCommon(this, follow_arg, init_arg);
    }

    void set(Actor* p_owner, const SquareInitArg& arg)
    {
        LoopRideLineBgCollisionUtil::set(this, p_owner, arg);
    }

    void setOfs(const sead::Vector2f& p0, const sead::Vector2f& p1) // left top and right bottom
    {
        LoopRideLineBgCollisionUtil::setOfs(this, p0, p1);
    }

private:
    sead::UnsafeArray<sead::Vector2f,   4>  mPointArray;
    sead::UnsafeArray<BasicRideLine,    4>  mRideLineArray1;
    sead::UnsafeArray<BasicRideLine,    4>  mRideLineArray2;
};
static_assert(sizeof(SquareBgCollision) == 0x290);
