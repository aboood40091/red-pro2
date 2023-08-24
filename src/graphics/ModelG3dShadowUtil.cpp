#include <graphics/ModelG3dShadowUtil.h>

// TODO: Move to the proper headers
#define SEAD_MACRO_UTIL_ROUNDUP(x, y) ((x) + ((y) - 1) & ~((y) - 1))

void ModelG3dShadowUtil::allocBuffer(sead::Buffer<sead::BitFlag32>& buffer, s32 num_shape, sead::Heap* heap, s32 alignment)
{
    u8* ptr = new (heap, alignment) u8[SEAD_MACRO_UTIL_ROUNDUP(sizeof(sead::BitFlag32) * num_shape, alignment)];
    buffer.setBuffer(num_shape, (sead::BitFlag32*)ptr);
}
