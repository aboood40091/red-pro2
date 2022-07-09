#define override
#include <graphics/RenderObjEx.h>
#include <graphics/SkeletalAnimation.h>

void SkeletalAnimation::bindRenderObj(RenderObjEx* p_render_obj, s32 index)
{
    if (mpRenderObj)
        unbindRenderObj();

    mpRenderObj = p_render_obj;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void SkeletalAnimation::unbindRenderObj()
{
    mpRenderObj = NULL;
    mIndex = -1;
}

void SkeletalAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpRenderObj->getModelEx().GetSkeleton()->GetResource());
}
