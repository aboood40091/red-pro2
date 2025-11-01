#include <system/ChallengeResCacheMgr.h>
#include <system/RDashMgr.h>
#include <system/ResMgr.h>

#include <filedevice/seadArchiveFileDevice.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <resource/seadResourceMgr.h>
#include <resource/seadSharcArchiveRes.h>

ResMgr* ResMgr::sInstance = nullptr;

bool ResMgr::loadCourseResPack(const sead::SafeString& level_name, sead::Heap* heap)
{
    if (ChallengeResCacheMgr::instance() != nullptr)
    {
        if (mpCourseArchiveRes != nullptr)
            return true;

        if (ChallengeResCacheMgr::instance()->isEnableCacheHeap())
            heap = ChallengeResCacheMgr::instance()->getCacheHeap();
    }

    sead::FormatFixedSafeString<128> archive_path("");

    if (RDashMgr::instance()->isNSLU())
        archive_path.append("rdash://");

    archive_path.appendWithFormat("course_res_pack/%s.szs", level_name.cstr());

    mpCourseArchiveRes = loadCourseResPackImpl_(level_name, archive_path, heap, true);
    if (mpCourseArchiveRes == nullptr)
        return false;

    new (heap) CourseArchiveResHolder(mpCourseArchiveRes);

    return true;
}

sead::ArchiveRes* ResMgr::loadCourseResPackImpl_(const sead::SafeString& level_name, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress)
{
    sead::ArchiveRes* archive;

    if (decompress)
        archive = loadArchiveResImpl_(archive_path, heap, mpSZSDecompressor);
    else
        archive = loadArchiveResImpl_(archive_path, heap);

    sead::ArchiveFileDevice device(archive);
    sead::DirectResourceFactory<sead::SharcArchiveRes> factory;
    sead::DirectoryHandle handle;
    sead::DirectoryEntry entry;
    sead::ResourceMgr::LoadArg arg;

    device.tryOpenDirectory(&handle, "");

    while (true)
    {
        u32 read_num = 0;
        device.tryReadDirectory(&read_num, &handle, &entry, 1);
        if (read_num == 0)
            break;

        if (isArchiveResLoaded(entry.name))
            continue;

        arg.device = &device;
        arg.path = entry.name;
        arg.instance_heap = heap;
        arg.instance_alignment = 0x2000;
        arg.load_data_alignment = 0x2000;
        arg.factory = &factory;

        sead::Resource* resource = sead::ResourceMgr::instance()->tryLoadWithoutDecomp(arg);
        sead::ArchiveRes* inner_arc = sead::DynamicCast<sead::ArchiveRes>(resource);

        if (entry.name == level_name)
            archive = inner_arc;

        else
            mResHolderTreeMap.insert(entry.name, new (heap) ResHolder(entry.name, inner_arc));
    }

    device.tryCloseDirectory(&handle);
    return archive;
}

bool ResMgr::loadArchiveRes(const sead::SafeString& key, const sead::SafeString& archive_path, sead::Heap* heap, bool decompress)
{
    if (ChallengeResCacheMgr::instance() != nullptr)
        if (ChallengeResCacheMgr::instance()->isEnableCacheHeap())
            heap = ChallengeResCacheMgr::instance()->getCacheHeap();

    if (mResHolderTreeMap.contains(key))
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
    DCFlushRangeNoSync(archive->getData(), archive->getSize());
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

bool ResMgr::isArchiveResLoaded(const sead::SafeString& key) const
{
    return mResHolderTreeMap.contains(key);
}

sead::ArchiveRes* ResMgr::getArchiveRes(const sead::SafeString& key) const
{
    ResHolder** holder = mResHolderTreeMap.find(key);
    if (!holder)
        return nullptr;

    return (*holder)->mpArchiveRes;
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
    sead::ArchiveRes::FileInfo file_info;
    void* data = archive->getFile(filename, &file_info);
    if (data && length)
        *length = file_info.getLength();

    return data;
}

bool ResMgr::unload(const sead::SafeString& key)
{
    ResHolder** holder = mResHolderTreeMap.find(key);
    if (!holder)
        return false;

    delete (*holder)->mpArchiveRes;
    delete (*holder);
    return true;
}

void ResMgr::remove(const sead::SafeString& key)
{
    if (mResHolderTreeMap.contains(key))
        mResHolderTreeMap.erase(key);
}

ResMgr::ResHolder::ResHolder(const sead::SafeString& key, sead::ArchiveRes* archive)
    : mpArchiveRes(archive)
{
    mKey = key;
}

ResMgr::CourseArchiveResHolder::CourseArchiveResHolder(sead::ArchiveRes* archive)
    : mpArchiveRes(archive)
{
}
