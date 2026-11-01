static u32 alignUp32_(u32 value)
{
    return (value + 0x1fu) & ~0x1fu;
}

// Address: 0x02AD8600
s32 sub_02AD8600_getSoundCount(void* sound_archive);

// Address: 0x02AD87B8
s32 sub_02AD87B8_readSoundEntry(void* sound_archive, u32 index);

// Address: 0x02AD8A4C
s32 sub_02AD8A4C_readArchiveHeader(void* sound_archive);

// Address: 0x02AD6968
s32 sub_02AD6968(void* archive_slice)
{
    void* archive = *reinterpret_cast<void**>(archive_slice);
    return sub_02AD8600_getSoundCount(archive);
}

// Address: 0x02AD6C58
s32 sub_02AD6C58(void* archive_slice, u32 index, u32* out_pair)
{
    void* archive = *reinterpret_cast<void**>(archive_slice);
    if (sub_02AD87B8_readSoundEntry(archive, index) == 0)
        return 0;

    void* reader = *reinterpret_cast<void**>(reinterpret_cast<u8*>(archive_slice) + 4);
    if (reader == nullptr)
        return 0;

    u32 vtable = *reinterpret_cast<u32*>(reader);
    using ReadPairFn = s32 (*)(void*, u32*);
    ReadPairFn read_pair = reinterpret_cast<ReadPairFn>(*reinterpret_cast<u32*>(vtable + 0x44));
    read_pair(reader, out_pair);
    return 1;
}

// Address: 0x02AD6CF0
s32 sub_02AD6CF0(void* archive_slice, void* out_pair)
{
    void* archive = *reinterpret_cast<void**>(archive_slice);
    if (sub_02AD8A4C_readArchiveHeader(archive) == 0)
        return 0;

    void* reader = *reinterpret_cast<void**>(reinterpret_cast<u8*>(archive_slice) + 4);
    if (reader == nullptr)
        return 0;

    u32 vtable = *reinterpret_cast<u32*>(reader);
    using ReadPairFn = s32 (*)(void*, void*);
    ReadPairFn read_pair = reinterpret_cast<ReadPairFn>(*reinterpret_cast<u32*>(vtable + 0x44));
    read_pair(reader, out_pair);
    return 1;
}

// Address: 0x02ADABBC
u32 sub_02ADABBC(void* sound_startable, void* archive_slice, void* heap, u32 heap_arg)
{
    s32 count = sub_02AD6968(archive_slice);
    u32 total = alignUp32_(static_cast<u32>(count) * 0x78u);

    for (s32 index = 0; index < count; ++index)
    {
        u32 pair[2] = {};
        if (sub_02AD6C58(archive_slice, static_cast<u32>(index) | 0x04000000u, pair) == 0)
            continue;
        if (pair[1] == 0 || pair[0] == 0)
            continue;

        u32 aligned_inner = alignUp32_(pair[1] + 0x1fu);
        for (u32 step = 0; step < pair[0]; ++step)
        {
            total += 0x20u;
            total += aligned_inner;
        }
    }

    u8 header_block[0x30] = {};
    u32* header = reinterpret_cast<u32*>(header_block + 0x10);
    if (sub_02AD6CF0(archive_slice, header_block + 0x10) != 0)
    {
        total += alignUp32_(header[5] * 0x5A4u + 0x1fu);
        total += alignUp32_(header[0] * 0x6A4u + 0x1fu);
        total += alignUp32_(header[2] * 0x6BD0u + 0x1fu);
        total += alignUp32_((header[1] << 8) + 0x1fu);
    }

    if (heap_arg != 0)
    {
        u8 extra_block[0x30] = {};
        u32* extra = reinterpret_cast<u32*>(extra_block + 0x10);
        sub_02AD6CF0(archive_slice, extra_block + 0x10);
        u32 mixed = extra[0] + extra[5] + extra[2];
        u32 scale = (heap_arg + 3u) & ~7u;
        total += scale * mixed;
    }

    return total;
}

// Address: 0x02ADAD00
u32 sub_02ADAD00(void* sound_startable, void* archive_slice)
{
    u8 block[0x28] = {};
    if (sub_02AD6CF0(archive_slice, block + 8) == 0)
        return 0;
    u32* words = reinterpret_cast<u32*>(block + 8);
    return words[4] * 0xCD00u;
}

// Address: 0x02ADB5E4
u32 sub_02ADB5E4(void* sound_startable, void* archive_slice, u32 aligned_size)
{
    u8 block[0x28] = {};
    if (sub_02AD6CF0(archive_slice, block + 8) == 0)
        return 0;
    u32* words = reinterpret_cast<u32*>(block + 8);
    return words[4] * aligned_size;
}

// Address: 0x02AD8600
s32 sub_02AD8600_getSoundCount(void* sound_archive)
{
    void* link = *reinterpret_cast<void**>(reinterpret_cast<u8*>(sound_archive) + 0x3C);
    return *reinterpret_cast<s32*>(link);
}

// Address: 0x02AD87B8
s32 sub_02AD87B8_readSoundEntry(void* sound_archive, u32 index)
{
    return 1;
}

// Address: 0x02AD8A4C
s32 sub_02AD8A4C_readArchiveHeader(void* sound_archive)
{
    return 1;
}
