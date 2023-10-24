#include <graphics/Mii_CentralMgr.h>
#include <graphics/ModelFFL.h>

#include <gfx/seadGraphicsContext.h>
#include <gfx/cafe/seadGraphicsCafe.h>
#include <heap/seadHeap.h>
#include <heap/seadHeapMgr.h>

namespace {

static const sead::Color4f cExLightRegColorDefault(
    0.0f, 0.0f, 0.0f, 0.0f
);

static const sead::Color4f cExDarkRegColorDefault(
    1.0f, 1.0f, 1.0f, 1.0f
);

}

ModelFFL::ModelFFL(s32 opa_buffer_idx, s32 xlu_buffer_idx)
    : mpHeap(nullptr)
    , mpHeapTmp(nullptr)
    , _814(0)
    , mMtxRT(sead::Matrix34f::ident)
    , mScale(sead::Vector3f::ones)
    , mMtxSRT(sead::Matrix34f::ident)
    , mLightmap02p_0(nullptr)
    , mLightmap02p_1(nullptr)
    , mLightmap02pType(cLightmap02pType_LightMapMgr)
    , mLightMapType(cLightmapType_LightMapMgr_Index_4)
    , mDrawOpaWithXlu(0)
    , mInitializeStep(cInitializeStep_NeedInitializeCpu)
    , mDrawType(cDrawType_Normal)
    , mpWmModeDBModel(nullptr)
    , mOpaBufferIdx(opa_buffer_idx)
    , mXluBufferIdx(xlu_buffer_idx)
{
    initExRegColor();
}

bool ModelFFL::initialize(const FFLCharModelDesc* p_desc, const sead::Vector3f& scale, sead::Heap* heap, sead::Heap* heap_tmp)
{
    mpHeap = heap;
    if (mpHeap == nullptr)
        mpHeap = sead::HeapMgr::instance()->getCurrentHeap();

    mpHeapTmp = heap_tmp;
    if (mpHeapTmp == nullptr)
        mpHeapTmp = mpHeap;

    mCharModelDesc = *p_desc;
    mScale.set(scale);

    return allocBuffer_();
}

bool ModelFFL::initialize(Mii::SlotID id, const FFLCharModelDesc* p_desc, const sead::Vector3f& scale, sead::Heap* heap, sead::Heap* heap_tmp)
{
    mSlotID = id;

    FFLStoreData store_data;
    if (!Mii::SlotMgr::getStoreData(&store_data, mSlotID))
        return false;

    InitArgStoreData arg;
    arg.desc = *p_desc;
    arg.data = &store_data;
    arg.index = 0;

    if (!initialize(arg, scale, heap, heap_tmp))
        return false;

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

void ModelFFL::setExRegColor(const sead::Color4f& light, const sead::Color4f& dark)
{
    mExLightRegColor = light;
    mExDarkRegColor = dark;
}

void ModelFFL::updateMtxSRT()
{
    sead::Vector3f scale = mScale;  // ???

    mMtxSRT = mMtxRT;
    mMtxSRT.scaleBases(scale.x, scale.y, scale.z);
}

void ModelFFL::setSpecialDrawType()
{
    mDrawType = cDrawType_Special;
}

void ModelFFL::calc()
{
}

void ModelFFL::updateView(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void ModelFFL::calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void ModelFFL::drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mDrawOpaWithXlu)
        return;

    setEnvViewUniformWithLightmapEnable_(mMtxSRT, view_mtx, proj_mtx, p_render_mgr);

    if (mDrawType == cDrawType_Special)
        drawOpaSpecial_();
    else
        drawOpaNormal_();
}

void ModelFFL::drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
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

    switch (mSlotID.getType())
    {
    case 2:
    case 3:
    case 4:
        if (!Mii::SlotMgr::getStoreData(&store_data, mSlotID))
            return false;

        source = FFL_DATA_SOURCE_STORE_DATA;
        data = &store_data;
        index = 0;
        break;
    }

    if (FFLGetAdditionalInfo(p_additional_info, source, data, index, checkFontRegion) == FFL_RESULT_OK)
        return true;

    return false;
}

sead::Color4f ModelFFL::getFavoriteColor() const
{
    sead::Color4f color;

    FFLAdditionalInfo additional_info;
    if (!getAdditionalInfo(&additional_info, false))
    {
        sead::Color4f color = sead::Color4f::cBlack;
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
        GX2SetContextState(sead::GraphicsCafe::instance()->getGX2ContextState());
        mInitializeStep = cInitializeStep_Done;
    }
}

bool ModelFFL::allocBuffer_()
{
    u32 size = FFLGetBufferSizeCharModel(&mCharModelDesc);
    void* p_buffer = mpHeap->tryAlloc(size, 4);
    if (p_buffer == nullptr)
        return false;

    mCharModelBuffer.pBuffer = p_buffer;
    mCharModelBuffer.bufferSize = size;

    size = FFLGetTempBufferSizeCharModel(&mCharModelDesc);
    p_buffer = mpHeapTmp->tryAlloc(size, 4);
    if (p_buffer == nullptr)
        return false;

    mCharModelBuffer.pTempBuffer = p_buffer;
    mCharModelBuffer.tempBufferSize = size;

    return true;
}

