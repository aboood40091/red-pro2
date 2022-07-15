#define override
#include <graphics/ModelNW.h>
#include <graphics/ShaderParamAnimation.h>

void ShaderParamAnimation::bindModel(const ModelNW* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void ShaderParamAnimation::unbindModel()
{
    mpModel = NULL;
    mIndex = -1;
}

void ShaderParamAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
}
