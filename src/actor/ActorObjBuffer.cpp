#include <actor/ActorObjBuffer.h>

ActorObjBuffer::iterator
ActorObjBuffer::searchBaseByComparator(const ActorComparator& cmp, iterator pp_start) const
{
    iterator itr_actor = end();

    if (pp_start >= begin() && pp_start <= end())
    {
        for (itr_actor = pp_start; itr_actor != end(); ++itr_actor)
        {
            ActorBase* const p_actor = *itr_actor;
            if (p_actor != nullptr && !p_actor->isDeleted() && cmp.isEqual(*p_actor))
                break;
        }
    }

    return itr_actor;
}
