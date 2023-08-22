#include <effect/PtclEmitterColorMgr.h>

PtclEmitterColorMgr::PtclEmitterColorMgr()
    : sead::IDisposer()
{
    for (s32 i = 0; i < 6; i++)
        mLightColor[i] = sead::Color4f::cWhite;
}
