#pragma once

#include <basis/seadTypes.h>

template <typename T, typename Method, typename Factory>
class IStateMgr
{
public:
    IStateMgr(T& obj)
        : mFactory(obj)
        , mMethod(mFactory)
    {
    }

    Method& getStateMethod()
    {
        return mMethod;
    }

    const Method& getStateMethod() const
    {
        return mMethod;
    }

protected:
    Factory mFactory;
    Method mMethod;
};
