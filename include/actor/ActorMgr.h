#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadUnitHeap.h>

#include <actor/ActorObjBuffer.h>

class ActorMgr
{
    SEAD_SINGLETON_DISPOSER(ActorMgr)

public:
    typedef ActorObjBuffer::iterator iterator;

public:
    ActorMgr();

    iterator searchBaseByProfId(u32 id, iterator pp_start);
    iterator searchBaseByProfId(u32 id)
    {
        return searchBaseByProfId(id, begin());
    }

    iterator begin() const
    {
        return &mActorObjBuffer.mActor.front();
    }

    iterator end() const
    {
        return mActorObjBuffer.mpActorLast;
    }

private:
    sead::UnitHeap* mpPlayerHeap;
    sead::UnitHeap* mpActorHeap;
    u32 mDeferredActorCreate[0x5970 / sizeof(u32)]; // sead::FixedRingBuffer<ActorInitArg, 520>
    sead::OffsetList<ActorBase> mCreateManage;
    sead::OffsetList<ActorBase> mDeleteManage;
    sead::OffsetList<ActorBase> mExecuteManage;
    sead::OffsetList<ActorBase> mDrawManage;
    sead::FixedPtrArray<sead::Heap, 520> mActorDeleteHeap;
    sead::FixedPtrArray<ActorBase, 520> mActorFinalExecute;
    ActorObjBuffer mActorObjBuffer;
    u32 mActorCreateId;
    u8 mActorCreateLifecycle;
    u8 _6a3d[3];
    bool mActorDrawDone;
    u8 _6a41[3];
};
static_assert(sizeof(ActorMgr) == 0x6A44, "ActorMgr size mismatch");
