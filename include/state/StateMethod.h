#pragma once

#include <state/IStateID.h>

class IState;
class IStateFactory;

class StateMethod
{
public:
    static const IStateID cNullStateID;

public:
    StateMethod(IStateFactory& factory, const IStateID& state_id = cNullStateID);

    IState* getState() const { return mpState; }
    IStateID* getNewStateID() const { return mpNewStateID; }
    IStateID* getStateID() const;
    IStateID* getOldStateID() const { return mpOldStateID; }

    void executeStateMethod();
    void changeStateMethod(const IStateID& state_id);

protected:
    IStateFactory*  mpFactory;
    IStateID*       mpNewStateID;
    IState*         mpState;
    IStateID*       mpOldStateID;
};
static_assert(sizeof(StateMethod) == 0x10);

class StateMethodMulti : public StateMethod
{
public:
    StateMethodMulti(IStateFactory& factory, const IStateID& state_id = cNullStateID)
        : StateMethod(factory, state_id)
    {
    }

    void changeToSubStateMethod(const IStateID& state_id);

protected:
    IStateID*   mpReturnStateID;
};
static_assert(sizeof(StateMethodMulti) == 0x14);
