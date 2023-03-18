#pragma once

#include <state/StateID.h>
#include <state/StateMethod.h>

template <typename T>
class StateVirtualID : public StateID<T>
{
public:
    typedef typename StateID<T>::FunctionPtr FunctionPtr;

public:
    StateVirtualID(FunctionPtr p_initialize, FunctionPtr p_execute, FunctionPtr p_finalize, const IStateID& base_state_id = StateMethod::cNullStateID)
        : StateID(p_initialize, p_execute, p_finalize)
        , mpBaseStateID(&base_state_id)
    {
    }

    virtual ~StateVirtualID()
    {
    }

    s32 number() const override
    {
        if (!mpBaseStateID->isNull())
            return mpBaseStateID->number();

        return mNumber;
    }

protected:
    const IStateID* mpBaseStateID;
};

#define DECLARE_STATE_VIRTUAL_ID_BASE(CLASS, NAME)          \
	static StateVirtualID<CLASS> StateID_##NAME;            \
	virtual void initializeState_##NAME();                  \
	virtual void executeState_##NAME();                     \
    virtual void finalizeState_##NAME();

#define DECLARE_STATE_VIRTUAL_ID_OVERRIDE(CLASS, NAME)      \
	static StateVirtualID<CLASS> StateID_##NAME;            \
	void initializeState_##NAME() override;                 \
	void executeState_##NAME() override;                    \
    void finalizeState_##NAME() override;

#define CREATE_STATE_VIRTUAL_ID_BASE(CLASS, NAME)           \
    StateVirtualID<CLASS> CLASS::StateID_##NAME             \
		(&CLASS::initializeState_##NAME,                    \
         &CLASS::executeState_##NAME,                       \
         &CLASS::finalizeState_##NAME);

#define CREATE_STATE_VIRTUAL_ID_OVERRIDE(CLASS, BASE, NAME) \
    StateVirtualID<CLASS> CLASS::StateID_##NAME             \
		(&CLASS::initializeState_##NAME,                    \
         &CLASS::executeState_##NAME,                       \
         &CLASS::finalizeState_##NAME,                      \
         &BASE::StateID_##NAME);
