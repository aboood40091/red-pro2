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

private:
    Model* mpModel;
    ModelResource* mpModelResource;
    sead::Buffer<SkeletalAnimation*> mpSklAnim;
    sead::Buffer<TexturePatternAnimation*> mpTexAnim;
    sead::Buffer<ShaderParamAnimation*> mpShuAnim;
    sead::Buffer<VisibilityAnimation*> mpVisAnim;
    sead::Buffer<ShapeAnimation*> mpShaAnim;
};
static_assert(sizeof(BasicModel) == 0x30, "BasicModel size mismatch");
