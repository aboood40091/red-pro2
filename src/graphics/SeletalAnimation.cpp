#define override
#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>
#include <graphics/SkeletalAnimation.h>

SkeletalAnimation::SkeletalAnimation()
    : Animation()
    , mAnimObj()
    , mpBuffer(nullptr)
    , mpModel(nullptr)
    , mIndex(-1)
    , mpRes(nullptr)
{
}

bool SkeletalAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    nw::g3d::SkeletalAnimObj::InitArg arg;
    arg.SetMaxBoneCount(p_model->getModelEx().GetResource()->GetSkeleton()->GetBoneCount());
    arg.SetMaxBoneAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (sead::PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::SkeletalAnimObj::CalcBufferSize(arg);
    mpBuffer = new (heap, nw::g3d::SkeletalAnimObj::BUFFER_ALIGNMENT) u8[size];
    return mAnimObj.Init(arg, mpBuffer, size);
}

void SkeletalAnimation::updateInitArg_(nw::g3d::SkeletalAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetSkeletalAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetSkeletalAnim(idx_anim));
}

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
    mpModel = nullptr;
    mIndex = -1;
}

void SkeletalAnimation::bindAnimObj_()
{
    if (mpRes)
        mAnimObj.Bind(mpModel->getModelEx().GetSkeleton()->GetResource());
}

void SkeletalAnimation::play(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetSkeletalAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResSkeletalAnim* p_res = p_mdl_res->getResFile()->GetSkeletalAnim(idx_anim);
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

void SkeletalAnimation::unbindTarget(s32 idx_target)
{
    nw::g3d::AnimBindTable& bind_tbl = mAnimObj.GetBindTable();

    s32 idx_anim = bind_tbl.GetAnimIndex(idx_target);
    if (idx_anim != nw::g3d::AnimBindTable::NOT_BOUND)
        bind_tbl.Unbind(idx_anim, idx_target);
}

void SkeletalAnimation::disableBindFlag()
{
    nw::g3d::AnimBindTable& bind_tbl = mAnimObj.GetBindTable();

    for (s32 i = 0, num_anim = bind_tbl.GetAnimCount(); i < num_anim; i++)
        bind_tbl.SetBindFlag(i, nw::g3d::AnimBindTable::DISABLED);
}

void SkeletalAnimation::enableBindFlag(s32 idx_bone)
{
    if (mpModel)
        mAnimObj.SetBindFlag(mpModel->getModelEx().GetSkeleton()->GetResource(), idx_bone, nw::g3d::AnimObj::ENABLED);
}

void SkeletalAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
