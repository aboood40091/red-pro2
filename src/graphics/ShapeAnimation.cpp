#define override
#include <graphics/ModelNW.h>
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

bool ShapeAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    nw::g3d::ShapeAnimObj::InitArg arg;
    arg.SetMaxShapeCount(p_model->getModelEx().GetResource()->GetShapeCount());
    arg.SetMaxVertexShapeAnimCount(0);
    arg.SetMaxKeyShapeAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (sead::PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::ShapeAnimObj::CalcBufferSize(arg);
    mpBuffer = new (heap, nw::g3d::ShapeAnimObj::BUFFER_ALIGNMENT) u8[size];
    return mAnimObj.Init(arg, mpBuffer, size);
}

void ShapeAnimation::updateInitArg_(nw::g3d::ShapeAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetShapeAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetShapeAnim(idx_anim));
}

void ShapeAnimation::bindModel(const ModelNW* p_model, s32 index)
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

void ShapeAnimation::play(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetShapeAnimIndex(name.cstr());
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShapeAnim* p_res = p_mdl_res->getResFile()->GetShapeAnim(idx_anim);
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

void ShapeAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
