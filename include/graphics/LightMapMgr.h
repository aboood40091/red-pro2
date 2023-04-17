#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <lighting/aglLightMapMgr.h>

class ModelNW;

class LightMapMgr : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(LightMapMgr)

public:
    static const u32 cLightMapNum = 2;

public:
    LightMapMgr(const sead::TaskConstructArg& arg);
    virtual ~LightMapMgr();

    agl::lght::LightMapMgr& getLightMapMgr() { return mLightMapMgr; }
    const agl::lght::LightMapMgr& getLightMapMgr() const { return mLightMapMgr; }

    void setModelLightMap(ModelNW* p_model, bool set_mdl_dl_dirty) const;

private:
    u32                     _cc[(0x2070 - 0xCC) / sizeof(u32)];
    agl::lght::LightMapMgr  mLightMapMgr;
    u32                     _4ddc[(0x52C8 - 0x4DDC) / sizeof(u32)];
    bool                    mIsInitialized;
};
static_assert(sizeof(LightMapMgr) == 0x52CC);
