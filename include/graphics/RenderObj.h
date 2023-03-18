#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

class RenderObjBase
{
    SEAD_RTTI_BASE(RenderObjBase)

public:
    RenderObjBase()
    {
    }

    virtual void calc() = 0;
};
static_assert(sizeof(RenderObjBase) == 4);

class RenderMgr;

class RenderObj : public RenderObjBase
{
    SEAD_RTTI_OVERRIDE(RenderObj, RenderObjBase)

public:
    RenderObj()
        : RenderObjBase()
    {
    }

    virtual void calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void updateView(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawShadowOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual void drawReflectionOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual void drawReflectionXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual bool hasShadow() const { return false; }

protected:
    sead::Vector3f  mOrderPos; // I think. Precisely used for z ordering.
};
static_assert(sizeof(RenderObj) == 0x10);
