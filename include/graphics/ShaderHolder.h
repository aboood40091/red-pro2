#pragma once

#include <common/aglShaderProgramArchive.h>
#include <container/seadStrTreeMap.h>
#include <heap/seadDisposer.h>

class ShaderHolder
{
    SEAD_SINGLETON_DISPOSER(ShaderHolder)

public:
    ShaderHolder();

    void initialize(sead::Heap* heap);

private:
    agl::ShaderProgramArchive* createShaderArchive_(const sead::SafeString& filename, sead::Heap* heap) const;
    void pushBackShaderArchive_(const sead::SafeString& filename, agl::ShaderProgramArchive* p_archive, sead::Heap* heap);

    void createAndPushBackShaderArchive_(const sead::SafeString& filename, sead::Heap* heap);

public:
    const agl::ShaderProgramArchive* getShaderArchive(const sead::SafeString& filename) const;
    const agl::ShaderProgramArchive* getNw4fShaderArchive() const;
    const agl::ShaderProgram* getNw4fBasicShaderProgram() const;

private:
    sead::FixedStrTreeMap<64, agl::ShaderProgramArchive*, 32> mShaderArchiveTreeMap;
};
static_assert(sizeof(ShaderHolder) == 0xCA4);
