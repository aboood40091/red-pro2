#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>

#include <agl/light/aglLightMapMgr.h>

class RenderObjEx;

class LightMapMgr : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(LightMapMgr)

public:
    static const u32 cLightMapNum = 2;

public:
    LightMapMgr(const sead::TaskConstructArg& arg);
    virtual ~LightMapMgr();

    void setRenderObjLightMap(RenderObjEx& render_obj, bool no_mat_dl) const;

private:
    u32 _cc[(0x2070 - 0xCC) / sizeof(u32)];
    agl::lght::LightMapMgr mLightMapMgr;
    u32 _4ddc[(0x52C8 - 0x4DDC) / sizeof(u32)];
    bool mIsInitialized;
};
static_assert(sizeof(LightMapMgr) == 0x52CC, "LightMapMgr size mismatch");
