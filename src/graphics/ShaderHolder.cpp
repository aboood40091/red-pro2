#include <graphics/ShaderHolder.h>

ShaderHolder* ShaderHolder::sInstance = nullptr;

const agl::ShaderProgramArchive* ShaderHolder::getShaderArchive(const sead::SafeString& filename) const
{
    // Don't think I'll decompile this
    return nullptr;
}

const agl::ShaderProgramArchive* ShaderHolder::getNw4fShaderArchive() const
{
    return getShaderArchive("nw4f_shader");
}

const agl::ShaderProgram* ShaderHolder::getNw4fBasicShaderProgram() const
{
    return getNw4fShaderArchive()->searchShaderProgram("nw4f_basic_shader");
}
