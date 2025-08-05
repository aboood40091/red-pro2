#include <boss/FinalKoopa.h>
#include <effect/EffectObjBase.h>
#include <effect/EffectGroupID.h>
#include <effect/PtclCalcCallback.h>
#include <effect/PtclEmitterColorMgr.h>
#include <effect/PtclEmitterUserDataUtil.h>
#include <effect/PtclMgr.h>
#include <effect/PtclParallelExecuter.h>
#include <effect/PtclParam.h>
#include <effect/PtclParamMgr.h>
#include <effect/PtclUserShaderCallback.h>

#include <common/aglTextureSampler.h>
#include <filedevice/seadMainFileDevice.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <layer/aglRenderInfo.h>
#include <ptcl/seadPtclSystem.h>

static const sead::SafeString cPtclBaseFname = "Eset";

SEAD_SINGLETON_DISPOSER_IMPL(PtclMgr)

PtclMgr::PtclMgr()
    : mpPtclSystem(nullptr)
    , mpParallelExecuter(nullptr)
    , mpEmitterColorMgr(new PtclEmitterColorMgr())
    , mpParamMgr(nullptr)
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
    for (u8 group = 0; group < cEffectGroupID_Num; group++)
        mpPtclSystem->KillEmitterGroup(group);

    mEffects.clear();
}

void PtclMgr::updateAmbientLight(bool update_emitter)
{
    if (!mpEmitterColorMgr->updateAmbientLight(update_emitter))
        return;

    for (u8 group = 0; group < cEffectGroupID_Num; group++)
        for (nw::eft::EmitterSet* p_emitter_set = mpPtclSystem->GetEmitterSetHead(group); p_emitter_set; p_emitter_set = p_emitter_set->GetNext())
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

void PtclMgr::draw(const agl::lyr::RenderInfo& render_info, s32 type, const sead::PtrArray<nw::eft::EmitterInstance>* p_emitters)
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
            for (sead::PtrArray<nw::eft::EmitterInstance>::constIterator itr = p_emitters->constBegin(), itr_end = p_emitters->constEnd(); itr != itr_end; ++itr)
                mpPtclSystem->RenderEmitter(const_cast<nw::eft::EmitterInstance*>(&(*itr)));
    }
    else
    {
        for (s32 group = 0; group < cEffectGroupID_Num; group++)
            for (nw::eft::EmitterInstance* p_emitter = mpPtclSystem->GetEmitterHead(group); p_emitter; p_emitter = p_emitter->next)
                if (PtclEmitterUserDataUtil::getEmitterUserType(p_emitter->GetSimpleEmitterData()->userData >> 16) == type)
                    mpPtclSystem->RenderEmitter(p_emitter);
    }

    mpPtclSystem->EndRender();

    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_REGISTER);
    sead::Graphics::instance()->setBlendEnable(true);
}

s32 PtclMgr::getEmitterSetGroupID(s32 set_id, u32 res_id) const
{
    return PtclEmitterUserDataUtil::getEmitterSetGroupID(mpPtclSystem->GetResource(res_id)->GetUserDataBit(set_id), mPlayerNo);
}

void PtclMgr::enterScene(sead::Heap* heap)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        sead::ptcl::Config config;
        {
            config.SetEmitterSetNum(128);
            config._28 = 8;
            config.SetEmitterNum(256);
            config._29 = 11;
            config.SetParticleNum(2048);
            config._2c = 9;
            config.SetStripeNum(256);
            config.mpHeap = heap;
        }
        mpPtclSystem = new (heap) sead::ptcl::PtclSystem(config);
    }
    sead::Graphics::instance()->unlockDrawContext();

    {
        sead::MainFileDevice device(heap);
        sead::FileDevice::LoadArg arg;
        {
            arg.heap = heap;
            arg.alignment = nw::eft::EFT_PTCL_BINARY_ALIGNMENT;
            arg.path = sead::FormatFixedSafeString<128>("CAFE/effect/%s_Cafe.ptcl", cPtclBaseFname.cstr()).cstr();
        }
        void* resource = device.load(arg);
        mpPtclSystem->entryResource(heap, resource, 0);
    }

    mpParallelExecuter = new (heap) PtclParallelExecuter(heap, this, mpPtclSystem);

    mpParamMgr = new (heap) PtclParamMgr();
    mpParamMgr->initialize(heap);

    setUserDataCallbacks();

    mpPtclSystem->SetUserShaderRenderStateSetCallback(nw::eft::EFT_USER_SHADER_CALLBACK_1, &PtclUserShaderCallback::areaLoopRenderStateSetCallback);
    mpPtclSystem->SetUserShaderDrawOverrideCallback  (nw::eft::EFT_USER_SHADER_CALLBACK_1, &PtclUserShaderCallback::areaLoopDrawOverrideCallback);
}

void PtclMgr::enableDisplayList()
{
    mIsUseDisplayList = true;
}

