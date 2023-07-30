#pragma once

#include <system/ID.h>

#include <math/seadVector.h>

class ChibiEatData
{
public:
    ChibiEatData(ID owner_id);

    virtual u32 vf0C();
    virtual void* vf14(void*);
    virtual void* vf1C(void*);
    virtual void vf24();
    virtual void vf2C();
    virtual bool handleEaten(void*);
    virtual void vf3C();

protected:
    ID              mOwnerID;
    u32             mYoshiChibiID;
    sead::Vector3f  mScale;
    u32             _14;
    u32             _18;
    u32             mScore;
};
static_assert(sizeof(ChibiEatData) == 0x24);
