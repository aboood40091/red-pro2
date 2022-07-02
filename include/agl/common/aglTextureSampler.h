#pragma once

#include <common/aglShaderLocation.h>
#include <common/aglTextureData.h>
#include <gfx/seadColor.h>
#include <gfx/seadGraphics.h>
#include <prim/seadBitFlag.h>

namespace agl {

class TextureSampler
{
public:
    TextureSampler();
    virtual ~TextureSampler();

    bool activate(const SamplerLocation& location, s32 = -1) const;

private:
    void initRegs_() const;

    void initTexture_() const;
    void initWrap_() const;
    void initFilter_() const;
    void initMipParam_() const;
    void initDepthComp_() const;
    void initBorderColor_() const;

private:
    TextureData mTextureData;
    u32 mFilterMag; // agl::TextureFilterType
    u32 mFilterMin; // ^^
    u32 mMipFilter;
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
    bool mIsTextureSet;
    sead::Graphics::DepthFunc mDepthComp;
    mutable GX2Sampler mGX2Sampler;
    mutable GX2Texture mGX2Texture;
    mutable bool mHasBorder;
    mutable sead::BitFlag8 mFlag;
};
static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
