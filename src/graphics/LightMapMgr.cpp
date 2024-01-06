#include <effect/PtclMgr.h>
#include <graphics/GfxParameter.h>
#include <graphics/LayerMgr.h>
#include <graphics/LightMapMgr.h>
#include <graphics/ModelG3d.h>

#include <environment/aglLight.h>
#include <g3d/aglTextureUtilG3D.h>
#include <layer/aglRenderer.h>
#include <layer/aglRenderInfo.h>

namespace {

static const sead::SafeString cDirectionalLightNameAll[LightMapMgr::cDirectionalLightNumAll] = {
    "DirectionalLight0",    "DirectionalLight1",
    "DL_e_01",              "DL_e_02",              "DL_e_03",  "DL_e_04",
    "DL_b_01",              "DL_b_02",              "DL_b_03",  "DL_b_04",
    "DL_mo_01",             "DL_mo_02",             "DL_mo_03", "DL_mo_04",
    "DL_i_01",              "DL_i_02",              "DL_i_03",  "DL_i_04",
    "DL_p_01",              "DL_p_02",              "DL_p_03",  "DL_p_04",
    "DL_m_01",              "DL_m_02",              "DL_m_03",  "DL_m_04",
    "DL_ef_01",             "DL_ef_02",             "DL_ef_03", "DL_ef_04",
    "lmDifCSW1a",           "lmSpcCSW1a",
    "lmDifCSW2a",           "lmSpcCSW2a",
    "lmDifCSW2b",           "lmSpcCSW2b",
    "lmDifCSW3a",           "lmSpcCSW3a",
    "lmDifCSW4a",           "lmSpcCSW4a",
    "lmDifCSW5a",           "lmSpcCSW5a",
    "lmDifCSW5b",           "lmSpcCSW5b",
    "lmDifCSW6a",           "lmSpcCSW6a",
    "lmDifCSW6b",           "lmSpcCSW6b",
    "lmDifCSW7a",           "lmSpcCSW7a",
    "lmDifCSW8a",           "lmSpcCSW8a",
    "lmDifCSW8b",           "lmSpcCSW8b",
    "lmDifCSW9a",           "lmSpcCSW9a"
};

static const sead::SafeString cAmbColorName[LightMapMgr::cAmbColorType_Num] = {
    "EffectColor13_0",
    "EffectColor13_1",
    "EffectColor14_0",
    "EffectColor14_1",
    "EffectColor15_0",
    "EffectColor15_1",
    "WaterHalfFrontColor0",
    "WaterHalfFrontKonst0",
    "WaterHalfFrontKonst1",
    "WaterHalfBehindColor0",
    "WaterHalfBehindColor1"
};

static const sead::SafeString cLightMapNameAll[LightMapMgr::cLightMapNumAll] = {
    "lm_01e",       "lm_02e",
    "lm_01m",       "lm_02m",
    "lm_01mo",      "lm_02mo",
    "lm_01i",       "lm_02i",
    "lm_01p",       "lm_02p",
    "lm_01b",       "lm_02b",
    "lm_01ef",      "lm_02ef",
    "lmDifCSW1a",   "lmSpcCSW1a",
    "lmDifCSW2a",   "lmSpcCSW2a",
    "lmDifCSW2b",   "lmSpcCSW2b",
    "lmDifCSW3a",   "lmSpcCSW3a",
    "lmDifCSW4a",   "lmSpcCSW4a",
    "lmDifCSW5a",   "lmSpcCSW5a",
    "lmDifCSW5b",   "lmSpcCSW5b",
    "lmDifCSW6a",   "lmSpcCSW6a",
    "lmDifCSW6b",   "lmSpcCSW6b",
    "lmDifCSW7a",   "lmSpcCSW7a",
    "lmDifCSW8a",   "lmSpcCSW8a",
    "lmDifCSW8b",   "lmSpcCSW8b",
    "lmDifCSW9a",   "lmSpcCSW9a"
};

static const sead::SafeString cEnvTypeNameCourse[LightMapMgr::cEnvTypeCourse_Num] = {
    "enemy",
    "boss",
    "mapobj",
    "item",
    "player",
    "DV",
    "effect"
};

static const sead::SafeString cEnvTypeNameCourseSelect[LightMapMgr::cEnvTypeCourseSelect_Num] = {
    "CS_W1a",
    "CS_W2a",
    "CS_W2b",
    "CS_W3a",
    "CS_W4a",
    "CS_W5a",
    "CS_W5b",
    "CS_W6a",
    "CS_W6b",
    "CS_W7a",
    "CS_W8a",
    "CS_W8b",
    "CS_W9a"
};

s32 sEnvTypeCourseSelectNum = LightMapMgr::cEnvTypeCourseSelect_Num; // TODO: Somehow make this end up in .bss

static const sead::SafeString cLightMapNameCourse[LightMapMgr::cLightMapNum][LightMapMgr::cEnvTypeCourse_Num] = {
    {
        "lm_01e",
        "lm_01m",
        "lm_01mo",
        "lm_01i",
        "lm_01p",
        "lm_01b",
        "lm_01ef"
    },
    {
        "lm_02e",
        "lm_02m",
        "lm_02mo",
        "lm_02i",
        "lm_02p",
        "lm_02b",
        "lm_02ef"
    }
};

}

