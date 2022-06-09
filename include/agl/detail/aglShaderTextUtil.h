#pragma once

#include <prim/seadSafeString.h>

namespace agl { namespace detail {

class ShaderTextUtil
{
public:
    static s32 findLineFeedCode(const char* p_string, s32* p_length);
    static void replaceMacro(sead::BufferedSafeString* p_text, const char* const* macro, const char* const* value, s32 macro_num, char* p_work, s32 worksize);
    static sead::HeapSafeString* createRawText(const sead::SafeString& text, const char* const* name_array, const char* const* text_array, s32 num_source, bool* source_used, sead::Heap* heap);
};

} }
