#include <container/seadBuffer.h>
#include <g3d/aglModelShaderAssign.h>

namespace agl { namespace g3d {

ModelShaderAttribute::ModelShaderAttribute()
    : mpVertexBuffer()
    , mFetchShader()
{
    clear();
}

ModelShaderAttribute::~ModelShaderAttribute()
{
    if (mFetchShader.GetShaderPtr())
        delete mFetchShader.GetShaderPtr(); // Nintendo forgot to do delete[] again
}

void ModelShaderAttribute::create(sead::Heap* heap)
{
    if (mFetchShader.GetShaderPtr())
        delete[] mFetchShader.GetShaderPtr();

    mFetchShader.SetAttribCount(16);
    mFetchShader.CalcSize();
    mFetchShader.SetShaderPtr(new (heap, nw::g3d::fnd::GfxFetchShader::SHADER_ALIGNMENT) u8[mFetchShader.GetShaderSize()]);
}

void ModelShaderAttribute::clear()
{
    mVertexBufferNum = 0;

    // TODO: sead::SafeArray
    {
        typedef sead::Buffer<const nw::g3d::fnd::GfxBuffer*>::iterator _Iterator;
        for (_Iterator it = _Iterator(mpVertexBuffer), it_end = _Iterator(mpVertexBuffer, 16); it != it_end; ++it)
            *it = NULL;
    }
}

void ModelShaderAttribute::setVertexBuffer(const nw::g3d::fnd::GfxBuffer* p_buffer, s32 index)
{
    for (u32 idx_attrib = 0; idx_attrib < mFetchShader.GetAttribCount(); idx_attrib++)
        if (mFetchShader.GetVertexBuffer(idx_attrib) == mpVertexBuffer[index])
            mFetchShader.SetVertexBuffer(idx_attrib, p_buffer);

    mpVertexBuffer[index] = p_buffer;
}

void ModelShaderAttribute::activateVertexBuffer() const
{
    mFetchShader.Load();

    for (u32 i = 0; i < mVertexBufferNum; i++)
        mpVertexBuffer[i]->LoadVertices(i);
}

ModelShaderAssign::ModelShaderAssign()
    : mpProgram(NULL)
    , mUniformBlockLocation()
    , mSamplerLocation()
    , mpResSampler()
    , mAttribute()
{
    clear_();
}

ModelShaderAssign::~ModelShaderAssign()
{
}

void ModelShaderAssign::create(sead::Heap* heap)
{
    mAttribute.create(heap);
}

void ModelShaderAssign::clear_()
{
    mAttribute.clear();
    mSamplerNum = 0;

    // TODO: sead::SafeArray
    {
        typedef sead::Buffer<nw::g3d::res::ResSampler*>::iterator _Iterator;
        for (_Iterator it = _Iterator(mpResSampler), it_end = _Iterator(mpResSampler, 16); it != it_end; ++it)
            *it = NULL;
    }
}

void ModelShaderAssign::bindShader(const nw::g3d::res::ResMaterial* p_res_mat, const nw::g3d::res::ResShape* p_res_shp, const ShaderProgram* p_program, const char*)
{
    clear_();
    if (p_program)
    {
        bind(p_res_mat, p_program, false, true);
        mAttribute.bind(p_res_mat, p_res_shp, p_program, false, true);
        updateLocation_("Mat");
    }
}

void ModelShaderAssign::activateMaterialUniformBlock(const nw::g3d::MaterialObj* p_material) const
{
    if (mUniformBlockLocation.isValid() && p_material->GetMatBlock().GetSize() > 0)
    {
        if (mUniformBlockLocation.getVertexLocation() != -1)
            p_material->GetMatBlock().LoadVertexUniforms(mUniformBlockLocation.getVertexLocation());

        if (mUniformBlockLocation.getGeometryLocation() != -1)
            p_material->GetMatBlock().LoadGeometryUniforms(mUniformBlockLocation.getGeometryLocation());

        if (mUniformBlockLocation.getFragmentLocation() != -1)
            p_material->GetMatBlock().LoadFragmentUniforms(mUniformBlockLocation.getFragmentLocation());
    }
}

void ModelShaderAssign::activateTextureSampler(const nw::g3d::MaterialObj* p_material) const
{
    for (u32 i = 0; i < mSamplerNum; i++)
    {
        const nw::g3d::res::ResSampler* p_res_sampler = mpResSampler[i];
        const nw::g3d::res::ResTexture* p_res_texture = p_material->GetResTexture(p_res_sampler->GetIndex());

        if (p_res_texture)
        {
            const nw::g3d::fnd::GfxSampler* p_gfx_sampler = p_res_sampler->GetGfxSampler();
            const nw::g3d::fnd::GfxTexture* p_gfx_texture = p_res_texture->GetGfxTexture();

            const agl::SamplerLocation& sampler_location = mSamplerLocation[i];

            if (sampler_location.getVertexLocation() != -1)
            {
                p_gfx_sampler->LoadVertexSampler(sampler_location.getVertexLocation());
                p_gfx_texture->LoadVertexTexture(sampler_location.getVertexLocation());
            }

            if (sampler_location.getGeometryLocation() != -1)
            {
                p_gfx_sampler->LoadGeometrySampler(sampler_location.getGeometryLocation());
                p_gfx_texture->LoadGeometryTexture(sampler_location.getGeometryLocation());
            }

            if (sampler_location.getFragmentLocation() != -1)
            {
                p_gfx_sampler->LoadFragmentSampler(sampler_location.getFragmentLocation());
                p_gfx_texture->LoadFragmentTexture(sampler_location.getFragmentLocation());
            }
        }
    }
}

} }
