#pragma once

#include <prim/seadSafeString.h>

namespace agl { namespace detail {

class ShaderTextUtil
{
public:
    static sead::HeapSafeString* createRawText(const sead::SafeString& text, const char* const* name_array, const char* const* text_array, s32 num_source, bool* source_used, sead::Heap* heap);
};

} }
