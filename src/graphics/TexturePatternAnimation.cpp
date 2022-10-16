#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>
#include <graphics/TexturePatternAnimation.h>

TexturePatternAnimation::TexturePatternAnimation()
    : Animation()
    , mAnimObj()
    , mpRes(nullptr)
    , mpModel(nullptr)
    , mIndex(-1)
    , mpBuffer(nullptr)
{
}

TexturePatternAnimation::~TexturePatternAnimation()
{
    if (mpBuffer)
    {
        rio::MemUtil::free(mpBuffer);
        mpBuffer = nullptr;
    }
}

bool TexturePatternAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    RIO_ASSERT(p_model != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    nw::g3d::TexPatternAnimObj::InitArg arg;
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxMatAnimCount(0);
    arg.SetMaxPatAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::TexPatternAnimObj::CalcBufferSize(arg);
    mpBuffer = rio::MemUtil::alloc(size, nw::g3d::TexPatternAnimObj::BUFFER_ALIGNMENT);
    return mAnimObj.Init(arg, mpBuffer, size);
}

void TexturePatternAnimation::updateInitArg_(nw::g3d::TexPatternAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    RIO_ASSERT(p_arg != nullptr);
    RIO_ASSERT(p_mdl_res != nullptr);

    const nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    for (s32 idx_anim = 0, num_anim = p_res_file->GetTexPatternAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_res_file->GetTexPatternAnim(idx_anim));
}

void TexturePatternAnimation::bindModel(const ModelNW* p_model, s32 index)
{
    if (mpModel)
        unbindModel();

    mpModel = p_model;
    mIndex = index;

    if (mpRes)
        bindAnimObj_();
}

void TexturePatternAnimation::unbindModel()
{
    mpModel = nullptr;
    mIndex = -1;
}

void TexturePatternAnimation::bindAnimObj_()
{
    if (mpRes)
    {
        mAnimObj.Bind(mpModel->getModelEx().GetResource());
        mAnimObj.ClearResult();
    }
}

void TexturePatternAnimation::play(const ModelResource* p_mdl_res, const char* name)
{
    RIO_ASSERT(p_mdl_res != nullptr);
    RIO_ASSERT(name != nullptr);

    nw::g3d::res::ResFile* p_res_file = p_mdl_res->getResFile();
    RIO_ASSERT(p_res_file != nullptr);

    RIO_ASSERT(p_res_file->GetTexPatternAnimCount() > 0);
    s32 idx_anim = p_res_file->GetTexPatternAnimIndex(name);
    RIO_ASSERT(idx_anim >= 0);

    nw::g3d::res::ResTexPatternAnim* p_res = p_res_file->GetTexPatternAnim(idx_anim);
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

bool TexturePatternAnimation::forceBind(const char* name, const nw::g3d::res::ResTexture* p_texture)
{
    return mpRes->ForceBind(p_texture, name);
}

void TexturePatternAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
