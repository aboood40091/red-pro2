#include <system/ChallengeResCacheMgr.h>

ChallengeResCacheMgr* ChallengeResCacheMgr::sInstance = nullptr;

sead::Heap* ChallengeResCacheMgr::getCacheHeap()
{
    return mpCacheHeap;
}

bool ChallengeResCacheMgr::isEnableCacheHeap() const
{
    return mIsEnableCacheHeap;
}
