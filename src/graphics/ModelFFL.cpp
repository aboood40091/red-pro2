#include <graphics/Mii_CentralMgr.h>
#include <graphics/Mii_SlotMgr.h>
#include <graphics/ModelFFL.h>

#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>

namespace {

static const rio::Color4f cExLightRegColorDefault {
    0.0f, 0.0f, 0.0f, 0.0f
};

static const rio::Color4f cExDarkRegColorDefault {
    1.0f, 1.0f, 1.0f, 1.0f
};

}

ModelFFL::ModelFFL()
    : mCharModelDesc()
    , mMtxRT(rio::Matrix34f::ident)
    , mScale { 1.0f, 1.0f, 1.0f }
    , mMtxSRT(rio::Matrix34f::ident)
    , mLightmap01p(nullptr)
    , mLightmap02p(nullptr)
    , mLightMapType(cLightmapType_LightMapMgr_Index_4)
    , mDrawOpaWithXlu(0)
    , mInitializeStep(cInitializeStep_NeedInitializeCpu)
    , mDrawType(cDrawType_Normal)
{
    initExRegColor();
}

void ModelFFL::initialize(const FFLCharModelDesc* p_desc, const rio::Vector3f& scale)
{
    mCharModelDesc = *p_desc;
    mScale = scale;
}

bool ModelFFL::initialize(Mii::DataSource source, const FFLCharModelDesc* p_desc, const rio::Vector3f& scale)
{
    mDataSource = source;

    FFLStoreData store_data;
    if (!Mii::SlotMgr::getStoreData(&store_data, mDataSource))
        return false;

    InitArgStoreData arg;
    arg.desc = *p_desc;
    arg.data = &store_data;
    arg.index = 0;

    initialize(arg, scale);
    return true;
}

void ModelFFL::destroy()
{
    FFLDeleteCharModel(&mCharModel);
}

void ModelFFL::initExRegColor()
{
    setExRegColor(cExLightRegColorDefault, cExDarkRegColorDefault);
}

void ModelFFL::setExRegColor(const rio::Color4f& light, const rio::Color4f& dark)
{
    mExLightRegColor = light;
    mExDarkRegColor = dark;
}

void ModelFFL::updateMtxSRT()
{
    mMtxSRT = mMtxRT;

    reinterpret_cast<rio::Vector3f&>(mMtxSRT.v[0].x) *= mScale;
    reinterpret_cast<rio::Vector3f&>(mMtxSRT.v[1].x) *= mScale;
    reinterpret_cast<rio::Vector3f&>(mMtxSRT.v[2].x) *= mScale;
}

void ModelFFL::setSpecialDrawType()
{
    mDrawType = cDrawType_Special;
}

void ModelFFL::calc()
{
}

