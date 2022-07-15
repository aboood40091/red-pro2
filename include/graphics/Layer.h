#pragma once

#include <basis/seadTypes.h>
// #include <layer/aglLayer.h>

// No idea what the actual name of this class is

class Layer /* : public agl::lyr::Layer */
{
    // SEAD_RTTI_OVERRIDE(Layer, agl::lyr::Layer)

protected:
    u32 _0[(0x41C - 0x0) / sizeof(u32)]; // agl::lyr::Layer
    u8 _41c;
};
static_assert(sizeof(Layer) == 0x420, "Layer size mismatch");
