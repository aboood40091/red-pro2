#define override
#include <graphics/ModelNW.h>
#include <graphics/TexturePatternAnimation.h>

void TexturePatternAnimation::bindModel(const ModelNW* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void TexturePatternAnimation::unbindModel()
{
    mpModel = NULL;
    mIndex = -1;
}

void TexturePatternAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}
