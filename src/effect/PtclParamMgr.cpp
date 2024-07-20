#include <effect/PtclParam.h>
#include <effect/PtclParamMgr.h>

#include <filedevice/seadFileDeviceMgr.h>

PtclParamMgr::PtclParamMgr()
    : mpParam(nullptr)
    , mParamNum(0)
{
}

void PtclParamMgr::initialize(sead::Heap* heap)
{
    sead::FileDevice::LoadArg arg;
    arg.path = "effect/Eset.param";
    arg.heap = heap;
    mpParam = (const PtclParam*)sead::FileDeviceMgr::instance()->getDefaultFileDevice()->load(arg);
    mParamNum = arg.read_size / sizeof(PtclParam);
}

const PtclParam* PtclParamMgr::getParam(u32 index) const
{
    return &(mpParam[index]);
}
