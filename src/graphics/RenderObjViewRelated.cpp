#include <graphics/RenderObjViewRelated.h>

// TODO: Move to the proper headers
#define SEAD_MACRO_UTIL_ROUNDUP(x, y) ((x) + ((y) - 1) & ~((y) - 1))

void RenderObjViewRelated::allocBuffer(sead::Buffer<nw::g3d::ShapeObj*>& buffer, s32 num_shape, sead::Heap* heap, s32 alignment)
{
    u8* ptr = new (heap, alignment) u8[SEAD_MACRO_UTIL_ROUNDUP(sizeof(void*) * num_shape, alignment)];
    buffer.setBuffer(num_shape, (nw::g3d::ShapeObj**)ptr);
}
