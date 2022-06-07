#pragma once

#include <agl/aglShaderProgram.h>
#include <agl/res/aglResShaderArchive.h>
#include <agl/res/aglResShaderSource.h>
#include <agl/shader/aglShaderCompileInfo.h>

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>

namespace agl {

class ShaderProgramArchive : public sead::IDisposer
{
public:
    class ShaderSource : public sead::IDisposer
    {
    public:
        ShaderSource();

        virtual ~ShaderSource()
        {
            delete _24;
            delete mCode;
            _28.freeBuffer();
        }

        void initialize(ShaderProgramArchive* archive, s32 index, ResShaderSource res, bool is_used, sead::Heap* heap);

        const char* getName() const
        {
            return mRes.getName();
        }

    private:
        s32 mIndex;
        sead::BitFlag32 mFlags;
        ShaderProgramArchive* mpArchive;
        ResShaderSource mRes;
        sead::HeapSafeString* mCode;
        sead::BufferedSafeString* _24; // ^^
        sead::Buffer<bool> _28;
    };
    static_assert(sizeof(ShaderSource) == 0x30, "agl::ShaderProgramArchive::ShaderSource size mismatch");

    class ShaderProgramEx;

    class ShaderCompileInfoEx : ShaderCompileInfo
    {
    public:
        ShaderCompileInfoEx()
            : ShaderCompileInfo()
        {
        }

        virtual ~ShaderCompileInfoEx()
        {
        }

    private:
        ShaderSource* mSource;

        friend class ShaderProgramEx;
    };
    static_assert(sizeof(ShaderCompileInfoEx) == 0x58, "agl::ShaderProgramArchive::ShaderCompileInfoEx size mismatch");

    class ShaderProgramEx
    {
    public:
        ShaderProgramEx();

        virtual ~ShaderProgramEx()
        {
        }

        void initialize(ShaderProgramArchive* archive, s32 index, ResShaderProgram res, sead::Heap* heap);

        void updateAnalyze();

    private:
        s32 mIndex;
        ShaderProgramArchive* mpArchive;
        ShaderCompileInfoEx mCompileInfoEx[cShaderType_Num];
        sead::Buffer<u32> _110; // No idea buffer of what
        u32 _118;
        sead::BitFlag8 _11c;
    };
    static_assert(sizeof(ShaderProgramEx) == 0x124, "agl::ShaderProgramArchive::ShaderProgramEx size mismatch");

public:
    ShaderProgramArchive();
    virtual ~ShaderProgramArchive();

    void destroy();

    sead::SafeString getName() const
    {
        if (mResBinary.isValid())
            return mResBinary.getName();
        else
            return mResText.getName();
    }

    s32 getShaderProgramNum() const
    {
        return mProgram.size();
    }

    ShaderProgram& getShaderProgram(s32 idx)
    {
        return mProgram[idx];
    }

    const ShaderProgram& getShaderProgram(s32 idx) const
    {
        return mProgram[idx];
    }

    void createWithOption(ResBinaryShaderArchive res_binary_archive, ResShaderArchive res_archive, u32 flag, sead::Heap* heap);
    bool setUp();

    void updateCompileInfo();

private:
    void destroyResFile_();
    void setResShaderArchive_(ResShaderArchive res_archive, sead::Heap* heap);
    bool setUp_(bool);

private:
    ResBinaryShaderArchive mResBinary;
    ResShaderArchive mResText;
    sead::Buffer<ShaderProgram> mProgram;
    u32 _20;
    u32 _24;
    u16 _28;
    sead::BitFlag16 _2a;
    sead::Buffer<ShaderProgramEx> mProgramEx;
    sead::Buffer<ShaderSource> mSource;
    sead::Buffer<const char*> mSourceCode;
    sead::Buffer<const char*> mSourceName;

    friend class ShaderSource;
    friend class ShaderProgramEx;
};
static_assert(sizeof(ShaderProgramArchive) == 0x4C, "agl::ShaderProgramArchive size mismatch");

}
