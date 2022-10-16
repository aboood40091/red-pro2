#pragma once

#include <common/aglShaderProgramArchive.h>

class ShaderHolder
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ShaderHolder* instance() { return sInstance; }

private:
    static ShaderHolder* sInstance;

    ShaderHolder();
    ~ShaderHolder();

    ShaderHolder(const ShaderHolder&);
    ShaderHolder& operator=(const ShaderHolder&);

public:
    const agl::ShaderProgramArchive* getShaderArchive(const char* filename) const;
    const agl::ShaderProgramArchive* getNw4fShaderArchive() const;
    const agl::ShaderProgram* getNw4fBasicShaderProgram() const;
};
