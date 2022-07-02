#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

class ShaderHolder
{
    SEAD_SINGLETON_DISPOSER(ShaderHolder)

public:
    ShaderHolder();

    agl::ShaderProgramArchive* getGlobalShaderArchive(const sead::SafeString& filename);
};
