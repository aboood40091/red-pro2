constexpr u32 kCourseOwnerSingleton = 0x101EC398u;
constexpr u32 kCourseOwnerSideSlot = 0x101EC39Cu;
constexpr u32 kCourseOwnerVtableRodata = 0x10119C88u;

// Address: 0x029F18DC
void* sub_029F18DC(void* size, sead::HeapMgr* heap, u32 alignment);

// Address: 0x02A0A2FC
void sub_02A0A2FC(void* object);

// Address: 0x02742B20
void sub_02742B20(void* course_owner);

// Address: 0x02742D2C
void sub_02742D2C(u32 arg)
{
    void** singleton = reinterpret_cast<void**>(kCourseOwnerSingleton);
    if (*singleton != nullptr)
        return;

    void* owner = sub_029F18DC(reinterpret_cast<void*>(0x15Cu), nullptr, 4u);
    if (owner == nullptr)
        return;

    sub_02A0A2FC(owner);
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(owner) + 0xC) = kCourseOwnerVtableRodata;
    *reinterpret_cast<void**>(kCourseOwnerSideSlot) = owner;
    *singleton = owner;
    sub_02742B20(owner);
    (void)arg;
}
