#include <graphics/RenderMgr.h>
#include <graphics/RenderObj.h>

#include <algorithm>

RenderMgr::RenderMgr()
    : mpCallback(nullptr)
    , mShadowMap(nullptr)
    , mReflectionMap(nullptr)
{
}

RenderMgr::~RenderMgr()
{
}

void RenderMgr::clear()
{
    mRenderObj.clear();
    mRenderObjOpa.clear();
    mRenderObjXlu.clear();
  //mRenderObjShadow.clear();
}

void RenderMgr::calc()
{
    // RenderObj calc is done using multi-threading in vanilla NSMBU

    for (RenderObj* obj : mRenderObj)
        obj->calc();
}

void RenderMgr::calcView(s32 view_index, const rio::Camera& camera, const rio::Projection& projection, const CullViewFrustum* p_cull)
{
    ViewInfo& view_info = getViewInfo(view_index);
    camera.getMatrix(&view_info.view_mtx);
    view_info.proj_mtx = static_cast<const rio::Matrix44f&>(projection.getMatrix());
  //view_info._74 = param_4;
    view_info.p_cull = p_cull;
  //view_info._7c = param_6;

    for (RenderObj* obj : mRenderObj)
        obj->updateView(view_index, view_info.view_mtx, view_info.proj_mtx, this);

    std::sort(mRenderObjXlu.begin(), mRenderObjXlu.end(), [](const RenderObj* a, const RenderObj* b)
    {
       return a->getOrderPos().z < b->getOrderPos().z;
    });
}

void RenderMgr::calcGPU(s32 view_index)
{
    ViewInfo& view_info = getViewInfo(view_index);

    mModelEnvView.setUniformData(view_index, view_info.view_mtx, view_info.proj_mtx);

    for (RenderObj* obj : mRenderObj)
        obj->calcGPU(view_index, view_info.view_mtx, view_info.proj_mtx, this);
}

void RenderMgr::drawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    if (mpCallback)
        mpCallback->preDrawOpa(view_index, draw_info);

    for (RenderObj* obj : mRenderObjOpa)
        obj->drawOpa(view_index, view_info.view_mtx, view_info.proj_mtx, this);

    if (mpCallback)
        mpCallback->postDrawOpa(view_index, draw_info);
}

void RenderMgr::drawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    if (mpCallback)
        mpCallback->preDrawXlu(view_index, draw_info);

    for (RenderObj* obj : mRenderObjXlu)
        obj->drawXlu(view_index, view_info.view_mtx, view_info.proj_mtx, this);

    if (mpCallback)
        mpCallback->postDrawXlu(view_index, draw_info);
}

void RenderMgr::pushBackRenderObj(RenderObj* obj, bool draw_opa, bool draw_xlu)
{
    mRenderObj.push_back(obj);

    if (draw_opa)
        mRenderObjOpa.push_back(obj);

    if (draw_xlu)
        mRenderObjXlu.push_back(obj);

  //if (obj->hasShadow())
  //    mRenderObjShadow.push_back(obj);
}

void RenderMgr::pushBackRenderObj(RenderObj* obj, bool draw_opa, bool draw_xlu, const rio::Vector3f& order_pos)
{
    obj->getOrderPos() = order_pos;
    pushBackRenderObj(obj, draw_opa, draw_xlu);
}

s32 RenderMgr::createView(RenderObjLayer* p_layer)
{
    s32 view_index = mViewInfo.size();
    ViewInfo& view_info = mViewInfo.emplace_back();
    view_info.p_layer = p_layer;
    mModelEnvView.addView();
    RIO_ASSERT(u32(mModelEnvView.getViewNum()) == mViewInfo.size());
    return view_index;
}
