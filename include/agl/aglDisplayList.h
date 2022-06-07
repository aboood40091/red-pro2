#pragma once

#include <basis/seadTypes.h>

namespace agl {

class DisplayList
{
public:
    DisplayList();
    virtual ~DisplayList();

    void clear();
    void setBuffer(u8* buffer, size_t size);

private:
    u8* mpBuffer;
    u32 mBufferMaxSize;
    u32 mDLSize;
};
static_assert(sizeof(DisplayList) == 0x10, "agl::DisplayList size mismatch");

}
