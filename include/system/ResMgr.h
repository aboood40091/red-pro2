#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>

class ResMgr
{
    SEAD_SINGLETON_DISPOSER(ResMgr)

public:
    ResMgr();

    bool loadArchiveRes(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress);

    sead::ArchiveRes* getArchiveRes(const sead::SafeString& key) const;

    void* getFileFromArchiveRes(const sead::SafeString& key, const sead::SafeString& filename, u32* length = nullptr) const;
    void* getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length = nullptr) const;

private:
    static void* getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length);
};
