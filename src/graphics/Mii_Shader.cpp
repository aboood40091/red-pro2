#include <graphics/Mii_Shader.h>

namespace Mii {

void Shader::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    s32 program_index = p_archive->searchShaderProgramIndex("mii_custom_shader");
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

    const s32 c_uniform_num = 28;
    const s32 c_sampler_num = 3;
    const s32 c_attrib_num = 5;

    static const sead::SafeString s_uniform_name[c_uniform_num] = {
        "u_proj",
        "u_mv",
        "u_it",
        "u_mode",
        "u_const0",
        "u_const1",
        "u_const2",
        "u_light_enable",
        "u_light_dir",
        "u_light_ambient",
        "u_light_diffuse",
        "u_light_specular",
        "u_material_ambient",
        "u_material_diffuse",
        "u_material_specular",
        "u_material_specular_power",
        "u_material_specular_mode",
        "u_rim_color",
        "u_rim_power",
        "u_specular_mask",
        "u_is_face_mask",
        "u_ex_light_reg_color",
        "u_ex_dark_reg_color",
        "u_lightmap_enable",
        "u_fog_color",
        "u_fog_start",
        "u_fog_start_end_inv",
        "u_fog_dir"
    };

    static const sead::SafeString s_sampler_name[c_sampler_num] = {
        "s_texture",
        "s_lightmap_01p",
        "s_lightmap_02p"
    };

    static const sead::SafeString s_attrib_name[c_attrib_num] = {
        "a_position",
        "a_texCoord",
        "a_normal",
        "a_tangent",
        "a_color"
    };

    p->createUniform(c_uniform_num, heap);
    for (s32 j = 0; j < c_uniform_num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(c_sampler_num, heap);
    for (s32 j = 0; j < c_sampler_num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);

    p->createAttribute(c_attrib_num, heap);
    for (s32 j = 0; j < c_attrib_num; j++)
        p->setAttributeName(j, s_attrib_name[j]);
}

}
