#include <stream/BinaryStreamFormat.h>
#include <stream/Stream.h>
#include <stream/StreamSrc.h>

BinaryStreamFormat sBinaryStreamInstance;
//TextStreamFormat sTextStreamInstance;

StreamFormat* const Stream::BASIC_STREAM_FORMAT[Stream::cModeNum] = {
    &sBinaryStreamInstance,
  //&sTextStreamInstance
};

Stream::Stream()
    : mFormat(nullptr)
    , mSrcStream(nullptr)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    , mIsBigEndian(true)
#else
    , mIsBigEndian(false)
#endif // __BYTE_ORDER__
{
}

void Stream::skip(u32 size)
{
    RIO_ASSERT(mFormat);
    RIO_ASSERT(mSrcStream);
    mFormat->skip(mSrcStream, size);
}

bool Stream::isEOF()
{
    RIO_ASSERT(mSrcStream);
    return mSrcStream->isEOF();
}

void Stream::setBinaryEndian(bool is_be)
{
    mIsBigEndian = is_be;
}

void Stream::setMode(Modes mode)
{
    RIO_ASSERT(0 <= mode && mode < cModeNum);
    setUserFormat(BASIC_STREAM_FORMAT[mode]);
}

void Stream::setUserFormat(StreamFormat* format)
{
    mFormat = format;
}

u32 ReadStream::readU32()
{
    RIO_ASSERT(mFormat);
    RIO_ASSERT(mSrcStream);
    return mFormat->readU32(mSrcStream, mIsBigEndian);
}

s32 ReadStream::readS32()
{
    RIO_ASSERT(mFormat);
    RIO_ASSERT(mSrcStream);
    return mFormat->readS32(mSrcStream, mIsBigEndian);
}

f32 ReadStream::readF32()
{
    RIO_ASSERT(mFormat);
    RIO_ASSERT(mSrcStream);
    return mFormat->readF32(mSrcStream, mIsBigEndian);
}

void ReadStream::readString(std::string* dst, u32 size)
{
    RIO_ASSERT(mFormat);
    RIO_ASSERT(mSrcStream);
    RIO_ASSERT(dst->capacity() >= size);
    mFormat->readString(mSrcStream, dst, size);
}
