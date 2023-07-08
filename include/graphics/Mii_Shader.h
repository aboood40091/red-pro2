#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadHeap.h>

namespace Mii {

class Shader
{
public:
    static void initialize(agl::ShaderProgramArchive* p_archive, sead::Heap* heap);
};

}
