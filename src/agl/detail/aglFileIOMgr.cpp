#include <agl/detail/aglFileIOMgr.h>
#include <agl/detail/aglPrivateResource.h>

#include <prim/seadMemUtil.h>

namespace agl { namespace detail {

FileIOMgr* FileIOMgr::sInstance = NULL;

bool FileIOMgr::showDialog(sead::hostio::FileInfo* p_info, const sead::SafeString& mode, const sead::SafeString& id, const sead::SafeString& filter, const sead::SafeString& filename) const
{
    // SEAD_ASSERT(p_info != nullptr);

    sead::SafeString id_ = (!id.isEqual("")) // Why not use id.isEmpty() ??
                                    ? id
                                    : filter;

    sead::FormatFixedSafeString<1024> arg(
        "FileName = %s, Mode = %s, Id = %s, Filter = %sファイル(*.%s)|*.%s|すべてのファイル(*.*)|*.*",
        filename.cstr(),
        mode.cstr(),
        id_.cstr(),
        filter.cstr(),
        filter.cstr(),
        filter.cstr()
    );

    // Stripped in release build:
    // return sead::hostio::ShowFileDialog(p_info, arg, "");

    return false;
}

bool FileIOMgr::save(const void* p_buf, u32 size, const DialogArg& arg)
{
    bool ret = false;

    // TODO: scoped lock
    mCriticalSection.lock();
    do
    {
        sead::hostio::FileInfo file_info;

        bool use_dialog;

        if (arg.mPath.isEmpty())
        {
            if (!showDialog(&file_info, "Save", arg.mDefaultID, arg.mDefaultFilter, arg.mDefaultFilename))
                break;

            use_dialog = true;
        }
        else
        {
            file_info.path = arg.mPath;
            use_dialog = false;
        }

        sead::FileHandle handle;

        sead::FileDevice* device = mFileDevice->tryOpen(&handle, file_info.path, sead::FileDevice::cFileOpenFlag_WriteOnly, 0);
        if (device)
        {
            u8* temp_buf = new (PrivateResource::instance()->getDebugHeap(), sead::FileDevice::cBufferMinAlignment) u8[size];
            sead::MemUtil::copy(temp_buf, p_buf, size);

            handle.write(temp_buf, size);
            device->close(&handle);

            delete temp_buf; // Nintendo did not use delete[] (fixed in later versions)

            if (arg.mOutPath)
                arg.mOutPath->copy(file_info.path);

            ret = true;
        }
        else
        {
            if (use_dialog)
            {
                // Stripped in release build:
                // sead::hostio::ShowMessageBox(
                //     sead::FormatFixedSafeString<1024>(
                //         "%sの保存に失敗しました。\n保存先のアクセス権を確認して下さい。",
                //         file_info.path.cstr()
                //     ),
                //     "Caption=ファイル保存失敗, Icon=Error",
                //     ""
                // );
            }
        }
        break;
    }
    while (false);
    mCriticalSection.unlock();

    return ret;
}

FileIOMgr::DialogArg::DialogArg()
    : mDefaultFilter()
    , mDefaultFilename()
    , mDefaultID("agl_default")
    , mPath()
    , mOutPath(NULL)
    , mLoadAlignment(0x20) // Why not sead::FileDevice::cBufferMinAlignment is beyond me
{
}

} }
