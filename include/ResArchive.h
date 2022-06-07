#pragma once

#include <ShaderArchive.h>

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>

#include <nw/g3d/res/g3d_ResFile.h>

class ResArchive : public sead::IDisposer
{
public:
    ResArchive();
    virtual ~ResArchive();

    void destroy();

    void load(
        sead::ArchiveRes* archive, const sead::SafeString& filename,
        const nw::g3d::res::ResFile* tex_res_file, sead::Heap* heap
    );

    agl::ShaderProgramArchive* getShaderProgramArchive(s32 idx_model) const;

private:
    nw::g3d::res::ResFile* mResFile;
    sead::Buffer<ShaderArchive> mShaderArchive;
    u32 _1c;
};
static_assert(sizeof(ResArchive) == 0x20, "ResArchive size mismatch");
