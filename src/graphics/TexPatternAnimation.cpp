#define override
#include <graphics/RenderObjEx.h>
#include <graphics/TexPatternAnimation.h>

void TexPatternAnimation::bindRenderObj(RenderObjEx* p_render_obj, s32 index)
{
    if (mpRenderObj)
        unbindRenderObj();

    mpRenderObj = p_render_obj;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void TexPatternAnimation::unbindRenderObj()
{
    mpRenderObj = NULL;
    mIndex = -1;
}

void TexPatternAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpRenderObj->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}
