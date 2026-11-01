static u32 alignUp32_(u32 value)
{
    return (value + 0x1fu) & ~0x1fu;
}

// Address: 0x02AD6968
s32 sub_02AD6968(void* archive_slice);

// Address: 0x02AD6C58
s32 sub_02AD6C58(void* archive_slice, u32 index, u32* out_pair);

// Address: 0x02ADAD4C
s32 sub_02ADAD4C(void* sound_startable, u32* cursor, u32 limit, u32 bump_bytes);

// Address: 0x02AF5A90
void sub_02AF5A90(u32 address);

// Address: 0x02AF5B60
void sub_02AF5B60(void* dest, u32 size, u32 value);

// Address: 0x02ADE508
void* sub_02ADE508(void* table_entry);

// Address: 0x02ADE940
void sub_02ADE940(void* handle, u32 count);

// Address: 0x02ADECE4
void sub_02ADECE4(void* handle);

// Address: 0x02ADE9C8
void sub_02ADE9C8(void* handle);

// Address: 0x02ADAE50
s32 sub_02ADAE50(void* sound_startable, void* archive_slice, u32* cursor, u32 limit)
{
    u32 cursor_value = *cursor;
    if ((cursor_value & 0x80000000u) != 0)
        return 0;

    s32 count = sub_02AD6968(archive_slice);
    u32 aligned = alignUp32_(static_cast<u32>(count) * 0x78u);
    u8* base = reinterpret_cast<u8*>(cursor_value);
    u8* end = base + aligned;
    if (reinterpret_cast<uintptr_t>(end) > limit)
        return 0;

    *cursor = reinterpret_cast<u32>(end);
    u8* player = reinterpret_cast<u8*>(sound_startable);
    *reinterpret_cast<void**>(player + 0x1C) = base;
    *reinterpret_cast<s32*>(player + 0x18) = count;
    if (count == 0)
        return 1;

    u8* entry = base;
    for (s32 index = 0; index < count; ++index)
    {
        void* handle = entry;
        if (handle != nullptr)
            handle = sub_02ADE508(handle);

        u32 pair[2] = {};
        if (sub_02AD6C58(archive_slice, static_cast<u32>(index) | 0x04000000u, pair) == 0)
            return 0;
        if (pair[1] == 0)
        {
            entry += 0x78;
            continue;
        }

        for (u32 step = 0; step < pair[0]; ++step)
        {
            if (sub_02ADAD4C(sound_startable, cursor, limit, pair[1]) == 0)
                return 0;
            sub_02ADECE4(handle);
            if (step + 1 < pair[0])
                sub_02ADE940(handle, pair[0]);
        }
        sub_02ADE9C8(handle);
        entry += 0x78;
    }

    return 1;
}

// Address: 0x02ADAD4C
s32 sub_02ADAD4C(void* sound_startable, u32* cursor, u32 limit, u32 bump_bytes)
{
    u32 base = *cursor;
    if ((base & 0x80000000u) == 0)
    {
        u32 probe = alignUp32_(base + 0x3bu);
        if (probe > limit)
            return 0;
        if (base != 0)
        {
            *cursor = base;
            sub_02AF5A90(base);
            base = *cursor;
        }
        u32 next = alignUp32_(base + 0x1fu) + alignUp32_(bump_bytes + 0x1fu);
        if (next > limit)
            return 0;
        *cursor = next;
        sub_02AF5B60(reinterpret_cast<void*>(base), bump_bytes, 0);
        return 1;
    }

    u32 next = alignUp32_(base + 0x1fu) + alignUp32_(bump_bytes + 0x1fu);
    if (next > limit)
        return 0;
    *cursor = next;
    return 1;
}
