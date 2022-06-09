#include <agl/detail/aglShaderTextUtil.h>

namespace agl { namespace detail {

// ShaderTextUtil
s32 ShaderTextUtil::findLineFeedCode(const char* p_string, s32* p_length)
{
    // SEAD_ASSERT(p_string != nullptr);

    s32 length;

    s32 i = 0;
    for (;;)
    {
        if (p_string[i] == '\0')
        {
            length = 0;
            break;
        }
        else if (p_string[i] == '\r')
        {
            length = (p_string[i + 1] == '\n') ? 2 : 1;
            break;
        }
        else if (p_string[i] == '\n')
        {
            length = 1;
            break;
        }

        i++;
    }

    if (length != 0)
    {
        if (p_length)
            *p_length = length;

        return i;
    }

    return -1;
}

} }
