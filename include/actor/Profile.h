#pragma once

#include <actor/ProfileID.h>

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
    static const u32 cNum = ProfileID::cNum;

public:
    enum ResLoadAt
    {
        cResLoadAt_Boot = 0,
        cResLoadAt_Course,
        cResLoadAt_CourseSelect
    };

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

    static s16 getPriority(u32 id);
    static u8 getResLoadAt(u32 id);
    static u8 getResNum(u32 id);
    static const sead::SafeString* getResList(u32 id);

private:
    ClassInit               mpClassInit;
    u32                     mID;
    const ActorCreateInfo*  mpActorCreateInfo;
    bool                    mIsResLoaded;
    u32                     mFlag;

    static sead::SafeArray<Profile*, cNum>  sProfile;

    static const s16                cPriority[cNum];
    static const u8                 cResLoadAt[cNum];
    static const u8                 cResNum[cNum];
    static const sead::SafeString*  cResList[cNum];

/* ----------------------------- Haxx ----------------------------- */

public:
    static u32 getProfileNumAll();

private:
    static const u32 cNumAll = ProfileID::cNumAll;
    static const u32 cNumCustom = cNumAll - cNum;

    static sead::SafeArray<Profile*, cNum>  sProfileCustom;

    static const s16                cPriorityCustom[cNumCustom];
    static const u8                 cResLoadAtCustom[cNumCustom];
    static const u8                 cResNumCustom[cNumCustom];
    static const sead::SafeString*  cResListCustom[cNumCustom];
};
static_assert(sizeof(Profile) == 0x14);
