#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

class ActorBase;
class ActorInfo;
class ActorInitArg;
class ModelResource;

typedef ActorBase* (*ClassInit)(const ActorInitArg&);

class Profile
{
public:
    static const u32 cNum = 913;

public:
    Profile(ClassInit p_class_init, u32 id, const sead::SafeString& name, const ActorInfo* p_actor_nfo, u32 flag);

    ClassInit getClassInit() const
    {
        return mpClassInit;
    }

    u32 getID() const
    {
        return mID;
    }

    const ActorInfo& getActorInfo() const
    {
        return *mpActorInfo;
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

private:
    ClassInit mpClassInit;
    u32 mID;
    const ActorInfo* mpActorInfo;
    bool mIsResLoaded;
    u32 mFlag;

    static sead::SafeArray<Profile*, cNum> sProfile;
};
