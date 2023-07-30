#pragma once

#include <state/IStateMgr.h>
#include <state/StateFactory.h>

template <typename T, typename Method>
class StateMgr : public IStateMgr< T, Method, StateFactory<T> >
{
public:
    StateMgr(T& obj)
        : IStateMgr< T, Method, StateFactory<T> >(obj)
    {
    }

    virtual ~StateMgr()
    {
    }
};
