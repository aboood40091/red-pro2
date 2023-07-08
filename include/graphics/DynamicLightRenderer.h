#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadHeap.h>

class DynamicLightRenderer
{
public:
    static void initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap);
};
