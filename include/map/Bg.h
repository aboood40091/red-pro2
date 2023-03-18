#pragma once

#include <heap/seadDisposer.h>

class Bg
{
    SEAD_SINGLETON_DISPOSER(Bg)

public:
    Bg();
    virtual ~Bg();

    static u16* getUnit(u16 x, u16 y, u32 file, u8 layer, s32* p_block_idx = nullptr);
    static u16* getUnitCurrentCdCile(u16 x, u16 y, u8 layer, s32* p_block_idx = nullptr);
};
