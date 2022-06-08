#include <agl/shader/aglShaderCompileInfo.h>

namespace agl {

ShaderCompileInfo::ShaderCompileInfo()
    : sead::INamable("unititled")
    , mSourceText(NULL)
    , _c(NULL)
    , mMacroName()
    , mMacroValue()
    , mVariationName()
    , mVariationValue()
    , _40()
    , _48()
{
}

ShaderCompileInfo::~ShaderCompileInfo()
{
    destroy();
}

void ShaderCompileInfo::create(s32 num_macro, s32 num_variation, sead::Heap* heap)
{
    if (num_macro > 0)
    {
        mMacroName.allocBuffer(num_macro, heap);
        mMacroValue.allocBuffer(num_macro, heap);
    }

    if (num_variation > 0)
    {
        mVariationName.allocBuffer(num_variation, heap);
        mVariationValue.allocBuffer(num_variation, heap);
    }
}

void ShaderCompileInfo::clearVariation()
{
    mVariationName.clear();
    mVariationValue.clear();
}

void ShaderCompileInfo::pushBackVariation(const char* name, const char* value)
{
    mVariationName.pushBack(name);
    mVariationValue.pushBack(value);
}

void ShaderCompileInfo::destroy()
{
    if (mMacroName.isBufferReady())
    {
        mMacroName.freeBuffer();

        // SEAD_ASSERT(mMacroValue.isBufferReady());
        mMacroValue.freeBuffer();
    }

    if (mVariationName.isBufferReady())
    {
        mVariationName.freeBuffer();

        // SEAD_ASSERT(mVariationValue.isBufferReady());
        mVariationValue.freeBuffer();
    }
}

}
