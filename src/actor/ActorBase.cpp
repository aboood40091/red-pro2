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
    , mParamEx(param.param_ex_1)
  //, mChildList()
  //, mChildNode()
    , mpParent(ActorMgr::instance()->getActorPtr(param.parent_id))
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

bool ActorBase::preCreate_()
{
    return true;
}

ActorBase::Result ActorBase::create_()
{
    return cResult_Success;
}

void ActorBase::postCreate_(MainState state)
{
    switch (state)
    {
    case cState_None:
        break;
    case cState_Failed:
        break;
    case cState_Success:
        break;
    case cState_Wait:
        break;
    }
}

bool ActorBase::preExecute_()
{
    EventMgr* event_mgr = EventMgr::instance();
    if (event_mgr == nullptr || event_mgr->getCurrentEvent() == nullptr)
        return true;

    return event_mgr->isJoin(this);
}

bool ActorBase::execute_()
{
    return true;
}

void ActorBase::postExecute_(MainState state)
{
    switch (state)
    {
    case cState_None:
        break;
    case cState_Failed:
        break;
    case cState_Success:
        break;
    }
}

void ActorBase::finalUpdate_()
{
}

bool ActorBase::preDraw_()
{
    return true;
}

bool ActorBase::draw_()
{
    return true;
}

void ActorBase::postDraw_(MainState state)
{
    switch (state)
    {
    case cState_None:
        break;
    case cState_Failed:
        break;
    case cState_Success:
        break;
    }
}

bool ActorBase::preDelete_()
{
    return true;
}

ActorBase::Result ActorBase::doDelete_()
{
    return cResult_Success;
}

void ActorBase::postDelete_(MainState state)
{
    switch (state)
    {
    case cState_None:
        break;
    case cState_Failed:
        break;
    case cState_Success:
        break;
    case cState_Wait:
        break;
    }
}
