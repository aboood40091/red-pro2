#pragma once

#include <prim/seadSafeString.h>

namespace agl { namespace lght {

class LightMapMgr /* : public utl::IParameterIO */
{
public:
    LightMapMgr();
    /* virtual */ ~LightMapMgr();

    s32 searchIndex(const sead::SafeString& name) const;

private:
    u32 _0[0x2D6C / sizeof(u32)];
};
static_assert(sizeof(LightMapMgr) == 0x2D6C, "agl::lght::LightMapMgr size mismatch");

} }
