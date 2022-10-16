#include <resource/SharcArchiveRes.h>
#include <resource/SharcHasher.h>

#include <cstdio>
#include <cstring>

namespace {

#if RIO_IS_CAFE

template <typename C>
inline int strcpy_s(C* d, size_t dmax, const C* s)
{
    if(dmax <=1 || !d)
    {
        if (!d || !dmax)
            return 22;

        *d = C(0);
        return 0;
    }

    for(C* de = d + dmax - 1; (d != de || (*d = C(0))) && (*d = *s); ++d, ++s)
        ;

    return 0;
}

#endif // RIO_IS_CAFE

inline u16 EndianToHost(bool is_be, u16 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        return __builtin_bswap16(value);

    return value;
}

inline u32 EndianToHost(bool is_be, u32 value)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    if (is_be)
#else
    if (!is_be)
#endif
        return __builtin_bswap32(value);

    return value;
}

inline s32 binarySearch_(
    u32 hash, const SharcArchiveRes::FATEntry* buffer,
    s32 start, s32 end, bool is_be
)
{
    s32 middle;

    for (;;)
    {
        middle = (start + end) / 2;

        u32 buf_hash = EndianToHost(is_be, buffer[middle].hash);
        if (buf_hash == hash)
            return middle;

        else if (buf_hash < hash)
        {
            if (start == middle)
                return -1;

            start = middle;
        }

        else
        {
            if (end == middle)
                return -1;

            end = middle;
        }
    }
}

inline uintptr_t GetOffsetFromPtr(const void* a, const void* b)
{
    return reinterpret_cast<uintptr_t>(a) - reinterpret_cast<uintptr_t>(b);
}

}

#define SHARC_ENDIAN_TO_HOST(val) (EndianToHost(mIsBigEndian, (val)))

bool SharcArchiveRes::prepareArchive(const void* archive)
{
    if (!archive)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): archive must not be nullptr.\n");
        RIO_ASSERT(false);
        return false;
    }

    const u8* archive8 = reinterpret_cast<const u8*>(archive);

    mArchiveBlockHeader = reinterpret_cast<const ArchiveBlockHeader*>(archive8);
    if (std::strncmp(mArchiveBlockHeader->signature, "SARC", 4) != 0)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid ArchiveBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    if (mArchiveBlockHeader->byte_order != 0xfeff && mArchiveBlockHeader->byte_order != 0xfffe)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid Endian Type\n");
        RIO_ASSERT(false);
        return false;
    }

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    mIsBigEndian = mArchiveBlockHeader->byte_order == 0xfffe;
#else
    mIsBigEndian = mArchiveBlockHeader->byte_order == 0xfeff;
#endif

    if (SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->version) != cArchiveVersion)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): unmatching version ( expect: %x, actual: %x )\n", cArchiveVersion, SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->version));
        RIO_ASSERT(false);
        return false;
    }

    if (SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->header_size) != sizeof(ArchiveBlockHeader))
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid ArchiveBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    mFATBlockHeader = reinterpret_cast<const FATBlockHeader*>(archive8 + SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->header_size));
    if (std::strncmp(mFATBlockHeader->signature, "SFAT", 4) != 0)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid FATBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    if (SHARC_ENDIAN_TO_HOST(mFATBlockHeader->header_size) != sizeof(FATBlockHeader))
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid FATBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    if (SHARC_ENDIAN_TO_HOST(mFATBlockHeader->file_num) > cArchiveEntryMax)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid FATBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    mFATEntrys = {
        reinterpret_cast<const FATEntry*>(
            archive8 + SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->header_size)
                     + SHARC_ENDIAN_TO_HOST(mFATBlockHeader->header_size)
        ),
        SHARC_ENDIAN_TO_HOST(mFATBlockHeader->file_num)
    };

    const FNTBlockHeader* fnt_header = reinterpret_cast<const FNTBlockHeader*>(
        archive8 + SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->header_size)
                 + SHARC_ENDIAN_TO_HOST(mFATBlockHeader->header_size)
                 + SHARC_ENDIAN_TO_HOST(mFATBlockHeader->file_num) * sizeof(FATEntry)
    );
    if (std::strncmp(fnt_header->signature, "SFNT", 4) != 0)
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid FNTBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    if (SHARC_ENDIAN_TO_HOST(fnt_header->header_size) != sizeof(FNTBlockHeader))
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid FNTBlockHeader\n");
        RIO_ASSERT(false);
        return false;
    }

    mFNTBlock = reinterpret_cast<const char*>(fnt_header) + SHARC_ENDIAN_TO_HOST(fnt_header->header_size);
    if (static_cast<s32>(SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->data_block_offset)) < static_cast<ssize_t>(GetOffsetFromPtr(mArchiveBlockHeader, mFNTBlock)))
    {
        RIO_LOG("SharcArchiveRes::prepareArchive(): Invalid data block offset\n");
        RIO_ASSERT(false);
        return false;
    }

    mDataBlock = archive8 + SHARC_ENDIAN_TO_HOST(mArchiveBlockHeader->data_block_offset);
    return true;
}

