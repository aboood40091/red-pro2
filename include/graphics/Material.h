#pragma once

#include <gfx/seadColor.h>
#include <math/seadVector.h>

class Material
{
public:
    virtual void setTexSrtMtx(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) = 0;
    virtual void setTexSrt(s32 index, const sead::Vector2f& scale, const u32& rotate, const sead::Vector2f& translate) = 0;
    virtual void getTexSrt(s32 index, sead::Vector2f* scale = nullptr, u32* rotate = nullptr, sead::Vector2f* translate = nullptr) const = 0;
    virtual void setTevColor(s32 index, const sead::Color4f& color) = 0;
    virtual void getTevColor(s32 index, sead::Color4f& color) const = 0;
    virtual void setTevKColor(s32 index, const sead::Color4f& color) = 0;
    virtual void getTevKColor(s32 index, sead::Color4f& color) const = 0;
};
static_assert(sizeof(Material) == 4);
