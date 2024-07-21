#include <effect/EffectGroupID.h>
#include <effect/PtclParallelExecuter.h>
#include <system/ParallelExecuter.h>
#include <system/ThreadUtil.h>

#include <mc/seadCoreInfo.h>
#include <prim/seadDelegate.h>

static const s32 cPriority = THREAD_PRIORITY(ParallelExecuter);
static const sead::CoreId cExecuterCore[PtclParallelExecuter::cExecuterNum] = {
    sead::CoreId::cMain,
    sead::CoreId::cSub2
};

s32 PtclParallelExecuter::comparePtcl_(const nw::eft::EmitterInstance* a, const nw::eft::EmitterInstance* b)
{
    return b->ptclNum - a->ptclNum;
}

s32 PtclParallelExecuter::compareChildPtcl_(const nw::eft::EmitterInstance* a, const nw::eft::EmitterInstance* b)
{
    return b->childPtclNum - a->childPtclNum;
}

void PtclParallelExecuter::run_(Step step)
{
    mEmitterCurrentIdx.setValueNonAtomic(0);
    mEmitter.clear();

    for (s32 group = 0; group < cEffectGroupID_Num; group++)
        for (nw::eft::EmitterInstance* p_emitter = mpPtclSystem->GetEmitter(group, 0); p_emitter; p_emitter = p_emitter->next)
            mEmitter.pushBack(p_emitter);

    if (!mEmitter.isEmpty())
    {
        switch (step)
        {
        case cStep_Ptcl:
            mEmitter.heapSort(&PtclParallelExecuter::comparePtcl_);
            break;
        case cStep_ChildPtcl:
            mEmitter.heapSort(&PtclParallelExecuter::compareChildPtcl_);
            break;
        }
    }

    for (sead::PtrArray<ParallelExecuter>::iterator itr = mExecuter.begin(), itr_end = mExecuter.end(); itr != itr_end; ++itr)
        itr->p_event->resetSignal();

    for (sead::PtrArray<ParallelExecuter>::iterator itr = mExecuter.begin(), itr_end = mExecuter.end(); itr != itr_end; ++itr)
        itr->p_thread->sendMessage(step, sead::MessageQueue::cNoBlock);

    for (sead::PtrArray<ParallelExecuter>::iterator itr = mExecuter.begin(), itr_end = mExecuter.end(); itr != itr_end; ++itr)
        itr->p_event->wait();
}

void PtclParallelExecuter::runCallback_(sead::Thread*, sead::MessageQueue::Element step)
{
    u32 idx_exec = 0;

    switch (Step(step))
    {
    case cStep_Ptcl:
        {
            sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
            nw::eft::CpuCore eftCore = nw::eft::CpuCore(sead::CoreInfo::getPlatformCoreId(core));

            sead::PtrArray<ParallelExecuter>::iterator itr = mExecuter.begin();
            for (sead::PtrArray<ParallelExecuter>::iterator itr_end = mExecuter.end(); itr != itr_end; ++itr)
            {
                if (cExecuterCore[idx_exec] == core)
                    break;
                idx_exec++;
            }

            u32 size = mEmitter.size();
            u32 index;
            while (index = mEmitterCurrentIdx.increment(), index < size)
                mpPtclSystem->CalcParticle(mEmitter.unsafeAt(index), eftCore);

            itr->p_event->setSignal();
        }
        break;
    case cStep_ChildPtcl:
        {
            sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
            nw::eft::CpuCore eftCore = nw::eft::CpuCore(sead::CoreInfo::getPlatformCoreId(core));

            sead::PtrArray<ParallelExecuter>::iterator itr = mExecuter.begin();
            for (sead::PtrArray<ParallelExecuter>::iterator itr_end = mExecuter.end(); itr != itr_end; ++itr)
            {
                if (cExecuterCore[idx_exec] == core)
                    break;
                idx_exec++;
            }

            u32 size = mEmitter.size();
            u32 index;
            while (index = mEmitterCurrentIdx.increment(), index < size)
                mpPtclSystem->CalcChildParticle(mEmitter.unsafeAt(index), eftCore);

            itr->p_event->setSignal();
        }
        break;
    }
}

PtclParallelExecuter::PtclParallelExecuter(sead::Heap* heap, PtclMgr* p_mgr, sead::ptcl::PtclSystem* p_system)
    : mpPtclSystem(p_system)
    , mEmitterCurrentIdx(0)
{
    for (s32 i = 0; i < cExecuterNum; i++)
    {
        if (i >= sead::CoreInfo::getNumCores())
            continue; // Whoever wrote this at Nintendo mistakenly didn't "break" instead

        ParallelExecuter* p_exec = new (heap) ParallelExecuter;
        {
            p_exec->p_thread = new (heap) sead::DelegateThread(
                "PtclParallelExecuter",
                new sead::Delegate2<PtclParallelExecuter, sead::Thread*, sead::MessageQueue::Element>(
                    this,
                    &PtclParallelExecuter::runCallback_
                ),
                heap,
                cPriority,
                sead::MessageQueue::cBlock,
                sead::DelegateThread::cDefaultQuitMsg,
                sead::DelegateThread::cDefaultStackSize * 2,
                sead::DelegateThread::cDefaultMsgQueueSize
            );
            p_exec->p_thread->setAffinity(sead::CoreIdMask(cExecuterCore[i]));
            p_exec->p_thread->start();

            p_exec->p_event = new (heap) sead::Event(true);

            p_exec->p_id = new (heap) ParallelExecuterID("PtclParallel");
        }
        mExecuter.pushBack(p_exec);
    }
}

void PtclParallelExecuter::execute()
{
    run_(cStep_Ptcl);

    mpPtclSystem->EmitChildParticle();
    run_(cStep_ChildPtcl);

    mpPtclSystem->RemovePtcl();
    mpPtclSystem->FlushCache();
    mpPtclSystem->FlushGpuCache();
}
