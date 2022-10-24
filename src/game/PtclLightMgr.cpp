#include <game/PtclLightMgr.h>

PtclLightMgr::PtclLightMgr()
    : sead::IDisposer()
    , mLightColor()
{
    for (s32 i = 0; i < 6; i++)
        mLightColor[i] = sead::Color4f::cWhite;
}
