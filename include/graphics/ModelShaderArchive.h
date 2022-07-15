#pragma once

#include <common/aglShaderProgramArchive.h>
#include <util/common/aglResShaderArchive.h>

struct ModelShaderArchive
{
    agl::ShaderProgramArchive* obj;
    const agl::ResBinaryShaderArchiveData* res_binary_archive;
    const agl::ResShaderArchiveData* res_archive;
    bool initialized;
};
static_assert(sizeof(ModelShaderArchive) == 0x10, "ModelShaderArchive size mismatch");
