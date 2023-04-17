#pragma once

#include <actor/ActorGeneral.h>

#include <container/seadBuffer.h>

class ActorObjBuffer
{
public:
    typedef ActorBase* const* iterator;

public:
    ActorObjBuffer(sead::Heap* heap, s32 size);

    iterator searchBaseByComparator(const ActorComparator& cmp, iterator pp_start) const;
    iterator searchBaseByComparator(const ActorComparator& cmp) const
    {
        return searchBaseByComparator(cmp, begin());
    }

    iterator begin() const
    {
        return &mActor.front();
    }

    iterator end() const
    {
        return mpActorLast;
    }

    u32 size() const
    {
        return mCount;
    }

    u32 maxSize() const
    {
        return mActor.size();
    }

private:
    sead::Buffer<ActorBase*>    mActor;
    u32                         mCount;
    iterator                    mpActorLast;
    u32                         _10;
    u8                          _14;
};
static_assert(sizeof(ActorObjBuffer) == 0x18);
