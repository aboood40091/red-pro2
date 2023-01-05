#pragma once

#include <dv/DVCameraParamList.h>

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

class DistantViewMgr;

class DVCameraParam : public sead::IDisposer
{
public:
    DVCameraParam(DistantViewMgr* dv_mgr, const sead::Vector3f* p_bg_pos, const sead::SafeString& dv_name);

    const sead::Vector2f& getProjOffset() const { return mProjOffset.getValue(); }
    s32 getTypeDirY() const { return mTypeDirY.getValue(); }
    f32 getMagnifProjOffsetY() const { return mMagnifProjOffsetY.getValue(); }
    f32 getMagnifCameraPosY() const { return mMagnifCameraPosY.getValue(); }
    const sead::Vector2f& getIndirectScrollSpd() const { return mIndirectScrollSpd.getValue(); }

    void getModelMtx(sead::Matrix34f* p_model_mtx) const;

private:
    DVCameraParamList mParamList;
    ParamVec2f mProjOffset;
    ParamS32 mTypeDirY;
    ParamF32 mMagnifProjOffsetY;
    ParamF32 mMagnifCameraPosY;
    ParamF32 mModelOffsetX;
    ParamF32 mModelOffsetY;
    ParamF32 mModelOffsetZ;
    ParamVec2f mIndirectScrollSpd;
    const sead::Vector3f* mpBgPos;
};
