#include <graphics/Mii_CafeResInitializer.h>
#include <system/MainGame.h>

#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/cafe/seadCafeFSAFileDeviceCafe.h>
#include <gfx/seadGraphics.h>
#include <heap/seadExpHeap.h>
#include <heap/seadFrameHeap.h>
#include <math/seadVector.h>

namespace Mii {

// Unused
const sead::Vector3f cUnk(0.0f, 0.0f, 0.0f);

// Unused
const sead::SafeString cFFLResFilename       = "FFLRes.dat";
const sead::SafeString cFFLResLowFilename    = "FFLResLow.dat";
const sead::SafeString cFFLResMiddleFilename = "FFLResMiddle.dat";
const sead::SafeString cFFLResHighFilename   = "FFLResHigh.dat";

const sead::SafeString cFFLShaderFilename = "FFLShader.gsh";

CafeResInitializer::CafeResInitializer(bool param)
    : mpWorkMemory(nullptr)
    , mpWorkMemoryHeap(nullptr)
    , mpGraphicsHeap(nullptr)
    , mpFFLShaderData(nullptr)
    , _10(param)
{
}

bool CafeResInitializer::initialize()
{
    FFLInitDesc init_desc;
    init_desc.pShaderData = nullptr;
    init_desc.pChangeParams = nullptr;
    init_desc.fontRegion = FFL_FONT_REGION_0;
    init_desc._c = _10;
    init_desc._10 = true;
    if (!createHeaps_(&init_desc))
        return false;

    FSInit();

    FFLResourceDesc res_desc;
    sead::MemUtil::fillZero(&res_desc, sizeof(FFLResourceDesc));
    {
        sead::CafeFSNativePathFileDevice device;

        sead::FixedSafeString<256> resPath;
        // Middle
        {
            FFLGetResourcePath(resPath.getBuffer(), 256, FFL_RESOURCE_TYPE_MIDDLE, false);

            sead::FileDevice::LoadArg arg;
            arg.path = resPath;
            arg.alignment = 0x2000;

            u8* buffer = device.tryLoad(arg);
            if (buffer == nullptr)
                return false;

            res_desc.pData[FFL_RESOURCE_TYPE_MIDDLE] = buffer;
            res_desc.size[FFL_RESOURCE_TYPE_MIDDLE] = arg.buffer_size;
        }
        // High
        {
            FFLGetResourcePath(resPath.getBuffer(), 256, FFL_RESOURCE_TYPE_HIGH, false);

            sead::FileDevice::LoadArg arg;
            arg.path = resPath;
            arg.alignment = 0x2000;

            u8* buffer = device.tryLoad(arg);
            if (buffer == nullptr)
                return false;

            res_desc.pData[FFL_RESOURCE_TYPE_HIGH] = buffer;
            res_desc.size[FFL_RESOURCE_TYPE_HIGH] = arg.buffer_size;
        }
    }

    FFLInitResEx(mpWorkMemory, &init_desc, &res_desc);
    FFLiEnableSpecialMii(333326543);
    if (!FFLIsAvailable())
        return false;

    sead::Graphics::instance()->lockDrawContext();
    {
        FFLInitResGPUStep();
    }
    sead::Graphics::instance()->unlockDrawContext();

    loadFFLShader_();

    MainGame::instance()->initMiiIconRenderBuffer();

    return true;
}

void CafeResInitializer::destroy()
{
    unloadFFLShader_();
    destroyHeaps_();
    FFLExit();
}

bool CafeResInitializer::createHeaps_(const FFLInitDesc* p_init_desc)
{
    mpGraphicsHeap = sead::ExpHeap::tryCreate(0x300000, "Mii Graphics Heap");   // 3 MB
    if (!mpGraphicsHeap)
        return false;

    mpWorkMemoryHeap = sead::FrameHeap::tryCreate(0, "MiiWorkMemory");
    if (!mpWorkMemoryHeap)
        return false;

    mpWorkMemory = mpWorkMemoryHeap->tryAlloc(FFLGetWorkSize(p_init_desc), PPC_IO_BUFFER_ALIGN);
    if (!mpWorkMemory)
        return false;

    mpWorkMemoryHeap->adjust();
    return true;
}

void CafeResInitializer::destroyHeaps_()
{
    if (mpWorkMemoryHeap != nullptr)
    {
        mpWorkMemoryHeap->destroy();
        mpWorkMemoryHeap = nullptr;
    }
    if (mpGraphicsHeap != nullptr)
    {
        mpGraphicsHeap->destroy();
        mpGraphicsHeap = nullptr;
    }
}

bool CafeResInitializer::loadFFLShader_()
{
    sead::FileDevice::LoadArg arg;
    arg.path = cFFLShaderFilename;
    mpFFLShaderData = sead::FileDeviceMgr::instance()->tryLoad(arg);
    return mpFFLShaderData != nullptr;
}

void CafeResInitializer::unloadFFLShader_()
{
    if (mpFFLShaderData != nullptr)
        sead::FileDeviceMgr::instance()->unload(mpFFLShaderData);
}

}
