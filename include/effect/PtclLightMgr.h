#pragma once

#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <heap/seadDisposer.h>

namespace nw { namespace eft {

class EmitterController;

} }

class PtclLightMgr : public sead::IDisposer
{
public:
    PtclLightMgr();
    virtual ~PtclLightMgr() {}

    bool updateAmbientLight(bool update_emitter = true);
    void setEmitterColor(nw::eft::EmitterController* p_emitter_controller, u16 user_data);

private:
    sead::UnsafeArray<sead::Color4f, 6> mLightColor;
};
static_assert(sizeof(PtclLightMgr) == 0x70);
