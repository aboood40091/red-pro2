#pragma once

#include <misc/rio_Types.h>

#include <gsl/span>
#include <vector>

class SharcArchiveRes
{
public:
    static constexpr u32 cArchiveVersion        = 0x100;
    static constexpr s32 cArchiveEntryMax       = 0x3fff;
    static constexpr s32 cFileNameTableAlign    = 4;

public:
    class FileInfo
    {
    public:
        explicit FileInfo()
            : mStartOffset(0)
            , mLength(0)
        {
        }

        u32 getStartOffset() const { return mStartOffset; }
        u32 getLength() const { return mLength; }

    private:
        u32 mStartOffset;
        u32 mLength;

        friend class SharcArchiveRes;
    };

    struct Entry
    {
        static constexpr s32 cMaxNameLength = 256;

        Entry()
        {
            name[0] = '\0';
        }

        char name[cMaxNameLength];
    };

public:
    struct ArchiveBlockHeader
    {
        char    signature[4];
        u16     header_size;
        u16     byte_order;
        u32     file_size;
        u32     data_block_offset;
        u16     version;
        u16     reserved;
    };
    static_assert(sizeof(ArchiveBlockHeader) == 0x14);

    struct FATBlockHeader
    {
        char    signature[4];
        u16     header_size;
        u16     file_num;
        u32     hash_key;
    };
    static_assert(sizeof(FATBlockHeader) == 0xC);

    struct FATEntry
    {
        u32     hash;
        u32     name_offset;
        u32     data_start_offset;
        u32     data_end_offset;
    };
    static_assert(sizeof(FATEntry) == 0x10);

    struct FNTBlockHeader
    {
        char    signature[4];
        u16     header_size;
        u16     reserved;
    };
    static_assert(sizeof(FNTBlockHeader) == 8);

public:
    SharcArchiveRes()
        : mArchiveBlockHeader(nullptr)
        , mFATBlockHeader(nullptr)
        , mFNTBlock(nullptr)
        , mDataBlock(nullptr)
    {
    }

    bool prepareArchive(const void* archive);

    std::vector<Entry> readEntry(u32 first = 0, u32 num = u32(-1)) const;

    void* getFile(const char* file_path, u32* length = nullptr) const
    {
        FileInfo file_info;
        void* data = getFileImpl_(file_path, &file_info);
        if (data && length)
            *length = file_info.getLength();

        return data;
    }

private:
    void* getFileImpl_(const char* file_path, FileInfo* file_info = nullptr) const
    {
        s32 id = convertPathToEntryIDImpl_(file_path);
        if (id < 0)
            return nullptr;

        return getFileFastImpl_(id, file_info);
    }

    void* getFileFastImpl_(s32 entry_id, FileInfo* file_info = nullptr) const;

    s32 convertPathToEntryIDImpl_(const char* file_path) const;

    static void setFileInfo_(FileInfo* file_info, u32 start_offset, u32 length)
    {
        RIO_ASSERT(file_info);
        file_info->mStartOffset = start_offset;
        file_info->mLength      = length;
    }

private:
    const ArchiveBlockHeader*   mArchiveBlockHeader;
    const FATBlockHeader*       mFATBlockHeader;
    const char*                 mFNTBlock;
    gsl::span<const FATEntry>   mFATEntrys;
    const u8*                   mDataBlock;
    bool                        mIsBigEndian;
};
