#include <event/EventMgr.h>
#include <game/AreaLayerMgr.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResourceMgr.h>
#include <graphics/RenderMgr.h>
#include <map/BgTexMgr.h>
#include <map/CoinOrigin.h>
#include <map/UnitID.h>
#include <system/ResMgr.h>

#include <gfx/seadGraphicsContext.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <layer/aglRenderer.h>

SEAD_SINGLETON_DISPOSER_IMPL(CoinOrigin)

static const f32 cTexWidth = 2048;
static const f32 cTexHeight = 512;
static const f32 cUnitSize = 64;
static const f32 cUnitSizeNoPad = 60;
static const s32 cUnitPerRow = 2048 / 64;
//static const s32 cUnitPerColumn = 512 / 64;

static const Angle cCoinAngleStep = 0x3fd27d2;

CoinOrigin::CoinOrigin()
{
}

void CoinOrigin::initialize(sead::Heap* heap)
{
    ResMgr::instance()->loadArchiveRes("obj_coin", "actor/obj_coin.sarc", heap, false);
    ModelResourceMgr::instance()->loadResFile("obj_coin", "obj_coin", heap);
    mpModelCoin = Model::createG3d(
        *ModelResourceMgr::instance()->getResource("obj_coin"),
        "obj_coin",
        1, 1, 1, 1, 0,
        Model::cBoundingMode_Disable,
        heap
    );
    mpModelBlueCoin = Model::createG3d(
        *ModelResourceMgr::instance()->getResource("obj_coin"),
        "obj_coin_blue",
        1, 1, 1, 1, 0,
        Model::cBoundingMode_Disable,
        heap
    );
}

void CoinOrigin::pushBackDrawMethod()
{
    mProjection.setNear(0.0f);
    mProjection.setFar(1000.0f);
    mProjection.setTBLR(cTexHeight, 0.0f, 0.0f, cTexWidth);

    mCamera.getPos().set(0.0f, 0.0f, 0.0f);
    mCamera.getAt().set(0.0f, 0.0f, -1.0f);
    mCamera.getUp().set(0.0f, 1.0f, 0.0f);
    mCamera.getUp().normalize();
    mCamera.updateViewMatrix(); // Most likely the normalize call has to be inside here instead

    calcMdl_();

    mDrawMethod.bind(this, &CoinOrigin::apply_, "CoinOrigin");
    mDrawMethod.setPriority(-200);

    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_BGUpdate)->pushBackDrawMethod(RenderObjLayer::cRenderStep_Opa, &mDrawMethod);
    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_BGUpdate)->setProjection(&mProjection);
    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_BGUpdate)->setCamera(&mCamera);
}

void CoinOrigin::removeDrawMethod()
{
    agl::lyr::Renderer::instance()->removeDrawMethod(&mDrawMethod);
}

void CoinOrigin::update()
{
    if (EventMgr::instance() == nullptr || EventMgr::instance()->getCurrentEvent() == nullptr)
        mCoinAngle += cCoinAngleStep;

    calcMdl_();
}

void CoinOrigin::draw()
{
    RenderObjLayer* p_layer = sead::DynamicCast<RenderObjLayer>(agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_BGUpdate));

    p_layer->getRenderMgr()->pushBackRenderObj(mpModelCoin, 0, 0, sead::Vector3f::zero);
    p_layer->getRenderMgr()->pushBackRenderObj(mpModelBlueCoin, 0, 0, sead::Vector3f::zero);
}

void CoinOrigin::calcMdl_()
{
    f32 x = cUnitSize * 0.5f;
    f32 y = (cUnitSize + cUnitSizeNoPad) * 0.5f;

    sead::Matrix34f mtx;
    {
        sead::Vector3u r = getCoinRotation();
        sead::Vector3f t((cUnitID_Coin              % cUnitPerRow) * cUnitSize + x, cTexHeight - (cUnitID_Coin              / cUnitPerRow + 1.5f) * cUnitSize + y, -500.0f);
        mtx.makeRzxyTIdx(r, t);
        mpModelCoin->setMtxRT(mtx);
    }
    {
        sead::Vector3u r = getCoinRotation();
        sead::Vector3f t((cUnitID_BlueCoin_CoreCoin % cUnitPerRow) * cUnitSize + x, cTexHeight - (cUnitID_BlueCoin_CoreCoin / cUnitPerRow + 1.5f) * cUnitSize + y, -500.0f);
        mtx.makeRzxyTIdx(r, t);
        mpModelBlueCoin->setMtxRT(mtx);
    }

    f32 scale = 1.5f * cUnitSizeNoPad / 24;

    mpModelCoin->setScale(sead::Vector3f(scale, scale, scale));
    mpModelBlueCoin->setScale(sead::Vector3f(scale, scale, scale));

    mpModelCoin->calcMdl();
    mpModelBlueCoin->calcMdl();
}

void CoinOrigin::apply_(const agl::lyr::RenderInfo& render_info)
{
    BgTexMgr::instance()->getTexRenderBuffer().bind();
    sead::Viewport viewport = sead::Viewport(BgTexMgr::instance()->getTexRenderBuffer());
    viewport.apply(BgTexMgr::instance()->getTexRenderBuffer());

    sead::GraphicsContext context;
    context.setDepthEnable(true, true);
    context.setDepthFunc(sead::Graphics::cDepthFunc_Always);
    context.setBlendEnable(false);
    context.setCullingMode(sead::Graphics::cCullingMode_None);
    context.apply();

    sead::PrimitiveRenderer* primitive_renderer = sead::PrimitiveRenderer::instance();
    primitive_renderer->setProjection(mProjection);
    primitive_renderer->setCamera(mCamera);
    primitive_renderer->setModelMatrix(sead::Matrix34f::ident);

    primitive_renderer->begin();
    {
        {
            sead::PrimitiveRenderer::QuadArg arg;
            sead::Vector3f p(cUnitID_Coin              % cUnitPerRow * cUnitSize, cTexHeight - (cUnitID_Coin              / cUnitPerRow + 1) * cUnitSize, -999.0f);
            sead::Vector2f size(cUnitSize, cUnitSize);
            arg.setCornerAndSize(p, size);
            sead::Color4f color(1.0f, 0.0f, 0.0f, 0.0f);
            arg.setColor(color, color);
            primitive_renderer->drawQuad(arg);
        }
        {
            sead::PrimitiveRenderer::QuadArg arg;
            sead::Vector3f p(cUnitID_BlueCoin_CoreCoin % cUnitPerRow * cUnitSize, cTexHeight - (cUnitID_BlueCoin_CoreCoin / cUnitPerRow + 1) * cUnitSize, -999.0f);
            sead::Vector2f size(cUnitSize, cUnitSize);
            arg.setCornerAndSize(p, size);
            sead::Color4f color(1.0f, 0.0f, 0.0f, 0.0f);
            arg.setColor(color, color);
            primitive_renderer->drawQuad(arg);
        }
    }
    primitive_renderer->end();

    render_info.getRenderBuffer()->bind();
    render_info.getViewport()->apply(*render_info.getRenderBuffer());
}
