#include <graphics/Mii_CentralMgr.h>

namespace Mii {

SEAD_SINGLETON_DISPOSER_IMPL(CentralMgr)

CentralMgr::CentralMgr()
    : mResInitializer(false)
{
}

void CentralMgr::destroy()
{
    mResInitializer.destroy();
}

bool CentralMgr::initialize()
{
    bool ret = mResInitializer.initialize();
    if (ret)
    {
        mShader.initialize();

        sead::Graphics::instance()->lockDrawContext();
        {
            mShader.setCallback();
        }
        sead::Graphics::instance()->unlockDrawContext();

        mModelGpuInitializer.initialize();
        mIconFacelineShader.initialize();
        mSlotMgr.initialize();
    }
    return ret;
}

}
