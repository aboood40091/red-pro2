#pragma once

//#include <distant_view/DVEnvTagMgr.h>
#include <graphics/CullViewFrustum.h>
#include <graphics/ModelResource.h>
#include <graphics/RenderMgr.h>

//#include <common/aglTextureData.h>
#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
//#include <layer/aglDrawMethod.h>
//#include <layer/aglLayer.h>
#include <math/BoundBox.h>
#include <math/rio_Matrix.h>
#include <math/rio_Vector.h>
//#include <postfx/aglDepthOfField.h>
#include <resource/SharcArchiveRes.h>

class BasicModel;

//class DistantViewCreditActorMgr;
class DistantViewEffectMgr;
//class DistantViewFFLMgr;
class DVCameraParam;

class ShaderParamAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;

class DistantViewMgr
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static DistantViewMgr* instance() { return sInstance; }

private:
    static DistantViewMgr* sInstance;

    DistantViewMgr();
    ~DistantViewMgr();

    DistantViewMgr(const DistantViewMgr&);
    DistantViewMgr& operator=(const DistantViewMgr&);

private:
    void calcView_();
    void calcModelMtx_();

    void drawParticle_(/* const agl::lyr::RenderInfo& render_info */);
    void applyDepthOfField_(/* const agl::lyr::RenderInfo& render_info */);

public:
    void initialize(const std::string& dv_fname /* , u8 course_file, u8 area, const sead::BoundBox2f& area_bound */);

    void resetAnim();

    SkeletalAnimation* getSklAnim() const;
    TexturePatternAnimation* getTexAnim() const; // Deleted
    ShaderParamAnimation* getShuTexSrtAnim() const; // Deleted
    ShaderParamAnimation* getShuColorAnim() const;

  //void pushBackDrawMethod();

    void update();

  //void draw(agl::lyr::Layer* p_layer) const;
    void calcMdl();
    void calcGPU();
    void drawOpa();
    void drawXlu();

  //void performMiiCheer(bool);

    void worldPosToScreenPos(rio::Vector3f* out_screen_pos, const rio::Vector3f& in_world_pos) const;
    void worldPosToBgScrollPos(rio::Vector3f* out_pos, const rio::Vector3f& in_world_pos) const;

    s32 searchBoneIndex(const char* name) const;
    void getBoneWorldMatrix(s32 index, rio::Matrix34f* mtx) const;

private:
    f32                         mNear;
    f32                         mFar;
    f32                         mFovyDeg;
    f32                         mScale;
    rio::Vector3f               mCameraBasePos;
    rio::Vector3f               mCameraPosOffset;
    rio::Vector3f               mCameraPos;
    rio::Vector3f               mCameraAtOffset;
    rio::LookAtCamera           mCamera;
    rio::PerspectiveProjection  mProjection;
    CullViewFrustum             mCull;
    BasicModel*                 mpBasicModel;
  //DVEnvTagMgr                 mEnvTagMgr;
    DVCameraParam*              mpCameraParam;
    DistantViewEffectMgr*       mpEffectMgr;
  //DistantViewFFLMgr*          mpFFLMgr;
    rio::Vector3f               mBgPos; // Position relative to the Bg / level camera
  //f32                         mAreaMinY;
  //agl::pfx::DepthOfField      mDof;
  //agl::TextureData            mDofIndTexture;
    rio::Vector2f               mDofIndScroll;
  //agl::lyr::DrawMethod        mEffDrawMethod;
  //agl::lyr::DrawMethod        mDofDrawMethod;
    bool                        mIsDrawParticle;
    u8                          _1455; // Unused
    bool                        mIsFlickerEnable;
    u8                          mFlickerCounter;
    rio::Vector2f               mFlickerOffset;

    // Custom
public:
    u8*             mpArchive;
    SharcArchiveRes mArchiveRes;
    ModelResource   mModelRes;
    RenderMgr       mRenderMgr;
};
//static_assert(sizeof(DistantViewMgr) == 0x1460);
