#pragma once

#include <graphics/ModelShaderArchive.h>

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>

#include <nw/g3d/res/g3d_ResFile.h>

class ModelResource : public sead::IDisposer
{
public:
    ModelResource();
    virtual ~ModelResource();

    void destroy();

    void load(
        const sead::SafeString& filename, sead::Heap* heap
    );

    void load(
        sead::ArchiveRes* archive, const sead::SafeString& filename,
        const nw::g3d::res::ResFile* tex_res_file, sead::Heap* heap
    );

    agl::ShaderProgramArchive* getModelShaderProgramArchive(s32 idx_model) const;

    nw::g3d::res::ResFile* getResFile() const
    {
        return mResFile;
    }

private:
    nw::g3d::res::ResFile*              mResFile;
    sead::Buffer<ModelShaderArchive>    mModelShaderArchive;
    u32                                 _1c;
};
static_assert(sizeof(ModelResource) == 0x20);
