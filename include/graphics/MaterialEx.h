#pragma once

#include <graphics/Material.h>

#include <nw/g3d/g3d_MaterialObj.h>

class MaterialEx : public Material
{
public:
    MaterialEx(nw::g3d::MaterialObj* material)
        : mMaterialObj(material)
        , mTexSrtMtx()
    {
    }

    void setTexSrtMtx(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void setTexSrt(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) override;
    void getTexSrt(s32 index, sead::Vector2f* p_scale = NULL, u32* p_rotate = NULL, sead::Vector2f* p_translate = NULL) const override;
    void setTevColor(s32 index, const sead::Color4f& color) override;
    void getTevColor(s32 index, sead::Color4f& color) const override;
    void setTevKColor(s32 index, const sead::Color4f& color) override;
    void getTevKColor(s32 index, sead::Color4f& color) const override;

    // TODO: sead::SafeArray
    sead::Matrix34f& getTexSrtMtx(s32 index) { if (index < 8) { return mTexSrtMtx[index]; } else { return mTexSrtMtx[0]; } }
    const sead::Matrix34f& getTexSrtMtx(s32 index) const { if (index < 8) { return mTexSrtMtx[index]; } else { return mTexSrtMtx[0]; } }

private:
    nw::g3d::MaterialObj* mMaterialObj;
    sead::Matrix34f mTexSrtMtx[8]; // sead::SafeArray<sead::Matrix34f, 8>
};
