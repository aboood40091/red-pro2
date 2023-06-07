#pragma once

#include <distant_view/DVCameraParamList.h>

#include <math/rio_Matrix.h>

#include <string>

class DistantViewMgr;

class DVCameraParam
{
public:
    DVCameraParam(DistantViewMgr* dv_mgr, const rio::Vector3f* p_bg_pos, const std::string& dv_fname);

    const rio::Vector2f& getProjOffset() const { return *mProjOffset; }
    s32 getTypeDirY() const { return *mTypeDirY; }
    f32 getMagnifProjOffsetY() const { return *mMagnifProjOffsetY; }
    f32 getMagnifCameraPosY() const { return *mMagnifCameraPosY; }
    const rio::Vector2f& getIndirectScrollSpd() const { return *mIndirectScrollSpd; }

    void getModelMtx(rio::Matrix34f* p_model_mtx) const;

private:
    DVCameraParamList       mParamList;
    ParamVec2               mProjOffset;
    ParamU32                mTypeDirY;
    ParamF32                mMagnifProjOffsetY;
    ParamF32                mMagnifCameraPosY;
    ParamF32                mModelOffsetX;
    ParamF32                mModelOffsetY;
    ParamF32                mModelOffsetZ;
    ParamVec2               mIndirectScrollSpd;
    const rio::Vector3f*    mpBgPos;
};
//static_assert(sizeof(DVCameraParam) == 0x16C);
