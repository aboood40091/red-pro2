#pragma once

#include <graphics/ModelEnvView.h>

#include <common/aglTextureSampler.h>
//#include <container/Buffer.h>
//#include <container/rio_LinkList.h>
//#include <container/PtrArray.h>
#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <gfx/lyr/rio_Drawable.h>
#include <math/rio_Matrix.h>

#include <vector>

class CullViewFrustum;
class RenderObj;
class RenderObjLayer;

class RenderMgr
{
public:
    struct ViewInfo
    {
        RenderObjLayer*         p_layer;
        rio::Matrix34f          view_mtx;
        rio::Matrix44f          proj_mtx;
      //const rio::Matrix44f*   _74;
        const CullViewFrustum*  p_cull = nullptr;
      //void*                   _7c; // pointer to struct of two f32 and one rio::Color4f for fog color
    };
  //static_assert(sizeof(ViewInfo) == 0x80);

    class CallbackBase
    {
    public:
        virtual void preDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) = 0;
        virtual void preDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) = 0;
        virtual void postDrawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info) = 0;
        virtual void postDrawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info) = 0;
    };

public:
    RenderMgr();
    ~RenderMgr();

    void clear();

    void calc();
    void calcView(s32 view_index, const rio::Camera& camera, const rio::Projection& projection, const CullViewFrustum* p_cull);
    void calcGPU(s32 view_index);
    void drawOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info);
    void drawXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info);
  //void drawShadowOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info);
  //void drawReflectionOpa(s32 view_index, const rio::lyr::DrawInfo& draw_info);
  //void drawReflectionXlu(s32 view_index, const rio::lyr::DrawInfo& draw_info);

    void pushBackRenderObj(RenderObj* obj, bool draw_opa, bool draw_xlu);
    void pushBackRenderObj(RenderObj* obj, bool draw_opa, bool draw_xlu, const rio::Vector3f& order_pos);

    s32 createView(RenderObjLayer* p_layer);

    ModelEnvView& getModelEnvView() { return mModelEnvView; }
    const ModelEnvView& getModelEnvView() const { return mModelEnvView; }

    CallbackBase* getDrawCallback() const { return mpCallback; }
    void setDrawCallback(CallbackBase* p_callback) { mpCallback = p_callback; }

    agl::TextureSampler* getShadowMap() const { return mShadowMap; }
    agl::TextureSampler* getReflectionMap() const { return mReflectionMap; }

    void setShadowMap(agl::TextureSampler* p_sampler) { mShadowMap = p_sampler; }
    void setReflectionMap(agl::TextureSampler* p_sampler) { mReflectionMap = p_sampler; }

    ViewInfo& getViewInfo(s32 view_index)
    {
        RIO_ASSERT(u32(view_index) < mViewInfo.size());
        return mViewInfo[view_index];
    }

    const ViewInfo& getViewInfo(s32 view_index) const
    {
        RIO_ASSERT(u32(view_index) < mViewInfo.size());
        return mViewInfo[view_index];
    }

private:
  //bool                    _18;
    std::vector<RenderObj*> mRenderObj;
    std::vector<RenderObj*> mRenderObjOpa;
    std::vector<RenderObj*> mRenderObjXlu;
  //std::vector<RenderObj*> mRenderObjShadow;
  //agl::env::EnvObjMgr     mEnvObjMgr;
    ModelEnvView            mModelEnvView;
    CallbackBase*           mpCallback;
  //bool                    mDrawShadow;        // I think
    agl::TextureSampler*    mShadowMap;
    agl::TextureSampler*    mReflectionMap;
    std::vector<ViewInfo>   mViewInfo;
  //rio::LinkListNode       mListNode;          // For OffsetList in LayerMgr
};
//static_assert(sizeof(RenderMgr) == 0x4D4);
