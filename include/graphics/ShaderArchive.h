#pragma once

#include <agl/aglShaderProgramArchive.h>
#include <agl/util/agl/res/aglResShaderArchive.h>

struct ShaderArchive
{
    agl::ShaderProgramArchive* obj;
    const agl::ResBinaryShaderArchiveData* res_binary_archive;
    const agl::ResShaderArchiveData* res_archive;
    bool initialized;
};
static_assert(sizeof(ShaderArchive) == 0x10, "ShaderArchive size mismatch");
