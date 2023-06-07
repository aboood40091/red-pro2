/*
#include <actor/ActorMgr.h>
#include <actor/ProfileID.h>
#include <effect/PtclMgr.h>
#include <game/AreaLayerMgr.h>
#include <game/AreaTask.h>
#include <game/Quake.h>
#include <graphics/EnvSetReader.h>
#include <graphics/GfxParameter.h>
#include <graphics/ModelResource.h>
#include <graphics/ModelResourceMgr.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>
#include <graphics/ShaderParamAnimation.h>
#include <graphics/SkeletalAnimation.h>
#include <graphics/TexturePatternAnimation.h>
#include <map/CourseData.h>
#include <scroll/BgScrollMgr.h>
#include <system/ResMgr.h>
#include <tag/BgCenter.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <g3d/aglTextureDataInitializerG3D.h>
#include <heap/seadFrameHeap.h>
#include <layer/aglRenderer.h>
#include <layer/aglRenderInfo.h>
#include <utility/aglResParameter.h>
*/

#include <distant_view/DistantViewMgr.h>
#include <distant_view/DVCameraParam.h>
#include <graphics/BasicModel.h>
#include <graphics/ModelNW.h>

#include <filedevice/rio_FileDeviceMgr.h>
#include <misc/rio_MemUtil.h>
#include <resource/SZSDecompressor.h>

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
  //, mEnvTagMgr()
    , mpCameraParam(nullptr)
    , mpEffectMgr(nullptr)
  //, mpFFLMgr(nullptr)
    , mBgPos{0.0f, 0.0f, 0.0f}
  //, mAreaMinY(AreaTask::instance()->getBound().getMin().y)
  //, mDof()
  //, mDofIndTexture()
    , mDofIndScroll{0.0f, 0.0f}
  //, mEffDrawMethod()
  //, mDofDrawMethod()
    , mIsDrawParticle(false)
    , mIsFlickerEnable(true)
    , mFlickerCounter(0)
    , mFlickerOffset{0.375f, 0.375f}
    // Custom
    , mpArchive(nullptr)
{
}

DistantViewMgr::~DistantViewMgr()
{
}

