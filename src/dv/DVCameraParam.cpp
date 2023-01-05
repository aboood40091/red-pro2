#define override
#include <dv/DVCameraParam.h>

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
