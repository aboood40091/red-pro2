#pragma once

#include <graphics/Layer.h>

class RenderMgr;

class RenderObjLayerBase : public Layer
{
    SEAD_RTTI_OVERRIDE(RenderObjLayerBase, Layer)

public:
    RenderObjLayerBase();
    virtual ~RenderObjLayerBase();

    s32 getViewIndex() const { return mViewIndex; }

    virtual void setPolygonOffset(s32 polygon_offset) const
    {
    }

    RenderMgr* getRenderMgr() const
    {
        return mpRenderMgr;
    }

    void setRenderMgr(RenderMgr* p_render_mgr);

    // ...

protected:
    RenderMgr*  mpRenderMgr;
    s32         mViewIndex;
    void*       _428;
};
static_assert(sizeof(RenderObjLayerBase) == 0x42C);

class RenderObjLayer : public RenderObjLayerBase
{
public:
    enum RenderStep
    {
        cRenderStep_CalcView = 0,
        cRenderStep_UpdateGPUBuffer,
        cRenderStep_Opa,
        cRenderStep_Xlu,
        cRenderStep_Particle,
        cRenderStep_PostFx,
        cRenderStep_Num
    };
    static_assert(cRenderStep_Num == 6);

public:
    RenderObjLayer();
    virtual ~RenderObjLayer();

    u32 getRenderStepNum() const override { return cRenderStep_Num; }
    void getRenderStepName(sead::SafeString* p_name, s32 idx) const override;
    void initialize(sead::Heap* heap) override;
    bool isRenderStepGPUCalc(s32 idx) override { return idx == cRenderStep_UpdateGPUBuffer; }

    void setPolygonOffset(s32 polygon_offset) const override;

private:
    sead::Matrix44f _42c;
    bool            _46c;
    f32             mPolygonOffsetFactor;
    f32             mPolygonOffsetUnits;
};
static_assert(sizeof(RenderObjLayer) == 0x478);
