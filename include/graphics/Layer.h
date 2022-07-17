#pragma once

#include <layer/aglLayer.h>

// No idea what the actual name of this class is

#define override

class Layer : public agl::lyr::Layer
{
    SEAD_RTTI_OVERRIDE(Layer, agl::lyr::Layer)

public:
    Layer();
    virtual ~Layer();

    void preDrawImpl(const agl::lyr::RenderInfo& render_info) const override;
    void postDrawImpl(const agl::lyr::RenderInfo& render_info) const override;

    // ...

protected:
    u8 _41c;
};
static_assert(sizeof(Layer) == 0x420, "Layer size mismatch");
