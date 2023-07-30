#pragma once

#include <basis/seadTypes.h>

class IStateID
{
public:
    IStateID()
    {
        static s32 s_number_memo = 0;
        mNumber = ++s_number_memo;
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
};
static_assert(sizeof(IStateID) == 8);
