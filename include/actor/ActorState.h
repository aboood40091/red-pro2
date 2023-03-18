#pragma once

#include <actor/ActorCollision.h>
#include <state/StateMethod.h>
#include <state/StateMgr.h>

class ActorState : public ActorCollision
{
    SEAD_RTTI_OVERRIDE(ActorState, ActorCollision)

public:
    ActorState(const ActorInitArg& arg);
    virtual ~ActorState() { }

    void changeState(const IStateID& state_id)
    {
        mStateMgr.getMethod().changeStateMethod(state);
    }

protected:
    StateMgr<ActorState, StateMethod> mStateMgr;
};
static_assert(sizeof(ActorState) == 0x17C8);

class ActorMultiState : public ActorCollision
{
    SEAD_RTTI_OVERRIDE(ActorMultiState, ActorCollision)

public:
    ActorMultiState(const ActorInitArg& arg);
    virtual ~ActorMultiState() { }

    virtual void changeState(const IStateID& state_id)
    {
        mStateMgr.getMethod().changeStateMethod(state);
    }

protected:
    StateMgr<ActorMultiState, StateMethodMulti> mStateMgr;
};
static_assert(sizeof(ActorMultiState) == 0x17C8);
