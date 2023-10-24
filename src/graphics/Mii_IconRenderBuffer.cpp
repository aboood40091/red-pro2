#include <graphics/Mii_IconRenderBuffer.h>

namespace Mii {

void IconRenderBuffer::initialize(sead::Heap* heap, const TextureInfo& info)
{
    getInfo() = info;
    getRenderBuffer().setVirtualSize(info.width, info.height);
    getRenderBuffer().setPhysicalArea(0, 0, info.width, info.height);
    initColor(heap);
    initDepth(heap);
}

void IconRenderBuffer::destroy()
{
}

bool IconRenderBuffer::registerModel(const ModelFFL* p_model)
{
    return false;
}

}
