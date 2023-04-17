#pragma once

#include <heap/seadDisposer.h>
#include <filedevice/cafe/seadCafeFSAFileDeviceCafe.h>

class RDashMgr
{
    SEAD_SINGLETON_DISPOSER(RDashMgr)

public:
    RDashMgr();

    bool isNSLU() const { return mIsNSLU; }

private:
    bool                        mIsDrivePresent;
    bool                        mIsNSLU;
    sead::CafeFSAFileDevice*    mpFileDevice;
};
static_assert(sizeof(RDashMgr) == 0x18);
