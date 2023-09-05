#include <system/ApplicationFramework.h>
#include <system/RootTask.h>

#include <heap/seadExpHeap.h>
#include <heap/seadForegroundBucketMgr.h>
#include <heap/seadSeparateHeap.h>
#include <thread/seadThreadUtil.h>

void main(int argc, char* argv[])
{
    sead::Framework::InitializeArg init_arg;
    init_arg.heap_size = 0x3C000000;    // 960 MB
    sead::GameFrameworkCafe::initialize(init_arg);

    ApplicationFramework* fw = nullptr;

    sead::GameFrameworkCafe::CreateArg arg;
    arg.create_default_framebuffer = false;

    {
        sead::Heap* heap = sead::ExpHeap::tryCreate(0, "GameFrameworkCafe", sead::HeapMgr::getRootHeap(0));
        fw = new (heap) ApplicationFramework(arg);
        heap->adjust();
    }

    sead::ForegroundBucketMgr::instance()->initialize(
        sead::HeapMgr::getRootHeap(0),  // heap
        100,                            // block_max
        0x2800000                       // alloc_area_size (40 MB)
    );

    {
        sead::Heap* heap = sead::ExpHeap::tryCreate(0, "GraphicSystem", sead::HeapMgr::getRootHeap(0));
        sead::Vector2f fb_size(1280.0f, 720.0f);
        fw->initializeGraphicsSystem(
            heap,
            argc, argv,
            fb_size, fb_size,
            sead::ForegroundBucketMgr::instance()->getSeparateHeap()
        );
        heap->adjust();
    }

    sead::TaskBase::CreateArg task_arg(
        sead::TTaskFactory<RootTask>
    );

    sead::Framework::RunArg run_arg;
    run_arg.prepare_priority = sead::ThreadUtil::ConvertPrioritySeadToPlatform(20);

    fw->run(
        sead::HeapMgr::getRootHeap(0),
        task_arg,
        run_arg
    );
}
