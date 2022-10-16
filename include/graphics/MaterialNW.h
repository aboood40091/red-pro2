#pragma once

#include <math/rio_Matrix.h>

#include <graphics/Material.h>

#include <nw/g3d/g3d_MaterialObj.h>

class MaterialNW final : public Material
{
public:
    MaterialNW(nw::g3d::MaterialObj* material)
        : mMaterialObj(material)
        , mTexSrtMtx()
    {
    }

    void setTexSrtMtx(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate) override;
    void setTexSrt(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate) override;
    void getTexSrt(s32 index, rio::Vector2f* p_scale = nullptr, u32* p_rotate = nullptr, rio::Vector2f* p_translate = nullptr) const override;
    void setTevColor(s32 index, const rio::Color4f& color) override;
    void getTevColor(s32 index, rio::Color4f& color) const override;
    void setTevKColor(s32 index, const rio::Color4f& color) override;
    void getTevKColor(s32 index, rio::Color4f& color) const override;

    // TODO: SafeArray
    rio::Matrix34f& getTexSrtMtx(s32 index) { if (index < 8) { return mTexSrtMtx[index]; } else { return mTexSrtMtx[0]; } }
    const rio::Matrix34f& getTexSrtMtx(s32 index) const { if (index < 8) { return mTexSrtMtx[index]; } else { return mTexSrtMtx[0]; } }

private:
    nw::g3d::MaterialObj* mMaterialObj;
    rio::Matrix34f mTexSrtMtx[8]; // SafeArray<rio::Matrix34f, 8>
};
