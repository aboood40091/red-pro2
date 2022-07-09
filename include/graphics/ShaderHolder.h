#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

class ShaderHolder
{
    SEAD_SINGLETON_DISPOSER(ShaderHolder)

public:
    ShaderHolder();

    const agl::ShaderProgramArchive* getShaderArchive(const sead::SafeString& filename) const;
    const agl::ShaderProgramArchive* getNw4fShaderArchive() const;
    const agl::ShaderProgram* getNw4fBasicShaderProgram() const;
};
