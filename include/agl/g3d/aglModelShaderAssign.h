#pragma once

#include <agl/aglShaderLocation.h>

#include <nw/g3d/fnd/g3d_GfxObject.h>
#include <nw/g3d/res/g3d_ResMaterial.h>

namespace agl {

class ShaderProgram;

}

namespace agl { namespace g3d {

class ModelShaderAttribute
{
public:
    ModelShaderAttribute();
    ~ModelShaderAttribute();

    s32 getVertexBufferNum() const { return mVertexBufferNum; }
    nw::g3d::fnd::GfxBuffer* getVertexBuffer(s32 index) const { return mVertexBuffer[index]; }
    void setVertexBuffer(const nw::g3d::fnd::GfxBuffer* p_buffer, s32 index);

    void activateVertexBuffer() const;

private:
    u8 _0;
    u8 mVertexBufferNum;
    nw::g3d::fnd::GfxBuffer* mVertexBuffer[16]; // sead::UnsafeArray
    nw::g3d::fnd::GfxFetchShader mFetchShader;
};
static_assert(sizeof(ModelShaderAttribute) == 0x6C, "agl::g3d::ModelShaderAttribute size mismatch");

class ModelShaderAssign
{
public:
    ModelShaderAssign();
    ~ModelShaderAssign();

    ShaderProgram* getShaderProgram() const { return mpProgram; }

    ModelShaderAttribute& getAttribute() { return mAttribute; }
    const ModelShaderAttribute& getAttribute() const { return mAttribute; }

private:
    ShaderProgram* mpProgram;
    UniformBlockLocation mUniformBlockLocation;
    SamplerLocation mSamplerLocation[16];       // sead::SafeArray?
    nw::g3d::res::ResSampler* mpResSampler[16]; // sead::SafeArray?
    u8 mSamplerNum;
    ModelShaderAttribute mAttribute;
};
static_assert(sizeof(ModelShaderAssign) == 0x1C4, "agl::g3d::ModelShaderAssign size mismatch");

} }
