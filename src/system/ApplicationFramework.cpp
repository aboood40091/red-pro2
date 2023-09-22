#include <graphics/LayerMgr.h>
#include <input/SeadControllerMgr.h>
#include <sound/SndSceneMgr.h>
#include <system/ApplicationFramework.h>
#include <system/CommentMgr.h>
#include <system/SaveMgr.h>

#include <audio/seadAudioMgr.h>
#include <audio/cafe/seadAudioSystemCafe.h>
#include <controller/seadControllerMgr.h>
#include <controller/cafe/seadCafeWPadDeviceCafe.h>
#include <framework/seadDualScreenMethodTreeMgr.h>
#include <framework/seadTaskMgr.h>
#include <gfx/cafe/seadGraphicsCafe.h>

#include <cafe/base/PPCArch.h>
#include <cafe/pads/kpad/kpad.h>

#include <nn/act.h>
#include <nn/boss.h>
#include <nn/ffl.h>

ApplicationFramework::ApplicationFramework(const CreateArg& arg)
    : sead::GameFrameworkCafe(arg)
    , mFirstSwapDone(false)
    , _38C(1)
    , _390(0)
    , mProcUIStatus(PROCUI_STATUS_FOREGROUND)
{
}

namespace {

void ProcUISaveCallback()
{
    SaveMgr* save_mgr = SaveMgr::instance();
    if (save_mgr != nullptr)
    {
        sead::TickSpan tick_span_100_msec = sead::TickSpan::makeFromMilliSeconds(100);
        while (save_mgr->isSaving())
            sead::Thread::sleep(tick_span_100_msec);
    }
    OSSavesDone_ReadyToRelease();
}

}

void ApplicationFramework::run(sead::Heap* heap, const sead::TaskBase::CreateArg& root_create_arg, const RunArg& run_arg)
{
    ProcUIInit(ProcUISaveCallback);
    sead::Framework::run(heap, root_create_arg, run_arg);
}

void ApplicationFramework::createProcessMeter(sead::TaskBase* root_task)
{
    sead::GameFramework::createProcessMeter(root_task);
}

void ApplicationFramework::procDraw_()
{
    sead::DualScreenMethodTreeMgr* method_tree_mgr = sead::DynamicCast<sead::DualScreenMethodTreeMgr>(getMethodTreeMgr());

    GX2SampleTopGPUCycle(&(mGpuCounters[cGpuCounter_TVDrawBegin]));
    {
        if (mDefaultFrameBuffer != nullptr)
            mDefaultFrameBuffer->bind();

        method_tree_mgr->drawTop();
    }
    GX2SampleBottomGPUCycle(&(mGpuCounters[cGpuCounter_TVDrawEnd]));

    if (!isScreenShotBusy())
    {
    }

    GX2SampleTopGPUCycle(&(mGpuCounters[cGpuCounter_DRCDrawBegin]));
    {
        if (mDefaultFrameBufferDRC != nullptr)
            mDefaultFrameBufferDRC->bind();

        method_tree_mgr->drawBtm();
    }
    GX2SampleBottomGPUCycle(&(mGpuCounters[cGpuCounter_DRCDrawEnd]));

    if (!isScreenShotBusy())
    {
    }

    GX2SetContextState(sead::GraphicsCafe::instance()->getGX2ContextState());
    GX2Flush();
}

void ApplicationFramework::calc_()
{
    GX2DrawDone();

    if (mFrameBuffer != nullptr)
    {
        mFrameBuffer->copyToDisplayBuffer(mDisplayBuffer);
        mFrameBuffer = nullptr;
    }
    else if (mDefaultFrameBuffer != nullptr)
    {
        mDefaultFrameBuffer->copyToDisplayBuffer(mDisplayBuffer);
    }

    GX2SetContextState(sead::GraphicsCafe::instance()->getGX2ContextState());

    // IDEK WTF
    bool post_draw_default_drc = false;

    if (mFrameBufferDRC != nullptr)
    {
        mFrameBufferDRC->copyToDisplayBuffer(mDisplayBufferDRC);
        mFrameBufferDRC = nullptr;

        post_draw_default_drc = true;
    }
    else if (mDefaultFrameBufferDRC != nullptr)
    {
        mDefaultFrameBufferDRC->copyToDisplayBuffer(mDisplayBufferDRC);

        if (mFrameBufferDRC != nullptr)
        {
            mFrameBufferDRC->copyToDisplayBuffer(mDisplayBufferDRC);
            mFrameBufferDRC = nullptr;
        }
        else
        {
            post_draw_default_drc = true;
        }
    }

    if (post_draw_default_drc && mDefaultFrameBufferDRC != nullptr)
    {
        mDefaultFrameBufferDRC->copyToDisplayBuffer(mDisplayBufferDRC);
    }

    GX2SetContextState(sead::GraphicsCafe::instance()->getGX2ContextState());
    GX2Flush();

    getTaskMgr()->afterCalc();

    LayerMgr* layer_mgr = LayerMgr::instance();

    sead::Graphics::instance()->lockDrawContext();
    {
        layer_mgr->calcParallelExec();
    }
    sead::Graphics::instance()->unlockDrawContext();
}

