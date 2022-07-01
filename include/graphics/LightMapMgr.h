#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>

class RenderObjEx;

class LightMapMgr : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(LightMapMgr)

public:
    LightMapMgr(const sead::TaskConstructArg& arg);
    virtual ~LightMapMgr();

    void setRenderObjLightMap(RenderObjEx& render_obj, bool no_mat_dl) const;

private:
    u8 _cc[0x52CC - 0xCC];
};
static_assert(sizeof(LightMapMgr) == 0x52CC, "LightMapMgr size mismatch");
