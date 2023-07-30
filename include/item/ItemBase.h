#pragma once

#include <actor/ActorState.h>

class Yoshi;

class ItemBase : public ActorMultiState
{
    SEAD_RTTI_OVERRIDE(ItemBase, ActorMultiState)

public:
    Yoshi* getEatenByYoshi() const;
};