void ApplicationFramework::procCalc_()
{
    LayerMgr* layer_mgr = LayerMgr::instance();

    if (_38C > 0)
    {
        if (layer_mgr != nullptr)
            layer_mgr->clearRenderMgr();

        sead::GameFrameworkCafe::procCalc_();

        sead::MethodTreeNode* app_calc_node = getMethodTreeMgr()->getRootMethodTreeNode(1);
        for (s32 i = 1; i < _38C; i++)
            app_calc_node->call();
    }
    else
    {
        s32 v = _390 + 1;
        if (v < -_38C)
        {
            _390 = v;
            return;
        }

        if (layer_mgr != nullptr)
            layer_mgr->clearRenderMgr();

        sead::GameFrameworkCafe::procCalc_();

        _390 = 0;
    }

    if (layer_mgr != nullptr)
    {
        layer_mgr->calcDL();
        calc_();
    }
}

void ApplicationFramework::swapBuffer_()
{
    if (!mFirstSwapDone && mDisplayState == cDisplayState_Show)
    {
        mFirstSwapDone = true;
        mDisplayState = cDisplayState_Ready;
        GX2SetTVEnable(GX2_ENABLE);
        GX2SetDRCEnable(GX2_ENABLE);
    }

    sead::GameFrameworkCafe::swapBuffer_();

    bool dim_enable = isDimEnable();
    ProcUIStatus prev_procui_status = mProcUIStatus;

    if (mProcUIStatus == PROCUI_STATUS_RELEASING)
    {
        if (SndSceneMgr::instance() != nullptr)
            SndSceneMgr::instance()->enterHBM();

        setDimEnable(true);

        SeadControllerMgr::instance()->enterHBM();

        ProcUIDrawDoneRelease();

        sead::Graphics::instance()->lockDrawContext();

        prev_procui_status = mProcUIStatus;
    }

    mProcUIStatus = ProcUIProcessMessages(true);

    if (mProcUIStatus == PROCUI_STATUS_EXIT)
    {
        ProcUIShutdown();

        if (SndSceneMgr::instance() != nullptr)
            SndSceneMgr::instance()->exit();

        if (sead::AudioMgr::instance() != nullptr)
        {
            sead::AudioSystemCafe* audio_system = sead::DynamicCast<sead::AudioSystemCafe>(sead::AudioMgr::instance()->getAudioSystem());
            if (audio_system != nullptr)
                audio_system->forceQuit();
        }

        FFLFlushQuota();

        nn::boss::Finalize();
        nn::act::Finalize();

        OSBlockThreadsOnExit();
        __PPCExit(-1);
    }

    if (prev_procui_status == PROCUI_STATUS_RELEASING)
    {
        if (mProcUIStatus == PROCUI_STATUS_FOREGROUND)
        {
            GX2SetContextState(sead::GraphicsCafe::instance()->getGX2ContextState());

            GX2SetTVEnable(GX2_ENABLE);
            GX2SetDRCEnable(GX2_ENABLE);

            setDimEnable(dim_enable);

            if (SndSceneMgr::instance() != nullptr)
                SndSceneMgr::instance()->exitHBM();

            {
                SeadControllerMgr::instance()->exitHBM();

                for (s32 i = 0; i < 4; i++)
                    KPADDisableDPD(i);

                if (sead::ControllerMgr::instance() != nullptr)
                    sead::ControllerMgr::instance()->getControlDeviceAs<sead::CafeWPadDevice*>()->setFreezeCounter(1);
            }

            if (CommentMgr::instance() != nullptr)
                CommentMgr::instance()->_7dd = 1;
        }

        sead::Graphics::instance()->unlockDrawContext();
    }
}

void ApplicationFramework::waitStartDisplayLoop_()
{
    sead::TickSpan tick_span_10_msec = sead::TickSpan::makeFromMilliSeconds(10);
    while (true)
    {
        sead::Graphics::instance()->lockDrawContext();
        {
            getTaskMgr()->beforeCalc();
            getTaskMgr()->afterCalc();
        }
        sead::Graphics::instance()->unlockDrawContext();

        if (getTaskMgr()->getRootTask() != nullptr || mDisplayState != cDisplayState_Hide)
            break;

        sead::Thread::sleep(tick_span_10_msec);
    }

    getMethodTreeMgr()->pauseAll(false);
}
