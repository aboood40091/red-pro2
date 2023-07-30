#pragma once

#include <actor/ActorBase.h>
#include <actor/ChibiEatData.h>
#include <actor/EatData.h>
#include <collision/ActorCollisionCheck.h>

#include <math/seadVector.h>

class ActorBgCollisionCheck;

class Actor : public ActorBase
{
    SEAD_RTTI_OVERRIDE(Actor, ActorBase)

public:
    Actor(const ActorInitArg& arg);
    virtual ~Actor();

    void postCreate(MainState state) override;

    s32 preExecute() override;
    void postExecute(MainState state) override;

    s32 preDraw() override;

    virtual void setPlayerId(s8 id)
    {
        mPlayerNo = id;
    }

    s8 getPlayerNo() const
    {
        return mPlayerNo;
    }

    virtual void removeCollisionCheck();
    virtual void reviveCollisionCheck();

    virtual ActorBgCollisionCheck* getBgCheck()
    {
        return nullptr;
    }

    virtual void vfAC()
    {
    }

    virtual bool isSpinLiftUpEnable()
    {
        return true;
    }

    virtual void setSpinLiftUpActor(Actor*)
    {
    }

    virtual void vfC4()
    {
    }

    virtual void vfCC()
    {
    }

    virtual void killAtGoal();
    virtual void splashWater(sead::Vector3f*);
    virtual void splashLava(sead::Vector3f*);
    virtual void splashLavaWave(sead::Vector3f*);
    virtual void splashPoison(sead::Vector3f*);
    virtual bool isOffScreen();

    virtual void damageFromUnder()
    {
    }

    ActorCollisionCheck& getCollisionCheck()
    {
        return mCollisionCheck;
    }

    const ActorCollisionCheck& getCollisionCheck() const
    {
        return mCollisionCheck;
    }

    u8 isVisible() const
    {
        return mIsVisible;
    }

    s32 distanceToPlayer(sead::Vector2f& out);
    u8 directionToPlayerH(const sead::Vector3f& position);
    u8 directionToPlayerV(const sead::Vector3f& position);
    u8 directionToActorH(const Actor& other);
    void cullCheck(u32 = 0);
    bool deleteActorWhenOutOfView(u32);

    const sead::Vector3f& getPos() const
    {
        return mPos;
    }

protected:
    u32                 mDirection;
    u8                  mPlayerNo;
    u8                  mControllerLytPlayerNo;
    u8                  mLayer;                     // Inited to ActorInitArg::layer
    sead::BitFlag8      mCollisionMask;
    f32                 mSpeedF;                    // Horizontal speed
    f32                 mSpeedFMax;                 // Maximum horizontal speed
    f32                 mAccelY;                    // Vertical acceleration
    f32                 mFallSpeedMax;              // Maximum fall speed
    f32                 mAccelF;                    // Horizontal acceleration
    sead::Vector3f      mPos;
    sead::Vector3f      mSpeed;
    sead::Vector3f      mSpeedMax;
    sead::Vector3f      mScale;
    sead::Vector3u      mAngle;
    sead::Vector3u      mAnglePrev;
    sead::Vector2f      mPosDelta;
    ActorCollisionCheck mCollisionCheck;
    struct
    {
        sead::Vector2f offset;
        sead::Vector2f size;
    }                   mVisibleArea;               // Inited to ActorCreateInfo::spawn_range
    sead::Vector2f      mSize;
    f32                 _rectQ_0;                   // Inited to 256.0 + ActorCreateInfo::_18
    f32                 _rectQ_1;                   // Inited to 256.0 + ActorCreateInfo::_1A
    f32                 _destroyBoundDistanceLeft;  // Inited to  80.0 + ActorCreateInfo::_1C
    f32                 _destroyBoundDistanceRight; // Inited to  80.0 + ActorCreateInfo::_1E
    u8                  mAreaNo;
    u8                  mType;                      // 0: Actor, 1: Player, 2: Yoshi, 3: Enemy, 4: Unknown
    u8                  mIsActive;
    u8                  mIsVisible;
    bool                mIsNoRespawn;
    u8                  _211;
    u8                  _212;
    u8                  mEventID[2];
    u16                 mCreateFlag;                // Inited to ActorCreateInfo::flag
    u32                 mBumpDamageTimer;
    u32                 _21c;
    u32                 _220;
    u32                 _224;
    u32                 _228;
    u32                 mKillStreak;
    u32                 mProfFlag;                  // Inited to Profile::mFlag
    sead::Vector3f      mCenterPos;
    sead::Vector3f      mPosPrev;
    sead::Vector3f      _24c;
    sead::Vector3f      _258;
    EatData*            mpEatData;
    ChibiEatData*       mpChibiEatData;
    u32                 _26c;
    u8*                 _270;                       // Inited to ActorInitArg::_28
    f32                 _274;
    void*               mpChibiBubbleData;
};
static_assert(sizeof(Actor) == 0x27C);
