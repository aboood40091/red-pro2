#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_VisibilityAnimObj.h>

class RenderObjEx;
class ResArchive;

class VisibilityAnimation : public Animation
{
public:
    VisibilityAnimation();

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);

    bool isValid() const { return mpRes && mpRenderObj; }

    void bindRenderObj(RenderObjEx* p_render_obj, s32 index);
    void unbindRenderObj();

private:
    void bindAnimObj_();

public:
    void play(ResArchive* p_res_archive, const sead::SafeString& name);

    void calc() override;

    nw::g3d::VisibilityAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::VisibilityAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResVisibilityAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mpRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::VisibilityAnimObj mAnimObj;
    nw::g3d::res::ResVisibilityAnim* mpRes;
    RenderObjEx* mpRenderObj;
    s32 mIndex;
    void* mpBuffer;
};
static_assert(sizeof(VisibilityAnimation) == 0x84, "VisibilityAnimation size mismatch");
