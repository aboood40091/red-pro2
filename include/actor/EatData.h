#pragma once

#include <system/ID.h>

#include <math/seadVector.h>

class EatData
{
public:
    EatData(ID owner_id);

    virtual void* vf0C();
    virtual void* vf14(void*);
    virtual f32 vf1C(void*);
    virtual void* vf24(void*);
    virtual void vf2C();
    virtual bool handleEaten();
    virtual void vf3C();
    virtual void vf44();
    virtual u32 vf4C();
    virtual bool vf54(void*);
    virtual void* vf5C(void*);

protected:
    ID              mOwnerID;
    u32             mYoshiID;
    u32             mState;
    u32             mSpitType;
    sead::Vector3f  mScale;
    u32             mScore;
};
static_assert(sizeof(EatData) == 0x24);
