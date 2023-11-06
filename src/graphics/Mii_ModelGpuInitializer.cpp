#include <graphics/Mii_ModelGpuInitializer.h>

namespace Mii {

ModelGpuInitializer::ModelGpuInitializer()
    : mDoubleBufferIndex(0)
{
}

ModelGpuInitializer::~ModelGpuInitializer()
{
}

void ModelGpuInitializer::initialize()
{
}

void ModelGpuInitializer::pushBack(ModelFFL* p_model)
{
  //mCriticalSection.lock();
    {
        Element* element = new Element(p_model);
        mElement.pushBack(element);
    }
  //mCriticalSection.unlock();
}

void ModelGpuInitializer::calc()
{
  //mCriticalSection.lock();
    {
        s32 index = 1 - mDoubleBufferIndex;
        {
            PtrArray<Element>& elementArray = mDoubleBuffer[index];
            for (PtrArray<Element>::constIterator itr = elementArray.constBegin(), itr_end = elementArray.constEnd(); itr != itr_end; ++itr)
                delete &(*itr);

            elementArray.clear();
        }
        mDoubleBufferIndex = index;
    }
  //mCriticalSection.unlock();
}

void ModelGpuInitializer::initializeGpu()
{
  //mCriticalSection.lock();
    {
        for (PtrArray<Element>::iterator itr = mElement.begin(), itr_end = mElement.end(); itr != itr_end; ++itr)
        {
            if (itr->type == cElementType_ModelFFL)
                static_cast<ModelFFL*>(itr->element)->initializeGpu();

            mDoubleBuffer[mDoubleBufferIndex].pushBack(&(*itr));
        }
        mElement.clear();
    }
  //mCriticalSection.unlock();
}

}