void ModelFFL::updateView(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void ModelFFL::calcGPU(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void ModelFFL::drawOpa(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mDrawOpaWithXlu)
        return;

    setEnvViewUniformWithLightmapEnable_(mMtxSRT, view_mtx, proj_mtx, p_render_mgr);

    if (mDrawType == cDrawType_Special)
        drawOpaSpecial_();
    else
        drawOpaNormal_();
}

void ModelFFL::drawXlu(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    setEnvViewUniformWithLightmapEnable_(mMtxSRT, view_mtx, proj_mtx, p_render_mgr);

    if (mDrawOpaWithXlu)
    {
        if (mDrawType == cDrawType_Special)
            drawOpaSpecial_();
        else
            drawOpaNormal_();
    }

    if (mDrawType == cDrawType_Special)
    {
        drawXluSpecial_();
        mDrawType = cDrawType_Normal;
    }
    else
    {
        drawXluNormal_();
    }

}

bool ModelFFL::getAdditionalInfo(FFLAdditionalInfo* p_additional_info, BOOL checkFontRegion) const
{
    const void* data = mCharModelSource.pBuffer;
    u16 index = mCharModelSource.index;
    FFLDataSource source = mCharModelSource.dataSource;

    FFLStoreData store_data;

    switch (mDataSource.getType())
    {
    case Mii::DataSource::cType_StoreData_Save:
    case Mii::DataSource::cType_StoreData_Custom:
    case Mii::DataSource::cType_StoreData_Account:
        if (!Mii::SlotMgr::getStoreData(&store_data, mDataSource))
            return false;

        source = FFL_DATA_SOURCE_STORE_DATA;
        data = &store_data;
        index = 0;
        break;
    default:
        break;
    }

    if (FFLGetAdditionalInfo(p_additional_info, source, data, index, checkFontRegion) == FFL_RESULT_OK)
        return true;

    return false;
}

rio::Color4f ModelFFL::getFavoriteColor() const
{
    rio::Color4f color;

    FFLAdditionalInfo additional_info;
    if (!getAdditionalInfo(&additional_info, false))
    {
        rio::Color4f color = rio::Color4f::cBlack;
        return color;
    }

    const FFLColor& ffl_color = FFLGetFavoriteColor(additional_info.favoriteColor);
    color.r = ffl_color.r;
    color.g = ffl_color.g;
    color.b = ffl_color.b;
    color.a = ffl_color.a;
    return color;
}

bool ModelFFL::initializeCpu(const FFLCharModelSource* p_source, const FFLCharModelDesc* p_desc)
{
    bool ret = true;

    if (mInitializeStep == cInitializeStep_NeedInitializeCpu)
    {
        ret = initializeCpu_(p_source, p_desc);
        if (ret)
            mInitializeStep = cInitializeStep_NeedInitializeGpu;
    }

    return ret;
}

void ModelFFL::initializeGpu()
{
    if (mInitializeStep == cInitializeStep_NeedInitializeGpu)
    {
        initializeGpu_();
        rio::Window::instance()->makeContextCurrent();
        mInitializeStep = cInitializeStep_Done;
    }
}

void ModelFFL::setEnvUniform_(RenderMgr* p_render_mgr)
{
    Mii::CentralMgr::instance()->getShader().activate();
    Mii::CentralMgr::instance()->getShader().setExRegColorUniform(&mExLightRegColor);
    Mii::CentralMgr::instance()->getShader().setModel(this);
    Mii::CentralMgr::instance()->getShader().setFogUniform(p_render_mgr);
}

void ModelFFL::setEnvViewUniform_(const rio::Matrix34f& model_mtx, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    setEnvUniform_(p_render_mgr);
    Mii::CentralMgr::instance()->getShader().setViewUniform(model_mtx, view_mtx, proj_mtx);
}

void ModelFFL::setEnvViewUniformWithLightmapEnable_(const rio::Matrix34f& model_mtx, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    setEnvViewUniform_(model_mtx, view_mtx, proj_mtx, p_render_mgr);
    Mii::CentralMgr::instance()->getShader().setLightmapEnableUniform(true);
}

void ModelFFL::drawOpaNormal_()
{
    rio::RenderState render_state;
    render_state.setDepthEnable(true, true);
    render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_LEQUAL);
    render_state.applyDepthAndStencilTest();
#if RIO_IS_CAFE
    GX2SetAlphaTest(GX2_ENABLE, GX2_COMPARE_GREATER, 0.0f);
#else
  //render_state.setAlphaTestEnable(true);  // TODO: Does disabling this cause problems?
  //render_state.applyAlphaTest();          // ^^^
#endif // RIO_IS_CAFE
    render_state.setBlendEnable(false);
    render_state.setBlendFactor(rio::Graphics::BLEND_MODE_ONE, rio::Graphics::BLEND_MODE_ZERO);
    render_state.applyBlendAndFastZ();

    FFLDrawOpa(&mCharModel);
}

void ModelFFL::drawOpaSpecial_()
{
    rio::RenderState render_state;
    render_state.setDepthEnable(true, true);
    render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_LEQUAL);
    render_state.setBlendEnable(false);
    render_state.setColorMask(true, true, true, true);
    render_state.apply();

    FFLDrawOpa(&mCharModel);
}

void ModelFFL::drawXluNormal_()
{
    rio::RenderState render_state;
    render_state.setDepthEnable(true, false);
    render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_LEQUAL);
    render_state.applyDepthAndStencilTest();
#if RIO_IS_CAFE
    GX2SetAlphaTest(GX2_ENABLE, GX2_COMPARE_GREATER, 0.0f);
#else
  //render_state.setAlphaTestEnable(true);  // TODO: Does disabling this cause problems?
  //render_state.applyAlphaTest();          // ^^^
#endif // RIO_IS_CAFE
    render_state.setBlendEnable(true);
    render_state.setBlendFactor(rio::Graphics::BLEND_MODE_SRC_ALPHA, rio::Graphics::BLEND_MODE_ONE_MINUS_SRC_ALPHA);
    render_state.applyBlendAndFastZ();

    FFLDrawXlu(&mCharModel);
}

