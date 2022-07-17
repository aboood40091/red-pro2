#pragma once

#include <common/aglTextureSampler.h>
#include <heap/seadDisposer.h>

namespace agl { namespace utl {

class PrimitiveTexture
{
    SEAD_SINGLETON_DISPOSER(PrimitiveTexture)

public:
    PrimitiveTexture();
    virtual ~PrimitiveTexture();

    TextureSampler& getTextureSampler(s32 index) { return mTextureSampler[index]; }
    const TextureSampler& getTextureSampler(s32 index) const { return mTextureSampler[index]; }

private:
    TextureSampler mTextureSampler[11]; // sead::SafeArray?
};
static_assert(sizeof(PrimitiveTexture) == 0x11F4, "agl::utl::PrimitiveTexture size mismatch");


} }
