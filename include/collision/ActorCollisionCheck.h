#pragma once

#include <system/LineNodeMgr.h>

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
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
        sead::Vector2f center_offset;
        sead::Vector2f size;
        Shape shape;
        u32 _14;
        u32 _18;
        u32 _1c;
        u32 collision_mask;     // Sets allowed collisions, such as colliding with Yoshi
        u32 mask_2;             // Sets allowed interactions, such as being pick-able
        HitCallback callback;

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

private:
    typedef LineNodeMgr<ActorCollisionCheck> List;

    List::Node                  mExecuteNode;
    List::Node                  mCreateNode;
    List::Node                  _28;
    List::Node                  _34;
    Actor*                      mpOwner;
    Actor*                      mpFollowMaybe;
    u32                         _48;
    sead::Vector2f              _4C;
    sead::Vector2f              _54;
    u32                         mHitFlag;
    u32                         _60;
    u32                         _64;
    u32                         _68;
    sead::BitFlag8              mCollisionMask;
    u8                          mLayer;
    u8                          mFlag;
    CollisionCallback*          mpCallbacks;
    Info                        mInfo;
    sead::UnsafeArray<f32, 4>   mDaikei;
    sead::UnsafeArray<f32, 15>  _b0;
    sead::UnsafeArray<f32, 15>  _ec;
};
static_assert(sizeof(ActorCollisionCheck) == 0x128);
