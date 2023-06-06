#pragma once

#include <graphics/Animation.h>

#include <container/PtrArray.h>

#include <nw/g3d/g3d_TexPatternAnimObj.h>

class ModelNW;
class ModelResource;

class TexturePatternAnimation : public Animation
{
public:
    TexturePatternAnimation();
    ~TexturePatternAnimation();

    bool init(const ModelNW* p_model, const ModelResource* p_mdl_res, const PtrArray<ModelResource>* p_anim_mdl_res_array);

    bool isValid() const { return mpRes && mpModel; }

    void bindModel(const ModelNW* p_model, s32 index);
    void unbindModel();

private:
    void bindAnimObj_();

public:
    void play(const ModelResource* p_mdl_res, const char* name);

    bool forceBind(const char* name, const nw::g3d::res::ResTexture* p_texture);

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

    // Custom
    void*   mpBuffer;
};
static_assert(sizeof(TexturePatternAnimation) == 0x84 + 4);
