#pragma once

#include <state/IStateFactory.h>
#include <state/State.h>

template <typename T>
class StateFactory : public IStateFactory
{
public:
    StateFactory(T& obj)
        : mState(obj)
    {
    }

    virtual ~StateFactory()
    {
    }

    IState* build(const IStateID& state_id) override
    {
        const StateID<T>& sid = static_cast<const StateID<T>&>(state_id);
        mState.setStateID(&sid);
        sid.initializeState(mState.getObject());
        return &mState;
    }

    void dispose(IState*& p_state) override
    {
        const StateID<T>& sid = static_cast<const StateID<T>&>(*mState.getStateID());
        sid.finalizeState(mState.getObject());
        mState.setStateID(nullptr);
        p_state = nullptr;
    }

    IState* buildNoInitializeState(const IStateID& state_id) override
    {
        const StateID<T>& sid = static_cast<const StateID<T>&>(state_id);
        mState.setStateID(&sid);
        return &mState;
    }

    void disposeNoFinalizeState(IState*& p_state) override
    {
        mState.setStateID(nullptr);
        p_state = nullptr;
    }

    void initializeState(IState* p_state) override
    {
        const StateID<T>& sid = static_cast<const StateID<T>&>(*(static_cast<State<T>*>(p_state)->getStateID()));
        sid.initializeState(mState.getObject());
    }

protected:
    State<T>    mState;
};
