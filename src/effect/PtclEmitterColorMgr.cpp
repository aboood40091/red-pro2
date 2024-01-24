#include <effect/PtclEmitterColorMgr.h>
#include <effect/PtclEmitterUserDataUtil.h>
#include <graphics/LightMapMgr.h>

#include <nw/eft/eft_EmitterSet.h>

PtclEmitterColorMgr::PtclEmitterColorMgr()
    : sead::IDisposer()
{
    for (s32 i = 0; i < cColorMax; i++)
        mLightColor[i] = sead::Color4f::cWhite;
}

bool PtclEmitterColorMgr::updateAmbientLight(bool update_emitter)
{
    static_assert(LightMapMgr::cAmbColorType_EffectColor15_1 + 1 == cColorMax);
    sead::Color4f color[cColorMax];
    for (u32 i = 0; i < cColorMax; i++)
    {
        LightMapMgr::instance()->getAmbColor(&(color[i]), LightMapMgr::AmbColorType(i));
        if (!(mLightColor[i] == color[i]))
        {
            mLightColor[i] = color[i];
            update_emitter = true;
        }
    }
    return update_emitter;
}

void PtclEmitterColorMgr::setEmitterColor(nw::eft::EmitterController* p_emitter_controller, u16 user_data_bit)
{
    switch (PtclEmitterUserDataUtil::getEmitterColorType(user_data_bit))
    {
    case 0:
    default:
        break;
    case 1:
        p_emitter_controller->SetEmitterColor0(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor13_0].r));
        p_emitter_controller->SetEmitterColor1(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor13_1].r));
        break;
    case 2:
        p_emitter_controller->SetEmitterColor0(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor14_0].r));
        p_emitter_controller->SetEmitterColor1(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor14_1].r));
        break;
    case 3:
        p_emitter_controller->SetEmitterColor0(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor15_0].r));
        p_emitter_controller->SetEmitterColor1(reinterpret_cast<const nw::ut::FloatColor&>(mLightColor[LightMapMgr::cAmbColorType_EffectColor15_1].r));
        break;
    }
}
