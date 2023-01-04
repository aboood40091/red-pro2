#include <actor/ActorGeneral.h>

/* This file has more than just ActorComparator.
   I don't actually know what to call this file,
   but at least it fits the order it appears in
   in the game's code. */

bool ActorComparatorProfID::isEqual(const ActorBase& actor) const
{
    return actor.getProfileID() == mProfID;
}

bool ActorComparatorID::isEqual(const ActorBase& actor) const
{
    return actor.getID() == mID;
}
