#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>

struct FollowArg
{
    FollowArg()
        : p_position(nullptr)
        , p_position_prev(nullptr)
        , p_layer(nullptr)
        , p_collision_mask(nullptr)
        , p_player_no(nullptr)
    {
    }

    sead::Vector3f* p_position;
    sead::Vector3f* p_position_prev;
    u8*             p_layer;
    sead::BitFlag8* p_collision_mask;
    u8*             p_player_no;
};
static_assert(sizeof(FollowArg) == 0x14);
