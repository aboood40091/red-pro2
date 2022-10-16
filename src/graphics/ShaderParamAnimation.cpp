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

ShaderParamAnimation::~ShaderParamAnimation()
{
    if (mpBuffer)
    {
        rio::MemUtil::free(mpBuffer);
        mpBuffer = nullptr;
    }
}

bool ShaderParamAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    RIO_ASSERT(p_model != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    nw::g3d::ShaderParamAnimObj::InitArg arg;
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxMatAnimCount(0);
    arg.SetMaxParamAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::ShaderParamAnimObj::CalcBufferSize(arg);
    mpBuffer = rio::MemUtil::alloc(size, nw::g3d::ShaderParamAnimObj::BUFFER_ALIGNMENT);
    return mAnimObj.Init(arg, mpBuffer, size);
}

void ShaderParamAnimation::updateInitArg_(nw::g3d::ShaderParamAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    RIO_ASSERT(p_arg != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    const nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    for (s32 idx_anim = 0, num_anim = p_res_file->GetColorAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetColorAnim(idx_anim));

    for (s32 idx_anim = 0, num_anim = p_res_file->GetTexSrtAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetTexSrtAnim(idx_anim));
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

void ShaderParamAnimation::playColorAnim(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetColorAnimCount() > 0);
    s32 idx_anim = p_res_file->GetColorAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShaderParamAnim* p_res = p_res_file->GetColorAnim(idx_anim);
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

void ShaderParamAnimation::playTexSrtAnim(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetTexSrtAnimCount() > 0);
    s32 idx_anim = p_res_file->GetTexSrtAnimIndex(name);
    if (idx_anim < 0)
        return;

    nw::g3d::res::ResShaderParamAnim* p_res = p_res_file->GetTexSrtAnim(idx_anim);
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

void ShaderParamAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
