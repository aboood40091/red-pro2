#include <graphics/Mii_IconFacelineShader.h>
#include <graphics/ShaderHolder.h>

namespace Mii {

namespace {

static const char* s_uniform_name[IconFacelineShader::cUniform_Num] = {
    "cWorldMtx[0]",
    "cViewMtx[0]",
    "cProjMtx[0]",
    "cResolutionX",
    "cResolutionY",
    "cLineWidth"
};

static const char* s_sampler_name[IconFacelineShader::cSampler_Num] = {
    "sampler_depth",
    "sampler_color"
};

}

IconFacelineShader::IconFacelineShader()
    : mpShaderProgram(nullptr)
{
}

void IconFacelineShader::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram("iconFaceline"));

    p->createUniform(cUniform_Num, heap);
    for (s32 j = 0; j < cUniform_Num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(cSampler_Num, heap);
    for (s32 j = 0; j < cSampler_Num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);
}

bool IconFacelineShader::initialize()
{
    return initializeShader_();
}

void IconFacelineShader::destroy()
{
}

void IconFacelineShader::setViewUniform(const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, const sead::Matrix34f& world_mtx) const
{
    mpShaderProgram->getUniformLocation(cUniform_ViewMtx).setVec4Array(view_mtx);
    mpShaderProgram->getUniformLocation(cUniform_ProjMtx).setVec4Array(proj_mtx);
    mpShaderProgram->getUniformLocation(cUniform_WorldMtx).setVec4Array(world_mtx);
}

void IconFacelineShader::setResolutionUniform(u32 width, u32 height) const
{
    mpShaderProgram->getUniformLocation(cUniform_ResolutionX).setFloat(width);
    mpShaderProgram->getUniformLocation(cUniform_ResolutionY).setFloat(height);
}

void IconFacelineShader::setLineWidthUniform(s32 line_width) const
{
    mpShaderProgram->getUniformLocation(cUniform_LineWidth).setFloat(line_width);
}

bool IconFacelineShader::activateTexture(const agl::TextureData& texture_data, Sampler sampler)
{
    mTextureSampler[sampler].applyTextureData(texture_data);
    return mTextureSampler[sampler].activate(mpShaderProgram->getSamplerLocationValidate(sampler));
}

bool IconFacelineShader::initializeShader_()
{
    mpShaderArchive = ShaderHolder::instance()->getShaderArchive("mii_icon_faceline_shader");
    mpShaderProgram = mpShaderArchive->searchShaderProgram("iconFaceline");
    return true;
}

}
