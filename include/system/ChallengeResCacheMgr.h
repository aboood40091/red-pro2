#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <heap/seadFrameHeap.h>

class ChallengeResCacheMgr : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(ChallengeResCacheMgr)

public:
    ChallengeResCacheMgr(const sead::TaskConstructArg& arg);
    virtual ~ChallengeResCacheMgr() { }

    virtual void prepare();
    virtual void enter() { }
    virtual void calc() { }

    void clearCacheHeap();
    sead::Heap* getCacheHeap();
    void enableCacheHeap();
    void disableCacheHeap();
    bool isEnableCacheHeap() const;

private:
    sead::FrameHeap*    mpCacheHeap;
    bool                mIsEnableCacheHeap;
};
static_assert(sizeof(ChallengeResCacheMgr) == 0xD4);
