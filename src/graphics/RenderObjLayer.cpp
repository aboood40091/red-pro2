#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>

#include <array>

RenderObjLayer::RenderObjLayer(const char* name, s32 priority)
    : Layer(name, priority)
    , mpRenderMgr(nullptr)
    , mViewIndex(-1)
    , mpCull(nullptr)
{
    mpCamera = nullptr;
    mpProjection = nullptr;
}

void RenderObjLayer::initialize()
{
    static const std::array<const char*, cRenderStep_Num> cRenderStepName = {
        "CalcView",
        "UpdateGPUBuffer",
        "Opa",
        "Xlu",
        "Particle",
        "PostFx"
    };

    for (const char* render_step_name : cRenderStepName)
        addRenderStep(render_step_name);

    addDrawMethodToAll(rio::lyr::DrawMethod(this, &RenderObjLayer::render_));
}

void RenderObjLayer::setRenderMgr(RenderMgr* p_render_mgr)
{
    RIO_ASSERT(p_render_mgr != nullptr);
    mViewIndex = p_render_mgr->createView(this);
    mpRenderMgr = p_render_mgr;
}

void RenderObjLayer::calcView_(const rio::lyr::DrawInfo& draw_info)
{
    if (mpRenderMgr == nullptr)
        return;

    RIO_ASSERT(mViewIndex != -1);
    RIO_ASSERT(camera() != nullptr);
    RIO_ASSERT(projection() != nullptr);

    mpRenderMgr->calcView(mViewIndex, *camera(), *projection(), mpCull);
}

void RenderObjLayer::updateGPUBuffer_(const rio::lyr::DrawInfo& draw_info)
{
    if (mpRenderMgr == nullptr)
        return;

    RIO_ASSERT(mViewIndex != -1);

    mpRenderMgr->calcGPU(mViewIndex);
}

void RenderObjLayer::drawOpa_(const rio::lyr::DrawInfo& draw_info)
{
    if (mpRenderMgr == nullptr)
        return;

    RIO_ASSERT(mViewIndex != -1);

    mpRenderMgr->drawOpa(mViewIndex, draw_info);
}

void RenderObjLayer::drawXlu_(const rio::lyr::DrawInfo& draw_info)
{
    if (mpRenderMgr == nullptr)
        return;

    RIO_ASSERT(mViewIndex != -1);

    mpRenderMgr->drawXlu(mViewIndex, draw_info);
}

void RenderObjLayer::render_(const rio::lyr::DrawInfo& draw_info)
{
    switch(RenderStep(draw_info.render_step_idx))
    {
    case cRenderStep_CalcView:
        calcView_(draw_info);
        break;
    case cRenderStep_UpdateGPUBuffer:
        updateGPUBuffer_(draw_info);
        break;
    case cRenderStep_Opa:
        drawOpa_(draw_info);
        break;
    case cRenderStep_Xlu:
        drawXlu_(draw_info);
        break;
    default:
        break;
    }
}

