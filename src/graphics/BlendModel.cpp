#include <graphics/BlendModel.h>
#include <graphics/ModelNW.h>

BlendModel::BlendModel(ModelNW* p_model, u32 skl_anim_num, u32 tex_anim_num, u32 shu_anim_num, u32 vis_anim_num, u32 sha_anim_num)
    : BasicModel(p_model, skl_anim_num, tex_anim_num, shu_anim_num, vis_anim_num, sha_anim_num)
    , mCurAnmIdx(0)
{
    // Need to assert that skl_anim_num <= 2
}

void BlendModel::init(ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    BasicModel::init(p_mdl_res, p_anim_mdl_res_array, heap);
}

void BlendModel::updateAnimations()
{
    BasicModel::updateAnimations();
}

void BlendModel::updateModel()
{
    calcBlend();
    BasicModel::updateModel();
}

void BlendModel::calcBlend()
{
    if (mCalcRatio.isActive())
    {
        mCalcRatio.calc();

        ModelNW* p_model = getModel();
        p_model->setSklAnimBlendWeight(mCurAnmIdx,      mCalcRatio.ratioB());   // Target animation
        p_model->setSklAnimBlendWeight(mCurAnmIdx ^ 1,  mCalcRatio.ratioA());   // Source animation
    }
}

void BlendModel::setAnimation(
    ModelResource* p_mdl_res,
    const sead::SafeString& name,
    f32 blend_duration
)
{
    setAnimation_(p_mdl_res, name, blend_duration);
}

void BlendModel::setAnimation(
    const sead::SafeString& name,
    f32 blend_duration,
    FrameCtrl::PlayMode mode,
    f32 rate,
    f32 frame
)
{
    setAnimation_(getModelResource(), name, blend_duration, mode, rate, frame);
}

void BlendModel::setAnimation(
    const sead::SafeString& name,
    FrameCtrl::PlayMode mode,
    f32 rate,
    f32 frame
)
{
    setAnimation_(getModelResource(), name, 0.0f, mode, rate, frame);
}

void BlendModel::setAnimation_(
    ModelResource* p_mdl_res,
    const sead::SafeString& name,
    f32 blend_duration,
    FrameCtrl::PlayMode mode,
    f32 rate,
    f32 frame
)
{
    // Slightly non-matching, but who cares

    if (blend_duration == 0.0f)
    {
        mCalcRatio.reset();

        ModelNW* p_model = getModel();
        p_model->setSklAnimBlendWeight(mCurAnmIdx,      1.0f);  // Target animation
        p_model->setSklAnimBlendWeight(mCurAnmIdx ^ 1,  0.0f);  // Source animation
    }
    else if (getSklAnim(mCurAnmIdx)->getResource() != nullptr)
    {
        mCurAnmIdx ^= 1;

        mCalcRatio.set(blend_duration);

        ModelNW* p_model = getModel();
        p_model->setSklAnimBlendWeight(mCurAnmIdx,      0.0f);  // Target animation
        p_model->setSklAnimBlendWeight(mCurAnmIdx ^ 1,  1.0f);  // Source animation
    }

    getSklAnim(mCurAnmIdx)->play(p_mdl_res, name);
    getSklAnim(mCurAnmIdx)->getFrameCtrl().set(mode, rate, frame);
}
