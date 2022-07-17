#pragma once

#include <container/seadBuffer.h>
#include <gfx/seadCamera.h>
#include <gfx/seadColor.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

namespace agl { namespace lyr {

class DrawMethod;
class Renderer;
class RenderInfo;
class RenderStep;

// TODO
enum DisplayType
{
};

class Layer : public sead::IDisposer
{
public:
    Layer();
    virtual ~Layer();

    SEAD_RTTI_BASE(Layer)

    virtual u32 getRenderStepNum() const = 0;
    virtual void getRenderStepName(sead::SafeString* p_name, s32 idx) const = 0;
    virtual void doInitialize(sead::Heap* heap) { }
    virtual void vf3C() { }
    virtual void preDrawImpl(const RenderInfo& render_info) const { }
    virtual void postDrawImpl(const RenderInfo& render_info) const { }
    virtual u32 vf54() { return 0; }
    virtual u32 vf5C() { return 0; }

    DrawMethod* pushBackDrawMethod(u32 render_step, DrawMethod* p_draw_method);
    DrawMethod* pushBackDrawMethod(DrawMethod* p_draw_method);
    // ...

protected:
    Renderer* mpRenderer;
    sead::Viewport mViewport;
    sead::Viewport mScissor; // I think
    sead::Camera* mpCamera;
    sead::Projection* mpProjection;
    sead::BitFlag32 _4c;
    sead::BitFlag32 _50;
    DisplayType mDisplayType;
    u32 mRenderDisplayFlag;
    u32 mDisplayType2; // ... ?
    sead::BitFlag32 mFlag;
    s32 mIndex;
    u32 _68;
    sead::Color4f mClearColor;
    f32 mClearDepth;
    sead::Buffer<RenderStep> mRenderStep;
    u32 _88;
    u32 mDebugInfo[0x390 / sizeof(u32)]; // TODO: agl::lyr::Layer::DebugInfo
};
static_assert(sizeof(Layer) == 0x41C, "agl::lyr::Layer size mismatch");

} }
