#pragma once

#include <prim/seadNamable.h>

namespace agl {

class ShaderLocation
{
public:
    ShaderLocation()
        : mVS(-1)
        , mFS(-1)
        , mGS(-1)
    {
    }

protected:
    s16 mVS;
    s16 mFS;
    s16 mGS;
};
static_assert(sizeof(ShaderLocation) == 6, "agl::ShaderLocation size mismatch");

class ShaderProgram;

class UniformLocation : public sead::INamable, public ShaderLocation
{
public:
    UniformLocation()
        : sead::INamable()
        , ShaderLocation()
    {
    }

    void search(const ShaderProgram& program);
};
static_assert(sizeof(UniformLocation) == 0x10, "agl::UniformLocation size mismatch");

class UniformBlockLocation : public sead::INamable, public ShaderLocation
{
public:
    UniformBlockLocation()
        : sead::INamable()
        , ShaderLocation()
    {
    }

    void search(const ShaderProgram& program);
};
static_assert(sizeof(UniformBlockLocation) == 0x10, "agl::UniformBlockLocation size mismatch");

class SamplerLocation : public sead::INamable, public ShaderLocation
{
public:
    SamplerLocation()
        : sead::INamable()
        , ShaderLocation()
    {
    }

    void search(const ShaderProgram& program);
};
static_assert(sizeof(SamplerLocation) == 0x10, "agl::SamplerLocation size mismatch");

class AttributeLocation : public sead::INamable, public ShaderLocation
{
public:
    AttributeLocation()
        : sead::INamable()
        , ShaderLocation()
    {
    }

    void search(const ShaderProgram& program);
};
static_assert(sizeof(AttributeLocation) == 0x10, "agl::AttributeLocation size mismatch");

}