SEAD_TASK_SINGLETON_DISPOSER_IMPL(LightMapMgr)

LightMapMgr::LightMapMgr(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "LightMapMgr")
    , mIsViewDependent(false)
    , mpCamera(nullptr)
    , mpProjection(nullptr)
    , mpCameraDRC(nullptr)
    , mpProjectionDRC(nullptr)
    , mpAglEnvBinary1(nullptr)
    , mpAglEnvBinary2(nullptr)
    , mOverrideModelLightMap(true)
{
    for (s32 i = 0; i < cLightMapNum; i++)
        mLightMapIndexCourse[i].fill(-1);

    mAmbientLightTypeIndex.fill(-1);
}

LightMapMgr::~LightMapMgr()
{
}

void LightMapMgr::loadAglEnvBinary(void* p_data, s32)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        if (p_data != nullptr)
            mEnvObjMgr.applyResource(p_data);

        for (s32 i = 0; i < cAmbColorType_Num; i++)
            mAmbientLightTypeIndex[i] = mEnvObjMgr.searchTypeIndex<agl::env::AmbientLight>(cAmbColorName[i]);

        if (PtclMgr::instance() != nullptr)
            PtclMgr::instance()->updateAmbientLight();
    }
    sead::Graphics::instance()->unlockDrawContext();
}

void LightMapMgr::loadAglEnvBinary(const sead::SafeString& name, s32 unk, sead::Heap* heap)
{
    loadAglEnvBinary(GfxParameter::instance()->getAglEnvBinary(name, heap), unk);
}

void LightMapMgr::loadAglEnvBinary(const sead::SafeString& name, sead::Heap* heap)
{
    loadAglEnvBinary(name, -1, heap);
}

void LightMapMgr::initializeViewDependent_()
{
    for (s32 i = 0; i < cEnvTypeCourse_Num * cLightMapNum; i++)
        mLightMapMgr.searchIndex(cLightMapNameAll[i]);

    for (s32 i = 0; i < cEnvTypeCourseSelect_Num * cLightMapNum; i++)
        mLightMapMgr.searchIndex(cLightMapNameAll[cEnvTypeCourse_Num * cLightMapNum + i]);

    mIsViewDependent = true;
}

void LightMapMgr::initializeViewDependent(
    const sead::Camera* p_camera, const sead::Projection* p_projection,
    const sead::Camera* p_camera_drc, const sead::Projection* p_projection_drc
)
{
    initializeViewDependent_();
    mpCamera = p_camera;
    mpProjection = p_projection;
    mpCameraDRC = p_camera_drc;
    mpProjectionDRC = p_projection_drc;
}

void LightMapMgr::initializeViewIndependent()
{
    for (s32 i = 0; i < cEnvTypeCourse_Num * cLightMapNum; i++)
        mLightMapMgr.searchIndex(cLightMapNameAll[i]);

    for (s32 i = 0; i < cEnvTypeCourseSelect_Num * cLightMapNum; i++)
        mLightMapMgr.searchIndex(cLightMapNameAll[cEnvTypeCourse_Num * cLightMapNum + i]);

    mIsViewDependent = false;
    mpCamera = nullptr;
    mpProjection = nullptr;
}

