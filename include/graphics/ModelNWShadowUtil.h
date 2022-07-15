#pragma once

#include <container/seadBuffer.h>
#include <heap/seadHeap.h>
#include <prim/seadBitFlag.h>

class ModelNWShadowUtil
{
public:
    static void allocBuffer(sead::Buffer<sead::BitFlag32>& buffer, s32 num_shape, sead::Heap* heap, s32 alignment = 0x20);
};
