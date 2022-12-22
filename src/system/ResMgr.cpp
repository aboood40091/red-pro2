#include <system/ResMgr.h>

ResMgr* ResMgr::sInstance = nullptr;

void* ResMgr::getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length)
{
    return getFileFromArchiveResImpl_(archive, filename, length);
}

void* ResMgr::getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length)
{
    return archive->getFile(filename, length);
}
