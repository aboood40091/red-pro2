#define override
#include <graphics/ModelNW.h>
#include <graphics/VisibilityAnimation.h>

void VisibilityAnimation::bindModel(const ModelNW* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void VisibilityAnimation::unbindModel()
{
    mpModel = NULL;
    mIndex = -1;
}

void VisibilityAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}
