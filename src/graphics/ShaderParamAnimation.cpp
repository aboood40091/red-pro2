#define override
#include <graphics/RenderObjEx.h>
#include <graphics/ShaderParamAnimation.h>

void ShaderParamAnimation::bindRenderObj(RenderObjEx* p_render_obj, s32 index)
{
    if (mpRenderObj)
        unbindRenderObj();

    mpRenderObj = p_render_obj;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void ShaderParamAnimation::unbindRenderObj()
{
    mpRenderObj = NULL;
    mIndex = -1;
}

void ShaderParamAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpRenderObj->getModelEx().GetResource());
}
