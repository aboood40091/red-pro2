#pragma once

#include <prim/seadSafeString.h>

namespace nw { namespace g3d { namespace res {

class ResFile;
class ResModel;

} } }

namespace agl {

class ShaderProgramArchive;

namespace g3d {

class ShaderUtilG3D
{
public:
    // Named these myself, not sure
    static void setMatBlockAndShaderParamOffs(nw::g3d::res::ResFile* res_file, const ShaderProgramArchive* shader_archive, const sead::SafeString& mat_block_name);

private:
    static void setMatBlockAndShaderParamOffs_(nw::g3d::res::ResModel* res_model, const ShaderProgramArchive* shader_archive, const sead::SafeString& mat_block_name);
};

}

}
