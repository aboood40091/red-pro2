#define override
#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>
#include <graphics/VisibilityAnimation.h>

VisibilityAnimation::VisibilityAnimation()
    : Animation()
    , mAnimObj()
    , mpRes(nullptr)
    , mpModel(nullptr)
    , mIndex(-1)
    , mpBuffer(nullptr)
{
}

bool VisibilityAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    nw::g3d::VisibilityAnimObj::InitArg arg;
    arg.SetMaxBoneCount(p_model->getModelEx().GetResource()->GetSkeleton()->GetBoneCount());
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxBoneAnimCount(0);
  //arg.SetMaxMatAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (sead::PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::VisibilityAnimObj::CalcBufferSize(arg);
    mpBuffer = new (heap, nw::g3d::VisibilityAnimObj::BUFFER_ALIGNMENT) u8[size];
    return mAnimObj.Init(arg, mpBuffer, size);
}

void VisibilityAnimation::updateInitArg_(nw::g3d::VisibilityAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetBoneVisAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetBoneVisAnim(idx_anim));

    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetMatVisAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetMatVisAnim(idx_anim));
}

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
    mpModel = nullptr;
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

void VisibilityAnimation::playBoneVisAnim(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetBoneVisAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResVisibilityAnim* p_res = p_mdl_res->getResFile()->GetBoneVisAnim(idx_anim);
    mAnimObj.SetResource(p_res);

    mpRes = p_res;
    mFrameCtrl.setFrameStart(0);
    mFrameCtrl.setFrameEnd(p_res->GetFrameCount());
    mFrameCtrl.setFrameMax(p_res->GetFrameCount());
    mFrameCtrl.setRate(1.0f);
    mFrameCtrl.set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);
    mFrameCtrl.reset();

    if (mpModel)
        bindModel(mpModel, mIndex);
}

void VisibilityAnimation::playMatVisAnim(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetMatVisAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResVisibilityAnim* p_res = p_mdl_res->getResFile()->GetMatVisAnim(idx_anim);
    mAnimObj.SetResource(p_res);

    mpRes = p_res;
    mFrameCtrl.setFrameStart(0);
    mFrameCtrl.setFrameEnd(p_res->GetFrameCount());
    mFrameCtrl.setFrameMax(p_res->GetFrameCount());
    mFrameCtrl.setRate(1.0f);
    mFrameCtrl.set(FrameCtrl::cMode_Repeat, 1.0f, 0.0f);
    mFrameCtrl.reset();

    if (mpModel)
        bindModel(mpModel, mIndex);
}

void VisibilityAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
