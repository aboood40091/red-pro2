#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

class ActorBase;
class ActorCreateInfo;
class ActorInitArg;
class ModelResource;

typedef ActorBase* (*ClassInit)(const ActorInitArg&);

class Profile
{
public:
    static const u32 cNum = 913;

public:
    Profile(ClassInit p_class_init, u32 id, const sead::SafeString& name, const ActorCreateInfo* p_create_info, u32 flag);

    ClassInit getClassInit() const
    {
        return mpClassInit;
    }

    u32 getID() const
    {
        return mID;
    }

    const ActorCreateInfo& getActorCreateInfo() const
    {
        return *mpActorCreateInfo;
    }

    bool isResLoaded() const
    {
        return mIsResLoaded;
    }

    u32 getFlag() const
    {
        return mFlag;
    }

    void loadRes(sead::Heap* heap);
    void unloadRes(sead::Heap* heap);
    ModelResource* getRes(u32 index) const;

    static Profile* get(u32 id);

protected:
    ClassInit               mpClassInit;
    u32                     mID;
    const ActorCreateInfo*  mpActorCreateInfo;
    bool                    mIsResLoaded;
    u32                     mFlag;

    static sead::SafeArray<Profile*, cNum>  sProfile;
};
static_assert(sizeof(Profile) == 0x14);
