#include <detail/aglGX2.h>

#ifdef cafe
#include <cafe.h>
#endif // cafe

namespace agl { namespace driver {

GX2Resource* GX2Resource::sInstance = NULL;

void GX2Resource::setShaderMode(ShaderMode mode) const
{
    setShaderMode(mode, *mpOptimizeInfo);
}

void GX2Resource::setShaderMode(ShaderMode mode, const ShaderOptimizeInfo& info) const
{
#ifdef cafe
    switch (mode)
    {
    case cShaderMode_UniformRegister:
        GX2SetShaderModeEx(
            GX2_SHADER_MODE_UNIFORM_REGISTER,
            info.getVertexShaderGprs(),
            info.getVertexShaderStackSize(),
            0,
            0,
            info.getFragmentShaderGprs(),
            info.getFragmentShaderStackSize()
        );
        break;
    case cShaderMode_UniformBlock:
        GX2SetShaderModeEx(
            GX2_SHADER_MODE_UNIFORM_BLOCK,
            info.getVertexShaderGprs(),
            info.getVertexShaderStackSize(),
            0,
            0,
            info.getFragmentShaderGprs(),
            info.getFragmentShaderStackSize()
        );
        GX2Invalidate(GX2_INVALIDATE_UNIFORM_BLOCK, NULL, 0xFFFFFFFF);
        break;
    case cShaderMode_GeometryShader:
        GX2SetShaderModeEx(
            GX2_SHADER_MODE_UNIFORM_BLOCK,
            info.getVertexShaderWithGSGprs(),
            info.getVertexShaderWithGSStackSize(),
            info.getGeometryShaderGprs(),
            info.getGeometryShaderStackSize(),
            info.getFragmentShaderWithGSGprs(),
            info.getFragmentShaderWithGSStackSize()
        );
        GX2Invalidate(GX2_INVALIDATE_UNIFORM_BLOCK, NULL, 0xFFFFFFFF);
        break;
    }
#endif // cafe
}

void GX2Resource::setGeometryShaderRingBuffer() const
{
#ifdef cafe
    GX2SetGeometryShaderInputRingBuffer(mGeometryShaderInputRingBuffer, mGeometryShaderInputRingBufferSize);
    GX2SetGeometryShaderOutputRingBuffer(mGeometryShaderOutputRingBuffer, mGeometryShaderOutputRingBufferSize);
#endif // cafe
}

} }
