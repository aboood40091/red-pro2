#include <game/AreaLayerMgr.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelNW.h>
#include <graphics/Renderer.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <map/BgRenderer.h>
#include <map/LayerID.h>
#include <map/UnitID.h>

#include <layer/aglRenderer.h>

SEAD_SINGLETON_DISPOSER_IMPL(Renderer)

Renderer::Renderer()
    : mpLayer(nullptr)
    , mDefaultOpaBufferIdx(3)
    , mDefaultXluBufferIdx(6)
{
}

Renderer::~Renderer()
{
}

void Renderer::setViewBoundBox(const sead::BoundBox2f& box)
{
    mViewBoundBox.setMin(box.getMin());
    mViewBoundBox.setMax(box.getMax());
}

void Renderer::calcForAreaTask()
{
    mProjection3D.setNear(1.0f);
    mProjection3D.setFar(20000.0f);

    mProjection3D.setTBLR(
        -mViewBoundBox.getMin().y,
        -mViewBoundBox.getMax().y,
         mViewBoundBox.getMin().x,
         mViewBoundBox.getMax().x
    );

    mCamera3D.getPos().set(0.0f, 0.0f, 10000.0f);

    mCamera3D.getAt().set(0.0f, 0.0f, -1.0f);

    mCamera3D.getUp().set(sead::Vector3f::ey);
    mCamera3D.getUp().normalize();

    mCamera3D.updateViewMatrix();

    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_3D)->setProjection(&mProjection3D);
    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_3D)->setCamera(&mCamera3D);

    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_3D_DRC)->setProjection(&mProjection3D);
    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_3D_DRC)->setCamera(&mCamera3D);

    agl::lyr::Layer* p_final_koopa_layer = agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_FinalKoopa);
    if (p_final_koopa_layer != nullptr)
    {
        mProjectionFinalKoopa.setNear(1.0f);
        mProjectionFinalKoopa.setFar(20000.0f);

        f32 center_x = ( mViewBoundBox.getMin().x + mViewBoundBox.getMax().x) * 0.5f;
        f32 center_y = (-mViewBoundBox.getMin().y - mViewBoundBox.getMax().y) * 0.5f;
        f32 half_size_x = (mViewBoundBox.getMax().x - mViewBoundBox.getMin().x) * 0.5f;
        f32 half_size_y = (mViewBoundBox.getMax().y - mViewBoundBox.getMin().y) * 0.5f;

        mProjectionFinalKoopa.setTBLR(
             half_size_y,
            -half_size_y,
            -half_size_x,
             half_size_x
        );

        mCameraFinalKoopa.getPos().set(center_x, center_y, 10000.0f);

        mCameraFinalKoopa.getAt().set(center_x, center_y, -1.0f);

        mCameraFinalKoopa.getUp().set(sead::Vector3f::ey);
        mCameraFinalKoopa.getUp().normalize();

        mCameraFinalKoopa.updateViewMatrix();

        p_final_koopa_layer->setProjection(&mProjectionFinalKoopa);
        p_final_koopa_layer->setCamera(&mCameraFinalKoopa);
    }
}

void Renderer::setLayer(agl::lyr::Layer* p_layer, GatherType type)
{
    mpLayer = sead::DynamicCast<RenderObjLayerBase>(p_layer);

    switch (type)
    {
    case cGatherType_0:
        mDefaultOpaBufferIdx = 3;
        mDefaultXluBufferIdx = 6;
        break;
    case cGatherType_1:
        mDefaultOpaBufferIdx = 1;
        mDefaultXluBufferIdx = 0;
        break;
    case cGatherType_2:
    case cGatherType_3:
        mDefaultOpaBufferIdx = 0;
        mDefaultXluBufferIdx = 0;
        break;
    }
}

void Renderer::resetLayer()
{
    mpLayer = nullptr;
}

void Renderer::drawModel(Model* p_model)
{
    s32 opa_buffer_idx;
    s32 xlu_buffer_idx;

    if (p_model->hasOpa())
    {
        opa_buffer_idx = p_model->getOpaBufferIdx();
        if (opa_buffer_idx == -2)
            opa_buffer_idx = mDefaultOpaBufferIdx;
    }
    else
    {
        opa_buffer_idx = -1;
    }

    if (p_model->hasXlu())
    {
        xlu_buffer_idx = p_model->getXluBufferIdx();
        if (xlu_buffer_idx == -2)
            xlu_buffer_idx = mDefaultXluBufferIdx;
    }
    else
    {
        xlu_buffer_idx = -1;
    }

    p_model->getMtxRT().getTranslation(p_model->getOrderPos());

    mpLayer->getRenderMgr()->pushBackRenderObj(p_model, opa_buffer_idx, xlu_buffer_idx);
}

void Renderer::drawModel(const BasicModel& model)
{
    drawModel(model.getModel());
}

// TODO
/*
void Renderer::drawModel(ModelFFL* p_model)
{
    s32 opa_buffer_idx;
    s32 xlu_buffer_idx;

    opa_buffer_idx = p_model->getOpaBufferIdx();
    if (opa_buffer_idx == -2)
        opa_buffer_idx = mDefaultOpaBufferIdx;

    xlu_buffer_idx = p_model->getXluBufferIdx();
    if (xlu_buffer_idx == -2)
        xlu_buffer_idx = mDefaultXluBufferIdx;

    p_model->getMtxRT().getTranslation(p_model->getOrderPos());

    mpLayer->getRenderMgr()->pushBackRenderObj(p_model, opa_buffer_idx, xlu_buffer_idx);
}
*/

void Renderer::drawActorBgUnit(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale)
{
    BgRenderer::instance()->drawActorBgUnit(
        (pos.z < 0
            ? cLayerID_Layer2
            : (pos.z < 3600
                  ? cLayerID_Layer1
                  : cLayerID_Layer0_Actor)),
        unit,
        pos,
        sead::Vector3u(0, 0, angle),
        scale
    );
}

void Renderer::drawActorBgUnitLayer0(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale)
{
    BgRenderer::instance()->drawActorBgUnit(
        cLayerID_Layer0_Actor,
        unit,
        pos,
        sead::Vector3u(0, 0, angle),
        scale
    );
}
