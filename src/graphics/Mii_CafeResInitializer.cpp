#include <graphics/Mii_CafeResInitializer.h>

#include <filedevice/rio_FileDeviceMgr.h>
#include <math/rio_Vector.h>

#include <cafe/os.h>

/*
namespace {

__attribute__((aligned(0x2000)))
static
#include "FFLResMiddle.h"

__attribute__((aligned(0x2000)))
static
#include "FFLResHigh.h"

}
*/

namespace Mii {

const std::string cFFLShaderFilename = "FFLShader.gsh";

CafeResInitializer::CafeResInitializer(bool param)
    : mpFFLShaderData(nullptr)
    , _10(param)
{
}

bool CafeResInitializer::initialize()
{
    FFLInitDesc init_desc;
  //init_desc.pShaderData = nullptr;
  //init_desc.pChangeParams = nullptr;
    init_desc.fontRegion = FFL_FONT_REGION_0;
    init_desc._c = _10;
    init_desc._10 = true;

#if RIO_IS_CAFE
    FSInit();
#endif // RIO_IS_CAFE

    FFLResourceDesc res_desc;
    rio::MemUtil::set(&res_desc, 0, sizeof(FFLResourceDesc));
    {
        std::string resPath;
        resPath.resize(256);
        // Middle
        {
            FFLGetResourcePath(resPath.data(), 256, FFL_RESOURCE_TYPE_MIDDLE, false);

          //if (resPath == "/vol/storage_mlc01/sys/title/0005001b/10056000/content/FFLResMiddle.dat")
            /*
            {
                res_desc.pData[FFL_RESOURCE_TYPE_MIDDLE] = FFLResMiddle;
                res_desc.size[FFL_RESOURCE_TYPE_MIDDLE] = sizeof(FFLResMiddle);
            }
            else
            */
            {
                rio::FileDevice::LoadArg arg;
                arg.path = resPath;
                arg.alignment = 0x2000;

                u8* buffer = rio::FileDeviceMgr::instance()->getNativeFileDevice()->tryLoad(arg);
                if (buffer == nullptr)
                {
                    RIO_LOG("CafeResInitializer::initialize(): NativeFileDevice failed to load: %s\n", resPath.c_str());
                    return false;
                }
                else
                {
                    RIO_LOG("CafeResInitializer::initialize(): NativeFileDevice loaded: %s\n", resPath.c_str());
                }

                res_desc.pData[FFL_RESOURCE_TYPE_MIDDLE] = buffer;
                res_desc.size[FFL_RESOURCE_TYPE_MIDDLE] = arg.read_size;
            }
        }
        // High
        {
            FFLGetResourcePath(resPath.data(), 256, FFL_RESOURCE_TYPE_HIGH, false);

          //if (resPath == "/vol/storage_mlc01/sys/title/0005001b/10056000/content/FFLResHigh.dat")
            /*
            {
                res_desc.pData[FFL_RESOURCE_TYPE_HIGH] = FFLResHigh;
                res_desc.size[FFL_RESOURCE_TYPE_HIGH] = sizeof(FFLResHigh);
            }
            else
            */
            {
                rio::FileDevice::LoadArg arg;
                arg.path = resPath;
                arg.alignment = 0x2000;

                u8* buffer = rio::FileDeviceMgr::instance()->getNativeFileDevice()->tryLoad(arg);
                if (buffer == nullptr)
                {
                    RIO_LOG("CafeResInitializer::initialize(): NativeFileDevice failed to load: %s\n", resPath.c_str());
                    return false;
                }
                else
                {
                    RIO_LOG("CafeResInitializer::initialize(): NativeFileDevice loaded: %s\n", resPath.c_str());
                }

                res_desc.pData[FFL_RESOURCE_TYPE_HIGH] = buffer;
                res_desc.size[FFL_RESOURCE_TYPE_HIGH] = arg.read_size;
            }
        }
    }

    FFLResult result = FFLInitResEx(&init_desc, &res_desc);
    if (result != FFL_RESULT_OK)
    {
        RIO_LOG("CafeResInitializer::initialize(): FFLInitResEx() failed with result: %d\n", (s32)result);
        return false;
    }
    else
    {
        RIO_LOG("CafeResInitializer::initialize(): FFLInitResEx() succeeded\n");
    }

    FFLiEnableSpecialMii(333326543);

    if (!FFLIsAvailable())
    {
        RIO_LOG("CafeResInitializer::initialize(): FFLIsAvailable() failed\n");
        return false;
    }

  //sead::Graphics::instance()->lockDrawContext();
    {
        FFLInitResGPUStep();
    }
  //sead::Graphics::instance()->unlockDrawContext();

    loadFFLShader_();

    return true;
}

void CafeResInitializer::destroy()
{
    unloadFFLShader_();
    FFLExit();
}

bool CafeResInitializer::loadFFLShader_()
{
    rio::FileDevice::LoadArg arg;
    arg.path = cFFLShaderFilename;
    mpFFLShaderData = rio::FileDeviceMgr::instance()->tryLoad(arg);
    return mpFFLShaderData != nullptr;
}

void CafeResInitializer::unloadFFLShader_()
{
    if (mpFFLShaderData != nullptr)
        rio::FileDeviceMgr::instance()->unload(mpFFLShaderData);
}

}