void ModelFFL::drawXluSpecial_()
{
    {
        rio::RenderState render_state;
        render_state.setDepthEnable(true, false);
        render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_LEQUAL);
        render_state.setBlendEnable(true);
        render_state.setBlendFactorSrcRGB(rio::Graphics::BLEND_MODE_SRC_ALPHA);
        render_state.setBlendFactorDstRGB(rio::Graphics::BLEND_MODE_ONE_MINUS_SRC_ALPHA);
        render_state.setBlendEquation(rio::Graphics::BLEND_FUNC_ADD);
      //render_state.setAlphaTestEnable(true);  // TODO: Does disabling this cause problems?
        render_state.setColorMask(true, true, true, false);
        render_state.apply();

#if RIO_IS_CAFE
        GX2SetAlphaTest(GX2_ENABLE, GX2_COMPARE_GREATER, 0.0f);
#endif // RIO_IS_CAFE

        FFLDrawXlu(&mCharModel);
    }

    {
        rio::RenderState render_state;
        render_state.setDepthEnable(true, true);
        render_state.setDepthFunc(rio::Graphics::COMPARE_FUNC_LEQUAL);
        render_state.setBlendEnable(true);
        render_state.setBlendFactorSrcRGB(rio::Graphics::BLEND_MODE_ONE_MINUS_DST_ALPHA);
        render_state.setBlendFactorDstRGB(rio::Graphics::BLEND_MODE_DST_ALPHA);
        render_state.setBlendFactorSrcAlpha(rio::Graphics::BLEND_MODE_ONE);
        render_state.setBlendFactorDstAlpha(rio::Graphics::BLEND_MODE_ONE);
        render_state.setBlendEquation(rio::Graphics::BLEND_FUNC_ADD);
      //render_state.setAlphaTestEnable(true);  // TODO: Does disabling this cause problems?
        render_state.setColorMask(true, true, true, true);
        render_state.apply();

#if RIO_IS_CAFE
        GX2SetAlphaTest(GX2_ENABLE, GX2_COMPARE_GREATER, 0.0f);
#endif // RIO_IS_CAFE

        FFLDrawXlu(&mCharModel);
    }
}

bool ModelFFL::initializeCpu_(const FFLCharModelSource* p_source, const FFLCharModelDesc* p_desc)
{
    RIO_LOG("Well then...\n");
    return FFLInitCharModelCPUStep(&mCharModel, p_source, p_desc) == FFL_RESULT_OK;
}

void ModelFFL::initializeGpu_()
{
    Mii::CentralMgr::instance()->getShader().activate();
    Mii::CentralMgr::instance()->getShader().setExRegColorUniform(&mExLightRegColor);
    Mii::CentralMgr::instance()->getShader().setModel(this);
    Mii::CentralMgr::instance()->getShader().setLightmapEnableUniform(false);

    FFLInitCharModelGPUStep(&mCharModel);
}

bool ModelFFL::setCharModelSource_(const FFLStoreData* p_store_data, u16)
{
    switch (mDataSource.getType())
    {
    case Mii::DataSource::cType_Database_Default:
        mCharModelSource.dataSource = FFL_DATA_SOURCE_DEFAULT;
        mCharModelSource.pBuffer = nullptr;
        mCharModelSource.index = mDataSource.getIndex();
        break;
    case Mii::DataSource::cType_Database_Official:
        mCharModelSource.dataSource = FFL_DATA_SOURCE_OFFICIAL;
        mCharModelSource.pBuffer = NULL;
        mCharModelSource.index = mDataSource.getIndex();
        break;
    default:
        mCharModelSource.dataSource = FFL_DATA_SOURCE_STORE_DATA;
        mCharModelSource.pBuffer = p_store_data;
        mCharModelSource.index = 0;
        break;
    }

    return initializeCpu(&mCharModelSource, &mCharModelDesc);
}

bool ModelFFL::setCharModelSource_(const FFLMiddleDB* p_middle_db, u16 index)
{
    mCharModelSource.pBuffer = p_middle_db;
    mCharModelSource.index = index;
    mCharModelSource.dataSource = FFL_DATA_SOURCE_MIDDLE_DB;

    return initializeCpu(&mCharModelSource, &mCharModelDesc);
}

void ModelFFL::pushBackModelGpuInitializer_()
{
    Mii::CentralMgr::instance()->getModelGpuInitializer().pushBack(this);
}
