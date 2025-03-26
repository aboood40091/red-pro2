#include <graphics/LayerMgr.h>
#include <graphics/Model.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObj.h>

#include <common/aglRenderBuffer.h>
#include <gfx/seadViewport.h>

RenderMgr::RenderMgr(const sead::SafeString& name)
    : sead::INamable(name)
    , _18(false)
    , mpCallback(nullptr)
    , mDrawShadow(false)
    , mpShadowMap(nullptr)
    , mpReflectionMap(nullptr)
{
}

RenderMgr::~RenderMgr()
{
    LayerMgr::instance()->removeRenderMgr(this);
}

bool RenderMgr::isFull() const
{
    return mRenderObj.isFull();
}

void RenderMgr::updateEnvObjMgr()
{
    mEnvObjMgr.update();
}

void RenderMgr::clear()
{
    mRenderObj.clear();

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr = mRenderObjOpa.begin(), itr_end = mRenderObjOpa.end(); itr != itr_end; ++itr)
        itr->clear();

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr = mRenderObjXlu.begin(), itr_end = mRenderObjXlu.end(); itr != itr_end; ++itr)
        itr->clear();

    mRenderObjShadow.clear();

    _18 = false;
}

int RenderMgr::compare_(const RenderObj* a, const RenderObj* b)
{
    f32 z = a->getOrderPos().z - b->getOrderPos().z;
    if (z < 0)
        return -1;

    return z > 0;
}

void RenderMgr::calcView(s32 view_index, const sead::Camera& camera, const sead::Projection& projection, const sead::Matrix44f* p_depth_shadow_mtx, const CullViewFrustum* p_cull, void* param_6)
{
    ViewInfo& view_info = getViewInfo(view_index);
    view_info.view_mtx = camera.getViewMatrix();
    view_info.proj_mtx = projection.getDeviceProjectionMatrix();
    view_info.p_depth_shadow_mtx = p_depth_shadow_mtx;
    view_info.p_cull = p_cull;
    view_info._7c = param_6;

    mEnvObjMgr.updateView(
        camera.getViewMatrix(),
        projection.getDeviceProjectionMatrix(),
        view_index
    );

    for (sead::PtrArray<RenderObj>::iterator itr = mRenderObj.begin(), itr_end = mRenderObj.end(); itr != itr_end; ++itr)
        itr->updateView(view_index, view_info.view_mtx, view_info.proj_mtx, this);

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr = mRenderObjXlu.begin(), itr_end = mRenderObjXlu.end(); itr != itr_end; ++itr)
        itr->heapSort(compare_);
}

void RenderMgr::enable_18_()
{
    _18 = true;
}

void RenderMgr::calcGPU(s32 view_index)
{
    if (!_18)
        enable_18_();

    ViewInfo& view_info = getViewInfo(view_index);

    mModelEnvView.setUniformData(view_index, view_info.view_mtx, view_info.proj_mtx, view_info.p_depth_shadow_mtx, &mEnvObjMgr.getEnvObjSet(), view_info._7c);

    view_info.p_depth_shadow_mtx = nullptr;

    for (sead::PtrArray<RenderObj>::iterator itr = mRenderObj.begin(), itr_end = mRenderObj.end(); itr != itr_end; ++itr)
        itr->calcGPU(view_index, view_info.view_mtx, view_info.proj_mtx, this);
}

void RenderMgr::drawOpa(s32 view_index, const agl::lyr::RenderInfo& render_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    const agl::RenderBuffer* p_render_buffer = render_info.getRenderBuffer();
    const sead::Viewport* p_viewport = render_info.getViewport();

    p_viewport->apply(*p_render_buffer);

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr_buffer = mRenderObjOpa.begin(), itr_buffer_end = mRenderObjOpa.end(); itr_buffer != itr_buffer_end; ++itr_buffer)
    {
        if (mpCallback)
            mpCallback->preDrawOpa(view_index, itr_buffer.getIndex(), render_info);

        for (sead::PtrArray<RenderObj>::iterator itr_obj = itr_buffer->begin(), itr_obj_end = itr_buffer->end(); itr_obj != itr_obj_end; ++itr_obj)
            itr_obj->drawOpa(view_index, view_info.view_mtx, view_info.proj_mtx, this);

        if (mpCallback)
            mpCallback->postDrawOpa(view_index, itr_buffer.getIndex(), render_info);
    }
}

