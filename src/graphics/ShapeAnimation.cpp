#include <graphics/ModelG3d.h>
#include <graphics/ModelResource.h>
#include <graphics/ShapeAnimation.h>

ShapeAnimation::ShapeAnimation()
    : Animation()
    , mAnimObj()
    , mpRes(nullptr)
    , mpModel(nullptr)
    , mIndex(-1)
    , mpBuffer(nullptr)
{
}

ShapeAnimation::~ShapeAnimation()
{
    if (mpBuffer)
    {
        rio::MemUtil::free(mpBuffer);
        mpBuffer = nullptr;
    }
}

bool ShapeAnimation::init(const ModelG3d* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    RIO_ASSERT(p_model != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    nw::g3d::ShapeAnimObj::InitArg arg;
    arg.SetMaxShapeCount(p_model->getModelEx().GetResource()->GetShapeCount());
    arg.SetMaxVertexShapeAnimCount(0);
    arg.SetMaxKeyShapeAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::ShapeAnimObj::CalcBufferSize(arg);
    mpBuffer = rio::MemUtil::alloc(size, nw::g3d::ShapeAnimObj::BUFFER_ALIGNMENT);
    return mAnimObj.Init(arg, mpBuffer, size);
}

void ShapeAnimation::updateInitArg_(nw::g3d::ShapeAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    RIO_ASSERT(p_arg != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    const nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    for (s32 idx_anim = 0, num_anim = p_res_file->GetShapeAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetShapeAnim(idx_anim));
}

void ShapeAnimation::bindModel(const ModelG3d* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void ShapeAnimation::unbindModel()
{
    mpModel = nullptr;
    mIndex = -1;
}

void ShapeAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}

void ShapeAnimation::play(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetShapeAnimCount() > 0);
    s32 idx_anim = p_res_file->GetShapeAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShapeAnim* p_res = p_res_file->GetShapeAnim(idx_anim);
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

void ShapeAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
