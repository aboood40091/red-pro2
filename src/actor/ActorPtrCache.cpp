#include <actor/ActorBase.h>
#include <actor/ActorFindFunc.h>
#include <actor/ActorPtrCache.h>

ActorPtrCache::iterator ActorPtrCache::find(ActorFindFunc* io_find_func, iterator it_start) const
{
    // SEAD_ASSERT_MSG(io_find_func != nullptr, "io_find_func must be valid(%08x).", uintptr(io_find_func));

    if (it_start < getActorBegin())
    {
        // SEAD_ASSERT_MSG(false, "検索を開始する先頭のイテレータ（0x%08x）が getActorBegin() の値（0x%08x）よりも前です。\n", uintptr(it_start), uintptr(getActorBegin()));
        return getActorEnd();
    }

    if (it_start > getActorEnd())
    {
        // SEAD_ASSERT_MSG(false, "検索を開始する先頭のイテレータ（0x%08x）が getActorEnd() の値（0x%08x）よりも後ろです。\n", uintptr(it_start), uintptr(getActorEnd()));
        return getActorEnd();
    }

    iterator it = it_start;

    for (; it != getActorEnd(); ++it)
    {
        if (*it == nullptr)
        {
            // SEAD_ASSERT_MSG(false, "it must be valid(%08x).", uintptr(*it));
            continue;
        }

        if (!(*it)->isRequestedDelete() && (*io_find_func)(**it))
            break;
    }

    return it;
}
