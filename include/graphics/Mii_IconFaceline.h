#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadHeap.h>

namespace Mii {

class IconFaceline
{
public:
    static void initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap);
};

}
