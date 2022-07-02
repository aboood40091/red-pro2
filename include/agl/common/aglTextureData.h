#pragma once

#include <common/aglTextureEnum.h>

namespace agl {

class TextureData
{
public:
    TextureData();
    virtual ~TextureData();

    /* agl::TextureType */ GX2SurfaceDim getTextureType() const { return mSurface.dim; }

    /* agl::TextureCompSel */ u32 getComponentR() const { return mCompR; }
    /* agl::TextureCompSel */ u32 getComponentG() const { return mCompG; }
    /* agl::TextureCompSel */ u32 getComponentB() const { return mCompB; }
    /* agl::TextureCompSel */ u32 getComponentA() const { return mCompA; }

private:
    TextureFormat mFormat;
    GX2Surface mSurface;
    u32 mWidth;
    u32 mHeight;
    u32 mDepth;
    u32 mImageByteSize;
    u32 mCompR; // agl::TextureCompSel
    u32 mCompG; // ^^
    u32 mCompB; // ^^
    u32 mCompA; // ^^
};
static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
