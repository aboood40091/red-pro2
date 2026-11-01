static u32 alignUp32_(u32 value)
{
    return (value + 0x1fu) & ~0x1fu;
}

using SoundSetupRegionPrepFn = void* (*)(void* region, u8* player, u32 player_data_offset);

static s32 carveSoundSetupRegion_(
    u8* player,
    u32* cursor,
    u32 limit,
    u32 unit_count,
    u32 unit_stride,
    u32 field_base_offset,
    u32 field_size_offset,
    u32 slot_offset,
    u32 stack_tag_offset,
    u32 player_data_offset,
    SoundSetupRegionPrepFn region_prep)
{
    u32 base = *cursor;
    if ((base & 0x80000000u) != 0)
        return 0;

    u32 bytes = unit_count * unit_stride;
    u32 aligned = alignUp32_(bytes + 0x1fu);
    u32 end = base + aligned;
    if (end > limit)
        return 0;

    u32 loop_count = unit_count;
    if (loop_count == 0)
        loop_count = 1;

    u8* region = reinterpret_cast<u8*>(base);
    for (u32 step = 0; step < loop_count; ++step)
    {
        void* handle = region;
        if (handle != nullptr && region_prep != nullptr)
            handle = region_prep(handle, player, player_data_offset);

        u32 stack_tag = stack_tag_offset;
        sub_02A9F50C(player + slot_offset, &stack_tag, reinterpret_cast<u8*>(handle) + 0x184);
        region += unit_stride;
    }

    *reinterpret_cast<u32*>(player + field_size_offset) = aligned;
    *reinterpret_cast<void**>(player + field_base_offset) = reinterpret_cast<void*>(base);
    *cursor = end;
    return 1;
}

// Address: 0x02AD6968
s32 sub_02AD6968(void* archive_slice);

// Address: 0x02AD07E0
void* sub_02AD07E0(void* region, u8* player, u32 player_data_offset);

// Address: 0x02AE8814
void* sub_02AE8814(void* region, u8* player, u32 player_data_offset);

// Address: 0x02AE0550
void* sub_02AE0550(void* region, u8* player, u32 player_data_offset);

// Address: 0x02A9F50C
void sub_02A9F50C(u8* slot, u32* stack_tag, u8* source);

// Address: 0x02AF5A74
void sub_02AF5A74(u8* player_ext);

// Address: 0x02ADAF9C
s32 sub_02ADAF9C(void* sound_startable, void* archive_slice, u32* cursor, u32 limit)
{
    u8* player = reinterpret_cast<u8*>(sound_startable);
    s32 count = sub_02AD6968(archive_slice);
    return carveSoundSetupRegion_(
        player,
        cursor,
        limit,
        static_cast<u32>(count),
        0x6A4u,
        0x20u,
        0x24u,
        0x34u,
        0x38u,
        0x20u,
        sub_02AD07E0);
}

// Address: 0x02ADB06C
s32 sub_02ADB06C(void* sound_startable, void* header_factor, u32* cursor, u32 limit)
{
    u8* player = reinterpret_cast<u8*>(sound_startable);
    u32 count = reinterpret_cast<u32>(header_factor);
    return carveSoundSetupRegion_(
        player,
        cursor,
        limit,
        count,
        0x5A4u,
        0x40u,
        0x44u,
        0x54u,
        0x58u,
        0x40u,
        sub_02AE8814);
}

// Address: 0x02ADB13C
s32 sub_02ADB13C(void* sound_startable, void* header_factor, u32* cursor, u32 limit)
{
    u8* player = reinterpret_cast<u8*>(sound_startable);
    u32 count = reinterpret_cast<u32>(header_factor);
    return carveSoundSetupRegion_(
        player,
        cursor,
        limit,
        count,
        0x6BD0u,
        0x60u,
        0x64u,
        0x74u,
        0x78u,
        0x60u,
        sub_02AE0550);
}

// Address: 0x02ADB20C
s32 sub_02ADB20C(void* sound_startable, void* header_factor, u32* cursor, u32 limit)
{
    u32 factor = reinterpret_cast<u32>(header_factor);
    u32 base = *cursor;
    if ((base & 0x80000000u) != 0)
        return 0;

    u32 aligned = alignUp32_((factor << 8) + 0x1fu);
    u32 end = base + aligned;
    if (end > limit)
        return 0;

    sub_02AF5A74(reinterpret_cast<u8*>(sound_startable) + 0x84);
    *cursor = end;
    return 1;
}

static void linkSoundSetupBlock_(u32*& head, u32 sentinel_offset, u8* player, u32 value, u32 stride)
{
    u32* node = reinterpret_cast<u32*>(player + sentinel_offset);
    while (reinterpret_cast<u8*>(*node) != player + sentinel_offset)
    {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(*node) - 8) = value;
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(*node) - 4) = stride;
        node = reinterpret_cast<u32*>(*node);
        value += stride;
    }
}

// Address: 0x02ADB290
s32 sub_02ADB290(void* sound_startable, void* out_pair, u32 total_size, void* holder)
{
    u8* player = reinterpret_cast<u8*>(sound_startable);
    u32 holder_value = reinterpret_cast<u32>(holder);
    if ((holder_value & 0x80000000u) != 0)
        return 0;

    u32 stride = (total_size + 3u) & ~7u;
    u32 cursor = holder_value;
    linkSoundSetupBlock_(reinterpret_cast<u32*&>(cursor), 0x58u, player, holder_value, stride);
    linkSoundSetupBlock_(reinterpret_cast<u32*&>(cursor), 0x38u, player, holder_value, stride);
    linkSoundSetupBlock_(reinterpret_cast<u32*&>(cursor), 0x78u, player, holder_value, stride);

    if (cursor > total_size)
        return 0;

    *reinterpret_cast<u32*>(player + 0xB4) = stride;
    return 1;
}
