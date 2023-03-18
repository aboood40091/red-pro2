#pragma once

#include <actor/ActorMultiState.h>
#include <collision/SquareCollider.h>

class BlockCoinBase : public ActorMultiState
{
    SEAD_RTTI_OVERRIDE(BlockCoinBase, ActorMultiState)

public:
    enum Content
    {
        cContent_FireMushroom = 0,
        cContent_MiniMushroom,
        cContent_LifeMushroom,
        cContent_Mushroom,
        cContent_FireFlower,
        cContent_IceMushroom,
        cContent_PenguinMushroom,
        cContent_PropellerMushroom,
        cContent_Star,
        cContent_ContinuousStar,
        cContent_SquirrelMushroom,
        cContent_LifeMoon,
        cContent_Coin,
        cContent_MultiCoin,

        cContent_Vine = 15,
        cContent_Yoshi,
        cContent_Spring,

        cContent_MushroomIfSmall = 19,

        cContent_Empty = 21
    };

public:
    BlockCoinBase(const ActorInitArg& arg);
    virtual ~BlockCoinBase() { }

    void spawnJumpdai();
    void spawnYoshiEgg(bool multi);
    void spawnVine();
    void spawnPowerup(const sead::Vector3f& pos, u32, u32, bool spawn_as_child);
    void spawnMultiPowerup(const sead::Vector3f& pos, u32, u32, bool spawn_as_child);

    virtual void vf18C();
    virtual void vf194();
    virtual void setFootSensor();
    virtual void vf1A4();
    virtual void spawnItemUp();
    virtual void vf1B4();
    virtual void vf1BC();
    virtual void spawnItemDown();
    virtual void vf1CC();
    virtual void vf1D4(bool);
    virtual u32 vf1DC();
    virtual void spawnCoinShower();
    virtual void vf1EC();

    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, UpMove)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, UpMoveEnd)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, DownMove)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, DownMoveEnd)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, UpMove_Diff)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, DownMove_Diff)
    DECLARE_STATE_VIRTUAL_ID_BASE(BlockCoinBase, DownMove_DiffEnd)

    static void callbackFoot(BgCollision* self, ActorBgCollisionCheck* other);
    static void callbackHead(BgCollision* self, ActorBgCollisionCheck* other);
    static void callBackWall(BgCollision* self, ActorBgCollisionCheck* other, u8 direction);

    static void callbackFoot_Hit(BgCollision* self, ActorBgCollisionCheck* other);
    static void callbackHead_Hit(BgCollision* self, ActorBgCollisionCheck* other);
    static void callBackWall_Hit(BgCollision* self, ActorBgCollisionCheck* other, u8 direction);

protected:
    ActorBgCollisionCheck::Sensor   _17c8;
    u8                              _17d4[4];
    SquareCollider                  mSquareCollider;
    sead::Vector2f                  _1a68;
    sead::Vector2f                  _1a70;
    f32                             _1a78;
    f32                             _1a7c;
    f32                             _1a80;
    f32                             _1a84;
    f32                             _1a88;
    f32                             _1a8c;
    u32                             _1a90;
    u32                             _1a94;
    s32                             _1a98;
    u32                             _1a9c;
    u16                             _1aa0;
    u16                             _1aa2;
    u16                             _1aa4;
    u8                              _1aa6;
    u8                              _1aa7;
    s8                              _1aa8;
    s8                              _1aa9;
    u8                              _1aaa;
    u8                              _1aab;
    u8                              _1aac;
    u8                              _1aad;
    u8                              _1aae;
    u8                              _1aaf;
    u8                              _1ab0;
    u8                              _1ab1;
    u8                              mPlayerNo2;
    u8                              _1ab3;
    u32                             _1ab4;
    Content                         mContent;
    u32                             mHitPlayerNo;
    u32                             mSpawnDirection;
    u8                              _1ac4;
    u32                             _1ac8;
    u8                              _1acc;
    u8                              _1acd;
    u8                              _1ace;
    u8                              _1acf;
    f32                             _1ad0;
    f32                             _1ad4;
    f32                             _1ad8;
    u32                             _1adc;
    u32                             _1ae0;
    u32                             _1ae4;
    u32                             _1ae8;
    u32                             _1aec;
    s8                              _1af0[48];
    u8                              _1b20;
    u32                             _1b24;
};
static_assert(sizeof(BlockCoinBase) == 0x1B28);
