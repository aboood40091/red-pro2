#pragma once

#include <misc/rio_Types.h>

namespace Mii {

class DataSource
{
public:
    enum Type
    {
        cType_Database_Default = 0,
        cType_Database_Official,
        cType_StoreData_Save,
        cType_StoreData_Custom,
        cType_StoreData_Account,
        cType_Num
    };

public:
    DataSource(Type type = cType_Num, u32 index = 0)
    {
        setValue(type, index);
    }

    DataSource(u32 value)
    {
        setValue(value);
    }

    void setValue(u32 value)
    {
        mValue = value;
    }

    void setValue(Type type, u32 index)
    {
        mValue = type << 24 | (index & 0xffffff);
    }

    u32 getValue() const
    {
        return mValue;
    }

    Type getType() const
    {
        return Type(mValue >> 24);
    }

    s32 getIndex() const
    {
        return mValue & 0xffffff;
    }

private:
    u32 mValue;
};
static_assert(sizeof(DataSource) == 4);

}
