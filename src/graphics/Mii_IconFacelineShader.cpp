#include <graphics/Mii_IconFacelineShader.h>

namespace Mii {

namespace {

static const s32 c_uniform_num = 6;
static const s32 c_sampler_num = 2;

static const char* s_uniform_name[c_uniform_num] = {
    "cWorldMtx[0]",
    "cViewMtx[0]",
    "cProjMtx[0]",
    "cResolutionX",
    "cResolutionY",
    "cLineWidth"
};

static const char* s_sampler_name[c_sampler_num] = {
    "sampler_depth",
    "sampler_color"
};

}

void IconFacelineShader::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram("iconFaceline"));

    p->createUniform(c_uniform_num, heap);
    for (s32 j = 0; j < c_uniform_num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(c_sampler_num, heap);
    for (s32 j = 0; j < c_sampler_num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);
}

}