void RenderMgr::drawXlu(s32 view_index, const agl::lyr::RenderInfo& render_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    const agl::RenderBuffer* p_render_buffer = render_info.getRenderBuffer();
    const sead::Viewport* p_viewport = render_info.getViewport();

    p_viewport->apply(*p_render_buffer);

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr_buffer = mRenderObjXlu.begin(), itr_buffer_end = mRenderObjXlu.end(); itr_buffer != itr_buffer_end; ++itr_buffer)
    {
        if (mpCallback)
            mpCallback->preDrawXlu(view_index, itr_buffer.getIndex(), render_info);

        for (sead::PtrArray<RenderObj>::iterator itr_obj = itr_buffer->begin(), itr_obj_end = itr_buffer->end(); itr_obj != itr_obj_end; ++itr_obj)
            itr_obj->drawXlu(view_index, view_info.view_mtx, view_info.proj_mtx, this);

        if (mpCallback)
            mpCallback->postDrawXlu(view_index, itr_buffer.getIndex(), render_info);
    }
}

void RenderMgr::drawShadowOpa(s32 view_index, const agl::lyr::RenderInfo& render_info)
{
    mDrawShadow = true;

    const ViewInfo& view_info = getViewInfo(view_index);

    for (sead::PtrArray<RenderObj>::iterator itr = mRenderObjShadow.begin(), itr_end = mRenderObjShadow.end(); itr != itr_end; ++itr)
        itr->drawShadowOpa(view_index, view_info.view_mtx, view_info.proj_mtx, this);

    mDrawShadow = false;
}

void RenderMgr::drawReflectionOpa(s32 view_index, const agl::lyr::RenderInfo& render_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr_buffer = mRenderObjOpa.begin(), itr_buffer_end = mRenderObjOpa.end(); itr_buffer != itr_buffer_end; ++itr_buffer)
        for (sead::PtrArray<RenderObj>::iterator itr_obj = itr_buffer->begin(), itr_obj_end = itr_buffer->end(); itr_obj != itr_obj_end; ++itr_obj)
            itr_obj->drawReflectionOpa(view_index, view_info.view_mtx, view_info.proj_mtx, this);
}

void RenderMgr::drawReflectionXlu(s32 view_index, const agl::lyr::RenderInfo& render_info)
{
    const ViewInfo& view_info = getViewInfo(view_index);

    for (sead::Buffer< sead::PtrArray<RenderObj> >::iterator itr_buffer = mRenderObjXlu.begin(), itr_buffer_end = mRenderObjXlu.end(); itr_buffer != itr_buffer_end; ++itr_buffer)
        for (sead::PtrArray<RenderObj>::iterator itr_obj = itr_buffer->begin(), itr_obj_end = itr_buffer->end(); itr_obj != itr_obj_end; ++itr_obj)
            itr_obj->drawReflectionXlu(view_index, view_info.view_mtx, view_info.proj_mtx, this);
}

void RenderMgr::pushBackRenderObj(RenderObj* obj, s32 opa_buffer_index, s32 xlu_buffer_index)
{
    mRenderObj.pushBack(obj);

    if (opa_buffer_index >= 0)
        mRenderObjOpa[opa_buffer_index].pushBack(obj);

    if (xlu_buffer_index >= 0)
        mRenderObjXlu[xlu_buffer_index].pushBack(obj);

    if (obj->hasShadow())
        mRenderObjShadow.pushBack(obj);
}

void RenderMgr::pushBackRenderObj(RenderObj* obj, s32 opa_buffer_index, s32 xlu_buffer_index, const sead::Vector3f& order_pos)
{
    obj->getOrderPos().set(order_pos);
    pushBackRenderObj(obj, opa_buffer_index, xlu_buffer_index);
}

s32 RenderMgr::createView(RenderObjLayerBase* p_layer)
{
    for (sead::Buffer<ViewInfo>::iterator itr = mViewInfo.begin(), itr_end = mViewInfo.end(); itr != itr_end; ++itr)
    {
        if (itr->p_layer == nullptr)
        {
            itr->p_layer = p_layer;
            return itr.getIndex();
        }
        else if (itr->p_layer == p_layer)
        {
            return itr.getIndex();
        }
    }
    return -1;
}

void RenderMgr::loadEnvRes(const void* p_file)
{
    mEnvObjMgr.applyResource(agl::utl::ResParameterArchive(p_file));
}

void RenderMgr::calcViewShapeShadowFlags(agl::sdw::DepthShadow* p_depth_shadow, RenderObjLayerBase* p_shadow_layer)
{
    for (sead::PtrArray<RenderObj>::iterator itr = mRenderObjShadow.begin(), itr_end = mRenderObjShadow.end(); itr != itr_end; ++itr)
    {
        if (itr->hasShadow())
        {
            Model* p_model = sead::DynamicCast<Model>(&(*itr));
            if (p_model)
                p_model->calcViewShapeShadowFlags(p_depth_shadow, p_shadow_layer, this);
        }
    }
}
