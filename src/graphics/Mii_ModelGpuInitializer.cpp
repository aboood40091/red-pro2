#include <graphics/LayerMgr.h>
#include <graphics/Mii_ModelGpuInitializer.h>

#include <heap/seadUnitHeap.h>
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include <layer/aglRenderInfo.h>

namespace Mii {

ModelGpuInitializer::ModelGpuInitializer()
    : mpHeap(nullptr)
    , mDoubleBufferIndex(0)
{
    mDrawMethod.bind(this, &ModelGpuInitializer::initializeGpuDrawMethod_, "Mii Initialize Gpu");

    agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_Gather)->pushBackDrawMethod(0, &mDrawMethod);
}

ModelGpuInitializer::~ModelGpuInitializer()
{
    agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_Gather)->removeDrawMethod(0, &mDrawMethod);
}

void ModelGpuInitializer::initialize(sead::Heap* heap)
{
    mpHeap = sead::UnitHeap::tryCreateWithBlockNum(8, 64, "ModelGpuInitializer");
}

void ModelGpuInitializer::pushBack(ModelFFL* p_model)
{
    mCriticalSection.lock();
    {
        Element* element = new (mpHeap) Element(p_model);
        mElement.pushBack(element);
    }
    mCriticalSection.unlock();
}

void ModelGpuInitializer::pushBack(sead::Event* p_event)
{
    mCriticalSection.lock();
    {
        Element* element = new (mpHeap) Element(p_event);
        mElement.pushBack(element);
    }
    mCriticalSection.unlock();
}

void ModelGpuInitializer::calc()
{
    mCriticalSection.lock();
    {
        s32 index = 1 - mDoubleBufferIndex;
        {
            sead::PtrArray<Element>& elementArray = mDoubleBuffer[index];
            for (sead::PtrArray<Element>::constIterator itr = elementArray.constBegin(), itr_end = elementArray.constEnd(); itr != itr_end; ++itr)
            {
                if (itr->type == cElementType_SeadEvent)
                    static_cast<sead::Event*>(itr->element)->setSignal();

                delete &(*itr);
            }
            elementArray.clear();
        }
        mDoubleBufferIndex = index;
    }
    mCriticalSection.unlock();
}

void ModelGpuInitializer::initializeGpu_()
{
    mCriticalSection.lock();
    {
        for (sead::PtrArray<Element>::iterator itr = mElement.begin(), itr_end = mElement.end(); itr != itr_end; ++itr)
        {
            if (itr->type == cElementType_ModelFFL)
                static_cast<ModelFFL*>(itr->element)->initializeGpu();

            mDoubleBuffer[mDoubleBufferIndex].pushBack(&(*itr));
        }
        mElement.clear();
    }
    mCriticalSection.unlock();
}

void ModelGpuInitializer::initializeGpuDrawMethod_(const agl::lyr::RenderInfo& render_info)
{
    if (render_info.getRenderStep() == 0)
        initializeGpu_();
}

}
