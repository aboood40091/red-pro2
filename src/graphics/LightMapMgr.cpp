#include <graphics/LightMapMgr.h>
#include <graphics/RenderObjEx.h>

SEAD_TASK_SINGLETON_DISPOSER_IMPL(LightMapMgr)

void LightMapMgr::setRenderObjLightMap(RenderObjEx& render_obj, bool no_mat_dl) const
{
    if (!mIsInitialized)
        return;

    for (s32 idx_shape = 0, num_shape = render_obj.getModelEx().GetShapeCount(); idx_shape < num_shape; idx_shape++)
    {
        RenderObjEx::LightMap& light_map = render_obj.getShape(idx_shape).light_map;
        light_map.clear();

        agl::g3d::ModelShaderAssign& shader_assign = render_obj.getModelEx().getShaderAssign(idx_shape);

        s32 idx_material = render_obj.getModelEx().GetShape(idx_shape)->GetMaterialIndex();
        const nw::g3d::MaterialObj* p_material = render_obj.getModelEx().GetMaterial(idx_material);

        s32 num_light_map = 0;

        for (s32 idx_sampler = 0, num_sampler = shader_assign.getSamplerNum(); idx_sampler < num_sampler; idx_sampler++)
        {
            const nw::g3d::res::ResSampler* p_res_sampler = shader_assign.getResSampler(idx_sampler);
            if (p_res_sampler)
            {
                const nw::g3d::res::ResTexture* p_res_texture = p_material->GetResTexture(p_res_sampler->GetIndex());
                if (p_res_texture)
                {
                    s32 idx_lghtmap = mLightMapMgr.searchIndex(p_res_texture->GetName());
                    if (idx_lghtmap > -1)
                    {
                        light_map.idx_lghtmap[num_light_map] = idx_lghtmap;
                        light_map.idx_sampler[num_light_map] = idx_sampler;

                        if (++num_light_map >= cLightMapNum)
                            break;
                    }
                }
            }
        }
    }

    if (no_mat_dl)
        render_obj.disableMaterialDL();
}
