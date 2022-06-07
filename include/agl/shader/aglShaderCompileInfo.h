#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadNamable.h>

namespace agl {

class ShaderCompileInfo : public sead::INamable
{
public:
    ShaderCompileInfo();
    virtual ~ShaderCompileInfo();

    void create(s32 num_macro, s32 num_variation, sead::Heap* heap);
    void destroy();

protected:
    const sead::SafeString* _8;
    const sead::BufferedSafeString* _c;
    sead::PtrArray<const char> mMacroName;
    sead::PtrArray<const char> mMacroValue;
    sead::PtrArray<const char> mVariationName;
    sead::PtrArray<const char> mVariationValue;
    sead::Buffer<u8> _40; // No idea buffer of what
    sead::Buffer<u8> _48; // ^^
};
static_assert(sizeof(ShaderCompileInfo) == 0x54, "agl::ShaderCompileInfo size mismatch");

}
