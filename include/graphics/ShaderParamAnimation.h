#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_ShaderParamAnimObj.h>

class RenderObjEx;
class ResArchive;

class ShaderParamAnimation : public Animation
{
public:
    ShaderParamAnimation();
    void calc() override;

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);
    void playColorAnim(ResArchive* p_res_archive, const sead::SafeString& name);
    void playTexSrtAnim(ResArchive* p_res_archive, const sead::SafeString& name);

    nw::g3d::ShaderParamAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::ShaderParamAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResShaderParamAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::ShaderParamAnimObj mAnimObj;
    nw::g3d::res::ResShaderParamAnim* mpRes;
    RenderObjEx* mRenderObj;
    s32 mIndex;
    void* mpBuffer;
};
static_assert(sizeof(ShaderParamAnimation) == 0x88, "ShaderParamAnimation size mismatch");
