#pragma once

#include <math/rio_Matrix.h>
#include <math/rio_Vector.h>

class RenderObjBase
{
public:
    RenderObjBase()
    {
    }

    virtual void calc() = 0;
};

class RenderMgr;

class RenderObj : public RenderObjBase
{
public:
    RenderObj()
        : RenderObjBase()
    {
    }

    virtual void calcGPU(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void updateView(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawOpa(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawXlu(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) = 0;
    virtual void drawShadowOpa(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual void drawReflectionOpa(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual void drawReflectionXlu(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) { }
    virtual bool hasShadow() const { return false; }

protected:
    rio::Vector3f mOrderPos; // I think. Precisely used for z ordering.
};
