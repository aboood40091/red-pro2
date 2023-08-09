#include <actor/ActorBase.h>
#include <actor/ActorFindFunc.h>

bool ActorProfileFindFunc::operator()(const ActorBase& actor)
{
    return actor.getProfileID() == mProfID;
}

bool ActorCreateIndexFindFunc::operator()(const ActorBase& actor)
{
    return actor.getActorUniqueID().getCreateIndex() == mCreateIndex;
}
