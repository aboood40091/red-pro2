#include <agl/shader/aglShader.h>

namespace agl {

Shader::Shader()
    : mBinary(NULL)
    , mCompileInfo(NULL)
{
}

void Shader::setBinary(const void* binary)
{
    mBinary = binary;
}

}
