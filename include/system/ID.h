#pragma once

#include <basis/seadTypes.h>

class ID
{
public:
    ID()
        : mID(0)
    {
    }

    ID(u32 id)
        : mID(id)
    {
    }

    void setValue(u32 id)
    {
        mID = id;
    }

    u32 getValue() const
    {
        return mID;
    }

    u32 getActorID() const
    {
        return mID & 0x3fffff;
    }

private:
    u32 mID;
};
static_assert(sizeof(ID) == 4);
