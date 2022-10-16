#include <graphics/Model.h>
#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>

Model::Model()
    : RenderObj()
    , mOpaBufferIdx(-2)
    , mXluBufferIdx(-2)
{
}

Model::~Model()
{
}

ModelNW* Model::createNW(const ModelResource& res, const char* name, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, u32 bounding_mode)
{
    return createNW(res, name, 1, num_skl_anim, num_tex_anim, num_shu_anim, num_vis_anim, num_sha_anim, bounding_mode);
}

ModelNW* Model::createNW(const ModelResource& res, const char* name, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, u32 bounding_mode)
{
    ModelNW* p_model = new ModelNW();
    s32 idx_model = res.getResFile()->GetModelIndex(name);
    p_model->initialize(
        res.getResFile()->GetModel(idx_model),
        res.getModelShaderProgramArchive(idx_model),
        num_view,
        num_skl_anim, num_tex_anim, num_shu_anim, num_vis_anim, num_sha_anim,
        bounding_mode
    );
    return p_model;
}
