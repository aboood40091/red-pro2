#pragma once

#include <basis/seadTypes.h>

class IState;
class IStateID;

class IStateFactory
{
public:
    IStateFactory()
    {
    }

    virtual ~IStateFactory()
    {
    }

    virtual IState* build(const IStateID& state_id) = 0;
    virtual void dispose(IState*& p_state) = 0;
    virtual IState* initialize(const IStateID& state_id) = 0;
    virtual void finalize(IState*& p_state) = 0;
    virtual void initializeState(IState* p_state) = 0;
};
static_assert(sizeof(IStateFactory) == 4);

