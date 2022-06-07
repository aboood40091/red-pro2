#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>

class ResMgr
{
    SEAD_SINGLETON_DISPOSER(ResMgr)

public:
    ResMgr();

    void* getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length=NULL);

private:
    static void* getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length);
};
