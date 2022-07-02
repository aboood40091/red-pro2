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

} }
