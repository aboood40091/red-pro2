#pragma once

#include <heap/seadDisposer.h>
#include <resource/seadSharcArchiveRes.h>
#include <utility/aglParameterIO.h>

class GfxParameter
{
    SEAD_SINGLETON_DISPOSER(GfxParameter)

public:
    GfxParameter();
    virtual ~GfxParameter();

    void setDelegateForParameter(agl::utl::IParameterIO* p_param);

private:
    sead::SharcArchiveRes*  mpPackArc;
    u32                     mDelegateData[8]; // Same idea as agl::lyr::DrawMethod
    u32                     _34;
};
static_assert(sizeof(GfxParameter) == 0x3C);
