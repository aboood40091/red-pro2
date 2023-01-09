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

    class CourseResPackHolder : public sead::IDisposer
    {
    public:
        CourseResPackHolder(sead::ArchiveRes* archive);

        virtual ~CourseResPackHolder()
        {
            ResMgr::instance()->mpCourseResPack = nullptr;
        }

    private:
        sead::ArchiveRes* mpArchiveRes;

        friend class ResMgr;
    };
    static_assert(sizeof(CourseResPackHolder) == 0x14);

public:
    ResMgr();

    bool loadCourseResPack(const sead::SafeString& level_name, sead::Heap* heap);

    sead::ArchiveRes* getCourseResPack() const
    {
        return mpCourseResPack;
    }

    void* getFileFromCourseResPack(const sead::SafeString& filename, u32* length = nullptr) const;

    bool loadArchiveRes(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress);

    sead::ArchiveRes* getArchiveRes(const sead::SafeString& key) const;

    void* getFileFromArchiveRes(const sead::SafeString& key, const sead::SafeString& filename, u32* length = nullptr) const;
    void* getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length = nullptr) const;

    void remove(const sead::SafeString& key);

private:
    sead::ArchiveRes* loadCourseResPackImpl_(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress);

    static sead::ArchiveRes* loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap, sead::Decompressor* decompressor);
    static sead::ArchiveRes* loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap);

    static void* getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length);

private:
    sead::ArchiveRes* mpCourseResPack;
    sead::FixedStrTreeMap<32, ResHolder*, 256> mResHolderTreeMap;
    sead::SZSDecompressor* mpSZSDecompressor;
};
static_assert(sizeof(ResMgr) == 0x442C, "ResMgr size mismatch");
