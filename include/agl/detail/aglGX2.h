#pragma once

#include <common/aglShaderEnum.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include <util/common/aglShaderOptimizeInfo.h>

namespace agl { namespace driver {

class GX2Resource
{
    SEAD_SINGLETON_DISPOSER(GX2Resource)

public:
    GX2Resource();
    virtual ~GX2Resource();

    void setShaderMode(ShaderMode mode) const;
    void setShaderMode(ShaderMode mode, const ShaderOptimizeInfo& info) const;

    void setGeometryShaderRingBuffer() const;

private:
    ShaderOptimizeInfo* mpOptimizeInfo;
    ShaderOptimizeInfo mDefaultOptimizeInfo;
    size_t mGeometryShaderInputRingItemSize;
    size_t mGeometryShaderOutputRingItemSize;
    u8* mGeometryShaderInputRingBuffer;
    size_t mGeometryShaderInputRingBufferSize;
    u8* mGeometryShaderOutputRingBuffer;
    size_t mGeometryShaderOutputRingBufferSize;
    sead::CriticalSection mCriticalSection;
    u8 _78;
    u8 _79;
};
static_assert(sizeof(GX2Resource) == 0x80, "agl::driver::GX2Resource size mismatch");


} }
