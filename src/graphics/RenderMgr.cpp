#include <graphics/RenderMgr.h>

void RenderMgr::loadEnvRes(const void* p_file)
{
    mEnvObjMgr.applyResource(agl::utl::ResParameterArchive(p_file));
}
