#include <state/StateStateMethod.h>

const StateID StateID::cNull(StateID::cNullNumber);

StateMethod::StateMethod(IStateFactory& factory, const StateID& state_id)
    : mFactory(factory)
    , mpNewStateID(nullptr)
    , mpState(nullptr)
    , mpOldStateID(&StateID::cNull)
{
    if (!state_id.isNull())
        mpNewStateID = &state_id;
}

void StateMethod::executeStateMethod()
{
    executeStateLocalMethod_();
}

void StateMethod::changeStateMethod(const StateID& state_id)
{
    mpNewStateID = &state_id;
    changeStateLocalMethod_();
}

const StateID* StateMethod::getStateID() const
{
    if (mpState == nullptr)
    {
        if (mpNewStateID == nullptr)
        {
            return &StateID::cNull;
        }
        return mpNewStateID;
    }
    return mpState->getStateID();
}

void StateStateMethod::changeToSubStateMethod(const StateID& state_id)
{
    mMain.set(getStateID());
    mpOldStateID = mpState->getStateID();
    mFactory.dispose(mpState);
    mpState = mFactory.buildWithInitialize(state_id);
}
