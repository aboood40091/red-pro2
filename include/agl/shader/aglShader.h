#pragma once

#include <agl/aglShaderEnum.h>

namespace agl {

class ShaderCompileInfo;

class Shader
{
public:
    Shader();
    virtual ~Shader() { }

    virtual ShaderType getShaderType() const = 0;
    virtual u32 getRingItemSize() const { return 0; }

    void setBinary(const void* binary);

    void setCompileInfo(ShaderCompileInfo* compile_info)
    {
        mCompileInfo = compile_info;
    }

private:
    const void* mBinary;
    ShaderCompileInfo* mCompileInfo;
};
static_assert(sizeof(Shader) == 0xC, "agl::Shader size mismatch");

class VertexShader : public Shader
{
public:
    VertexShader()
        : Shader()
    {
    }

    virtual ShaderType getShaderType() const
    {
        return cShaderType_Vertex;
    }
};

class FragmentShader : public Shader
{
public:
    FragmentShader()
        : Shader()
    {
    }

    virtual ShaderType getShaderType() const
    {
        return cShaderType_Fragment;
    }
};

class GeometryShader : public Shader
{
public:
    GeometryShader()
        : Shader()
    {
    }

    virtual ShaderType getShaderType() const
    {
        return cShaderType_Geometry;
    }
};

}