void LightMapMgr::loadAglLmapBinary(void* p_data)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        if (p_data != nullptr)
            mLightMapMgr.applyResParameterArchive(p_data);

        for (s32 i = 0; i < cLightMapNumAll; i++)
        {
            agl::lght::LightMap* p_lightmap = mLightMapMgr.getLightMap(i);
            p_lightmap->setLightingHint(2);
            mResTextureData[i].ofsName.set_ptr(p_lightmap->getName().cstr());
            mResTextureData[i].ofsPath.set_ptr("");
            mpResTexture[i] = agl::g3d::TextureUtilG3D::convertToResTexture(&(mResTextureData[i]), p_lightmap->getTextureSampler().getTextureData());
        }

        if (mIsViewDependent)
            initializeViewDependent(mpCamera, mpProjection, mpCameraDRC, mpProjectionDRC);

        else
            initializeViewIndependent();

        for (s32 i = 0; i < cLightMapNum; i++)
            for (s32 j = 0; j < cEnvTypeCourse_Num; j++)
                mLightMapIndexCourse[i][j] = mLightMapMgr.searchIndex(cLightMapNameCourse[i][j]);
    }
    sead::Graphics::instance()->unlockDrawContext();
}

void LightMapMgr::initialize(sead::Heap* heap)
{
    loadAglEnvBinary("system", heap);
    loadAglLmapBinary("system", heap);
}

void LightMapMgr::loadAglLmapBinary(const sead::SafeString& name, sead::Heap* heap)
{
    loadAglLmapBinary(GfxParameter::instance()->getAglLmapBinary(name, heap));
}

void LightMapMgr::prepare()
{
    agl::env::EnvObjMgr::InitArg init_arg;
    init_arg.setContainMax<agl::env::AmbientLight>(cAmbColorType_Num);
    init_arg.setContainMax<agl::env::HemisphereLight>(cHemisphereLightNum);
    init_arg.setContainMax<agl::env::DirectionalLight>(cDirectionalLightNumAll);
    init_arg.setViewMax(cView_Num);

    mEnvObjMgr.initialize(init_arg);
    GfxParameter::instance()->setDelegateForParameter(&mEnvObjMgr);

    for (s32 i = 0; i < cDirectionalLightNumAll; i++)
        mEnvObjMgr.getEnvObj<agl::env::DirectionalLight>(i)->setName(cDirectionalLightNameAll[i]);

    for (s32 i = 0; i < cAmbColorType_Num; i++)
        mEnvObjMgr.getEnvObj<agl::env::AmbientLight>(i)->setName(cAmbColorName[i]);

    static_assert(cLightMapHemisphereLightNum <= cHemisphereLightNum);
    static_assert(cLightMapDirectionalLightNum <= cDirectionalLightNumAll);

    agl::env::EnvObjBuffer::AllocateArg alloc_arg;
    alloc_arg.setContainMax<agl::env::AmbientLight>(1);
    alloc_arg.setContainMax<agl::env::HemisphereLight>(cLightMapHemisphereLightNum);
    alloc_arg.setContainMax<agl::env::DirectionalLight>(cLightMapDirectionalLightNum);

    agl::lght::LightMapMgr::CreateArg create_arg;
    create_arg.setViewMax(cView_Num);
    create_arg.setNum(cLightMapNumAll);

    mLightMapMgr.initialize(alloc_arg, create_arg, &mEnvObjMgr);
    GfxParameter::instance()->setDelegateForParameter(&mLightMapMgr);
    mCalcObj.mpLightMapMgr = &mLightMapMgr;

    for (s32 i = 0; i < cLightMapNumAll; i++)
    {
        agl::lght::LightMap* p_lightmap = mLightMapMgr.getLightMap(i);
        p_lightmap->setLightingHint(2);

        p_lightmap->pushBack(mEnvObjMgr.getEnvObj<agl::env::AmbientLight>(0));

        for (s32 j = 0; j < cLightMapHemisphereLightNum; j++)
            p_lightmap->pushBack(mEnvObjMgr.getEnvObj<agl::env::HemisphereLight>(j));

        if (i < cEnvTypeCourse_Num * cLightMapNum)
            for (s32 j = 0; j < cLightMapDirectionalLightNumCourse; j++)
                p_lightmap->pushBack(mEnvObjMgr.getEnvObj<agl::env::DirectionalLight>(i / cLightMapNum * cLightMapDirectionalLightNumCourse + j));

        else
            p_lightmap->pushBack(mEnvObjMgr.getEnvObj<agl::env::DirectionalLight>(cDirectionalLightNumAll - cEnvTypeCourse_Num * cLightMapNum + i));

        p_lightmap->setName(cLightMapNameAll[i]);
    }

    initialize();
    initializeViewIndependent();
}

