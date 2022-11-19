#pragma once

#include <container/seadBuffer.h>

class ActorBase;
class ActorMgr;

class ActorObjBuffer
{
public:
    typedef ActorBase* const* iterator;

public:
    ActorObjBuffer(sead::Heap* heap, s32 size);

private:
    sead::Buffer<ActorBase*> mActor;
    u32 mCount;
    iterator mpActorLast;
    u32 _10;
    u8 _14;

    friend class ActorMgr;
};
static_assert(sizeof(ActorObjBuffer) == 0x18, "ActorObjBuffer size mismatch");
