#pragma once

#include <collision/Ride2Point.h>

struct RideLineArg
{
    RideLineArg()
        : flag(0)
        , _4(0)
    {
    }

    u32 flag;   // & 0xFF00: BgCollision::SurfaceType, & 0xF == 1: Ignore active camera
    u32 _4;
};
static_assert(sizeof(RideLineArg) == 8);

class BasicRideLine
{
public:
    BasicRideLine();

//protected:
    u8          _0;
    u8          _1;
    u8          _2;
    u8          _3;
    Ride2Point  mRide2Point;
    u32         _14;
    RideLineArg mArg;
};
static_assert(sizeof(BasicRideLine) == 0x20);

class BgCollision;

class RideLine : public BasicRideLine
{
public:
    RideLine(); // Idk

//protected:
    BgCollision*    mpOwner;
    u8              _24[4];
    u32             _28;
    u32             _2c;
    u32             _30;
    u32             _34;
};
static_assert(sizeof(RideLine) == 0x38);
