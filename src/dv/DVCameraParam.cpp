#define override
#include <dv/DVCameraParam.h>
#include <system/ResMgr.h>

DVCameraParam::DVCameraParam(DistantViewMgr* dv_mgr, const sead::Vector3f* p_bg_pos, const sead::SafeString& dv_name)
    : mProjOffset           (sead::Vector2f(0.0f, 0.0f),    &mParamList, "mProjOffset")
    , mTypeDirY             (0,                             &mParamList, "mTypeDirY")
    , mMagnifProjOffsetY    (0.3f,                          &mParamList, "mMagnifProjOffsetY")
    , mMagnifCameraPosY     (0.0f,                          &mParamList, "mMagnifCameraPosY")
    , mModelOffsetX         (0.0f,                          &mParamList, "mModelOffsetX")
    , mModelOffsetY         (0.0f,                          &mParamList, "mModelOffsetY")
    , mModelOffsetZ         (0.0f,                          &mParamList, "mModelOffsetZ")
    , mIndirectScrollSpd    (sead::Vector2f(0.0f, 0.0f),    &mParamList, "mIndirectScrollSpd")
    , mpBgPos(p_bg_pos)
{
    sead::FixedSafeString<64> dv_camera_fname(dv_name);
    dv_camera_fname.append(".camera");

    u32 size = 0;
    const void* file = ResMgr::instance()->getFileFromArchiveRes(dv_name, dv_camera_fname, &size);

    if (file)
        mParamList.read(file, size);
}

void DVCameraParam::getModelMtx(sead::Matrix34f* p_model_mtx) const
{
    sead::Vector3f model_offset(
        *mModelOffsetX,
        *mModelOffsetY,
        *mModelOffsetZ
    );
    model_offset += *mpBgPos;

    p_model_mtx->makeT(model_offset);
}
