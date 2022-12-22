#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

class ModelResource;

class ModelResourceMgr
{
    SEAD_SINGLETON_DISPOSER(ModelResourceMgr)

public:
    ModelResourceMgr();

    bool loadResFile(const sead::SafeString& key, const sead::SafeString& archive_name, sead::Heap* heap = nullptr);
    ModelResource* getResource(const sead::SafeString& key) const;

private:
    u32 mResTree[0x4414 / sizeof(u32)]; // TreeMap<ModelResource>
    u32 _4424;
};
static_assert(sizeof(ModelResourceMgr) == 0x4428, "ModelResourceMgr size mismatch");
