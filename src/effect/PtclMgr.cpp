#include <effect/PtclEmitterColorMgr.h>
#include <effect/PtclEmitterUserDataUtil.h>
#include <effect/PtclMgr.h>

#include <gfx/seadCamera.h>
#include <gfx/seadGraphics.h>
#include <gfx/seadProjection.h>
#include <layer/aglRenderInfo.h>
#include <ptcl/seadPtclSystem.h>

SEAD_SINGLETON_DISPOSER_IMPL(PtclMgr)

PtclMgr::PtclMgr()
    : mpPtclSystem(nullptr)
    , mpPtclParallelTbl(nullptr)
    , mpEmitterColorMgr(new PtclEmitterColorMgr())
    , mpUserShaderParamTbl(nullptr)
    , mEffects()
    , mpEmitter1()
    , mpEmitter2()
    , mPlayerNo(-1)
    , mIsUseDisplayList(false)
    , mIsDrawDisable(false)
    , mIsUseParallel(true)
{
}

PtclMgr::~PtclMgr()
{
    cleanUp();
    mpPtclSystem->clearResource(0);
}

void PtclMgr::cleanUp()
{
    for (u8 group = 0; group < 8; group++)
        mpPtclSystem->KillEmitterGroup(group);

    mEffects.clear();
}

void PtclMgr::updateAmbientLight(bool update_emitter)
{
    if (!mpEmitterColorMgr->updateAmbientLight(update_emitter))
        return;

    for (u8 i = 0; i < 8; i++)
        for (nw::eft::EmitterSet* p_emitter_set = mpPtclSystem->GetEmitterSetHead(i); p_emitter_set; p_emitter_set = p_emitter_set->GetNext())
            setEmitterColor_(p_emitter_set);
}

void PtclMgr::setEmitterColor_(nw::eft::EmitterSet* p_emitter_set)
{
    for (s32 i = 0, n = p_emitter_set->GetNumEmitter(); i < n; ++i)
    {
        const nw::eft::EmitterInstance* p_emitter = p_emitter_set->GetAliveEmitter(i);
        if (p_emitter != nullptr)
            mpEmitterColorMgr->setEmitterColor(p_emitter->controller, p_emitter->GetSimpleEmitterData()->userData >> 16);
    }
}

s32 PtclMgr::compare(const nw::eft::EmitterInstance* a, const nw::eft::EmitterInstance* b)
{
    f32 dist = a->emitterRT.m[2][3] - b->emitterRT.m[2][3];
    if (dist < 0.0f)
        return -1;
    return dist > 0.0f;
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
                if (PtclEmitterUserDataUtil::getEmitterUserType(p_emitter->GetSimpleEmitterData()->userData >> 16) == type)
                    mpPtclSystem->RenderEmitter(p_emitter);

                p_emitter = p_emitter->next;
            }
        }
    }

    mpPtclSystem->EndRender();

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
    sead::Graphics::instance()->setBlendEnable(true);
}
