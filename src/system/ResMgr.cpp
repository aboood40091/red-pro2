#include <system/ChallengeResCacheMgr.h>
#include <system/ResMgr.h>

#include <filedevice/seadFileDeviceMgr.h>
#include <resource/seadResourceMgr.h>
#include <resource/seadSharcArchiveRes.h>

ResMgr* ResMgr::sInstance = nullptr;

bool ResMgr::loadArchiveRes(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress)
{
    if (ChallengeResCacheMgr::instance() != nullptr)
        if (ChallengeResCacheMgr::instance()->isEnableCacheHeap())
            heap = ChallengeResCacheMgr::instance()->getCacheHeap();

    if (mResHolderTreeMap.find(key))
        return true;

    sead::ArchiveRes* archive;

    if (decompress)
        archive = loadArchiveResImpl_(archive_path, heap, mpSZSDecompressor);
    else
        archive = loadArchiveResImpl_(archive_path, heap);

    if (archive == nullptr)
        return false;

    mResHolderTreeMap.insert(key, new (heap) ResHolder(key, archive));
    return true;
}

sead::ArchiveRes* ResMgr::loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap, sead::Decompressor* decompressor)
{
    sead::DirectResourceFactory<sead::SharcArchiveRes> factory;

    sead::Resource* resource = nullptr;
    sead::FixedSafeString<260> path_no_drive;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->findDeviceFromPath(archive_path, &path_no_drive);
    if (device != nullptr)
    {
        sead::ResourceMgr::LoadArg arg;
        arg.device = device;
        arg.path = path_no_drive;
        arg.instance_heap = heap;
        arg.load_data_heap = heap;
        arg.instance_alignment = 0x2000;
        arg.load_data_alignment = 0x2000;
        arg.factory = &factory;

        resource = sead::ResourceMgr::instance()->tryLoad(arg, "sarc", decompressor);
    }

    if (resource == nullptr)
        return nullptr;

    sead::ArchiveRes* archive = sead::DynamicCast<sead::ArchiveRes>(resource);
    DCFlushRangeNoSync(archive->mRawData, archive->mRawSize);
    return archive;
}

sead::ArchiveRes* ResMgr::loadArchiveResImpl_(const sead::SafeString& archive_path, sead::Heap* heap)
{
    sead::DirectResourceFactory<sead::SharcArchiveRes> factory;

    sead::Resource* resource = nullptr;
    sead::FixedSafeString<260> path_no_drive;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->findDeviceFromPath(archive_path, &path_no_drive);
    if (device != nullptr)
    {
        sead::ResourceMgr::LoadArg arg;
        arg.device = device;
        arg.path = path_no_drive;
        arg.instance_heap = heap;
        arg.load_data_heap = heap;
        arg.instance_alignment = 0x2000;
        arg.load_data_alignment = 0x2000;
        arg.factory = &factory;

        resource = sead::ResourceMgr::instance()->tryLoadWithoutDecomp(arg);
    }

    if (resource == nullptr)
        return nullptr;

    return sead::DynamicCast<sead::ArchiveRes>(resource);
}

void* ResMgr::getFileFromArchiveRes(const sead::SafeString& key, const sead::SafeString& filename, u32* length) const
{
    return getFileFromArchiveResImpl_(getArchiveRes(key), filename, length);
}

void* ResMgr::getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length) const
{
    return getFileFromArchiveResImpl_(archive, filename, length);
}

void* ResMgr::getFileFromArchiveResImpl_(sead::ArchiveRes* archive, const sead::SafeString& filename, u32* length)
{
    return archive->getFile(filename, length);
}

ResMgr::ResHolder::ResHolder(const sead::SafeString& key, sead::ArchiveRes* archive)
    : mpArchiveRes(archive)
{
    mKey = key;
}
