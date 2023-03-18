#pragma once

#include <framework/seadCalculateTask.h>
#include <framework/seadTaskMgr.h>
#include <layer/aglRenderInfo.h>
#include <math/seadBoundBox.h>

class AreaTask : public sead::CalculateTask
{
    SEAD_TASK_SINGLETON_DISPOSER(AreaTask)

public:
    AreaTask(const sead::TaskConstructArg& arg);
    virtual ~AreaTask();

    sead::BoundBox2f& getBound() { return mBound; }
    const sead::BoundBox2f& getBound() const { return mBound; }

    void setLoopType_Haxx();
    void drawLayer3D(const agl::lyr::RenderInfo& render_info);
    void debugDraw(const agl::lyr::RenderInfo& render_info);

private:
    u8                  _c9;
    bool                mIsPrepareDone;
    bool                mIsDrawMethodReady;
    u32                 mControllerWrapper[4][0x194 / sizeof(u32)]; // ControllerWrapper[4]
    sead::BoundBox2f    mBound;
    u32                 mLoopType;
    u32                 _730[(0xBE4 - 0x730) / sizeof(u32)];
};
static_assert(sizeof(AreaTask) == 0xBE4);
