#define override
#include <graphics/ModelNW.h>
#include <graphics/SkeletalAnimation.h>

void SkeletalAnimation::bindModel(const ModelNW* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void SkeletalAnimation::unbindModel()
{
    mpModel = NULL;
    mIndex = -1;
}

void SkeletalAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpModel->getModelEx().GetSkeleton()->GetResource());
}