void LightMapMgr::enter()
{
    // Reflection
    {
        agl::lyr::Layer* p_layer = agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_ReflectionLightMap);
        mDrawMethodReflection.bind(this, &LightMapMgr::drawReflection_, "LightMapMgr");
        p_layer->pushBackDrawMethod(&mDrawMethodReflection);
    }
    // Main
    {
        agl::lyr::Layer* p_layer = agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_LightMap);
        mDrawMethodMain.bind(this, &LightMapMgr::drawMain_, "LightMapMgr");
        p_layer->pushBackDrawMethod(&mDrawMethodMain);
    }
    // ReflectionDRC
    {
        agl::lyr::Layer* p_layer = agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_ReflectionLightMap_DRC);
        mDrawMethodReflectionDRC.bind(this, &LightMapMgr::drawReflectionDRC_, "LightMapMgr");
        p_layer->pushBackDrawMethod(&mDrawMethodReflectionDRC);
    }
    // MainDRC
    {
        agl::lyr::Layer* p_layer = agl::lyr::Renderer::instance()->getLayer(LayerMgr::cLayer_LightMap_DRC);
        mDrawMethodMainDRC.bind(this, &LightMapMgr::drawMainDRC_, "LightMapMgr");
        p_layer->pushBackDrawMethod(&mDrawMethodMainDRC);
    }
}

void LightMapMgr::calc()
{
    mEnvObjMgr.update();
    mLightMapMgr.update();
}

void LightMapMgr::setModelLightMap(ModelG3d* p_model, bool set_mdl_dl_dirty) const
{
    if (!mOverrideModelLightMap)
        return;

    agl::g3d::ModelEx& model = p_model->getModelEx();

    for (s32 idx_shape = 0, num_shape = model.GetShapeCount(); idx_shape < num_shape; idx_shape++)
    {
        ModelG3d::LightMap& light_map = p_model->getShape(idx_shape).light_map;
        light_map.clear();

        agl::g3d::ModelShaderAssign& shader_assign = model.getShaderAssign(idx_shape);

        s32 idx_material = model.GetShape(idx_shape)->GetMaterialIndex();
        const nw::g3d::MaterialObj* p_material = model.GetMaterial(idx_material);

        s32 num_light_map = 0;

        for (s32 idx_sampler = 0, num_sampler = shader_assign.getSamplerNum(); idx_sampler < num_sampler; idx_sampler++)
        {
            const nw::g3d::res::ResSampler* p_res_sampler = shader_assign.getResSampler(idx_sampler);
            if (p_res_sampler)
            {
                const nw::g3d::res::ResTexture* p_res_texture = p_material->GetResTexture(p_res_sampler->GetIndex());
                if (p_res_texture)
                {
                    s32 idx_lghtmap = mLightMapMgr.searchIndex(p_res_texture->GetName());
                    if (idx_lghtmap >= 0)
                    {
                        light_map.idx_lghtmap[num_light_map] = idx_lghtmap;
                        light_map.idx_sampler[num_light_map] = idx_sampler;

                        if (++num_light_map >= cLightMapNum)
                            break;
                    }
                }
            }
        }
    }

    if (set_mdl_dl_dirty)
        p_model->setDisplayListDirty();
}

