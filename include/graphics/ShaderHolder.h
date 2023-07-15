#pragma once

#include <common/aglShaderProgramArchive.h>
#include <resource/SharcArchiveRes.h>

#include <string>
#include <unordered_map>

class ShaderHolder
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static ShaderHolder* instance() { return sInstance; }

private:
    static ShaderHolder* sInstance;

    ShaderHolder();
    ~ShaderHolder();

    ShaderHolder(const ShaderHolder&);
    ShaderHolder& operator=(const ShaderHolder&);

public:
    void initialize(const std::string& arc_path);

private:
    agl::ShaderProgramArchive* createShaderArchive_(const std::string& filename) const;
    void pushBackShaderArchive_(const std::string& filename, agl::ShaderProgramArchive* p_archive);

    void createAndPushBackShaderArchive_(const std::string& filename);

public:
    const agl::ShaderProgramArchive* getShaderArchive(const std::string& filename) const;
    const agl::ShaderProgramArchive* getNw4fShaderArchive() const;
    const agl::ShaderProgram* getNw4fBasicShaderProgram() const;

private:
    u8* mpArchive;
    SharcArchiveRes mArchiveRes;
    std::unordered_map<std::string, agl::ShaderProgramArchive*> mShaderArchiveMap;
};
