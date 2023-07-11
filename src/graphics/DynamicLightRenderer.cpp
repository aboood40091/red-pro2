#include <graphics/DynamicLightRenderer.h>

// I don't get this

struct DynamicLightRenderer_ShaderNumSetter
{
    DynamicLightRenderer_ShaderNumSetter()
        : val(4)
    {
    }

    s32 val;
};
static DynamicLightRenderer_ShaderNumSetter s_shader_num;

void DynamicLightRenderer::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    const s32 c_shader_num = 4;
    const s32 c_uniform_num = 7;
    const s32 c_sampler_num = 1;

    static const char* s_shader_name[c_shader_num] = {
        "point_light",
        "doughnut_point_light",
        "fan_point_light",
        "directional_light"
    };

    static const char* s_uniform_name[c_uniform_num] = {
        "cProjection[0]",
        "cModelView[0]",
        "cProjSize",
        "cLightColor",
        "cLightPos",
        "cLightParam",
        "cLightParam2"
    };

    static const char* s_sampler_name[c_sampler_num] = {
        "cGBufferMap"
    };

    for (s32 i = 0; i < s_shader_num.val; i++)
    {
        agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(s_shader_name[i]));

        p->createUniform(c_uniform_num, heap);
        for (s32 j = 0; j < c_uniform_num; j++)
            p->setUniformName(j, s_uniform_name[j]);

        p->createSamplerLocation(c_sampler_num, heap);
        for (s32 j = 0; j < c_sampler_num; j++)
            p->setSamplerLocationName(j, s_sampler_name[j]);
    }
}
