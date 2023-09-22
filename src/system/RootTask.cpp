#include <system/RootTask.h>

RootTask::RootTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "RootTask")
    , mIsLastFrameValid(false)
    , mIsLastFrameDRCValid(false)
{
}
