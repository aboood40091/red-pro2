#pragma once

#include <graphics/Layer.h>

class RenderMgr;

class RenderObjBaseLayer : public Layer
{
    SEAD_RTTI_OVERRIDE(RenderObjBaseLayer, Layer)

public:
    RenderObjBaseLayer();
    virtual ~RenderObjBaseLayer();

    s32 getViewIndex() const { return mViewIndex; }

    virtual void setPolygonOffset(s32 polygon_offset) const
    {
    }

    void setRenderMgr(RenderMgr* p_render_mgr);

    // ...

protected:
    RenderMgr* mpRenderMgr;
    s32 mViewIndex;
    void* _428;
};
static_assert(sizeof(RenderObjBaseLayer) == 0x42C, "RenderObjBaseLayer size mismatch");
