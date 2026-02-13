#include <actor/ActorMgr.h>
#include <actor/ActorFindFunc.h>
#include <actor/Profile.h>
#include <item/ItemBase.h>
#include <map_obj/ChibiYoshiBase.h>
#include <player/Yoshi.h>

#include <heap/seadFrameHeap.h>
#include <heap/seadUnitHeap.h>

SEAD_SINGLETON_DISPOSER_IMPL(ActorMgr)

ActorMgr::ActorMgr()
    : mpPlayerUnitHeap(nullptr)
    , mpActorUnitHeap(nullptr)
    , mActorPtrCache(sead::HeapMgr::instance()->getCurrentHeap(), 520)
    , mActorCreateImmediately(false)
    , mActorDrawDone(false)
{
    mCreateManage.initOffset(offsetof(ActorBase, mExecuteNode));
    mDeleteManage.initOffset(offsetof(ActorBase, mExecuteNode));
    mExecuteManage.initOffset(offsetof(ActorBase, mExecuteNode));
    mDrawManage.initOffset(offsetof(ActorBase, mDrawNode));
}

ActorMgr::~ActorMgr()
{
    moveActorOnCreateListToDestoryList_();

    for (ActorBase::List::robustIterator itr = mExecuteManage.robustBegin(), itr_end = mExecuteManage.robustEnd(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        mExecuteManage.erase(p_actor);
        mDeleteManage.pushBack(p_actor);
    }

    doDeleteActors_(true);
}

ActorBase* ActorMgr::doConstructActor_(const ActorCreateParam& param, bool create_immediately)
{
    ActorBase* p_actor = nullptr;
    sead::Heap* heap = nullptr;

    s32 profile_id = param.p_profile->getID();

    if (profile_id == ProfileInfo::cProfileID_PlayerObject ||
        profile_id == ProfileInfo::cProfileID_TottenPlayer ||
        profile_id == ProfileInfo::cProfileID_CourseSelectPlayer ||
        profile_id == ProfileInfo::cProfileID_CourseSelectPlayer2PSub)
    {
        heap = sead::FrameHeap::tryCreate(0, "PlayerHeap", mpPlayerUnitHeap);
    }
    else
    {
        heap = sead::FrameHeap::tryCreate(0, "ActorHeap", mpActorUnitHeap);
    }

    if (heap != nullptr)
    {
        mActorCreateID.setValue(mActorPtrCache.getEmptyHeadIndex(), mActorPtrCache.getNextCreateIndex());
        mActorCreateImmediately = create_immediately;

        sead::CurrentHeapSetter chs(heap);

        p_actor = (*param.p_profile->getActorFactory())(param);
        mActorPtrCache.pushActor(p_actor);
    }

    return p_actor;
}

ActorBase::MainState ActorMgr::doCreate_(ActorBase* p_actor)
{
    if (p_actor->isActive())
        return ActorBase::cState_Success;

    ActorBase::MainState create_state = ActorBase::cState_None;

    if (p_actor->preCreate_())
    {
        sead::CurrentHeapSetter chs(p_actor->getActorHeap());

        switch (p_actor->create_())
        {
        case ActorBase::cResult_Wait:       create_state = ActorBase::cState_Wait;      break;
        case ActorBase::cResult_Success:    create_state = ActorBase::cState_Success;   break;
        case ActorBase::cResult_Failed:     create_state = ActorBase::cState_Failed;    break;
        }
    }
    p_actor->postCreate_(create_state);

    if (create_state == ActorBase::cState_Success)
        p_actor->setActive_(true);

    return create_state;
}

void ActorMgr::delete_(ActorBase* p_actor)
{
    p_actor->deleteRequest();
}

void ActorMgr::doDelete_(ActorBase* p_actor)
{
    mExecuteManage.erase(p_actor);

    s32 draw_priority = ProfileInfo::getDrawPriority(p_actor->getProfileID());
    if (draw_priority >= 0)
        mDrawManage.erase(p_actor);

    mDeleteManage.pushBack(p_actor);

    for (ActorBase::List::iterator itr = p_actor->mChildList.begin(); itr != p_actor->mChildList.end(); ++itr)
        delete_(&(*itr));
}

void ActorMgr::pushExecuteAndDrawList_(ActorBase* p_actor)
{
    s32 profile_id = p_actor->getProfileID();

    bool added = false;

    for (ActorBase::List::iterator itr = mExecuteManage.begin(), itr_end = mExecuteManage.end(); itr != itr_end; ++itr)
    {
        if (profile_id <= itr->getProfileID())
        {
            mExecuteManage.insertBefore(&(*itr), p_actor);
            added = true;
            break;
        }
    }

    if (!added)
        mExecuteManage.pushBack(p_actor);

    s32 draw_priority = ProfileInfo::getDrawPriority(p_actor->getProfileID());
    if (draw_priority >= 0)
    {
        bool added = false;

        for (ActorBase::List::iterator itr = mDrawManage.begin(), itr_end = mDrawManage.end(); itr != itr_end; ++itr)
        {
            if (draw_priority <= ProfileInfo::getDrawPriority(itr->getProfileID()))
            {
                mDrawManage.insertBefore(&(*itr), p_actor);
                added = true;
                break;
            }
        }

        if (!added)
            mDrawManage.pushBack(p_actor);
    }
}

bool ActorMgr::deleteNotRequested_(ActorBase* p_actor)
{
    return !p_actor->isRequestedDelete();
}

void ActorMgr::moveActorOnCreateListToDestoryList_()
{
    for (ActorBase::List::robustIterator itr = mCreateManage.robustBegin(), itr_end = mCreateManage.robustEnd(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        mCreateManage.erase(p_actor);
        mDeleteManage.pushBack(p_actor);
    }
}

void ActorMgr::doDeleteActors_(bool destroy)
{
    bool keep_heap = false;

    if (!mActorDrawDone && !destroy)
        keep_heap = true;

    else
    {
        if (mActorDeleteHeap.size() > 0)
        {
            for (sead::PtrArray<sead::Heap>::iterator itr = mActorDeleteHeap.begin(), itr_end = mActorDeleteHeap.end(); itr != itr_end; ++itr)
                itr->destroy();

            mActorDeleteHeap.clear();
        }
    }

    mActorDrawDone = false;

    for (ActorBase::List::robustIterator itr = mDeleteManage.robustBegin(), itr_end = mDeleteManage.robustEnd(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        ActorBase::MainState delete_state = ActorBase::cState_None;
        if (destroy && !p_actor->isActive())
            delete_state = ActorBase::cState_Success;

        else
        {
            bool res = p_actor->preDelete_();
            if (destroy || res)
            {
                switch (p_actor->doDelete_())
                {
                case ActorBase::cResult_Wait:       delete_state = ActorBase::cState_Wait;      break;
                case ActorBase::cResult_Success:    delete_state = ActorBase::cState_Success;   break;
                case ActorBase::cResult_Failed:     delete_state = ActorBase::cState_Failed;    break;
                }
            }
            p_actor->postDelete_(delete_state);

            if (destroy && delete_state != ActorBase::cState_Success)
                delete_state = ActorBase::cState_Failed;
        }

        switch (delete_state)
        {
        case ActorBase::cState_Failed:
        case ActorBase::cState_Success:
            break;
        default:
            continue;
        }

        mDeleteManage.erase(p_actor);
        mActorPtrCache.popActor(p_actor);

        sead::Heap* heap = p_actor->getActorHeap();

        delete p_actor;

        if (keep_heap)
        {
            heap->freeAll();
            mActorDeleteHeap.pushBack(heap);
        }
        else
        {
            heap->destroy();
        }
    }
}

void ActorMgr::initialize(sead::Heap* heap)
{
    mpPlayerUnitHeap = sead::UnitHeap::tryCreateWithBlockNum(0x001A0000 + 0x200,   4, "PlayerUnitHeap", 4, heap);
    mpActorUnitHeap  = sead::UnitHeap::tryCreateWithBlockNum(0x00020000 + 0x200, 512, "ActorUnitHeap",  4, heap);
}

void ActorMgr::createAdditionalHeap(sead::Heap** pp_heap)
{
    if (*pp_heap == nullptr)
        *pp_heap = sead::FrameHeap::tryCreate(0, "ActorAdditionalHeap", mpActorUnitHeap);
}

void ActorMgr::destroyAdditionalHeap(sead::Heap** pp_heap)
{
    if (*pp_heap != nullptr)
    {
        (*pp_heap)->destroy();
        *pp_heap = nullptr;
    }
}

namespace {

void RequestDeleteNotPlayerYoshiItem(ActorBase* p_actor, u32)
{
    if (p_actor->getProfileID() == ProfileInfo::cProfileID_PlayerObject || p_actor->getProfileID() == ProfileInfo::cProfileID_TottenPlayer)
        return;

    if (p_actor->getProfileID() == ProfileInfo::cProfileID_Yoshi)
    {
        Yoshi* p_yoshi = sead::DynamicCast<Yoshi>(p_actor);
        if (p_yoshi != nullptr && p_yoshi->getPlayerNo() != -1)
            return;
    }

    ChibiYoshiBase* p_chibiyoshi = sead::DynamicCast<ChibiYoshiBase>(p_actor);
    if (p_chibiyoshi != nullptr && p_chibiyoshi->_1a78 != 0)
        return;

    ItemBase* p_item = sead::DynamicCast<ItemBase>(p_actor);
    if (p_item != nullptr && p_item->getEatenByYoshi() != nullptr)
        return;

    p_actor->deleteRequest();
}

}

void ActorMgr::destroy()
{
    mActorPtrCache.forEach(RequestDeleteNotPlayerYoshiItem, 0);

    moveActorOnCreateListToDestoryList_();

    for (ActorBase::List::robustIterator itr = mExecuteManage.robustBegin(), itr_end = mExecuteManage.robustEnd(); itr != itr_end; ++itr)
        if (itr->mDeleteRequestFlag)
            doDelete_(&(*itr));

    doDeleteActors_(true);
}

void ActorMgr::createLater(const ActorCreateParam& param)
{
    mDeferredActorCreate.pushBack(param);
}

ActorBase* ActorMgr::createImmediately(const ActorCreateParam& param, CreateOption option)
{
    ActorBase* p_actor = doConstructActor_(param, true);
    if (p_actor != nullptr)
    {
        ActorBase::MainState create_state = doCreate_(p_actor);
        switch (create_state)
        {
        case ActorBase::cState_Success:
            if (option == cCreateOption_ActiveLater)
                mCreateManage.pushBack(p_actor);
            else if (option == cCreateOption_ActiveImmediately)
                pushExecuteAndDrawList_(p_actor);
            return p_actor;
        case ActorBase::cState_None:
        case ActorBase::cState_Failed:
        case ActorBase::cState_Wait:
            p_actor->deleteRequest();
            mDeleteManage.pushBack(p_actor);
            break;
        }
    }
    return nullptr;
}

ActorMgr::iterator ActorMgr::find(s32 i_profile_id, iterator pp_start) const
{
    ActorProfileFindFunc func(i_profile_id);
    return mActorPtrCache.find(&func, pp_start);
}

u32 ActorMgr::count(s32 i_profile_id) const
{
    ActorProfileFindFunc func(i_profile_id);
    return mActorPtrCache.count(&func);
}

void ActorMgr::calcCreateDelete_()
{
    doDeleteActors_(false);

  //bool continue_loop = true;

    for (sead::RingBuffer<ActorCreateParam>::iterator itr = mDeferredActorCreate.begin(), itr_end = mDeferredActorCreate.end(); /* continue_loop && */ itr != itr_end; ++itr)
    {
        ActorBase* p_actor = doConstructActor_(*itr, false);
        if (p_actor != nullptr)
            mCreateManage.pushBack(p_actor);
    }

    mDeferredActorCreate.clear();

    for (ActorBase::List::robustIterator itr = mCreateManage.robustBegin(), itr_end = mCreateManage.robustEnd(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        ActorBase::MainState create_state = doCreate_(p_actor);
        switch (create_state)
        {
        case ActorBase::cState_Success:
            mCreateManage.erase(p_actor);
            pushExecuteAndDrawList_(p_actor);
            break;
        case ActorBase::cState_Failed:
            p_actor->deleteRequest();
            mCreateManage.erase(p_actor);
            mDeleteManage.pushBack(p_actor);
            break;
        }
    }
}

void ActorMgr::execute()
{
    calcCreateDelete_();

    for (ActorBase::List::robustIterator itr = mExecuteManage.robustBegin(), itr_end = mExecuteManage.robustEnd(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        if (deleteNotRequested_(p_actor))
        {
            ActorBase::MainState execute_state = ActorBase::cState_None;

            if (p_actor->preExecute_())
            {
                if (p_actor->execute_())
                    execute_state = ActorBase::cState_Success;

                else
                {
                    execute_state = ActorBase::cState_Failed;
                    p_actor->deleteRequest();
                }
            }
            p_actor->postExecute_(execute_state);
        }

        if (p_actor->mDeleteRequestFlag)
            doDelete_(p_actor);
    }

    if (mActorFinalUpdate.size() > 0)
    {
        for (sead::PtrArray<ActorBase>::iterator itr = mActorFinalUpdate.begin(), itr_end = mActorFinalUpdate.end(); itr != itr_end; ++itr)
            if (deleteNotRequested_(&(*itr)))
                itr->finalUpdate_();

        mActorFinalUpdate.clear();
    }
}

void ActorMgr::addToFinalUpdate(ActorBase* p_actor)
{
    mActorFinalUpdate.pushBack(p_actor);
}

void ActorMgr::draw()
{
    mActorDrawDone = true;

    for (ActorBase::List::iterator itr = mDrawManage.begin(), itr_end = mDrawManage.end(); itr != itr_end; ++itr)
    {
        ActorBase* p_actor = &(*itr);

        if (!p_actor->isRequestedDelete())
        {
            ActorBase::MainState draw_state = ActorBase::cState_None;

            if (p_actor->preDraw_())
            {
                if (p_actor->draw_())
                    draw_state = ActorBase::cState_Success;
                else
                    draw_state = ActorBase::cState_Failed;
            }
            p_actor->postDraw_(draw_state);
        }
    }
}
