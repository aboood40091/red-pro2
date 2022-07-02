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

    bool isValid() const
    {
        return getVertexLocation()   != -1 ||
               getFragmentLocation() != -1 ||
               getGeometryLocation() != -1;
    }

    s32 getVertexLocation() const { return mVS; }
    s32 getFragmentLocation() const { return mFS; }
    s32 getGeometryLocation() const { return mGS; }

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
        : sead::INamable("Undefined")
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
        : sead::INamable("Undefined")
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
        : sead::INamable("Undefined")
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
        : sead::INamable("Undefined")
        , ShaderLocation()
    {
    }

    void search(const ShaderProgram& program);
};
static_assert(sizeof(AttributeLocation) == 0x10, "agl::AttributeLocation size mismatch");

}
