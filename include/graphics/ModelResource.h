#pragma once

#include <graphics/ModelShaderArchive.h>

#include <container/Buffer.h>
#include <resource/SharcArchiveRes.h>

#include <nw/g3d/res/g3d_ResFile.h>

class ModelResource
{
public:
    ModelResource();
    ~ModelResource();

    void destroy();

    void load(
        SharcArchiveRes* archive, const char* filename,
        const nw::g3d::res::ResFile* tex_res_file = nullptr
    );

    agl::ShaderProgramArchive* getModelShaderProgramArchive(s32 idx_model) const;

    nw::g3d::res::ResFile* getResFile() const
    {
        return mResFile;
    }

private:
    nw::g3d::res::ResFile* mResFile;
    Buffer<ModelShaderArchive> mModelShaderArchive;
    u32 _1c;
};
//static_assert(sizeof(ModelResource) == 0x20, "ModelResource size mismatch");
