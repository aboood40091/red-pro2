#include <graphics/TexQuadMgr.h>

namespace {

static const s32 c_shader_num = 8;
static const s32 c_uniform_num = 3;
static const s32 c_sampler_num = 5;

static const char* s_shader_name[c_shader_num] = {
    "texQuadCommon",
    "texQuadWaveNormal",
    "texQuadWaveSand",
    "texQuadWavePoison",
    "texQuadWaveMagmaWave",
    "texQuadFloor",
    "texQuadFlower",
    "texQuadWaveNormalBehind"
};

static const char* s_uniform_name[c_uniform_num] = {
    "cWorldMtx[0]",
    "cViewMtx[0]",
    "cProjMtx[0]"
};

static const char* s_sampler_name[c_sampler_num] = {
    "sampler2d_00",
    "sampler2d_01",
    "sampler2d_normal",
    "sampler2d_lightmap",
    "sampler2d_lightmap2"
};

}

void TexQuadMgr::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
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
}