void ModelFFL::setEnvUniform_(RenderMgr* p_render_mgr)
{
    Mii::CentralMgr::instance()->getShader().activate();
    Mii::CentralMgr::instance()->getShader().setExRegColorUniform(&mExLightRegColor);
    Mii::CentralMgr::instance()->getShader().setModel(this);
    Mii::CentralMgr::instance()->getShader().setFogUniform(p_render_mgr);
}

void ModelFFL::setEnvViewUniform_(const sead::Matrix34f& model_mtx, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    setEnvUniform_(p_render_mgr);
    Mii::CentralMgr::instance()->getShader().setViewUniform(model_mtx, view_mtx, proj_mtx);
}

void ModelFFL::setEnvViewUniformWithLightmapEnable_(const sead::Matrix34f& model_mtx, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    setEnvViewUniform_(model_mtx, view_mtx, proj_mtx, p_render_mgr);
    Mii::CentralMgr::instance()->getShader().setLightmapEnableUniform(true);
}

void ModelFFL::drawOpaNormal_()
{
    sead::Graphics::instance()->setDepthEnable(true, true);
    sead::Graphics::instance()->setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    sead::Graphics::instance()->setAlphaTestEnable(true);
    sead::Graphics::instance()->setBlendEnable(false);

    GX2SetBlendControl(
        GX2_RENDER_TARGET_0,

        GX2_BLEND_ONE,
        GX2_BLEND_ZERO,
        GX2_BLEND_COMBINE_ADD,

        GX2_DISABLE,

        GX2_BLEND_ONE,
        GX2_BLEND_ZERO,
        GX2_BLEND_COMBINE_ADD
    );

    FFLDrawOpa(&mCharModel);
}

void ModelFFL::drawOpaSpecial_()
{
    sead::GraphicsContext context;
    context.setDepthEnable(true, true);
    context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    context.setBlendEnable(false);
    context.setColorMask(true, true, true, true);
    context.apply();

    FFLDrawOpa(&mCharModel);
}

void ModelFFL::drawXluNormal_()
{
    sead::Graphics::instance()->setDepthEnable(true, false);
    sead::Graphics::instance()->setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    sead::Graphics::instance()->setAlphaTestEnable(true);
    sead::Graphics::instance()->setBlendEnable(true);

    GX2SetBlendControl(
        GX2_RENDER_TARGET_0,

        GX2_BLEND_SRC_ALPHA,
        GX2_BLEND_ONE_MINUS_SRC_ALPHA,
        GX2_BLEND_COMBINE_ADD,
        
        GX2_DISABLE,

        GX2_BLEND_SRC_ALPHA,
        GX2_BLEND_ZERO,
        GX2_BLEND_COMBINE_ADD
    );

    FFLDrawXlu(&mCharModel);
}

void ModelFFL::drawXluSpecial_()
{
    {
        sead::GraphicsContext context;
        context.setDepthEnable(true, false);
        context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
        context.setBlendEnable(true);
        context.setBlendFactorSrcRGB(sead::Graphics::cBlendFactor_SrcAlpha);
        context.setBlendFactorDstRGB(sead::Graphics::cBlendFactor_InvSrcAlpha);
        context.setBlendEquation(sead::Graphics::cBlendEquation_Add);
        context.setAlphaTestEnable(true);
        context.setColorMask(true, true, true, false);
        context.apply();

        FFLDrawXlu(&mCharModel);
    }

    {
        sead::GraphicsContext context;
        context.setDepthEnable(true, true);
        context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
        context.setBlendEnable(true);
        context.setBlendFactorSrcRGB(sead::Graphics::cBlendFactor_InvDstAlpha);
        context.setBlendFactorDstRGB(sead::Graphics::cBlendFactor_DstAlpha);
        context.setBlendFactorSrcAlpha(sead::Graphics::cBlendFactor_One);
        context.setBlendFactorDstAlpha(sead::Graphics::cBlendFactor_One);
        context.setBlendEquation(sead::Graphics::cBlendEquation_Add);
        context.setAlphaTestEnable(true);
        context.setColorMask(true, true, true, true);
        context.apply();

        FFLDrawXlu(&mCharModel);
    }
}

bool ModelFFL::initializeCpu_(const FFLCharModelSource* p_source, const FFLCharModelDesc* p_desc)
{
    return FFLInitCharModelCPUStep(&mCharModel, p_source, p_desc, &mCharModelBuffer) == FFL_RESULT_OK;
}

void ModelFFL::initializeGpu_()
{
    Mii::CentralMgr::instance()->getShader().activate();
    Mii::CentralMgr::instance()->getShader().setExRegColorUniform(&mExLightRegColor);
    Mii::CentralMgr::instance()->getShader().setModel(this);
    Mii::CentralMgr::instance()->getShader().setLightmapEnableUniform(false);

    FFLInitCharModelGPUStep(&mCharModel);
}

bool ModelFFL::setCharModelSource_(const FFLStoreData* p_store_data)
{
    switch (mSlotID.getType())
    {
    case 0:
        mCharModelSource.dataSource = FFL_DATA_SOURCE_DEFAULT;
        mCharModelSource.pBuffer = nullptr;
        mCharModelSource.index = mSlotID.getSlotNo();
        break;
    case 1:
        mCharModelSource.dataSource = FFL_DATA_SOURCE_OFFICIAL;
        mCharModelSource.pBuffer = NULL;
        mCharModelSource.index = mSlotID.getSlotNo();
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
