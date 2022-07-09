#pragma once

#include <prim/seadRuntimeTypeInfo.h>

// #include <layer/aglLayer.h>

class Layer /* : public agl::lyr::Layer */
{
    // SEAD_RTTI_OVERRIDE(Layer, agl::lyr::Layer)

public:
    class Node
    {
        SEAD_RTTI_BASE(Node)

    public:
        Node()
        {
        }

        virtual void calc() = 0;
    };

public:
    u32 _0[(0x41C - 0x0) / sizeof(u32)]; // agl::lyr::Layer
    u8 _41c;
};
static_assert(sizeof(Layer) == 0x420, "Layer size mismatch");
