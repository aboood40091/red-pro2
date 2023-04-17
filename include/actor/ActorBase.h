#pragma once

#include <system/ID.h>

#include <container/seadOffsetList.h>
#include <heap/seadHeap.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

class Profile;

struct ActorInitArg
{
    u32             param_0;
    u32             param_1;
    u32             parent_id;
    Profile*        profile;
    sead::Vector3f  position;
    u32             angle;
    u8              layer;
    u8              event_id[2];
    u8              _23;                // Unused
    u8              movement_id;
    u8              link_id;
    u8              init_state_flag;
  //u8              _27;                // Unused, padding?
    u8*             _28;

    ActorInitArg()
        : parent_id(0)
        , angle(0)
    {
        initialize();
    }

    void initialize()
    {
        sead::MemUtil::fillZero(this, sizeof(ActorInitArg));
    }
};
static_assert(sizeof(ActorInitArg) == 0x2C);

class ActorBase
{
    SEAD_RTTI_BASE(ActorBase)

public:
    enum MainState
    {
        cState_Cancelled = 0,
        cState_Error,
        cState_Success,
        cState_Waiting
    };

public:
    typedef sead::OffsetList<ActorBase> List;

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

    bool isActive() const
    {
        return mIsActive;
    }

    void requestDelete()
    {
        mRequestDelete = true;
    }

    bool isDeleted() const
    {
        return mRequestDelete;
    }

    ID getID() const
    {
        return mID;
    }

    u32 getProfileID() const;

protected:
    sead::Heap*     mpHeap;
    ID              mID;
    Profile*        mpProfile;
    u8              mLifecycle;     // 0: Wait for create, 1: Active, 2: Delete
    bool            _d;
    bool            mIsActive;
    bool            mRequestDelete;
    u32             mParam0;
    u32             mParam1;
    u8              mMovementID;
    u8              mLinkID;
    u8              mInitStateFlag;
    List            mChildList;
    sead::ListNode  mChildNode;
    ActorBase*      mpParent;
    sead::ListNode  mExecuteNode;
    sead::ListNode  mDrawNode;
    sead::BitFlag32 mFlag;
};
static_assert(sizeof(ActorBase) == 0x50);
