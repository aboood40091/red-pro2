#include <ShaderHolder.h>

ShaderHolder* ShaderHolder::sInstance = NULL;

agl::ShaderProgramArchive* ShaderHolder::getGlobalShaderArchive(const sead::SafeString& filename)
{
    // Don't think I'll decompile this
    return NULL;
}
