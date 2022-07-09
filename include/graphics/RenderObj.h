#pragma once

#include <graphics/Animation.h>
#include <graphics/Material.h>
#include <graphics/ObjLayer.h>

#include <heap/seadDisposer.h>
#include <math/seadSphere.h>

#include <shadow/aglDepthShadow.h>

class RenderObj : public ObjLayer::Node, public sead::IDisposer
{
    SEAD_RTTI_OVERRIDE(RenderObj, ObjLayer::Node)

public:
    RenderObj();
    virtual ~RenderObj();

    virtual void updateAnimations() = 0;
    virtual void updateModel() = 0;
    virtual void setMtxRT(const sead::Matrix34f& mtxRT) = 0;
    virtual const sead::Matrix34f& getMtxRT() const = 0;
    virtual void setScale(const sead::Vector3f& scale) = 0;
    virtual const sead::Vector3f& getScale() const = 0;
    virtual bool hasOpa() const = 0;
    virtual bool hasXlu() const = 0;
    virtual s32 getBoneIndex(const sead::SafeString& name) const = 0;
    virtual const char* getBoneName(s32 index) const = 0;
    virtual u32 getBoneCount() const = 0;
    virtual void setBoneLocalSRT(s32 index, const sead::Matrix34f& mtxRT, const sead::Vector3f& scale) = 0;
    virtual void getBoneLocalSRT(s32 index, sead::Matrix34f* mtxRT, sead::Vector3f* scale) const = 0;
    virtual void setBoneWorldSRT(s32 index, const sead::Matrix34f& mtxSRT) = 0;
    virtual void getBoneWorldSRT(s32 index, sead::Matrix34f& mtxSRT) const = 0;
    virtual void setBoneVisibility(s32 index, bool visibility) = 0;
    virtual bool getBoneVisibility(s32 index) const = 0;
    virtual u32 getMaterialCount() const = 0;
    virtual s32 getMaterialIndex(const sead::SafeString& name) const = 0;
    virtual const char* getMaterialName(s32 index) const = 0;
    virtual Material* getMaterial(s32 index) const = 0;
    virtual void setMaterialVisibility(s32 index, bool visibility) = 0;
    virtual bool getMaterialVisibility(s32 index) const = 0;
    virtual void setBoundingEnable(bool enable) = 0;
    virtual bool getBoundingEnable() const = 0;
    virtual const sead::Sphere3f& getBounding() const = 0;
    virtual void calcViewShapeShadowFlags(agl::sdw::DepthShadow* p_depth_shadow, ObjLayer* p_shadow_layer, ObjLayerRenderer* renderer) = 0;
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

protected:
    s32 mOpaBufferIdx;
    s32 mXluBufferIdx;
};
static_assert(sizeof(RenderObj) == 0x28, "RenderObj size mismatch");
