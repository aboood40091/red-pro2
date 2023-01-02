#include <effect/PtclLightMgr.h>

PtclLightMgr::PtclLightMgr()
    : sead::IDisposer()
{
    for (s32 i = 0; i < 6; i++)
        mLightColor[i] = sead::Color4f::cWhite;
}
