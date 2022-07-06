#pragma once

#include <graphics/RenderObj.h>
#include <graphics/ResArchive.h>

#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <g3d/aglModelEx.h>
#include <math/seadBoundBox.h>

#include <nw/g3d/g3d_SkeletalAnimObj.h>
#include <nw/g3d/g3d_ShapeObj.h>

#define override

#include <graphics/MaterialEx.h>

#include <graphics/SkeletalAnimation.h>
#include <graphics/TexPatternAnimation.h>
#include <graphics/ShaderParamAnimation.h>
#include <graphics/VisibilityAnimation.h>
#include <graphics/ShapeAnimation.h>

class RenderObjEx : public RenderObj
{
    SEAD_RTTI_OVERRIDE(RenderObjEx, RenderObj)

public:
    struct ShaderAssign
    {
        void initialize(agl::ShaderProgram* p_shader_program)
        {
            this->p_shader_program = p_shader_program;

            env_location.setName("MdlEnvView");
            mtx_location.setName("MdlMtx");
            shp_location.setName("Shp");
            mat_location.setName("Mat");
            sdw_location.setName("cShadowMap");
            rfl_location.setName("cReflectionMap");

            updateLocation();
        }

        void updateLocation()
        {
            if (p_shader_program)
            {
                env_location.search(*p_shader_program);
                mtx_location.search(*p_shader_program);
                shp_location.search(*p_shader_program);
                mat_location.search(*p_shader_program);
                sdw_location.search(*p_shader_program);
                rfl_location.search(*p_shader_program);
            }
        }

        agl::ShaderProgram* p_shader_program;
        agl::UniformBlockLocation env_location;
        agl::UniformBlockLocation mtx_location;
        agl::UniformBlockLocation shp_location;
        agl::UniformBlockLocation mat_location;
        agl::SamplerLocation sdw_location;
        agl::SamplerLocation rfl_location;
    };
    static_assert(sizeof(ShaderAssign) == 0x64, "RenderObjEx::ShaderAssign size mismatch");

    struct ShapeRenderInfo
    {
        s32 idx_shape;
        s32 priority;
        sead::BitFlag32 flag;
        s32 polygon_offset;
        agl::DisplayList attrib_dl;
        agl::DisplayList mat_dl;
    };
    static_assert(sizeof(ShapeRenderInfo) == 0x30, "RenderObjEx::ShapeRenderInfo size mismatch");

    struct LightMap
    {
        void clear()
        {
            sead::MemUtil::fill(idx_lghtmap, u8(-1), sizeof(idx_lghtmap));
            sead::MemUtil::fill(idx_sampler, u8(-1), sizeof(idx_sampler));
        }

        s32 idx_lghtmap[LightMapMgr::cLightMapNum];
        s32 idx_sampler[LightMapMgr::cLightMapNum];
    };
    static_assert(sizeof(LightMap) == 0x10, "RenderObjEx::LightMap size mismatch");

    struct Shape
    {
        agl::UniformBlock uniform_block; // Shp
        LightMap light_map;
        sead::Buffer<nw::g3d::fnd::GfxBuffer> vtx_buffer;
    };
    static_assert(sizeof(Shape) == 0x2C, "RenderObjEx::Shape size mismatch");

public:
    // Calculates the drawing resources for skeleton matrices, shapes and materials
    void calc() override;

    // Updates buffers for the GPU
    void calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;

