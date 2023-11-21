#include <distant_view/DistantViewMgr.h>
#include <distant_view/DVCameraParam.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelG3d.h>
#include <graphics/Renderer.h>
#include <graphics/RenderObjLayer.h>

#include <common/aglTextureFormatInfo.h>
#include <filedevice/rio_FileDeviceMgr.h>
#include <g3d/aglTextureDataInitializerG3D.h>
#include <gfx/rio_Graphics.h>
#include <gfx/rio_Window.h>
#include <misc/rio_MemUtil.h>
#include <resource/SZSDecompressor.h>
#include <utility/aglResParameter.h>

#if RIO_IS_CAFE
#include <gx2/event.h>
#endif // RIO_IS_CAFE

DistantViewMgr* DistantViewMgr::sInstance = nullptr;

bool DistantViewMgr::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new DistantViewMgr();
    return true;
}

void DistantViewMgr::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

DistantViewMgr::DistantViewMgr()
    : mNear(100.0f)
    , mFar(80000.0f)
    , mFovyDeg(20.0f)
    , mScale(1.0f)
    , mCameraBasePos{0.0f, 0.0f, 0.0f}
    , mCameraPosOffset{0.0f, 0.0f, 0.0f}
    , mCameraPos{0.0f, 0.0f, 0.0f}
    , mCameraAtOffset{0.0f, 0.0f, 0.0f}
    , mCamera()
    , mProjection(mNear, mFar, rio::Mathf::deg2rad(mFovyDeg), 16.f / 9.f)
    , mCull()
    , mpBasicModel(nullptr)
    , mpCameraParam(nullptr)
    , mBgPos{0.0f, 0.0f, 0.0f}
  //, mAreaMinY(AreaTask::instance()->getBound().getMin().y)
    , mDof()
    , mpDofIndTexture(nullptr)
    , mDofIndScroll{0.0f, 0.0f}
    , mIsFlickerEnable(true)
    , mFlickerCounter(0)
    , mFlickerOffset{0.375f, 0.375f}
    // Custom
    , mpArchive(nullptr)
    , mRenderBuffer(
        rio::Vector2i{ s32(rio::Window::instance()->getWidth()), s32(rio::Window::instance()->getHeight()) }
    )
{
    mRenderBuffer.setRenderTargetColor(&mColorTarget);
    mRenderBuffer.setRenderTargetDepth(&mDepthTarget);

    const rio::NativeWindow& native_window = rio::Window::instance()->getNativeWindow();

    [[maybe_unused]] const u32 width = rio::Window::instance()->getWidth();
    [[maybe_unused]] const u32 height = rio::Window::instance()->getHeight();

#if RIO_IS_CAFE

    mColorTextureData.initializeFromSurface(native_window.getColorBuffer().surface);

#elif RIO_IS_WIN

    mColorTextureData.initialize(
        agl::TextureFormatInfo::convFormatGX2ToAGL(
            static_cast<GX2SurfaceFormat>(native_window.getColorBufferTextureFormat()),
            true,
            false
        ),
        width,
        height,
        1
    );

    mColorTextureData.setHandle(std::make_shared<agl::TextureHandle>(native_window.getColorBufferTextureHandle()));

#endif

    mColorTarget.applyTextureData(mColorTextureData);

#if RIO_IS_CAFE

    GX2Surface& depth_surface = const_cast<GX2Surface&>(rio::Window::instance()->getWindowDepthBufferTexture()->surface);
    if (depth_surface.use & GX2_SURFACE_USE_DEPTH_BUFFER)
    {
        mDepthTextureData.initializeFromSurface(depth_surface);
    }
    else
    {
        depth_surface.use = GX2SurfaceUse(depth_surface.use | GX2_SURFACE_USE_DEPTH_BUFFER);
        mDepthTextureData.initializeFromSurface(depth_surface);
        depth_surface.use = GX2SurfaceUse(depth_surface.use & ~GX2_SURFACE_USE_DEPTH_BUFFER);
    }

#elif RIO_IS_WIN

    mDepthTextureData.initialize(
        agl::TextureFormatInfo::convFormatGX2ToAGL(
            static_cast<GX2SurfaceFormat>(native_window.getDepthBufferTextureFormat()),
            false,
            true
        ),
        width,
        height,
        1
    );

    mDepthTextureData.setHandle(std::make_shared<agl::TextureHandle>(rio::Window::instance()->getWindowDepthBufferTexture()));

#endif

    mDepthTarget.applyTextureData(mDepthTextureData);

#if RIO_IS_WIN
    mRenderBuffer.bind();

    // Check Frame Buffer completeness
    GLenum framebuffer_status;
    RIO_GL_CALL(framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
    {
        RIO_LOG("Frame Buffer incomplete! Status 0x%08X\n", framebuffer_status);
        RIO_ASSERT(false);
    }
#endif // RIO_IS_WIN

    rio::Window::instance()->makeContextCurrent();

    mDof.initialize();
}

DistantViewMgr::~DistantViewMgr()
{
    destroy();
}

void DistantViewMgr::destroy()
{
#if RIO_IS_CAFE
    GX2DrawDone();
#elif RIO_IS_WIN
    RIO_GL_CALL(glFinish());
#endif

    mDofIndScroll.set(0.0f, 0.0f);

    if (mpDofIndTexture)
    {
        mDof.setIndirectTextureData(nullptr);

        delete mpDofIndTexture;
        mpDofIndTexture = nullptr;
    }

    if (mpBasicModel)
    {
        ModelG3d* p_mdl = mpBasicModel->getModel();
        if (p_mdl)
        {
            delete p_mdl;
            p_mdl = nullptr;
        }

        delete mpBasicModel;
        mpBasicModel = nullptr;
    }

    if (mModelRes.getResFile())
        mModelRes.destroy();

    if (mpCameraParam)
    {
        delete mpCameraParam;
        mpCameraParam = nullptr;
    }

    if (mpArchive)
    {
        mArchiveRes.destroy();
        rio::MemUtil::free(mpArchive);
        mpArchive = nullptr;
    }
}

void DistantViewMgr::calcView_(const rio::BaseVec2f& bg_screen_center, f32 bg_offset_area_bottom_to_screen_bottom, f32 bg_zoom)
{
    mProjection.setOffset(mpCameraParam->getProjOffset());

    f32 fovy_tan = std::tan(rio::Mathf::deg2rad(mFovyDeg * 0.5f));

    f32 screen_center_x = /* BgScrollMgr::instance()->getScreenCenterX() */ bg_screen_center.x;
    f32 screen_center_y = /* BgScrollMgr::instance()->getScreenCenterY() - BgScrollMgr::instance()->getScrollEffectMgr()._3c._8 */ bg_screen_center.y;

    f32 base_z = (112.0f / fovy_tan) * /* BgScrollMgr::instance()->getZoom() */ bg_zoom * mScale;

    fovy_tan = std::tan(rio::Mathf::deg2rad(mFovyDeg * 0.5f)); // ???????????? ok
    fovy_tan = base_z * fovy_tan * 2;

    mCameraBasePos.z = base_z;

    mCameraBasePos.x = screen_center_x - fovy_tan * mpCameraParam->getProjOffset().x;
    mCameraBasePos.y = screen_center_y - fovy_tan * mpCameraParam->getProjOffset().y;
    if (mpCameraParam->getTypeDirY() == 1)
        mCameraBasePos.y += mpCameraParam->getMagnifCameraPosY() * /* (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY) */ bg_offset_area_bottom_to_screen_bottom;

    mCameraPos.setAdd(mCameraBasePos, mCameraPosOffset);

    rio::Vector2f proj_base_offs { 0.0f, 0.0f };
    /*
    if (Quake::instance())
        proj_base_offs = Quake::instance()->getOffset();
    */
    if (mpCameraParam->getTypeDirY() == 0)
        proj_base_offs.y += mpCameraParam->getMagnifProjOffsetY() * /* (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY) */ bg_offset_area_bottom_to_screen_bottom;

    if (proj_base_offs.x != 0.0f || proj_base_offs.y != 0.0f)
    {
        f32 proj_base_offs_x = proj_base_offs.x / 1280;
        f32 proj_base_offs_y = proj_base_offs.y / 720;

        proj_base_offs_x *= s32(rio::Window::instance()->getWidth()) / 1280.0f;
        proj_base_offs_y *= s32(rio::Window::instance()->getHeight()) / 720.0f;

        proj_base_offs = mProjection.offset();

        proj_base_offs.x += proj_base_offs_x;
        proj_base_offs.y += proj_base_offs_y;

        mProjection.setOffset(proj_base_offs);
    }

    if (mIsFlickerEnable)
    {
        f32 flicker_proj_offs_x = (mFlickerOffset.x * 0.5f) / 1280;
        f32 flicker_proj_offs_y = (mFlickerOffset.y * 0.5f) / 720;

        flicker_proj_offs_x *= s32(rio::Window::instance()->getWidth()) / 1280.0f;
        flicker_proj_offs_y *= s32(rio::Window::instance()->getHeight()) / 720.0f;

        rio::Vector2f proj_offset = mProjection.offset();

        if ((++mFlickerCounter & 1) == 0)
        {
            proj_offset.x += flicker_proj_offs_x;
            proj_offset.y += flicker_proj_offs_y;
        }
        else
        {
            proj_offset.x -= flicker_proj_offs_x;
            proj_offset.y -= flicker_proj_offs_y;
        }

        mProjection.setOffset(proj_offset);
    }

    rio::Vector3f at = mCameraPos + mCameraAtOffset;

    mCamera.at().set(at.x, at.y, at.z - 1.0f);
    mCamera.pos() = mCameraPos;

    mCull.update(mCamera, mProjection);
}

void DistantViewMgr::calcModelMtx_()
{
    ModelG3d* p_model = mpBasicModel->getModel();

    rio::Matrix34f model_mtx;
    mpCameraParam->getModelMtx(&model_mtx);

    p_model->setMtxRT(model_mtx);
}

void DistantViewMgr::applyDepthOfField()
{
    rio::Window::instance()->updateDepthBufferTexture();

    mDof.draw(0, mRenderBuffer, mProjection.getNear(), mProjection.getFar());
}

void DistantViewMgr::initialize(const std::string& dv_name, const std::string& dv_path, bool force_sharcfb, const rio::BaseVec2f& bg_pos, const rio::BaseVec2f& bg_screen_center, f32 bg_offset_area_bottom_to_screen_bottom, f32 bg_zoom)
{
    destroy();

    const std::string& dv_fname = "dv_" + dv_name;
    const std::string& dv_fpath = dv_path.empty() ? dv_fname : dv_path + "/" + dv_fname;

    mDof.setEnable(false);

    mBgPos.set(bg_pos.x, bg_pos.y, 0.0f);

    rio::FileDevice::LoadArg arg;
    arg.path = dv_fpath;
    arg.path += ".szs";
    arg.alignment = 0x2000;

    mpArchive = SZSDecompressor::tryDecomp(arg);
    RIO_ASSERT(mpArchive);

    mArchiveRes.prepareArchive(mpArchive);

  //mEnvTagMgr.initialize(mArchiveRes.getFile((dv_fname + ".opt").c_str()));

    mpCameraParam = new DVCameraParam(this, &mBgPos, dv_fname);

    const void* p_dof_file = mArchiveRes.getFile((dv_fname + ".bagldof").c_str());
    if (p_dof_file)
    {
        agl::utl::ResParameterArchive res_param_arc(p_dof_file);
        mDof.applyResParameterArchive(res_param_arc);
    }
    else
    {
        mDof.setEnable(false);
    }

    const char* const dv_fname_c = dv_fname.c_str();

    mModelRes.load(&mArchiveRes, dv_fname_c, force_sharcfb);

    ModelG3d* p_mdl = Model::createG3d(mModelRes, dv_fname_c, 1, 1, 1, 2, 0, 0, Model::cBoundingMode_Enable);
    BasicModel* p_basic_mdl = new BasicModel(p_mdl, 1, 1, 2, 0, 0);
    p_basic_mdl->init(&mModelRes);
    mpBasicModel = p_basic_mdl;

    if (mModelRes.getResFile()->GetSkeletalAnimCount() > 0)
        mpBasicModel->getSklAnim(0)->play(&mModelRes, dv_fname_c);

    if (mModelRes.getResFile()->GetTexSrtAnimCount() > 0)
        mpBasicModel->getShuAnim(0)->playTexSrtAnim(&mModelRes, dv_fname_c);

    if (mModelRes.getResFile()->GetColorAnimCount() > 0)
        mpBasicModel->getShuAnim(1)->playColorAnim(&mModelRes, dv_fname_c);

    if (mModelRes.getResFile()->GetTexPatternAnimCount() > 0)
        mpBasicModel->getTexAnim(0)->play(&mModelRes, dv_fname_c);

    s32 idx_dof_ind = mModelRes.getResFile()->GetTextureIndex("dof_indirect");
    if (idx_dof_ind >= 0)
    {
        nw::g3d::res::ResTexture* p_dof_ind = mModelRes.getResFile()->GetTexture(idx_dof_ind);

        mpDofIndTexture = new agl::TextureData();

      //sead::Graphics::instance()->lockDrawContext();
        {
            agl::g3d::TextureDataInitializerG3D::initialize(mpDofIndTexture, *p_dof_ind);
        }
      //sead::Graphics::instance()->unlockDrawContext();

        mDof.setIndirectTextureData(mpDofIndTexture);
        mDof.setIndirectTextureTrans(mDofIndScroll);
        mDof.setIndirectEnable(true);
    }

    calcView_(bg_screen_center, bg_offset_area_bottom_to_screen_bottom, bg_zoom);
    calcModelMtx_();

    mpBasicModel->updateModel();
}

void DistantViewMgr::resetAnim()
{
    SkeletalAnimation* const p_skl_anim = mpBasicModel->getSklAnim(0);
    if (p_skl_anim)
        p_skl_anim->getFrameCtrl().reset();

    TexturePatternAnimation* const p_tex_anim = mpBasicModel->getTexAnim(0);
    if (p_tex_anim)
        p_tex_anim->getFrameCtrl().reset();

    for (s32 i = 0; i < 2; i++)
    {
        ShaderParamAnimation* const p_shu_anim = mpBasicModel->getShuAnim(i);
        if (p_shu_anim)
            p_shu_anim->getFrameCtrl().reset();
    }
}

SkeletalAnimation* DistantViewMgr::getSklAnim() const
{
    return mpBasicModel->getSklAnim(0);
}

TexturePatternAnimation* DistantViewMgr::getTexAnim() const
{
    return mpBasicModel->getTexAnim(0);
}

ShaderParamAnimation* DistantViewMgr::getShuTexSrtAnim() const
{
    return mpBasicModel->getShuAnim(0);
}

ShaderParamAnimation* DistantViewMgr::getShuColorAnim() const
{
    return mpBasicModel->getShuAnim(1);
}

void DistantViewMgr::update(RenderObjLayer* p_layer, const rio::BaseVec2f& bg_screen_center, f32 bg_offset_area_bottom_to_screen_bottom, f32 bg_zoom)
{
    calcView_(bg_screen_center, bg_offset_area_bottom_to_screen_bottom, bg_zoom);

    mpBasicModel->updateAnimations();
    mpBasicModel->updateModel();

    mDofIndScroll += mpCameraParam->getIndirectScrollSpd();

    mDofIndScroll.x = std::fmod(mDofIndScroll.x + 1.0f, 1.0f);
    mDofIndScroll.y = std::fmod(mDofIndScroll.y + 1.0f, 1.0f);

    mDof.setIndirectTextureTrans(mDofIndScroll);

    RIO_ASSERT(p_layer != nullptr);

    p_layer->setCamera(&mCamera);
    p_layer->setProjection(&mProjection);
    p_layer->setCullViewFrustum(&mCull);
}

void DistantViewMgr::draw(RenderObjLayer* p_layer)
{
    Renderer::instance()->setLayer(p_layer);
    {
        Renderer::instance()->drawModel(*mpBasicModel);
    }
    Renderer::instance()->resetLayer();
}
