#pragma once

#include <state/StateMethod.h>
#include <state/StateMgr.h>

#include <math/seadVector.h>

enum ParentMovementType
{
    cPos_None                       = 0,
    cPos_CenterRotation             = 1,    // Pivotal Rotation
    cPos_Screw                      = 2,    // Bolt
    cPos_Rail                       = 3,
    cPos_GoAndCome                  = 4,    // Two Way
    //
    cPos_ScrewKinokoLift            = 6,    // Bolt Mushroom Lift
    cPos_ScrewKinokoLift_NoScrew    = 7,    // Bolt Mushroom Lift - No Bolt
    cPos_ShiftingPlatform           = 8,
    cPos_Gyration                   = 9,
    cPos_FloorGyration              = 10,   // Rolling Hill
    cPos_KinokoLift                 = 11,   // Mushroom Lift
};

class ParentMovementMgr
{
public:
    ParentMovementMgr();

    void link(const sead::Vector3f& position, u32 type_mask, u8 movement_id);
    void execute();
    u32 getTypeMask(ParentMovementType type);

    DECLARE_STATE_ID(ParentMovementType, Search)
    DECLARE_STATE_ID(ParentMovementType, Move)

private:
    sead::Vector3f          mPosition;
    sead::Vector3f          _c;
    sead::Vector3f          _18;
    sead::Vector3f          _24;
    u32                     _30;
    u32                     _34;
    u32                     _38;
    u32                     _3c;
    u32                     _40;
    u32                     _44;
    u32                     mTypeMask;
    u8                      mMovementId;
    u32                     mRotation;
    u8                      _54;
    f32                     _58;

    u8                      _5c[0x74-0x5C];

    u32                     _74;
    u32                     _78;
    u32                     _7c;
    u32                     _80;
    u8                      _84;
    u8                      _85;
    u8                      _86;
    u8                      _87;
    u8                      _88;
    u8                      _89;
    u32                     _8c;
    f32                     _90;
    u32                     _94;

    u8                      _98[0xA0-0x98];

    u32                     _a0;
    u32                     _a4;
    u32                     _a8;
    u32                     _ac;
    u32                     _b0;
    u32                     _b4;
    u32                     _b8;
    u32                     _bc;

    u8                      _c0[0xD4-0xC0];

    StateMgr<
        ParentMovementMgr,
        StateMethod
    >                       mFStateMgr;
};
static_assert(sizeof(ParentMovementMgr) == 0xF8);
