#include <effect/EffectObjBase.h>

void EffectObjBase::cleanup()
{
    fade();

    if (mNode.isLinked())
        mNode.erase();

    mEffectID = cEffectID_None;
    mIsActive = false;
}

EffectObjBase::EffectObjBase()
    : mNode(this)
    , mEffectID(cEffectID_None)
    , mIsActive(false)
{
}
