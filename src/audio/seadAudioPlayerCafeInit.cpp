namespace sead {

class HeapMgr;

// Address: 0x02A0D554
HeapMgr* HeapMgr_getCurrentHeap();

}

using AudioChildPrecheckFn = s32 (*)(void*);

// Address: 0x029E6C38
void sub_029E6C38(
    void* child,
    void* player,
    u32 arg10,
    u32 arg14,
    sead::HeapMgr* heap,
    u32 arg18);

constexpr u32 kAudioPlayerInitFlag = 0x101F364Cu;
constexpr u32 kAudioPlayerInitWord = 0x101FBAD4u;
constexpr u32 kAudioPlayerInitValue = 0x1019D9E0u;

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
        self,
        *reinterpret_cast<u32*>(bytes + 0x10),
        *reinterpret_cast<u32*>(bytes + 0x14),
        heap,
        *reinterpret_cast<u32*>(bytes + 0x18));
}
