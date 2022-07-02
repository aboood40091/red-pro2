#pragma once

#include <common/aglShaderLocation.h>
#include <common/aglTextureData.h>
#include <gfx/seadColor.h>
#include <prim/seadBitFlag.h>

namespace agl {

class TextureSampler
{
public:
    TextureSampler();
    virtual ~TextureSampler();

    bool activate(const SamplerLocation& location, s32 = -1) const;

private:
    TextureData mTextureData;
    u32 mFilterMag; // agl::TextureFilterType
    u32 mFilterMin; // ^^
    u32 mFilterMip;
    u32 mWrapX;
    u32 mWrapY;
    u32 mWrapZ;
    sead::Color4f mBorderColor;
    f32 mLODMin;
    f32 mLODMax;
    f32 mLODBias;
    u32 mMaxAniso;
    bool mReplaceCompSel;
    u32 mCompR; // agl::TextureCompSel
    u32 mCompG; // ^^
    u32 mCompB; // ^^
    u32 mCompA; // ^^
    bool mIsInitialized;
    u32 mDepthCompare;
    GX2Sampler mGX2Sampler;
    GX2Texture mGX2Texture;
    bool mHasBorder;
    mutable sead::BitFlag8 mFlag;
};
static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
