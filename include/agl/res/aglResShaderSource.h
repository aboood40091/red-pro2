#pragma once

#include <agl/res/aglResCommon.h>

namespace agl {

struct ResShaderSourceData
{
    u32 mSize;
    u32 mNameLen;
    u32 mCodeLen; // Code Length
    u32 _c;       // Code Length... 2
    // char mName[];
};
static_assert(sizeof(ResShaderSourceData) == 0x10, "agl::ResShaderSourceData size mismatch");

class ResShaderSource : public ResCommon<ResShaderSourceData>
{
    AGL_RES_COMMON(ResShaderSource)

public:
    const char* getName() const
    {
        return (const char*)(ptr() + 1);
    }

    const char* getCode() const
    {
        return getName() + ptr()->mNameLen;
    }
};

typedef ResArray<ResShaderSource> ResShaderSourceArray;

typedef ResShaderSourceArray::DataType ResShaderSourceArrayData;
static_assert(sizeof(ResShaderSourceArrayData) == 8, "agl::ResShaderSourceArrayData size mismatch");

}
