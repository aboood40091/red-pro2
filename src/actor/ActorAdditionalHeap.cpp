#include <actor/ActorAdditionalHeap.h>
#include <actor/ActorMgr.h>

void ActorAdditionalHeap::create()
{
    ActorMgr::instance()->createAdditionalHeap(&mpHeap);
}

void ActorAdditionalHeap::destroy()
{
    if (ActorMgr::instance() != nullptr)
        ActorMgr::instance()->destroyAdditionalHeap(&mpHeap);
}
