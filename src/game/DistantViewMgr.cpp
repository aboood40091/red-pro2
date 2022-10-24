#include <game/DistantViewMgr.h>
#include <game/DistantViewMgrCameraParam.h>
#include <game/PtclMgr.h>
#include <game/course/AreaTask.h>
#include <game/course/Quake.h>
#include <graphics/BasicModel.h>
#include <graphics/Model.h>
#include <scroll/BgScrollMgr.h>

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <layer/aglRenderInfo.h>

SEAD_SINGLETON_DISPOSER_IMPL(DistantViewMgr)

DistantViewMgr::DistantViewMgr()
    : mNear(100.0f)
    , mFar(80000.0f)
    , mFovyDeg(20.0f)
    , mScale(1.0f)
    , mCameraBasePos(0.0f, 0.0f, 0.0f)
    , mCameraPosOffset(0.0f, 0.0f, 0.0f)
    , mCameraPos(0.0f, 0.0f, 0.0f)
    , mCameraAtOffset(0.0f, 0.0f, 0.0f)
    , mCamera()
    , mProjection(mNear, mFar, sead::Mathf::deg2rad(mFovyDeg), 16.f / 9.f)
    , mCull()
    , mpBasicModel(NULL)
    , mOpt()
    , mpCameraParam(NULL)
    , mpEffectMgr(NULL)
    , mpFFLMgr(NULL)
    , mBgPos(0.0f, 0.0f, 0.0f)
    , mAreaMinY(AreaTask::instance()->getBound().getMin().y)
    , mDof()
    , mDofIndTexture()
    , mDofIndScroll(0.0f, 0.0f)
    , mEffDrawMethod()
    , mDofDrawMethod()
    , mIsKoopalingShipFlying(false)
    , mIsFlickerEnable(true)
    , mFlickerCounter(0)
    , mFlickerOffset(0.375f, 0.375f)
{
}

void DistantViewMgr::calcView_()
{
    mProjection.setOffset(mpCameraParam->getProjOffset());

    f32 fovy_tan = sead::Mathf::tan(sead::Mathf::deg2rad(mFovyDeg * 0.5f));

    f32 screen_center_x = BgScrollMgr::instance()->getScreenCenterX();
    f32 screen_center_y = BgScrollMgr::instance()->getScreenCenterY() - BgScrollMgr::instance()->getScrollEffectMgr()._3c._8;

    f32 base_z = (112.0f / fovy_tan) * BgScrollMgr::instance()->getZoom() * mScale;

    fovy_tan = sead::Mathf::tan(sead::Mathf::deg2rad(mFovyDeg * 0.5f)); // ???????????? ok
    fovy_tan = base_z * fovy_tan * 2;

    mCameraBasePos.z = base_z;

    mCameraBasePos.x = screen_center_x - fovy_tan * mpCameraParam->getProjOffset().x;
    mCameraBasePos.y = screen_center_y - fovy_tan * mpCameraParam->getProjOffset().y;
    if (mpCameraParam->getTypeDirY() == 1)
        mCameraBasePos.y += mpCameraParam->getMagnifCameraPosY() * (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY);

    mCameraPos.set(mCameraBasePos + mCameraPosOffset);

    sead::Vector2f proj_base_offs(0.0f, 0.0f);
    if (Quake::instance())
        proj_base_offs = Quake::instance()->getOffset();
    if (mpCameraParam->getTypeDirY() == 0)
        proj_base_offs.y += mpCameraParam->getMagnifProjOffsetY() * (BgScrollMgr::instance()->getScreenBottom() - mAreaMinY);

    if (proj_base_offs.x != 0.0f || proj_base_offs.y != 0.0f)
    {
        f32 proj_offset_x = mProjection.getOffset().x + proj_base_offs.x / 1280;
        f32 proj_offset_y = mProjection.getOffset().y + proj_base_offs.y / 720;

        proj_base_offs.set(proj_offset_x, proj_offset_y);
        mProjection.setOffset(proj_base_offs);
    }

    if (mIsFlickerEnable)
    {
        f32 flicker_proj_offs_x = (mFlickerOffset.x * 0.5f) / 1280;
        f32 flicker_proj_offs_y = (mFlickerOffset.y * 0.5f) / 720;

        sead::Vector2f proj_offset = mProjection.getOffset();

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

    sead::Vector3f at = mCameraPos + mCameraAtOffset;

    mCamera.getAt().set(at.x, at.y, at.z - 1.0f);
    mCamera.getPos().set(mCameraPos);
    mCamera.updateViewMatrix();

    mCull.update(mCamera, mProjection);
}

void DistantViewMgr::calcModelMtx_()
{
    Model* p_model = mpBasicModel->getModel();

    sead::Matrix34f model_mtx;
    mpCameraParam->getModelMtx(&model_mtx);

    p_model->setMtxRT(model_mtx);
}

void DistantViewMgr::drawParticle_(const agl::lyr::RenderInfo& render_info)
{
    PtclMgr::instance()->draw(render_info, 0);
}

void DistantViewMgr::applyDepthOfField_(const agl::lyr::RenderInfo& render_info)
{
    const agl::RenderBuffer* p_render_buffer = static_cast<const agl::RenderBuffer*>(render_info.getFrameBuffer());
    if (!p_render_buffer)
        return;

    p_render_buffer->getColorTarget()->expandAuxBuffer();
    p_render_buffer->getDepthTarget()->expandHiZBuffer();

    mDof.draw(0, *p_render_buffer, mProjection.getNear(), mProjection.getFar());
}
