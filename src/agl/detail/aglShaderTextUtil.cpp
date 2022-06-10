#include <agl/detail/aglShaderTextUtil.h>

#include <prim/seadMemUtil.h>
#include <prim/seadSafeString.h>

namespace agl { namespace detail {

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

void ShaderTextUtil::replaceMacro(sead::BufferedSafeString* p_text, const char* const* macro, const char* const* value, s32 macro_num, char* p_work, s32 worksize)
{
    // SEAD_ASSERT(p_text != nullptr);
    // SEAD_ASSERT(p_work != nullptr);
    // SEAD_ASSERT(macro != nullptr);
    // SEAD_ASSERT(value != nullptr);

    // SEAD_ASSERT(macro_num < 1024);
    bool macro_replaced[1024];
    for (s32 i_macro = 0; i_macro < macro_num; i_macro++)
        macro_replaced[i_macro] = false;

    const char* p_src = p_text->cstr();
    char* p_dst = p_work;

    s32 i_macro = 0;
    for (;;)
    {
        s32 line_feed_pos, line_feed_len;
        line_feed_pos = detail::ShaderTextUtil::findLineFeedCode(p_src, &line_feed_len);
        if (line_feed_pos == -1)
            break;

        bool replaced = false;

        if (*p_src == '#')
        {
            s32 macro_pos = 1;
            while (p_src[macro_pos] != '\0')
            {
                if (p_src[macro_pos] != ' ' &&
                    p_src[macro_pos] != '\t' &&
                    p_src[macro_pos] != '\r' &&
                    p_src[macro_pos] != '\n')
                {
                    break;
                }
                macro_pos++;
            }

            if (p_src[macro_pos + 0] == 'd' &&
                p_src[macro_pos + 1] == 'e' &&
                p_src[macro_pos + 2] == 'f' &&
                p_src[macro_pos + 3] == 'i' &&
                p_src[macro_pos + 4] == 'n' &&
                p_src[macro_pos + 5] == 'e' &&
                (p_src[macro_pos + 6] == ' ' ||
                 p_src[macro_pos + 6] == '\t'))
            {
                macro_pos += 7;
                while (p_src[macro_pos] != '\0')
                {
                    if (p_src[macro_pos] != ' ' &&
                        p_src[macro_pos] != '\t' &&
                        p_src[macro_pos] != '\r' &&
                        p_src[macro_pos] != '\n')
                    {
                        break;
                    }
                    macro_pos++;
                }

                for (s32 i_match_macro = 0; i_match_macro < macro_num; i_match_macro++)
                {
                    if (macro_replaced[i_match_macro])
                        continue;

                    const char* const match_macro = macro[i_match_macro];
                    bool match = true;

                    for (s32 i = 0; match_macro[i] != '\0'; i++)
                    {
                        if (p_src[macro_pos] != match_macro[i])
                        {
                            match = false;
                            break;
                        }

                        macro_pos++;
                    }

                    if (!match || (p_src[macro_pos] != ' ' &&
                                   p_src[macro_pos] != '\t'))
                        continue;

                    p_dst += sead::BufferedSafeString(p_dst, worksize - (s32)(p_dst - p_work))
                                .format("#define %s %s", match_macro, value[i_match_macro]);

                    for (s32 i = 0; i < line_feed_len; i++)
                    {
                        p_dst += sead::BufferedSafeString(p_dst, worksize - (s32)(p_dst - p_work))
                                    .append(p_src[line_feed_pos + i]);
                    }

                    macro_replaced[i_match_macro] = true;
                    replaced = true;
                    break;
                }
            }
        }

        if (!replaced)
        {
            sead::MemUtil::copy(p_dst, p_src, line_feed_pos + line_feed_len);
            p_dst += line_feed_pos + line_feed_len;
            *p_dst = '\0';
        }

        p_src += line_feed_pos + line_feed_len;

        if (replaced)
        {
            i_macro++;
            if (i_macro == macro_num)
                break;
        }
    }

    while (*p_src != '\0')
        *p_dst++ = *p_src++;

    // SEAD_ASSERT(static_cast<int>(p_dst - p_work) <= worksize);
    *p_dst = '\0';

    p_text->copy(sead::SafeString(p_work));
}

} }
