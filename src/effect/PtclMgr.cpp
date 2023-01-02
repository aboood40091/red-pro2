#include <effect/PtclLightMgr.h>
#include <effect/PtclMgr.h>

#include <gfx/seadCamera.h>
#include <gfx/seadGraphics.h>
#include <gfx/seadProjection.h>
#include <layer/aglRenderInfo.h>
#include <ptcl/seadPtclSystem.h>

u32 PtclMgr::userDataToType_(u16 user_data)
{
    if (user_data & 0x0200)
    {
        if (user_data & 0x0800)
            return 14;

        if (user_data & 0x0400)
            return 13;

        return 15;
    }

    if (user_data & 0x0800)
        return 16;

    if (user_data & 0x0100)
    {
        if (user_data & 0x0400)
            return 10;

        return 11;
    }

    if (user_data & 0x0400)
        return 12;

    if (user_data & 1)
        return 0;

    if (user_data & 0x0080)
        return 7;

    if (user_data & 0x0040)
        return 6;

    if (user_data & 0x0020)
        return 5;

    if (user_data & 0x0010)
        return 4;

    if (user_data & 0x0008)
        return 3;

    if (user_data & 0x0002)
        return 1;

    if (user_data & 0x0004)
        return 2;

    if (user_data & 0x1000)
        return 8;

    return 9;
}

SEAD_SINGLETON_DISPOSER_IMPL(PtclMgr)

PtclMgr::PtclMgr()
    : mpPtclSystem(nullptr)
    , mpPtclParallelTbl(nullptr)
    , mpLightMgr(new PtclLightMgr())
    , mpUserShaderParamTbl(nullptr)
    , mEffects()
    , mpEmitter1()
    , mpEmitter2()
    , mPlayerId(-1)
    , mIsUseDisplayList(false)
    , mIsDrawDisable(false)
    , mIsUseParallel(true)
{
}

void PtclMgr::draw(const agl::lyr::RenderInfo& render_info, u32 type, const sead::PtrArray<nw::eft::EmitterInstance>* p_emitters)
{
    if (mIsDrawDisable)
        return;

    const sead::Camera* p_camera = render_info.getCamera();
    const sead::Projection* p_projection = render_info.getProjection();

    f32 near = 1.0f;
    f32 far = 10000.0f;

    if (sead::IsDerivedTypes<sead::PerspectiveProjection>(p_projection))
    {
        const sead::PerspectiveProjection& projection = *static_cast<const sead::PerspectiveProjection*>(p_projection);
        near = projection.getNear();
        far = projection.getFar();
    }
    else if (sead::IsDerivedTypes<sead::OrthoProjection>(p_projection))
    {
        const sead::OrthoProjection& projection = *static_cast<const sead::OrthoProjection*>(p_projection);
        near = projection.getNear();
        far = projection.getFar();
    }
    else if (sead::IsDerivedTypes<sead::FrustumProjection>(p_projection))
    {
        const sead::FrustumProjection& projection = *static_cast<const sead::FrustumProjection*>(p_projection);
        near = projection.getNear();
        far = projection.getFar();
    }

    sead::Vector3f cam_pos;
    p_camera->getWorldPosByMatrix(&cam_pos);

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
    GX2Invalidate(GX2_INVALIDATE_SHADER, 0, 0xffffffff);

    mpPtclSystem->BeginRender(
        reinterpret_cast<const nw::math::MTX44&>(p_projection->getDeviceProjectionMatrix()),
        reinterpret_cast<const nw::math::MTX34&>(p_camera->getViewMatrix()),
        reinterpret_cast<const nw::math::VEC3&>(cam_pos),
        near,
        far
    );

    if (p_emitters)
    {
        if (p_emitters->size() > 0)
        {
            for (sead::PtrArray<nw::eft::EmitterInstance>::constIterator itr = p_emitters->constBegin(), itr_end = p_emitters->constEnd(); itr != itr_end; ++itr)
                mpPtclSystem->RenderEmitter(const_cast<nw::eft::EmitterInstance*>(&(*itr)));
        }
    }
    else
    {
        for (s32 i = 0; i < 8; i++)
        {
            nw::eft::EmitterInstance* p_emitter = mpPtclSystem->GetEmitterHead(i);
            while (p_emitter)
            {
                if (userDataToType_(p_emitter->GetSimpleEmitterData()->userData >> 16) == type)
                    mpPtclSystem->RenderEmitter(p_emitter);

                p_emitter = p_emitter->next;
            }
        }
    }

    mpPtclSystem->EndRender();

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
    sead::Graphics::instance()->setBlendEnable(true);
}
