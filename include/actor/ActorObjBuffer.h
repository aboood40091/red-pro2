#pragma once

#include <actor/ActorGeneral.h>

#include <container/seadBuffer.h>

class ActorObjBuffer
{
public:
    typedef ActorBase* const* iterator;

public:
    ActorObjBuffer(sead::Heap* heap, s32 size);
    ~ActorObjBuffer();

    iterator searchBaseByComparator(const ActorComparator& cmp, iterator pp_start) const;
    iterator searchBaseByComparator(const ActorComparator& cmp) const
    {
        return searchBaseByComparator(cmp, begin());
    }

    u32 countBaseByComparator(const ActorComparator& cmp) const;

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

    void pushBackBase(ActorBase* p_actor);
    void eraseBase(ActorBase* p_actor);

    void foreachBase(void (*p_callback)(ActorBase* p_actor, u32), u32);

    u32 currentID() const
    {
        return mCurrentID;
    }

private:
    sead::Buffer<ActorBase*>    mActor;
    u32                         mCount;
    iterator                    mpActorLast;
    u32                         mCurrentID;
    u8                          _14;
};
static_assert(sizeof(ActorObjBuffer) == 0x18);
