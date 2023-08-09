#include <actor/ActorBase.h>
#include <actor/ActorFindFunc.h>
#include <actor/ActorPtrCache.h>

ActorPtrCache::iterator ActorPtrCache::find(ActorFindFunc* p_func, iterator pp_start) const
{
    iterator itr_actor = end();

    if (pp_start >= begin() && pp_start <= end())
    {
        for (itr_actor = pp_start; itr_actor != end(); ++itr_actor)
        {
            ActorBase* const p_actor = *itr_actor;
            if (p_actor != nullptr && !p_actor->isDeleted() && (*p_func)(*p_actor))
                break;
        }
    }

    return itr_actor;
}
