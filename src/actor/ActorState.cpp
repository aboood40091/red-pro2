#include <actor/ActorState.h>

ActorState::ActorState(const ActorCreateParam& param)
    : ActorCollision(param)
    , mStateMgr(*this)
{
}

ActorMultiState::ActorMultiState(const ActorCreateParam& param)
    : ActorCollision(param)
    , mStateMgr(*this)
{
}
