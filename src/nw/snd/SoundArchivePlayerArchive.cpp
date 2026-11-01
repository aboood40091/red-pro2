constexpr u32 kArchiveLoadGateA = 0x101F9B18u;
constexpr u32 kArchiveLoadGateB = 0x101F9B1Cu;
constexpr u32 kArchiveLoadMessageA = 0x101FBC8u;
constexpr u32 kArchiveLoadMessageB = 0x101FBCCu;
constexpr u32 kArchiveLoadLabelRodata = 0x1019D80Cu;

using ArchiveHolderLoadFn = s32 (*)(void* node);

static s32 invokeArchiveHolderLoad_(void* node)
{
    void* child = *reinterpret_cast<void**>(reinterpret_cast<u8*>(node) + 4);
    u32 vtable = *reinterpret_cast<u32*>(child);
    ArchiveHolderLoadFn load =
        reinterpret_cast<ArchiveHolderLoadFn>(*reinterpret_cast<u32*>(vtable + 0xC));
    return load(node);
}

// Address: 0x029E779C
void* sub_029E779C(void* archive_holder)
{
    if (archive_holder == nullptr)
        return nullptr;

    void* node = *reinterpret_cast<void**>(reinterpret_cast<u8*>(archive_holder) + 0x220);
    if (node == nullptr)
        return nullptr;

    u32 kind = *reinterpret_cast<u32*>(node);
    if (kind < 1)
    {
        if (*reinterpret_cast<u32*>(kArchiveLoadGateA) == 0)
        {
            *reinterpret_cast<u32*>(kArchiveLoadMessageA) = kArchiveLoadLabelRodata;
            *reinterpret_cast<u32*>(kArchiveLoadGateA) = 1;
        }
    }
    else if (kind == 1)
    {
        u32* gate = reinterpret_cast<u32*>(kArchiveLoadGateB);
        if (*gate == 0)
        {
            *reinterpret_cast<u32*>(kArchiveLoadMessageB) = kArchiveLoadLabelRodata;
            *gate = 1;
        }
    }
    else
    {
        return nullptr;
    }

    if (invokeArchiveHolderLoad_(node) == 0)
        return nullptr;

    return reinterpret_cast<u8*>(node) + 8;
}
