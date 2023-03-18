#pragma once

#include <collision/BasicRideLine.h>
#include <collision/FollowArg.h>
#include <system/LineNodeMgr.h>

#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <prim/seadRuntimeTypeInfo.h>

class Actor;
class ActorBgCollisionCheck;

class BgCollision : public sead::IDisposer
{
public:
    typedef void (*Callback)(BgCollision*, ActorBgCollisionCheck*);
    typedef void (*CallbackWall)(BgCollision*, ActorBgCollisionCheck*, u8 direction);

    typedef bool (*CheckRev)(BgCollision*, ActorBgCollisionCheck*);
    typedef bool (*CheckRevWall)(BgCollision*, ActorBgCollisionCheck*, u8 direction);

    struct InitArg
    {
        sead::Vector2f          center_offset;
        sead::Vector2f          _8;
        const sead::Vector2f*   points;
        u32                     rotation;
    };
    static_assert(sizeof(InitArg) == 0x18);

    struct CircleInitArg
    {
        sead::Vector2f  center_offset;
        sead::Vector2f  _8;
        sead::Vector2f  p0;
        f32             radius;
        u32             rotation;
    };
    static_assert(sizeof(CircleInitArg) == 0x20);

    struct SquareInitArg
    {
        sead::Vector2f  center_offset;
        sead::Vector2f  _8;
        sead::Vector2f  p0;             // left top
        sead::Vector2f  p1;             // right bottom
        u32             rotation;
    };
    static_assert(sizeof(InitArg) == 0x24);

    enum Kind
    {
        cKind_Solid             = 0,
        cKind_Coin              = 1,
        cKind_GreenCoin         = 2,
        cKind_BlueCoin          = 3,
        cKind_CoinOutline       = 4,
        cKind_Fence             = 5,
        cKind_Vine              = 6,
        cKind_QuestionBlock     = 7,
        cKind_BrickBlock        = 8,
        cKind_QuestionBlockBig  = 9,
        cKind_BrickBlockBig     = 10,
        cKind_BlockUsedBig      = 11,
        cKind_BlockUsed         = 12,
        cKind_Unknown           = 13,
        cKind_WoodStoneBlock    = 14,
        cKind_Unknown2          = 15,
        cKind_DonutBlock        = 16,
        cKind_BoostBlock        = 17,
        cKind_Unknown3          = 18,
        cKind_Water             = 19,
        cKind_Lava              = 20,
        cKind_Poison            = 21,
        cKind_Quicksand         = 22,
        cKind_Carpet            = 23,   // Unused
        cKind_Leaves            = 24,   // Used by Palm Tree
        cKind_Wood              = 25,   // Used by Floating Barrel
        cKind_Unknown4          = 26,   // Used by Bouncy Cloud
        cKind_SwingingVine      = 27,
        cKind_SwingingChain     = 28,
        cKind_RopeLadder        = 29,
        cKind_Ice               = 30,
        cKind_Ice2              = 31,   // Used by frozen actors
        cKind_Ice3              = 32,   // Used by Portable Ice Block
        cKind_Unknown5          = 33,   // Used by Grrrol Passage and Grrrol Spawner
        cKind_Unknown6          = 34,
        cKind_Unknown7          = 35,   // Used by Pipe Bubbles
        cKind_Unknown8          = 36,   // Used by Airship Hand
        cKind_Unknown9          = 37,   // Used by Water Geyser
        cKind_Unknown10         = 38,   // Used by Pipes
        cKind_Unknown11         = 39,   // Used by Spine Coaster
        cKind_Unknown12         = 40,   // Used by Urchin
        cKind_InvisibleBlock    = 41
    };

    enum Type
    {
        cType_None                  = 0,
        cType_Solid                 = 1,
        cType_SolidOnTop            = 2,
        cType_SolidOnBottom         = 3,
        cType_SolidOnTopAndBottom   = 4,
        cType_Slide                 = 17,
        cType_SteepSlide            = 18,
        cType_Staircase             = 33,
        cType_Staircase2            = 34
    };

    enum SurfaceType
    {
        cSurfaceType_Regular        = 0,
        cSurfaceType_Ice            = 1,
        cSurfaceType_Snow           = 2,
        cSurfaceType_Quicksand      = 3,
        cSurfaceType_Sand           = 4,
        cSurfaceType_Grass          = 5,
        cSurfaceType_Cloud          = 6,
        cSurfaceType_BeachSand      = 7,    // Unused
        cSurfaceType_Carpet         = 8,    // Unused
        cSurfaceType_Leaves         = 9,
        cSurfaceType_Wood           = 10,
        cSurfaceType_Water          = 11,
        cSurfaceType_BeanstalkLeaf  = 12
    };

public:
    BgCollision();
    virtual ~BgCollision();

    SEAD_RTTI_BASE(BgCollision)

    virtual bool vf24(u32*, u32);   // TODO: Define
    virtual u32 vf2C(u32*);         // deleted
    virtual void vf34() = 0;
    virtual void execute() = 0;
    virtual bool vf44(RideLine*, u8*, sead::Vector2f*, sead::Vector2f*, u8) = 0;
    virtual bool vf4C(RideLine*, sead::Vector2f*, sead::Vector2f*, u8 direction, ActorBgCollisionCheck*) = 0;
    virtual bool vf54(u8*, sead::Vector2f*) = 0;
    virtual bool vf5C(u32*) = 0;
    virtual void vf64();
    virtual void vf6C() = 0;
    virtual void vf74(u32*) = 0;
    virtual bool vf7C(sead::Vector2f*, f32) = 0;

    void setKind(Kind kind);
    void setType(Type type);
    void setSurfaceType(SurfaceType surface_type);

protected:
    typedef LineNodeMgr<BgCollision> List;

    List::Node          _10;
    List::Node          _1c;
    List::Node          _28;
    List::Node          _34;
    List::Node          _40;
    List::Node          _4c;
    List::Node          _58;
    List::Node          _64;
    sead::BoundBox2f    _70;
    sead::Vector2f      _80;
    sead::BitFlag32     _88;
    sead::BitFlag32     _8c;
    Actor*              mpOwner;
    u32                 _94;
    FollowArg           mFollowArg;
    sead::Vector2f      mCenterOffset;
    sead::Vector2f      _b4;
    sead::Vector2f      _bc;
    sead::Vector2f      _c4;
    sead::Vector2f      _cc;
    sead::Vector2f      _d4;
    u8                  _dc;
    u32                 _e0;
    sead::Vector4f      _e4;
    u32                 mRotation;
    u32                 _f8;
    List                _fc;
    List                _108;
    List                _114;
    List                _120;
    Kind                mKind;
    RideLineArg         mRideLineArg;
    Callback            mCallbackFoot;
    Callback            mCallbackHead;
    CallbackWall        mCallbackWall;
    CheckRev            mCheckRevFoot;
    CheckRev            mCheckRevHead;
    CheckRevWall        mCheckRevWall;
    CollisionCallback*  mpCallbacks;
    u32                 _154;
};
static_assert(sizeof(BgCollision) == 0x158);
