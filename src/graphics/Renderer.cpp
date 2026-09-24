#include <game/AreaLayerMgr.h>
#include <graphics/AnimModel.h>
#include <graphics/ModelG3d.h>
#include <graphics/Renderer.h>
#include <graphics/RenderObjLayer.h>
#include <graphics/RenderObjRenderMgr.h>
#include <map/BgRenderer.h>
#include <map/LayerID.h>
#include <map/UnitID.h>

#include <layer/aglRenderer.h>

SEAD_SINGLETON_DISPOSER_IMPL(Renderer)

Renderer::Renderer()
    : mpLayer(nullptr)
    , mDefaultOpaRenderPass(3)
    , mDefaultXluRenderPass(6)
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

void Renderer::setLayer(agl::lyr::Layer* p_layer, RenderPassType render_pass_type)
{
    mpLayer = sead::DynamicCast<RenderObjLayerBase>(p_layer);

    switch (render_pass_type)
    {
    case cRenderPassType_Course:
        mDefaultOpaRenderPass = 3;
        mDefaultXluRenderPass = 6;
        break;
    case cRenderPassType_CourseSelect:
        mDefaultOpaRenderPass = 1;
        mDefaultXluRenderPass = 0;
        break;
    case cRenderPassType_DemoScene:
    case cRenderPassType_Misc:
        mDefaultOpaRenderPass = 0;
        mDefaultXluRenderPass = 0;
        break;
    }
}

void Renderer::resetLayer()
{
    mpLayer = nullptr;
}

void Renderer::drawModel(Model* p_model)
{
    s32 opa_render_pass;
    s32 xlu_render_pass;

    if (p_model->hasOpa())
    {
        opa_render_pass = p_model->getOpaRenderPass();
        if (opa_render_pass == cDefaultRenderPass)
            opa_render_pass = mDefaultOpaRenderPass;
    }
    else
    {
        opa_render_pass = -1;
    }

    if (p_model->hasXlu())
    {
        xlu_render_pass = p_model->getXluRenderPass();
        if (xlu_render_pass == cDefaultRenderPass)
            xlu_render_pass = mDefaultXluRenderPass;
    }
    else
    {
        xlu_render_pass = -1;
    }

    p_model->getBaseModelMtx().getTranslation(p_model->getOrderPos());

    mpLayer->getRenderMgr()->pushBackRenderObj(p_model, opa_render_pass, xlu_render_pass);
}

void Renderer::drawModel(const AnimModel* p_model)
{
    drawModel(p_model->getModel());
}

// TODO
/*
void Renderer::drawModel(ModelFFL* p_model)
{
    s32 opa_render_pass;
    s32 xlu_render_pass;

    opa_render_pass = p_model->getOpaRenderPass();
    if (opa_render_pass == cDefaultRenderPass)
        opa_render_pass = mDefaultOpaRenderPass;

    xlu_render_pass = p_model->getXluRenderPass();
    if (xlu_render_pass == cDefaultRenderPass)
        xlu_render_pass = mDefaultXluRenderPass;

    p_model->getBaseModelMtx().getTranslation(p_model->getOrderPos());

    mpLayer->getRenderMgr()->pushBackRenderObj(p_model, opa_render_pass, xlu_render_pass);
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
        Angle3(0, 0, angle),
        scale
    );
}

void Renderer::drawActorBgUnitLayer0(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale)
{
    BgRenderer::instance()->drawActorBgUnit(
        cLayerID_Layer0_Actor,
        unit,
        pos,
        Angle3(0, 0, angle),
        scale
    );
}
