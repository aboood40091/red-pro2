#pragma once

#include <misc/rio_Types.h>

#include <nn/ffl.h>

namespace Mii {

class CafeResInitializer
{
public:
    CafeResInitializer(bool param);

    bool initialize();
    void destroy();

private:
    void createHeaps_(const FFLInitDesc* p_init_desc);
    void destroyHeaps_();

    bool loadFFLShader_();
    void unloadFFLShader_();

private:
    void*       mpWorkMemory;
    u8*         mpFFLShaderData;
    bool        _10;
};
//static_assert(sizeof(CafeResInitializer) == 0x14);

}
