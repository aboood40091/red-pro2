#include <actor/ActorBase.h>
#include <actor/ActorMgr.h>
#include <actor/Profile.h>
#include <event/EventMgr.h>

#include <heap/seadHeapMgr.h>

s32 ActorBase::getProfileID() const
{
    return mpActorProfile->getID();
}

void ActorBase::removeChild(ActorBase* p_child)
{
    mChildList.erase(p_child);
    p_child->mpParent = nullptr;
}

ActorBase::ActorBase(const ActorCreateParam& param)
    : mpActorHeap(sead::HeapMgr::instance()->getCurrentHeap())
    , mActorUniqueID(ActorMgr::instance()->mActorCreateID)
    , mpActorProfile(param.p_profile)
    , mCreateImmediately(ActorMgr::instance()->mActorCreateImmediately)
    , _d(param._28 != nullptr)
    , mIsActive(false)
    , mRequestDelete(false)
    , mParam0(param.param_0)
    , mParam1(param.param_1)
    , mMovementID(param.movement_id)
    , mLinkID(param.link_id)
    , mInitStateFlag(param.init_state_flag)
  //, mChildList()
  //, mChildNode()
    , mpParent(ActorMgr::instance()->mActorPtrCache.getActorPtr(param.parent_id))
  //, mExecuteNode()
  //, mDrawNode()
  //, mFlag()
{
    mChildList.initOffset(offsetof(ActorBase, mChildNode));

    if (mpParent != nullptr)
    {
        mpParent->mChildList.pushBack(this);
    }
    else
    {
        if (param.parent_id.isValid())
            mRequestDelete = true;
    }
}

ActorBase::~ActorBase()
{
    while (true)
    {
        ActorBase* p_child = mChildList.front();
        if (p_child == nullptr)
            break;

        removeChild(p_child);
    }

    if (mpParent != nullptr)
        mpParent->removeChild(this);
}

s32 ActorBase::preCreate_()
{
    return 1;
}

s32 ActorBase::create_()
{
    return 1;
}

void ActorBase::postCreate_(MainState state)
{
    switch (state)
    {
    case cState_Cancelled:
        break;
    case cState_Error:
        break;
    case cState_Success:
        break;
    case cState_Waiting:
        break;
    }
}

s32 ActorBase::preExecute_()
{
    EventMgr* event_mgr = EventMgr::instance();
    if (event_mgr == nullptr || event_mgr->getCurrentEvent() == nullptr)
        return 1;

    return static_cast<s32>(event_mgr->isJoin(this));
}

s32 ActorBase::execute_()
{
    return 1;
}

void ActorBase::postExecute_(MainState state)
{
    switch (state)
    {
    case cState_Cancelled:
        break;
    case cState_Error:
        break;
    case cState_Success:
        break;
    }
}

void ActorBase::finalUpdate_()
{
}

s32 ActorBase::preDraw_()
{
    return 1;
}

s32 ActorBase::draw_()
{
    return 1;
}

void ActorBase::postDraw_(MainState state)
{
    switch (state)
    {
    case cState_Cancelled:
        break;
    case cState_Error:
        break;
    case cState_Success:
        break;
    }
}

s32 ActorBase::preDelete_()
{
    return 1;
}

s32 ActorBase::doDelete_()
{
    return 1;
}

void ActorBase::postDelete_(MainState state)
{
    switch (state)
    {
    case cState_Cancelled:
        break;
    case cState_Error:
        break;
    case cState_Success:
        break;
    case cState_Waiting:
        break;
    }
}