void LightMapMgr::loadAglEnvBinaryWithType(const sead::SafeString& name, const sead::SafeString& type, sead::Heap* heap)
{
    loadAglEnvBinary(name, -1, heap);
}

void LightMapMgr::initializeForCourseSelect(sead::Heap* heap)
{
    loadAglEnvBinary("system", heap);

    for (s32 i = 0; i < sEnvTypeCourseSelectNum; i++)
    {
        const sead::SafeString& name = cEnvTypeNameCourseSelect[i];
        if (name != "CS_W8a")
            loadAglEnvBinaryWithType(name, name, heap);

        else
        {
            void* ptr = GfxParameter::instance()->getAglEnvBinary(name, heap);
            loadAglEnvBinary(ptr);
            mpAglEnvBinary1 = ptr;
        }
    }

    loadAglEnvBinaryWithType("CS_W8a_DarkCloud", "DV", heap);
    loadAglLmapBinary(GfxParameter::instance()->getAglLmapBinary("CS_All", heap));
    mpAglEnvBinary2 = GfxParameter::instance()->getAglEnvBinary("CS_W8a_demo", heap);
}

void LightMapMgr::loadAglEnvBinaryWithLerpForCourseSelect(f32 t)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        if (mpAglEnvBinary1 != nullptr && mpAglEnvBinary2 != nullptr)
            mEnvObjMgr.applyResourceLerp(mpAglEnvBinary1, mpAglEnvBinary2, t);

        for (s32 i = 0; i < cAmbColorType_Num; i++)
            mAmbientLightTypeIndex[i] = mEnvObjMgr.searchTypeIndex<agl::env::AmbientLight>(cAmbColorName[i]);

        if (PtclMgr::instance() != nullptr)
            PtclMgr::instance()->updateAmbientLight();
    }
    sead::Graphics::instance()->unlockDrawContext();
}

const agl::TextureSampler& LightMapMgr::getLightmap1(EnvTypeCourse type) const
{
    return mLightMapMgr.getLightMap(mLightMapIndexCourse[0][type])->getTextureSampler();
}

const agl::TextureSampler& LightMapMgr::getLightmap2(EnvTypeCourse type) const
{
    const agl::lght::LightMap* p_lightmap = mLightMapMgr.getLightMap(mLightMapIndexCourse[1][type]);
    return p_lightmap->getTextureSampler();
}

void LightMapMgr::getAmbColor(sead::Color4f* p_color, AmbColorType type) const
{
    s32 index = mAmbientLightTypeIndex[type];
    if (index >= 0)
        *p_color = mEnvObjMgr.getEnvObj<agl::env::AmbientLight>(index)->getColor();
    else
        p_color->setf(1.0f, 1.0f, 1.0f, 1.0f);
}

void LightMapMgr::setModelLightMapWithName_(ModelG3d* p_model, const sead::SafeString& name, s32 idx_lghtmap, s32 model_light_map_index) const
{
    agl::g3d::ModelEx& model = p_model->getModelEx();

    for (s32 idx_shape = 0, num_shape = model.GetShapeCount(); idx_shape < num_shape; idx_shape++)
    {
        ModelG3d::LightMap& light_map = p_model->getShape(idx_shape).light_map;

        agl::g3d::ModelShaderAssign& shader_assign = model.getShaderAssign(idx_shape);

        s32 idx_material = model.GetShape(idx_shape)->GetMaterialIndex();
        const nw::g3d::MaterialObj* p_material = model.GetMaterial(idx_material);

        for (s32 idx_sampler = 0, num_sampler = shader_assign.getSamplerNum(); idx_sampler < num_sampler; idx_sampler++)
        {
            const nw::g3d::res::ResSampler* p_res_sampler = shader_assign.getResSampler(idx_sampler);
            if (p_res_sampler)
            {
                const nw::g3d::res::ResTexture* p_res_texture = p_material->GetResTexture(p_res_sampler->GetIndex());
                if (p_res_texture)
                {
                    if (name == p_res_texture->GetName())
                    {
                        light_map.idx_lghtmap[model_light_map_index] = idx_lghtmap;
                        light_map.idx_sampler[model_light_map_index] = idx_sampler;
                    }
                }
            }
        }
    }
}

