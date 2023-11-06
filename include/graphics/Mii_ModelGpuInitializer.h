#pragma once

#include <graphics/ModelFFL.h>

#include <container/PtrArray.h>

namespace Mii {

class ModelGpuInitializer
{
public:
    ModelGpuInitializer();
    ~ModelGpuInitializer();

    void initialize();
    void initializeGpu();

    void pushBack(ModelFFL* p_model);

    void calc();

private:
    enum ElementType
    {
        cElementType_ModelFFL = 0
    };
    static_assert(sizeof(ElementType) == 4);

    struct Element
    {
        Element(ModelFFL* p_model)
            : type(cElementType_ModelFFL)
            , element(p_model)
        {
        }

        ElementType type;
        void*       element;
    };
    static_assert(sizeof(Element) == 8);

    FixedPtrArray<Element, 64>  mElement;
    FixedPtrArray<Element, 64>  mDoubleBuffer[2];
    s32                         mDoubleBufferIndex;
};
//static_assert(sizeof(ModelGpuInitializer) == 0x3A8);

}
