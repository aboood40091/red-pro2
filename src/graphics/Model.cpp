#include <graphics/Model.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResource.h>

Model::Model()
    : RenderObj()
{
}

Model::~Model()
{
}

ModelG3d* Model::createG3d(const ModelResource& res, const char* name, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, BoundingMode bounding_mode)
{
    return createG3d(res, name, 1, num_skl_anim, num_tex_anim, num_shu_anim, num_vis_anim, num_sha_anim, bounding_mode);
}

ModelG3d* Model::createG3d(const ModelResource& res, const char* name, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, BoundingMode bounding_mode)
{
    ModelG3d* p_model = new ModelG3d();
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
