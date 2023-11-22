#pragma once

#include <graphics/CullViewFrustum.h>
#include <graphics/ModelResource.h>

#include <common/aglRenderBuffer.h>
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

class RenderObjLayer;

class ShaderParamAnimation;
class SkeletalAnimation;
class TexturePatternAnimation;

class DistantViewMgr
{
public:
    static bool createSingleton(const agl::RenderBuffer& render_buffer);
    static void destroySingleton();
    static DistantViewMgr* instance() { return sInstance; }

private:
    static DistantViewMgr* sInstance;

    DistantViewMgr(const agl::RenderBuffer& render_buffer);
    ~DistantViewMgr();

    DistantViewMgr(const DistantViewMgr&);
    DistantViewMgr& operator=(const DistantViewMgr&);

private:
    void calcView_(const rio::BaseVec2f& bg_screen_center, f32 bg_offset_area_bottom_to_screen_bottom, f32 bg_zoom);
    void calcModelMtx_();

public:
    void onResizeRenderBuffer();
    void applyDepthOfField();

    void initialize(
        const std::string& dv_name = "Nohara", const std::string& dv_path = "",
        bool force_sharcfb = false,
        const rio::BaseVec2f& bg_pos = { 0.0f, 0.0f },
        const rio::BaseVec2f& bg_screen_center = { 0.0f, 0.0f },
        f32 bg_offset_area_bottom_to_screen_bottom = 0.0f,
        f32 bg_zoom = 1.0f
    );
    void destroy();

    void setScale(f32 scale)
    {
        mScale = scale;
    }

    f32 getScale() const
    {
        return mScale;
    }

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

    void update(
        RenderObjLayer* p_layer,
        const rio::BaseVec2f& bg_screen_center = { 0.0f, 0.0f },
        f32 bg_offset_area_bottom_to_screen_bottom = 0.0f,
        f32 bg_zoom = 1.0f
    );

    void draw(RenderObjLayer* p_layer);

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

    const agl::RenderBuffer&    mRenderBuffer;

    friend class DVCameraParam;
};
//static_assert(sizeof(DistantViewMgr) == 0x1460);
