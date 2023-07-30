#pragma once

#include <system/LineNodeMgr.h>

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>

class Actor;
class CollisionCallback;

class ActorCollisionCheck : public sead::IDisposer
{
public:
    enum Shape
    {
        cShape_Square   = 0,
        cShape_Circle,
        cShape_DaikeiUD,    // Vertical Trapezoid
        cShape_DaikeiLR     // Horizontal Trapezoid
    };

    typedef void (*HitCallback)(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other);

    struct Info
    {
        sead::Vector2f  center_offset;
        sead::Vector2f  half_size;
        Shape           shape;
        u32             _14;
        u32             _18;
        u32             _1c;
        u32             collision_mask; // Sets allowed collisions, such as colliding with Yoshi
        u32             mask_2;         // Sets allowed interactions, such as being pick-able
        HitCallback     callback;

        static const Info cDefault;
    };
    static_assert(sizeof(Info) == 0x2C);

public:
    ActorCollisionCheck();
    virtual ~ActorCollisionCheck();

    void set(Actor* p_owner, const Info& info, CollisionCallback* p_callbacks = nullptr);
    void set(Actor* p_owner, const Info& info, const sead::BitFlag8& collision_mask, CollisionCallback* p_callbacks = nullptr);
    void set(Actor* p_owner, const Info& info, const sead::BitFlag8& collision_mask, u8 layer, CollisionCallback* p_callbacks = nullptr);

    f32 getTopPos() const;
    f32 getUnderPos() const;
    f32 getCenterPosY() const;
    f32 getRightPos() const;
    f32 getLeftPos() const;
    f32 getCenterPosX() const;

    Actor* getOwner() const
    {
        return mpOwner;
    }

    bool isInactive() const
    {
        return mFlag & 2;
    }

    bool isCollidable() const
    {
        return mCollisionMask.getDirect() != 0;
    }

    CollisionCallback* getCollisionCallback() const
    {
        return mpCallbacks;
    }

    const Info& getInfo() const
    {
        return mInfo;
    }

    f32 getDaikei(s32 index) const
    {
        return mDaikei[index];
    }

    sead::BoundBox2f getBoundBox() const
    {
        return sead::BoundBox2f(
            sead::Vector2f(
                getLeftPos(),
                getUnderPos()
            ),
            sead::Vector2f(
                getRightPos(),
                getTopPos()
            )
        );
    }

    bool isOverlap(const ActorCollisionCheck& cc_other)
    {
        const sead::BoundBox2f& a = getBoundBox();
        const sead::BoundBox2f& b = cc_other.getBoundBox();

        const sead::Vector2f& min_a = a.getMin();
        const sead::Vector2f& min_b = b.getMin();

        const sead::Vector2f& max_a = a.getMax();
        const sead::Vector2f& max_b = b.getMax();

        return min_a.x < max_b.x && max_a.x > min_b.x &&
               min_a.y < max_b.y && max_a.y > min_b.y;
    }

private:
    typedef LineNodeMgr<ActorCollisionCheck> List;

    List::Node                  mExecuteNode;
    List::Node                  mCreateNode;
    List::Node                  _28;
    List::Node                  _34;
    Actor*                      mpOwner;
    Actor*                      mpFriend;   // Collisions with this are ignored
    u32                         _48;
    sead::Vector2f              _4C;
    sead::Vector2f              _54;
    u32                         mHitFlag1;
    u32                         mHitFlag2;
    u32                         mHitFlag3;
    u32                         _68;
    sead::BitFlag8              mCollisionMask;
    u8                          mLayer;
    u8                          mFlag;
    CollisionCallback*          mpCallbacks;
    Info                        mInfo;
    sead::SafeArray<f32, 4>     mDaikei;
    sead::UnsafeArray<f32, 15>  _b0;
    sead::UnsafeArray<f32, 15>  _ec;
};
static_assert(sizeof(ActorCollisionCheck) == 0x128);
