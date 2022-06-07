#include <agl/aglShaderProgram.h>

namespace agl {

ShaderProgram::ShaderProgram()
    : mFlags(0)
    , mVariationID(0)
    , mDisplayList()
    , mAttributeLocation()
    , mUniformLocation()
    , mUniformBlockLocation()
    , mSamplerLocation()
    , mVertexShader()
    , mFragmentShader()
    , mGeometryShader()
    , mpSharedData(NULL)
{
}

ShaderProgram::~ShaderProgram()
{
    cleanUp();

    destroyAttribute();
    destroyUniform();
    destroySamplerLocation();
    destroyUniformBlock();

    if (mpSharedData->mpOriginal == this)
    {
        delete mpSharedData->mpVariationBuffer;
        delete mpSharedData;
    }
}

void ShaderProgram::initialize(const sead::SafeString& name, sead::Heap* heap)
{
    mpSharedData = new (heap) SharedData();
    mpSharedData->mpOriginal = this;
    mpSharedData->mpVariationBuffer = NULL;
    mpSharedData->_10 = 0;
    mpSharedData->setName(name);
    mpSharedData->_28 = 0;

    // TODO: sead::SafeArray
    {
        typedef sead::Buffer<ResShaderSymbolArray>::iterator _Iterator;
        ResShaderSymbolArray* const buffer = mpSharedData->mResShaderSymbolArray;
        for (_Iterator it = _Iterator(buffer), it_end = _Iterator(buffer, cShaderSymbolType_Num); it != it_end; ++it)
            *it = NULL;
    }
}

void ShaderProgram::createVariationBuffer(s32 num_variation, sead::Heap* heap)
{
    mpSharedData->mpVariationBuffer = new (heap) VariationBuffer();
    mpSharedData->mpVariationBuffer->initialize(this, num_variation, heap);
}

void ShaderProgram::createVariationMacro(s32 index, const sead::SafeString& name, const sead::SafeString& id, s32 num_value, sead::Heap* heap)
{
    mpSharedData->mpVariationBuffer->createMacro(index, name, id, num_value, heap);
}

void ShaderProgram::setVariationMacroValue(s32 macro_index, s32 value_index, const sead::SafeString& value)
{
    mpSharedData->mpVariationBuffer->setMacroValue(macro_index, value_index, value);
}

void ShaderProgram::createVariation(sead::Heap* heap)
{
    mpSharedData->mpVariationBuffer->create(heap);

    for (sead::Buffer<ShaderProgram>::iterator it = mpSharedData->mpVariationBuffer->mProgram.begin(), it_end = mpSharedData->mpVariationBuffer->mProgram.end(); it != it_end; ++it)
    {
        it->mpSharedData = mpSharedData;
        it->mVariationID = it.getIndex() + 1;
    }
}

Shader* ShaderProgram::getShader(ShaderType type)
{
    switch (type)
    {
    case cShaderType_Vertex:
        return &mVertexShader;
    case cShaderType_Fragment:
        return &mFragmentShader;
    case cShaderType_Geometry:
        return &mGeometryShader;
    default:
        return NULL;
    }
}

const Shader* ShaderProgram::getShader(ShaderType type) const
{
    switch (type)
    {
    case cShaderType_Vertex:
        return &mVertexShader;
    case cShaderType_Fragment:
        return &mFragmentShader;
    case cShaderType_Geometry:
        return &mGeometryShader;
    default:
        return NULL;
    }
}

s32 ShaderProgram::getVariationNum() const
{
    const VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (!variation_buffer)
        return 1;

    return variation_buffer->mProgram.size() + 1;
}

s32 ShaderProgram::getVariationMacroNum() const
{
    const VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (!variation_buffer)
        return 0;

    return variation_buffer->mMacro.size();
}

ShaderProgram* ShaderProgram::getVariation(s32 index)
{
    VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (!variation_buffer)
        return this;

    if (index <= 0)
        return variation_buffer->mpOriginal;

    return &variation_buffer->mProgram[index - 1];
}

const ShaderProgram* ShaderProgram::getVariation(s32 index) const
{
    const VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (!variation_buffer)
        return this;

    if (index <= 0)
        return variation_buffer->mpOriginal;

    return &variation_buffer->mProgram[index - 1];
}

void ShaderProgram::reserveSetUpAllVariation()
{
    if (mpSharedData->mpVariationBuffer)
    {
        mpSharedData->mpVariationBuffer->mpOriginal->mFlags.setBit(1);
        for (sead::Buffer<ShaderProgram>::iterator it = mpSharedData->mpVariationBuffer->mProgram.begin(), it_end = mpSharedData->mpVariationBuffer->mProgram.end(); it != it_end; ++it)
            it->mFlags.setBit(1);
    }
    else
    {
        mFlags.setBit(1);
    }
}

void ShaderProgram::cleanUp()
{
    if (mFlags.isOnBit(0))
        mFlags.resetBit(0);
}

void ShaderProgram::destroyAttribute()
{
    mAttributeLocation.freeBuffer();

    VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (variation_buffer)
    {
        for (sead::Buffer<ShaderProgram>::iterator it = variation_buffer->mProgram.begin(), it_end = variation_buffer->mProgram.end(); it != it_end; ++it)
            it->mAttributeLocation.freeBuffer();
    }
}

void ShaderProgram::destroyUniform()
{
    mUniformLocation.freeBuffer();

    VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (variation_buffer)
    {
        for (sead::Buffer<ShaderProgram>::iterator it = variation_buffer->mProgram.begin(), it_end = variation_buffer->mProgram.end(); it != it_end; ++it)
            it->mUniformLocation.freeBuffer();
    }
}

void ShaderProgram::destroyUniformBlock()
{
    mUniformBlockLocation.freeBuffer();

    VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (variation_buffer)
    {
        for (sead::Buffer<ShaderProgram>::iterator it = variation_buffer->mProgram.begin(), it_end = variation_buffer->mProgram.end(); it != it_end; ++it)
            it->mUniformBlockLocation.freeBuffer();
    }
}

void ShaderProgram::destroySamplerLocation()
{
    mSamplerLocation.freeBuffer();

    VariationBuffer* variation_buffer = mpSharedData->mpVariationBuffer;
    if (variation_buffer)
    {
        for (sead::Buffer<ShaderProgram>::iterator it = variation_buffer->mProgram.begin(), it_end = variation_buffer->mProgram.end(); it != it_end; ++it)
            it->mSamplerLocation.freeBuffer();
    }
}

ShaderProgram::VariationBuffer::VariationBuffer()
    : mProgram()
    , mMacro()
{
}

ShaderProgram::VariationBuffer::~VariationBuffer()
{
    mProgram.freeBuffer();

    for (sead::Buffer<Macro>::iterator it = mMacro.begin(), it_end = mMacro.end(); it != it_end; ++it)
        it->mValue.freeBuffer();

    mMacro.freeBuffer();
}

void ShaderProgram::VariationBuffer::initialize(ShaderProgram* program, s32 num_variation, sead::Heap* heap)
{
    mpOriginal = program;
    mMacro.allocBuffer(num_variation, heap);
}

void ShaderProgram::VariationBuffer::createMacro(s32 index, const sead::SafeString& name, const sead::SafeString& id, s32 num_value, sead::Heap* heap)
{
    Macro& macro = mMacro[index];
    macro.mName = name;
    macro.mID = id;
    macro._18 = 1;
    macro.mValue.allocBuffer(num_value, heap);
}

void ShaderProgram::VariationBuffer::setMacroValue(s32 macro_index, s32 value_index, const sead::SafeString& value)
{
    mMacro[macro_index].mValue[value_index] = value;
}

void ShaderProgram::VariationBuffer::create(sead::Heap* heap)
{
    u32 num_variation = 1;

    for (sead::Buffer<Macro>::iterator it = mMacro.begin(), it_end = mMacro.end(); it != it_end; ++it)
    {
        for (s32 i = it.getIndex() + 1; i < mMacro.size(); i++)
            it->_18 *= mMacro[i].mValue.size();

        num_variation *= it->mValue.size();
    }

    mProgram.allocBuffer(num_variation - 1, heap);
}

}
