#pragma once

#include <graphics/ModelG3d.h>

#include <container/Buffer.h>
#include <container/PtrArray.h>

class ModelResource;
class ShaderParamAnimation;
class ShapeAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;
class VisibilityAnimation;

class BasicModel
{
public:
    static BasicModel* createFromModel(
        ModelResource* p_mdl_res,
        ModelG3d* p_model,
        s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
        const PtrArray<ModelResource>* p_anim_mdl_res_array = nullptr
    );
    static void destroyFromModel(BasicModel* p_bmdl);

    static BasicModel* create(
        ModelResource* p_mdl_res,
        const char* name,
        s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
        Model::BoundingMode bounding_mode = Model::cBoundingMode_Disable
    );
    static BasicModel* create(
        ModelResource* p_mdl_res,
        const char* name,
        s32 view_num,
        s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
        Model::BoundingMode bounding_mode
    );
    static void destroy(BasicModel* p_bmdl);

public:
    BasicModel(ModelG3d* p_model, u32 skl_anim_num, u32 tex_anim_num, u32 shu_anim_num, u32 vis_anim_num, u32 sha_anim_num);
    virtual ~BasicModel();

public:
    ModelG3d* getModel() const { return mpModel; }
    ModelResource* getModelResource() const { return mpModelResource; }

    SkeletalAnimation*          getSklAnim(s32 index) const { return mpSklAnim[index]; }
    TexturePatternAnimation*    getTexAnim(s32 index) const { return mpTexAnim[index]; }
    ShaderParamAnimation*       getShuAnim(s32 index) const { return mpShuAnim[index]; }
    VisibilityAnimation*        getVisAnim(s32 index) const { return mpVisAnim[index]; }
    ShapeAnimation*             getShaAnim(s32 index) const { return mpShaAnim[index]; }

    void init(ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array = nullptr);

    void updateAnimations();
    void updateModel();

private:
    ModelG3d*                           mpModel;
    ModelResource*                      mpModelResource;
    Buffer<SkeletalAnimation*>          mpSklAnim;
    Buffer<TexturePatternAnimation*>    mpTexAnim;
    Buffer<ShaderParamAnimation*>       mpShuAnim;
    Buffer<VisibilityAnimation*>        mpVisAnim;
    Buffer<ShapeAnimation*>             mpShaAnim;
};
//static_assert(sizeof(BasicModel) == 0x30);

inline BasicModel* BasicModel::createFromModel(
    ModelResource* p_mdl_res,
    ModelG3d* p_model,
    s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
    const PtrArray<ModelResource>* p_anim_mdl_res_array
)
{
    BasicModel* p_bmdl = new BasicModel(p_model, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num);
    p_bmdl->init(p_mdl_res, p_anim_mdl_res_array);
    return p_bmdl;
}

inline void BasicModel::destroyFromModel(BasicModel* p_bmdl)
{
    delete p_bmdl;
}

inline BasicModel* BasicModel::create(
    ModelResource* p_mdl_res,
    const char* name,
    s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
    Model::BoundingMode bounding_mode
)
{
    ModelG3d* p_model = Model::createG3d(*p_mdl_res, name, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num, bounding_mode);
    return createFromModel(p_mdl_res, p_model, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num);
}

inline BasicModel* BasicModel::create(
    ModelResource* p_mdl_res,
    const char* name,
    s32 view_num,
    s32 skl_anim_num, s32 tex_anim_num, s32 shu_anim_num, s32 vis_anim_num, s32 sha_anim_num,
    Model::BoundingMode bounding_mode
)
{
    ModelG3d* p_model = Model::createG3d(*p_mdl_res, name, view_num, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num, bounding_mode);
    return createFromModel(p_mdl_res, p_model, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num);
}

inline void BasicModel::destroy(BasicModel* p_bmdl)
{
    ModelG3d* p_model = p_bmdl->getModel();
    destroyFromModel(p_bmdl);
    delete p_model;
}
