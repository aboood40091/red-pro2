#include <graphics/AnimExpDecayCalcRatio.h>
#include <graphics/Model.h>

AnimExpDecayCalcRatio::AnimExpDecayCalcRatio(s32 bone_num_max)
    : mBoneNumMax(bone_num_max)
    , mBlendWeight(0.0f)
    , mCounter(0.0f)
    , mInvDuration(0.0f)
    , mRatioA(0.0f)
    , mRatioB(0.0f)
    , mIsFramesPrepared(false)
    , mIsActive(false)
{
    mBoneTrans.allocBuffer(bone_num_max);
    mBoneRot.allocBuffer(bone_num_max);
    mBoneScale.allocBuffer(bone_num_max);

    mBoneFlag.allocBuffer(bone_num_max);
    mBoneFlag.fill(cBoneFlag_BlendEnable);
}

AnimExpDecayCalcRatio::~AnimExpDecayCalcRatio()
{
}

void AnimExpDecayCalcRatio::reset()
{
    mBlendWeight = 0.0f;
    mCounter = 1.0f;
    mRatioA = 0.0f;
    mRatioB = 1.0f;
}

void AnimExpDecayCalcRatio::set(f32 duration)
{
    if (duration == 0.0f)
        reset();
    else
    {
        mBlendWeight = 1.0f;
        mCounter = 0.0f;
        mInvDuration = 1.0f / duration;
        mRatioA = 1.0f;
        mRatioB = 0.0f;
        mIsActive = true;
    }
}

void AnimExpDecayCalcRatio::calc()
{
    if (mBlendWeight == 0.0f)
        return;

    mCounter += mInvDuration;
    if (mCounter >= 1.0f)
        reset();
    else
    {
        f32 w_prev = mBlendWeight;
        f32 w_next = w_prev - w_prev * mCounter * mCounter; // Exponential decay

        f32 ratio_a = w_next / w_prev;
        f32 ratio_b = 1.0f - w_next;
        f32 inv_mag = 1.0f / (ratio_a + ratio_b);

        mBlendWeight = w_next;
        mRatioA = ratio_a * inv_mag;
        mRatioB = ratio_b * inv_mag;
        mIsActive = true;
    }
}

bool AnimExpDecayCalcRatio::isFramesPrepared() const
{
    if (!mIsFramesPrepared)
        return false;

    if (mBlendWeight == 0.0f)
        return false;

    return true;
}

bool AnimExpDecayCalcRatio::isBlendDisable(s32 bone_index) const
{
    return mBoneFlag[bone_index] != cBoneFlag_BlendEnable;
}

void AnimExpDecayCalcRatio::applyTo(sead::Matrixf* p_bone_rt, sead::Vector3f* p_bone_scale, s32 bone_index)
{
    if (!isFramesPrepared() || isBlendDisable(bone_index))
    {
        p_bone_rt->getTranslation(mBoneTrans[bone_index]);
        p_bone_rt->toQuat(mBoneRot[bone_index]);
        mBoneScale[bone_index] = *p_bone_scale;
        return;
    }

    if (!mIsActive)
        return;

    sead::Vector3f scale_A = mBoneScale[bone_index] * mRatioA;
    sead::Vector3f scale_B = (*p_bone_scale) * mRatioB;
    sead::Vector3f scale = scale_A + scale_B;

    const sead::Quatf& quat_A = mBoneRot[bone_index];
    sead::Quatf quat_B;
    p_bone_rt->toQuat(quat_B);
    sead::Quatf quat;
    quat.setSlerp(quat_A, quat_B, mRatioB);

    sead::Vector3f trans_A = mBoneTrans[bone_index];
    trans_A *= mRatioA;
    sead::Vector3f trans_B;
    p_bone_rt->getTranslation(trans_B);
    trans_B *= mRatioB;

    mBoneTrans[bone_index] = trans_A + trans_B;
    mBoneRot[bone_index] = quat;
    mBoneScale[bone_index] = scale;

    p_bone_rt->fromQuat(quat);
    p_bone_rt->setTranslation(trans_A + trans_B);
    *p_bone_scale = scale;
}

void AnimExpDecayCalcRatio::offUpdate()
{
    mIsFramesPrepared = true;
    mIsActive = false;
}

void AnimExpDecayCalcRatio::applyTo(Model* p_model)
{
    s32 bone_num = p_model->getBoneNum();
    for (s32 i = 0; i < bone_num; i++)
    {
        sead::Matrixf bone_rt;
        sead::Vector3f bone_scale;
        p_model->getBoneLocalMatrix(i, &bone_rt, &bone_scale);
        applyTo(&bone_rt, &bone_scale, i);
        p_model->setBoneLocalMatrix(i, bone_rt, bone_scale);
    }
    offUpdate();
}

void AnimExpDecayCalcRatio::setBlendDisable(s32 bone_index)
{
    mBoneFlag[bone_index] = cBoneFlag_BlendDisable;
}
