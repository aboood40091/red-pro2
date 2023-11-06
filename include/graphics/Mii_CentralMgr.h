#pragma once

#include <graphics/Mii_CafeResInitializer.h>
#include <graphics/Mii_ModelGpuInitializer.h>
#include <graphics/Mii_Shader.h>
#include <graphics/Mii_IconFacelineShader.h>

namespace Mii {

class CentralMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static CentralMgr* instance() { return sInstance; }

private:
    static CentralMgr* sInstance;

    CentralMgr();

    ~CentralMgr()
    {
        destroy();
    }

    CentralMgr(const CentralMgr&);
    CentralMgr& operator=(const CentralMgr&);

public:
    bool initialize();
    void destroy();

    ModelGpuInitializer& getModelGpuInitializer()
    {
        return mModelGpuInitializer;
    }

    Shader& getShader()
    {
        return mShader;
    }

    IconFacelineShader& getIconFacelineShader()
    {
        return mIconFacelineShader;
    }

private:
    CafeResInitializer  mResInitializer;
    ModelGpuInitializer mModelGpuInitializer;
    Shader              mShader;
    IconFacelineShader  mIconFacelineShader;
};
//static_assert(sizeof(CentralMgr) == 0x1300);

}
