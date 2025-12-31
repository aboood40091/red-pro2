#include <actor/ActorBase.h>
#include <actor/ActorFindFunc.h>
#include <actor/ActorPtrCache.h>

ActorPtrCache::ActorPtrCache(sead::Heap* heap, s32 i_max_actor_num)
    : mActorPtrArray()
    , mEmptyHeadIndex(0)
    , mLiveActorEnd(nullptr)
    , mNextCreateIndex(1)
    , mCreateIndexOverflow(false)
{
    // SEAD_ASSERT(i_max_actor_num > 0);

    // SEAD_ASSERT(mActorPtrArray.isBufferReady() == false);
    mActorPtrArray.tryAllocBuffer(i_max_actor_num, heap);
    // SEAD_ASSERT(mActorPtrArray.isBufferReady());

    mActorPtrArray.fill(nullptr);
    mLiveActorEnd = &mActorPtrArray[0];
}

ActorPtrCache::~ActorPtrCache()
{
    mActorPtrArray.freeBuffer();
}

ActorPtrCache::iterator ActorPtrCache::find(ActorFindFunc* io_find_func, iterator it_begin) const
{
    // SEAD_ASSERT_MSG(io_find_func != nullptr, "io_find_func must be valid(%08x).", uintptr(io_find_func));

    if (it_begin < getActorBegin())
    {
        // SEAD_ASSERT_MSG(false, "検索を開始する先頭のイテレータ（0x%08x）が getActorBegin() の値（0x%08x）よりも前です。\n", uintptr(it_begin), uintptr(getActorBegin()));
        return getActorEnd();
    }

    if (it_begin > getActorEnd())
    {
        // SEAD_ASSERT_MSG(false, "検索を開始する先頭のイテレータ（0x%08x）が getActorEnd() の値（0x%08x）よりも後ろです。\n", uintptr(it_begin), uintptr(getActorEnd()));
        return getActorEnd();
    }

    iterator it = it_begin;

    for (; it != getActorEnd(); ++it)
    {
        // SEAD_ASSERT_MSG(it != nullptr, "it must be valid(%08x).", uintptr(*it));
        const ActorBase* p_actor = *it;
        if (p_actor != nullptr && !p_actor->isRequestedDelete() && (*io_find_func)(*p_actor))
            break;
    }

    return it;
}

void ActorPtrCache::pushActor(ActorBase* io_actor)
{
    // SEAD_ASSERT_MSG(io_actor != nullptr, "io_actor must be valid(%08x).", uintptr(io_actor));
    // SEAD_ASSERT_MSG(io_actor->getActorUniqueID() == ActorUniqueID(mEmptyHeadIndex, mNextCreateIndex), "[プログラマー向けASSERT] アクターのコンストラクタの中でアクターを即時生成しないでください。\n");

    // SEAD_ASSERT(mEmptyHeadIndex <= ActorUniqueID::cArrayIndexMax);
    // SEAD_ASSERT(mNextCreateIndex <= ActorUniqueID::cCreateIndexMax);
    // SEAD_ASSERT(mActorPtrArray[mEmptyHeadIndex] == nullptr);

    mActorPtrArray[mEmptyHeadIndex] = io_actor;

    iterator it_begin = &mActorPtrArray[mEmptyHeadIndex];
    iterator it_end = getActorBegin() + mActorPtrArray.size();

    iterator it = it_begin;

    for (; it != it_end; ++it)
    {
        if (*it == nullptr)
            break;
        mEmptyHeadIndex++;
    }

    if (mLiveActorEnd < it)
    {
        mLiveActorEnd = it;
        // SEAD_ASSERT(getActorBegin() <= mLiveActorEnd);
    }

    if (mNextCreateIndex == ActorUniqueID::cCreateIndexMax)
    {
        mCreateIndexOverflow = true;
        mNextCreateIndex = 1;
        // SEAD_WARN("生成インデックスがオーバーしました。以降は 0 から空きを探します。\n");
    }
    else
    {
        mNextCreateIndex++;
    }

    if (mCreateIndexOverflow)
    {
        ActorCreateIndexFindFunc find_func(mNextCreateIndex);
        iterator found_it = find(&find_func);
        while (found_it != getActorEnd())
        {
            mNextCreateIndex++;
            if (mNextCreateIndex == ActorUniqueID::cCreateIndexMax)
            {
                // SEAD_ASSERT_MSG(false, "アクターへのポインタ配列に空きがありませんでした。\n");
                mNextCreateIndex = 1;
                return;
            }
            find_func.setCreateIndex(mNextCreateIndex);
            found_it = find(&find_func);
        }
    }
}

void ActorPtrCache::popActor(const ActorBase* i_actor)
{
    // SEAD_ASSERT_MSG(i_actor != nullptr, "i_actor must be valid(%08x).", uintptr(i_actor));

    const ActorUniqueID& id = i_actor->getActorUniqueID();
    u32 a_array_index = id.getArrayIndex();
    // SEAD_ASSERT(a_array_index <= ActorUniqueID::cArrayIndexMax);
    // SEAD_ASSERT(a_array_index < static_cast<u32>(mActorPtrArray.size()));
    // SEAD_ASSERT(a_array_index != mEmptyHeadIndex);
    // SEAD_ASSERT(mActorPtrArray[a_array_index] == i_actor);
    mActorPtrArray[a_array_index] = nullptr;

    if (a_array_index < mEmptyHeadIndex)
        mEmptyHeadIndex = a_array_index;

    iterator it_begin = getActorBegin();

    if (mLiveActorEnd != it_begin + a_array_index + 1)
        return;

    while (mLiveActorEnd != it_begin)
    {
        if (*(mLiveActorEnd - 1) != nullptr)
            break;
        --mLiveActorEnd;
    }
}

ActorBase* ActorPtrCache::getActorPtr(ActorUniqueID id) const
{
    if (id.isValid())
    {
        u32 a_array_index = id.getArrayIndex();
        // SEAD_ASSERT(a_array_index <= ActorUniqueID::cArrayIndexMax);
        // SEAD_ASSERT(a_array_index < static_cast<u32>(mActorPtrArray.size()));
        ActorBase* p_actor = getActorBegin()[a_array_index];
        if (p_actor != nullptr && !p_actor->isRequestedDelete() && p_actor->getActorUniqueID() == id)
            return p_actor;
    }
    return nullptr;
}

u32 ActorPtrCache::count(ActorFindFunc* io_find_func) const
{
    // SEAD_ASSERT_MSG(io_find_func != nullptr, "io_find_func must be valid(%08x).", uintptr(io_find_func));

    u32 count = 0;
    for (iterator it = getActorBegin(); it != getActorEnd(); ++it)
    {
        // SEAD_ASSERT_MSG(it != nullptr, "it must be valid(%08x).", uintptr(*it));
        const ActorBase* p_actor = *it;
        if (p_actor != nullptr && !p_actor->isRequestedDelete() && (*io_find_func)(*p_actor))
            count++;
    }
    return count;
}

void ActorPtrCache::forEach(ActorForEachCallback p_callback, ActorForEachParam param) const
{
    for (iterator it = getActorBegin(); it != getActorEnd(); ++it)
    {
        // SEAD_ASSERT_MSG(it != nullptr, "it must be valid(%08x).", uintptr(*it));
        ActorBase* p_actor = *it;
        if (p_actor != nullptr && !p_actor->isRequestedDelete())
            p_callback(p_actor, param);
    }
}
