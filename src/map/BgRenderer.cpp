#include <map/BgRenderer.h>

namespace {

static const s32 c_shader_num = 3;
static const s32 c_uniform_num = 2;
static const s32 c_sampler_num = 3;

static const char* s_shader_name[c_shader_num] = {
    "bg_renderer",
    "bg_renderer_lava_line",
    "bg_renderer_normal_rotate"
};

static const char* s_uniform_name[c_uniform_num] = {
    "projection[0]",
    "normal_rotate[0]"
};

static const char* s_sampler_name[c_sampler_num] = {
    "texture",
    "normal_texture",
    "lava_line_texture"
};

static const s32 c_mask_shader_num = 2;
static const s32 c_mask_uniform_num = 2;
static const s32 c_mask_sampler_num = 2;

static const char* s_mask_shader_name[c_mask_shader_num] = {
    "bg_renderer_mask",
    "bg_renderer_dark_mask"
};

static const char* s_mask_uniform_name[c_mask_uniform_num] = {
    "projection[0]",
    "circle_color"
};

static const char* s_mask_sampler_name[c_mask_sampler_num] = {
    "texture_layer0",
    "texture_mask"
};

}

void BgRenderer::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    for (s32 i = 0; i < c_shader_num; i++)
    {
        const char* const name = s_shader_name[i];
        s32 program_index = p_archive->searchShaderProgramIndex(name);
        agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

        p->createUniform(c_uniform_num, heap);
        for (s32 j = 0; j < c_uniform_num; j++)
            p->setUniformName(j, s_uniform_name[j]);

        p->createSamplerLocation(c_sampler_num, heap);
        for (s32 j = 0; j < c_sampler_num; j++)
            p->setSamplerLocationName(j, s_sampler_name[j]);
    }

    for (s32 i = 0; i < c_mask_shader_num; i++)
    {
        const char* const name = s_mask_shader_name[i];
        s32 program_index = p_archive->searchShaderProgramIndex(name);
        agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

        p->createUniform(c_mask_uniform_num, heap);
        for (s32 j = 0; j < c_mask_uniform_num; j++)
            p->setUniformName(j, s_mask_uniform_name[j]);

        p->createSamplerLocation(c_mask_sampler_num, heap);
        for (s32 j = 0; j < c_mask_sampler_num; j++)
            p->setSamplerLocationName(j, s_mask_sampler_name[j]);
    }
}
