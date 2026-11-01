namespace sead {

class TaskMgr;
class MethodTreeNode;

namespace {

// Address: 0x029FF618
void MethodTreeNode_call_(MethodTreeNode* node);

// Address: 0x02A18F20
void sub_02A18F20(void* cs);

// Address: 0x02A18F28
bool sub_02A18F28(TaskMgr* task_mgr);

// Address: 0x02A18F54
void sub_02A18F54(TaskMgr* task_mgr);

// Address: 0x02A0167C
bool sub_02A0167C(TaskMgr* task_mgr, void* destroyable);

// Address: 0x02A0099C
void sub_02A0099C(TaskMgr* task_mgr, void* destroyable, s32 reason);

// Address: 0x02A00CA4
void sub_02A00CA4(TaskMgr* task_mgr, void* entry);

// Address: 0x029F24DC
void sub_029F24DC(void* obj);

using TaskFn = void (*)(void*);

} // namespace

// Address: 0x02A01730
void TaskMgr_afterCalc_(TaskMgr* task_mgr)
{
    MethodTreeNode* destruction_node =
        reinterpret_cast<MethodTreeNode*>(reinterpret_cast<u8*>(task_mgr) + 0x14C);
    MethodTreeNode_call_(destruction_node);

    if (!sub_02A18F28(task_mgr))
        return;

    u8* bytes = reinterpret_cast<u8*>(task_mgr);
    u32* destroy_head = reinterpret_cast<u32*>(bytes + 0x64);
    u32 destroy_end = reinterpret_cast<u32>(bytes + 0x60);

    u32 link = *destroy_head;
    while (link != destroy_end)
    {
        void* destroyable = *reinterpret_cast<void**>(link + 0x8);
        u32 vtable = *reinterpret_cast<u32*>(destroyable);
        u32 dtor_flags = *reinterpret_cast<u32*>(vtable + 0x30);
        link = *reinterpret_cast<u32*>(link + 0x4);

        if ((dtor_flags & 1) == 0)
            continue;

        if (!sub_02A0167C(task_mgr, destroyable))
            continue;

        sub_02A0099C(task_mgr, destroyable, 6);
    }

    u32* pending_head = reinterpret_cast<u32*>(bytes + 0x88);
    u32 pending_end = reinterpret_cast<u32>(bytes + 0x84);

    link = *pending_head;
    while (link != pending_end)
    {
        void* entry = *reinterpret_cast<void**>(link + 0x8);
        void* inner = *reinterpret_cast<void**>(reinterpret_cast<u8*>(entry) + 0x70);

        TaskFn pre = reinterpret_cast<TaskFn>(*reinterpret_cast<u32*>(*reinterpret_cast<u32*>(inner) + 0x8C));
        pre(entry);

        TaskFn post = reinterpret_cast<TaskFn>(*reinterpret_cast<u32*>(*reinterpret_cast<u32*>(inner) + 0x94));
        post(entry);

        sub_029F24DC(entry);
        sub_02A00CA4(task_mgr, entry);

        link = *reinterpret_cast<u32*>(link + 0x4);
    }

    sub_02A18F54(task_mgr);
}

// Address: 0x02A0183C
void TaskMgr_afterCalc_thunk_(TaskMgr* task_mgr)
{
    TaskMgr_afterCalc_(task_mgr);
}

} // namespace sead
