#pragma once

#include <container/seadStrTreeMap.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>
#include <resource/seadSZSDecompressor.h>

class ResMgr
{
    SEAD_SINGLETON_DISPOSER(ResMgr)

private:
    class ResHolder : public sead::IDisposer
    {
    public:
        ResHolder(const sead::SafeString& key, sead::ArchiveRes* archive);

        virtual ~ResHolder()
        {
            ResMgr::instance()->remove(mKey);
        }

    private:
        sead::FixedSafeString<32> mKey;
        sead::ArchiveRes* mpArchiveRes;

        friend class ResMgr;
    };
    static_assert(sizeof(ResHolder) == 0x40);

public:
    ResMgr();

    bool loadArchiveRes(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress);

    sead::ArchiveRes* getArchiveRes(const sead::SafeString& key) const;

    void* getFileFromArchiveRes(const sead::SafeString& key, const sead::SafeString& filename, u32* length = nullptr) const;
    void* getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length = nullptr) const;

private:
    static sead::ArchiveRes* loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap, sead::Decompressor* decompressor);
    static sead::ArchiveRes* loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap);

    static void* getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length);

private:
    sead::ArchiveRes* mpCourseResPack;
    sead::FixedStrTreeMap<32, ResHolder*, 256> mResHolderTreeMap;
    sead::SZSDecompressor* mpSZSDecompressor;
};
static_assert(sizeof(ResMgr) == 0x442C, "ResMgr size mismatch");
