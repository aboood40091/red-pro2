#pragma once

#include <state/IStateID.h>

template <typename T>
class StateID : public IStateID
{
public:
    typedef void (T::*FunctionPtr)();

public:
    StateID(FunctionPtr p_initialize, FunctionPtr p_execute, FunctionPtr p_finalize)
        : mpInitialize(p_initialize)
        , mpExecute(p_execute)
        , mpFinalize(p_finalize)
    {
    }

    virtual ~StateID()
    {
    }

    void initializeState(T& obj) const
    {
        (obj.*mpInitialize)();
    }

    void executeState(T& obj) const
    {
        (obj.*mpExecute)();
    }

    void finalizeState(T& obj) const
    {
        (obj.*mpFinalize)();
    }

protected:
    FunctionPtr mpInitialize;
    FunctionPtr mpExecute;
    FunctionPtr mpFinalize;
};

#define DECLARE_STATE_ID(CLASS, NAME)       \
	static StateID<CLASS> StateID_##NAME;   \
	void initializeState_##NAME();          \
	void executeState_##NAME();             \
    void finalizeState_##NAME();

#define CREATE_STATE_ID(CLASS, NAME)        \
    StateID<CLASS> CLASS::StateID_##NAME    \
		(&CLASS::initializeState_##NAME,    \
         &CLASS::executeState_##NAME,       \
         &CLASS::finalizeState_##NAME);
