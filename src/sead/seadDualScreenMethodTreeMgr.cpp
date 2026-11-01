namespace sead {

class DualScreenMethodTreeMgr;
class MethodTreeNode;

namespace {

// Address: 0x029FF618
void MethodTreeNode_call_(MethodTreeNode* node);

} // namespace

// Address: 0x029FD944
void DualScreenMethodTreeMgr_drawTop_(DualScreenMethodTreeMgr* self)
{
    MethodTreeNode* node = reinterpret_cast<MethodTreeNode*>(reinterpret_cast<u8*>(self) + 0x13C);
    MethodTreeNode_call_(node);
}

// Address: 0x029FD94C
void DualScreenMethodTreeMgr_drawBtm_(DualScreenMethodTreeMgr* self)
{
    MethodTreeNode* node = reinterpret_cast<MethodTreeNode*>(reinterpret_cast<u8*>(self) + 0x28C);
    MethodTreeNode_call_(node);
}

// Address: 0x029FD93C
void DualScreenMethodTreeMgr_calc_(DualScreenMethodTreeMgr* self)
{
    MethodTreeNode* node = reinterpret_cast<MethodTreeNode*>(reinterpret_cast<u8*>(self) + 0x40);
    MethodTreeNode_call_(node);
}

} // namespace sead
