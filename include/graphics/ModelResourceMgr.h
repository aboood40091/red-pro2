#pragma once

#include <container/seadStrTreeMap.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

class ModelResource;

class ModelResourceMgr
{
    SEAD_SINGLETON_DISPOSER(ModelResourceMgr)

private:
    class ModelResourceHolder : public sead::IDisposer
    {
    public:
        ModelResourceHolder(const sead::SafeString& key, ModelResource* p_mdl_res);

        virtual ~ModelResourceHolder()
        {
            if (ModelResourceMgr::instance() != nullptr)
                ModelResourceMgr::instance()->remove(mKey);
        }

    private:
        sead::FixedSafeString<32>   mKey;
        ModelResource*              mpModelResource;

        friend class ModelResourceMgr;
    };
    static_assert(sizeof(ModelResourceHolder) == 0x40);

public:
    ModelResourceMgr();

    bool loadResFile(const sead::SafeString& key, const sead::SafeString& archive_name, sead::Heap* heap = nullptr);
    ModelResource* getResource(const sead::SafeString& key) const;

    void remove(const sead::SafeString& key);

private:
    sead::FixedStrTreeMap<32, ModelResourceHolder*, 256>    mResHolderTreeMap;
    u32                                                     _4424;
};
static_assert(sizeof(ModelResourceMgr) == 0x4428);
