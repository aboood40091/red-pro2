#include <graphics/ModelG3d.h>
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

VisibilityAnimation::~VisibilityAnimation()
{
    if (mpBuffer)
    {
        rio::MemUtil::free(mpBuffer);
        mpBuffer = nullptr;
    }
}

bool VisibilityAnimation::init(const ModelG3d* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    RIO_ASSERT(p_model != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    nw::g3d::VisibilityAnimObj::InitArg arg;
    arg.SetMaxBoneCount(p_model->getModelEx().GetResource()->GetSkeleton()->GetBoneCount());
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxBoneAnimCount(0);
  //arg.SetMaxMatAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::VisibilityAnimObj::CalcBufferSize(arg);
    mpBuffer = rio::MemUtil::alloc(size, nw::g3d::VisibilityAnimObj::BUFFER_ALIGNMENT);
    return mAnimObj.Init(arg, mpBuffer, size);
}

void VisibilityAnimation::updateInitArg_(nw::g3d::VisibilityAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    RIO_ASSERT(p_arg != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    const nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    for (s32 idx_anim = 0, num_anim = p_res_file->GetBoneVisAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetBoneVisAnim(idx_anim));

    for (s32 idx_anim = 0, num_anim = p_res_file->GetMatVisAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetMatVisAnim(idx_anim));
}

void VisibilityAnimation::bindModel(const ModelG3d* p_model, s32 index)
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

void VisibilityAnimation::playBoneVisAnim(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetBoneVisAnimCount() > 0);
    s32 idx_anim = p_res_file->GetBoneVisAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResVisibilityAnim* p_res = p_res_file->GetBoneVisAnim(idx_anim);
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

void VisibilityAnimation::playMatVisAnim(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetMatVisAnimCount() > 0);
    s32 idx_anim = p_res_file->GetMatVisAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResVisibilityAnim* p_res = p_res_file->GetMatVisAnim(idx_anim);
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

void VisibilityAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
