#pragma once

#include <distant_view/DVCameraParamList.h>

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

class DistantViewMgr;

class DVCameraParam : public sead::IDisposer
{
public:
    DVCameraParam(DistantViewMgr* dv_mgr, const sead::Vector3f* p_bg_pos, const sead::SafeString& dv_name);

    const sead::Vector2f& getProjOffset() const { return *mProjOffset; }
    s32 getTypeDirY() const { return *mTypeDirY; }
    f32 getMagnifProjOffsetY() const { return *mMagnifProjOffsetY; }
    f32 getMagnifCameraPosY() const { return *mMagnifCameraPosY; }
    const sead::Vector2f& getIndirectScrollSpd() const { return *mIndirectScrollSpd; }

    void getModelMtx(sead::Matrix34f* p_model_mtx) const;

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
    const sead::Vector3f*   mpBgPos;
};
static_assert(sizeof(DVCameraParam) == 0x16C);
