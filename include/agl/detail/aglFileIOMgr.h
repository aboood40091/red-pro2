#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
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

        sead::SafeString _0;
        sead::SafeString _8;
        sead::SafeString _10;
        sead::SafeString mSavePath;
        u32 _20;
        u32 _24;
    };
    static_assert(sizeof(DialogArg) == 0x28, "agl::detail::FileIOMgr::DialogArg size mismatch");

public:
    FileIOMgr();
    virtual ~FileIOMgr();

    bool save(const void* p_buf, u32 size, const DialogArg& arg);

private:
    void* mFileDevice; // sead::CafeHostIOFileDevice*
    sead::Buffer<u16> _14;
    sead::CriticalSection mCriticalSection;
};
static_assert(sizeof(FileIOMgr) == 0x5C, "agl::detail::FileIOMgr size mismatch");


} }
