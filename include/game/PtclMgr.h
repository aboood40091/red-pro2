#pragma once

#include <basis/seadTypes.h>

namespace sead { namespace ptcl {

class PtclSystem;

} }

namespace nw { namespace eft {

struct EmitterInstance;

} }

namespace agl { namespace lyr {

class RenderInfo;

} }

class LevelEffect;

class PtclMgr
{
    SEAD_SINGLETON_DISPOSER(PtclMgr)

public:
    PtclMgr();

    void draw(const agl::lyr::RenderInfo& render_info, u32 group_id, sead::PtrArray<nw::eft::EmitterInstance>* p_emitters = NULL);

private:
    sead::ptcl::PtclSystem* mpPtclSystem;
    void* mPtclParallelTbl;
    void* mColors;
    void* mpUserShaderParamTbl;
    sead::TList<LevelEffect*> mEffects;
    u32 mpEmitter1[0x40C / sizeof(u32)]; // sead::FixedPtrArray<nw::eft::EmitterInstance, 256>
    u32 mpEmitter2[0x40C / sizeof(u32)]; // ^^^
    s32 mPlayerId;
    bool mIsUseDisplayList;
    u8 _849;
    bool mIsUseParallel;
};
static_assert(sizeof(PtclMgr) == 0x84C, "PtclMgr size mismatch");
