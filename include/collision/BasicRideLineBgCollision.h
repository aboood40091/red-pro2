#pragma once

#include <collision/BgCollision.h>

class BasicRideLineBgCollision : public BgCollision
{
    SEAD_RTTI_OVERRIDE(BasicRideLineBgCollision, BgCollision)

public:
    BasicRideLineBgCollision();
    BasicRideLineBgCollision(s32 point_num, sead::Vector2f* points, BasicRideLine* lines_1, BasicRideLine* lines_2);
    virtual ~BasicRideLineBgCollision();

    void vf34() override;
    void execute() override;
    bool vf44(RideLine*, u8*, sead::Vector2f*, sead::Vector2f*, u8) override;
    bool vf4C(RideLine*, sead::Vector2f*, sead::Vector2f*, u8 direction, ActorBgCollisionCheck*) override;
    bool vf54(u8*, sead::Vector2f*) override;
    bool vf5C(u32*) override;
    void vf64() override;
    void vf6C() override;
    void vf74(u32*) override;
    bool vf7C(sead::Vector2f*, f32) override;

    void setCommon(const FollowArg& follow_arg, const InitArg& init_arg);

    void set(Actor* p_owner, const InitArg& arg);
    void set(Actor* p_owner, const InitArg& arg, s32 point_num, sead::Heap* heap = nullptr);

protected:
    sead::Buffer<sead::Vector2f>    mPoint;
    sead::Buffer<BasicRideLine>     mRideLine1;
    sead::Buffer<BasicRideLine>     mRideLine2;
    f32                             _170;
    u8                              _174[0x178 - 0x174];
};
static_assert(sizeof(BasicRideLineBgCollision) == 0x178);
