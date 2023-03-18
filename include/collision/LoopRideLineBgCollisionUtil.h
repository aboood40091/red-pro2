#pragma once

#include <collision/LoopRideLineBgCollision.h>

class LoopRideLineBgCollisionUtil
{
    // For setting a LoopRideLineBgCollision as a square

public:
    static void setCommon(LoopRideLineBgCollision* p_bg_collision, const FollowArg& follow_arg, const BgCollision::SquareInitArg& init_arg);
    static void set(LoopRideLineBgCollision* p_bg_collision, Actor* p_owner, const BgCollision::SquareInitArg& arg);
    static void setOfs(LoopRideLineBgCollision* p_bg_collision, const sead::Vector2f& p0, const sead::Vector2f& p1);
};
