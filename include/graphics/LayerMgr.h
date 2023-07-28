#pragma once

#include <framework/seadTaskMgr.h>

class RenderMgr;

class LayerMgr : public sead::TaskBase
{
    SEAD_TASK_SINGLETON_DISPOSER(LayerMgr)

public:
    enum Layer
    {
        cLayer_Gather = 0,
        cLayer_Capture,
        cLayer_ReflectionLightMap,
        cLayer_Reflection_User,
        cLayer_LightMap,
        cLayer_User_0,
        cLayer_User_1,
        cLayer_User_2,
        cLayer_User_3,
        cLayer_User_4,
        cLayer_User_5,
        cLayer_User_6,
        cLayer_User_7,
        cLayer_User_8,
        cLayer_System,
        cLayer_15,                      // Unknown
        cLayer_16,                      // Unknown
        cLayer_Fader,
        cLayer_DRCMode,
        cLayer_DebugDraw,
        cLayer_ReflectionLightMap_DRC,
        cLayer_Reflection_User_DRC,
        cLayer_LightMap_DRC,
        cLayer_DRC_User_0,
        cLayer_DRC_User_1,
        cLayer_DRC_User_2,
        cLayer_DRC_User_3,
        cLayer_DRC_User_4,
        cLayer_System_DRC,
        cLayer_Fader_DRC,
        cLayer_DebugDraw_DRC,
        cLayer_Num
    };
    static_assert(cLayer_Num == 31);

public:
    LayerMgr(const sead::TaskConstructArg& arg);

    // TODO
    // virtual ...

    void removeRenderMgr(RenderMgr* p_render_mgr);
};
