#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_TexPatternAnimObj.h>

class ModelNW;
class ModelResource;

class TexturePatternAnimation : public Animation
{
public:
    TexturePatternAnimation();

    bool init(const ModelNW* p_model, const ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap);

    bool isValid() const { return mpRes && mpModel; }

    void bindModel(const ModelNW* p_model, s32 index);
    void unbindModel();

private:
    void bindAnimObj_();

public:
    void play(const ModelResource* p_mdl_res, const sead::SafeString& name);

    bool forceBind(const sead::SafeString& name, const nw::g3d::res::ResTexture* p_texture);

    void calc() override;

    nw::g3d::TexPatternAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::TexPatternAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResTexPatternAnim* getResource() const { return mpRes; }

    const ModelNW* getModel() const { return mpModel; }
    s32 getIndex() const { return mIndex; }

private:
    static void updateInitArg_(nw::g3d::TexPatternAnimObj::InitArg* p_arg, const ModelResource* p_mdl_res);

private:
    nw::g3d::TexPatternAnimObj          mAnimObj;
    nw::g3d::res::ResTexPatternAnim*    mpRes;
    const ModelNW*                      mpModel;
    s32                                 mIndex;
};
static_assert(sizeof(TexturePatternAnimation) == 0x84);
