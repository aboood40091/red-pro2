#include <agl/aglShaderProgramArchive.h>
#include <agl/g3d/aglShaderUtilG3D.h>
#include <agl/res/aglResShaderSymbol.h>

#include <nw/g3d/res/g3d_ResFile.h>

namespace agl { namespace g3d {

void ShaderUtilG3D::setMatBlockAndShaderParamOffs(nw::g3d::res::ResFile* res_file, const ShaderProgramArchive* shader_archive, const sead::SafeString& mat_block_name)
{
    for (s32 idx_model = 0, num_model = res_file->GetModelCount(); idx_model < num_model; idx_model++)
        setMatBlockAndShaderParamOffs_(res_file->GetModel(idx_model), shader_archive, mat_block_name);
}

void ShaderUtilG3D::setMatBlockAndShaderParamOffs_(nw::g3d::res::ResModel* res_model, const ShaderProgramArchive* shader_archive, const sead::SafeString& mat_block_name)
{
    for (s32 idx_material = 0, num_material = res_model->GetMaterialCount(); idx_material < num_material; idx_material++)
    {
        nw::g3d::res::ResMaterial* res_material = res_model->GetMaterial(idx_material);

        if (!res_material->GetShaderAssign() ||
            !res_material->GetShaderAssign()->GetShaderArchiveName() ||
            !res_material->GetShaderAssign()->GetShadingModelName() ||
            !shader_archive->getName().isEqual(res_material->GetShaderAssign()->GetShaderArchiveName()))
        {
            continue;
        }

        for (s32 idx_program = 0, num_program = shader_archive->getShaderProgramNum(); idx_program < num_program; idx_program++)
        {
            if (!shader_archive->getShaderProgram(idx_program).getName().isEqual(res_material->GetShaderAssign()->GetShadingModelName()))
                continue;

            const ShaderProgram& shader_program = shader_archive->getShaderProgram(idx_program);
            ResShaderSymbolArray uniforms = shader_program.getResShaderSymbolArray(cShaderSymbolType_Uniform);
            ResShaderSymbolArray uniformBlocks = shader_program.getResShaderSymbolArray(cShaderSymbolType_UniformBlock);
            if (uniforms.isValid() && uniformBlocks.isValid())
            {
                const ResShaderSymbol symbol = uniformBlocks.searchResShaderSymbolByID(mat_block_name);
                if (symbol.isValid())
                {
                    res_material->SetRawParamSize(symbol.ref().mOffset);

                    for (s32 idx_param = 0, num_param = res_material->GetShaderParamCount(); idx_param < num_param; idx_param++)
                    {
                        nw::g3d::res::ResShaderParam* res_shader_param = res_material->GetShaderParam(idx_param);
                        const ResShaderSymbol param_symbol = uniforms.searchResShaderSymbolByID(res_shader_param->GetId());
                        if (param_symbol.isValid())
                            res_shader_param->SetOffset(param_symbol.ref().mOffset);
                    }

                    break;
                }
            }
        }
    }
}

} }
