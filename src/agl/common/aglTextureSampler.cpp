#include <common/aglTextureSampler.h>

namespace agl {

void TextureSampler::initRegs_() const
{
    if (mFlag.isOn(1 << 0))
        initTexture_();

    if (mFlag.isOn(1 << 1))
        initWrap_();

    if (mFlag.isOn(1 << 2))
        initFilter_();

    if (mFlag.isOn(1 << 3))
        initMipParam_();

    if (mFlag.isOn(1 << 4))
        initDepthComp_();

    if (mFlag.isOn(1 << 5))
        initBorderColor_();

    mFlag.makeAllZero();
}

void TextureSampler::initTexture_() const
{
    if (mReplaceCompSel)
    {
        mGX2Texture.compSel = GX2_GET_COMP_SEL(mCompR,
                                               mCompG,
                                               mCompB,
                                               mCompA);
    }
    else if (mIsTextureSet)
    {
        mGX2Texture.compSel = GX2_GET_COMP_SEL(mTextureData.getComponentR(),
                                               mTextureData.getComponentG(),
                                               mTextureData.getComponentB(),
                                               mTextureData.getComponentA());
    }

    if (mIsTextureSet)
        GX2InitTextureRegs(&mGX2Texture);
}

void TextureSampler::initWrap_() const
{
    GX2InitSamplerClamping(&mGX2Sampler,
                           (GX2TexClamp)mWrapX,
                           (GX2TexClamp)mWrapY,
                           (GX2TexClamp)mWrapZ);
}

void TextureSampler::initFilter_() const
{
    GX2InitSamplerXYFilter(&mGX2Sampler,
                           (GX2TexXYFilterType)mFilterMag,
                           (GX2TexXYFilterType)mFilterMin,
                           (GX2TexAnisoRatio)mMaxAniso);

    GX2TexZFilterType z_filter = (mIsTextureSet && mTextureData.getTextureType() == GX2_SURFACE_DIM_2D_ARRAY)
                                    ? GX2_TEX_Z_FILTER_POINT
                                    : GX2_TEX_Z_FILTER_USE_XY;

    GX2InitSamplerZMFilter(&mGX2Sampler,
                           z_filter,
                           (GX2TexMipFilterType)mMipFilter);
}

void TextureSampler::initMipParam_() const
{
    GX2InitSamplerLOD(&mGX2Sampler, mLODMin, mLODMax, mLODBias);
}

void TextureSampler::initDepthComp_() const
{
    GX2InitSamplerDepthCompare(&mGX2Sampler, (GX2CompareFunction)mDepthComp);
}
void TextureSampler::initBorderColor_() const
{
    if (mBorderColor == sead::Color4f::cBlack)
    {
        GX2InitSamplerBorderType(&mGX2Sampler, GX2_TEX_BORDER_SOLID_BLACK);
        mHasBorder = false;
    }
    else if (mBorderColor == sead::Color4f::cWhite)
    {
        GX2InitSamplerBorderType(&mGX2Sampler, GX2_TEX_BORDER_SOLID_WHITE);
        mHasBorder = false;
    }
    else if (mBorderColor == sead::Color4f(0.0f, 0.0f, 0.0f, 0.0f))
    {
        GX2InitSamplerBorderType(&mGX2Sampler, GX2_TEX_BORDER_CLEAR_BLACK);
        mHasBorder = false;
    }
    else
    {
        GX2InitSamplerBorderType(&mGX2Sampler, GX2_TEX_BORDER_USE_REGISTER);
        mHasBorder = true;
    }
}

bool TextureSampler::activate(const SamplerLocation& location, s32) const
{
    if (!mFlag.isZero())
        initRegs_();

    if (!location.isValid())
        return false;

    if (location.getVertexLocation() == -1)
    {
        if (mHasBorder)
            GX2SetVertexSamplerBorderColor(location.getVertexLocation(), mBorderColor.r,
                                                                         mBorderColor.g,
                                                                         mBorderColor.b,
                                                                         mBorderColor.a);

        GX2SetVertexTexture(&mGX2Texture, location.getVertexLocation());
        GX2SetVertexSampler(&mGX2Sampler, location.getVertexLocation());
    }

    if (location.getFragmentLocation() != -1)
    {
        if (mHasBorder)
            GX2SetPixelSamplerBorderColor(location.getFragmentLocation(), mBorderColor.r,
                                                                          mBorderColor.g,
                                                                          mBorderColor.b,
                                                                          mBorderColor.a);

        GX2SetPixelTexture(&mGX2Texture, location.getFragmentLocation());
        GX2SetPixelSampler(&mGX2Sampler, location.getFragmentLocation());
    }

    if (location.getGeometryLocation() != -1)
    {
        if (mHasBorder)
            GX2SetGeometrySamplerBorderColor(location.getGeometryLocation(), mBorderColor.r,
                                                                             mBorderColor.g,
                                                                             mBorderColor.b,
                                                                             mBorderColor.a);

        GX2SetGeometryTexture(&mGX2Texture, location.getGeometryLocation());
        GX2SetGeometrySampler(&mGX2Sampler, location.getGeometryLocation());
    }

    return true;
}

}
