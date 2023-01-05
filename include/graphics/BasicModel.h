#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>

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
    BasicModel(ModelNW* p_model, u32 skl_anim_num, u32 tex_anim_num, u32 shu_anim_num, u32 vis_anim_num, u32 sha_anim_num);

    ModelNW* getModel() const { return mpModel; }
    ModelResource* getModelResource() const { return mpModelResource; }

    SkeletalAnimation*          getSklAnim(s32 index) const { return mpSklAnim[index]; }
    TexturePatternAnimation*    getTexAnim(s32 index) const { return mpTexAnim[index]; }
    ShaderParamAnimation*       getShuAnim(s32 index) const { return mpShuAnim[index]; }
    VisibilityAnimation*        getVisAnim(s32 index) const { return mpVisAnim[index]; }
    ShapeAnimation*             getShaAnim(s32 index) const { return mpShaAnim[index]; }

    void init(const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array = nullptr, sead::Heap* heap = nullptr);

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
