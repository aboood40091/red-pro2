#include <stream/BinaryStreamFormat.h>
#include <stream/StreamSrc.h>

namespace {

static inline u16 EndianToHost16(bool is_be, u16 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        return __builtin_bswap16(value);

    return value;
}

static inline u32 EndianToHost32(bool is_be, u32 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        return __builtin_bswap32(value);

    return value;
}

static inline u64 EndianToHost64(bool is_be, u64 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        return __builtin_bswap64(value);

    return value;
}

}

u8 BinaryStreamFormat::readU8(StreamSrc* src, bool is_be)
{
    u8 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(u8));
    RIO_ASSERT(rb == sizeof( u8 ));
    //
    return ret;
}

u16 BinaryStreamFormat::readU16(StreamSrc* src, bool is_be)
{
    u16 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(u16));
    RIO_ASSERT(rb == sizeof( u16 ));
    ret = EndianToHost16(is_be, ret);
    return ret;
}

u32 BinaryStreamFormat::readU32(StreamSrc* src, bool is_be)
{
    u32 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(u32));
    RIO_ASSERT(rb == sizeof( u32 ));
    ret = EndianToHost32(is_be, ret);
    return ret;
}

u64 BinaryStreamFormat::readU64(StreamSrc* src, bool is_be)
{
    u64 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(u64));
    RIO_ASSERT(rb == sizeof( u64 ));
    ret = EndianToHost64(is_be, ret);
    return ret;
}

s8 BinaryStreamFormat::readS8(StreamSrc* src, bool is_be)
{
    s8 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(s8));
    RIO_ASSERT(rb == sizeof( s8 ));
    //
    return ret;
}

s16 BinaryStreamFormat::readS16(StreamSrc* src, bool is_be)
{
    s16 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(s16));
    RIO_ASSERT(rb == sizeof( s16 ));
    ret = EndianToHost16(is_be, ret);
    return ret;
}

s32 BinaryStreamFormat::readS32(StreamSrc* src, bool is_be)
{
    s32 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(s32));
    RIO_ASSERT(rb == sizeof( s32 ));
    ret = EndianToHost32(is_be, ret);
    return ret;
}

s64 BinaryStreamFormat::readS64(StreamSrc* src, bool is_be)
{
    s64 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(s64));
    RIO_ASSERT(rb == sizeof( s64 ));
    ret = EndianToHost64(is_be, ret);
    return ret;
}

f32 BinaryStreamFormat::readF32(StreamSrc* src, bool is_be)
{
    u32 ret = 0;
    [[maybe_unused]] u32 rb = src->read(&ret, sizeof(u32));
    RIO_ASSERT(rb == sizeof( u32 ));
    ret = EndianToHost32(is_be, ret);
    return *(f32*)&ret;
}

void BinaryStreamFormat::readBit(StreamSrc* src, void* data, u32 bitnum)
{
    u8* data8 = static_cast<u8*>(data);
    u32 bytenum = bitnum / 8;
    [[maybe_unused]] u32 rb = src->read(data8, bytenum);
    RIO_ASSERT(rb == bytenum);
    bitnum -= bytenum * 8;
    if (bitnum > 0)
    {
        u8 buffer;
        rb = src->read(&buffer, 1);
        RIO_ASSERT(rb == 1);
        u8 mask = 0xff << (bitnum & 0xff);
        data8[bytenum] &= mask;
        data8[bytenum] |= buffer & ~mask;
    }
}

void BinaryStreamFormat::readString(StreamSrc* src, std::string* dst, u32 size)
{
    u32 remain_size = 0;
    if (dst->capacity() < size)
    {
        remain_size = size - dst->capacity();
        size = dst->capacity();
        RIO_LOG("Warning: not enough buffer length. drop %u char(s).\n", remain_size);
    }
    dst->resize(size); dst->c_str(); // Forces null termination
    [[maybe_unused]] u32 rb = src->read(dst->data(), size);
    RIO_ASSERT(rb == size);
    if (size + 1 < dst->capacity())
    {
        dst->erase(size, std::string::npos);
    }
    else
    {
        dst->erase(dst->capacity() - 1, std::string::npos);
    }
    if (remain_size > 0)
    {
        // IDK why they are doing this
        rb = src->read(dst->data(), remain_size);
        RIO_ASSERT(rb == remain_size);
    }
}

