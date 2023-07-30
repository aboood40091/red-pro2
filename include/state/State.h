#pragma once

#include <state/IState.h>
#include <state/StateID.h>

template <typename T>
class State : public IState
{
public:
    State(T& obj)
        : mpObject(&obj)
    {
    }

    T& getObject() const { return *mpObject; }

    const IStateID* getStateID() const override { return mStateID; }
    void setStateID(const StateID<T>* p_state_id) { mStateID = p_state_id; }

    void execute() override
    {
        mStateID->executeState(getObject());
    }

protected:
    T*                  mpObject;
    const StateID<T>*   mStateID;
};
