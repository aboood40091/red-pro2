namespace sead {

class HeapMgr;

// Address: 0x02A0D554
HeapMgr* HeapMgr_getCurrentHeap();

}

struct SoundArchivePlayerSetupParams {
    void* archive_slice;
    void* field_04;
    void* buffer_primary;
    void* archive_holder;
    void* mem_c8;
    void* buffer_primary_copy;
    void* mem_d0;
    u32 combined_offset;
    void* mem_dc;
    void* mem_e0;
    void* heap_arg;
};

using AudioChildPrecheckFn = s32 (*)(void*);

// Address: 0x029E779C
void* sub_029E779C(void* archive_holder);

// Address: 0x02ADABBC
u32 sub_02ADABBC(void* sound_startable, void* archive_slice, sead::HeapMgr* heap, u32 heap_arg);

// Address: 0x02ADAD00
u32 sub_02ADAD00(void* sound_startable, void* archive_slice);

// Address: 0x02ADB5E4
u32 sub_02ADB5E4(void* sound_startable, void* archive_slice, u32 aligned_size);

// Address: 0x029F18DC
void* sub_029F18DC(void* buffer, sead::HeapMgr* heap, u32 alignment);

// Address: 0x02ADB634
s32 sub_02ADB634(void* sound_startable, SoundArchivePlayerSetupParams* params);

constexpr u32 kAudioPlayerInitFlag = 0x101F364Cu;
constexpr u32 kAudioPlayerInitWord = 0x101FBAD4u;
constexpr u32 kAudioPlayerInitValue = 0x1019D9E0u;

// Address: 0x029E6C38
void sub_029E6C38(
    void* child,
    u32 arg_10,
    u32 arg_14,
    u32 arg_18,
    sead::HeapMgr* heap)
{
    if (child == nullptr)
        return;

    u8* bytes = reinterpret_cast<u8*>(child);
    void* sound_startable = bytes + 4;
    void* archive_holder = *reinterpret_cast<void**>(bytes + 0xE4);
    void* archive_slice = sub_029E779C(archive_holder);

    u32 buffer_a_size = sub_02ADABBC(sound_startable, archive_slice, heap, arg_18);
    void* buffer_a = reinterpret_cast<void*>(buffer_a_size);
    void* mem_c8 = sub_029F18DC(buffer_a, heap, 0x40u);
    *reinterpret_cast<void**>(bytes + 0xC8) = mem_c8;

    u32 buffer_b_size = sub_02ADAD00(sound_startable, archive_slice);
    u32 combined = buffer_b_size + arg_10;
    void* buffer_b = reinterpret_cast<void*>(combined);
    void* mem_d0 = sub_029F18DC(buffer_b, heap, 0x40u);
    *reinterpret_cast<void**>(bytes + 0xD0) = mem_d0;

    SoundArchivePlayerSetupParams params = {};
    params.archive_slice = archive_slice;
    params.buffer_primary = buffer_a;
    params.archive_holder = archive_holder;
    params.mem_c8 = mem_c8;
    params.buffer_primary_copy = buffer_a;
    params.mem_d0 = mem_d0;
    params.combined_offset = combined;
    params.heap_arg = reinterpret_cast<void*>(arg_18);

    if (arg_14 == 0)
    {
        params.mem_d0 = mem_d0;
        params.mem_dc = *reinterpret_cast<void**>(bytes + 0xDC);
        params.mem_e0 = *reinterpret_cast<void**>(bytes + 0xE0);
        sub_02ADB634(sound_startable, &params);
        *reinterpret_cast<void**>(bytes + 0xCC) = buffer_a;
        *reinterpret_cast<u32*>(bytes + 0xD4) = combined;
        return;
    }

    u32 aligned = (arg_14 + 0x3Fu) & ~0x3Fu;
    u32 extra_size = sub_02ADB5E4(sound_startable, archive_slice, aligned);
    void* extra = reinterpret_cast<void*>(extra_size);
    void* mem_e0 = sub_029F18DC(extra, heap, 0x40u);
    *reinterpret_cast<void**>(bytes + 0xE0) = mem_e0;
    void* mem_dc = sub_029F18DC(mem_d0, heap, 0x40u);
    *reinterpret_cast<void**>(bytes + 0xDC) = mem_dc;

    params.mem_d0 = mem_d0;
    params.mem_dc = mem_dc;
    params.mem_e0 = mem_e0;
    sub_02ADB634(sound_startable, &params);
    *reinterpret_cast<u32*>(bytes + 0xD4) = combined;
    *reinterpret_cast<void**>(bytes + 0xCC) = buffer_a;
}

// Address: 0x029E8324
void sub_029E8324(void* self)
{
    u8* bytes = reinterpret_cast<u8*>(self);
    void* holder = *reinterpret_cast<void**>(bytes + 0x34);
    void* child = nullptr;
    if (holder != nullptr)
        child = *reinterpret_cast<void**>(reinterpret_cast<u8*>(holder) + 0x18);

    u32* flag = reinterpret_cast<u32*>(kAudioPlayerInitFlag);
    if (*flag == 0)
    {
        *flag = 1;
        *reinterpret_cast<u32*>(kAudioPlayerInitWord) = kAudioPlayerInitValue;
    }

    if (child != nullptr)
    {
        u32 vtable = *reinterpret_cast<u32*>(child);
        AudioChildPrecheckFn pre =
            reinterpret_cast<AudioChildPrecheckFn>(*reinterpret_cast<u32*>(vtable + 0xC));
        if (pre(child) == 0)
            child = nullptr;
    }

    sead::HeapMgr* heap = *reinterpret_cast<sead::HeapMgr**>(bytes + 0x8);
    if (heap == nullptr)
        heap = sead::HeapMgr_getCurrentHeap();

    sub_029E6C38(
        child,
        *reinterpret_cast<u32*>(bytes + 0x10),
        *reinterpret_cast<u32*>(bytes + 0x14),
        *reinterpret_cast<u32*>(bytes + 0x18),
        heap);
}
