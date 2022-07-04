#pragma once

#include <prim/seadRuntimeTypeInfo.h>

// #include <layer/aglLayer.h>

class Layer /* : public agl::lyr::Layer // size: 0x420 */
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
    // ...
};
