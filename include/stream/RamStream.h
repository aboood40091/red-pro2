#pragma once

#include <stream/Stream.h>
#include <stream/StreamSrc.h>

class RamStreamSrc : public StreamSrc
{
public:
    RamStreamSrc(void* start, u32 size);
    ~RamStreamSrc();

    u32 read(void* dst, u32 size) override;
    u32 write(const void* src, u32 size) override;
    u32 skip(s32 byte) override;
    void rewind() override { mCurPos = 0; }
    bool isEOF() override { return mCurPos >= mSize; }

    u8* getCurrentAddres() const { return mStartAddr + mCurPos; }
    u32 getCurrentPosition() const { return mCurPos; }

protected:
    u8* mStartAddr;
    u32 mSize;
    u32 mCurPos;
};
static_assert(sizeof(RamStreamSrc) == 0x10);

class RamReadStream : public ReadStream
{
public:
    RamReadStream(const void* start, u32 size, Modes mode);

    u8* getCurrentAddres() const { return mRamStreamSrc.getCurrentAddres(); }
    u32 getCurrentPosition() const { return mRamStreamSrc.getCurrentPosition(); }

protected:
    RamStreamSrc    mRamStreamSrc;
};
static_assert(sizeof(RamReadStream) == 0x20);
