#pragma once

#include <graphics/Animation.h>

#include <container/PtrArray.h>

#include <nw/g3d/g3d_SkeletalAnimObj.h>

class ModelG3d;
class ModelResource;

class SkeletalAnimation : public Animation
{
public:
    SkeletalAnimation();
    ~SkeletalAnimation();

    bool init(const ModelG3d* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array);

    bool isValid() const { return mpRes && mpModel; }

    void bindModel(const ModelG3d* p_model, s32 index);
    void unbindModel();

private:
    void bindAnimObj_();

public:
    void play(const ModelResource* p_mdl_res, const char* name);

    void unbindTarget(s32 idx_target);

    void disableBindFlag();
    void enableBindFlag(s32 idx_bone);

    void calc() override;

    nw::g3d::SkeletalAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::SkeletalAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResSkeletalAnim* getResource() const { return mpRes; }

    const ModelG3d* getModel() const { return mpModel; }
    s32 getIndex() const { return mIndex; }

private:
    static void updateInitArg_(nw::g3d::SkeletalAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res);

private:
    nw::g3d::SkeletalAnimObj        mAnimObj;
    void*                           mpBuffer;
    const ModelG3d*                 mpModel;
    s32                             mIndex;
    nw::g3d::res::ResSkeletalAnim*  mpRes;
};
static_assert(sizeof(SkeletalAnimation) == 0x98);
