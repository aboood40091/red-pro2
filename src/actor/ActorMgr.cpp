#include <actor/ActorMgr.h>

ActorMgr* ActorMgr::sInstance = nullptr;

ActorMgr::iterator
ActorMgr::searchBaseByProfID(u32 id, iterator pp_start) const
{
    ActorComparatorProfID cmp(id);
    return mActorObjBuffer.searchBaseByComparator(cmp, pp_start);
}
