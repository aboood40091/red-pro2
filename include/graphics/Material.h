#pragma once

#include <gfx/rio_Color.h>
#include <math/rio_Vector.h>

class Material
{
public:
    virtual void setTexSrtMtx(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate) = 0;
    virtual void setTexSrt(s32 index, const rio::Vector2f& scale, const u32& rotate, const rio::Vector2f& translate) = 0;
    virtual void getTexSrt(s32 index, rio::Vector2f* scale = nullptr, u32* rotate = nullptr, rio::Vector2f* translate = nullptr) const = 0;
    virtual void setTevColor(s32 index, const rio::Color4f& color) = 0;
    virtual void getTevColor(s32 index, rio::Color4f& color) const = 0;
    virtual void setTevKColor(s32 index, const rio::Color4f& color) = 0;
    virtual void getTevKColor(s32 index, rio::Color4f& color) const = 0;
};
