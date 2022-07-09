#define override
#include <graphics/RenderObjEx.h>
#include <graphics/ShapeAnimation.h>

void ShapeAnimation::bindRenderObj(RenderObjEx* p_render_obj, s32 index)
{
    if (mpRenderObj)
        unbindRenderObj();

    mpRenderObj = p_render_obj;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void ShapeAnimation::unbindRenderObj()
{
    mpRenderObj = NULL;
    mIndex = -1;
}

void ShapeAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpRenderObj->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}