void* SharcArchiveRes::getFileFastImpl_(s32 entry_id, FileInfo* file_info) const
{
    if (entry_id < 0 || size_t(entry_id) >= mFATEntrys.size())
        return nullptr;

    u32 start_offset = SHARC_ENDIAN_TO_HOST(mFATEntrys[entry_id].data_start_offset);

    if (file_info)
    {
        u32 end_offset = SHARC_ENDIAN_TO_HOST(mFATEntrys[entry_id].data_end_offset);
        if (start_offset > end_offset)
            return nullptr;

        u32 length = end_offset - start_offset;

        setFileInfo_(file_info, start_offset, length);
    }

    return const_cast<u8*>(mDataBlock) + start_offset;
}

s32 SharcArchiveRes::convertPathToEntryIDImpl_(const char* file_path) const
{
    u32 hash = sharcCalcHash32(file_path, SHARC_ENDIAN_TO_HOST(mFATBlockHeader->hash_key));

    s32 start = 0;
    s32 end = mFATEntrys.size();

    s32 id = binarySearch_(hash, mFATEntrys.data(), start, end, mIsBigEndian);
    if (id == -1)
        return -1;

    u32 offset = SHARC_ENDIAN_TO_HOST(mFATEntrys[id].name_offset);
    if (offset != 0)
    {
        id -= (offset >> 24) - 1;

        while (id < end)
        {
            const FATEntry* entry = &mFATEntrys[id];
            if (SHARC_ENDIAN_TO_HOST(entry->hash) != hash)
                return -1;

            else
            {
                u32 name_offset = SHARC_ENDIAN_TO_HOST(entry->name_offset);

                if (reinterpret_cast<const u8*>(mFNTBlock + (name_offset & 0x00ffffff)) > mDataBlock)
                {
                    RIO_LOG("SharcArchiveRes::convertPathToEntryIDImpl_(): Warning: Invalid data start offset\n");
                    return -1;
                }

                if (std::strcmp(file_path, mFNTBlock + (name_offset & 0x00ffffff) * cFileNameTableAlign) == 0)
                    return id;
            }

            id++;
        }
    }

    return id;
}

std::vector<SharcArchiveRes::Entry> SharcArchiveRes::readEntry(u32 first, u32 num) const
{
    std::vector<Entry> entry;

    while (first + entry.size() < SHARC_ENDIAN_TO_HOST(mFATBlockHeader->file_num) && entry.size() < num)
    {
        u32 id = first + entry.size();
        RIO_ASSERT(id >= first);

        Entry& new_entry = entry.emplace_back();

        u32 offset = SHARC_ENDIAN_TO_HOST(mFATEntrys[id].name_offset);
        if (offset == 0)
        {
            std::snprintf(
                new_entry.name,
                Entry::cMaxNameLength,
                "%08x",
                SHARC_ENDIAN_TO_HOST(mFATEntrys[id].hash)
            );
        }
        else
        {
            if (reinterpret_cast<const u8*>(mFNTBlock + (offset & 0x00ffffff)) > mDataBlock)
            {
                RIO_LOG("SharcArchiveRes::readDirectory(): Warning: Invalid data start offset\n");
                new_entry.name[0] = '\0';
            }
            else
            {
                strcpy_s(new_entry.name, Entry::cMaxNameLength, mFNTBlock + (offset & 0x00ffffff) * cFileNameTableAlign);
            }
        }
    }

    return entry;
}
