#pragma once

#include <common/aglShaderLocation.h>
#include <heap/seadHeap.h>

#include <nw/g3d/fnd/g3d_GfxObject.h>
#include <nw/g3d/res/g3d_ResMaterial.h>
#include <nw/g3d/res/g3d_ResShape.h>
#include <nw/g3d/g3d_MaterialObj.h>

namespace agl {

class ShaderProgram;

}

namespace agl { namespace g3d {

class ModelShaderAttribute
{
    class Attribute
    {
        Attribute()
            : mIndex(0)
            , mName("Undefined")
            , mLocation(0)
        {
        }

        s32 mIndex;
        sead::SafeString mName;
        s16 mLocation;

        friend class ModelShaderAttribute;
    };
    static_assert(sizeof(Attribute) == 0x10, "agl::g3d::ModelShaderAttribute::Attribute size mismatch");

public:
    ModelShaderAttribute();
    ~ModelShaderAttribute();

    void create(sead::Heap* heap);
    void clear();

    void bind(const nw::g3d::res::ResMaterial* p_res_mat, const nw::g3d::res::ResShape* p_res_shp, const ShaderProgram* p_program, bool use_res_assign, bool use_shader_symbol_id);

    s32 getVertexBufferNum() const { return mVertexBufferNum; }

    void activateVertexBuffer() const;

    const nw::g3d::fnd::GfxBuffer* getVertexBuffer(s32 index) const { return mpVertexBuffer[index]; }
    void setVertexBuffer(const nw::g3d::fnd::GfxBuffer* p_buffer, s32 index);

private:
    u8 _0;
    u8 mVertexBufferNum;
    const nw::g3d::fnd::GfxBuffer* mpVertexBuffer[16]; // sead::UnsafeArray
    nw::g3d::fnd::GfxFetchShader mFetchShader;
};
static_assert(sizeof(ModelShaderAttribute) == 0x6C, "agl::g3d::ModelShaderAttribute size mismatch");

class ModelShaderAssign
{
public:
    ModelShaderAssign();
    ~ModelShaderAssign();

    const ShaderProgram* getShaderProgram() const { return mpProgram; }

    SamplerLocation& getSamplerLocation(s32 index) { return mSamplerLocation[index]; }
    const SamplerLocation& getSamplerLocation(s32 index) const { return mSamplerLocation[index]; }

    s32 getSamplerNum() const { return mSamplerNum; }
    const nw::g3d::res::ResSampler* getResSampler(s32 index) const { return mpResSampler[index]; }

    ModelShaderAttribute& getAttribute() { return mAttribute; }
    const ModelShaderAttribute& getAttribute() const { return mAttribute; }

    void create(sead::Heap* heap);

    void bind(const nw::g3d::res::ResMaterial* p_res_mat, const ShaderProgram* p_program, bool use_res_assign, bool use_shader_symbol_id);
    void bindShaderResAssign(const nw::g3d::res::ResMaterial* p_res_mat, const nw::g3d::res::ResShape* p_res_shp, const ShaderProgram* p_program, const char* = "Mat");
    void bindShader(const nw::g3d::res::ResMaterial* p_res_mat, const nw::g3d::res::ResShape* p_res_shp, const ShaderProgram* p_program, const char* = "Mat");

    void pushBackSampler(const nw::g3d::res::ResSampler* p_res_sampler, const SamplerLocation& location);

    void activateMaterialUniformBlock(const nw::g3d::MaterialObj* p_material) const;
    void activateTextureSampler(const nw::g3d::MaterialObj* p_material) const;

private:
    void clear_();
    void updateLocation_(const char* uniform_block_name);

private:
    const ShaderProgram* mpProgram;
    UniformBlockLocation mUniformBlockLocation;
    SamplerLocation mSamplerLocation[16];       // sead::UnsafeArray
    const nw::g3d::res::ResSampler* mpResSampler[16]; // sead::UnsafeArray
    u8 mSamplerNum;
    ModelShaderAttribute mAttribute;
};
static_assert(sizeof(ModelShaderAssign) == 0x1C4, "agl::g3d::ModelShaderAssign size mismatch");

} }
