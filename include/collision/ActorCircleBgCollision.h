#pragma once

#include <collision/BgCollision.h>
#include <system/ID.h>

class ActorCircleBgCollision : public BgCollision
{
    SEAD_RTTI_OVERRIDE(CircularCollider, ColliderBase)

public:
    ActorCircleBgCollision();
    virtual ~ActorCircleBgCollision();

    bool vf24(u32*, u32) override;
    u32 vf2C(u32*) override;
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

private:
    void setCommon_(const FollowArg& follow_arg, const CircleInitArg& init_arg);

public:
    void set(Actor* p_owner, const CircleInitArg& arg);
    void set(Actor* p_owner, const CircleInitArg& arg, ID id_1, ID id_2);

private:
    sead::Vector2f  mP0;
    sead::Vector2f  _160;
    sead::Vector2f  _168;
    f32             mRadius;
    f32             _174;
    u32             _178;
    u32             _17c;
    u32             _180;
    u32             _184;
    u32             _188;
    u32             _18c;
};
static_assert(sizeof(ActorCircleBgCollision) == 0x190);
