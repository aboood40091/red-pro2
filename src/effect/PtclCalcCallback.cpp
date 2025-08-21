#include <collision/ActorBgCollisionCheck.h>
#include <effect/PtclCalcCallback.h>
#include <map/Bg.h>
#include <map/LayerID.h>
#include <scroll/BgScrollMgr.h>

void PtclCalcCallback::callback_0(nw::eft::ParticleCalcArg& arg)
{
    nw::eft::EmitterInstance* emitter = arg.emitter;
    if (emitter == nullptr)
        return;

    nw::eft::PtclInstance* ptcl = arg.ptcl;
    if (ptcl == nullptr)
        return;

    if (Bg::instance() == nullptr)
        return;

    sead::Vector3f pos(ptcl->worldPos.x, ptcl->worldPos.y, ptcl->worldPos.z);
    WaterType water_type = ActorBgCollisionCheck::checkWater(pos, cLayerID_Layer1);
    switch (water_type)
    {
    case cWaterType_Water:
    case cWaterType_AirWater:
        return;
    }

    nw::eft::EmitterCalc::RemoveParticle(emitter, ptcl, arg.core);
}

void PtclCalcCallback::callback_1(nw::eft::ParticleCalcArg& arg)
{
    nw::eft::EmitterInstance* emitter = arg.emitter;
    if (emitter == nullptr)
        return;

    nw::eft::PtclInstance* ptcl = arg.ptcl;
    if (ptcl == nullptr)
        return;

    if (BgScrollMgr::instance() == nullptr)
        return;

    const sead::BoundBox2f& screen_rect = BgScrollMgr::instance()->getScreenRect();

    f32 screen_w = screen_rect.getSizeX();
    f32 x;
    if (x = screen_rect.getMin().x - ptcl->worldPos.x, x > 0.0f)
        ptcl->worldPos.x += screen_w * ((s32)x / (s32)screen_w + 1);
    else if (x = ptcl->worldPos.x - screen_rect.getMax().x, x > 0.0f)
        ptcl->worldPos.x -= screen_w * ((s32)x / (s32)screen_w + 1);

    f32 screen_h = screen_rect.getSizeY();
    f32 y;
    if (y = screen_rect.getMin().y - ptcl->worldPos.y, y > 0.0f)
        ptcl->worldPos.y += screen_h * ((s32)y / (s32)screen_h + 1);
    else if (y = ptcl->worldPos.y - screen_rect.getMax().y, y > 0.0f)
        ptcl->worldPos.y -= screen_h * ((s32)y / (s32)screen_h + 1);
}

void PtclCalcCallback::callback_2(nw::eft::ParticleCalcArg& arg)
{
    nw::eft::EmitterInstance* emitter = arg.emitter;
    if (emitter == nullptr)
        return;

    nw::eft::PtclInstance* ptcl = arg.ptcl;
    if (ptcl == nullptr)
        return;

    if (BgScrollMgr::instance() == nullptr)
        return;

    const sead::BoundBox2f& screen_rect = BgScrollMgr::instance()->getScreenRectDefault();

    f32 screen_w = screen_rect.getSizeX();
    f32 x;
    if (x = screen_rect.getMin().x - ptcl->worldPos.x, x > 0.0f)
        ptcl->worldPos.x += screen_w * ((s32)x / (s32)screen_w + 1);
    else if (x = ptcl->worldPos.x - screen_rect.getMax().x, x > 0.0f)
        ptcl->worldPos.x -= screen_w * ((s32)x / (s32)screen_w + 1);

    f32 screen_h = screen_rect.getSizeY();
    f32 y;
    if (y = screen_rect.getMin().y - ptcl->worldPos.y, y > 0.0f)
        ptcl->worldPos.y += screen_h * ((s32)y / (s32)screen_h + 1);
    else if (y = ptcl->worldPos.y - screen_rect.getMax().y, y > 0.0f)
        ptcl->worldPos.y -= screen_h * ((s32)y / (s32)screen_h + 1);
}
