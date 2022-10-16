#include <graphics/ShaderHolder.h>

ShaderHolder* ShaderHolder::sInstance = NULL;

const agl::ShaderProgramArchive* ShaderHolder::getShaderArchive(const char* filename) const
{
    // Don't think I'll decompile this
    RIO_ASSERT(false);
    return NULL;
}

const agl::ShaderProgramArchive* ShaderHolder::getNw4fShaderArchive() const
{
    return getShaderArchive("nw4f_shader");
}

const agl::ShaderProgram* ShaderHolder::getNw4fBasicShaderProgram() const
{
    return getNw4fShaderArchive()->searchShaderProgram("nw4f_basic_shader");
}
