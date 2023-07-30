#pragma once

#include <actor/Actor.h>
#include <collision/ActorBgCollisionObjCheck.h>
#include <collision/BgCollisionCheckParam.h>

class ActorCollision : public Actor
{
    SEAD_RTTI_OVERRIDE(ActorCollision, Actor)

public:
    ActorCollision(const ActorInitArg& arg);
    virtual ~ActorCollision() { }

    void postCreate(MainState state) override;

    s32 preExecute() override;
    void postExecute(MainState state) override;

    s32 doDelete() override;

    ActorBgCollisionCheck* getBgCheck() override
    {
        return &mBgCheck;
    }

    virtual void vf10C(u8 unk)
    {
        _179A = unk;
    }

    virtual u8 vf114();                 // deleted

    virtual void vf11C()
    {
    }

    virtual void vf124(f32)
    {
    }

    virtual u32 vf12C()
    {
        return 0;
    }

    virtual void vf134();               // deleted
    virtual u32 vf13C();                // returns 0
    virtual void vf144(bool);           // nullsub
    virtual void vf14C(Actor*);         // nullsub

    virtual bool vf154()
    {
        return false;
    }

    virtual void move(const sead::Vector2f& dst)
    {
        mPos.x = dst.x;
        mPos.y = dst.y;
    }

    virtual void setSpeedY(f32 speed)
    {
        mSpeed.y = speed;
    }

    virtual u32 vf16C()
    {
        return 1;
    }

    virtual u32 vf174()
    {
        return 0;
    }

    virtual void getBox(sead::BoundBox2f& box)
    {
        box.set(
            mPos.x - 16.0f, mPos.y,
            mPos.x + 16.0f, mPos.y + 32.0f
        );
    }

    void calcSpeedY();
    void posMove();

    bool checkForSuitableGround(const sead::Vector2f& offset)
    {
        BgCollisionCheckParam param = { 0 };
        param.layer = mLayer;
        param.collision_mask = mCollisionMask;

        BasicBgCollisionCheck tile_check(param);

        sead::Vector2f a(mPos.x, mPos.y);
        sead::Vector2f b(a + offset);

        return tile_check.check(nullptr, a, b, 8);
    }

protected:
    u32                         _27C;
    ActorBgCollisionObjCheck    mBgCheck;
    f32                         _1760;
    f32                         _1764;
    sead::Vector3f*             _1768;
    u8                          _176C;
    u32                         _1770;
    f32                         _1774;
    sead::Vector2f              _1778;
    sead::Vector2f              _1780;
    f32                         mSpeedYMax;
    f32                         mSpeedYMin;
    f32                         _1790;
    u8                          _1794;
    u8                          _1795;
    u8                          _1796;
    u8                          _1797;
    u8                          _1798;
    u8                          _1799;
    u8                          _179A;
    bool                        mIsOnGround;
    u32                         _179C;
};
static_assert(sizeof(ActorCollision) == 0x17A0);
