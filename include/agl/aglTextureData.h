#pragma once

#include <agl/aglTextureEnum.h>

namespace agl {

class TextureData
{
public:
    TextureData();
    virtual ~TextureData();

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
