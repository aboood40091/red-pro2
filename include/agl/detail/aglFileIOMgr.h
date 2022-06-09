#pragma once

#include <container/seadBuffer.h>
#include <filedevice/seadFileDevice.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIODefine.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace agl { namespace detail {

class FileIOMgr
{
    SEAD_SINGLETON_DISPOSER(FileIOMgr)

public:
    struct DialogArg
    {
        DialogArg();

        sead::SafeString mDefaultFilter;
        sead::SafeString mDefaultFilename;
        sead::SafeString mDefaultID;
        sead::SafeString mPath;
        sead::BufferedSafeString* mOutPath;
        u32 _24;
    };
    static_assert(sizeof(DialogArg) == 0x28, "agl::detail::FileIOMgr::DialogArg size mismatch");

public:
    FileIOMgr();
    virtual ~FileIOMgr();

    bool showDialog(sead::hostio::FileInfo* p_info, const sead::SafeString& mode, const sead::SafeString& id, const sead::SafeString& filter, const sead::SafeString& filename) const;
    bool save(const void* p_buf, u32 size, const DialogArg& arg);

private:
    sead::FileDevice* mFileDevice; // CafeHostIOFileDevice*
    sead::Buffer<u16> mBuffer;
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(FileIOMgr) == 0x5C, "agl::detail::FileIOMgr size mismatch");


} }
