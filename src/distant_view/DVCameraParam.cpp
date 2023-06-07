#include <distant_view/DistantViewMgr.h>
#include <distant_view/DVCameraParam.h>

DVCameraParam::DVCameraParam(DistantViewMgr* dv_mgr, const rio::Vector3f* p_bg_pos, const std::string& dv_name)
    : mProjOffset           (rio::Vector2f{0.0f, 0.0f}, &mParamList, "mProjOffset")
    , mTypeDirY             (0,                         &mParamList, "mTypeDirY")
    , mMagnifProjOffsetY    (0.3f,                      &mParamList, "mMagnifProjOffsetY")
    , mMagnifCameraPosY     (0.0f,                      &mParamList, "mMagnifCameraPosY")
    , mModelOffsetX         (0.0f,                      &mParamList, "mModelOffsetX")
    , mModelOffsetY         (0.0f,                      &mParamList, "mModelOffsetY")
    , mModelOffsetZ         (0.0f,                      &mParamList, "mModelOffsetZ")
    , mIndirectScrollSpd    (rio::Vector2f{0.0f, 0.0f}, &mParamList, "mIndirectScrollSpd")
    , mpBgPos(p_bg_pos)
{
    u32 size = 0;
    const void* file = dv_mgr->mArchiveRes.getFile((dv_name + ".camera").c_str(), &size);

    if (file)
        mParamList.read(file, size);
}

void DVCameraParam::getModelMtx(rio::Matrix34f* p_model_mtx) const
{
    rio::Vector3f model_offset {
        *mModelOffsetX,
        *mModelOffsetY,
        *mModelOffsetZ
    };
    model_offset += *mpBgPos;

    p_model_mtx->makeT(model_offset);
}