    // (Does nothing)
    void updateView(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override
    {
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Notes:
    // 1. Shadow-only shapes and reflection-only shapes are always invisible
    // 2. Shadow casting for a shape is automatically enabled if "shadow_cast" is not present in its material's render info

    void drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;
    void drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;

    // This draws the shadow of shadow-casting shapes
    void drawShadowOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;

    // These draws the reflection on shapes
    void drawReflectionOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;
    void drawReflectionXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) override;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool hasShadow() const override
    {
        return mShapeFlag.isOn(4);
    }

public:
    RenderObjEx();
    virtual ~RenderObjEx();

    void updateAnimations() override;
    void updateModel() override;

    // Rotation + Translation matrix
    void setMtxRT(const sead::Matrix34f& mtxRT) override
    {
        mMtxRT = mtxRT;
        mViewFlag.set(2);
    }

    const sead::Matrix34f& getMtxRT() const override
    {
        return mMtxRT;
    }

    void setScale(const sead::Vector3f& scale) override
    {
        mScale = scale;
        mViewFlag.set(2);
    }

    const sead::Vector3f& getScale() const override
    {
        return mScale;
    }

    // Determines if there are any shapes that can be drawn by draw*Opa()
    bool hasOpa() const override;
    // Determines if there are any shapes that can be drawn by draw*Xlu()
    bool hasXlu() const override;

    s32 getBoneIndex(const sead::SafeString& name) const override;
    const char* getBoneName(s32 index) const override;
    u32 getBoneCount() const override;

    void setBoneLocalSRT(s32 index, const sead::Matrix34f& mtxRT, const sead::Vector3f& scale) override;
    void getBoneLocalSRT(s32 index, sead::Matrix34f* mtxRT = NULL, sead::Vector3f* scale = NULL) const override;

    void setBoneWorldSRT(s32 index, const sead::Matrix34f& mtxSRT) override;
    void getBoneWorldSRT(s32 index, sead::Matrix34f& mtxSRT) const override;

    void setBoneVisibility(s32 index, bool visibility) override;
    bool getBoneVisibility(s32 index) const override; // deleted

    u32 getMaterialCount() const override;
    s32 getMaterialIndex(const sead::SafeString& name) const override;
    const char* getMaterialName(s32 index) const override;

    Material* getMaterial(s32 index) const override
    {
        return mpMaterial[index];
    }

    void setMaterialVisibility(s32 index, bool visibility) override;
    bool getMaterialVisibility(s32 index) const override; // deleted

    void setBoundingEnable(bool enable) override // deleted
    {
        mViewFlag.change(1, enable);
    }

    bool getBoundingEnable() const override
    {
        return mViewFlag.isOn(1);
    }

    const nw::g3d::Sphere& getBounding() const override
    {
        return mBounding;
    }

    void initViewShapesBuffer(void*, ObjLayer* layer, ObjLayerRenderer* renderer) override;

    sead::SafeString getName() const override
    {
        return mModelEx.GetResource()->GetName();
    }

    void setSklAnimBlendWeight(s32 index, f32 weight) override
    {
        mSklAnimBlendWeight[index] = weight;
    }

    f32 getSklAnimBlendWeight(s32 index) const override // deleted
    {
        return mSklAnimBlendWeight[index];
    }

    void setSklAnim(s32 index, Animation* anim) override;
    void setTexAnim(s32 index, Animation* anim) override;
    void setShuAnim(s32 index, Animation* anim) override;
    void setVisAnim(s32 index, Animation* anim) override;
    void setShaAnim(s32 index, Animation* anim) override;

    Animation* const* getSklAnims() const override
    {
        return reinterpret_cast<Animation* const*>(mpSklAnim.getBufferPtr());
    }

    Animation* const* getTexAnims() const override
    {
        return reinterpret_cast<Animation* const*>(mpTexAnim.getBufferPtr());
    }

    Animation* const* getShuAnims() const override
    {
        return reinterpret_cast<Animation* const*>(mpShuAnim.getBufferPtr());
    }

    Animation* const* getVisAnims() const override
    {
        return reinterpret_cast<Animation* const*>(mpVisAnim.getBufferPtr());
    }

    Animation* const* getShaAnims() const override
    {
        return reinterpret_cast<Animation* const*>(mpShaAnim.getBufferPtr());
    }

public:
    void create(nw::g3d::res::ResModel* res_model, const agl::ShaderProgramArchive* shader_archive, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, u32 bounding_mode, sead::Heap* heap);

    agl::g3d::ModelEx& getModelEx() { return mModelEx; }
    const agl::g3d::ModelEx& getModelEx() const { return mModelEx; }

    Shape& getShape(s32 index) { return mShape[index]; }
    const Shape& getShape(s32 index) const { return mShape[index]; }

    void activateMaterial(const agl::g3d::ModelShaderAssign& shader_assign, const nw::g3d::MaterialObj* p_material, const LightMap& light_map) const;

    void disableMaterialDL();

private:
    void setBoundingFlag_(s32 index)
    {
        mBoundingFlagArray[index >> 5] |= 1 << (index & 0x1F);
    }

    bool getBoundingFlag_(s32 index) const
    {
        return mBoundingFlagArray[index >> 5] & 1 << (index & 0x1F);
    }

    void setSubBoundingFlag_(s32 index)
    {
        mSubBoundingFlagArray[index >> 5] |= 1 << (index & 0x1F);
    }

    bool getSubBoundingFlag_(s32 index) const
    {
        return mSubBoundingFlagArray[index >> 5] & 1 << (index & 0x1F);
    }

    void createViewShapes_(s32 num_view, sead::Heap* heap);
    void initializeShapeRenderInfo_(ShapeRenderInfo& render_info, const nw::g3d::MaterialObj* p_material, const nw::g3d::ShapeObj* p_shape);
    static s32 sortShapeRenderInfoCmp(const ShapeRenderInfo* a, const ShapeRenderInfo* b);
    void updateBounding_();
    void applyBlendWeight_(s32 shape_index);
    static void setBoundingFlagArray_(u32 flag_array[], const SkeletalAnimation& anim);

private:
    agl::g3d::ModelEx mModelEx;
    nw::g3d::SkeletalAnimBlender mSklAnimBlender;
    sead::Buffer<SkeletalAnimation*> mpSklAnim;
    sead::Buffer<TexPatternAnimation*> mpTexAnim;
    sead::Buffer<ShaderParamAnimation*> mpShuAnim;
    sead::Buffer<VisibilityAnimation*> mpVisAnim;
    sead::Buffer<ShapeAnimation*> mpShaAnim;
    void* mpBuffer;
    void* mpBlockBuffer;
    size_t mBlockBufferSize;
    void* mpSklAnimBlenderBuffer;
    sead::Buffer<f32> mSklAnimBlendWeight;
    sead::PtrArray<ShapeRenderInfo> mOpaShapeInfo;
    sead::PtrArray<ShapeRenderInfo> mXluShapeInfo;
    sead::Buffer<ShaderAssign> mShaderAssign;
    sead::Buffer<MaterialEx*> mpMaterial;
    sead::Buffer<Shape> mShape;
    sead::Matrix34f mMtxRT;
    sead::Vector3f mScale;
    u8 _128;
    sead::BitFlag32 _12c;
    sead::BitFlag32 mViewFlag;
    sead::Buffer< sead::Buffer<nw::g3d::ShapeObj*> > mpViewShapeBuffer; // Idk
    nw::g3d::Sphere mBounding;
    sead::BoundBox3f* mpSubBounding;
    sead::BitFlag32 mShapeFlag; // & 4: a shape has shadow cast, & 2: a shape has reflection, & 1: a shape is visible
    u32 mBoundingFlagArray[10];    // sead::UnsafeArray?
    u32 mSubBoundingFlagArray[10]; // sead::UnsafeArray?
    sead::BitFlag32 _1a4;
    bool mMaterialNoDL;
};
static_assert(sizeof(RenderObjEx) == 0x1AC, "RenderObjEx size mismatch"); // Incomplete