void DistantViewMgr::calcView_()
{
    mProjection.setOffset(mpCameraParam->getProjOffset());

    f32 fovy_tan = std::tan(rio::Mathf::deg2rad(mFovyDeg * 0.5f));

    f32 screen_center_x = /* BgScrollMgr::instance()->getScreenCenterX() */ 0.0f;
    f32 screen_center_y = /* BgScrollMgr::instance()->getScreenCenterY() - BgScrollMgr::instance()->getScrollEffectMgr()._3c._8 */ 0.0f;

    f32 base_z = (112.0f / fovy_tan) * /* BgScrollMgr::instance()->getZoom() */ 1 * mScale;

    fovy_tan = std::tan(rio::Mathf::deg2rad(mFovyDeg * 0.5f)); // ???????????? ok
    fovy_tan = base_z * fovy_tan * 2;

    mCameraBasePos.z = base_z;

    mCameraBasePos.x = screen_center_x - fovy_tan * mpCameraParam->getProjOffset().x;
    mCameraBasePos.y = screen_center_y - fovy_tan * mpCameraParam->getProjOffset().y;
    if (mpCameraParam->getTypeDirY() == 1)
        mCameraBasePos.y += mpCameraParam->getMagnifCameraPosY() * /* (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY) */ 0;

    mCameraPos.setAdd(mCameraBasePos, mCameraPosOffset);

    rio::Vector2f proj_base_offs { 0.0f, 0.0f };
    /*
    if (Quake::instance())
        proj_base_offs = Quake::instance()->getOffset();
    */
    if (mpCameraParam->getTypeDirY() == 0)
        proj_base_offs.y += mpCameraParam->getMagnifProjOffsetY() * /* (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY) */ 0;

    if (proj_base_offs.x != 0.0f || proj_base_offs.y != 0.0f)
    {
        f32 proj_offset_x = mProjection.offset().x + proj_base_offs.x / 1280;
        f32 proj_offset_y = mProjection.offset().y + proj_base_offs.y / 720;

        proj_base_offs.set(proj_offset_x, proj_offset_y);
        mProjection.setOffset(proj_base_offs);
    }

    if (mIsFlickerEnable)
    {
        f32 flicker_proj_offs_x = (mFlickerOffset.x * 0.5f) / 1280;
        f32 flicker_proj_offs_y = (mFlickerOffset.y * 0.5f) / 720;

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
  //mCamera.updateViewMatrix();

    mCull.update(mCamera, mProjection);
}

void DistantViewMgr::calcModelMtx_()
{
    ModelNW* p_model = mpBasicModel->getModel();

    rio::Matrix34f model_mtx;
    mpCameraParam->getModelMtx(&model_mtx);

    p_model->setMtxRT(model_mtx);
}

/*
void DistantViewMgr::drawParticle_(const agl::lyr::RenderInfo& render_info)
{
    PtclMgr::instance()->draw(render_info, 0);
}

void DistantViewMgr::applyDepthOfField_(const agl::lyr::RenderInfo& render_info)
{
    const agl::RenderBuffer* p_render_buffer = static_cast<const agl::RenderBuffer*>(render_info.getFrameBuffer());
    if (!p_render_buffer)
        return;

    p_render_buffer->getRenderTargetColor()->expandAuxBuffer();
    p_render_buffer->getRenderTargetDepth()->expandHiZBuffer();

    mDof.draw(0, *p_render_buffer, mProjection.getNear(), mProjection.getFar());
}
*/

void DistantViewMgr::initialize(const std::string& dv_fname /* , u8 course_file, u8 area, const sead::BoundBox2f& area_bound */)
{
    /*
    mDof.initialize();
    GfxParameter::instance()->setDelegateForParameter(&mDof);
    mDof.setEnable(false);
    */

    /*
    const CourseDataFile* p_cd_file = CourseData::instance()->getFile(course_file);
    const AreaData* p_area_data = p_cd_file->getAreaData(area);
    const DistantViewData* p_dv_data = p_cd_file->getBg2Data(p_area_data->bg2);

    const ActorMgr::iterator itr_bg_center = ActorMgr::instance()->searchBaseByProfID(ProfileID::cBgCenter);
    if (itr_bg_center != ActorMgr::instance()->end())
    {
        BgCenter* p_bg_center = sead::DynamicCast<BgCenter>(*itr_bg_center);
        if (p_bg_center)
        {
            mBgPos = p_bg_center->getPosition();
            p_bg_center->requestDelete();
        }
    }
    else
    {
        mBgPos.set(area_bound.getCenter().x, BgScrollMgr::instance()->getBgCenterYPos(), 0.0f);
    }
    */

    /*
    sead::FixedSafeString<32> dv_fname("dv_");

    if (!p_dv_data)
        dv_fname.append("Nohara");

    else
        dv_fname.append(p_dv_data->name);

    sead::FixedSafeString<256> dv_path("distant_view/");
    dv_path.append(dv_fname);
    dv_path.append(".szs");
    {
        sead::Heap* heap = sead::FrameHeap::tryCreate(0, "DistantViewRes");
        ResMgr::instance()->loadArchiveRes(dv_fname, dv_path, heap, true);
        heap->adjust();
    }
    */

    if (mpArchive)
    {
        mArchiveRes.destroy();
        rio::MemUtil::free(mpArchive);
        mpArchive = nullptr;
    }

    rio::FileDevice::LoadArg arg;
    arg.path = "content://";
    arg.path += dv_fname;
    arg.path += ".szs";
    arg.alignment = 0x2000;

    mpArchive = SZSDecompressor::tryDecomp(arg);
    RIO_ASSERT(mpArchive);

    mArchiveRes.prepareArchive(mpArchive);

    /*
    sead::FixedSafeString<64> dv_subfile_fname(dv_fname);
    dv_subfile_fname.append(".opt");
    mEnvTagMgr.initialize(ResMgr::instance()->getFileFromArchiveRes(dv_fname, dv_subfile_fname));
    */

  //mEnvTagMgr.initialize(mArchiveRes.getFile(dv_fname + ".opt"));

    mpCameraParam = new DVCameraParam(this, &mBgPos, dv_fname);

    /*
    dv_subfile_fname = dv_fname;
    dv_subfile_fname.append(".baglenv");
    const void* p_env_file = ResMgr::instance()->getFileFromArchiveRes(dv_fname, dv_subfile_fname);
    if (p_env_file)
        sead::DynamicCast<RenderObjLayerBase>(agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_DistantView))->getRenderMgr()->loadEnvRes(p_env_file);
    */

    /*
    dv_subfile_fname = dv_fname;
    dv_subfile_fname.append(".bagldof");
    const void* p_dof_file = ResMgr::instance()->getFileFromArchiveRes(dv_fname, dv_subfile_fname);
    if (p_dof_file)
    {
        agl::utl::ResParameterArchive res_param_arc(p_dof_file);
        mDof.applyResParameterArchive(res_param_arc);
    }
    else
    {
        mDof.setEnable(false);
    }
    */

    /*
    EnvSetReader::read(sead::FormatFixedSafeString<128>("distant_view/%s.envset", dv_fname.cstr()));
    */

    const char* const dv_fname_c = dv_fname.c_str();

    mModelRes.load(&mArchiveRes, dv_fname_c);

    ModelNW* p_mdl = Model::createNW(mModelRes, dv_fname_c, 1, 1, 1, 2, 0, 0, Model::cBoundingMode_Enable);
    BasicModel* p_basic_mdl = new BasicModel(p_mdl, 1, 1, 2, 0, 0);
    p_basic_mdl->init(&mModelRes);
    mpBasicModel = p_basic_mdl;

    mpBasicModel->getModel()->setOpaBufferIdx(0);
    mpBasicModel->getModel()->setXluBufferIdx(0);

    // TODO: mpEffectMgr = new DistantViewEffectMgr(sead::HeapMgr::instance()->getCurrentHeap(), mpBasicModel->getModel(), this);
    // TODO: mpFFLMgr = ...

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
        /*
        nw::g3d::res::ResTexture* p_dof_ind = mModelRes.getResFile()->GetTexture(idx_dof_ind);

      //sead::Graphics::instance()->lockDrawContext();
        {
            agl::g3d::TextureDataInitializerG3D::initialize(&mDofIndTexture, *p_dof_ind);
        }
      //sead::Graphics::instance()->unlockDrawContext();

        mDof.setIndirectTextureData(&mDofIndTexture);
        mDof.setIndirectTextureTrans(mDofIndScroll);
        mDof.setIndirectEnable(true);
        */
    }

    calcView_();
    calcModelMtx_();

    mpBasicModel->updateModel();

    // TODO: mpEffectMgr
    mIsDrawParticle = true;

    // TODO: mpFFLMgr calc view

    // TODO: DistantViewEndMgr::processModel(mpBasicModel->getModel());
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

/*
void DistantViewMgr::pushBackDrawMethod()
{
    if (mIsDrawParticle)
    {
        mEffDrawMethod.bind(this, &DistantViewMgr::drawParticle_, "DistantViewMgr");
        agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_DistantView)->pushBackDrawMethod(RenderObjLayer::cRenderStep_Particle, &mEffDrawMethod);
    }

    mDofDrawMethod.bind(this, &DistantViewMgr::applyDepthOfField_, "DistantViewMgr");
    agl::lyr::Renderer::instance()->getLayer(AreaLayerMgr::cLayer_DistantView)->pushBackDrawMethod(RenderObjLayer::cRenderStep_PostFx, &mDofDrawMethod);
}
*/

void DistantViewMgr::update()
{
    calcView_();

    mpBasicModel->updateAnimations();
    mpBasicModel->updateModel();

    mDofIndScroll += mpCameraParam->getIndirectScrollSpd();

    mDofIndScroll.x = std::fmod(mDofIndScroll.x + 1.0f, 1.0f);
    mDofIndScroll.y = std::fmod(mDofIndScroll.y + 1.0f, 1.0f);

    /*
    mDof.setIndirectTextureTrans(mDofIndScroll);
    */
}

void DistantViewMgr::calcMdl()
{
    mpBasicModel->getModel()->calc();
}

void DistantViewMgr::calcGPU()
{
    const rio::Camera* p_camera = &mCamera;
    const rio::Projection* p_proj = &mProjection;

    rio::Matrix34f view_mtx;
    p_camera->getMatrix(&view_mtx);

    const rio::Matrix44f& proj_mtx = static_cast<const rio::Matrix44f&>(p_proj->getMatrix());

    mRenderMgr.getViewInfo(0).p_cull = &mCull;
    mRenderMgr.update(0, view_mtx, proj_mtx);

    mpBasicModel->getModel()->calcGPU(0, view_mtx, proj_mtx, &mRenderMgr);
}

void DistantViewMgr::drawOpa()
{
    const rio::Camera* p_camera = &mCamera;
    const rio::Projection* p_proj = &mProjection;

    /*
    rio::PrimitiveRenderer::instance()->setCamera(*p_camera);
    rio::PrimitiveRenderer::instance()->setProjection(*p_proj);

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::PrimitiveRenderer::instance()->drawCircle32({}, 16.f, rio::Color4f::cRed);
    }
    rio::PrimitiveRenderer::instance()->end();
    */

    rio::Matrix34f view_mtx;
    p_camera->getMatrix(&view_mtx);

    const rio::Matrix44f& proj_mtx = static_cast<const rio::Matrix44f&>(p_proj->getMatrix());

    mpBasicModel->getModel()->drawOpa(0, view_mtx, proj_mtx, &mRenderMgr);
}

void DistantViewMgr::drawXlu()
{
    const rio::Camera* p_camera = &mCamera;
    const rio::Projection* p_proj = &mProjection;

    /*
    rio::PrimitiveRenderer::instance()->setCamera(*p_camera);
    rio::PrimitiveRenderer::instance()->setProjection(*p_proj);

    rio::PrimitiveRenderer::instance()->begin();
    {
        rio::PrimitiveRenderer::instance()->drawCircle32({ 0.0f, 16.0f, 0.0f }, 16.f, rio::Color4f::cGreen);
    }
    rio::PrimitiveRenderer::instance()->end();
    */

    rio::Matrix34f view_mtx;
    p_camera->getMatrix(&view_mtx);

    const rio::Matrix44f& proj_mtx = static_cast<const rio::Matrix44f&>(p_proj->getMatrix());

    mpBasicModel->getModel()->drawXlu(0, view_mtx, proj_mtx, &mRenderMgr);
}
