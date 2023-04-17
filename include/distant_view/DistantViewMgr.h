#pragma once

#include <distant_view/DVEnvTagMgr.h>
#include <graphics/CullViewFrustum.h>

#include <common/aglTextureData.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <heap/seadDisposer.h>
#include <layer/aglDrawMethod.h>
#include <layer/aglLayer.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <postfx/aglDepthOfField.h>

class BasicModel;

//class DistantViewCreditActorMgr;
class DistantViewEffectMgr;
class DistantViewFFLMgr;
class DVCameraParam;

class ShaderParamAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;

class DistantViewMgr
{
    SEAD_SINGLETON_DISPOSER(DistantViewMgr)

public:
    DistantViewMgr();

private:
    void calcView_();
    void calcModelMtx_();

    void drawParticle_(const agl::lyr::RenderInfo& render_info);
    void applyDepthOfField_(const agl::lyr::RenderInfo& render_info);

public:
    void initialize(u8 course_file, u8 area, const sead::BoundBox2f& area_bound);

    void resetAnim();

    SkeletalAnimation* getSklAnim() const;
    TexturePatternAnimation* getTexAnim() const; // Deleted
    ShaderParamAnimation* getShuTexSrtAnim() const; // Deleted
    ShaderParamAnimation* getShuColorAnim() const;

    void pushBackDrawMethod();

    void update();
    void draw(agl::lyr::Layer* p_layer) const;

    void performMiiCheer(bool);

    void worldPosToScreenPos(sead::Vector3f* out_screen_pos, const sead::Vector3f& in_world_pos) const;
    void worldPosToBgScrollPos(sead::Vector3f* out_pos, const sead::Vector3f& in_world_pos) const;

    s32 searchBoneIndex(const sead::SafeString& name) const;
    void getBoneWorldMatrix(s32 index, sead::Matrix34f* mtx) const;

private:
    f32                         mNear;
    f32                         mFar;
    f32                         mFovyDeg;
    f32                         mScale;
    sead::Vector3f              mCameraBasePos;
    sead::Vector3f              mCameraPosOffset;
    sead::Vector3f              mCameraPos;
    sead::Vector3f              mCameraAtOffset;
    sead::LookAtCamera          mCamera;
    sead::PerspectiveProjection mProjection;
    CullViewFrustum             mCull;
    BasicModel*                 mpBasicModel;
    DVEnvTagMgr                 mEnvTagMgr;
    DVCameraParam*              mpCameraParam;
    DistantViewEffectMgr*       mpEffectMgr;
    DistantViewFFLMgr*          mpFFLMgr;
    sead::Vector3f              mBgPos; // Position relative to the Bg / level camera
    f32                         mAreaMinY;
    agl::pfx::DepthOfField      mDof;
    agl::TextureData            mDofIndTexture;
    sead::Vector2f              mDofIndScroll;
    agl::lyr::DrawMethod        mEffDrawMethod;
    agl::lyr::DrawMethod        mDofDrawMethod;
    bool                        mIsDrawParticle;
    u8                          _1455; // Unused
    bool                        mIsFlickerEnable;
    u8                          mFlickerCounter;
    sead::Vector2f              mFlickerOffset;
};
static_assert(sizeof(DistantViewMgr) == 0x1460);
