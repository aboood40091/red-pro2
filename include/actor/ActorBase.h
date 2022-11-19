#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadHeap.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

class Profile;

struct ActorInitArg
{
    u32 param_1;
    u32 param_2;
    u32 parentId;
    Profile* profile;
    sead::Vector3f position;
    u32 rotation;
    u8 layer;
    u8 eventId1;
    u8 eventId2;
    u8 _23;                     // Unused
    u8 movementId;
    u8 linkId;
    u8 initStateFlag;
    u8 _27;                     // Unused
    u8* _28;
};

class ActorBase
{
    SEAD_RTTI_BASE(ActorBase)

public:
    enum MainState
    {
        cState_Cancelled,
        cState_Error,
        cState_Success,
        cState_Waiting,
    };

public:
    ActorBase(const ActorInitArg& arg);
    virtual ~ActorBase();

    virtual s32 preCreate();
    virtual s32 create();
    virtual void postCreate(MainState state);

    virtual s32 preExecute();
    virtual s32 execute();
    virtual void postExecute(MainState state);
    virtual void finalUpdate();

    virtual s32 preDraw();
    virtual s32 draw();
    virtual void postDraw(MainState state);

    virtual s32 preDelete();
    virtual s32 doDelete();
    virtual void postDelete(MainState state);

    void requestDelete()
    {
        mRequestDelete = true;
    }

protected:
    sead::Heap* mpHeap;
    u32 mID;
    Profile* mpProfile;
    u8 mLifecycle;                      // 0: Wait for create, 1: Active, 2: Delete
    bool _d;
    bool mIsActive;
    bool mRequestDelete;
    u32 mParam1;
    u32 mParam2;
    u8 mMovementID;
    u8 mLinkID;
    u8 mInitStateFlag;
    sead::OffsetList<ActorBase> mChildList;
    sead::ListNode mChildNode;
    ActorBase* mpParent;
    sead::ListNode mExecuteNode;
    sead::ListNode mDrawNode;
    sead::BitFlag32 flags;
};
