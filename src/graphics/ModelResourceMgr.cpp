#include <graphics/ModelResource.h>
#include <graphics/ModelResourceMgr.h>

ModelResourceMgr* ModelResourceMgr::sInstance = nullptr;

bool ModelResourceMgr::loadResFile(const sead::SafeString& key, const sead::SafeString& archive_name, sead::Heap* heap)
{
    if (getResource(key) != nullptr)
        return false;

    ModelResource* p_mdl_res = new (heap) ModelResource();
    if (p_mdl_res == nullptr)
        return false;

    p_mdl_res->load(archive_name, heap);

    mResHolderTreeMap.insert(key, new (heap) ModelResourceHolder(key, p_mdl_res));
    return true;
}

ModelResource* ModelResourceMgr::getResource(const sead::SafeString& key) const
{
    ModelResourceHolder** holder = mResHolderTreeMap.find(key);
    if (!holder)
        return nullptr;

    return (*holder)->mpModelResource;
}

ModelResourceMgr::ModelResourceHolder::ModelResourceHolder(const sead::SafeString& key, ModelResource* p_mdl_res)
    : mpModelResource(p_mdl_res)
{
    mKey = key;
}
