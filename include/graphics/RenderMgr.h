#pragma once

#include <graphics/ModelEnvView.h>

#include <common/aglTextureSampler.h>
#include <container/Buffer.h>
#include <container/rio_LinkList.h>
#include <container/PtrArray.h>
#include <math/rio_Matrix.h>

class CullViewFrustum;
class RenderObj;
class RenderObjBaseLayer;

class RenderMgr
{
public:
    struct ViewInfo
    {
      //RenderObjBaseLayer* layer;
      //rio::Matrix34f view_mtx;
      //rio::Matrix44f proj_mtx;
      //rio::Matrix44f* _74;
        CullViewFrustum* p_cull;
      //void* _7c; // pointer to struct of two f32 and one rio::Color4f for fog color
    };
  //static_assert(sizeof(ViewInfo) == 0x80, "RenderMgr::ViewInfo size mismatch");

public:
    RenderMgr(u32 view_num = 1);
    ~RenderMgr();

    void update(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx);

    ModelEnvView& getModelEnvView() { return mModelEnvView; }
    const ModelEnvView& getModelEnvView() const { return mModelEnvView; }

    agl::TextureSampler* getShadowMap() const { return mShadowMap; }
    agl::TextureSampler* getReflectionMap() const { return mReflectionMap; }

    void setShadowMap(agl::TextureSampler* p_sampler) { mShadowMap = p_sampler; }
    void setReflectionMap(agl::TextureSampler* p_sampler) { mReflectionMap = p_sampler; }

    ViewInfo& getViewInfo(s32 view_index) { return mViewInfo[view_index]; }
    const ViewInfo& getViewInfo(s32 view_index) const { return mViewInfo[view_index]; }

private:
  //u8 _18;
  //PtrArray<RenderObj> mRenderObj;
  //Buffer< PtrArray<RenderObj> > mRenderObjOpa;
  //Buffer< PtrArray<RenderObj> > mRenderObjXlu;
  //PtrArray<RenderObj> mRenderObjShadow;
  //u32 mEnvObjMgr[0x464 / sizeof(u32)]; // agl::env::EnvObjMgr
    ModelEnvView mModelEnvView;
  //void* _4b4;
  //bool mDrawShadow; // I think
    agl::TextureSampler* mShadowMap;
    agl::TextureSampler* mReflectionMap;
    Buffer<ViewInfo> mViewInfo;
  //rio::LinkListNode mNode; // For OffsetList in LayerMgr
};
//static_assert(sizeof(RenderMgr) == 0x4D4, "RenderMgr size mismatch");
