#include <graphics/Mii_CentralMgr.h>

namespace Mii {

CentralMgr* CentralMgr::sInstance = nullptr;

bool CentralMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new CentralMgr();
    return true;
}

void CentralMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

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
        RIO_LOG("Before mShader.initialize()\n");

        mShader.initialize();

        RIO_LOG("Before mShader.setCallback()\n");

      //sead::Graphics::instance()->lockDrawContext();
        {
            mShader.setCallback();
        }
      //sead::Graphics::instance()->unlockDrawContext();

        RIO_LOG("Before mModelGpuInitializer.initialize()\n");

        mModelGpuInitializer.initialize();

        RIO_LOG("Before mIconFacelineShader.initialize()\n");

        mIconFacelineShader.initialize();
    }
    return ret;
}

}
