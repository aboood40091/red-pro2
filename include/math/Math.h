#pragma once

#include <misc/rio_Types.h>

#include <cmath>

f32 Idx2Rad(s32 a)
{
    return a * 3.141592653589793238462f / 0x80000000u;
}

s32 Rad2Idx(f32 a)
{
    return a * 0x80000000u / 3.141592653589793238462f;
}

void SinCosIdx(f32* p_sin, f32* p_cos, u32 idx)
{
    f32 rad = Idx2Rad(idx);
    *p_sin = std::sin(rad);
    *p_cos = std::cos(rad);
}