void LightMapMgr::setCobModelLightMapForCourseSelect(ModelG3d* p_model, u8 world, u8 world_sub_letter) const
{
    sead::FixedSafeString<64> name;
    {
        name.format("lmDifCSW%u%c", 1 + world, 'a' + world_sub_letter);
        s32 idx_lghtmap = mLightMapMgr.searchIndex(name);
        if (idx_lghtmap >= 0)
            setModelLightMapWithName_(p_model, "lmDifCob", idx_lghtmap, 0);
    }
    {
        name.format("lmSpcCSW%u%c", 1 + world, 'a' + world_sub_letter);
        s32 idx_lghtmap = mLightMapMgr.searchIndex(name);
        if (idx_lghtmap >= 0)
            setModelLightMapWithName_(p_model, "lmSpcCob", idx_lghtmap, 1);
    }
    p_model->setDisplayListDirty();
}

void LightMapMgr::setModelLightMapForCourseSelect(ModelG3d* p_model) const
{
    {
        s32 idx_lghtmap = mLightMapMgr.searchIndex("lm_01mo");
        if (idx_lghtmap >= 0)
            setModelLightMapWithName_(p_model, "lmDifCob", idx_lghtmap, 0);
    }
    {
        s32 idx_lghtmap = mLightMapMgr.searchIndex("lm_02mo");
        if (idx_lghtmap >= 0)
            setModelLightMapWithName_(p_model, "lmSpcCob", idx_lghtmap, 1);
    }
    p_model->setDisplayListDirty();
}

const sead::SafeString& LightMapMgr::getEnvTypeCourseStr(EnvTypeCourse type) const
{
    return cEnvTypeNameCourse[type];
}

void LightMapMgr::draw_(const agl::lyr::RenderInfo& render_info, View view, bool view_dependent, const sead::Matrix34f* p_view_mtx, const sead::Projection* p_projection)
{
    switch (render_info.getRenderStep())
    {
    default:
        break;
    case cRenderStep_CalcView:
        if (!view_dependent || p_view_mtx == nullptr || p_projection == nullptr)
        {
            sead::DirectCamera camera; camera.setMatrix(sead::Matrix34f::ident);
            sead::OrthoProjection projection(0.0f, 1000.0f, 1.0f, -1.0f, -1.0f, 1.0f);
            mEnvObjMgr.updateView(camera.getViewMatrix(), projection.getDeviceProjectionMatrix(), view);
        }
        else
        {
            mEnvObjMgr.updateView(*p_view_mtx, p_projection->getDeviceProjectionMatrix(), view);
        }
        break;
    case cRenderStep_UpdateGPUBuffer:
        if (view == cView_Main)
            mLightMapMgr.updateGPU();
        if (!view_dependent || p_view_mtx == nullptr || p_projection == nullptr)
            mLightMapMgr.updateViewGPU(view, true, sead::Matrix34f::ident);
        else
            mLightMapMgr.updateViewGPU(view, true, *p_view_mtx);
        break;
    case cRenderStep_LightDraw:
        mLightMapMgr.draw(view, true, agl::cShaderMode_UniformRegister);
        agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
        render_info.getRenderBuffer()->bind();
        render_info.getViewport()->apply(*render_info.getRenderBuffer());
        break;
    }
}

void LightMapMgr::drawMain_(const agl::lyr::RenderInfo& render_info)
{
    draw_(render_info, cView_Main, mIsViewDependent, &mpCamera->getViewMatrix(), mpProjection);
}

void LightMapMgr::drawMainDRC_(const agl::lyr::RenderInfo& render_info)
{
    draw_(render_info, cView_MainDRC, mIsViewDependent, &mpCameraDRC->getViewMatrix(), mpProjectionDRC);
}

/*
TODO: Too lazy to add ReflectionRenderObjLayer

void LightMapMgr::drawReflection_(const agl::lyr::RenderInfo& render_info);

void LightMapMgr::drawReflectionDRC_(const agl::lyr::RenderInfo& render_info);
*/

void LightMapMgr::CalcObj::calc()
{
    mpLightMapMgr->updateGPU();
}
