#pragma once

#include <basis/seadTypes.h>

class BgCheckUnitInfo
{
public:
    enum Kind
    {
        // ---------- Common ---------- //

        cKind_Normal            = 0,
        cKind_Rail              = 1,
        cKind_CoinOutline       = 2,
        cKind_Coin              = 3,
        cKind_CoinBlue          = 4,
        cKind_Block             = 5,
        cKind_BrickBlock        = 6,
        cKind_QuestionBlock     = 7,
        cKind_RedBlockOutline   = 8,
        cKind_PartialBlock      = 9,
        cKind_InvisibleBlock    = 10,
        cKind_Slope             = 11,
        cKind_ReverseSlope      = 12,
        cKind_Liquid            = 13,
        cKind_Climbable         = 14,   // Vine, Fence and Climbable wall with ledge
        cKind_Damage            = 15,
        cKind_Pipe              = 16,
        cKind_ConveyorBelt      = 17,
        cKind_DonutBlock        = 18,
        cKind_CaveEntrance      = 19,
        cKind_Ledge             = 20,
        cKind_Rope              = 21,
        cKind_Pole              = 22,

        // ------ Game--specific ------ //

        cKind_PoleRope          = 23,   // Swinging chain/vine and Rope ladder
        cKind_BreakableIce      = 24,
        cKind_GrrrolPassage     = 25,
        cKind_StreamCurrent     = 26,
        cKind_Carpet            = 27,
        cKind_Leaves            = 28,
        cKind_Wood              = 29,
        cKind_Cloud             = 30,
        cKind_BoostBlock        = 31,
        cKind_AirshipHand       = 32,
        cKind_WaterGeyser       = 33,
        cKind_BrickBlockBig     = 34,
        cKind_QuestionBlockBig  = 35,
        cKind_BlockUsedBig      = 36,
        cKind_RemoLiftElevator  = 37,
        cKind_SpineCoaster      = 38,
        cKind_Urchin            = 39
    };

    enum SolidType
    {
        cSolidType_None             = 0,    // Collision is not solid
        cSolidType_Fill             = 1,    // Collision is completely solid                        (filled)
        cSolidType_Outer            = 2,    // Collision is solid on the outer surface              (line)
        cSolidType_Inner            = 3,    // Collision is solid on the inner surface              (line)
        cSolidType_OuterAndInner    = 4     // Collision is solid on the outer and inner surfaces   (line)
    };

    enum SlideType
    {
        cSlideType_Normal   = 0,    // Player can slide while colliding when crouching
        cSlideType_Slide    = 1,    // Player instantly enters sliding state when colliding
        cSlideType_NoSlide  = 2     // Player cannot slide while colliding
    };

    enum SurfaceType
    {
        cSurfaceType_Normal         = 0,
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
    BgCheckUnitInfo()
        : mData(0)
    {
    }

    BgCheckUnitInfo(u64 data)
        : mData(data)
    {
    }

    u64 getData() const
    {
        return mData;
    }

    void setData(u64 data)
    {
        mData = data;
    }

    // -------------------------------------

    u64 getUnitType() const
    {
        return mData & 0xFFFFFFFFF;
    }

    Kind getUnitKind() const
    {
        return Kind(mData & 0xFFFF);
    }

    u8 getUnitParam0() const
    {
        return (mData >> 16) & 0xFF;
    }

    u8 getUnitParam1() const
    {
        return (mData >> 24) & 0xFF;
    }

    SolidType getUnitSolidType() const
    {
        return SolidType((mData >> 32) & 0xF);
    }

    // -------------------------------------

    SlideType getUnitSlideType() const
    {
        return SlideType((mData >> 36) & 0xF);
    }

    SurfaceType getUnitSurfaceType() const
    {
        return SurfaceType((mData >> 40) & 0xFF);
    }

private:
    u64 mData;  // SolidType == 1: Ignore active camera
};
static_assert(sizeof(BgCheckUnitInfo) == 8);
