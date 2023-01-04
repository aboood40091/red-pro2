#pragma once

/* This file has more than just ActorComparator.
   I don't actually know what to call this file,
   but at least it fits the order it appears in
   in the game's code. */

#include <actor/ActorBase.h>

class ActorComparator
{
public:
    virtual bool isEqual(const ActorBase& actor) const = 0;
};
static_assert(sizeof(ActorComparator) == 4);

class ActorComparatorProfID : public ActorComparator
{
public:
    ActorComparatorProfID(u32 id)
        : mProfID(id)
    {
    }

    virtual bool isEqual(const ActorBase& actor) const;

private:
    u32 mProfID;
};
static_assert(sizeof(ActorComparatorProfID) == 8);

class ActorComparatorID : public ActorComparator
{
public:
    ActorComparatorID(u32 id)
        : mID(id)
    {
    }

    virtual bool isEqual(const ActorBase& actor) const;

private:
    u32 mID;
};
static_assert(sizeof(ActorComparatorID) == 8);
