#pragma once

#include <graphics/Layer.h>

class RenderMgr;

class RenderObjBaseLayer : public Layer
{
    // SEAD_RTTI_OVERRIDE(RenderObjBaseLayer, Layer)

public:
    s32 getViewIndex() const { return mViewIndex; }

protected:
    RenderMgr* mRenderer;
    s32 mViewIndex;
    void* _428;
};
static_assert(sizeof(RenderObjBaseLayer) == 0x42C, "RenderObjBaseLayer size mismatch");
