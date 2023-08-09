#include <actor/ActorBase.h>
#include <actor/ActorFindFunc.h>

bool ActorProfileFindFunc::operator()(const ActorBase& actor)
{
    return actor.getProfileID() == mProfID;
}

bool ActorNearestFindFunc::operator()(const ActorBase& actor)
{
    return actor.getActorUniqueID().getActorID() == mID;
}
