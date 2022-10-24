#pragma once

#include <basis/seadTypes.h>

class Model;
class ModelResource;
class ShaderParamAnimation;
class ShapeAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;
class VisibilityAnimation;

class BasicModel
{
public:
    Model* getModel() const { return mpModel; }
    ModelResource* getModelResource() const { return mpModelResource; }

    SkeletalAnimation*          getSklAnim(s32 index) const { return mpSklAnim[index]; }
    TexturePatternAnimation*    getTexAnim(s32 index) const { return mpTexAnim[index]; }
    ShaderParamAnimation*       getShuAnim(s32 index) const { return mpShuAnim[index]; }
    VisibilityAnimation*        getVisAnim(s32 index) const { return mpVisAnim[index]; }
    ShapeAnimation*             getShaAnim(s32 index) const { return mpShaAnim[index]; }

private:
    Model*                                  mpModel;
    ModelResource*                          mpModelResource;
    sead::Buffer<SkeletalAnimation*>        mpSklAnim;
    sead::Buffer<TexturePatternAnimation*>  mpTexAnim;
    sead::Buffer<ShaderParamAnimation*>     mpShuAnim;
    sead::Buffer<VisibilityAnimation*>      mpVisAnim;
    sead::Buffer<ShapeAnimation*>           mpShaAnim;
};
static_assert(sizeof(BasicModel) == 0x30, "BasicModel size mismatch");
