#include <actor/Profile.h>
#include <graphics/ModelResourceMgr.h>
#include <system/ResMgr.h>

Profile::Profile(ActorFactory factory, s32 id, const sead::SafeString& name, const ActorCreateInfo* p_create_info, Flag flag)
    : mFactory(factory)
    , mID(id)
    , mpActorCreateInfo(p_create_info != nullptr ? p_create_info : &ActorCreateInfo::cDefault)
    , mIsResLoaded(false)
    , mFlag(flag)
{
    sProfileList[mID] = this;
}

void Profile::loadResource(sead::Heap* heap)
{
    if (!mIsResLoaded)
    {
        const sead::SafeString* res = ProfileInfo::getResList(mID);
        if (res != nullptr)
        {
            for (s32 num = ProfileInfo::getResNum(mID); num != 0; --num)
            {
                ResMgr::instance()->loadArchiveRes(
                    *res, sead::FormatFixedSafeString<260>("actor/%s.szs", res->cstr()), heap, true
                );
                ModelResourceMgr::instance()->loadResFile(*res, *res, heap);
                res++;
            }
        }
        mIsResLoaded = true;
    }
}

void Profile::unloadResource(sead::Heap* heap)
{
    if (mIsResLoaded)
    {
        mIsResLoaded = false;
    }
}

ModelResource* Profile::getResource(u32 index) const
{
    const sead::SafeString* res = ProfileInfo::getResList(mID);
    if (res != nullptr && index < ProfileInfo::getResNum(mID))
        return ModelResourceMgr::instance()->getResource(res[index]);

    return nullptr;
}

Profile* Profile::get(s32 id)
{
    return sProfileList[id];
}

// -------------------------------------------------------------------------------------------- //

sead::SafeArray<Profile*, ProfileInfo::cProfileID_Max> Profile::sProfileList;
