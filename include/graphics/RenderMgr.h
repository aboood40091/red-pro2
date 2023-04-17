#pragma once

#include <graphics/ModelEnvView.h>

#include <common/aglTextureSampler.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadPtrArray.h>
#include <environment/aglEnvObjMgr.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <prim/seadNamable.h>

class CullViewFrustum;
class RenderObj;
class RenderObjLayerBase;

class RenderMgr : public sead::IDisposer, public sead::INamable
{
public:
    struct ViewInfo
    {
        RenderObjLayerBase* layer;
        sead::Matrix34f     view_mtx;
        sead::Matrix44f     proj_mtx;
        sead::Matrix44f*    _74;
        CullViewFrustum*    p_cull;
        void*               _7c; // pointer to struct of two f32 and one sead::Color4f for fog color
    };
    static_assert(sizeof(ViewInfo) == 0x80);

public:
    RenderMgr(const sead::SafeString& name);
    ~RenderMgr();

    void initialize(s32 layer_num_max, s32 render_obj_num_max, s32 opa_num_max, s32 xlu_num_max, sead::Heap* heap);
    void update(s32 view_index);

    void loadEnvRes(const void* p_file);

    ModelEnvView& getModelEnvView() { return mModelEnvView; }
    const ModelEnvView& getModelEnvView() const { return mModelEnvView; }

    agl::TextureSampler* getShadowMap() const { return mShadowMap; }
    agl::TextureSampler* getReflectionMap() const { return mReflectionMap; }

    void setShadowMap(agl::TextureSampler* p_sampler) { mShadowMap = p_sampler; }
    void setReflectionMap(agl::TextureSampler* p_sampler) { mReflectionMap = p_sampler; }

    ViewInfo& getViewInfo(s32 view_index) { return mViewInfo[view_index]; }
    const ViewInfo& getViewInfo(s32 view_index) const { return mViewInfo[view_index]; }

private:
    u8                                          _18;
    sead::PtrArray<RenderObj>                   mRenderObj;
    sead::Buffer< sead::PtrArray<RenderObj> >   mRenderObjOpa;
    sead::Buffer< sead::PtrArray<RenderObj> >   mRenderObjXlu;
    sead::PtrArray<RenderObj>                   mRenderObjShadow;
    agl::env::EnvObjMgr                         mEnvObjMgr;
    ModelEnvView                                mModelEnvView;
    void*                                       _4b4;
    bool                                        mDrawShadow;        // I think
    agl::TextureSampler*                        mShadowMap;
    agl::TextureSampler*                        mReflectionMap;
    sead::Buffer<ViewInfo>                      mViewInfo;
    sead::ListNode                              mNode;              // For sead::OffsetList in LayerMgr
};
static_assert(sizeof(RenderMgr) == 0x4D4);
