#pragma once

#include <graphics/Mii_DataSource.h>
#include <graphics/RenderObj.h>

#include <common/aglTextureData.h>
#include <gfx/rio_Color.h>

#include <nn/ffl.h>

class ModelFFL : public RenderObj
{
public:
    enum LightMapType
    {
        cLightmapType_Custom = 0,
        cLightmapType_LightMapMgr_Index_4,
        cLightmapType_LightMapMgr_Index_0
    };
    static_assert(sizeof(LightMapType) == 4);

    enum InitializeStep
    {
        cInitializeStep_NeedInitializeCpu = 0,
        cInitializeStep_NeedInitializeGpu,
        cInitializeStep_Done
    };
    static_assert(sizeof(InitializeStep) == 4);

    enum DrawType
    {
        cDrawType_Normal = 0,
        cDrawType_Special
    };
    static_assert(sizeof(DrawType) == 4);

    template <typename T>
    struct InitArg
    {
        FFLCharModelDesc    desc;
        const T*            data;
        u16                 index;
    };

    typedef InitArg<FFLStoreData>   InitArgStoreData;
    typedef InitArg<FFLMiddleDB>    InitArgMiddleDB;

    static_assert(sizeof(InitArgStoreData) == 0x1C);
    static_assert(sizeof(InitArgMiddleDB) == 0x1C);

public:
    ModelFFL();

    virtual ~ModelFFL()
    {
        destroy();
    }

    void initialize(const FFLCharModelDesc* p_desc, const rio::Vector3f& scale);
    bool initialize(Mii::DataSource source, const FFLCharModelDesc* p_desc, const rio::Vector3f& scale);

    template <typename T>
    bool initialize(const InitArg<T>& arg, const rio::Vector3f& scale);

    void destroy();

    void initExRegColor();
    void setExRegColor(const rio::Color4f& light, const rio::Color4f& dark);

    void updateMtxSRT();

    void setSpecialDrawType();

    void calc() override;
    void updateView(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) override;
    void calcGPU(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) override;
    void drawOpa(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) override;
    void drawXlu(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr) override;

    bool getAdditionalInfo(FFLAdditionalInfo* p_additional_info, BOOL checkFontRegion) const;
    rio::Color4f getFavoriteColor() const;

    bool initializeCpu(const FFLCharModelSource* p_source, const FFLCharModelDesc* p_desc);
    void initializeGpu();

    const rio::Matrix34f& getMtxRT() const
    {
        return mMtxRT;
    }

    void setMtxRT(const rio::Matrix34f& mtx)
    {
        mMtxRT = mtx;
        updateMtxSRT();
    }

    const rio::Vector3f& getScale() const
    {
        return mScale;
    }

    void setScale(const rio::Vector3f& scale)
    {
        mScale = scale;
        updateMtxSRT();
    }

    agl::TextureData* getLightmap01p() const
    {
        return mLightmap01p;
    }

    void setLightmap01p(agl::TextureData* p_texture_data)
    {
        mLightmap01p = p_texture_data;
    }

    agl::TextureData* getLightmap02p() const
    {
        return mLightmap02p;
    }

    void setLightmap02p(agl::TextureData* p_texture_data)
    {
        mLightmap02p = p_texture_data;
    }

    LightMapType getLightMapType() const
    {
        return mLightMapType;
    }

    void setLightMapType(LightMapType type)
    {
        mLightMapType = type;
    }

private:
    void setEnvUniform_(RenderMgr* p_render_mgr);
    void setEnvViewUniform_(const rio::Matrix34f& model_mtx, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr);
    void setEnvViewUniformWithLightmapEnable_(const rio::Matrix34f& model_mtx, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx, RenderMgr* p_render_mgr);

    void drawOpaNormal_();
    void drawOpaSpecial_();

    void drawXluNormal_();
    void drawXluSpecial_();

    bool initializeCpu_(const FFLCharModelSource* p_source, const FFLCharModelDesc* p_desc);
    void initializeGpu_();

    bool setCharModelSource_(const FFLStoreData* p_store_data, u16);
    bool setCharModelSource_(const FFLMiddleDB* p_middle_db, u16 index);

    void pushBackModelGpuInitializer_();

private:
    FFLCharModel        mCharModel;
    FFLCharModelBuffer  mCharModelBuffer;
    FFLCharModelDesc    mCharModelDesc;
    FFLCharModelSource  mCharModelSource;
    rio::Matrix34f      mMtxRT;
    rio::Vector3f       mScale;
    rio::Matrix34f      mMtxSRT;
    rio::Color4f        mExLightRegColor;
    rio::Color4f        mExDarkRegColor;
    agl::TextureData*   mLightmap01p;
    agl::TextureData*   mLightmap02p;
    LightMapType        mLightMapType;
    bool                mDrawOpaWithXlu;
    InitializeStep      mInitializeStep;
    DrawType            mDrawType;
    Mii::DataSource     mDataSource;
};
//static_assert(sizeof(ModelFFL) == 0x8F0);

template <typename T>
bool ModelFFL::initialize(const InitArg<T>& arg, const rio::Vector3f& scale)
{
    initialize(&arg.desc, scale);

    if (!setCharModelSource_(arg.data, arg.index))
        return false;

    pushBackModelGpuInitializer_();
    return true;
}
