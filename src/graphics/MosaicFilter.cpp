#include <graphics/MosaicFilter.h>

namespace {

static const s32 c_uniform_num = 2;
static const s32 c_sampler_num = 1;
static const s32 c_attrib_num = 2;

static const sead::SafeString s_uniform_name[c_uniform_num] = {
    "uDivisionNum",
    "uDiffuseColor"
};

static const sead::SafeString s_sampler_name[c_sampler_num] = {
    "sTexture"
};

static const sead::SafeString s_attrib_name[c_attrib_num] = {
    "aPosition",
    "aTexCoord"
};

}

void MosaicFilter::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    s32 program_index = p_archive->searchShaderProgramIndex("mosaic_filter");
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

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
