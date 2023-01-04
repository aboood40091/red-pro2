#include <actor/ActorBase.h>
#include <actor/Profile.h>

u32 ActorBase::getProfileID() const
{
    return mpProfile->getID();
}
