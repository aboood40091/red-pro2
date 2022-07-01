#define override
#include <graphics/MaterialEx.h>

namespace {

const sead::SafeString sTexMtxStr[8] = {
    "texmtx0",
    "texmtx1",
    "texmtx2",
    "texmtx3",
    "texmtx4",
    "texmtx5",
    "texmtx6",
    "texmtx7"
};

const sead::SafeString sTevColorStr[3] = {
    "tev_color0",
    "tev_color1",
    "tev_color2"
};

const sead::SafeString sTevKColorStr[4] = {
    "konst0",
    "konst1",
    "konst2",
    "konst3"
};

}

void MaterialEx::setTexSrtMtx(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            nw::g3d::res::TexSrtEx& srt = *mMaterialObj->EditShaderParam<nw::g3d::res::TexSrtEx>(param_index);

            f32 sin_r, cos_r;
            sead::Mathf::sinCosIdx(&sin_r, &cos_r, rotate);

            sead::Matrix34f& mtx = getTexSrtMtx(index); // mTexSrtMtx[index]

            mtx.m[0][0] =  scale.x * cos_r;
            mtx.m[0][1] =  scale.x * sin_r;
            mtx.m[0][2] =  0.0f;
            mtx.m[0][3] =  translate.x;

            mtx.m[1][0] = -scale.y * sin_r;
            mtx.m[1][1] =  scale.y * cos_r;
            mtx.m[1][2] =  0.0f;
            mtx.m[1][3] =  translate.y;

            mtx.m[2][0] =  0.0f;
            mtx.m[2][1] =  0.0f;
            mtx.m[2][2] =  0.0f;
            mtx.m[2][3] =  1.0f;

            srt.pEffectMtx = (nw::g3d::math::Mtx34*)(&mtx);
        }
    }
}

void MaterialEx::setTexSrt(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            nw::g3d::res::TexSrt& srt = mMaterialObj->EditShaderParam<nw::g3d::res::TexSrtEx>(param_index)->srt;
            srt.sx = scale.x;
            srt.sy = scale.y;
            srt.r  = sead::Mathf::idx2rad(rotate);
            srt.tx = translate.x;
            srt.ty = translate.y;
        }
    }
}

void MaterialEx::getTexSrt(s32 index, sead::Vector2f* p_scale, u32* p_rotate, sead::Vector2f* p_translate) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTexMtxStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            const nw::g3d::res::TexSrt& srt = mMaterialObj->GetShaderParam<nw::g3d::res::TexSrtEx>(param_index)->srt;
            if (p_scale)
            {
                p_scale->x = srt.sx;
                p_scale->y = srt.sy;
            }
            if (p_rotate)
            {
                *p_rotate = sead::Mathf::rad2idx(srt.r);
            }
            if (p_translate)
            {
                p_translate->x = srt.tx;
                p_translate->y = srt.ty;
            }
            return;
        }
    }

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

void MaterialEx::setTevColor(s32 index, const sead::Color4f& color)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevColorStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            sead::MemUtil::copy(mMaterialObj->EditShaderParam<nw::g3d::math::Vec4>(param_index),
                                &color.r,
                                sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialEx::getTevColor(s32 index, sead::Color4f& color) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevColorStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            sead::MemUtil::copy(&color.r,
                                mMaterialObj->GetShaderParam<nw::g3d::math::Vec4>(param_index),
                                sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialEx::setTevKColor(s32 index, const sead::Color4f& color)
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevKColorStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            sead::MemUtil::copy(mMaterialObj->EditShaderParam<nw::g3d::math::Vec4>(param_index),
                                &color.r,
                                sizeof(nw::g3d::math::Vec4));
        }
    }
}

void MaterialEx::getTevKColor(s32 index, sead::Color4f& color) const
{
    s32 param_index = mMaterialObj->GetResource()->GetShaderParamIndex(sTevKColorStr[index].cstr());
    if (param_index >= 0)
    {
        if (mMaterialObj->GetResShaderParam(param_index)->GetOffset() >= 0)
        {
            sead::MemUtil::copy(&color.r,
                                mMaterialObj->GetShaderParam<nw::g3d::math::Vec4>(param_index),
                                sizeof(nw::g3d::math::Vec4));
        }
    }
}
