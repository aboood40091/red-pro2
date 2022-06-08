#pragma once

#include <basis/seadTypes.h>

namespace agl {

class DisplayList
{
public:
    DisplayList();
    virtual ~DisplayList();

    u8* getBuffer() const
    {
        return mpBuffer;
    }

    void setBuffer(u8* buffer, size_t size);
    void clear();

    bool beginDisplayList();
    size_t endDisplayList();

    static size_t suspend(void** p_dl);
    static void resume(void* dl, size_t size);

private:
    u8* mpBuffer;
    u32 mBufferMaxSize;
    u32 mDLSize;
};
static_assert(sizeof(DisplayList) == 0x10, "agl::DisplayList size mismatch");

}
