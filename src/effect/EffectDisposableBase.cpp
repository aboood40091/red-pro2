#include <effect/EffectDisposableBase.h>

void EffectDisposableBase::cleanup()
{
    fadeAndKill();

    if (mNode.isLinked())
        mNode.erase();

    mEffectID = cEffectID_None;
    mIsActive = false;
}

EffectDisposableBase::EffectDisposableBase()
    : mNode(this)
    , mEffectID(cEffectID_None)
    , mIsActive(false)
{
}
