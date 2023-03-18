#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_ShaderParamAnimObj.h>

class ModelNW;
class ModelResource;

class ShaderParamAnimation : public Animation
{
public:
    ShaderParamAnimation();

    bool init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap);

    bool isValid() const { return mpRes && mpModel; }

    void bindModel(const ModelNW* p_model, s32 index);
    void unbindModel();

private:
    void bindAnimObj_();

public:
    void playColorAnim(const ModelResource* p_mdl_res, const sead::SafeString& name);
    void playTexSrtAnim(const ModelResource* p_mdl_res, const sead::SafeString& name);

    void calc() override;

    nw::g3d::ShaderParamAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::ShaderParamAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResShaderParamAnim* getResource() const { return mpRes; }

    const ModelNW* getModel() const { return mpModel; }
    s32 getIndex() const { return mIndex; }

private:
    static void updateInitArg_(nw::g3d::ShaderParamAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res);

private:
    nw::g3d::ShaderParamAnimObj         mAnimObj;
    nw::g3d::res::ResShaderParamAnim*   mpRes;
    const ModelNW*                      mpModel;
    s32                                 mIndex;
    void*                               mpBuffer;
};
static_assert(sizeof(ShaderParamAnimation) == 0x88);
