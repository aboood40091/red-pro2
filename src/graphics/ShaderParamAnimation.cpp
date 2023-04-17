#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>
#include <graphics/ShaderParamAnimation.h>

ShaderParamAnimation::ShaderParamAnimation()
    : Animation()
    , mAnimObj()
    , mpRes(nullptr)
    , mpModel(nullptr)
    , mIndex(-1)
    , mpBuffer(nullptr)
{
}

bool ShaderParamAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    nw::g3d::ShaderParamAnimObj::InitArg arg;
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxMatAnimCount(0);
    arg.SetMaxParamAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (sead::PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::ShaderParamAnimObj::CalcBufferSize(arg);
    mpBuffer = new (heap, nw::g3d::ShaderParamAnimObj::BUFFER_ALIGNMENT) u8[size];
    return mAnimObj.Init(arg, mpBuffer, size);
}

void ShaderParamAnimation::updateInitArg_(nw::g3d::ShaderParamAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetColorAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetColorAnim(idx_anim));

    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetTexSrtAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetTexSrtAnim(idx_anim));
}

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
    mpModel = nullptr;
    mIndex = -1;
}

void ShaderParamAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
}

void ShaderParamAnimation::playColorAnim(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetColorAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShaderParamAnim* p_res = p_mdl_res->getResFile()->GetColorAnim(idx_anim);
    mAnimObj.SetResource(p_res);

    mpRes = p_res;
    mFrameCtrl.setFrameStart(0);
    mFrameCtrl.setFrameEnd(p_res->GetFrameCount());
    mFrameCtrl.setFrameMax(p_res->GetFrameCount());
    mFrameCtrl.setRate(1.0f);
    mFrameCtrl.setPlayMode(FrameCtrl::cMode_Repeat);
    mFrameCtrl.setFrame(0.0f);
    mFrameCtrl.reset();

    if (mpModel)
        bindModel(mpModel, mIndex);
}

void ShaderParamAnimation::playTexSrtAnim(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetTexSrtAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShaderParamAnim* p_res = p_mdl_res->getResFile()->GetTexSrtAnim(idx_anim);
    mAnimObj.SetResource(p_res);

    mpRes = p_res;
    mFrameCtrl.setFrameStart(0);
    mFrameCtrl.setFrameEnd(p_res->GetFrameCount());
    mFrameCtrl.setFrameMax(p_res->GetFrameCount());
    mFrameCtrl.setRate(1.0f);
    mFrameCtrl.setPlayMode(FrameCtrl::cMode_Repeat);
    mFrameCtrl.setFrame(0.0f);
    mFrameCtrl.reset();

    if (mpModel)
        bindModel(mpModel, mIndex);
}

void ShaderParamAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
