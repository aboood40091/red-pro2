#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_SkeletalAnimObj.h>

class RenderObjEx;
class ResArchive;

class SkeletalAnimation : public Animation
{
public:
    SkeletalAnimation();
    void calc() override;

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);
    void bindRenderObj(RenderObjEx* p_render_obj, s32 index);
    void play(ResArchive* p_res_archive, const sead::SafeString& name);

    nw::g3d::SkeletalAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::SkeletalAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResSkeletalAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::SkeletalAnimObj mAnimObj;
    void* mpBuffer;
    RenderObjEx* mRenderObj;
    s32 mIndex;
    nw::g3d::res::ResSkeletalAnim* mpRes;
};
static_assert(sizeof(SkeletalAnimation) == 0x98, "SkeletalAnimation size mismatch");
