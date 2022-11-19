#pragma once

#include <basis/seadTypes.h>

class ModelNW;
class ModelResource;
class ShaderParamAnimation;
class ShapeAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;
class VisibilityAnimation;

class BasicModel
{
public:
    BasicModel(ModelNW* p_model, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim);

    ModelNW* getModel() const { return mpModel; }
    ModelResource* getModelResource() const { return mpModelResource; }

    SkeletalAnimation*          getSklAnim(s32 index) const { return mpSklAnim[index]; }
    TexturePatternAnimation*    getTexAnim(s32 index) const { return mpTexAnim[index]; }
    ShaderParamAnimation*       getShuAnim(s32 index) const { return mpShuAnim[index]; }
    VisibilityAnimation*        getVisAnim(s32 index) const { return mpVisAnim[index]; }
    ShapeAnimation*             getShaAnim(s32 index) const { return mpShaAnim[index]; }

    void init(const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array = NULL, sead::Heap* heap = NULL);

    void updateAnimations();
    void updateModel();

private:
    ModelNW*                                mpModel;
    ModelResource*                          mpModelResource;
    sead::Buffer<SkeletalAnimation*>        mpSklAnim;
    sead::Buffer<TexturePatternAnimation*>  mpTexAnim;
    sead::Buffer<ShaderParamAnimation*>     mpShuAnim;
    sead::Buffer<VisibilityAnimation*>      mpVisAnim;
    sead::Buffer<ShapeAnimation*>           mpShaAnim;
};
static_assert(sizeof(BasicModel) == 0x30, "BasicModel size mismatch");
