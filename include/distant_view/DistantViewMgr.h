#pragma once

#include <graphics/CullViewFrustum.h>
#include <graphics/ModelResource.h>
#include <graphics/RenderMgr.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglTextureData.h>
#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <math/BoundBox.h>
#include <math/rio_Matrix.h>
#include <math/rio_Vector.h>
#include <postfx/aglDepthOfField.h>
#include <resource/SharcArchiveRes.h>

class BasicModel;

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

public:
    void applyDepthOfField();

    void initialize(const std::string& dv_name = "Nohara", const std::string& dv_path = "");
    void destroy();

    rio::Vector3f& cameraPosOffset() { return mCameraPosOffset; }
    const rio::Vector3f& cameraPosOffset() const { return mCameraPosOffset; }

    rio::Vector3f& cameraAtOffset() { return mCameraAtOffset; }
    const rio::Vector3f& cameraAtOffset() const { return mCameraAtOffset; }

    void setFlickerEnable(bool enable)
    {
        mIsFlickerEnable = enable;
    }

    bool isFlickerEnable() const
    {
        return mIsFlickerEnable;
    }

    void resetAnim();

    SkeletalAnimation* getSklAnim() const;
    TexturePatternAnimation* getTexAnim() const; // Deleted
    ShaderParamAnimation* getShuTexSrtAnim() const; // Deleted
    ShaderParamAnimation* getShuColorAnim() const;

    void update();

    void calcMdl();
    void calcGPU();
    void drawOpa();
    void drawXlu();

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
    DVCameraParam*              mpCameraParam;
    rio::Vector3f               mBgPos; // Position relative to the Bg / level camera
  //f32                         mAreaMinY;
    agl::pfx::DepthOfField      mDof;
    agl::TextureData*           mpDofIndTexture;
    rio::Vector2f               mDofIndScroll;
    u8                          _1455; // Unused
    bool                        mIsFlickerEnable;
    u8                          mFlickerCounter;
    rio::Vector2f               mFlickerOffset;

    // Custom
    u8*                     mpArchive;
    SharcArchiveRes         mArchiveRes;
    ModelResource           mModelRes;
    RenderMgr               mRenderMgr;

    agl::RenderBuffer       mRenderBuffer;
    agl::RenderTargetColor  mColorTarget;
    agl::RenderTargetDepth  mDepthTarget;
    agl::TextureData        mColorTextureData;
    agl::TextureData        mDepthTextureData;

    friend class DVCameraParam;
};
//static_assert(sizeof(DistantViewMgr) == 0x1460);
