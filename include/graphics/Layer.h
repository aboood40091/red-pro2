#pragma once

#include <layer/aglLayer.h>

// No idea what the actual name of this class is

class Layer : public agl::lyr::Layer
{
    SEAD_RTTI_OVERRIDE(Layer, agl::lyr::Layer)

public:
    Layer();
    virtual ~Layer();

    void preDraw(const agl::lyr::RenderInfo& render_info) const override;
    void postDraw(const agl::lyr::RenderInfo& render_info) const override;

    // ...

protected:
    u8  _41c;
};
static_assert(sizeof(Layer) == 0x420);
