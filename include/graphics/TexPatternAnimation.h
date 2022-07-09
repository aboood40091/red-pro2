#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_TexPatternAnimObj.h>

class RenderObjEx;
class ResArchive;

class TexPatternAnimation : public Animation
{
public:
    TexPatternAnimation();

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);

    bool isValid() const { return mpRes && mpRenderObj; }

    void bindRenderObj(RenderObjEx* p_render_obj, s32 index);
    void unbindRenderObj();

private:
    void bindAnimObj_();

public:
    void play(ResArchive* p_res_archive, const sead::SafeString& name);

    void calc() override;

    nw::g3d::TexPatternAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::TexPatternAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResTexPatternAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mpRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::TexPatternAnimObj mAnimObj;
    nw::g3d::res::ResTexPatternAnim* mpRes;
    RenderObjEx* mpRenderObj;
    s32 mIndex;
};
static_assert(sizeof(TexPatternAnimation) == 0x84, "TexPatternAnimation size mismatch");
