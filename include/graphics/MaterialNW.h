#pragma once

#include <graphics/Material.h>

#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>

#include <nw/g3d/g3d_MaterialObj.h>

class MaterialNW : public Material
{
public:
    MaterialNW(nw::g3d::MaterialObj* material)
        : mMaterialObj(material)
    {
    }

    void setTexSrtMtx(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void setTexSrt(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void getTexSrt(s32 index, sead::Vector2f* p_scale = nullptr, u32* p_rotate = nullptr, sead::Vector2f* p_translate = nullptr) const override;
    void setTevColor(s32 index, const sead::Color4f& color) override;
    void getTevColor(s32 index, sead::Color4f& color) const override;
    void setTevKColor(s32 index, const sead::Color4f& color) override;
    void getTevKColor(s32 index, sead::Color4f& color) const override;

    sead::Matrix34f& getTexSrtMtx(s32 index) { return mTexSrtMtx[index]; }
    const sead::Matrix34f& getTexSrtMtx(s32 index) const { return mTexSrtMtx[index]; }

private:
    nw::g3d::MaterialObj*               mMaterialObj;
    sead::SafeArray<sead::Matrix34f, 8> mTexSrtMtx;
};
static_assert(sizeof(MaterialNW) == 0x188);
