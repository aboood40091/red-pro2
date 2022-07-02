#pragma once

#include <container/seadBuffer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadNamable.h>

#include <agl/aglDisplayList.h>
#include <agl/aglShaderLocation.h>
#include <agl/util/agl/res/aglResShaderSymbol.h>
#include <agl/util/agl/res/aglResShaderVariation.h>
#include <agl/util/agl/shader/aglShader.h>

namespace agl {

class ShaderProgram
{
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    DisplayList& getDisplayList()
    {
        return mDisplayList;
    }

    const DisplayList& getDisplayList() const
    {
        return mDisplayList;
    }

    const sead::SafeString& getName() const
    {
        return mpSharedData->getName();
    }

    const ResShaderSymbolArray& getResShaderSymbolArray(ShaderSymbolType type) const
    {
        return mpSharedData->mResShaderSymbolArray[type];
    }

    void setResShaderSymbolArray(ShaderSymbolType type, const ResShaderSymbolArray& array)
    {
        mpSharedData->mResShaderSymbolArray[type] = array;
    }

    void setResShaderVariationDefaultArray(const ResShaderVariationArray& array)
    {
        mpSharedData->mResShaderVariationDefaultArray = array;
    }

    void initialize(const sead::SafeString& name, sead::Heap* heap);

    void createVariationBuffer(s32 num_variation, sead::Heap* heap);

    void createVariationMacro(s32 index, const sead::SafeString& name, const sead::SafeString& id, s32 num_value, sead::Heap* heap);
    void setVariationMacroValue(s32 macro_index, s32 value_index, const sead::SafeString& value);

    void createVariation(sead::Heap* heap);

    Shader* getShader(ShaderType type);
    const Shader* getShader(ShaderType type) const;

#ifdef cafe
    GX2VertexShader* getVertexShaderBinary()
    {
        validate_();
        return mVertexShader.getBinary();
    }

    const GX2VertexShader* getVertexShaderBinary() const
    {
        validate_();
        return mVertexShader.getBinary();
    }

    GX2PixelShader* getFragmentShaderBinary()
    {
        validate_();
        return mFragmentShader.getBinary();
    }

    const GX2PixelShader* getFragmentShaderBinary() const
    {
        validate_();
        return mFragmentShader.getBinary();
    }

    GX2GeometryShader* getGeometryShaderBinary()
    {
        validate_();
        return mGeometryShader.getBinary();
    }

    const GX2GeometryShader* getGeometryShaderBinary() const
    {
        validate_();
        return mGeometryShader.getBinary();
    }
#endif // cafe

    u32 setUpAllVariation(); // I don't know the actual return type
    void reserveSetUpAllVariation();

    s32 getVariationNum() const;
    s32 getVariationMacroNum() const;

    ShaderProgram* getVariation(s32 index);
    const ShaderProgram* getVariation(s32 index) const;

    void updateVariation(s32 index) // I don't know the actual name
    {
        ShaderProgram* program = getVariation(index);
        program->mFlag.set(8 | 2);
        program->validate_();
    }

    void updateAttributeLocation() const;
    void updateUniformLocation() const;
    void updateUniformBlockLocation() const;
    void updateSamplerLocation() const;

    void dump() const;

    void cleanUp();

    void destroyAttribute();
    void destroyUniform();
    void destroyUniformBlock();
    void destroySamplerLocation();

private:
    u32 validate_() const;
    u32 forceValidate_() const;

    void setUpForVariation_() const;

    void setShaderGX2_() const;

    class SharedData;
    class VariationBuffer;

private:
    class VariationBuffer
    {
        VariationBuffer();
        virtual ~VariationBuffer();

        void initialize(ShaderProgram* program, s32 num_variation, sead::Heap* heap);

        void createMacro(s32 index, const sead::SafeString& name, const sead::SafeString& id, s32 num_value, sead::Heap* heap);
        void setMacroValue(s32 macro_index, s32 value_index, const sead::SafeString& value);

        void create(sead::Heap* heap);

        s32 getMacroAndValueArray(s32 index, const char** macro_array, const char** value_array) const;

        class Macro
        {
            sead::SafeString mName;
            sead::SafeString mID;
            sead::Buffer<sead::SafeString> mValue;
            u16 _18;

            friend class VariationBuffer;
        };
        static_assert(sizeof(Macro) == 0x1C, "agl::ShaderProgram::VariationBuffer::Macro size mismatch");

        ShaderProgram* mpOriginal;
        sead::Buffer<ShaderProgram> mProgram;
        sead::Buffer<Macro> mMacro;

        friend class ShaderProgram;
        friend class SharedData;
    };
    static_assert(sizeof(VariationBuffer) == 0x18, "agl::ShaderProgram::VariationBuffer size mismatch");

    class SharedData : public sead::INamable
    {
        ShaderProgram* mpOriginal;
        VariationBuffer* mpVariationBuffer;
        u32 _10;
        ResShaderVariationArray mResShaderVariationDefaultArray; // Variation macro defaults
        ResShaderSymbolArray mResShaderSymbolArray[cShaderSymbolType_Num]; // sead::SafeArray<ResShaderSymbolArray, cShaderSymbolType_Num>
        u32 _28;

        friend class ShaderProgram;
    };
    static_assert(sizeof(SharedData) == 0x2C, "agl::ShaderProgram::SharedData size mismatch");

    VariationBuffer* getVariation_() { return mpSharedData->mpVariationBuffer; }
    const VariationBuffer* getVariation_() const { return mpSharedData->mpVariationBuffer; }

private:
    static const u32 cVariationMacroMax = 1024;
    static const u32 cVariationValueMax = 1024;

    mutable sead::BitFlag8 mFlag;
    u16 mVariationID;
    mutable DisplayList mDisplayList;
    mutable sead::Buffer<AttributeLocation> mAttributeLocation;
    mutable sead::Buffer<UniformLocation> mUniformLocation;
    mutable sead::Buffer<UniformBlockLocation> mUniformBlockLocation;
    mutable sead::Buffer<SamplerLocation> mSamplerLocation;
    VertexShader mVertexShader;
    FragmentShader mFragmentShader;
    GeometryShader mGeometryShader;
    SharedData* mpSharedData;
};
static_assert(sizeof(ShaderProgram) == 0x60, "agl::ShaderProgram size mismatch");

}