u32 BinaryStreamFormat::readMemBlock(StreamSrc* src, void* dst, u32 size)
{
    return src->read(dst, size);
}

void BinaryStreamFormat::writeU8(StreamSrc* src, bool is_be, u8 value)
{
    //
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(u8));
    RIO_ASSERT(wb == sizeof( u8 ));
}

void BinaryStreamFormat::writeU16(StreamSrc* src, bool is_be, u16 value)
{
    value = EndianToHost16(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(u16));
    RIO_ASSERT(wb == sizeof( u16 ));
}

void BinaryStreamFormat::writeU32(StreamSrc* src, bool is_be, u32 value)
{
    value = EndianToHost32(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(u32));
    RIO_ASSERT(wb == sizeof( u32 ));
}

void BinaryStreamFormat::writeU64(StreamSrc* src, bool is_be, u64 value)
{
    value = EndianToHost64(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(u64));
    RIO_ASSERT(wb == sizeof( u64 ));
}

void BinaryStreamFormat::writeS8(StreamSrc* src, bool is_be, s8 value)
{
    //
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(s8));
    RIO_ASSERT(wb == sizeof( s8 ));
}

void BinaryStreamFormat::writeS16(StreamSrc* src, bool is_be, s16 value)
{
    value = EndianToHost16(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(s16));
    RIO_ASSERT(wb == sizeof( s16 ));
}

void BinaryStreamFormat::writeS32(StreamSrc* src, bool is_be, s32 value)
{
    value = EndianToHost32(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(s32));
    RIO_ASSERT(wb == sizeof( s32 ));
}

void BinaryStreamFormat::writeS64(StreamSrc* src, bool is_be, s64 value)
{
    value = EndianToHost64(is_be, value);
    [[maybe_unused]] u32 wb = src->write(&value, sizeof(s64));
    RIO_ASSERT(wb == sizeof( s64 ));
}

void BinaryStreamFormat::writeF32(StreamSrc* src, bool is_be, f32 value)
{
    u32 u_value = EndianToHost32(is_be, *(u32*)&value);
    [[maybe_unused]] u32 wb = src->write(&u_value, sizeof(u32));
    RIO_ASSERT(wb == sizeof( u32 ));
}

void BinaryStreamFormat::writeBit(StreamSrc* src, const void* data, u32 bitnum)
{
    const u8* data8 = static_cast<const u8*>(const_cast<void*>(data));
    u8 bytenum = bitnum / 8;
    [[maybe_unused]] u32 wb = src->write(data8, bytenum);
    RIO_ASSERT(wb == bytenum);
    bitnum -= bytenum * 8;
    if (bitnum > 0)
    {
        wb = src->write(&data8[bytenum], 1);
        RIO_ASSERT(wb == 1);
    }
}

void BinaryStreamFormat::writeString(StreamSrc* src, const std::string& str, u32 size)
{
    u32 str_size = str.length();
    if (size < str_size)
    {
        str_size = size;
    }
    [[maybe_unused]] u32 wb = src->write(str.c_str(), str_size);
    RIO_ASSERT(wb == str_size);
    char nullchar = '\0';
    for (; str_size < size; str_size++)
    {
        wb += src->write(&nullchar, 1);
    }
    RIO_ASSERT(wb == size);
}

void BinaryStreamFormat::writeMemBlock(StreamSrc* src, const void* data, u32 size)
{
    [[maybe_unused]] u32 wb = src->write(data, size);
    RIO_ASSERT(wb == size);
}

void BinaryStreamFormat::skip(StreamSrc* src, u32 size)
{
    src->skip(size);
}

void BinaryStreamFormat::rewind(StreamSrc* src)
{
    src->rewind();
}
