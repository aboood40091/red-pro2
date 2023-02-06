#pragma once

#include <container/seadPtrArray.h>
#include <container/seadTList.h>
#include <heap/seadDisposer.h>

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
class PtclLightMgr;

class PtclMgr
{
    SEAD_SINGLETON_DISPOSER(PtclMgr)

public:
    PtclMgr();
    ~PtclMgr();

    void cleanUp();

    void draw(const agl::lyr::RenderInfo& render_info, u32 type, const sead::PtrArray<nw::eft::EmitterInstance>* p_emitters = nullptr);

private:
    static u32 userDataToType_(u16 user_data);

private:
    sead::ptcl::PtclSystem* mpPtclSystem;
    void* mpPtclParallelTbl;
    PtclLightMgr* mpLightMgr;
    void* mpUserShaderParamTbl;
    sead::TList<LevelEffect*> mEffects;
    sead::FixedPtrArray<nw::eft::EmitterInstance, 256> mpEmitter1;
    sead::FixedPtrArray<nw::eft::EmitterInstance, 256> mpEmitter2;
    s32 mPlayerId;
    bool mIsUseDisplayList;
    bool mIsDrawDisable;
    bool mIsUseParallel;
};
static_assert(sizeof(PtclMgr) == 0x84C, "PtclMgr size mismatch");
