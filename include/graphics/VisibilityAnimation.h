#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_VisibilityAnimObj.h>

class ModelNW;
class ModelResource;

class VisibilityAnimation : public Animation
{
public:
    VisibilityAnimation();

    bool init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap);

    bool isValid() const { return mpRes && mpModel; }

    void bindModel(const ModelNW* p_model, s32 index);
    void unbindModel();

private:
    void bindAnimObj_();

public:
    void playBoneVisAnim(const ModelResource* p_mdl_res, const sead::SafeString& name);
    void playMatVisAnim(const ModelResource* p_mdl_res, const sead::SafeString& name);

    void calc() override;

    nw::g3d::VisibilityAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::VisibilityAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResVisibilityAnim* getResource() const { return mpRes; }

    const ModelNW* getModel() const { return mpModel; }
    s32 getIndex() const { return mIndex; }

private:
    static void updateInitArg_(nw::g3d::VisibilityAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res);

private:
    nw::g3d::VisibilityAnimObj          mAnimObj;
    nw::g3d::res::ResVisibilityAnim*    mpRes;
    const ModelNW*                      mpModel;
    s32                                 mIndex;
    void*                               mpBuffer;
};
static_assert(sizeof(VisibilityAnimation) == 0x84);
