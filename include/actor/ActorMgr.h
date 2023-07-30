#pragma once

#include <actor/ActorObjBuffer.h>

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <container/seadRingBuffer.h>
#include <heap/seadDisposer.h>
#include <heap/seadUnitHeap.h>

class ActorMgr
{
    SEAD_SINGLETON_DISPOSER(ActorMgr)

public:
    enum CreateOption
    {
        cCreateOption_ActiveNextFrame = 0,
        cCreateOption_ActiveNow,
        // Anything else other than above:
      //cCreateOption_Independent (most likely unintentional)
    };

public:
    typedef ActorObjBuffer::iterator iterator;

public:
    ActorMgr();
    ~ActorMgr();

private:
    ActorBase* create_(const ActorInitArg& arg, u8 lifecycle);
    ActorBase::MainState doCreate_(ActorBase* p_actor);

    static void delete_(ActorBase* p_actor);
    void doDelete_(ActorBase* p_actor);

    void addToExecuteAndDraw_(ActorBase* p_actor);

    bool deleteNotRequested_(ActorBase* p_actor);

    void moveCreateToDelete_();
    void doDeleteActors_(bool destroy);

public:
    void initialize(sead::Heap* heap);

    void createAdditionalHeap(sead::Heap** pp_heap);
    void destroyAdditionalHeap(sead::Heap** pp_heap);

    void destroy();

    void createNextFrame(const ActorInitArg& arg);
    ActorBase* create(const ActorInitArg& arg, CreateOption option = cCreateOption_ActiveNextFrame);

public:
    iterator searchBaseByProfID(u32 id, iterator pp_start) const;
    iterator searchBaseByProfID(u32 id) const
    {
        return searchBaseByProfID(id, begin());
    }

    u32 countBaseByProfID(u32 id) const;

    iterator begin() const
    {
        return mActorObjBuffer.begin();
    }

    iterator end() const
    {
        return mActorObjBuffer.end();
    }

private:
    void calcCreateDelete_();

public:
    void execute();

    void addToFinalUpdate(ActorBase* p_actor);

    void draw();

private:
    sead::UnitHeap*                             mpPlayerHeap;
    sead::UnitHeap*                             mpActorHeap;
    sead::FixedRingBuffer<ActorInitArg, 520>    mDeferredActorCreate;
    ActorBase::List                             mCreateManage;
    ActorBase::List                             mDeleteManage;
    ActorBase::List                             mExecuteManage;
    ActorBase::List                             mDrawManage;
    sead::FixedPtrArray<sead::Heap, 520>        mActorDeleteHeap;
    sead::FixedPtrArray<ActorBase, 520>         mActorFinalUpdate;
    ActorObjBuffer                              mActorObjBuffer;
    u32                                         mActorCreateID;
    u8                                          mActorCreateLifecycle;
    u8                                          _6a3d[3];
    bool                                        mActorDrawDone;
    u8                                          _6a41[3];
};
static_assert(sizeof(ActorMgr) == 0x6A44);