void PtclMgr::pushBackDrawMethod()
{
    mpPtclSystem->SwapDoubleBuffer();

    nw::eft::Resource* p_res = mpPtclSystem->GetResource(0);
    for (u8 group = 0; group < cEffectGroupID_Num; group++)
        for (nw::eft::EmitterSet* p_emitter_set = mpPtclSystem->GetEmitterSetHead(group); p_emitter_set; p_emitter_set = p_emitter_set->GetNext())
            if (PtclEmitterUserDataUtil::isForceCalcEmitterSet(p_res->GetUserDataBit(p_emitter_set->GetEmitterSetID())))
                p_emitter_set->ForceCalc(60);

    updateAmbientLight();
    mIsDrawDisable = false;
}

void PtclMgr::exitScene()
{
    cleanUp();
    mIsDrawDisable = true;
}

void PtclMgr::setUserDataCallbacks()
{
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_0, &PtclCalcCallback::callback_0);
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_1, &PtclCalcCallback::callback_1);
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_2, &PtclCalcCallback::callback_2);
    mpPtclSystem->SetUserDataEmitterPostCalcCallback(nw::eft::EFT_USER_DATA_CALLBACK_ID_7, &FinalKoopa::emitterPostCalcCallback);
}

void PtclMgr::resetUserDataCallbacks()
{
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_0, nullptr);
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_1, nullptr);
    mpPtclSystem->SetUserDataParticleCalcCallback   (nw::eft::EFT_USER_DATA_CALLBACK_ID_2, nullptr);
    mpPtclSystem->SetUserDataEmitterPostCalcCallback(nw::eft::EFT_USER_DATA_CALLBACK_ID_7, nullptr);
}

void PtclMgr::execute()
{
    mpPtclSystem->SwapDoubleBuffer();
    mpPtclSystem->beginFrame();

    bool calc_group[cEffectGroupID_Num];
    for (u8 group = 0; group < cEffectGroupID_Num; group++)
        calc_group[group] = PtclEmitterUserDataUtil::isCalcGroup(group);

    for (sead::TList<EffectObjBase*>::robustIterator itr = mEffects.robustBegin(); itr != mEffects.robustEnd(); ++itr)
    {
        EffectObjBase* effect = itr->mData;

        bool calc = true;
        s32 group_id = effect->getGroupID();
        if (0 <= group_id && group_id < cEffectGroupID_Num)
            calc = calc_group[group_id];

        if (!effect->isActive())
        {
            if (calc)
                effect->cleanup();
        }
        else
        {
            effect->setActive(false);
        }
    }

    for (u8 group = 0; group < cEffectGroupID_Num; group++)
        if (calc_group[group])
            mpPtclSystem->calcEmitter(group);

    if (mIsUseParallel)
        mpParallelExecuter->execute();
    else
        mpPtclSystem->CalcParticle();

    mpEmitter1.clear();
    mpEmitter2.clear();

    for (s32 group = 0; group < cEffectGroupID_Num; group++)
    {
        for (nw::eft::EmitterInstance* p_emitter = mpPtclSystem->GetEmitterHead(group); p_emitter; p_emitter = p_emitter->next)
        {
            if (PtclEmitterUserDataUtil::getEmitterUserType(p_emitter->GetSimpleEmitterData()->userData >> 16) != 3)
                continue;

            if (p_emitter->emitterRT.m[2][3] <= 3600.0f)
                mpEmitter1.pushBack(p_emitter);
            else
                mpEmitter2.pushBack(p_emitter);
        }
    }

    if (!mpEmitter1.isEmpty())
        mpEmitter1.sort(&PtclMgr::compare);

    if (!mpEmitter2.isEmpty())
        mpEmitter2.sort(&PtclMgr::compare);
}

void PtclMgr::drawRange(const agl::lyr::RenderInfo& render_info, s32 typeMin, s32 typeMax)
{
    for (s32 type = typeMin; type < typeMax; type++)
        draw(render_info, type);
}

bool PtclMgr::createEmitterSet(nw::eft::Handle* p_handle, const sead::Matrix34f& mtxRT, EffectID id)
{
    const PtclParam* p_param = getParam(id);
    if (p_param == nullptr)
        return false;

    s32 set_id = p_param->emitter_set_id;
    s32 group_id = getEmitterSetGroupID(set_id);
    bool ret = mpPtclSystem->createEmitterSetID(p_handle, mtxRT, set_id, 0, group_id);
    if (p_handle->IsValid())
    {
        nw::eft::EmitterSet* p_set = p_handle->GetEmitterSet();
        p_set->SetRuntimeUserData(group_id);
        setEmitterColor_(p_set);
    }
    return ret;
}

const PtclParam* PtclMgr::getParam(EffectID id) const
{
    if (id < cEffectID_NumOriginal)
        return mpParamMgr->getParam(id);
    else
        return nullptr;
}

void PtclMgr::setFrameBufferTexture(const agl::TextureSampler& sampler, f32 x_offset, f32 y_offset, f32 x_scale, f32 y_scale)
{
    nw::eft::System* p_system = static_cast<nw::eft::System*>(mpPtclSystem);
    nw::eft::Texture texture = &sampler.getTexture();
    p_system->GetRenderer()->SetFrameBufferTexture(texture, x_offset, y_offset, x_scale, y_scale);
}
