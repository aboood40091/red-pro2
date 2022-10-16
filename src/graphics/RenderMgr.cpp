#include <graphics/RenderMgr.h>

RenderMgr::RenderMgr(u32 view_num)
    : mModelEnvView(view_num)
    , mShadowMap(nullptr)
    , mReflectionMap(nullptr)
{
    mViewInfo.allocBuffer(view_num);
    for (Buffer<ViewInfo>::iterator itr = mViewInfo.begin(), itr_end = mViewInfo.end(); itr != itr_end; ++itr)
        itr->p_cull = nullptr;
}

RenderMgr::~RenderMgr()
{
    mViewInfo.freeBuffer();
}

void RenderMgr::update(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx)
{
    RIO_ASSERT(view_index < mViewInfo.size());
    mModelEnvView.setUniformData(view_index, view_mtx, proj_mtx);
}
