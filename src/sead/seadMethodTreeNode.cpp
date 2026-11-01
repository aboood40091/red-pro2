namespace sead {

class MethodTreeNode;

namespace {

// Address: 0x029FF410
void sub_029FF410(MethodTreeNode* node);

// Address: 0x029FF420
void sub_029FF420(MethodTreeNode* node);

} // namespace

// Address: 0x029FF588
void MethodTreeNode_callRecursive_(MethodTreeNode* node)
{
    u32 pause = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(node) + 0x44);
    if ((pause & 1) == 0)
    {
        u32 delegate_obj = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(node) + 0x2C);
        u32 vtable = *reinterpret_cast<u32*>(delegate_obj);
        using DelegateFn = void (*)(u8*);
        DelegateFn fn = reinterpret_cast<DelegateFn>(*reinterpret_cast<u32*>(vtable + 0xC));
        fn(reinterpret_cast<u8*>(node) + 0x2C);
    }

    u32 child_link = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(node) + 0x4);
    if (child_link == 0)
        return;

    if ((pause & 1) != 0)
        return;

    u32 link = child_link;
    while (link != 0)
    {
        u32 child = *reinterpret_cast<u32*>(link + 0x10);
        MethodTreeNode_callRecursive_(reinterpret_cast<MethodTreeNode*>(child));
        link = *reinterpret_cast<u32*>(child + 0x8);
    }
}

// Address: 0x029FF618
void MethodTreeNode_call_(MethodTreeNode* node)
{
    sub_029FF410(node);
    MethodTreeNode_callRecursive_(node);
    sub_029FF420(node);
}

} // namespace sead
