#define override
#include <graphics/ModelNW.h>
#include <graphics/ModelResource.h>
#include <graphics/TexturePatternAnimation.h>

TexturePatternAnimation::TexturePatternAnimation()
    : Animation()
    , mAnimObj()
    , mpRes(NULL)
    , mpModel(NULL)
    , mIndex(-1)
  //, mpBuffer(NULL)
{
}

bool TexturePatternAnimation::init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    nw::g3d::TexPatternAnimObj::InitArg arg;
    arg.SetMaxMatCount(p_model->getModelEx().GetResource()->GetMaterialCount());
    arg.SetMaxMatAnimCount(0);
    arg.SetMaxPatAnimCount(0);
    arg.SetMaxCurveCount(0);

    updateInitArg_(&arg, p_mdl_res);
    if (p_anim_mdl_res_array)
    {
        for (sead::PtrArray<ModelResource>::constIterator itr = p_anim_mdl_res_array->constBegin(), itr_end = p_anim_mdl_res_array->constEnd(); itr != itr_end; ++itr)
            updateInitArg_(&arg, &(*itr));
    }

    size_t size = nw::g3d::TexPatternAnimObj::CalcBufferSize(arg);
    /* mpBuffer */ u8* p_buf = new (heap, nw::g3d::TexPatternAnimObj::BUFFER_ALIGNMENT) u8[size];
    return mAnimObj.Init(arg, /* mpBuffer */ p_buf, size);
}

void TexturePatternAnimation::updateInitArg_(nw::g3d::TexPatternAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res)
{
    for (s32 idx_anim = 0, num_anim = p_mdl_res->getResFile()->GetTexPatternAnimCount(); idx_anim < num_anim; idx_anim++)
        p_arg->Reserve(p_mdl_res->getResFile()->GetTexPatternAnim(idx_anim));
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
    mpModel = NULL;
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

void TexturePatternAnimation::play(const ModelResource* p_mdl_res, const sead::SafeString& name)
{
    s32 idx_anim = p_mdl_res->getResFile()->GetTexPatternAnimIndex(name.cstr());
  //if (idx_anim < 0)
  //    return;

    nw::g3d::res::ResTexPatternAnim* p_res = p_mdl_res->getResFile()->GetTexPatternAnim(idx_anim);
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

bool TexturePatternAnimation::forceBind(const sead::SafeString& name, const nw::g3d::res::ResTexture* p_texture)
{
    return mpRes->ForceBind(p_texture, name.cstr());
}

void TexturePatternAnimation::calc()
{
    if (!isValid())
        return;

    mAnimObj.GetFrameCtrl().SetFrame(mFrameCtrl.getFrame());
    mAnimObj.Calc();
}
