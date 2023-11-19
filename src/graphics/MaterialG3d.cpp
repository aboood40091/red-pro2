#include <graphics/MaterialG3d.h>
#include <math/Math.h>

#include <misc/rio_MemUtil.h>

#include <string>

namespace {

const char* sTexMtxStr[8] = {
    "texmtx0",
    "texmtx1",
    "texmtx2",
    "texmtx3",
    "texmtx4",
    "texmtx5",
    "texmtx6",
    "texmtx7"
};

const char* sTevColorStr[3] = {
    "tev_color0",
    "tev_color1",
    "tev_color2"
};

const char* sTevKColorStr[4] = {
    "konst0",
    "konst1",
    "konst2",
    "konst3"
};

}

void MaterialG3d::setTexSrtMtx(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            nw::g3d::res::TexSrtEx& srt = *static_cast<nw::g3d::res::TexSrtEx*>(mMaterialObj->EditShaderParam(param_index));

            f32 sin_r, cos_r;
            SinCosIdx(&sin_r, &cos_r, rotate);

            mTexSrtMtx[index].m[0][0] =  scale.x * cos_r;
            mTexSrtMtx[index].m[0][1] =  scale.x * sin_r;
            mTexSrtMtx[index].m[0][2] =  0.0f;
            mTexSrtMtx[index].m[0][3] =  translate.x;

            mTexSrtMtx[index].m[1][0] = -scale.y * sin_r;
            mTexSrtMtx[index].m[1][1] =  scale.y * cos_r;
            mTexSrtMtx[index].m[1][2] =  0.0f;
            mTexSrtMtx[index].m[1][3] =  translate.y;

            mTexSrtMtx[index].m[2][0] =  0.0f;
            mTexSrtMtx[index].m[2][1] =  0.0f;
            mTexSrtMtx[index].m[2][2] =  0.0f;
            mTexSrtMtx[index].m[2][3] =  1.0f;

            srt.pEffectMtx = (nw::g3d::math::Mtx34*)(&mTexSrtMtx[index]);
        }
    }
}

void MaterialG3d::setTexSrt(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            nw::g3d::res::TexSrt& srt = static_cast<nw::g3d::res::TexSrtEx*>(mMaterialObj->EditShaderParam(param_index))->srt;
            srt.sx = scale.x;
            srt.sy = scale.y;
            srt.r  = Idx2Rad(rotate);
            srt.tx = translate.x;
            srt.ty = translate.y;
        }
    }
}

void MaterialG3d::getTexSrt(s32 index, rio::Vector2f* p_scale, u32* p_rotate, rio::Vector2f* p_translate) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index]);
    if (param_index < 0 || mMaterialObj->GetResShaderParam(param_index)->GetOffset() < 0)
    {
        if (p_scale)
        {
            p_scale->x = 1.0f;
            p_scale->y = 1.0f;
        }
        if (p_rotate)
        {
            *p_rotate = 0;
        }
        if (p_translate)
        {
            p_translate->x = 0.0f;
            p_translate->y = 0.0f;
        }
    }
    else
    {
        const nw::g3d::res::TexSrt& srt = static_cast<const nw::g3d::res::TexSrtEx*>(mMaterialObj->GetShaderParam(param_index))->srt;
        if (p_scale)
        {
            p_scale->x = srt.sx;
            p_scale->y = srt.sy;
        }
        if (p_rotate)
        {
            *p_rotate = Rad2Idx(srt.r);
        }
        if (p_translate)
        {
            p_translate->x = srt.tx;
            p_translate->y = srt.ty;
        }
    }
}

void MaterialG3d::setTevColor(s32 index, const rio::Color4f& color)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevColorStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            rio::MemUtil::copy(mMaterialObj->EditShaderParam(param_index),
                               &color.r,
                               sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialG3d::getTevColor(s32 index, rio::Color4f& color) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevColorStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            rio::MemUtil::copy(&color.r,
                               mMaterialObj->GetShaderParam(param_index),
                               sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialG3d::setTevKColor(s32 index, const rio::Color4f& color)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevKColorStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            rio::MemUtil::copy(mMaterialObj->EditShaderParam(param_index),
                               &color.r,
                               sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialG3d::getTevKColor(s32 index, rio::Color4f& color) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevKColorStr[index]);
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            rio::MemUtil::copy(&color.r,
                               mMaterialObj->GetShaderParam(param_index),
                               sizeof(nw::g3d::math::Vec4));
        }
    }
}
