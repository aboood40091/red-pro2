#pragma once

#include <stream/StreamFormat.h>

class BinaryStreamFormat : public StreamFormat
{
    u8 readU8(StreamSrc* src, bool is_be) override;
    u16 readU16(StreamSrc* src, bool is_be) override;
    u32 readU32(StreamSrc* src, bool is_be) override;
    u64 readU64(StreamSrc* src, bool is_be) override;
    s8 readS8(StreamSrc* src, bool is_be) override;
    s16 readS16(StreamSrc* src, bool is_be) override;
    s32 readS32(StreamSrc* src, bool is_be) override;
    s64 readS64(StreamSrc* src, bool is_be) override;
    f32 readF32(StreamSrc* src, bool is_be) override;
    void readBit(StreamSrc* src, void* data, u32 bitnum) override;
    void readString(StreamSrc* src, std::string* dst, u32 size) override;
    u32 readMemBlock(StreamSrc* src, void* dst, u32 size) override;
    void writeU8(StreamSrc* src, bool is_be, u8 value) override;
    void writeU16(StreamSrc* src, bool is_be, u16 value) override;
    void writeU32(StreamSrc* src, bool is_be, u32 value) override;
    void writeU64(StreamSrc* src, bool is_be, u64 value) override;
    void writeS8(StreamSrc* src, bool is_be, s8 value) override;
    void writeS16(StreamSrc* src, bool is_be, s16 value) override;
    void writeS32(StreamSrc* src, bool is_be, s32 value) override;
    void writeS64(StreamSrc* src, bool is_be, s64 value) override;
    void writeF32(StreamSrc* src, bool is_be, f32 value) override;
    void writeBit(StreamSrc* src, const void* data, u32 bitnum) override;
    void writeString(StreamSrc* src, const std::string& str, u32 size) override;
    void writeMemBlock(StreamSrc* src, const void* data, u32 size) override;
    void writeDecorationText(StreamSrc* src, const std::string&) override { }
    void writeNullChar(StreamSrc* src) override { }
    void skip(StreamSrc* src, u32 size) override;
    void flush(StreamSrc* src) override { }
    void rewind(StreamSrc* src) override;
};
