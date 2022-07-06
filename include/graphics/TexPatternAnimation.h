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
    void calc() override;

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);
    void bindRenderObj(RenderObjEx* p_render_obj, s32 index);
    void play(ResArchive* p_res_archive, const sead::SafeString& name);

    nw::g3d::TexPatternAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::TexPatternAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResTexPatternAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::TexPatternAnimObj mAnimObj;
    nw::g3d::res::ResTexPatternAnim* mpRes;
    RenderObjEx* mRenderObj;
    s32 mIndex;
};
static_assert(sizeof(TexPatternAnimation) == 0x84, "TexPatternAnimation size mismatch");
