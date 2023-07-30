#include <actor/ActorBase.h>
#include <actor/Profile.h>

s32 ActorBase::getProfileID() const
{
    return mpProfile->getID();
}
