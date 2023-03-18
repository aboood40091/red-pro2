#pragma once

#include <basis/seadTypes.h>

class IStateID
{
public:
    IStateID()
        : mNumber(sNumberMemo++)
    {
    }

    IStateID(s32 number)
        : mNumber(number)
    {
    }

    virtual ~IStateID()
    {
    }

    virtual s32 number() const
    {
        return mNumber;
    }

    bool isNull() const
    {
        return mNumber == -1;
    }

    bool isEqual(const IStateID& rhs) const
    {
        return number() == rhs.number();
    }

    bool operator==(const IStateID& rhs) const
    {
        return isEqual(rhs);
    }

    bool operator!=(const IStateID& rhs) const
    {
        return !isEqual(rhs);
    }

protected:
    s32 mNumber;

    static s32 sNumberMemo;
};
static_assert(sizeof(IStateID) == 8);
