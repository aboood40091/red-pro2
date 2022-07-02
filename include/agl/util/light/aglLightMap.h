#pragma once

#include <prim/seadSafeString.h>

namespace agl { namespace lght {

class LightMapMgr;

class LightMap /* : public agl::env::EnvObjSet */
{
public:
    LightMap();
    /* virtual */ ~LightMap();

private:
    u32 _0[(0xB4 - 0x0) / sizeof(u32)];
    sead::FixedSafeString<32> mName; // Member of agl::utl::Parameter< sead::FixedSafeString<32> >
    u32 _e0[(0x8AC - 0xE0) / sizeof(u32)];

    friend class LightMapMgr;
};
static_assert(sizeof(LightMap) == 0x8AC, "agl::lght::LightMap size mismatch");

} }
