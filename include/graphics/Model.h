#pragma once

#include <graphics/Animation.h>
#include <graphics/Material.h>
#include <graphics/RenderObj.h>
#include <graphics/RenderObjLayer.h>

#include <geom/seadSphere.h>
#include <heap/seadDisposer.h>
#include <shadow/aglDepthShadow.h>

class ModelNW;
class ModelResource;

class Model : public RenderObj, public sead::IDisposer
{
    SEAD_RTTI_OVERRIDE(Model, RenderObj)

public:
    enum BoundingMode
    {
        cBoundingMode_Disable,
        cBoundingMode_Enable,
        cBoundingMode_EnableSubBounding
    };

    // Why are these here... ?
    static ModelNW* createNW(const ModelResource& res, const sead::SafeString& name, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, BoundingMode bounding_mode, sead::Heap* heap);
    static ModelNW* createNW(const ModelResource& res, const sead::SafeString& name, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, BoundingMode bounding_mode, sead::Heap* heap);

public:
    Model();
    virtual ~Model();

    virtual void updateAnimations() = 0;
    virtual void updateModel() = 0;
    virtual void setMtxRT(const sead::Matrix34f& rt) = 0;
    virtual const sead::Matrix34f& getMtxRT() const = 0;
    virtual void setScale(const sead::Vector3f& scale) = 0;
    virtual const sead::Vector3f& getScale() const = 0;
    virtual bool hasOpa() const = 0;
    virtual bool hasXlu() const = 0;
    virtual s32 searchBoneIndex(const sead::SafeString& name) const = 0;
    virtual const char* getBoneName(s32 index) const = 0;
    virtual u32 getBoneNum() const = 0;
    virtual void setBoneLocalMatrix(s32 index, const sead::Matrix34f& rt, const sead::Vector3f& scale) = 0;
    virtual void getBoneLocalMatrix(s32 index, sead::Matrix34f* rt, sead::Vector3f* scale) const = 0;
    virtual void setBoneWorldMatrix(s32 index, const sead::Matrix34f& mtx) = 0;
    virtual void getBoneWorldMatrix(s32 index, sead::Matrix34f* mtx) const = 0;
    virtual void setBoneVisible(s32 index, bool visible) = 0;
    virtual bool isBoneVisible(s32 index) const = 0;
    virtual u32 getMaterialNum() const = 0;
    virtual s32 searchMaterialIndex(const sead::SafeString& name) const = 0;
    virtual const char* getMaterialName(s32 index) const = 0;
    virtual Material* getMaterial(s32 index) const = 0;
    virtual void setMaterialVisible(s32 index, bool visible) = 0;
    virtual bool isMaterialVisible(s32 index) const = 0;
    virtual void setBoundingEnable(bool enable) = 0;
    virtual bool isBoundingEnable() const = 0;
    virtual const sead::Sphere3f& getBounding() const = 0;
    virtual void calcViewShapeShadowFlags(agl::sdw::DepthShadow* p_depth_shadow, RenderObjLayerBase* p_shadow_layer, RenderMgr* p_render_mgr) = 0;
    virtual sead::SafeString getName() const = 0;
    virtual void setSklAnimBlendWeight(s32 index, f32 weight) = 0;
    virtual f32 getSklAnimBlendWeight(s32 index) const = 0;
    virtual void setSklAnim(s32 index, Animation* anim) = 0;
    virtual void setTexAnim(s32 index, Animation* anim) = 0;
    virtual void setShuAnim(s32 index, Animation* anim) = 0;
    virtual void setVisAnim(s32 index, Animation* anim) = 0;
    virtual void setShaAnim(s32 index, Animation* anim) = 0;
    virtual Animation* const* getSklAnims() const = 0;
    virtual Animation* const* getTexAnims() const = 0;
    virtual Animation* const* getShuAnims() const = 0;
    virtual Animation* const* getVisAnims() const = 0;
    virtual Animation* const* getShaAnims() const = 0;

    s32 getOpaBufferIdx() const { return mOpaBufferIdx; }
    s32 getXluBufferIdx() const { return mXluBufferIdx; }

    void setOpaBufferIdx(s32 index) { mOpaBufferIdx = index; }
    void setXluBufferIdx(s32 index) { mXluBufferIdx = index; }

protected:
    s32 mOpaBufferIdx;
    s32 mXluBufferIdx;
};
static_assert(sizeof(Model) == 0x28);
