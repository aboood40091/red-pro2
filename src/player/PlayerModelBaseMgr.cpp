#include <game/AreaLayerMgr.h>
#include <graphics/ModelG3d.h>
#include <graphics/Renderer.h>
#include <player/PlayerEnum.h>
#include <player/PlayerModelBaseMgr.h>

PlayerModelBaseMgr::PlayerModelBaseMgr()
    : mpModelBase(nullptr)
    , mDrawType(cDrawType_Normal)
{
}

void PlayerModelBaseMgr::setModelBase(PlayerModelBase* p_mdl_base)
{
    mpModelBase = p_mdl_base;
    if (p_mdl_base->isValidSceneType())
        p_mdl_base->setModelRenderPass(Renderer::cDefaultRenderPass, Renderer::cDefaultRenderPass);
    setAnm(PlayerAnmID::wait);
}

void PlayerModelBaseMgr::setAnm(s32 anm_id, f32 frame)
{
    setAnm(anm_id, getAnmRate(anm_id), getAnmBlendDuration(anm_id), frame);
}

void PlayerModelBaseMgr::setAnm(s32 anm_id, f32 blend_duration, f32 frame)
{
    setAnm(anm_id, getAnmRate(anm_id), blend_duration, frame);
}

void PlayerModelBaseMgr::setBodyAnm(s32 anm_id)
{
    setBodyAnm(anm_id, getAnmRate(anm_id));
}

void PlayerModelBaseMgr::draw()
{
    if (mDrawType != cDrawType_InDistantView)
        return mpModelBase->draw();

    Renderer::LayerSwitcher<
        AreaLayerMgr::cLayer_DistantView,
        AreaLayerMgr::cLayer_3D,
        Renderer::cRenderPassType_Course
    > layer_switcher;

    mpModelBase->draw();
}

void PlayerModelBaseMgr::setDrawType(DrawType type)
{
    mDrawType = type;
    switch (type)
    {
    default:
        break;
    case cDrawType_Normal:
        mpModelBase->setModelG3dRenderFlag(ModelG3d::cRenderFlag_Default);
        mpModelBase->setModelRenderPass(Renderer::cDefaultRenderPass, Renderer::cDefaultRenderPass);
        break;
    case cDrawType_InBalloon:
        mpModelBase->setModelG3dRenderFlag(ModelG3d::cRenderFlag_DrawAllAtXlu);
        mpModelBase->setModelRenderPass(Renderer::cDefaultRenderPass, 8);
        break;
    case cDrawType_InDistantView:
        mpModelBase->setModelG3dRenderFlag(ModelG3d::cRenderFlag_Default);
        mpModelBase->setModelRenderPass(0, 0);
        break;
    }
}
