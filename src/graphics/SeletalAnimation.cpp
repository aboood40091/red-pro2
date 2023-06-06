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

SkeletalAnimation::~SkeletalAnimation()
{
    if (mpBuffer)
    {
        rio::MemUtil::free(mpBuffer);
        mpBuffer = nullptr;
    }
}

bool SkeletalAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    RIO_ASSERT(p_model != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    nw::g3d::SkeletalAnimObj::InitArg arg;
    arg.SetMaxBoneCount(p_model->getModelEx().GetResource()->GetSkeleton()->GetBoneCount());
    arg.SetMaxBoneAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::SkeletalAnimObj::CalcBufferSize(arg);
    mpBuffer = rio::MemUtil::alloc(size, nw::g3d::SkeletalAnimObj::BUFFER_ALIGNMENT);
    return mAnimObj.Init(arg, mpBuffer, size);
}

void SkeletalAnimation::updateInitArg_(nw::g3d::SkeletalAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    RIO_ASSERT(p_arg != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    const nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    for (s32 idx_anim = 0, num_anim = p_res_file->GetSkeletalAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetSkeletalAnim(idx_anim));
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

void SkeletalAnimation::play(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetSkeletalAnimCount() > 0);
    s32 idx_anim = p_res_file->GetSkeletalAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResSkeletalAnim* p_res = p_res_file->GetSkeletalAnim(idx_anim);
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
