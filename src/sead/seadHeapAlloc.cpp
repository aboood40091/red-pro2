namespace sead {

class HeapMgr;

// Address: 0x02A0D554
HeapMgr* HeapMgr_getCurrentHeap();

}

constexpr u32 kDefaultHeapRoot = 0x101F8040u;

// Address: 0x029F18DC
void* sub_029F18DC(void* size_or_null, sead::HeapMgr* heap, u32 alignment)
{
    sead::HeapMgr* active = heap;
    if (active == nullptr)
    {
        active = *reinterpret_cast<sead::HeapMgr**>(kDefaultHeapRoot);
        if (active == nullptr)
            active = sead::HeapMgr_getCurrentHeap();
    }
    if (active == nullptr)
        return nullptr;

    u32 size = reinterpret_cast<u32>(size_or_null);
    u32 vtable = *reinterpret_cast<u32*>(active);
    using AllocFn = void* (*)(sead::HeapMgr*, u32, u32);
    AllocFn alloc = reinterpret_cast<AllocFn>(*reinterpret_cast<u32*>(vtable + 0x34));
    return alloc(active, size, alignment);
}
