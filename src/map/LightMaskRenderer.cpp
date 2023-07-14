#include <map/LightMaskRenderer.h>

namespace {

static const s32 c_uniform_num = 4;
static const s32 c_sampler_num = 1;

static const char* s_uniform_name[c_uniform_num] = {
    "projection[0]",
    "view[0]",
    "world[0]",
    "color"
};

static const char* s_sampler_name[c_sampler_num] = {
    "texture"
};

}

void LightMaskRenderer::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    s32 program_index = p_archive->searchShaderProgramIndex("light_mask_shader");
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

    p->createUniform(c_uniform_num, heap);
    for (s32 j = 0; j < c_uniform_num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(c_sampler_num, heap);
    for (s32 j = 0; j < c_sampler_num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);
}
