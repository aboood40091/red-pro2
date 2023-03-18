#pragma once

#include <collision/BgCollision.h>

class LoopRideLineBgCollisionUtil;

class LoopRideLineBgCollision : public BgCollision
{
    SEAD_RTTI_OVERRIDE(LoopRideLineBgCollision, BgCollision)

public:
    LoopRideLineBgCollision();
    LoopRideLineBgCollision(s32 point_num, sead::Vector2f* points, BasicRideLine* lines_1, BasicRideLine* lines_2);
    virtual ~LoopRideLineBgCollision();

    void vf34() override;
    void execute() override;
    bool vf44(RideLine*, u8*, sead::Vector2f*, sead::Vector2f*, u8) override;
    bool vf4C(RideLine*, sead::Vector2f*, sead::Vector2f*, u8 direction, ActorBgCollisionCheck*) override;
    bool vf54(u8*, sead::Vector2f*) override;
    bool vf5C(u32*) override; // deleted
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(sead::Vector2f*, f32) override;

    virtual void vf84();

    void setCommon(const FollowArg& follow_arg, const InitArg& init_arg);

    void set(Actor* p_owner, const InitArg& arg);
    void set(Actor* p_owner, const InitArg& arg, s32 point_num, sead::Heap* heap = nullptr);

protected:
    sead::Buffer<sead::Vector2f>    mPoint;
    sead::Buffer<BasicRideLine>     mRideLine1;
    sead::Buffer<BasicRideLine>     mRideLine2;

    friend class LoopRideLineBgCollisionUtil;
};
static_assert(sizeof(LoopRideLineBgCollision) == 0x170);
