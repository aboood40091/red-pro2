#pragma once

#include <container/seadBuffer.h>
#include <heap/seadHeap.h>

#include <nw/g3d/g3d_ShapeObj.h>

class RenderObjViewRelated
{
public:
    static void allocBuffer(sead::Buffer<nw::g3d::ShapeObj*>& buffer, s32 num_shape, sead::Heap* heap, s32 alignment = 0x20);
};
