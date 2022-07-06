#pragma once

#include <graphics/Animation.h>

#include <container/seadPtrArray.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

#include <nw/g3d/g3d_ShapeAnimObj.h>

class RenderObjEx;
class ResArchive;

class ShapeAnimation : public Animation
{
public:
    ShapeAnimation();
    void calc() override;

    bool init(RenderObjEx* p_render_obj, ResArchive* p_res_archive, sead::PtrArray<ResArchive>* p_res_archive_array, sead::Heap* heap);
    void play(ResArchive* p_res_archive, const sead::SafeString& name);

    nw::g3d::ShapeAnimObj& getAnimObj() { return mAnimObj; }
    const nw::g3d::ShapeAnimObj& getAnimObj() const { return mAnimObj; }

    nw::g3d::res::ResShapeAnim* getResource() const { return mpRes; }

    RenderObjEx* getRenderObj() const { return mRenderObj; }
    s32 getIndex() const { return mIndex; }

private:
    nw::g3d::ShapeAnimObj mAnimObj;
    nw::g3d::res::ResShapeAnim* mpRes;
    RenderObjEx* mRenderObj;
    s32 mIndex;
    void* mpBuffer;
};
static_assert(sizeof(ShapeAnimation) == 0x88, "ShapeAnimation size mismatch");