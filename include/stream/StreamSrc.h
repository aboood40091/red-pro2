#pragma once

#include <misc/rio_Types.h>

class StreamSrc
{
public:
    virtual u32 read(void* dst, u32 size) = 0;
    virtual u32 write(const void* src, u32 size) = 0;
    virtual u32 skip(s32 byte) = 0;
    virtual void rewind() = 0;
    virtual bool isEOF() = 0;
    virtual bool flush() { return true; }
};
