#include <actor/ProfileInfo.h>

s16 ProfileInfo::getDrawPriority(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return -1;

    return cDrawPriority[id];
}

ProfileInfo::ResType ProfileInfo::getResType(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return cResType_Boot;

    return ResType(cResType[id]);
}

u32 ProfileInfo::getResNum(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return 0;

    return cResNum[id];
}

const sead::SafeString* ProfileInfo::getResList(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return nullptr;

    return cResList[id];
}

// --------------------------------------- DrawPriority --------------------------------------- //

const s16 ProfileInfo::cDrawPriority[cProfileID_Max] = {
    ProfileInfo::cDrawPriority_000,                                     // ProfileInfo::cProfileID_000
    ProfileInfo::cDrawPriority_001,                                     // ProfileInfo::cProfileID_001
    ProfileInfo::cDrawPriority_002,                                     // ProfileInfo::cProfileID_002
    ProfileInfo::cDrawPriority_003,                                     // ProfileInfo::cProfileID_003
    ProfileInfo::cDrawPriority_004,                                     // ProfileInfo::cProfileID_004
    ProfileInfo::cDrawPriority_005,                                     // ProfileInfo::cProfileID_005
    ProfileInfo::cDrawPriority_006,                                     // ProfileInfo::cProfileID_006
    ProfileInfo::cDrawPriority_007,                                     // ProfileInfo::cProfileID_007
    ProfileInfo::cDrawPriority_008,                                     // ProfileInfo::cProfileID_008
    ProfileInfo::cDrawPriority_009,                                     // ProfileInfo::cProfileID_009
    ProfileInfo::cDrawPriority_00A,                                     // ProfileInfo::cProfileID_00A
    ProfileInfo::cDrawPriority_00B,                                     // ProfileInfo::cProfileID_00B
    ProfileInfo::cDrawPriority_00C,                                     // ProfileInfo::cProfileID_00C
    ProfileInfo::cDrawPriority_00D,                                     // ProfileInfo::cProfileID_00D
    ProfileInfo::cDrawPriority_00E,                                     // ProfileInfo::cProfileID_00E
    ProfileInfo::cDrawPriority_00F,                                     // ProfileInfo::cProfileID_00F
    ProfileInfo::cDrawPriority_010,                                     // ProfileInfo::cProfileID_010
    ProfileInfo::cDrawPriority_011,                                     // ProfileInfo::cProfileID_011
    ProfileInfo::cDrawPriority_012,                                     // ProfileInfo::cProfileID_012
    ProfileInfo::cDrawPriority_013,                                     // ProfileInfo::cProfileID_013
    ProfileInfo::cDrawPriority_014,                                     // ProfileInfo::cProfileID_014
    ProfileInfo::cDrawPriority_015,                                     // ProfileInfo::cProfileID_015
    ProfileInfo::cDrawPriority_016,                                     // ProfileInfo::cProfileID_016
    ProfileInfo::cDrawPriority_017,                                     // ProfileInfo::cProfileID_017
    ProfileInfo::cDrawPriority_MiniGameMgr,                             // ProfileInfo::cProfileID_MiniGameMgr
    ProfileInfo::cDrawPriority_MiniGameMgrRDash,                        // ProfileInfo::cProfileID_MiniGameMgrRDash
    ProfileInfo::cDrawPriority_ShuffleBlockMgr,                         // ProfileInfo::cProfileID_ShuffleBlockMgr
    ProfileInfo::cDrawPriority_SlotMgr,                                 // ProfileInfo::cProfileID_SlotMgr
    ProfileInfo::cDrawPriority_CoinmakiMgr,                             // ProfileInfo::cProfileID_CoinmakiMgr
    ProfileInfo::cDrawPriority_01D,                                     // ProfileInfo::cProfileID_01D
    ProfileInfo::cDrawPriority_01E,                                     // ProfileInfo::cProfileID_01E
    ProfileInfo::cDrawPriority_01F,                                     // ProfileInfo::cProfileID_01F
    ProfileInfo::cDrawPriority_020,                                     // ProfileInfo::cProfileID_020
    ProfileInfo::cDrawPriority_ShootingStar,                            // ProfileInfo::cProfileID_ShootingStar
    ProfileInfo::cDrawPriority_StaffRollMgr,                            // ProfileInfo::cProfileID_StaffRollMgr
    ProfileInfo::cDrawPriority_StaffRollMgrRDash,                       // ProfileInfo::cProfileID_StaffRollMgrRDash
    ProfileInfo::cDrawPriority_024,                                     // ProfileInfo::cProfileID_024
    ProfileInfo::cDrawPriority_025,                                     // ProfileInfo::cProfileID_025
    ProfileInfo::cDrawPriority_026,                                     // ProfileInfo::cProfileID_026
    ProfileInfo::cDrawPriority_027,                                     // ProfileInfo::cProfileID_027
    ProfileInfo::cDrawPriority_028,                                     // ProfileInfo::cProfileID_028
    ProfileInfo::cDrawPriority_029,                                     // ProfileInfo::cProfileID_029
    ProfileInfo::cDrawPriority_02A,                                     // ProfileInfo::cProfileID_02A
    ProfileInfo::cDrawPriority_02B,                                     // ProfileInfo::cProfileID_02B
    ProfileInfo::cDrawPriority_02C,                                     // ProfileInfo::cProfileID_02C
    ProfileInfo::cDrawPriority_02D,                                     // ProfileInfo::cProfileID_02D
    ProfileInfo::cDrawPriority_02E,                                     // ProfileInfo::cProfileID_02E
    ProfileInfo::cDrawPriority_02F,                                     // ProfileInfo::cProfileID_02F
    ProfileInfo::cDrawPriority_030,                                     // ProfileInfo::cProfileID_030
    ProfileInfo::cDrawPriority_031,                                     // ProfileInfo::cProfileID_031
    ProfileInfo::cDrawPriority_032,                                     // ProfileInfo::cProfileID_032
    ProfileInfo::cDrawPriority_033,                                     // ProfileInfo::cProfileID_033
    ProfileInfo::cDrawPriority_ElasticKinokoParent,                     // ProfileInfo::cProfileID_ElasticKinokoParent
    ProfileInfo::cDrawPriority_FloorGyration,                           // ProfileInfo::cProfileID_FloorGyration
    ProfileInfo::cDrawPriority_036,                                     // ProfileInfo::cProfileID_036
    ProfileInfo::cDrawPriority_037,                                     // ProfileInfo::cProfileID_037
    ProfileInfo::cDrawPriority_038,                                     // ProfileInfo::cProfileID_038
    ProfileInfo::cDrawPriority_039,                                     // ProfileInfo::cProfileID_039
    ProfileInfo::cDrawPriority_03A,                                     // ProfileInfo::cProfileID_03A
    ProfileInfo::cDrawPriority_03B,                                     // ProfileInfo::cProfileID_03B
    ProfileInfo::cDrawPriority_PairObjChild,                            // ProfileInfo::cProfileID_PairObjChild
    ProfileInfo::cDrawPriority_03D,                                     // ProfileInfo::cProfileID_03D
    ProfileInfo::cDrawPriority_03E,                                     // ProfileInfo::cProfileID_03E
    ProfileInfo::cDrawPriority_03F,                                     // ProfileInfo::cProfileID_03F
    ProfileInfo::cDrawPriority_040,                                     // ProfileInfo::cProfileID_040
    ProfileInfo::cDrawPriority_041,                                     // ProfileInfo::cProfileID_041
    ProfileInfo::cDrawPriority_042,                                     // ProfileInfo::cProfileID_042
    ProfileInfo::cDrawPriority_043,                                     // ProfileInfo::cProfileID_043
    ProfileInfo::cDrawPriority_044,                                     // ProfileInfo::cProfileID_044
    ProfileInfo::cDrawPriority_045,                                     // ProfileInfo::cProfileID_045
    ProfileInfo::cDrawPriority_046,                                     // ProfileInfo::cProfileID_046
    ProfileInfo::cDrawPriority_047,                                     // ProfileInfo::cProfileID_047
    ProfileInfo::cDrawPriority_048,                                     // ProfileInfo::cProfileID_048
    ProfileInfo::cDrawPriority_049,                                     // ProfileInfo::cProfileID_049
    ProfileInfo::cDrawPriority_04A,                                     // ProfileInfo::cProfileID_04A
    ProfileInfo::cDrawPriority_04B,                                     // ProfileInfo::cProfileID_04B
    ProfileInfo::cDrawPriority_04C,                                     // ProfileInfo::cProfileID_04C
    ProfileInfo::cDrawPriority_KinokoLift,                              // ProfileInfo::cProfileID_KinokoLift
    ProfileInfo::cDrawPriority_KinokoLiftColor,                         // ProfileInfo::cProfileID_KinokoLiftColor
    ProfileInfo::cDrawPriority_LiftZenStar,                             // ProfileInfo::cProfileID_LiftZenStar
    ProfileInfo::cDrawPriority_050,                                     // ProfileInfo::cProfileID_050
    ProfileInfo::cDrawPriority_051,                                     // ProfileInfo::cProfileID_051
    ProfileInfo::cDrawPriority_052,                                     // ProfileInfo::cProfileID_052
    ProfileInfo::cDrawPriority_053,                                     // ProfileInfo::cProfileID_053
    ProfileInfo::cDrawPriority_054,                                     // ProfileInfo::cProfileID_054
    ProfileInfo::cDrawPriority_055,                                     // ProfileInfo::cProfileID_055
    ProfileInfo::cDrawPriority_056,                                     // ProfileInfo::cProfileID_056
    ProfileInfo::cDrawPriority_057,                                     // ProfileInfo::cProfileID_057
    ProfileInfo::cDrawPriority_058,                                     // ProfileInfo::cProfileID_058
    ProfileInfo::cDrawPriority_059,                                     // ProfileInfo::cProfileID_059
    ProfileInfo::cDrawPriority_BgActorYukaMario,                        // ProfileInfo::cProfileID_BgActorYukaMario
    ProfileInfo::cDrawPriority_05B,                                     // ProfileInfo::cProfileID_05B
    ProfileInfo::cDrawPriority_05C,                                     // ProfileInfo::cProfileID_05C
    ProfileInfo::cDrawPriority_05D,                                     // ProfileInfo::cProfileID_05D
    ProfileInfo::cDrawPriority_05E,                                     // ProfileInfo::cProfileID_05E
    ProfileInfo::cDrawPriority_05F,                                     // ProfileInfo::cProfileID_05F
    ProfileInfo::cDrawPriority_060,                                     // ProfileInfo::cProfileID_060
    ProfileInfo::cDrawPriority_061,                                     // ProfileInfo::cProfileID_061
    ProfileInfo::cDrawPriority_062,                                     // ProfileInfo::cProfileID_062
    ProfileInfo::cDrawPriority_063,                                     // ProfileInfo::cProfileID_063
    ProfileInfo::cDrawPriority_064,                                     // ProfileInfo::cProfileID_064
    ProfileInfo::cDrawPriority_KillerHoudai,                            // ProfileInfo::cProfileID_KillerHoudai
    ProfileInfo::cDrawPriority_StretchKillerHoudai,                     // ProfileInfo::cProfileID_StretchKillerHoudai
    ProfileInfo::cDrawPriority_MagnumKillerHoudai,                      // ProfileInfo::cProfileID_MagnumKillerHoudai
    ProfileInfo::cDrawPriority_MagnumKillerHoudaiDown,                  // ProfileInfo::cProfileID_MagnumKillerHoudaiDown
    ProfileInfo::cDrawPriority_SearchKillerHoudai,                      // ProfileInfo::cProfileID_SearchKillerHoudai
    ProfileInfo::cDrawPriority_SearchMagnumKillerHoudai,                // ProfileInfo::cProfileID_SearchMagnumKillerHoudai
    ProfileInfo::cDrawPriority_SearchMagnumKillerHoudaiDown,            // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDown
    ProfileInfo::cDrawPriority_MagnumKillerHoudaiRDash,                 // ProfileInfo::cProfileID_MagnumKillerHoudaiRDash
    ProfileInfo::cDrawPriority_MagnumKillerHoudaiDownRDash,             // ProfileInfo::cProfileID_MagnumKillerHoudaiDownRDash
    ProfileInfo::cDrawPriority_SearchMagnumKillerHoudaiRDash,           // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiRDash
    ProfileInfo::cDrawPriority_SearchMagnumKillerHoudaiDownRDash,       // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDownRDash
    ProfileInfo::cDrawPriority_070,                                     // ProfileInfo::cProfileID_070
    ProfileInfo::cDrawPriority_071,                                     // ProfileInfo::cProfileID_071
    ProfileInfo::cDrawPriority_072,                                     // ProfileInfo::cProfileID_072
    ProfileInfo::cDrawPriority_073,                                     // ProfileInfo::cProfileID_073
    ProfileInfo::cDrawPriority_074,                                     // ProfileInfo::cProfileID_074
    ProfileInfo::cDrawPriority_075,                                     // ProfileInfo::cProfileID_075
    ProfileInfo::cDrawPriority_076,                                     // ProfileInfo::cProfileID_076
    ProfileInfo::cDrawPriority_077,                                     // ProfileInfo::cProfileID_077
    ProfileInfo::cDrawPriority_078,                                     // ProfileInfo::cProfileID_078
    ProfileInfo::cDrawPriority_Intermittent,                            // ProfileInfo::cProfileID_Intermittent
    ProfileInfo::cDrawPriority_IntermittentPermanent,                   // ProfileInfo::cProfileID_IntermittentPermanent
    ProfileInfo::cDrawPriority_WaterIntermittent,                       // ProfileInfo::cProfileID_WaterIntermittent
    ProfileInfo::cDrawPriority_WaterIntermittentPermanent,              // ProfileInfo::cProfileID_WaterIntermittentPermanent
    ProfileInfo::cDrawPriority_WaterIntermittentPermanentRD3_3,         // ProfileInfo::cProfileID_WaterIntermittentPermanentRD3_3
    ProfileInfo::cDrawPriority_07E,                                     // ProfileInfo::cProfileID_07E
    ProfileInfo::cDrawPriority_WaterIntermittentBossChild,              // ProfileInfo::cProfileID_WaterIntermittentBossChild
    ProfileInfo::cDrawPriority_YoganIntermittent,                       // ProfileInfo::cProfileID_YoganIntermittent
    ProfileInfo::cDrawPriority_081,                                     // ProfileInfo::cProfileID_081
    ProfileInfo::cDrawPriority_082,                                     // ProfileInfo::cProfileID_082
    ProfileInfo::cDrawPriority_083,                                     // ProfileInfo::cProfileID_083
    ProfileInfo::cDrawPriority_084,                                     // ProfileInfo::cProfileID_084
    ProfileInfo::cDrawPriority_085,                                     // ProfileInfo::cProfileID_085
    ProfileInfo::cDrawPriority_ObjPipeDownNG,                           // ProfileInfo::cProfileID_ObjPipeDownNG
    ProfileInfo::cDrawPriority_087,                                     // ProfileInfo::cProfileID_087
    ProfileInfo::cDrawPriority_088,                                     // ProfileInfo::cProfileID_088
    ProfileInfo::cDrawPriority_089,                                     // ProfileInfo::cProfileID_089
    ProfileInfo::cDrawPriority_08A,                                     // ProfileInfo::cProfileID_08A
    ProfileInfo::cDrawPriority_08B,                                     // ProfileInfo::cProfileID_08B
    ProfileInfo::cDrawPriority_08C,                                     // ProfileInfo::cProfileID_08C
    ProfileInfo::cDrawPriority_08D,                                     // ProfileInfo::cProfileID_08D
    ProfileInfo::cDrawPriority_08E,                                     // ProfileInfo::cProfileID_08E
    ProfileInfo::cDrawPriority_08F,                                     // ProfileInfo::cProfileID_08F
    ProfileInfo::cDrawPriority_090,                                     // ProfileInfo::cProfileID_090
    ProfileInfo::cDrawPriority_091,                                     // ProfileInfo::cProfileID_091
    ProfileInfo::cDrawPriority_092,                                     // ProfileInfo::cProfileID_092
    ProfileInfo::cDrawPriority_093,                                     // ProfileInfo::cProfileID_093
    ProfileInfo::cDrawPriority_094,                                     // ProfileInfo::cProfileID_094
    ProfileInfo::cDrawPriority_095,                                     // ProfileInfo::cProfileID_095
    ProfileInfo::cDrawPriority_096,                                     // ProfileInfo::cProfileID_096
    ProfileInfo::cDrawPriority_097,                                     // ProfileInfo::cProfileID_097
    ProfileInfo::cDrawPriority_098,                                     // ProfileInfo::cProfileID_098
    ProfileInfo::cDrawPriority_099,                                     // ProfileInfo::cProfileID_099
    ProfileInfo::cDrawPriority_09A,                                     // ProfileInfo::cProfileID_09A
    ProfileInfo::cDrawPriority_09B,                                     // ProfileInfo::cProfileID_09B
    ProfileInfo::cDrawPriority_09C,                                     // ProfileInfo::cProfileID_09C
    ProfileInfo::cDrawPriority_09D,                                     // ProfileInfo::cProfileID_09D
    ProfileInfo::cDrawPriority_09E,                                     // ProfileInfo::cProfileID_09E
    ProfileInfo::cDrawPriority_09F,                                     // ProfileInfo::cProfileID_09F
    ProfileInfo::cDrawPriority_0A0,                                     // ProfileInfo::cProfileID_0A0
    ProfileInfo::cDrawPriority_0A1,                                     // ProfileInfo::cProfileID_0A1
    ProfileInfo::cDrawPriority_0A2,                                     // ProfileInfo::cProfileID_0A2
    ProfileInfo::cDrawPriority_0A3,                                     // ProfileInfo::cProfileID_0A3
    ProfileInfo::cDrawPriority_0A4,                                     // ProfileInfo::cProfileID_0A4
    ProfileInfo::cDrawPriority_0A5,                                     // ProfileInfo::cProfileID_0A5
    ProfileInfo::cDrawPriority_0A6,                                     // ProfileInfo::cProfileID_0A6
    ProfileInfo::cDrawPriority_0A7,                                     // ProfileInfo::cProfileID_0A7
    ProfileInfo::cDrawPriority_0A8,                                     // ProfileInfo::cProfileID_0A8
    ProfileInfo::cDrawPriority_0A9,                                     // ProfileInfo::cProfileID_0A9
    ProfileInfo::cDrawPriority_0AA,                                     // ProfileInfo::cProfileID_0AA
    ProfileInfo::cDrawPriority_0AB,                                     // ProfileInfo::cProfileID_0AB
    ProfileInfo::cDrawPriority_0AC,                                     // ProfileInfo::cProfileID_0AC
    ProfileInfo::cDrawPriority_0AD,                                     // ProfileInfo::cProfileID_0AD
    ProfileInfo::cDrawPriority_0AE,                                     // ProfileInfo::cProfileID_0AE
    ProfileInfo::cDrawPriority_0AF,                                     // ProfileInfo::cProfileID_0AF
    ProfileInfo::cDrawPriority_0B0,                                     // ProfileInfo::cProfileID_0B0
    ProfileInfo::cDrawPriority_0B1,                                     // ProfileInfo::cProfileID_0B1
    ProfileInfo::cDrawPriority_0B2,                                     // ProfileInfo::cProfileID_0B2
    ProfileInfo::cDrawPriority_0B3,                                     // ProfileInfo::cProfileID_0B3
    ProfileInfo::cDrawPriority_0B4,                                     // ProfileInfo::cProfileID_0B4
    ProfileInfo::cDrawPriority_0B5,                                     // ProfileInfo::cProfileID_0B5
    ProfileInfo::cDrawPriority_0B6,                                     // ProfileInfo::cProfileID_0B6
    ProfileInfo::cDrawPriority_0B7,                                     // ProfileInfo::cProfileID_0B7
    ProfileInfo::cDrawPriority_LineSpinLift,                            // ProfileInfo::cProfileID_LineSpinLift
    ProfileInfo::cDrawPriority_LineSpinLiftParentRDash,                 // ProfileInfo::cProfileID_LineSpinLiftParentRDash
    ProfileInfo::cDrawPriority_LineSpinLiftChildRDash,                  // ProfileInfo::cProfileID_LineSpinLiftChildRDash
    ProfileInfo::cDrawPriority_0BB,                                     // ProfileInfo::cProfileID_0BB
    ProfileInfo::cDrawPriority_0BC,                                     // ProfileInfo::cProfileID_0BC
    ProfileInfo::cDrawPriority_0BD,                                     // ProfileInfo::cProfileID_0BD
    ProfileInfo::cDrawPriority_0BE,                                     // ProfileInfo::cProfileID_0BE
    ProfileInfo::cDrawPriority_0BF,                                     // ProfileInfo::cProfileID_0BF
    ProfileInfo::cDrawPriority_0C0,                                     // ProfileInfo::cProfileID_0C0
    ProfileInfo::cDrawPriority_0C1,                                     // ProfileInfo::cProfileID_0C1
    ProfileInfo::cDrawPriority_SnakeBlock,                              // ProfileInfo::cProfileID_SnakeBlock
    ProfileInfo::cDrawPriority_0C3,                                     // ProfileInfo::cProfileID_0C3
    ProfileInfo::cDrawPriority_0C4,                                     // ProfileInfo::cProfileID_0C4
    ProfileInfo::cDrawPriority_0C5,                                     // ProfileInfo::cProfileID_0C5
    ProfileInfo::cDrawPriority_0C6,                                     // ProfileInfo::cProfileID_0C6
    ProfileInfo::cDrawPriority_0C7,                                     // ProfileInfo::cProfileID_0C7
    ProfileInfo::cDrawPriority_0C8,                                     // ProfileInfo::cProfileID_0C8
    ProfileInfo::cDrawPriority_0C9,                                     // ProfileInfo::cProfileID_0C9
    ProfileInfo::cDrawPriority_0CA,                                     // ProfileInfo::cProfileID_0CA
    ProfileInfo::cDrawPriority_0CB,                                     // ProfileInfo::cProfileID_0CB
    ProfileInfo::cDrawPriority_0CC,                                     // ProfileInfo::cProfileID_0CC
    ProfileInfo::cDrawPriority_0CD,                                     // ProfileInfo::cProfileID_0CD
    ProfileInfo::cDrawPriority_0CE,                                     // ProfileInfo::cProfileID_0CE
    ProfileInfo::cDrawPriority_0CF,                                     // ProfileInfo::cProfileID_0CF
    ProfileInfo::cDrawPriority_0D0,                                     // ProfileInfo::cProfileID_0D0
    ProfileInfo::cDrawPriority_0D1,                                     // ProfileInfo::cProfileID_0D1
    ProfileInfo::cDrawPriority_FloorHoleDokan,                          // ProfileInfo::cProfileID_FloorHoleDokan
    ProfileInfo::cDrawPriority_0D3,                                     // ProfileInfo::cProfileID_0D3
    ProfileInfo::cDrawPriority_0D4,                                     // ProfileInfo::cProfileID_0D4
    ProfileInfo::cDrawPriority_0D5,                                     // ProfileInfo::cProfileID_0D5
    ProfileInfo::cDrawPriority_0D6,                                     // ProfileInfo::cProfileID_0D6
    ProfileInfo::cDrawPriority_0D7,                                     // ProfileInfo::cProfileID_0D7
    ProfileInfo::cDrawPriority_0D8,                                     // ProfileInfo::cProfileID_0D8
    ProfileInfo::cDrawPriority_0D9,                                     // ProfileInfo::cProfileID_0D9
    ProfileInfo::cDrawPriority_0DA,                                     // ProfileInfo::cProfileID_0DA
    ProfileInfo::cDrawPriority_0DB,                                     // ProfileInfo::cProfileID_0DB
    ProfileInfo::cDrawPriority_0DC,                                     // ProfileInfo::cProfileID_0DC
    ProfileInfo::cDrawPriority_0DD,                                     // ProfileInfo::cProfileID_0DD
    ProfileInfo::cDrawPriority_0DE,                                     // ProfileInfo::cProfileID_0DE
    ProfileInfo::cDrawPriority_0DF,                                     // ProfileInfo::cProfileID_0DF
    ProfileInfo::cDrawPriority_Burner,                                  // ProfileInfo::cProfileID_Burner
    ProfileInfo::cDrawPriority_0E1,                                     // ProfileInfo::cProfileID_0E1
    ProfileInfo::cDrawPriority_0E2,                                     // ProfileInfo::cProfileID_0E2
    ProfileInfo::cDrawPriority_0E3,                                     // ProfileInfo::cProfileID_0E3
    ProfileInfo::cDrawPriority_0E4,                                     // ProfileInfo::cProfileID_0E4
    ProfileInfo::cDrawPriority_0E5,                                     // ProfileInfo::cProfileID_0E5
    ProfileInfo::cDrawPriority_0E6,                                     // ProfileInfo::cProfileID_0E6
    ProfileInfo::cDrawPriority_0E7,                                     // ProfileInfo::cProfileID_0E7
    ProfileInfo::cDrawPriority_0E8,                                     // ProfileInfo::cProfileID_0E8
    ProfileInfo::cDrawPriority_0E9,                                     // ProfileInfo::cProfileID_0E9
    ProfileInfo::cDrawPriority_0EA,                                     // ProfileInfo::cProfileID_0EA
    ProfileInfo::cDrawPriority_0EB,                                     // ProfileInfo::cProfileID_0EB
    ProfileInfo::cDrawPriority_0EC,                                     // ProfileInfo::cProfileID_0EC
    ProfileInfo::cDrawPriority_PlyIce,                                  // ProfileInfo::cProfileID_PlyIce
    ProfileInfo::cDrawPriority_TarzanIvy,                               // ProfileInfo::cProfileID_TarzanIvy
    ProfileInfo::cDrawPriority_0EF,                                     // ProfileInfo::cProfileID_0EF
    ProfileInfo::cDrawPriority_0F0,                                     // ProfileInfo::cProfileID_0F0
    ProfileInfo::cDrawPriority_0F1,                                     // ProfileInfo::cProfileID_0F1
    ProfileInfo::cDrawPriority_0F2,                                     // ProfileInfo::cProfileID_0F2
    ProfileInfo::cDrawPriority_0F3,                                     // ProfileInfo::cProfileID_0F3
    ProfileInfo::cDrawPriority_0F4,                                     // ProfileInfo::cProfileID_0F4
    ProfileInfo::cDrawPriority_0F5,                                     // ProfileInfo::cProfileID_0F5
    ProfileInfo::cDrawPriority_0F6,                                     // ProfileInfo::cProfileID_0F6
    ProfileInfo::cDrawPriority_0F7,                                     // ProfileInfo::cProfileID_0F7
    ProfileInfo::cDrawPriority_0F8,                                     // ProfileInfo::cProfileID_0F8
    ProfileInfo::cDrawPriority_0F9,                                     // ProfileInfo::cProfileID_0F9
    ProfileInfo::cDrawPriority_0FA,                                     // ProfileInfo::cProfileID_0FA
    ProfileInfo::cDrawPriority_0FB,                                     // ProfileInfo::cProfileID_0FB
    ProfileInfo::cDrawPriority_0FC,                                     // ProfileInfo::cProfileID_0FC
    ProfileInfo::cDrawPriority_0FD,                                     // ProfileInfo::cProfileID_0FD
    ProfileInfo::cDrawPriority_0FE,                                     // ProfileInfo::cProfileID_0FE
    ProfileInfo::cDrawPriority_0FF,                                     // ProfileInfo::cProfileID_0FF
    ProfileInfo::cDrawPriority_100,                                     // ProfileInfo::cProfileID_100
    ProfileInfo::cDrawPriority_101,                                     // ProfileInfo::cProfileID_101
    ProfileInfo::cDrawPriority_102,                                     // ProfileInfo::cProfileID_102
    ProfileInfo::cDrawPriority_103,                                     // ProfileInfo::cProfileID_103
    ProfileInfo::cDrawPriority_104,                                     // ProfileInfo::cProfileID_104
    ProfileInfo::cDrawPriority_ShuffleBlock,                            // ProfileInfo::cProfileID_ShuffleBlock
    ProfileInfo::cDrawPriority_KokoopaShipWarpCannon,                   // ProfileInfo::cProfileID_KokoopaShipWarpCannon
    ProfileInfo::cDrawPriority_107,                                     // ProfileInfo::cProfileID_107
    ProfileInfo::cDrawPriority_108,                                     // ProfileInfo::cProfileID_108
    ProfileInfo::cDrawPriority_KoopaShutter,                            // ProfileInfo::cProfileID_KoopaShutter
    ProfileInfo::cDrawPriority_10A,                                     // ProfileInfo::cProfileID_10A
    ProfileInfo::cDrawPriority_10B,                                     // ProfileInfo::cProfileID_10B
    ProfileInfo::cDrawPriority_10C,                                     // ProfileInfo::cProfileID_10C
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJrLift,             // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLift
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJrLiftHmove,        // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftHmove
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJrLiftPairObj,      // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftPairObj
    ProfileInfo::cDrawPriority_RoyLiftWakiStep,                         // ProfileInfo::cProfileID_RoyLiftWakiStep
    ProfileInfo::cDrawPriority_WendyFloor,                              // ProfileInfo::cProfileID_WendyFloor
    ProfileInfo::cDrawPriority_IggyRoom,                                // ProfileInfo::cProfileID_IggyRoom
    ProfileInfo::cDrawPriority_113,                                     // ProfileInfo::cProfileID_113
    ProfileInfo::cDrawPriority_114,                                     // ProfileInfo::cProfileID_114
    ProfileInfo::cDrawPriority_115,                                     // ProfileInfo::cProfileID_115
    ProfileInfo::cDrawPriority_116,                                     // ProfileInfo::cProfileID_116
    ProfileInfo::cDrawPriority_117,                                     // ProfileInfo::cProfileID_117
    ProfileInfo::cDrawPriority_118,                                     // ProfileInfo::cProfileID_118
    ProfileInfo::cDrawPriority_119,                                     // ProfileInfo::cProfileID_119
    ProfileInfo::cDrawPriority_11A,                                     // ProfileInfo::cProfileID_11A
    ProfileInfo::cDrawPriority_11B,                                     // ProfileInfo::cProfileID_11B
    ProfileInfo::cDrawPriority_11C,                                     // ProfileInfo::cProfileID_11C
    ProfileInfo::cDrawPriority_11D,                                     // ProfileInfo::cProfileID_11D
    ProfileInfo::cDrawPriority_11E,                                     // ProfileInfo::cProfileID_11E
    ProfileInfo::cDrawPriority_Block,                                   // ProfileInfo::cProfileID_Block
    ProfileInfo::cDrawPriority_120,                                     // ProfileInfo::cProfileID_120
    ProfileInfo::cDrawPriority_121,                                     // ProfileInfo::cProfileID_121
    ProfileInfo::cDrawPriority_122,                                     // ProfileInfo::cProfileID_122
    ProfileInfo::cDrawPriority_ActorBlockRenga,                         // ProfileInfo::cProfileID_ActorBlockRenga
    ProfileInfo::cDrawPriority_124,                                     // ProfileInfo::cProfileID_124
    ProfileInfo::cDrawPriority_125,                                     // ProfileInfo::cProfileID_125
    ProfileInfo::cDrawPriority_126,                                     // ProfileInfo::cProfileID_126
    ProfileInfo::cDrawPriority_127,                                     // ProfileInfo::cProfileID_127
    ProfileInfo::cDrawPriority_128,                                     // ProfileInfo::cProfileID_128
    ProfileInfo::cDrawPriority_129,                                     // ProfileInfo::cProfileID_129
    ProfileInfo::cDrawPriority_12A,                                     // ProfileInfo::cProfileID_12A
    ProfileInfo::cDrawPriority_12B,                                     // ProfileInfo::cProfileID_12B
    ProfileInfo::cDrawPriority_12C,                                     // ProfileInfo::cProfileID_12C
    ProfileInfo::cDrawPriority_12D,                                     // ProfileInfo::cProfileID_12D
    ProfileInfo::cDrawPriority_12E,                                     // ProfileInfo::cProfileID_12E
    ProfileInfo::cDrawPriority_12F,                                     // ProfileInfo::cProfileID_12F
    ProfileInfo::cDrawPriority_130,                                     // ProfileInfo::cProfileID_130
    ProfileInfo::cDrawPriority_131,                                     // ProfileInfo::cProfileID_131
    ProfileInfo::cDrawPriority_132,                                     // ProfileInfo::cProfileID_132
    ProfileInfo::cDrawPriority_133,                                     // ProfileInfo::cProfileID_133
    ProfileInfo::cDrawPriority_134,                                     // ProfileInfo::cProfileID_134
    ProfileInfo::cDrawPriority_ActorBlockMakeDRC,                       // ProfileInfo::cProfileID_ActorBlockMakeDRC
    ProfileInfo::cDrawPriority_136,                                     // ProfileInfo::cProfileID_136
    ProfileInfo::cDrawPriority_137,                                     // ProfileInfo::cProfileID_137
    ProfileInfo::cDrawPriority_138,                                     // ProfileInfo::cProfileID_138
    ProfileInfo::cDrawPriority_139,                                     // ProfileInfo::cProfileID_139
    ProfileInfo::cDrawPriority_13A,                                     // ProfileInfo::cProfileID_13A
    ProfileInfo::cDrawPriority_13B,                                     // ProfileInfo::cProfileID_13B
    ProfileInfo::cDrawPriority_13C,                                     // ProfileInfo::cProfileID_13C
    ProfileInfo::cDrawPriority_13D,                                     // ProfileInfo::cProfileID_13D
    ProfileInfo::cDrawPriority_13E,                                     // ProfileInfo::cProfileID_13E
    ProfileInfo::cDrawPriority_13F,                                     // ProfileInfo::cProfileID_13F
    ProfileInfo::cDrawPriority_140,                                     // ProfileInfo::cProfileID_140
    ProfileInfo::cDrawPriority_141,                                     // ProfileInfo::cProfileID_141
    ProfileInfo::cDrawPriority_142,                                     // ProfileInfo::cProfileID_142
    ProfileInfo::cDrawPriority_143,                                     // ProfileInfo::cProfileID_143
    ProfileInfo::cDrawPriority_144,                                     // ProfileInfo::cProfileID_144
    ProfileInfo::cDrawPriority_145,                                     // ProfileInfo::cProfileID_145
    ProfileInfo::cDrawPriority_146,                                     // ProfileInfo::cProfileID_146
    ProfileInfo::cDrawPriority_147,                                     // ProfileInfo::cProfileID_147
    ProfileInfo::cDrawPriority_148,                                     // ProfileInfo::cProfileID_148
    ProfileInfo::cDrawPriority_149,                                     // ProfileInfo::cProfileID_149
    ProfileInfo::cDrawPriority_14A,                                     // ProfileInfo::cProfileID_14A
    ProfileInfo::cDrawPriority_14B,                                     // ProfileInfo::cProfileID_14B
    ProfileInfo::cDrawPriority_14C,                                     // ProfileInfo::cProfileID_14C
    ProfileInfo::cDrawPriority_14D,                                     // ProfileInfo::cProfileID_14D
    ProfileInfo::cDrawPriority_14E,                                     // ProfileInfo::cProfileID_14E
    ProfileInfo::cDrawPriority_14F,                                     // ProfileInfo::cProfileID_14F
    ProfileInfo::cDrawPriority_ObjPipeDown,                             // ProfileInfo::cProfileID_ObjPipeDown
    ProfileInfo::cDrawPriority_151,                                     // ProfileInfo::cProfileID_151
    ProfileInfo::cDrawPriority_152,                                     // ProfileInfo::cProfileID_152
    ProfileInfo::cDrawPriority_153,                                     // ProfileInfo::cProfileID_153
    ProfileInfo::cDrawPriority_ObjPipeDownGroup,                        // ProfileInfo::cProfileID_ObjPipeDownGroup
    ProfileInfo::cDrawPriority_155,                                     // ProfileInfo::cProfileID_155
    ProfileInfo::cDrawPriority_156,                                     // ProfileInfo::cProfileID_156
    ProfileInfo::cDrawPriority_157,                                     // ProfileInfo::cProfileID_157
    ProfileInfo::cDrawPriority_SwitchHatenaButton,                      // ProfileInfo::cProfileID_SwitchHatenaButton
    ProfileInfo::cDrawPriority_SwitchPbutton,                           // ProfileInfo::cProfileID_SwitchPbutton
    ProfileInfo::cDrawPriority_SwitchPbuttonRDash,                      // ProfileInfo::cProfileID_SwitchPbuttonRDash
    ProfileInfo::cDrawPriority_SwitchPbuttonNoWallKick,                 // ProfileInfo::cProfileID_SwitchPbuttonNoWallKick
    ProfileInfo::cDrawPriority_15C,                                     // ProfileInfo::cProfileID_15C
    ProfileInfo::cDrawPriority_15D,                                     // ProfileInfo::cProfileID_15D
    ProfileInfo::cDrawPriority_IcicleBig,                               // ProfileInfo::cProfileID_IcicleBig
    ProfileInfo::cDrawPriority_LemmyBall,                               // ProfileInfo::cProfileID_LemmyBall
    ProfileInfo::cDrawPriority_LemmyBomb,                               // ProfileInfo::cProfileID_LemmyBomb
    ProfileInfo::cDrawPriority_161,                                     // ProfileInfo::cProfileID_161
    ProfileInfo::cDrawPriority_162,                                     // ProfileInfo::cProfileID_162
    ProfileInfo::cDrawPriority_163,                                     // ProfileInfo::cProfileID_163
    ProfileInfo::cDrawPriority_164,                                     // ProfileInfo::cProfileID_164
    ProfileInfo::cDrawPriority_165,                                     // ProfileInfo::cProfileID_165
    ProfileInfo::cDrawPriority_166,                                     // ProfileInfo::cProfileID_166
    ProfileInfo::cDrawPriority_167,                                     // ProfileInfo::cProfileID_167
    ProfileInfo::cDrawPriority_168,                                     // ProfileInfo::cProfileID_168
    ProfileInfo::cDrawPriority_169,                                     // ProfileInfo::cProfileID_169
    ProfileInfo::cDrawPriority_PentaroIce,                              // ProfileInfo::cProfileID_PentaroIce
    ProfileInfo::cDrawPriority_16B,                                     // ProfileInfo::cProfileID_16B
    ProfileInfo::cDrawPriority_16C,                                     // ProfileInfo::cProfileID_16C
    ProfileInfo::cDrawPriority_16D,                                     // ProfileInfo::cProfileID_16D
    ProfileInfo::cDrawPriority_16E,                                     // ProfileInfo::cProfileID_16E
    ProfileInfo::cDrawPriority_16F,                                     // ProfileInfo::cProfileID_16F
    ProfileInfo::cDrawPriority_KameckIce,                               // ProfileInfo::cProfileID_KameckIce
    ProfileInfo::cDrawPriority_WendyIcicle,                             // ProfileInfo::cProfileID_WendyIcicle
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJrClown,            // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrClown
    ProfileInfo::cDrawPriority_BoxingKoopaJrClown,                      // ProfileInfo::cProfileID_BoxingKoopaJrClown
    ProfileInfo::cDrawPriority_174,                                     // ProfileInfo::cProfileID_174
    ProfileInfo::cDrawPriority_FinalKoopaJrClown,                       // ProfileInfo::cProfileID_FinalKoopaJrClown
    ProfileInfo::cDrawPriority_FinalKoopa,                              // ProfileInfo::cProfileID_FinalKoopa
    ProfileInfo::cDrawPriority_FireBar,                                 // ProfileInfo::cProfileID_FireBar
    ProfileInfo::cDrawPriority_FireBarSync,                             // ProfileInfo::cProfileID_FireBarSync
    ProfileInfo::cDrawPriority_179,                                     // ProfileInfo::cProfileID_179
    ProfileInfo::cDrawPriority_17A,                                     // ProfileInfo::cProfileID_17A
    ProfileInfo::cDrawPriority_17B,                                     // ProfileInfo::cProfileID_17B
    ProfileInfo::cDrawPriority_17C,                                     // ProfileInfo::cProfileID_17C
    ProfileInfo::cDrawPriority_17D,                                     // ProfileInfo::cProfileID_17D
    ProfileInfo::cDrawPriority_17E,                                     // ProfileInfo::cProfileID_17E
    ProfileInfo::cDrawPriority_17F,                                     // ProfileInfo::cProfileID_17F
    ProfileInfo::cDrawPriority_180,                                     // ProfileInfo::cProfileID_180
    ProfileInfo::cDrawPriority_181,                                     // ProfileInfo::cProfileID_181
    ProfileInfo::cDrawPriority_182,                                     // ProfileInfo::cProfileID_182
    ProfileInfo::cDrawPriority_183,                                     // ProfileInfo::cProfileID_183
    ProfileInfo::cDrawPriority_184,                                     // ProfileInfo::cProfileID_184
    ProfileInfo::cDrawPriority_185,                                     // ProfileInfo::cProfileID_185
    ProfileInfo::cDrawPriority_186,                                     // ProfileInfo::cProfileID_186
    ProfileInfo::cDrawPriority_187,                                     // ProfileInfo::cProfileID_187
    ProfileInfo::cDrawPriority_188,                                     // ProfileInfo::cProfileID_188
    ProfileInfo::cDrawPriority_189,                                     // ProfileInfo::cProfileID_189
    ProfileInfo::cDrawPriority_18A,                                     // ProfileInfo::cProfileID_18A
    ProfileInfo::cDrawPriority_ActorCoin,                               // ProfileInfo::cProfileID_ActorCoin
    ProfileInfo::cDrawPriority_18C,                                     // ProfileInfo::cProfileID_18C
    ProfileInfo::cDrawPriority_18D,                                     // ProfileInfo::cProfileID_18D
    ProfileInfo::cDrawPriority_18E,                                     // ProfileInfo::cProfileID_18E
    ProfileInfo::cDrawPriority_18F,                                     // ProfileInfo::cProfileID_18F
    ProfileInfo::cDrawPriority_190,                                     // ProfileInfo::cProfileID_190
    ProfileInfo::cDrawPriority_191,                                     // ProfileInfo::cProfileID_191
    ProfileInfo::cDrawPriority_192,                                     // ProfileInfo::cProfileID_192
    ProfileInfo::cDrawPriority_193,                                     // ProfileInfo::cProfileID_193
    ProfileInfo::cDrawPriority_194,                                     // ProfileInfo::cProfileID_194
    ProfileInfo::cDrawPriority_195,                                     // ProfileInfo::cProfileID_195
    ProfileInfo::cDrawPriority_196,                                     // ProfileInfo::cProfileID_196
    ProfileInfo::cDrawPriority_197,                                     // ProfileInfo::cProfileID_197
    ProfileInfo::cDrawPriority_198,                                     // ProfileInfo::cProfileID_198
    ProfileInfo::cDrawPriority_199,                                     // ProfileInfo::cProfileID_199
    ProfileInfo::cDrawPriority_19A,                                     // ProfileInfo::cProfileID_19A
    ProfileInfo::cDrawPriority_19B,                                     // ProfileInfo::cProfileID_19B
    ProfileInfo::cDrawPriority_19C,                                     // ProfileInfo::cProfileID_19C
    ProfileInfo::cDrawPriority_19D,                                     // ProfileInfo::cProfileID_19D
    ProfileInfo::cDrawPriority_19E,                                     // ProfileInfo::cProfileID_19E
    ProfileInfo::cDrawPriority_19F,                                     // ProfileInfo::cProfileID_19F
    ProfileInfo::cDrawPriority_1A0,                                     // ProfileInfo::cProfileID_1A0
    ProfileInfo::cDrawPriority_1A1,                                     // ProfileInfo::cProfileID_1A1
    ProfileInfo::cDrawPriority_1A2,                                     // ProfileInfo::cProfileID_1A2
    ProfileInfo::cDrawPriority_1A3,                                     // ProfileInfo::cProfileID_1A3
    ProfileInfo::cDrawPriority_1A4,                                     // ProfileInfo::cProfileID_1A4
    ProfileInfo::cDrawPriority_1A5,                                     // ProfileInfo::cProfileID_1A5
    ProfileInfo::cDrawPriority_1A6,                                     // ProfileInfo::cProfileID_1A6
    ProfileInfo::cDrawPriority_1A7,                                     // ProfileInfo::cProfileID_1A7
    ProfileInfo::cDrawPriority_1A8,                                     // ProfileInfo::cProfileID_1A8
    ProfileInfo::cDrawPriority_BlueCoin,                                // ProfileInfo::cProfileID_BlueCoin
    ProfileInfo::cDrawPriority_1AA,                                     // ProfileInfo::cProfileID_1AA
    ProfileInfo::cDrawPriority_1AB,                                     // ProfileInfo::cProfileID_1AB
    ProfileInfo::cDrawPriority_1AC,                                     // ProfileInfo::cProfileID_1AC
    ProfileInfo::cDrawPriority_1AD,                                     // ProfileInfo::cProfileID_1AD
    ProfileInfo::cDrawPriority_1AE,                                     // ProfileInfo::cProfileID_1AE
    ProfileInfo::cDrawPriority_1AF,                                     // ProfileInfo::cProfileID_1AF
    ProfileInfo::cDrawPriority_1B0,                                     // ProfileInfo::cProfileID_1B0
    ProfileInfo::cDrawPriority_1B1,                                     // ProfileInfo::cProfileID_1B1
    ProfileInfo::cDrawPriority_1B2,                                     // ProfileInfo::cProfileID_1B2
    ProfileInfo::cDrawPriority_1B3,                                     // ProfileInfo::cProfileID_1B3
    ProfileInfo::cDrawPriority_1B4,                                     // ProfileInfo::cProfileID_1B4
    ProfileInfo::cDrawPriority_1B5,                                     // ProfileInfo::cProfileID_1B5
    ProfileInfo::cDrawPriority_CoinmakiCoin,                            // ProfileInfo::cProfileID_CoinmakiCoin
    ProfileInfo::cDrawPriority_1B7,                                     // ProfileInfo::cProfileID_1B7
    ProfileInfo::cDrawPriority_1B8,                                     // ProfileInfo::cProfileID_1B8
    ProfileInfo::cDrawPriority_1B9,                                     // ProfileInfo::cProfileID_1B9
    ProfileInfo::cDrawPriority_Yoshi,                                   // ProfileInfo::cProfileID_Yoshi
    ProfileInfo::cDrawPriority_TottenPlayer,                            // ProfileInfo::cProfileID_TottenPlayer
    ProfileInfo::cDrawPriority_PlayerObject,                            // ProfileInfo::cProfileID_PlayerObject
    ProfileInfo::cDrawPriority_1BD,                                     // ProfileInfo::cProfileID_1BD
    ProfileInfo::cDrawPriority_1BE,                                     // ProfileInfo::cProfileID_1BE
    ProfileInfo::cDrawPriority_1BF,                                     // ProfileInfo::cProfileID_1BF
    ProfileInfo::cDrawPriority_1C0,                                     // ProfileInfo::cProfileID_1C0
    ProfileInfo::cDrawPriority_1C1,                                     // ProfileInfo::cProfileID_1C1
    ProfileInfo::cDrawPriority_1C2,                                     // ProfileInfo::cProfileID_1C2
    ProfileInfo::cDrawPriority_1C3,                                     // ProfileInfo::cProfileID_1C3
    ProfileInfo::cDrawPriority_1C4,                                     // ProfileInfo::cProfileID_1C4
    ProfileInfo::cDrawPriority_SlotYoshiChibi,                          // ProfileInfo::cProfileID_SlotYoshiChibi
    ProfileInfo::cDrawPriority_1C6,                                     // ProfileInfo::cProfileID_1C6
    ProfileInfo::cDrawPriority_1C7,                                     // ProfileInfo::cProfileID_1C7
    ProfileInfo::cDrawPriority_1C8,                                     // ProfileInfo::cProfileID_1C8
    ProfileInfo::cDrawPriority_1C9,                                     // ProfileInfo::cProfileID_1C9
    ProfileInfo::cDrawPriority_1CA,                                     // ProfileInfo::cProfileID_1CA
    ProfileInfo::cDrawPriority_1CB,                                     // ProfileInfo::cProfileID_1CB
    ProfileInfo::cDrawPriority_1CC,                                     // ProfileInfo::cProfileID_1CC
    ProfileInfo::cDrawPriority_1CD,                                     // ProfileInfo::cProfileID_1CD
    ProfileInfo::cDrawPriority_1CE,                                     // ProfileInfo::cProfileID_1CE
    ProfileInfo::cDrawPriority_QuestPrizeItem,                          // ProfileInfo::cProfileID_QuestPrizeItem
    ProfileInfo::cDrawPriority_1D0,                                     // ProfileInfo::cProfileID_1D0
    ProfileInfo::cDrawPriority_1D1,                                     // ProfileInfo::cProfileID_1D1
    ProfileInfo::cDrawPriority_1D2,                                     // ProfileInfo::cProfileID_1D2
    ProfileInfo::cDrawPriority_1D3,                                     // ProfileInfo::cProfileID_1D3
    ProfileInfo::cDrawPriority_1D4,                                     // ProfileInfo::cProfileID_1D4
    ProfileInfo::cDrawPriority_1D5,                                     // ProfileInfo::cProfileID_1D5
    ProfileInfo::cDrawPriority_1D6,                                     // ProfileInfo::cProfileID_1D6
    ProfileInfo::cDrawPriority_1D7,                                     // ProfileInfo::cProfileID_1D7
    ProfileInfo::cDrawPriority_1D8,                                     // ProfileInfo::cProfileID_1D8
    ProfileInfo::cDrawPriority_1D9,                                     // ProfileInfo::cProfileID_1D9
    ProfileInfo::cDrawPriority_IceBall,                                 // ProfileInfo::cProfileID_IceBall
    ProfileInfo::cDrawPriority_IceBallPakkun,                           // ProfileInfo::cProfileID_IceBallPakkun
    ProfileInfo::cDrawPriority_FireBallPlayer,                          // ProfileInfo::cProfileID_FireBallPlayer
    ProfileInfo::cDrawPriority_FireBallPakkun,                          // ProfileInfo::cProfileID_FireBallPakkun
    ProfileInfo::cDrawPriority_YoshiFire,                               // ProfileInfo::cProfileID_YoshiFire
    ProfileInfo::cDrawPriority_1DF,                                     // ProfileInfo::cProfileID_1DF
    ProfileInfo::cDrawPriority_1E0,                                     // ProfileInfo::cProfileID_1E0
    ProfileInfo::cDrawPriority_1E1,                                     // ProfileInfo::cProfileID_1E1
    ProfileInfo::cDrawPriority_1E2,                                     // ProfileInfo::cProfileID_1E2
    ProfileInfo::cDrawPriority_1E3,                                     // ProfileInfo::cProfileID_1E3
    ProfileInfo::cDrawPriority_1E4,                                     // ProfileInfo::cProfileID_1E4
    ProfileInfo::cDrawPriority_1E5,                                     // ProfileInfo::cProfileID_1E5
    ProfileInfo::cDrawPriority_1E6,                                     // ProfileInfo::cProfileID_1E6
    ProfileInfo::cDrawPriority_1E7,                                     // ProfileInfo::cProfileID_1E7
    ProfileInfo::cDrawPriority_1E8,                                     // ProfileInfo::cProfileID_1E8
    ProfileInfo::cDrawPriority_1E9,                                     // ProfileInfo::cProfileID_1E9
    ProfileInfo::cDrawPriority_1EA,                                     // ProfileInfo::cProfileID_1EA
    ProfileInfo::cDrawPriority_1EB,                                     // ProfileInfo::cProfileID_1EB
    ProfileInfo::cDrawPriority_1EC,                                     // ProfileInfo::cProfileID_1EC
    ProfileInfo::cDrawPriority_1ED,                                     // ProfileInfo::cProfileID_1ED
    ProfileInfo::cDrawPriority_1EE,                                     // ProfileInfo::cProfileID_1EE
    ProfileInfo::cDrawPriority_1EF,                                     // ProfileInfo::cProfileID_1EF
    ProfileInfo::cDrawPriority_1F0,                                     // ProfileInfo::cProfileID_1F0
    ProfileInfo::cDrawPriority_1F1,                                     // ProfileInfo::cProfileID_1F1
    ProfileInfo::cDrawPriority_1F2,                                     // ProfileInfo::cProfileID_1F2
    ProfileInfo::cDrawPriority_1F3,                                     // ProfileInfo::cProfileID_1F3
    ProfileInfo::cDrawPriority_1F4,                                     // ProfileInfo::cProfileID_1F4
    ProfileInfo::cDrawPriority_1F5,                                     // ProfileInfo::cProfileID_1F5
    ProfileInfo::cDrawPriority_1F6,                                     // ProfileInfo::cProfileID_1F6
    ProfileInfo::cDrawPriority_1F7,                                     // ProfileInfo::cProfileID_1F7
    ProfileInfo::cDrawPriority_1F8,                                     // ProfileInfo::cProfileID_1F8
    ProfileInfo::cDrawPriority_1F9,                                     // ProfileInfo::cProfileID_1F9
    ProfileInfo::cDrawPriority_1FA,                                     // ProfileInfo::cProfileID_1FA
    ProfileInfo::cDrawPriority_1FB,                                     // ProfileInfo::cProfileID_1FB
    ProfileInfo::cDrawPriority_1FC,                                     // ProfileInfo::cProfileID_1FC
    ProfileInfo::cDrawPriority_1FD,                                     // ProfileInfo::cProfileID_1FD
    ProfileInfo::cDrawPriority_1FE,                                     // ProfileInfo::cProfileID_1FE
    ProfileInfo::cDrawPriority_1FF,                                     // ProfileInfo::cProfileID_1FF
    ProfileInfo::cDrawPriority_Nokonoko,                                // ProfileInfo::cProfileID_Nokonoko
    ProfileInfo::cDrawPriority_201,                                     // ProfileInfo::cProfileID_201
    ProfileInfo::cDrawPriority_202,                                     // ProfileInfo::cProfileID_202
    ProfileInfo::cDrawPriority_203,                                     // ProfileInfo::cProfileID_203
    ProfileInfo::cDrawPriority_204,                                     // ProfileInfo::cProfileID_204
    ProfileInfo::cDrawPriority_205,                                     // ProfileInfo::cProfileID_205
    ProfileInfo::cDrawPriority_206,                                     // ProfileInfo::cProfileID_206
    ProfileInfo::cDrawPriority_207,                                     // ProfileInfo::cProfileID_207
    ProfileInfo::cDrawPriority_208,                                     // ProfileInfo::cProfileID_208
    ProfileInfo::cDrawPriority_209,                                     // ProfileInfo::cProfileID_209
    ProfileInfo::cDrawPriority_20A,                                     // ProfileInfo::cProfileID_20A
    ProfileInfo::cDrawPriority_20B,                                     // ProfileInfo::cProfileID_20B
    ProfileInfo::cDrawPriority_MechaKoopa,                              // ProfileInfo::cProfileID_MechaKoopa
    ProfileInfo::cDrawPriority_20D,                                     // ProfileInfo::cProfileID_20D
    ProfileInfo::cDrawPriority_20E,                                     // ProfileInfo::cProfileID_20E
    ProfileInfo::cDrawPriority_20F,                                     // ProfileInfo::cProfileID_20F
    ProfileInfo::cDrawPriority_210,                                     // ProfileInfo::cProfileID_210
    ProfileInfo::cDrawPriority_211,                                     // ProfileInfo::cProfileID_211
    ProfileInfo::cDrawPriority_212,                                     // ProfileInfo::cProfileID_212
    ProfileInfo::cDrawPriority_213,                                     // ProfileInfo::cProfileID_213
    ProfileInfo::cDrawPriority_214,                                     // ProfileInfo::cProfileID_214
    ProfileInfo::cDrawPriority_215,                                     // ProfileInfo::cProfileID_215
    ProfileInfo::cDrawPriority_216,                                     // ProfileInfo::cProfileID_216
    ProfileInfo::cDrawPriority_217,                                     // ProfileInfo::cProfileID_217
    ProfileInfo::cDrawPriority_218,                                     // ProfileInfo::cProfileID_218
    ProfileInfo::cDrawPriority_219,                                     // ProfileInfo::cProfileID_219
    ProfileInfo::cDrawPriority_21A,                                     // ProfileInfo::cProfileID_21A
    ProfileInfo::cDrawPriority_21B,                                     // ProfileInfo::cProfileID_21B
    ProfileInfo::cDrawPriority_21C,                                     // ProfileInfo::cProfileID_21C
    ProfileInfo::cDrawPriority_21D,                                     // ProfileInfo::cProfileID_21D
    ProfileInfo::cDrawPriority_21E,                                     // ProfileInfo::cProfileID_21E
    ProfileInfo::cDrawPriority_21F,                                     // ProfileInfo::cProfileID_21F
    ProfileInfo::cDrawPriority_220,                                     // ProfileInfo::cProfileID_220
    ProfileInfo::cDrawPriority_221,                                     // ProfileInfo::cProfileID_221
    ProfileInfo::cDrawPriority_222,                                     // ProfileInfo::cProfileID_222
    ProfileInfo::cDrawPriority_223,                                     // ProfileInfo::cProfileID_223
    ProfileInfo::cDrawPriority_224,                                     // ProfileInfo::cProfileID_224
    ProfileInfo::cDrawPriority_225,                                     // ProfileInfo::cProfileID_225
    ProfileInfo::cDrawPriority_226,                                     // ProfileInfo::cProfileID_226
    ProfileInfo::cDrawPriority_227,                                     // ProfileInfo::cProfileID_227
    ProfileInfo::cDrawPriority_228,                                     // ProfileInfo::cProfileID_228
    ProfileInfo::cDrawPriority_229,                                     // ProfileInfo::cProfileID_229
    ProfileInfo::cDrawPriority_22A,                                     // ProfileInfo::cProfileID_22A
    ProfileInfo::cDrawPriority_22B,                                     // ProfileInfo::cProfileID_22B
    ProfileInfo::cDrawPriority_22C,                                     // ProfileInfo::cProfileID_22C
    ProfileInfo::cDrawPriority_22D,                                     // ProfileInfo::cProfileID_22D
    ProfileInfo::cDrawPriority_FireBallKeronpa,                         // ProfileInfo::cProfileID_FireBallKeronpa
    ProfileInfo::cDrawPriority_FireBallKeronpaRDash,                    // ProfileInfo::cProfileID_FireBallKeronpaRDash
    ProfileInfo::cDrawPriority_230,                                     // ProfileInfo::cProfileID_230
    ProfileInfo::cDrawPriority_FireSnake,                               // ProfileInfo::cProfileID_FireSnake
    ProfileInfo::cDrawPriority_232,                                     // ProfileInfo::cProfileID_232
    ProfileInfo::cDrawPriority_233,                                     // ProfileInfo::cProfileID_233
    ProfileInfo::cDrawPriority_234,                                     // ProfileInfo::cProfileID_234
    ProfileInfo::cDrawPriority_235,                                     // ProfileInfo::cProfileID_235
    ProfileInfo::cDrawPriority_236,                                     // ProfileInfo::cProfileID_236
    ProfileInfo::cDrawPriority_237,                                     // ProfileInfo::cProfileID_237
    ProfileInfo::cDrawPriority_238,                                     // ProfileInfo::cProfileID_238
    ProfileInfo::cDrawPriority_239,                                     // ProfileInfo::cProfileID_239
    ProfileInfo::cDrawPriority_23A,                                     // ProfileInfo::cProfileID_23A
    ProfileInfo::cDrawPriority_23B,                                     // ProfileInfo::cProfileID_23B
    ProfileInfo::cDrawPriority_23C,                                     // ProfileInfo::cProfileID_23C
    ProfileInfo::cDrawPriority_23D,                                     // ProfileInfo::cProfileID_23D
    ProfileInfo::cDrawPriority_Kazandan,                                // ProfileInfo::cProfileID_Kazandan
    ProfileInfo::cDrawPriority_23F,                                     // ProfileInfo::cProfileID_23F
    ProfileInfo::cDrawPriority_240,                                     // ProfileInfo::cProfileID_240
    ProfileInfo::cDrawPriority_241,                                     // ProfileInfo::cProfileID_241
    ProfileInfo::cDrawPriority_242,                                     // ProfileInfo::cProfileID_242
    ProfileInfo::cDrawPriority_243,                                     // ProfileInfo::cProfileID_243
    ProfileInfo::cDrawPriority_244,                                     // ProfileInfo::cProfileID_244
    ProfileInfo::cDrawPriority_245,                                     // ProfileInfo::cProfileID_245
    ProfileInfo::cDrawPriority_246,                                     // ProfileInfo::cProfileID_246
    ProfileInfo::cDrawPriority_247,                                     // ProfileInfo::cProfileID_247
    ProfileInfo::cDrawPriority_248,                                     // ProfileInfo::cProfileID_248
    ProfileInfo::cDrawPriority_249,                                     // ProfileInfo::cProfileID_249
    ProfileInfo::cDrawPriority_24A,                                     // ProfileInfo::cProfileID_24A
    ProfileInfo::cDrawPriority_BgCenter,                                // ProfileInfo::cProfileID_BgCenter
    ProfileInfo::cDrawPriority_24C,                                     // ProfileInfo::cProfileID_24C
    ProfileInfo::cDrawPriority_24D,                                     // ProfileInfo::cProfileID_24D
    ProfileInfo::cDrawPriority_24E,                                     // ProfileInfo::cProfileID_24E
    ProfileInfo::cDrawPriority_Kinoko,                                  // ProfileInfo::cProfileID_Kinoko
    ProfileInfo::cDrawPriority_FireFlower,                              // ProfileInfo::cProfileID_FireFlower
    ProfileInfo::cDrawPriority_MameKinoko,                              // ProfileInfo::cProfileID_MameKinoko
    ProfileInfo::cDrawPriority_IceFlower,                               // ProfileInfo::cProfileID_IceFlower
    ProfileInfo::cDrawPriority_Propeller,                               // ProfileInfo::cProfileID_Propeller
    ProfileInfo::cDrawPriority_Penguin,                                 // ProfileInfo::cProfileID_Penguin
    ProfileInfo::cDrawPriority_OneUpKinoko,                             // ProfileInfo::cProfileID_OneUpKinoko
    ProfileInfo::cDrawPriority_Musasabi,                                // ProfileInfo::cProfileID_Musasabi
    ProfileInfo::cDrawPriority_SuperMoon,                               // ProfileInfo::cProfileID_SuperMoon
    ProfileInfo::cDrawPriority_TitleDemoItem,                           // ProfileInfo::cProfileID_TitleDemoItem
    ProfileInfo::cDrawPriority_259,                                     // ProfileInfo::cProfileID_259
    ProfileInfo::cDrawPriority_25A,                                     // ProfileInfo::cProfileID_25A
    ProfileInfo::cDrawPriority_25B,                                     // ProfileInfo::cProfileID_25B
    ProfileInfo::cDrawPriority_25C,                                     // ProfileInfo::cProfileID_25C
    ProfileInfo::cDrawPriority_25D,                                     // ProfileInfo::cProfileID_25D
    ProfileInfo::cDrawPriority_25E,                                     // ProfileInfo::cProfileID_25E
    ProfileInfo::cDrawPriority_25F,                                     // ProfileInfo::cProfileID_25F
    ProfileInfo::cDrawPriority_260,                                     // ProfileInfo::cProfileID_260
    ProfileInfo::cDrawPriority_261,                                     // ProfileInfo::cProfileID_261
    ProfileInfo::cDrawPriority_262,                                     // ProfileInfo::cProfileID_262
    ProfileInfo::cDrawPriority_263,                                     // ProfileInfo::cProfileID_263
    ProfileInfo::cDrawPriority_264,                                     // ProfileInfo::cProfileID_264
    ProfileInfo::cDrawPriority_265,                                     // ProfileInfo::cProfileID_265
    ProfileInfo::cDrawPriority_266,                                     // ProfileInfo::cProfileID_266
    ProfileInfo::cDrawPriority_267,                                     // ProfileInfo::cProfileID_267
    ProfileInfo::cDrawPriority_268,                                     // ProfileInfo::cProfileID_268
    ProfileInfo::cDrawPriority_Spanner,                                 // ProfileInfo::cProfileID_Spanner
    ProfileInfo::cDrawPriority_26A,                                     // ProfileInfo::cProfileID_26A
    ProfileInfo::cDrawPriority_26B,                                     // ProfileInfo::cProfileID_26B
    ProfileInfo::cDrawPriority_26C,                                     // ProfileInfo::cProfileID_26C
    ProfileInfo::cDrawPriority_26D,                                     // ProfileInfo::cProfileID_26D
    ProfileInfo::cDrawPriority_26E,                                     // ProfileInfo::cProfileID_26E
    ProfileInfo::cDrawPriority_26F,                                     // ProfileInfo::cProfileID_26F
    ProfileInfo::cDrawPriority_270,                                     // ProfileInfo::cProfileID_270
    ProfileInfo::cDrawPriority_271,                                     // ProfileInfo::cProfileID_271
    ProfileInfo::cDrawPriority_272,                                     // ProfileInfo::cProfileID_272
    ProfileInfo::cDrawPriority_273,                                     // ProfileInfo::cProfileID_273
    ProfileInfo::cDrawPriority_274,                                     // ProfileInfo::cProfileID_274
    ProfileInfo::cDrawPriority_275,                                     // ProfileInfo::cProfileID_275
    ProfileInfo::cDrawPriority_SearchKiller,                            // ProfileInfo::cProfileID_SearchKiller
    ProfileInfo::cDrawPriority_277,                                     // ProfileInfo::cProfileID_277
    ProfileInfo::cDrawPriority_278,                                     // ProfileInfo::cProfileID_278
    ProfileInfo::cDrawPriority_279,                                     // ProfileInfo::cProfileID_279
    ProfileInfo::cDrawPriority_WakiSearchMagKiller,                     // ProfileInfo::cProfileID_WakiSearchMagKiller
    ProfileInfo::cDrawPriority_27B,                                     // ProfileInfo::cProfileID_27B
    ProfileInfo::cDrawPriority_27C,                                     // ProfileInfo::cProfileID_27C
    ProfileInfo::cDrawPriority_27D,                                     // ProfileInfo::cProfileID_27D
    ProfileInfo::cDrawPriority_27E,                                     // ProfileInfo::cProfileID_27E
    ProfileInfo::cDrawPriority_27F,                                     // ProfileInfo::cProfileID_27F
    ProfileInfo::cDrawPriority_GabonRock,                               // ProfileInfo::cProfileID_GabonRock
    ProfileInfo::cDrawPriority_281,                                     // ProfileInfo::cProfileID_281
    ProfileInfo::cDrawPriority_282,                                     // ProfileInfo::cProfileID_282
    ProfileInfo::cDrawPriority_RockGabonRock,                           // ProfileInfo::cProfileID_RockGabonRock
    ProfileInfo::cDrawPriority_284,                                     // ProfileInfo::cProfileID_284
    ProfileInfo::cDrawPriority_SeichanSnowBall,                         // ProfileInfo::cProfileID_SeichanSnowBall
    ProfileInfo::cDrawPriority_286,                                     // ProfileInfo::cProfileID_286
    ProfileInfo::cDrawPriority_287,                                     // ProfileInfo::cProfileID_287
    ProfileInfo::cDrawPriority_288,                                     // ProfileInfo::cProfileID_288
    ProfileInfo::cDrawPriority_289,                                     // ProfileInfo::cProfileID_289
    ProfileInfo::cDrawPriority_Woochan,                                 // ProfileInfo::cProfileID_Woochan
    ProfileInfo::cDrawPriority_28B,                                     // ProfileInfo::cProfileID_28B
    ProfileInfo::cDrawPriority_28C,                                     // ProfileInfo::cProfileID_28C
    ProfileInfo::cDrawPriority_28D,                                     // ProfileInfo::cProfileID_28D
    ProfileInfo::cDrawPriority_Bubble,                                  // ProfileInfo::cProfileID_Bubble
    ProfileInfo::cDrawPriority_BubbleSync,                              // ProfileInfo::cProfileID_BubbleSync
    ProfileInfo::cDrawPriority_BubbleRDash,                             // ProfileInfo::cProfileID_BubbleRDash
    ProfileInfo::cDrawPriority_BubbleSyncRDash,                         // ProfileInfo::cProfileID_BubbleSyncRDash
    ProfileInfo::cDrawPriority_292,                                     // ProfileInfo::cProfileID_292
    ProfileInfo::cDrawPriority_293,                                     // ProfileInfo::cProfileID_293
    ProfileInfo::cDrawPriority_294,                                     // ProfileInfo::cProfileID_294
    ProfileInfo::cDrawPriority_295,                                     // ProfileInfo::cProfileID_295
    ProfileInfo::cDrawPriority_296,                                     // ProfileInfo::cProfileID_296
    ProfileInfo::cDrawPriority_297,                                     // ProfileInfo::cProfileID_297
    ProfileInfo::cDrawPriority_298,                                     // ProfileInfo::cProfileID_298
    ProfileInfo::cDrawPriority_299,                                     // ProfileInfo::cProfileID_299
    ProfileInfo::cDrawPriority_29A,                                     // ProfileInfo::cProfileID_29A
    ProfileInfo::cDrawPriority_29B,                                     // ProfileInfo::cProfileID_29B
    ProfileInfo::cDrawPriority_29C,                                     // ProfileInfo::cProfileID_29C
    ProfileInfo::cDrawPriority_29D,                                     // ProfileInfo::cProfileID_29D
    ProfileInfo::cDrawPriority_29E,                                     // ProfileInfo::cProfileID_29E
    ProfileInfo::cDrawPriority_29F,                                     // ProfileInfo::cProfileID_29F
    ProfileInfo::cDrawPriority_2A0,                                     // ProfileInfo::cProfileID_2A0
    ProfileInfo::cDrawPriority_2A1,                                     // ProfileInfo::cProfileID_2A1
    ProfileInfo::cDrawPriority_2A2,                                     // ProfileInfo::cProfileID_2A2
    ProfileInfo::cDrawPriority_2A3,                                     // ProfileInfo::cProfileID_2A3
    ProfileInfo::cDrawPriority_2A4,                                     // ProfileInfo::cProfileID_2A4
    ProfileInfo::cDrawPriority_2A5,                                     // ProfileInfo::cProfileID_2A5
    ProfileInfo::cDrawPriority_Bun,                                     // ProfileInfo::cProfileID_Bun
    ProfileInfo::cDrawPriority_BunW2,                                   // ProfileInfo::cProfileID_BunW2
    ProfileInfo::cDrawPriority_BunW3,                                   // ProfileInfo::cProfileID_BunW3
    ProfileInfo::cDrawPriority_BunW4,                                   // ProfileInfo::cProfileID_BunW4
    ProfileInfo::cDrawPriority_BunW5,                                   // ProfileInfo::cProfileID_BunW5
    ProfileInfo::cDrawPriority_BunW6,                                   // ProfileInfo::cProfileID_BunW6
    ProfileInfo::cDrawPriority_BunDemo,                                 // ProfileInfo::cProfileID_BunDemo
    ProfileInfo::cDrawPriority_KokoopaDemo,                             // ProfileInfo::cProfileID_KokoopaDemo
    ProfileInfo::cDrawPriority_KoopaJrDemo,                             // ProfileInfo::cProfileID_KoopaJrDemo
    ProfileInfo::cDrawPriority_KameckDemo,                              // ProfileInfo::cProfileID_KameckDemo
    ProfileInfo::cDrawPriority_BossKKDemo,                              // ProfileInfo::cProfileID_BossKKDemo
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJrDemo,             // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrDemo
    ProfileInfo::cDrawPriority_KoopaDemo,                               // ProfileInfo::cProfileID_KoopaDemo
    ProfileInfo::cDrawPriority_FinalKoopaDemo,                          // ProfileInfo::cProfileID_FinalKoopaDemo
    ProfileInfo::cDrawPriority_PeachDemo,                               // ProfileInfo::cProfileID_PeachDemo
    ProfileInfo::cDrawPriority_Larry,                                   // ProfileInfo::cProfileID_Larry
    ProfileInfo::cDrawPriority_KokoopaSearchFire,                       // ProfileInfo::cProfileID_KokoopaSearchFire
    ProfileInfo::cDrawPriority_Lemmy,                                   // ProfileInfo::cProfileID_Lemmy
    ProfileInfo::cDrawPriority_Morton,                                  // ProfileInfo::cProfileID_Morton
    ProfileInfo::cDrawPriority_MortonSanbo,                             // ProfileInfo::cProfileID_MortonSanbo
    ProfileInfo::cDrawPriority_MortonSanboParts,                        // ProfileInfo::cProfileID_MortonSanboParts
    ProfileInfo::cDrawPriority_Wendy,                                   // ProfileInfo::cProfileID_Wendy
    ProfileInfo::cDrawPriority_WendyRing,                               // ProfileInfo::cProfileID_WendyRing
    ProfileInfo::cDrawPriority_Ludwig,                                  // ProfileInfo::cProfileID_Ludwig
    ProfileInfo::cDrawPriority_LudwigAlterEgo,                          // ProfileInfo::cProfileID_LudwigAlterEgo
    ProfileInfo::cDrawPriority_Iggy,                                    // ProfileInfo::cProfileID_Iggy
    ProfileInfo::cDrawPriority_IggyMagic,                               // ProfileInfo::cProfileID_IggyMagic
    ProfileInfo::cDrawPriority_Woogan,                                  // ProfileInfo::cProfileID_Woogan
    ProfileInfo::cDrawPriority_Roy,                                     // ProfileInfo::cProfileID_Roy
    ProfileInfo::cDrawPriority_RoyLiftWaki,                             // ProfileInfo::cProfileID_RoyLiftWaki
    ProfileInfo::cDrawPriority_BossKK,                                  // ProfileInfo::cProfileID_BossKK
    ProfileInfo::cDrawPriority_BossKKThunder,                           // ProfileInfo::cProfileID_BossKKThunder
    ProfileInfo::cDrawPriority_Kameck,                                  // ProfileInfo::cProfileID_Kameck
    ProfileInfo::cDrawPriority_KameckIceConfig,                         // ProfileInfo::cProfileID_KameckIceConfig
    ProfileInfo::cDrawPriority_KameckWarpPos,                           // ProfileInfo::cProfileID_KameckWarpPos
    ProfileInfo::cDrawPriority_KameckMagic,                             // ProfileInfo::cProfileID_KameckMagic
    ProfileInfo::cDrawPriority_PeachFinalCastleKoopaJr,                 // ProfileInfo::cProfileID_PeachFinalCastleKoopaJr
    ProfileInfo::cDrawPriority_Koopa,                                   // ProfileInfo::cProfileID_Koopa
    ProfileInfo::cDrawPriority_KoopaFireWaki,                           // ProfileInfo::cProfileID_KoopaFireWaki
    ProfileInfo::cDrawPriority_KoopaFire,                               // ProfileInfo::cProfileID_KoopaFire
    ProfileInfo::cDrawPriority_DemoKoopaJrClown,                        // ProfileInfo::cProfileID_DemoKoopaJrClown
    ProfileInfo::cDrawPriority_DemoKoopaJr,                             // ProfileInfo::cProfileID_DemoKoopaJr
    ProfileInfo::cDrawPriority_BunDemoKameck,                           // ProfileInfo::cProfileID_BunDemoKameck
    ProfileInfo::cDrawPriority_KoopaDemoKameck,                         // ProfileInfo::cProfileID_KoopaDemoKameck
    ProfileInfo::cDrawPriority_BossKKDemoKameck,                        // ProfileInfo::cProfileID_BossKKDemoKameck
    ProfileInfo::cDrawPriority_BossKKDemoKK,                            // ProfileInfo::cProfileID_BossKKDemoKK
    ProfileInfo::cDrawPriority_FinalKoopaFire,                          // ProfileInfo::cProfileID_FinalKoopaFire
    ProfileInfo::cDrawPriority_FinalKoopaJr,                            // ProfileInfo::cProfileID_FinalKoopaJr
    ProfileInfo::cDrawPriority_FinalKoopaJrFire,                        // ProfileInfo::cProfileID_FinalKoopaJrFire
    ProfileInfo::cDrawPriority_FinalBomhei,                             // ProfileInfo::cProfileID_FinalBomhei
    ProfileInfo::cDrawPriority_KokoopaShipLemmy,                        // ProfileInfo::cProfileID_KokoopaShipLemmy
    ProfileInfo::cDrawPriority_KokoopaShipMorton,                       // ProfileInfo::cProfileID_KokoopaShipMorton
    ProfileInfo::cDrawPriority_KokoopaShipLarry,                        // ProfileInfo::cProfileID_KokoopaShipLarry
    ProfileInfo::cDrawPriority_KokoopaShipWendy,                        // ProfileInfo::cProfileID_KokoopaShipWendy
    ProfileInfo::cDrawPriority_KokoopaShipIggy,                         // ProfileInfo::cProfileID_KokoopaShipIggy
    ProfileInfo::cDrawPriority_KokoopaShipRoy,                          // ProfileInfo::cProfileID_KokoopaShipRoy
    ProfileInfo::cDrawPriority_KokoopaShipLudwig,                       // ProfileInfo::cProfileID_KokoopaShipLudwig
    ProfileInfo::cDrawPriority_Peach,                                   // ProfileInfo::cProfileID_Peach
    ProfileInfo::cDrawPriority_2E0,                                     // ProfileInfo::cProfileID_2E0
    ProfileInfo::cDrawPriority_FinalDVPeach,                            // ProfileInfo::cProfileID_FinalDVPeach
    ProfileInfo::cDrawPriority_FinalDVShutter,                          // ProfileInfo::cProfileID_FinalDVShutter
    ProfileInfo::cDrawPriority_2E3,                                     // ProfileInfo::cProfileID_2E3
    ProfileInfo::cDrawPriority_2E4,                                     // ProfileInfo::cProfileID_2E4
    ProfileInfo::cDrawPriority_2E5,                                     // ProfileInfo::cProfileID_2E5
    ProfileInfo::cDrawPriority_2E6,                                     // ProfileInfo::cProfileID_2E6
    ProfileInfo::cDrawPriority_2E7,                                     // ProfileInfo::cProfileID_2E7
    ProfileInfo::cDrawPriority_2E8,                                     // ProfileInfo::cProfileID_2E8
    ProfileInfo::cDrawPriority_2E9,                                     // ProfileInfo::cProfileID_2E9
    ProfileInfo::cDrawPriority_2EA,                                     // ProfileInfo::cProfileID_2EA
    ProfileInfo::cDrawPriority_2EB,                                     // ProfileInfo::cProfileID_2EB
    ProfileInfo::cDrawPriority_2EC,                                     // ProfileInfo::cProfileID_2EC
    ProfileInfo::cDrawPriority_2ED,                                     // ProfileInfo::cProfileID_2ED
    ProfileInfo::cDrawPriority_2EE,                                     // ProfileInfo::cProfileID_2EE
    ProfileInfo::cDrawPriority_2EF,                                     // ProfileInfo::cProfileID_2EF
    ProfileInfo::cDrawPriority_2F0,                                     // ProfileInfo::cProfileID_2F0
    ProfileInfo::cDrawPriority_2F1,                                     // ProfileInfo::cProfileID_2F1
    ProfileInfo::cDrawPriority_2F2,                                     // ProfileInfo::cProfileID_2F2
    ProfileInfo::cDrawPriority_2F3,                                     // ProfileInfo::cProfileID_2F3
    ProfileInfo::cDrawPriority_2F4,                                     // ProfileInfo::cProfileID_2F4
    ProfileInfo::cDrawPriority_2F5,                                     // ProfileInfo::cProfileID_2F5
    ProfileInfo::cDrawPriority_Hammer,                                  // ProfileInfo::cProfileID_Hammer
    ProfileInfo::cDrawPriority_2F7,                                     // ProfileInfo::cProfileID_2F7
    ProfileInfo::cDrawPriority_Boomerang,                               // ProfileInfo::cProfileID_Boomerang
    ProfileInfo::cDrawPriority_2F9,                                     // ProfileInfo::cProfileID_2F9
    ProfileInfo::cDrawPriority_FireBallBros,                            // ProfileInfo::cProfileID_FireBallBros
    ProfileInfo::cDrawPriority_2FB,                                     // ProfileInfo::cProfileID_2FB
    ProfileInfo::cDrawPriority_IceBallBros,                             // ProfileInfo::cProfileID_IceBallBros
    ProfileInfo::cDrawPriority_2FD,                                     // ProfileInfo::cProfileID_2FD
    ProfileInfo::cDrawPriority_MegaHammer,                              // ProfileInfo::cProfileID_MegaHammer
    ProfileInfo::cDrawPriority_2FF,                                     // ProfileInfo::cProfileID_2FF
    ProfileInfo::cDrawPriority_300,                                     // ProfileInfo::cProfileID_300
    ProfileInfo::cDrawPriority_301,                                     // ProfileInfo::cProfileID_301
    ProfileInfo::cDrawPriority_302,                                     // ProfileInfo::cProfileID_302
    ProfileInfo::cDrawPriority_303,                                     // ProfileInfo::cProfileID_303
    ProfileInfo::cDrawPriority_304,                                     // ProfileInfo::cProfileID_304
    ProfileInfo::cDrawPriority_305,                                     // ProfileInfo::cProfileID_305
    ProfileInfo::cDrawPriority_306,                                     // ProfileInfo::cProfileID_306
    ProfileInfo::cDrawPriority_307,                                     // ProfileInfo::cProfileID_307
    ProfileInfo::cDrawPriority_308,                                     // ProfileInfo::cProfileID_308
    ProfileInfo::cDrawPriority_309,                                     // ProfileInfo::cProfileID_309
    ProfileInfo::cDrawPriority_30A,                                     // ProfileInfo::cProfileID_30A
    ProfileInfo::cDrawPriority_30B,                                     // ProfileInfo::cProfileID_30B
    ProfileInfo::cDrawPriority_30C,                                     // ProfileInfo::cProfileID_30C
    ProfileInfo::cDrawPriority_30D,                                     // ProfileInfo::cProfileID_30D
    ProfileInfo::cDrawPriority_30E,                                     // ProfileInfo::cProfileID_30E
    ProfileInfo::cDrawPriority_30F,                                     // ProfileInfo::cProfileID_30F
    ProfileInfo::cDrawPriority_310,                                     // ProfileInfo::cProfileID_310
    ProfileInfo::cDrawPriority_311,                                     // ProfileInfo::cProfileID_311
    ProfileInfo::cDrawPriority_312,                                     // ProfileInfo::cProfileID_312
    ProfileInfo::cDrawPriority_313,                                     // ProfileInfo::cProfileID_313
    ProfileInfo::cDrawPriority_314,                                     // ProfileInfo::cProfileID_314
    ProfileInfo::cDrawPriority_315,                                     // ProfileInfo::cProfileID_315
    ProfileInfo::cDrawPriority_316,                                     // ProfileInfo::cProfileID_316
    ProfileInfo::cDrawPriority_317,                                     // ProfileInfo::cProfileID_317
    ProfileInfo::cDrawPriority_318,                                     // ProfileInfo::cProfileID_318
    ProfileInfo::cDrawPriority_319,                                     // ProfileInfo::cProfileID_319
    ProfileInfo::cDrawPriority_31A,                                     // ProfileInfo::cProfileID_31A
    ProfileInfo::cDrawPriority_31B,                                     // ProfileInfo::cProfileID_31B
    ProfileInfo::cDrawPriority_31C,                                     // ProfileInfo::cProfileID_31C
    ProfileInfo::cDrawPriority_31D,                                     // ProfileInfo::cProfileID_31D
    ProfileInfo::cDrawPriority_31E,                                     // ProfileInfo::cProfileID_31E
    ProfileInfo::cDrawPriority_31F,                                     // ProfileInfo::cProfileID_31F
    ProfileInfo::cDrawPriority_320,                                     // ProfileInfo::cProfileID_320
    ProfileInfo::cDrawPriority_321,                                     // ProfileInfo::cProfileID_321
    ProfileInfo::cDrawPriority_322,                                     // ProfileInfo::cProfileID_322
    ProfileInfo::cDrawPriority_323,                                     // ProfileInfo::cProfileID_323
    ProfileInfo::cDrawPriority_324,                                     // ProfileInfo::cProfileID_324
    ProfileInfo::cDrawPriority_325,                                     // ProfileInfo::cProfileID_325
    ProfileInfo::cDrawPriority_326,                                     // ProfileInfo::cProfileID_326
    ProfileInfo::cDrawPriority_327,                                     // ProfileInfo::cProfileID_327
    ProfileInfo::cDrawPriority_328,                                     // ProfileInfo::cProfileID_328
    ProfileInfo::cDrawPriority_BattleItem,                              // ProfileInfo::cProfileID_BattleItem
    ProfileInfo::cDrawPriority_32A,                                     // ProfileInfo::cProfileID_32A
    ProfileInfo::cDrawPriority_VsBattleItem,                            // ProfileInfo::cProfileID_VsBattleItem
    ProfileInfo::cDrawPriority_32C,                                     // ProfileInfo::cProfileID_32C
    ProfileInfo::cDrawPriority_32D,                                     // ProfileInfo::cProfileID_32D
    ProfileInfo::cDrawPriority_32E,                                     // ProfileInfo::cProfileID_32E
    ProfileInfo::cDrawPriority_32F,                                     // ProfileInfo::cProfileID_32F
    ProfileInfo::cDrawPriority_330,                                     // ProfileInfo::cProfileID_330
    ProfileInfo::cDrawPriority_331,                                     // ProfileInfo::cProfileID_331
    ProfileInfo::cDrawPriority_KoopaJrFire,                             // ProfileInfo::cProfileID_KoopaJrFire
    ProfileInfo::cDrawPriority_KoopaJrBall,                             // ProfileInfo::cProfileID_KoopaJrBall
    ProfileInfo::cDrawPriority_UnderwaterKoopaJr,                       // ProfileInfo::cProfileID_UnderwaterKoopaJr
    ProfileInfo::cDrawPriority_UnderwaterKoopaJrClown,                  // ProfileInfo::cProfileID_UnderwaterKoopaJrClown
    ProfileInfo::cDrawPriority_UnderwaterKoopaJrRetreatPos,             // ProfileInfo::cProfileID_UnderwaterKoopaJrRetreatPos
    ProfileInfo::cDrawPriority_BoxingKoopaJr,                           // ProfileInfo::cProfileID_BoxingKoopaJr
    ProfileInfo::cDrawPriority_BoxingKoopaJrPostBattleDemo,             // ProfileInfo::cProfileID_BoxingKoopaJrPostBattleDemo
    ProfileInfo::cDrawPriority_BoxingKoopaJrClownPostBattleDemo,        // ProfileInfo::cProfileID_BoxingKoopaJrClownPostBattleDemo
    ProfileInfo::cDrawPriority_MiniGamePanelItem,                       // ProfileInfo::cProfileID_MiniGamePanelItem
    ProfileInfo::cDrawPriority_SlotItem,                                // ProfileInfo::cProfileID_SlotItem
    ProfileInfo::cDrawPriority_CoinmakiCannon,                          // ProfileInfo::cProfileID_CoinmakiCannon
    ProfileInfo::cDrawPriority_CoinmakiItem,                            // ProfileInfo::cProfileID_CoinmakiItem
    ProfileInfo::cDrawPriority_MiniGameKinopio,                         // ProfileInfo::cProfileID_MiniGameKinopio
    ProfileInfo::cDrawPriority_33F,                                     // ProfileInfo::cProfileID_33F
    ProfileInfo::cDrawPriority_340,                                     // ProfileInfo::cProfileID_340
    ProfileInfo::cDrawPriority_341,                                     // ProfileInfo::cProfileID_341
    ProfileInfo::cDrawPriority_342,                                     // ProfileInfo::cProfileID_342
    ProfileInfo::cDrawPriority_343,                                     // ProfileInfo::cProfileID_343
    ProfileInfo::cDrawPriority_344,                                     // ProfileInfo::cProfileID_344
    ProfileInfo::cDrawPriority_345,                                     // ProfileInfo::cProfileID_345
    ProfileInfo::cDrawPriority_346,                                     // ProfileInfo::cProfileID_346
    ProfileInfo::cDrawPriority_347,                                     // ProfileInfo::cProfileID_347
    ProfileInfo::cDrawPriority_StaffCreditChibiYoshiABC,                // ProfileInfo::cProfileID_StaffCreditChibiYoshiABC
    ProfileInfo::cDrawPriority_StaffCreditChibiYoshiBalloon,            // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloon
    ProfileInfo::cDrawPriority_StaffCreditChibiYoshiBalloonCheer,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloonCheer
    ProfileInfo::cDrawPriority_StaffCreditChibiYoshiLight,              // ProfileInfo::cProfileID_StaffCreditChibiYoshiLight
    ProfileInfo::cDrawPriority_StaffCreditChibiYoshiLightCheer,         // ProfileInfo::cProfileID_StaffCreditChibiYoshiLightCheer
    ProfileInfo::cDrawPriority_StaffCreditSoapABC,                      // ProfileInfo::cProfileID_StaffCreditSoapABC
    ProfileInfo::cDrawPriority_StaffCreditSoapCoin,                     // ProfileInfo::cProfileID_StaffCreditSoapCoin
    ProfileInfo::cDrawPriority_StaffCreditTottenKun,                    // ProfileInfo::cProfileID_StaffCreditTottenKun
    ProfileInfo::cDrawPriority_350,                                     // ProfileInfo::cProfileID_350
    ProfileInfo::cDrawPriority_351,                                     // ProfileInfo::cProfileID_351
    ProfileInfo::cDrawPriority_352,                                     // ProfileInfo::cProfileID_352
    ProfileInfo::cDrawPriority_353,                                     // ProfileInfo::cProfileID_353
    ProfileInfo::cDrawPriority_RealizeFeverStar,                        // ProfileInfo::cProfileID_RealizeFeverStar
    ProfileInfo::cDrawPriority_Star,                                    // ProfileInfo::cProfileID_Star
    ProfileInfo::cDrawPriority_CourseSelectPlayer,                      // ProfileInfo::cProfileID_CourseSelectPlayer
    ProfileInfo::cDrawPriority_CourseSelectPlayer2PSub,                 // ProfileInfo::cProfileID_CourseSelectPlayer2PSub
    ProfileInfo::cDrawPriority_CourseSelectChibiYoshi,                  // ProfileInfo::cProfileID_CourseSelectChibiYoshi
    ProfileInfo::cDrawPriority_CourseSelectCamera,                      // ProfileInfo::cProfileID_CourseSelectCamera
    ProfileInfo::cDrawPriority_CourseSelectCastle,                      // ProfileInfo::cProfileID_CourseSelectCastle
    ProfileInfo::cDrawPriority_CourseSelectToride,                      // ProfileInfo::cProfileID_CourseSelectToride
    ProfileInfo::cDrawPriority_CourseSelectKinokoHouse1up,              // ProfileInfo::cProfileID_CourseSelectKinokoHouse1up
    ProfileInfo::cDrawPriority_CourseSelectKinokoHouseShuffle,          // ProfileInfo::cProfileID_CourseSelectKinokoHouseShuffle
    ProfileInfo::cDrawPriority_CourseSelectKinokoHouseSlot,             // ProfileInfo::cProfileID_CourseSelectKinokoHouseSlot
    ProfileInfo::cDrawPriority_CourseSelectPeachGates1st,               // ProfileInfo::cProfileID_CourseSelectPeachGates1st
    ProfileInfo::cDrawPriority_CourseSelectPeachGates2nd,               // ProfileInfo::cProfileID_CourseSelectPeachGates2nd
    ProfileInfo::cDrawPriority_CourseSelectCoursePoint,                 // ProfileInfo::cProfileID_CourseSelectCoursePoint
    ProfileInfo::cDrawPriority_CourseSelectWorldMoveDokan,              // ProfileInfo::cProfileID_CourseSelectWorldMoveDokan
    ProfileInfo::cDrawPriority_CourseSelectW8Cloud,                     // ProfileInfo::cProfileID_CourseSelectW8Cloud
    ProfileInfo::cDrawPriority_CourseSelectGhost,                       // ProfileInfo::cProfileID_CourseSelectGhost
    ProfileInfo::cDrawPriority_CourseSelectW2Bros,                      // ProfileInfo::cProfileID_CourseSelectW2Bros
    ProfileInfo::cDrawPriority_CourseSelectShipW1,                      // ProfileInfo::cProfileID_CourseSelectShipW1
    ProfileInfo::cDrawPriority_CourseSelectShipW2,                      // ProfileInfo::cProfileID_CourseSelectShipW2
    ProfileInfo::cDrawPriority_CourseSelectShipW3,                      // ProfileInfo::cProfileID_CourseSelectShipW3
    ProfileInfo::cDrawPriority_CourseSelectShipW4,                      // ProfileInfo::cProfileID_CourseSelectShipW4
    ProfileInfo::cDrawPriority_CourseSelectShipW5,                      // ProfileInfo::cProfileID_CourseSelectShipW5
    ProfileInfo::cDrawPriority_CourseSelectShipW6,                      // ProfileInfo::cProfileID_CourseSelectShipW6
    ProfileInfo::cDrawPriority_CourseSelectShipW7,                      // ProfileInfo::cProfileID_CourseSelectShipW7
    ProfileInfo::cDrawPriority_CourseSelectShipW8,                      // ProfileInfo::cProfileID_CourseSelectShipW8
    ProfileInfo::cDrawPriority_CourseSelectShipW8Broken,                // ProfileInfo::cProfileID_CourseSelectShipW8Broken
    ProfileInfo::cDrawPriority_CourseSelectSurrender,                   // ProfileInfo::cProfileID_CourseSelectSurrender
    ProfileInfo::cDrawPriority_CourseSelectSwitchA,                     // ProfileInfo::cProfileID_CourseSelectSwitchA
    ProfileInfo::cDrawPriority_CourseSelectSwitchB,                     // ProfileInfo::cProfileID_CourseSelectSwitchB
    ProfileInfo::cDrawPriority_CourseSelectTeresa,                      // ProfileInfo::cProfileID_CourseSelectTeresa
    ProfileInfo::cDrawPriority_CourseSelectOpeningKameck,               // ProfileInfo::cProfileID_CourseSelectOpeningKameck
    ProfileInfo::cDrawPriority_CourseSelectTorideBoss,                  // ProfileInfo::cProfileID_CourseSelectTorideBoss
    ProfileInfo::cDrawPriority_CourseSelectPakkun,                      // ProfileInfo::cProfileID_CourseSelectPakkun
    ProfileInfo::cDrawPriority_CourseSelectShadowFirstDemoKinopio,      // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoKinopio
    ProfileInfo::cDrawPriority_CourseSelectTobiPuku,                    // ProfileInfo::cProfileID_CourseSelectTobiPuku
    ProfileInfo::cDrawPriority_CourseSelectChorobon,                    // ProfileInfo::cProfileID_CourseSelectChorobon
    ProfileInfo::cDrawPriority_CourseSelectW7Item,                      // ProfileInfo::cProfileID_CourseSelectW7Item
    ProfileInfo::cDrawPriority_CourseSelectW5Teresa,                    // ProfileInfo::cProfileID_CourseSelectW5Teresa
    ProfileInfo::cDrawPriority_CourseSelectFlag,                        // ProfileInfo::cProfileID_CourseSelectFlag
    ProfileInfo::cDrawPriority_CourseSelectMusasabi,                    // ProfileInfo::cProfileID_CourseSelectMusasabi
    ProfileInfo::cDrawPriority_CourseSelectWPillar,                     // ProfileInfo::cProfileID_CourseSelectWPillar
    ProfileInfo::cDrawPriority_CourseSelectW7Bridge,                    // ProfileInfo::cProfileID_CourseSelectW7Bridge
    ProfileInfo::cDrawPriority_CourseSelectMiiBalloon,                  // ProfileInfo::cProfileID_CourseSelectMiiBalloon
    ProfileInfo::cDrawPriority_CourseSelectPenguin,                     // ProfileInfo::cProfileID_CourseSelectPenguin
    ProfileInfo::cDrawPriority_CourseSelectW4Item,                      // ProfileInfo::cProfileID_CourseSelectW4Item
    ProfileInfo::cDrawPriority_CourseSelectW2Kuribo,                    // ProfileInfo::cProfileID_CourseSelectW2Kuribo
    ProfileInfo::cDrawPriority_CourseSelectPakkunBig,                   // ProfileInfo::cProfileID_CourseSelectPakkunBig
    ProfileInfo::cDrawPriority_CourseSelectShadowKunIcon,               // ProfileInfo::cProfileID_CourseSelectShadowKunIcon
    ProfileInfo::cDrawPriority_CourseSelectDekaUnira,                   // ProfileInfo::cProfileID_CourseSelectDekaUnira
    ProfileInfo::cDrawPriority_CourseSelectTomb,                        // ProfileInfo::cProfileID_CourseSelectTomb
    ProfileInfo::cDrawPriority_CourseSelectShadowFirstDemoShadowKun,    // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoShadowKun
    ProfileInfo::cDrawPriority_CourseSelectKotsuCoaster,                // ProfileInfo::cProfileID_CourseSelectKotsuCoaster
    ProfileInfo::cDrawPriority_CourseSelectKoopaJr,                     // ProfileInfo::cProfileID_CourseSelectKoopaJr
    ProfileInfo::cDrawPriority_CourseSelectPeach,                       // ProfileInfo::cProfileID_CourseSelectPeach
    ProfileInfo::cDrawPriority_CourseSelectW1Item,                      // ProfileInfo::cProfileID_CourseSelectW1Item
    ProfileInfo::cDrawPriority_CourseSelectStarGate,                    // ProfileInfo::cProfileID_CourseSelectStarGate
    ProfileInfo::cDrawPriority_CourseSelectEventAssistant,              // ProfileInfo::cProfileID_CourseSelectEventAssistant
    ProfileInfo::cDrawPriority_38E,                                     // Profile 910
    ProfileInfo::cDrawPriority_38F,                                     // Profile 911
    ProfileInfo::cDrawPriority_390                                      // Profile 912
};

// -----------------------------------------  ResType ----------------------------------------- //

const s8 ProfileInfo::cResType[cProfileID_Max] = {
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_000
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_001
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_002
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_003
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_004
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_005
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_006
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_007
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_008
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_009
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00B
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00C
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_00F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_010
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_011
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_012
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_013
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_014
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_015
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_016
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_017
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MiniGameMgr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MiniGameMgrRDash
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_ShuffleBlockMgr
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_SlotMgr
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_CoinmakiMgr
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_01D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_01E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_01F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_020
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ShootingStar
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffRollMgr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffRollMgrRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_024
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_025
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_026
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_027
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_028
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_029
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_02A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_02B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_02C
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_02D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_02E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_02F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_030
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_031
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_032
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_033
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ElasticKinokoParent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FloorGyration
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_036
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_037
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_038
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_039
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_03A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_03B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PairObjChild
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_03D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_03E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_03F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_040
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_041
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_042
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_043
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_044
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_045
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_046
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_047
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_048
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_049
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_04A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_04B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_04C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KinokoLift
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KinokoLiftColor
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LiftZenStar
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_050
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_051
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_052
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_053
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_054
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_055
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_056
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_057
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_058
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_059
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BgActorYukaMario
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_05B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_05C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_05D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_05E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_05F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_060
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_061
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_062
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_063
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_064
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KillerHoudai
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StretchKillerHoudai
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MagnumKillerHoudai
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MagnumKillerHoudaiDown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SearchKillerHoudai
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SearchMagnumKillerHoudai
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MagnumKillerHoudaiRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MagnumKillerHoudaiDownRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDownRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_070
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_071
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_072
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_073
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_074
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_075
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_076
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_077
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_078
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Intermittent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_IntermittentPermanent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WaterIntermittent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WaterIntermittentPermanent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WaterIntermittentPermanentRD3_3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_07E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WaterIntermittentBossChild
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_YoganIntermittent
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_081
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_082
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_083
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_084
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_085
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ObjPipeDownNG
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_087
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_088
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_089
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_08F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_090
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_091
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_092
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_093
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_094
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_095
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_096
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_097
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_098
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_099
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_09F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0A9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0AF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0B7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LineSpinLift
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LineSpinLiftParentRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LineSpinLiftChildRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0BB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0BC
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_0BD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0BE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0BF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SnakeBlock
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0C9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0CF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FloorHoleDokan
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0D9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0DF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Burner
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0E9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0EA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0EB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0EC
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_PlyIce
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_TarzanIvy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0EF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0F9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_0FF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_100
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_101
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_102
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_103
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_104
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ShuffleBlock
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipWarpCannon
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_107
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_108
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaShutter
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_10A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_10B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_10C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLift
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftHmove
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftPairObj
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_RoyLiftWakiStep
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WendyFloor
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_IggyRoom
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_113
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_114
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_115
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_116
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_117
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_118
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_119
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_11A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_11B
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_11C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_11D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_11E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Block
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_120
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_121
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_122
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_ActorBlockRenga
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_124
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_125
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_126
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_127
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_128
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_129
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12B
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12C
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_12F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_130
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_131
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_132
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_133
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_134
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_ActorBlockMakeDRC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_136
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_137
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_138
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_139
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_13A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_13B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_13C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_13D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_13E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_13F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_140
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_141
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_142
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_143
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_144
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_145
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_146
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_147
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_148
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_149
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_14F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ObjPipeDown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_151
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_152
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_153
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_ObjPipeDownGroup
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_155
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_156
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_157
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SwitchHatenaButton
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SwitchPbutton
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SwitchPbuttonRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SwitchPbuttonNoWallKick
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_15C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_15D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_IcicleBig
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LemmyBall
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LemmyBomb
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_161
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_162
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_163
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_164
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_165
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_166
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_167
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_168
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_169
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PentaroIce
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_16B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_16C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_16D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_16E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_16F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KameckIce
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WendyIcicle
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrClown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BoxingKoopaJrClown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_174
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopaJrClown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopa
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireBar
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireBarSync
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_179
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_17F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_180
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_181
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_182
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_183
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_184
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_185
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_186
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_187
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_188
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_189
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_18A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_ActorCoin
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_18C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_18D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_18E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_18F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_190
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_191
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_192
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_193
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_194
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_195
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_196
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_197
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_198
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_199
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19B
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19C
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_19F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A0
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1A2
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A3
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A4
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A5
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A6
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A7
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1A8
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_BlueCoin
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1AF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1B5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_CoinmakiCoin
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1B7
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1B8
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1B9
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Yoshi
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_TottenPlayer
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_PlayerObject
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1BD
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1BE
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1BF
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1C0
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1C1
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1C2
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1C3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1C4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SlotYoshiChibi
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1C6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1C7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1C8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1C9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1CA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1CB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1CC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1CD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1CE
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_QuestPrizeItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1D9
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_IceBall
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_IceBallPakkun
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_FireBallPlayer
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_FireBallPakkun
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_YoshiFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1DF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1E9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1EA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1EB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1EC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1ED
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1EE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1EF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1F9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1FA
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1FB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1FC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1FD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_1FE
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_1FF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Nokonoko
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_201
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_202
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_203
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_204
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_205
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_206
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_207
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_208
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_209
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_20A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_20B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MechaKoopa
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_20D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_20E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_20F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_210
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_211
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_212
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_213
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_214
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_215
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_216
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_217
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_218
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_219
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_21F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_220
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_221
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_222
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_223
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_224
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_225
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_226
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_227
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_228
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_229
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_22A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_22B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_22C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_22D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireBallKeronpa
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireBallKeronpaRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_230
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireSnake
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_232
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_233
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_234
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_235
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_236
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_237
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_238
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_239
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_23A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_23B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_23C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_23D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Kazandan
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_23F
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_240
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_241
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_242
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_243
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_244
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_245
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_246
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_247
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_248
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_249
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_24A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_BgCenter
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_24C
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_24D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_24E
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Kinoko
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_FireFlower
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_MameKinoko
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_IceFlower
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Propeller
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Penguin
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_OneUpKinoko
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Musasabi
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_SuperMoon
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_TitleDemoItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_259
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_25F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_260
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_261
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_262
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_263
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_264
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_265
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_266
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_267
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_268
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Spanner
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_26F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_270
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_271
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_272
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_273
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_274
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_275
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_SearchKiller
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_277
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_278
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_279
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WakiSearchMagKiller
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_27B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_27C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_27D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_27E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_27F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_GabonRock
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_281
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_282
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_RockGabonRock
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_284
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SeichanSnowBall
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_286
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_287
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_288
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_289
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Woochan
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_28B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_28C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_28D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Bubble
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BubbleSync
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BubbleRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BubbleSyncRDash
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_292
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_293
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_294
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_295
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_296
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_297
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_298
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_299
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_29F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2A5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Bun
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunW2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunW3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunW4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunW5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunW6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaJrDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KameckDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BossKKDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopaDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Larry
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaSearchFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Lemmy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Morton
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MortonSanbo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MortonSanboParts
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Wendy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_WendyRing
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Ludwig
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_LudwigAlterEgo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Iggy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_IggyMagic
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Woogan
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Roy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_RoyLiftWaki
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BossKK
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BossKKThunder
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Kameck
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KameckIceConfig
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KameckWarpPos
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KameckMagic
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_PeachFinalCastleKoopaJr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Koopa
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaFireWaki
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_DemoKoopaJrClown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_DemoKoopaJr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BunDemoKameck
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaDemoKameck
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BossKKDemoKameck
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BossKKDemoKK
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopaFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopaJr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalKoopaJrFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalBomhei
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipLemmy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipMorton
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipLarry
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipWendy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipIggy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipRoy
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KokoopaShipLudwig
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Peach
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalDVPeach
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FinalDVShutter
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E6
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E8
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2E9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2EA
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_2EB
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_2EC
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_2ED
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2EE
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2EF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F0
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F1
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F2
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F3
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F4
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F5
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Hammer
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F7
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_Boomerang
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2F9
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_FireBallBros
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2FB
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_IceBallBros
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2FD
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MegaHammer
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_2FF
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_300
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_301
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_302
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_303
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_304
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_305
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_306
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_307
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_308
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_309
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_30A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_30B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_30C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_30D
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_30E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_30F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_310
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_311
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_312
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_313
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_314
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_315
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_316
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_317
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_318
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_319
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31A
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31B
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_31F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_320
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_321
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_322
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_323
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_324
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_325
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_326
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_327
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_328
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_BattleItem
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_32A
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_VsBattleItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_32C
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_32D
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_32E
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_32F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_330
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_331
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaJrFire
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_KoopaJrBall
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_UnderwaterKoopaJr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_UnderwaterKoopaJrClown
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_UnderwaterKoopaJrRetreatPos
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BoxingKoopaJr
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BoxingKoopaJrPostBattleDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_BoxingKoopaJrClownPostBattleDemo
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MiniGamePanelItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_SlotItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_CoinmakiCannon
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_CoinmakiItem
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_MiniGameKinopio
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_33F
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_340
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_341
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_342
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_343
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_344
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_345
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_346
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_347
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiABC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloon
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloonCheer
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiLight
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditChibiYoshiLightCheer
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditSoapABC
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditSoapCoin
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_StaffCreditTottenKun
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_350
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_351
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_352
    ProfileInfo::cResType_Course,       // ProfileInfo::cProfileID_353
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_RealizeFeverStar
    ProfileInfo::cResType_Boot,         // ProfileInfo::cProfileID_Star
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPlayer
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPlayer2PSub
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectChibiYoshi
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectCamera
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectCastle
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectToride
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectKinokoHouse1up
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectKinokoHouseShuffle
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectKinokoHouseSlot
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPeachGates1st
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPeachGates2nd
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectCoursePoint
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectWorldMoveDokan
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW8Cloud
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectGhost
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW2Bros
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW1
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW2
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW3
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW4
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW5
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW6
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW7
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW8
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShipW8Broken
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectSurrender
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectSwitchA
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectSwitchB
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectTeresa
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectOpeningKameck
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectTorideBoss
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPakkun
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoKinopio
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectTobiPuku
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectChorobon
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW7Item
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW5Teresa
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectFlag
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectMusasabi
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectWPillar
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW7Bridge
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectMiiBalloon
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPenguin
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW4Item
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW2Kuribo
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPakkunBig
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShadowKunIcon
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectDekaUnira
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectTomb
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoShadowKun
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectKotsuCoaster
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectKoopaJr
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectPeach
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectW1Item
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectStarGate
    ProfileInfo::cResType_CourseSelect, // ProfileInfo::cProfileID_CourseSelectEventAssistant
    ProfileInfo::cResType_Course,       // Profile 910
    ProfileInfo::cResType_Course,       // Profile 911
    ProfileInfo::cResType_Course        // Profile 912
};

// -------------------------------------------  Res ------------------------------------------- //

static const sead::SafeString cRes_015[]  = {
    "bombhei",
    "obj_coin"
};

static const sead::SafeString cRes_016[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_017[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_MiniGameMgr[]  = {
    "miniGame_shuffle",
    "block_pata",
    "KinopioMdl",
    "CommonAnm",
    "KinopioAnm",
    "miniGame_mochimaki",
    "miniGame_slot"
};

static const sead::SafeString cRes_MiniGameMgrRDash[]  = {
    "R_miniGame_shuffle",
    "block_pata",
    "KinopioMdl",
    "CommonAnm",
    "KinopioAnm",
    "miniGame_mochimaki",
    "miniGame_slot"
};

static const sead::SafeString cRes_ShootingStar[]  = {
    "I_star"
};

static const sead::SafeString cRes_StaffRollMgr[]  = {
    "baloon_ABC",
    "YoshiChibi_TexBubble",
    "copyright",
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexLight",
    "balloon",
    "obj_coin",
    "shadowkun"
};

static const sead::SafeString cRes_StaffRollMgrRDash[]  = {
    "baloon_ABC",
    "YoshiChibi_TexBubble",
    "R_copyright",
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexLight",
    "balloon",
    "obj_coin",
    "shadowkun"
};

static const sead::SafeString cRes_024[]  = {
    "peach"
};

static const sead::SafeString cRes_026[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_02B[]  = {
    "guru"
};

static const sead::SafeString cRes_02C[]  = {
    "guru"
};

static const sead::SafeString cRes_02D[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_02E[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_032[]  = {
    "bombhei"
};

static const sead::SafeString cRes_033[]  = {
    "bolt",
    "bolt_pyramid"
};

static const sead::SafeString cRes_FloorGyration[]  = {
    "circle_ground",
    "circle_ground_sabaku",
    "circle_ground_kori"
};

static const sead::SafeString cRes_036[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_037[]  = {
    "lift_zen_toride"
};

static const sead::SafeString cRes_038[]  = {
    "lift_zen_nohara"
};

static const sead::SafeString cRes_039[]  = {
    "lift_zen_kogen"
};

static const sead::SafeString cRes_03A[]  = {
    "lift_zen_ashiba"
};

static const sead::SafeString cRes_03B[]  = {
    "lift_zen_kaihei"
};

static const sead::SafeString cRes_PairObjChild[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_03D[]  = {
    "lift_zen_toride"
};

static const sead::SafeString cRes_03E[]  = {
    "lift_zen_shiro_iwa"
};

static const sead::SafeString cRes_03F[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_040[]  = {
    "lift_zen_nohara"
};

static const sead::SafeString cRes_041[]  = {
    "lift_zen_kogen"
};

static const sead::SafeString cRes_042[]  = {
    "lift_zen_kumiawase"
};

static const sead::SafeString cRes_043[]  = {
    "lift_zen_tagaichigai"
};

static const sead::SafeString cRes_044[]  = {
    "lift_zen_tagaichigai"
};

static const sead::SafeString cRes_045[]  = {
    "lift_zen_shiro_yogan"
};

static const sead::SafeString cRes_046[]  = {
    "lift_zen_sabaku_iseki"
};

static const sead::SafeString cRes_047[]  = {
    "lift_zen_toride_rock"
};

static const sead::SafeString cRes_048[]  = {
    "lift_zen_toride_rock"
};

static const sead::SafeString cRes_049[]  = {
    "lift_zen_shiro"
};

static const sead::SafeString cRes_04A[]  = {
    "lift_zen_warning"
};

static const sead::SafeString cRes_04B[]  = {
    "lift_han_iwakabe",
    "lift_han_iwakabe_moyou"
};

static const sead::SafeString cRes_04C[]  = {
    "obj_kinoko"
};

static const sead::SafeString cRes_KinokoLift[]  = {
    "lift_kinoko_sora"
};

static const sead::SafeString cRes_KinokoLiftColor[]  = {
    "lift_kinoko_sora"
};

static const sead::SafeString cRes_LiftZenStar[]  = {
    "lift_zen_star"
};

static const sead::SafeString cRes_050[]  = {
    "obj_kinoko"
};

static const sead::SafeString cRes_051[]  = {
    "obj_kinoko",
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_052[]  = {
    "lift_trampoline"
};

static const sead::SafeString cRes_053[]  = {
    "lift_trampoline"
};

static const sead::SafeString cRes_054[]  = {
    "obj_waterfull",
    "obj_waterhalf"
};

static const sead::SafeString cRes_055[]  = {
    "obj_magma",
    "obj_magmadeco",
    "obj_magmawave",
    "yogan_line"
};

static const sead::SafeString cRes_056[]  = {
    "obj_poisonwater",
    "obj_magmadeco"
};

static const sead::SafeString cRes_057[]  = {
    "obj_quicksand"
};

static const sead::SafeString cRes_058[]  = {
    "obj_envfog"
};

static const sead::SafeString cRes_059[]  = {
    "obj_envfog"
};

static const sead::SafeString cRes_BgActorYukaMario[]  = {
    "mario_brothers_yuka"
};

static const sead::SafeString cRes_05B[]  = {
    "koopaJr_clown_yuka"
};

static const sead::SafeString cRes_05C[]  = {
    "lift_han_spin",
    "bolt"
};

static const sead::SafeString cRes_05F[]  = {
    "lift_huriko_ue"
};

static const sead::SafeString cRes_060[]  = {
    "lift_huriko_ue"
};

static const sead::SafeString cRes_061[]  = {
    "lift_han_rotate_light"
};

static const sead::SafeString cRes_062[]  = {
    "lift_huriko_yougan"
};

static const sead::SafeString cRes_063[]  = {
    "lift_huriko_yougan"
};

static const sead::SafeString cRes_064[]  = {
    "test_lift"
};

static const sead::SafeString cRes_KillerHoudai[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_StretchKillerHoudai[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_MagnumKillerHoudai[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_MagnumKillerHoudaiDown[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_SearchKillerHoudai[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_SearchMagnumKillerHoudai[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_SearchMagnumKillerHoudaiDown[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_MagnumKillerHoudaiRDash[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_MagnumKillerHoudaiDownRDash[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_SearchMagnumKillerHoudaiRDash[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_SearchMagnumKillerHoudaiDownRDash[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_070[]  = {
    "killer_rot_houdai",
    "killer"
};

static const sead::SafeString cRes_071[]  = {
    "killer_rot_houdai",
    "killer"
};

static const sead::SafeString cRes_072[]  = {
    "houdai_slope",
    "houdai_ball",
    "bombhei"
};

static const sead::SafeString cRes_073[]  = {
    "houdai_rot",
    "houdai_ball"
};

static const sead::SafeString cRes_074[]  = {
    "houdai_rot_large_B",
    "houdai_ball"
};

static const sead::SafeString cRes_075[]  = {
    "houdai",
    "houdai_ball"
};

static const sead::SafeString cRes_076[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_077[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_Intermittent[]  = {
    "sandpillar"
};

static const sead::SafeString cRes_IntermittentPermanent[]  = {
    "sandpillar"
};

static const sead::SafeString cRes_WaterIntermittent[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_WaterIntermittentPermanent[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_WaterIntermittentPermanentRD3_3[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_07E[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_WaterIntermittentBossChild[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_YoganIntermittent[]  = {
    "firepillar"
};

static const sead::SafeString cRes_081[]  = {
    "lift_zen_kaitenita",
    "lift_zen_kaitenita_toride"
};

static const sead::SafeString cRes_082[]  = {
    "obj_dokan"
};

static const sead::SafeString cRes_083[]  = {
    "obj_dokan"
};

static const sead::SafeString cRes_084[]  = {
    "obj_dokan"
};

static const sead::SafeString cRes_085[]  = {
    "obj_dokan"
};

static const sead::SafeString cRes_ObjPipeDownNG[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_087[]  = {
    "obj_dokan_CB"
};

static const sead::SafeString cRes_088[]  = {
    "obj_dokan_CB"
};

static const sead::SafeString cRes_089[]  = {
    "obj_dokan_CB"
};

static const sead::SafeString cRes_08A[]  = {
    "obj_dokan_CB"
};

static const sead::SafeString cRes_08B[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_08C[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_08D[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_08E[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_08F[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_090[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_091[]  = {
    "obj_dokan_cannon",
    "obj_dokan"
};

static const sead::SafeString cRes_092[]  = {
    "obj_dokan_cannon",
    "obj_dokan"
};

static const sead::SafeString cRes_093[]  = {
    "lift_zen_hanebashi"
};

static const sead::SafeString cRes_094[]  = {
    "lift_zen_hanebashi"
};

static const sead::SafeString cRes_095[]  = {
    "lift_zen_hanebashi"
};

static const sead::SafeString cRes_096[]  = {
    "lift_zen_yoko"
};

static const sead::SafeString cRes_097[]  = {
    "test_lift"
};

static const sead::SafeString cRes_098[]  = {
    "test_lift"
};

static const sead::SafeString cRes_099[]  = {
    "lift_zen_chika_pori"
};

static const sead::SafeString cRes_09B[]  = {
    "lift_zen_rotate_wood"
};

static const sead::SafeString cRes_09C[]  = {
    "lift_zen_rotate_wood"
};

static const sead::SafeString cRes_09D[]  = {
    "lift_zen_rotate_stone"
};

static const sead::SafeString cRes_09E[]  = {
    "lift_obake_chikei"
};

static const sead::SafeString cRes_09F[]  = {
    "lift_obake_chikei"
};

static const sead::SafeString cRes_0A0[]  = {
    "lift_obake_chikei"
};

static const sead::SafeString cRes_0A1[]  = {
    "lift_obake_chikei_heya"
};

static const sead::SafeString cRes_0A2[]  = {
    "lift_zen_color_pori"
};

static const sead::SafeString cRes_0A3[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_0A4[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_0A5[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_0A6[]  = {
    "lift_obake_chikei_fune"
};

static const sead::SafeString cRes_0A7[]  = {
    "lift_zen_hammer"
};

static const sead::SafeString cRes_0A8[]  = {
    "lift_moaidon"
};

static const sead::SafeString cRes_0A9[]  = {
    "lift_moaidon"
};

static const sead::SafeString cRes_0AA[]  = {
    "lift_moaidon"
};

static const sead::SafeString cRes_0AB[]  = {
    "lift_moaidon"
};

static const sead::SafeString cRes_0AC[]  = {
    "lift_moaidon"
};

static const sead::SafeString cRes_0AD[]  = {
    "lift_zen_spin_cube"
};

static const sead::SafeString cRes_0AE[]  = {
    "lift_zen_spin_pyramid"
};

static const sead::SafeString cRes_0AF[]  = {
    "lift_zen_spin_pyramid"
};

static const sead::SafeString cRes_0B0[]  = {
    "lift_turi_ashiba"
};

static const sead::SafeString cRes_0B1[]  = {
    "lift_turi_ashiba_wire"
};

static const sead::SafeString cRes_0B2[]  = {
    "lift_zen_yogan_down"
};

static const sead::SafeString cRes_0B3[]  = {
    "lift_obake_chikei"
};

static const sead::SafeString cRes_0B4[]  = {
    "lift_number_ship_yougan",
    "lift_number_ship"
};

static const sead::SafeString cRes_0B5[]  = {
    "block_challenge"
};

static const sead::SafeString cRes_0B6[]  = {
    "block_odai",
    "coinedit_batten"
};

static const sead::SafeString cRes_0B7[]  = {
    "block_challenge"
};

static const sead::SafeString cRes_LineSpinLift[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_LineSpinLiftParentRDash[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_LineSpinLiftChildRDash[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_0BB[]  = {
    "light_search",
    "Mask_flashlight_obake",
    "Mask"
};

static const sead::SafeString cRes_0BC[]  = {
    "block_challenge"
};

static const sead::SafeString cRes_0BD[]  = {
    "block_tsuta"
};

static const sead::SafeString cRes_0BE[]  = {
    "obj_yashi",
    "obj_yashi_sabaku"
};

static const sead::SafeString cRes_0BF[]  = {
    "iron_boll_hole"
};

static const sead::SafeString cRes_0C0[]  = {
    "iron_boll_hole"
};

static const sead::SafeString cRes_0C1[]  = {
    "gorogoro"
};

static const sead::SafeString cRes_SnakeBlock[]  = {
    "block_snake",
    "block_snake_ice"
};

static const sead::SafeString cRes_0C3[]  = {
    "block_snake",
    "block_snake_ice"
};

static const sead::SafeString cRes_0C4[]  = {
    "block_snake",
    "block_snake_ice"
};

static const sead::SafeString cRes_0C5[]  = {
    "lift_spin_kinoko",
    "bolt"
};

static const sead::SafeString cRes_0C6[]  = {
    "lift_spin_kinoko",
    "bolt"
};

static const sead::SafeString cRes_0C7[]  = {
    "lift_obake_chikei"
};

static const sead::SafeString cRes_0C8[]  = {
    "light_block"
};

static const sead::SafeString cRes_0C9[]  = {
    "lift_kinoko_yoko"
};

static const sead::SafeString cRes_0CA[]  = {
    "lift_kinoko_yoko"
};

static const sead::SafeString cRes_0CB[]  = {
    "block_slide"
};

static const sead::SafeString cRes_0CC[]  = {
    "block_slide"
};

static const sead::SafeString cRes_0CD[]  = {
    "met_pata"
};

static const sead::SafeString cRes_0CE[]  = {
    "met_pataBig"
};

static const sead::SafeString cRes_0CF[]  = {
    "met_pata"
};

static const sead::SafeString cRes_0D0[]  = {
    "obj_gear",
    "obj_gear_shiro"
};

static const sead::SafeString cRes_0D1[]  = {
    "R_obj_gear",
    "obj_gear_shiro"
};

static const sead::SafeString cRes_FloorHoleDokan[]  = {
    "circle_ground_holeD_chika",
    "obj_dokan"
};

static const sead::SafeString cRes_0D3[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso",
    "lift_han_sky"
};

static const sead::SafeString cRes_0D4[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso",
    "lift_han_sky"
};

static const sead::SafeString cRes_0D5[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso",
    "lift_han_sky"
};

static const sead::SafeString cRes_0D6[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso",
    "lift_han_sky"
};

static const sead::SafeString cRes_0D7[]  = {
    "lift_han_wood"
};

static const sead::SafeString cRes_0D8[]  = {
    "lift_han_wood"
};

static const sead::SafeString cRes_0D9[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_0DA[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_0DB[]  = {
    "lift_han_wood",
    "lift_han_stone",
    "lift_kinoko_yoko",
    "lift_han_spin",
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_0DC[]  = {
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_0DD[]  = {
    "R_lift_kinoko_shiso"
};

static const sead::SafeString cRes_0DE[]  = {
    "lift_maruta"
};

static const sead::SafeString cRes_0DF[]  = {
    "lift_taru"
};

static const sead::SafeString cRes_Burner[]  = {
    "fire_cannon"
};

static const sead::SafeString cRes_0E1[]  = {
    "fire_cannon"
};

static const sead::SafeString cRes_0E2[]  = {
    "fire_cannon"
};

static const sead::SafeString cRes_0E3[]  = {
    "fire_rot_cannon"
};

static const sead::SafeString cRes_0E4[]  = {
    "block_jump"
};

static const sead::SafeString cRes_0E5[]  = {
    "noboribou_obake"
};

static const sead::SafeString cRes_0E6[]  = {
    "lift_tenbin",
    "lift_han_wood"
};

static const sead::SafeString cRes_0E7[]  = {
    "lift_tenbin",
    "lift_han_wood"
};

static const sead::SafeString cRes_0E8[]  = {
    "lift_tenbin",
    "lift_han_wood"
};

static const sead::SafeString cRes_0E9[]  = {
    "lift_guraIwa"
};

static const sead::SafeString cRes_0EA[]  = {
    "lift_zen_kanaami"
};

static const sead::SafeString cRes_0EB[]  = {
    "bombhei",
    "iron_ball"
};

static const sead::SafeString cRes_0EC[]  = {
    "obj_waterfloat"
};

static const sead::SafeString cRes_PlyIce[]  = {
    "ice"
};

static const sead::SafeString cRes_TarzanIvy[]  = {
    "tarzantsuta"
};

static const sead::SafeString cRes_0EF[]  = {
    "tarzantsuta"
};

static const sead::SafeString cRes_0F0[]  = {
    "hashigo"
};

static const sead::SafeString cRes_0F1[]  = {
    "box_wood"
};

static const sead::SafeString cRes_0F2[]  = {
    "box_iron"
};

static const sead::SafeString cRes_0F3[]  = {
    "remo_lift"
};

static const sead::SafeString cRes_0F4[]  = {
    "remo_lift_line"
};

static const sead::SafeString cRes_0F6[]  = {
    "obj_block"
};

static const sead::SafeString cRes_0F7[]  = {
    "obj_block"
};

static const sead::SafeString cRes_0F8[]  = {
    "block_help"
};

static const sead::SafeString cRes_0F9[]  = {
    "R_block_luigi"
};

static const sead::SafeString cRes_0FA[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_0FB[]  = {
    "lift_zen_toride_iron"
};

static const sead::SafeString cRes_0FC[]  = {
    "yogan_jimen",
    "yogan_jimen_line"
};

static const sead::SafeString cRes_0FD[]  = {
    "R_yogan_jimen",
    "R_yogan_jimen_line"
};

static const sead::SafeString cRes_0FE[]  = {
    "block_zen_rail_shiro"
};

static const sead::SafeString cRes_0FF[]  = {
    "block_zen_rail_shiro"
};

static const sead::SafeString cRes_100[]  = {
    "lift_han_wood",
    "lift_han_stone"
};

static const sead::SafeString cRes_101[]  = {
    "lift_han_sky"
};

static const sead::SafeString cRes_102[]  = {
    "test_lift"
};

static const sead::SafeString cRes_103[]  = {
    "lift_kanransha"
};

static const sead::SafeString cRes_104[]  = {
    "lift_han_leaf"
};

static const sead::SafeString cRes_ShuffleBlock[]  = {
    "miniGame_shuffle",
    "block_pata",
    "R_miniGame_shuffle"
};

static const sead::SafeString cRes_KokoopaShipWarpCannon[]  = {
    "boss_cannon"
};

static const sead::SafeString cRes_107[]  = {
    "lift_han_tsuru"
};

static const sead::SafeString cRes_108[]  = {
    "boss_koopa_ashiba"
};

static const sead::SafeString cRes_KoopaShutter[]  = {
    "boss_shutter_koopa"
};

static const sead::SafeString cRes_10A[]  = {
    "ship_bottom"
};

static const sead::SafeString cRes_10B[]  = {
    "ship_bottom"
};

static const sead::SafeString cRes_10C[]  = {
    "ship_bottom"
};

static const sead::SafeString cRes_PeachFinalCastleKoopaJrLift[]  = {
    "lift_han_koopa"
};

static const sead::SafeString cRes_PeachFinalCastleKoopaJrLiftHmove[]  = {
    "lift_han_koopa"
};

static const sead::SafeString cRes_PeachFinalCastleKoopaJrLiftPairObj[]  = {
    "lift_han_koopa"
};

static const sead::SafeString cRes_RoyLiftWakiStep[]  = {
    "lift_han_hikousen"
};

static const sead::SafeString cRes_WendyFloor[]  = {
    "ice_wendy"
};

static const sead::SafeString cRes_IggyRoom[]  = {
    "room_iggy"
};

static const sead::SafeString cRes_113[]  = {
    "goal_set"
};

static const sead::SafeString cRes_114[]  = {
    "goal_set_kaiga"
};

static const sead::SafeString cRes_115[]  = {
    "R_goal_set"
};

static const sead::SafeString cRes_116[]  = {
    "R_goal_set_kaiga"
};

static const sead::SafeString cRes_118[]  = {
    "cookie"
};

static const sead::SafeString cRes_119[]  = {
    "magic_hand"
};

static const sead::SafeString cRes_11A[]  = {
    "magic_hand"
};

static const sead::SafeString cRes_11B[]  = {
    "block_ice",
    "ice_coin"
};

static const sead::SafeString cRes_11D[]  = {
    "lift_zen_float"
};

static const sead::SafeString cRes_11E[]  = {
    "lift_zen_float"
};

static const sead::SafeString cRes_ActorBlockMakeDRC[]  = {
    "block_DRC"
};

static const sead::SafeString cRes_136[]  = {
    "block_pata"
};

static const sead::SafeString cRes_138[]  = {
    "block_cloud",
    "jugem",
    "obj_coin"
};

static const sead::SafeString cRes_13A[]  = {
    "switch"
};

static const sead::SafeString cRes_13B[]  = {
    "switch"
};

static const sead::SafeString cRes_13C[]  = {
    "I_yoshichibi_egg",
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexBubble",
    "YoshiChibi_TexLight",
    "balloon"
};

static const sead::SafeString cRes_140[]  = {
    "block_pata"
};

static const sead::SafeString cRes_141[]  = {
    "block_roulette"
};

static const sead::SafeString cRes_142[]  = {
    "obj_chikuwa_block"
};

static const sead::SafeString cRes_143[]  = {
    "block_kameck",
    "obj_chikuwa_block"
};

static const sead::SafeString cRes_144[]  = {
    "box_wood"
};

static const sead::SafeString cRes_145[]  = {
    "box_iron"
};

static const sead::SafeString cRes_146[]  = {
    "box_iron"
};

static const sead::SafeString cRes_147[]  = {
    "box_iron"
};

static const sead::SafeString cRes_148[]  = {
    "magic_hand"
};

static const sead::SafeString cRes_149[]  = {
    "magic_hand"
};

static const sead::SafeString cRes_14A[]  = {
    "magic_hand"
};

static const sead::SafeString cRes_14B[]  = {
    "block_DRC_hide"
};

static const sead::SafeString cRes_14D[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_14E[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_14F[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_ObjPipeDown[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_151[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_152[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_153[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_ObjPipeDownGroup[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_155[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_156[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_157[]  = {
    "obj_dokan",
    "obj_dokan_kaiga"
};

static const sead::SafeString cRes_SwitchHatenaButton[]  = {
    "switch"
};

static const sead::SafeString cRes_SwitchPbutton[]  = {
    "switch"
};

static const sead::SafeString cRes_SwitchPbuttonRDash[]  = {
    "switch"
};

static const sead::SafeString cRes_SwitchPbuttonNoWallKick[]  = {
    "switch"
};

static const sead::SafeString cRes_15D[]  = {
    "switch_koopa"
};

static const sead::SafeString cRes_IcicleBig[]  = {
    "obj_turara_rakka_Big"
};

static const sead::SafeString cRes_LemmyBall[]  = {
    "lemmy"
};

static const sead::SafeString cRes_LemmyBomb[]  = {
    "lemmy"
};

static const sead::SafeString cRes_161[]  = {
    "shell_fish",
    "star_coin",
    "switch"
};

static const sead::SafeString cRes_163[]  = {
    "lift_ice_ashiba"
};

static const sead::SafeString cRes_164[]  = {
    "lift_ice_ashiba"
};

static const sead::SafeString cRes_165[]  = {
    "lift_ice_ashiba"
};

static const sead::SafeString cRes_166[]  = {
    "lift_suisha"
};

static const sead::SafeString cRes_167[]  = {
    "lift_number_ship_up"
};

static const sead::SafeString cRes_168[]  = {
    "lift_number_ship_up"
};

static const sead::SafeString cRes_169[]  = {
    "R_lift_number_ship_up"
};

static const sead::SafeString cRes_PentaroIce[]  = {
    "ice"
};

static const sead::SafeString cRes_16B[]  = {
    "lift_up_down_side"
};

static const sead::SafeString cRes_16C[]  = {
    "lift_up_down_side"
};

static const sead::SafeString cRes_16D[]  = {
    "block_ice_hard"
};

static const sead::SafeString cRes_16E[]  = {
    "wanwan"
};

static const sead::SafeString cRes_16F[]  = {
    "wanwan"
};

static const sead::SafeString cRes_KameckIce[]  = {
    "ice_kameck",
    "kuribo",
    "nokonokoA",
    "bombhei",
    "choropoo",
    "wing",
    "kuriboMini"
};

static const sead::SafeString cRes_WendyIcicle[]  = {
    "obj_turara_rakka"
};

static const sead::SafeString cRes_PeachFinalCastleKoopaJrClown[]  = {
    "koopaJr_clown"
};

static const sead::SafeString cRes_BoxingKoopaJrClown[]  = {
    "koopaJr_clown",
    "koopaJr_clown_b",
    "bombhei"
};

static const sead::SafeString cRes_174[]  = {
    "block_koopaJr_clown"
};

static const sead::SafeString cRes_FinalKoopaJrClown[]  = {
    "koopaJr_clown"
};

static const sead::SafeString cRes_FinalKoopa[]  = {
    "koopa",
    "koopa_model",
    "peach",
    "boss_shutter_peach"
};

static const sead::SafeString cRes_FireBar[]  = {
    "center_firebar",
    "firebar_L"
};

static const sead::SafeString cRes_FireBarSync[]  = {
    "center_firebar",
    "firebar_L"
};

static const sead::SafeString cRes_179[]  = {
    "firebar_L"
};

static const sead::SafeString cRes_17A[]  = {
    "center_firebar",
    "firebar_L"
};

static const sead::SafeString cRes_17B[]  = {
    "block_ice"
};

static const sead::SafeString cRes_17D[]  = {
    "met"
};

static const sead::SafeString cRes_17E[]  = {
    "met"
};

static const sead::SafeString cRes_17F[]  = {
    "unizo"
};

static const sead::SafeString cRes_180[]  = {
    "unizo"
};

static const sead::SafeString cRes_181[]  = {
    "unizoBig"
};

static const sead::SafeString cRes_182[]  = {
    "unizo"
};

static const sead::SafeString cRes_183[]  = {
    "block_pow",
    "EF_POW"
};

static const sead::SafeString cRes_184[]  = {
    "block_light"
};

static const sead::SafeString cRes_185[]  = {
    "block_fly"
};

static const sead::SafeString cRes_186[]  = {
    "ice",
    "obj_coin"
};

static const sead::SafeString cRes_187[]  = {
    "block_taru"
};

static const sead::SafeString cRes_188[]  = {
    "ice"
};

static const sead::SafeString cRes_189[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_18A[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_ActorCoin[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_18C[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_18D[]  = {
    "obj_coin",
    "ice_coin"
};

static const sead::SafeString cRes_18E[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_18F[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_190[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_191[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_192[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_193[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_194[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_195[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_196[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_197[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_198[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_199[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_19A[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_19C[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_19D[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_19F[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A0[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A1[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A3[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A4[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A5[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A6[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A7[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1A8[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_BlueCoin[]  = {
    "obj_coin"
};

static const sead::SafeString cRes_1AA[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1AB[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1AC[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1AD[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1AE[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1AF[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1B0[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1B1[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1B2[]  = {
    "star_coin"
};

static const sead::SafeString cRes_1B3[]  = {
    "star_coin"
};

static const sead::SafeString cRes_CoinmakiCoin[]  = {
    "miniGame_mochimaki"
};

static const sead::SafeString cRes_1B9[]  = {
    "balloon",
    "I_kinoko"
};

static const sead::SafeString cRes_Yoshi[]  = {
    "YoshiAnm",
    "Yoshi_TexGreen",
    "Yoshi_TexPink",
    "Yoshi_TexYellow",
    "Yoshi_TexLightBlue"
};

static const sead::SafeString cRes_TottenPlayer[]  = {
    "EF_HipdropEX",
    "shadowkun_player"
};

static const sead::SafeString cRes_PlayerObject[]  = {
    "MarioMdl",
    "LuigiMdl",
    "KinopioMdl",
    "MiiMdl",
    "CommonAnm",
    "LuigiAnm",
    "KinopioAnm",
    "MiiAnm",
    "EF_HipdropEX"
};

static const sead::SafeString cRes_1BD[]  = {
    "KinopioMdl",
    "CommonAnm",
    "KinopioAnm",
    "baloon_hey"
};

static const sead::SafeString cRes_1BE[]  = {
    "I_yoshichibi_egg",
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexBubble",
    "YoshiChibi_TexLight",
    "balloon_awachibiyoshi"
};

static const sead::SafeString cRes_1BF[]  = {
    "YoshiChibi_TexBubble",
    "balloon_awachibiyoshi"
};

static const sead::SafeString cRes_1C0[]  = {
    "YoshiChibi_TexBalloon"
};

static const sead::SafeString cRes_1C1[]  = {
    "YoshiChibi_TexLight"
};

static const sead::SafeString cRes_1C2[]  = {
    "YoshiChibi_TexBalloon"
};

static const sead::SafeString cRes_1C3[]  = {
    "balloon_awachibiyoshi",
    "obj_coin",
    "I_kinoko",
    "I_fireflower",
    "I_iceflower",
    "I_musasabi"
};

static const sead::SafeString cRes_SlotYoshiChibi[]  = {
    "YoshiChibi_TexBubble",
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexLight",
    "miniGame_slot"
};

static const sead::SafeString cRes_1C6[]  = {
    "obj_coin",
    "kuribo"
};

static const sead::SafeString cRes_1C8[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_1CB[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_1CC[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_1CE[]  = {
    "KinopioMdl",
    "CommonAnm",
    "KinopioAnm"
};

static const sead::SafeString cRes_QuestPrizeItem[]  = {
    "I_musasabi",
    "I_star",
    "I_kinoko",
    "I_fireflower",
    "I_iceflower"
};

static const sead::SafeString cRes_1D0[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_1D1[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_1D2[]  = {
    "obj_balloon",
    "kuribo",
    "kakibo",
    "obj_coin"
};

static const sead::SafeString cRes_1D3[]  = {
    "kuribo"
};

static const sead::SafeString cRes_1D4[]  = {
    "kakibo"
};

static const sead::SafeString cRes_1D5[]  = {
    "kuribo",
    "wing"
};

static const sead::SafeString cRes_1D6[]  = {
    "kuribo_iga"
};

static const sead::SafeString cRes_1D7[]  = {
    "kuriboMini"
};

static const sead::SafeString cRes_1D8[]  = {
    "kuribo",
    "kuriboBig"
};

static const sead::SafeString cRes_1D9[]  = {
    "kuribo",
    "kuriboBig"
};

static const sead::SafeString cRes_1DF[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E0[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E1[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E2[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E3[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E4[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E5[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E6[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E7[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E8[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1E9[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1EA[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1EB[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1EC[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1ED[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1EE[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1EF[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1F0[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1F1[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1F2[]  = {
    "pakkun"
};

static const sead::SafeString cRes_1F3[]  = {
    "pakkun_walk"
};

static const sead::SafeString cRes_1F4[]  = {
    "pakkun_water"
};

static const sead::SafeString cRes_1F5[]  = {
    "pakkun_water"
};

static const sead::SafeString cRes_1F6[]  = {
    "pakkun_black"
};

static const sead::SafeString cRes_1F7[]  = {
    "pakkun_black"
};

static const sead::SafeString cRes_1F8[]  = {
    "musasabi"
};

static const sead::SafeString cRes_1F9[]  = {
    "sanbo"
};

static const sead::SafeString cRes_1FA[]  = {
    "sanbo"
};

static const sead::SafeString cRes_1FB[]  = {
    "hanachan_big"
};

static const sead::SafeString cRes_1FC[]  = {
    "hanachan"
};

static const sead::SafeString cRes_1FD[]  = {
    "hanachan"
};

static const sead::SafeString cRes_1FE[]  = {
    "hanachan_big"
};

static const sead::SafeString cRes_Nokonoko[]  = {
    "nokonokoA"
};

static const sead::SafeString cRes_201[]  = {
    "nokonokoA"
};

static const sead::SafeString cRes_202[]  = {
    "nokonokoBig"
};

static const sead::SafeString cRes_203[]  = {
    "nokonokoA",
    "wing"
};

static const sead::SafeString cRes_204[]  = {
    "nokonokoA",
    "wing"
};

static const sead::SafeString cRes_205[]  = {
    "togezo",
    "paipo"
};

static const sead::SafeString cRes_206[]  = {
    "togezo",
    "paipo"
};

static const sead::SafeString cRes_207[]  = {
    "kanibo"
};

static const sead::SafeString cRes_208[]  = {
    "kanibo"
};

static const sead::SafeString cRes_209[]  = {
    "bombhei"
};

static const sead::SafeString cRes_20A[]  = {
    "bombhei"
};

static const sead::SafeString cRes_20B[]  = {
    "bombhei"
};

static const sead::SafeString cRes_MechaKoopa[]  = {
    "mecha_koopa"
};

static const sead::SafeString cRes_20D[]  = {
    "penguin2",
    "ice"
};

static const sead::SafeString cRes_20E[]  = {
    "penguin2"
};

static const sead::SafeString cRes_20F[]  = {
    "penguin2"
};

static const sead::SafeString cRes_210[]  = {
    "met_hone"
};

static const sead::SafeString cRes_211[]  = {
    "met_hone"
};

static const sead::SafeString cRes_212[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_213[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_214[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_215[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_216[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_217[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_218[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_219[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_21A[]  = {
    "pukupuku_mecha"
};

static const sead::SafeString cRes_21B[]  = {
    "pukupuku_toge"
};

static const sead::SafeString cRes_21C[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_21D[]  = {
    "pukupuku_mecha"
};

static const sead::SafeString cRes_21E[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_21F[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_220[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_221[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_222[]  = {
    "pukupuku_mecha"
};

static const sead::SafeString cRes_223[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_224[]  = {
    "fishbone"
};

static const sead::SafeString cRes_225[]  = {
    "fugu"
};

static const sead::SafeString cRes_226[]  = {
    "fuguBig"
};

static const sead::SafeString cRes_227[]  = {
    "fugu"
};

static const sead::SafeString cRes_228[]  = {
    "fuguBig"
};

static const sead::SafeString cRes_229[]  = {
    "kurage"
};

static const sead::SafeString cRes_22A[]  = {
    "ankou"
};

static const sead::SafeString cRes_22B[]  = {
    "jump_step"
};

static const sead::SafeString cRes_22C[]  = {
    "keronpa"
};

static const sead::SafeString cRes_22D[]  = {
    "keronpa"
};

static const sead::SafeString cRes_230[]  = {
    "keronpa"
};

static const sead::SafeString cRes_FireSnake[]  = {
    "fire_snake"
};

static const sead::SafeString cRes_232[]  = {
    "gorogoro"
};

static const sead::SafeString cRes_233[]  = {
    "gorogoro"
};

static const sead::SafeString cRes_234[]  = {
    "gorogoro"
};

static const sead::SafeString cRes_235[]  = {
    "middle_flag"
};

static const sead::SafeString cRes_236[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_237[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_238[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_239[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_23A[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_23B[]  = {
    "daikonbou"
};

static const sead::SafeString cRes_23C[]  = {
    "kazan_rock"
};

static const sead::SafeString cRes_23D[]  = {
    "kazan_rock"
};

static const sead::SafeString cRes_Kazandan[]  = {
    "kazan_rock"
};

static const sead::SafeString cRes_Kinoko[]  = {
    "I_kinoko"
};

static const sead::SafeString cRes_FireFlower[]  = {
    "I_fireflower"
};

static const sead::SafeString cRes_MameKinoko[]  = {
    "I_kinoko"
};

static const sead::SafeString cRes_IceFlower[]  = {
    "I_iceflower"
};

static const sead::SafeString cRes_Propeller[]  = {
    "I_propeller"
};

static const sead::SafeString cRes_Penguin[]  = {
    "I_penguin"
};

static const sead::SafeString cRes_OneUpKinoko[]  = {
    "I_kinoko"
};

static const sead::SafeString cRes_Musasabi[]  = {
    "I_musasabi"
};

static const sead::SafeString cRes_SuperMoon[]  = {
    "I_moon"
};

static const sead::SafeString cRes_TitleDemoItem[]  = {
    "I_musasabi"
};

static const sead::SafeString cRes_259[]  = {
    "obj_sea_wakame"
};

static const sead::SafeString cRes_25A[]  = {
    "obj_door"
};

static const sead::SafeString cRes_25B[]  = {
    "obj_door_obake"
};

static const sead::SafeString cRes_25C[]  = {
    "obj_door_torideboss"
};

static const sead::SafeString cRes_25D[]  = {
    "obj_door_torideboss"
};

static const sead::SafeString cRes_25E[]  = {
    "obj_door_shiroboss"
};

static const sead::SafeString cRes_25F[]  = {
    "obj_door_shiroboss"
};

static const sead::SafeString cRes_260[]  = {
    "boss_koopa_door"
};

static const sead::SafeString cRes_261[]  = {
    "boss_koopa_door"
};

static const sead::SafeString cRes_262[]  = {
    "choropoo"
};

static const sead::SafeString cRes_263[]  = {
    "choropoo"
};

static const sead::SafeString cRes_264[]  = {
    "basabasa"
};

static const sead::SafeString cRes_265[]  = {
    "center_fire"
};

static const sead::SafeString cRes_266[]  = {
    "kuribo",
    "kakibo",
    "bombhei",
    "nokonokoA"
};

static const sead::SafeString cRes_267[]  = {
    "obj_kinoko",
    "lift_kinoko_shiso"
};

static const sead::SafeString cRes_268[]  = {
    "choropoo"
};

static const sead::SafeString cRes_Spanner[]  = {
    "choropoo"
};

static const sead::SafeString cRes_26A[]  = {
    "choropoo"
};

static const sead::SafeString cRes_26B[]  = {
    "pakkun_tane"
};

static const sead::SafeString cRes_26C[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_26D[]  = {
    "jugem",
    "togezo",
    "paipo"
};

static const sead::SafeString cRes_26E[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_26F[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_270[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_271[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_272[]  = {
    "jugem",
    "togezo",
    "paipo",
    "pakkun",
    "pakkun_tane"
};

static const sead::SafeString cRes_278[]  = {
    "killer_king"
};

static const sead::SafeString cRes_279[]  = {
    "killer_king"
};

static const sead::SafeString cRes_WakiSearchMagKiller[]  = {
    "killer_mag"
};

static const sead::SafeString cRes_27B[]  = {
    "dossun"
};

static const sead::SafeString cRes_27C[]  = {
    "dossun"
};

static const sead::SafeString cRes_27D[]  = {
    "gabon"
};

static const sead::SafeString cRes_27E[]  = {
    "gabon"
};

static const sead::SafeString cRes_27F[]  = {
    "gabon"
};

static const sead::SafeString cRes_GabonRock[]  = {
    "gabon"
};

static const sead::SafeString cRes_281[]  = {
    "gabon_rock"
};

static const sead::SafeString cRes_282[]  = {
    "gabon_rock"
};

static const sead::SafeString cRes_RockGabonRock[]  = {
    "gabon_rock"
};

static const sead::SafeString cRes_284[]  = {
    "seichan"
};

static const sead::SafeString cRes_SeichanSnowBall[]  = {
    "seichan"
};

static const sead::SafeString cRes_286[]  = {
    "seichan"
};

static const sead::SafeString cRes_287[]  = {
    "karon"
};

static const sead::SafeString cRes_288[]  = {
    "karon"
};

static const sead::SafeString cRes_289[]  = {
    "karon"
};

static const sead::SafeString cRes_Woochan[]  = {
    "woochan"
};

static const sead::SafeString cRes_28B[]  = {
    "mouse"
};

static const sead::SafeString cRes_28C[]  = {
    "chorobon"
};

static const sead::SafeString cRes_28D[]  = {
    "chorobon"
};

static const sead::SafeString cRes_Bubble[]  = {
    "bubble"
};

static const sead::SafeString cRes_BubbleSync[]  = {
    "bubble"
};

static const sead::SafeString cRes_BubbleRDash[]  = {
    "bubble"
};

static const sead::SafeString cRes_BubbleSyncRDash[]  = {
    "bubble"
};

static const sead::SafeString cRes_292[]  = {
    "crasher"
};

static const sead::SafeString cRes_293[]  = {
    "unabon"
};

static const sead::SafeString cRes_294[]  = {
    "unabon"
};

static const sead::SafeString cRes_295[]  = {
    "unabon"
};

static const sead::SafeString cRes_296[]  = {
    "unabon"
};

static const sead::SafeString cRes_297[]  = {
    "unabon"
};

static const sead::SafeString cRes_298[]  = {
    "unabon"
};

static const sead::SafeString cRes_299[]  = {
    "KK"
};

static const sead::SafeString cRes_29A[]  = {
    "KK"
};

static const sead::SafeString cRes_29B[]  = {
    "KK"
};

static const sead::SafeString cRes_29D[]  = {
    "wanwan"
};

static const sead::SafeString cRes_29E[]  = {
    "poltergeist"
};

static const sead::SafeString cRes_29F[]  = {
    "poltergeist"
};

static const sead::SafeString cRes_2A0[]  = {
    "bakubaku"
};

static const sead::SafeString cRes_2A1[]  = {
    "bakubaku"
};

static const sead::SafeString cRes_2A2[]  = {
    "ibaramushi"
};

static const sead::SafeString cRes_2A3[]  = {
    "crow"
};

static const sead::SafeString cRes_2A4[]  = {
    "met_toge"
};

static const sead::SafeString cRes_2A5[]  = {
    "met_toge"
};

static const sead::SafeString cRes_Bun[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunW2[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunW3[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunW4[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunW5[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunW6[]  = {
    "bunbun"
};

static const sead::SafeString cRes_BunDemo[]  = {
    "kameck"
};

static const sead::SafeString cRes_BossKKDemo[]  = {
    "kameck",
    "KK"
};

static const sead::SafeString cRes_KoopaDemo[]  = {
    "koopaJr",
    "koopaJr_clown",
    "kameck"
};

static const sead::SafeString cRes_Larry[]  = {
    "larry",
    "boss_ef_attack"
};

static const sead::SafeString cRes_KokoopaSearchFire[]  = {
    "boss_ef_attack"
};

static const sead::SafeString cRes_Lemmy[]  = {
    "lemmy"
};

static const sead::SafeString cRes_Morton[]  = {
    "morton",
    "deka_sanbo",
    "ef_dekasanbo",
    "EF_MortonHammerBlur"
};

static const sead::SafeString cRes_MortonSanbo[]  = {
    "deka_sanbo",
    "ef_dekasanbo"
};

static const sead::SafeString cRes_MortonSanboParts[]  = {
    "deka_sanbo",
    "ef_dekasanbo"
};

static const sead::SafeString cRes_Wendy[]  = {
    "wendy"
};

static const sead::SafeString cRes_WendyRing[]  = {
    "wendy"
};

static const sead::SafeString cRes_Ludwig[]  = {
    "ludwig",
    "boss_ef_attack"
};

static const sead::SafeString cRes_LudwigAlterEgo[]  = {
    "ludwig"
};

static const sead::SafeString cRes_Iggy[]  = {
    "iggy",
    "woogan"
};

static const sead::SafeString cRes_Woogan[]  = {
    "woogan"
};

static const sead::SafeString cRes_Roy[]  = {
    "roy",
    "killer"
};

static const sead::SafeString cRes_RoyLiftWaki[]  = {
    "lift_han_hikousen"
};

static const sead::SafeString cRes_BossKK[]  = {
    "boss_KK"
};

static const sead::SafeString cRes_Kameck[]  = {
    "kameck",
    "ice_kameck",
    "kuribo",
    "nokonokoA",
    "bombhei",
    "choropoo",
    "wing",
    "kuriboMini"
};

static const sead::SafeString cRes_PeachFinalCastleKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown",
    "koopa_model"
};

static const sead::SafeString cRes_Koopa[]  = {
    "koopa",
    "koopa_model",
    "boss_ef_attack"
};

static const sead::SafeString cRes_KoopaFireWaki[]  = {
    "boss_ef_attack",
    "koopa_model"
};

static const sead::SafeString cRes_KoopaFire[]  = {
    "boss_ef_attack",
    "koopa_model"
};

static const sead::SafeString cRes_DemoKoopaJrClown[]  = {
    "koopaJr_clown",
    "kameck"
};

static const sead::SafeString cRes_DemoKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown",
    "kameck"
};

static const sead::SafeString cRes_BunDemoKameck[]  = {
    "kameck"
};

static const sead::SafeString cRes_KoopaDemoKameck[]  = {
    "kameck"
};

static const sead::SafeString cRes_BossKKDemoKameck[]  = {
    "kameck"
};

static const sead::SafeString cRes_BossKKDemoKK[]  = {
    "KK"
};

static const sead::SafeString cRes_FinalKoopaFire[]  = {
    "koopa_model"
};

static const sead::SafeString cRes_FinalKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown",
    "bombhei",
    "koopa_model"
};

static const sead::SafeString cRes_FinalBomhei[]  = {
    "bombhei"
};

static const sead::SafeString cRes_KokoopaShipLemmy[]  = {
    "ShipLemmy"
};

static const sead::SafeString cRes_KokoopaShipMorton[]  = {
    "ShipMorton"
};

static const sead::SafeString cRes_KokoopaShipLarry[]  = {
    "ShipLarry"
};

static const sead::SafeString cRes_KokoopaShipWendy[]  = {
    "ShipWendy"
};

static const sead::SafeString cRes_KokoopaShipIggy[]  = {
    "ShipIggy"
};

static const sead::SafeString cRes_KokoopaShipRoy[]  = {
    "ShipRoy"
};

static const sead::SafeString cRes_KokoopaShipLudwig[]  = {
    "ShipLudwig"
};

static const sead::SafeString cRes_Peach[]  = {
    "peach"
};

static const sead::SafeString cRes_2E0[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_2E3[]  = {
    "peach"
};

static const sead::SafeString cRes_2E4[]  = {
    "kanban_yajirushi"
};

static const sead::SafeString cRes_2E5[]  = {
    "kanban_yajirushi"
};

static const sead::SafeString cRes_2E6[]  = {
    "kanban_yajirushi"
};

static const sead::SafeString cRes_2E7[]  = {
    "R_kanban_1_1"
};

static const sead::SafeString cRes_2E8[]  = {
    "R_kanban_9_9"
};

static const sead::SafeString cRes_2EE[]  = {
    "red_ring"
};

static const sead::SafeString cRes_2EF[]  = {
    "green_ring"
};

static const sead::SafeString cRes_2F0[]  = {
    "red_ring",
    "star_coin"
};

static const sead::SafeString cRes_2F1[]  = {
    "R_blue_ring"
};

static const sead::SafeString cRes_2F2[]  = {
    "goal_odai"
};

static const sead::SafeString cRes_2F3[]  = {
    "fruit"
};

static const sead::SafeString cRes_2F4[]  = {
    "fruits_kusa",
    "fruits_kusa_gake"
};

static const sead::SafeString cRes_2F5[]  = {
    "bros"
};

static const sead::SafeString cRes_Hammer[]  = {
    "bros"
};

static const sead::SafeString cRes_2F7[]  = {
    "bros"
};

static const sead::SafeString cRes_Boomerang[]  = {
    "bros"
};

static const sead::SafeString cRes_2F9[]  = {
    "bros"
};

static const sead::SafeString cRes_2FB[]  = {
    "bros"
};

static const sead::SafeString cRes_2FD[]  = {
    "bros_mega"
};

static const sead::SafeString cRes_MegaHammer[]  = {
    "bros_mega"
};

static const sead::SafeString cRes_2FF[]  = {
    "bilikyu"
};

static const sead::SafeString cRes_300[]  = {
    "densen",
    "bilikyu"
};

static const sead::SafeString cRes_301[]  = {
    "densen"
};

static const sead::SafeString cRes_302[]  = {
    "bilikyu"
};

static const sead::SafeString cRes_303[]  = {
    "koton"
};

static const sead::SafeString cRes_304[]  = {
    "koton"
};

static const sead::SafeString cRes_305[]  = {
    "pakkun"
};

static const sead::SafeString cRes_306[]  = {
    "pakkun"
};

static const sead::SafeString cRes_307[]  = {
    "pakkun"
};

static const sead::SafeString cRes_308[]  = {
    "pakkun"
};

static const sead::SafeString cRes_309[]  = {
    "pakkun"
};

static const sead::SafeString cRes_30A[]  = {
    "obj_turara_rakka"
};

static const sead::SafeString cRes_30B[]  = {
    "obj_turara_kotei"
};

static const sead::SafeString cRes_30C[]  = {
    "teresa"
};

static const sead::SafeString cRes_30D[]  = {
    "teresa"
};

static const sead::SafeString cRes_30F[]  = {
    "teresa"
};

static const sead::SafeString cRes_310[]  = {
    "teresa"
};

static const sead::SafeString cRes_311[]  = {
    "huhu",
    "env_mist"
};

static const sead::SafeString cRes_312[]  = {
    "huhu",
    "env_mist"
};

static const sead::SafeString cRes_313[]  = {
    "env_mist"
};

static const sead::SafeString cRes_314[]  = {
    "env_mist"
};

static const sead::SafeString cRes_315[]  = {
    "env_mist"
};

static const sead::SafeString cRes_316[]  = {
    "env_underwater"
};

static const sead::SafeString cRes_317[]  = {
    "env_snow"
};

static const sead::SafeString cRes_318[]  = {
    "obj_magmadeco"
};

static const sead::SafeString cRes_31C[]  = {
    "I_musasabi"
};

static const sead::SafeString cRes_31D[]  = {
    "shinkai_light"
};

static const sead::SafeString cRes_31F[]  = {
    "big_shell"
};

static const sead::SafeString cRes_320[]  = {
    "lift_zen_yoko"
};

static const sead::SafeString cRes_321[]  = {
    "lift_huriko_yougan"
};

static const sead::SafeString cRes_322[]  = {
    "guru"
};

static const sead::SafeString cRes_323[]  = {
    "gesso"
};

static const sead::SafeString cRes_324[]  = {
    "gessoMini"
};

static const sead::SafeString cRes_325[]  = {
    "gesso",
    "gessoMini"
};

static const sead::SafeString cRes_326[]  = {
    "obj_nut"
};

static const sead::SafeString cRes_327[]  = {
    "treasure_box",
    "I_kinoko",
    "I_fireflower",
    "I_propeller",
    "I_penguin",
    "I_kinoko",
    "I_star",
    "I_iceflower",
    "I_yoshichibi_egg",
    "I_musasabi",
    "shadowkun"
};

static const sead::SafeString cRes_BattleItem[]  = {
    "I_kinoko",
    "I_fireflower",
    "I_propeller",
    "I_penguin",
    "I_kinoko",
    "I_star",
    "I_iceflower",
    "I_yoshichibi_egg",
    "I_musasabi"
};

static const sead::SafeString cRes_32A[]  = {
    "I_yoshi_egg"
};

static const sead::SafeString cRes_VsBattleItem[]  = {
    "I_kinoko",
    "I_fireflower",
    "I_propeller",
    "I_penguin",
    "I_kinoko",
    "I_star",
    "I_iceflower",
    "I_yoshichibi_egg",
    "I_musasabi"
};

static const sead::SafeString cRes_32C[]  = {
    "torpedo"
};

static const sead::SafeString cRes_32D[]  = {
    "torpedo"
};

static const sead::SafeString cRes_32F[]  = {
    "torpedo"
};

static const sead::SafeString cRes_330[]  = {
    "torpedo"
};

static const sead::SafeString cRes_331[]  = {
    "torpedo"
};

static const sead::SafeString cRes_KoopaJrFire[]  = {
    "boss_ef_attack"
};

static const sead::SafeString cRes_KoopaJrBall[]  = {
    "koopaJr_clown_b"
};

static const sead::SafeString cRes_UnderwaterKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown",
    "koopaJr_clown_m",
    "magic_hand"
};

static const sead::SafeString cRes_UnderwaterKoopaJrClown[]  = {
    "koopaJr_clown",
    "koopaJr_clown_m",
    "torpedo"
};

static const sead::SafeString cRes_UnderwaterKoopaJrRetreatPos[]  = {
    "block_broken"
};

static const sead::SafeString cRes_BoxingKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown",
    "koopaJr_clown_b",
    "bombhei",
    "boss_ef_attack"
};

static const sead::SafeString cRes_BoxingKoopaJrPostBattleDemo[]  = {
    "koopaJr",
    "koopaJr_clown",
    "magic_hand"
};

static const sead::SafeString cRes_BoxingKoopaJrClownPostBattleDemo[]  = {
    "koopaJr_clown"
};

static const sead::SafeString cRes_MiniGamePanelItem[]  = {
    "miniGame_shuffle",
    "R_miniGame_shuffle"
};

static const sead::SafeString cRes_SlotItem[]  = {
    "miniGame_slot"
};

static const sead::SafeString cRes_CoinmakiCannon[]  = {
    "miniGame_mochimaki"
};

static const sead::SafeString cRes_CoinmakiItem[]  = {
    "miniGame_mochimaki"
};

static const sead::SafeString cRes_MiniGameKinopio[]  = {
    "KinopioMdl",
    "CommonAnm",
    "KinopioAnm"
};

static const sead::SafeString cRes_33F[]  = {
    "obj_tsuru"
};

static const sead::SafeString cRes_340[]  = {
    "obj_dokan_joint"
};

static const sead::SafeString cRes_341[]  = {
    "obj_dokan_joint"
};

static const sead::SafeString cRes_342[]  = {
    "goal_kinoko_house"
};

static const sead::SafeString cRes_StaffCreditChibiYoshiABC[]  = {
    "YoshiChibi_TexBubble",
    "baloon_ABC"
};

static const sead::SafeString cRes_StaffCreditChibiYoshiBalloon[]  = {
    "YoshiChibi_TexBalloon"
};

static const sead::SafeString cRes_StaffCreditChibiYoshiBalloonCheer[]  = {
    "YoshiChibi_TexBalloon"
};

static const sead::SafeString cRes_StaffCreditChibiYoshiLight[]  = {
    "YoshiChibi_TexLight"
};

static const sead::SafeString cRes_StaffCreditChibiYoshiLightCheer[]  = {
    "YoshiChibi_TexLight"
};

static const sead::SafeString cRes_StaffCreditSoapABC[]  = {
    "baloon_ABC"
};

static const sead::SafeString cRes_StaffCreditSoapCoin[]  = {
    "balloon",
    "obj_coin"
};

static const sead::SafeString cRes_StaffCreditTottenKun[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_RealizeFeverStar[]  = {
    "I_star_DRC"
};

static const sead::SafeString cRes_Star[]  = {
    "I_star"
};

static const sead::SafeString cRes_CourseSelectPlayer[]  = {
    "MarioMdl",
    "CommonAnm"
};

static const sead::SafeString cRes_CourseSelectPlayer2PSub[]  = {
    "MarioMdl",
    "LuigiMdl",
    "KinopioMdl",
    "CommonAnm",
    "LuigiAnm",
    "KinopioAnm"
};

static const sead::SafeString cRes_CourseSelectChibiYoshi[]  = {
    "YoshiChibi_TexBalloon",
    "YoshiChibi_TexBubble"
};

static const sead::SafeString cRes_CourseSelectCastle[]  = {
    "cobCastle"
};

static const sead::SafeString cRes_CourseSelectToride[]  = {
    "cobToride"
};

static const sead::SafeString cRes_CourseSelectKinokoHouse1up[]  = {
    "cobKinoko1up"
};

static const sead::SafeString cRes_CourseSelectKinokoHouseShuffle[]  = {
    "cobKinokoShuffle"
};

static const sead::SafeString cRes_CourseSelectKinokoHouseSlot[]  = {
    "cobKinokoSlot"
};

static const sead::SafeString cRes_CourseSelectPeachGates1st[]  = {
    "cobPeachGates1st"
};

static const sead::SafeString cRes_CourseSelectPeachGates2nd[]  = {
    "cobPeachGates2nd"
};

static const sead::SafeString cRes_CourseSelectCoursePoint[]  = {
    "cobCourse",
    "cobRing",
    "cobStarCoin"
};

static const sead::SafeString cRes_CourseSelectWorldMoveDokan[]  = {
    "cobCannon"
};

static const sead::SafeString cRes_CourseSelectGhost[]  = {
    "cobGhost"
};

static const sead::SafeString cRes_CourseSelectW2Bros[]  = {
    "bros"
};

static const sead::SafeString cRes_CourseSelectShipW1[]  = {
    "cobShipLemmy"
};

static const sead::SafeString cRes_CourseSelectShipW2[]  = {
    "cobShipMorton"
};

static const sead::SafeString cRes_CourseSelectShipW3[]  = {
    "cobShipLarry"
};

static const sead::SafeString cRes_CourseSelectShipW4[]  = {
    "cobShipWendy"
};

static const sead::SafeString cRes_CourseSelectShipW5[]  = {
    "cobShipIggy"
};

static const sead::SafeString cRes_CourseSelectShipW6[]  = {
    "cobShipRoy"
};

static const sead::SafeString cRes_CourseSelectShipW7[]  = {
    "cobShipLudwig"
};

static const sead::SafeString cRes_CourseSelectShipW8[]  = {
    "cobShipKoopaJr",
    "magic_hand"
};

static const sead::SafeString cRes_CourseSelectShipW8Broken[]  = {
    "cobShipKoopaJrBoro",
    "cobShipKoopaJrJimen"
};

static const sead::SafeString cRes_CourseSelectSurrender[]  = {
    "cobSurrender"
};

static const sead::SafeString cRes_CourseSelectSwitchA[]  = {
    "cobSwitchA"
};

static const sead::SafeString cRes_CourseSelectSwitchB[]  = {
    "cobSwitchB"
};

static const sead::SafeString cRes_CourseSelectTeresa[]  = {
    "teresa"
};

static const sead::SafeString cRes_CourseSelectOpeningKameck[]  = {
    "kameck"
};

static const sead::SafeString cRes_CourseSelectTorideBoss[]  = {
    "kameck",
    "bunbun",
    "boss_KK"
};

static const sead::SafeString cRes_CourseSelectPakkun[]  = {
    "pakkun"
};

static const sead::SafeString cRes_CourseSelectShadowFirstDemoKinopio[]  = {
    "KinopioMdl",
    "KinopioAnm"
};

static const sead::SafeString cRes_CourseSelectTobiPuku[]  = {
    "pukupuku"
};

static const sead::SafeString cRes_CourseSelectChorobon[]  = {
    "chorobon",
    "block_pata"
};

static const sead::SafeString cRes_CourseSelectW7Item[]  = {
    "I_star",
    "I_kinoko",
    "I_fireflower",
    "I_iceflower",
    "I_musasabi",
    "block_pata"
};

static const sead::SafeString cRes_CourseSelectW5Teresa[]  = {
    "teresa"
};

static const sead::SafeString cRes_CourseSelectFlag[]  = {
    "cobFlagPeach",
    "cobFlagKoopa"
};

static const sead::SafeString cRes_CourseSelectMusasabi[]  = {
    "I_musasabi",
    "I_kinoko"
};

static const sead::SafeString cRes_CourseSelectWPillar[]  = {
    "cobWaterPillar"
};

static const sead::SafeString cRes_CourseSelectW7Bridge[]  = {
    "cobRainbowYoko",
    "cobRainbowTate"
};

static const sead::SafeString cRes_CourseSelectMiiBalloon[]  = {
    "obj_baloon_Mii"
};

static const sead::SafeString cRes_CourseSelectPenguin[]  = {
    "penguin2"
};

static const sead::SafeString cRes_CourseSelectW4Item[]  = {
    "I_iceflower",
    "I_kinoko"
};

static const sead::SafeString cRes_CourseSelectW2Kuribo[]  = {
    "kuribo"
};

static const sead::SafeString cRes_CourseSelectPakkunBig[]  = {
    "pakkun"
};

static const sead::SafeString cRes_CourseSelectShadowKunIcon[]  = {
    "balloon_shadowkun"
};

static const sead::SafeString cRes_CourseSelectDekaUnira[]  = {
    "unizoBig"
};

static const sead::SafeString cRes_CourseSelectTomb[]  = {
    "cobTomb"
};

static const sead::SafeString cRes_CourseSelectShadowFirstDemoShadowKun[]  = {
    "shadowkun"
};

static const sead::SafeString cRes_CourseSelectKotsuCoaster[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_CourseSelectKoopaJr[]  = {
    "koopaJr",
    "koopaJr_clown"
};

static const sead::SafeString cRes_CourseSelectPeach[]  = {
    "peach",
    "cobPeachWindow"
};

static const sead::SafeString cRes_CourseSelectW1Item[]  = {
    "I_musasabi"
};

static const sead::SafeString cRes_CourseSelectStarGate[]  = {
    "cobStarGate"
};

static const sead::SafeString cRes_38E[]  = {
    "I_fireflower",
    "miniGame_shuffle"
};

static const sead::SafeString cRes_38F[]  = {
    "kuribo"
};

// ------------------------------------------ ResNum ------------------------------------------ //

template <typename T, size_t N>
u8 (&_ResNumGetter(T(&)[N]))[N];
#define GetResNum(array) (sizeof(_ResNumGetter(array)))

const u8 ProfileInfo::cResNum[cProfileID_Max] = {
    0,                                                          // ProfileInfo::cProfileID_000
    0,                                                          // ProfileInfo::cProfileID_001
    0,                                                          // ProfileInfo::cProfileID_002
    0,                                                          // ProfileInfo::cProfileID_003
    0,                                                          // ProfileInfo::cProfileID_004
    0,                                                          // ProfileInfo::cProfileID_005
    0,                                                          // ProfileInfo::cProfileID_006
    0,                                                          // ProfileInfo::cProfileID_007
    0,                                                          // ProfileInfo::cProfileID_008
    0,                                                          // ProfileInfo::cProfileID_009
    0,                                                          // ProfileInfo::cProfileID_00A
    0,                                                          // ProfileInfo::cProfileID_00B
    0,                                                          // ProfileInfo::cProfileID_00C
    0,                                                          // ProfileInfo::cProfileID_00D
    0,                                                          // ProfileInfo::cProfileID_00E
    0,                                                          // ProfileInfo::cProfileID_00F
    0,                                                          // ProfileInfo::cProfileID_010
    0,                                                          // ProfileInfo::cProfileID_011
    0,                                                          // ProfileInfo::cProfileID_012
    0,                                                          // ProfileInfo::cProfileID_013
    0,                                                          // ProfileInfo::cProfileID_014
    GetResNum(cRes_015),                                        // ProfileInfo::cProfileID_015
    GetResNum(cRes_016),                                        // ProfileInfo::cProfileID_016
    GetResNum(cRes_017),                                        // ProfileInfo::cProfileID_017
    GetResNum(cRes_MiniGameMgr),                                // ProfileInfo::cProfileID_MiniGameMgr
    GetResNum(cRes_MiniGameMgrRDash),                           // ProfileInfo::cProfileID_MiniGameMgrRDash
    0,                                                          // ProfileInfo::cProfileID_ShuffleBlockMgr
    0,                                                          // ProfileInfo::cProfileID_SlotMgr
    0,                                                          // ProfileInfo::cProfileID_CoinmakiMgr
    0,                                                          // ProfileInfo::cProfileID_01D
    0,                                                          // ProfileInfo::cProfileID_01E
    0,                                                          // ProfileInfo::cProfileID_01F
    0,                                                          // ProfileInfo::cProfileID_020
    GetResNum(cRes_ShootingStar),                               // ProfileInfo::cProfileID_ShootingStar
    GetResNum(cRes_StaffRollMgr),                               // ProfileInfo::cProfileID_StaffRollMgr
    GetResNum(cRes_StaffRollMgrRDash),                          // ProfileInfo::cProfileID_StaffRollMgrRDash
    GetResNum(cRes_024),                                        // ProfileInfo::cProfileID_024
    0,                                                          // ProfileInfo::cProfileID_025
    GetResNum(cRes_026),                                        // ProfileInfo::cProfileID_026
    0,                                                          // ProfileInfo::cProfileID_027
    0,                                                          // ProfileInfo::cProfileID_028
    0,                                                          // ProfileInfo::cProfileID_029
    0,                                                          // ProfileInfo::cProfileID_02A
    GetResNum(cRes_02B),                                        // ProfileInfo::cProfileID_02B
    GetResNum(cRes_02C),                                        // ProfileInfo::cProfileID_02C
    GetResNum(cRes_02D),                                        // ProfileInfo::cProfileID_02D
    GetResNum(cRes_02E),                                        // ProfileInfo::cProfileID_02E
    0,                                                          // ProfileInfo::cProfileID_02F
    0,                                                          // ProfileInfo::cProfileID_030
    0,                                                          // ProfileInfo::cProfileID_031
    GetResNum(cRes_032),                                        // ProfileInfo::cProfileID_032
    GetResNum(cRes_033),                                        // ProfileInfo::cProfileID_033
    0,                                                          // ProfileInfo::cProfileID_ElasticKinokoParent
    GetResNum(cRes_FloorGyration),                              // ProfileInfo::cProfileID_FloorGyration
    GetResNum(cRes_036),                                        // ProfileInfo::cProfileID_036
    GetResNum(cRes_037),                                        // ProfileInfo::cProfileID_037
    GetResNum(cRes_038),                                        // ProfileInfo::cProfileID_038
    GetResNum(cRes_039),                                        // ProfileInfo::cProfileID_039
    GetResNum(cRes_03A),                                        // ProfileInfo::cProfileID_03A
    GetResNum(cRes_03B),                                        // ProfileInfo::cProfileID_03B
    GetResNum(cRes_PairObjChild),                               // ProfileInfo::cProfileID_PairObjChild
    GetResNum(cRes_03D),                                        // ProfileInfo::cProfileID_03D
    GetResNum(cRes_03E),                                        // ProfileInfo::cProfileID_03E
    GetResNum(cRes_03F),                                        // ProfileInfo::cProfileID_03F
    GetResNum(cRes_040),                                        // ProfileInfo::cProfileID_040
    GetResNum(cRes_041),                                        // ProfileInfo::cProfileID_041
    GetResNum(cRes_042),                                        // ProfileInfo::cProfileID_042
    GetResNum(cRes_043),                                        // ProfileInfo::cProfileID_043
    GetResNum(cRes_044),                                        // ProfileInfo::cProfileID_044
    GetResNum(cRes_045),                                        // ProfileInfo::cProfileID_045
    GetResNum(cRes_046),                                        // ProfileInfo::cProfileID_046
    GetResNum(cRes_047),                                        // ProfileInfo::cProfileID_047
    GetResNum(cRes_048),                                        // ProfileInfo::cProfileID_048
    GetResNum(cRes_049),                                        // ProfileInfo::cProfileID_049
    GetResNum(cRes_04A),                                        // ProfileInfo::cProfileID_04A
    GetResNum(cRes_04B),                                        // ProfileInfo::cProfileID_04B
    GetResNum(cRes_04C),                                        // ProfileInfo::cProfileID_04C
    GetResNum(cRes_KinokoLift),                                 // ProfileInfo::cProfileID_KinokoLift
    GetResNum(cRes_KinokoLiftColor),                            // ProfileInfo::cProfileID_KinokoLiftColor
    GetResNum(cRes_LiftZenStar),                                // ProfileInfo::cProfileID_LiftZenStar
    GetResNum(cRes_050),                                        // ProfileInfo::cProfileID_050
    GetResNum(cRes_051),                                        // ProfileInfo::cProfileID_051
    GetResNum(cRes_052),                                        // ProfileInfo::cProfileID_052
    GetResNum(cRes_053),                                        // ProfileInfo::cProfileID_053
    GetResNum(cRes_054),                                        // ProfileInfo::cProfileID_054
    GetResNum(cRes_055),                                        // ProfileInfo::cProfileID_055
    GetResNum(cRes_056),                                        // ProfileInfo::cProfileID_056
    GetResNum(cRes_057),                                        // ProfileInfo::cProfileID_057
    GetResNum(cRes_058),                                        // ProfileInfo::cProfileID_058
    GetResNum(cRes_059),                                        // ProfileInfo::cProfileID_059
    GetResNum(cRes_BgActorYukaMario),                           // ProfileInfo::cProfileID_BgActorYukaMario
    GetResNum(cRes_05B),                                        // ProfileInfo::cProfileID_05B
    GetResNum(cRes_05C),                                        // ProfileInfo::cProfileID_05C
    0,                                                          // ProfileInfo::cProfileID_05D
    0,                                                          // ProfileInfo::cProfileID_05E
    GetResNum(cRes_05F),                                        // ProfileInfo::cProfileID_05F
    GetResNum(cRes_060),                                        // ProfileInfo::cProfileID_060
    GetResNum(cRes_061),                                        // ProfileInfo::cProfileID_061
    GetResNum(cRes_062),                                        // ProfileInfo::cProfileID_062
    GetResNum(cRes_063),                                        // ProfileInfo::cProfileID_063
    GetResNum(cRes_064),                                        // ProfileInfo::cProfileID_064
    GetResNum(cRes_KillerHoudai),                               // ProfileInfo::cProfileID_KillerHoudai
    GetResNum(cRes_StretchKillerHoudai),                        // ProfileInfo::cProfileID_StretchKillerHoudai
    GetResNum(cRes_MagnumKillerHoudai),                         // ProfileInfo::cProfileID_MagnumKillerHoudai
    GetResNum(cRes_MagnumKillerHoudaiDown),                     // ProfileInfo::cProfileID_MagnumKillerHoudaiDown
    GetResNum(cRes_SearchKillerHoudai),                         // ProfileInfo::cProfileID_SearchKillerHoudai
    GetResNum(cRes_SearchMagnumKillerHoudai),                   // ProfileInfo::cProfileID_SearchMagnumKillerHoudai
    GetResNum(cRes_SearchMagnumKillerHoudaiDown),               // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDown
    GetResNum(cRes_MagnumKillerHoudaiRDash),                    // ProfileInfo::cProfileID_MagnumKillerHoudaiRDash
    GetResNum(cRes_MagnumKillerHoudaiDownRDash),                // ProfileInfo::cProfileID_MagnumKillerHoudaiDownRDash
    GetResNum(cRes_SearchMagnumKillerHoudaiRDash),              // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiRDash
    GetResNum(cRes_SearchMagnumKillerHoudaiDownRDash),          // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDownRDash
    GetResNum(cRes_070),                                        // ProfileInfo::cProfileID_070
    GetResNum(cRes_071),                                        // ProfileInfo::cProfileID_071
    GetResNum(cRes_072),                                        // ProfileInfo::cProfileID_072
    GetResNum(cRes_073),                                        // ProfileInfo::cProfileID_073
    GetResNum(cRes_074),                                        // ProfileInfo::cProfileID_074
    GetResNum(cRes_075),                                        // ProfileInfo::cProfileID_075
    GetResNum(cRes_076),                                        // ProfileInfo::cProfileID_076
    GetResNum(cRes_077),                                        // ProfileInfo::cProfileID_077
    0,                                                          // ProfileInfo::cProfileID_078
    GetResNum(cRes_Intermittent),                               // ProfileInfo::cProfileID_Intermittent
    GetResNum(cRes_IntermittentPermanent),                      // ProfileInfo::cProfileID_IntermittentPermanent
    GetResNum(cRes_WaterIntermittent),                          // ProfileInfo::cProfileID_WaterIntermittent
    GetResNum(cRes_WaterIntermittentPermanent),                 // ProfileInfo::cProfileID_WaterIntermittentPermanent
    GetResNum(cRes_WaterIntermittentPermanentRD3_3),            // ProfileInfo::cProfileID_WaterIntermittentPermanentRD3_3
    GetResNum(cRes_07E),                                        // ProfileInfo::cProfileID_07E
    GetResNum(cRes_WaterIntermittentBossChild),                 // ProfileInfo::cProfileID_WaterIntermittentBossChild
    GetResNum(cRes_YoganIntermittent),                          // ProfileInfo::cProfileID_YoganIntermittent
    GetResNum(cRes_081),                                        // ProfileInfo::cProfileID_081
    GetResNum(cRes_082),                                        // ProfileInfo::cProfileID_082
    GetResNum(cRes_083),                                        // ProfileInfo::cProfileID_083
    GetResNum(cRes_084),                                        // ProfileInfo::cProfileID_084
    GetResNum(cRes_085),                                        // ProfileInfo::cProfileID_085
    GetResNum(cRes_ObjPipeDownNG),                              // ProfileInfo::cProfileID_ObjPipeDownNG
    GetResNum(cRes_087),                                        // ProfileInfo::cProfileID_087
    GetResNum(cRes_088),                                        // ProfileInfo::cProfileID_088
    GetResNum(cRes_089),                                        // ProfileInfo::cProfileID_089
    GetResNum(cRes_08A),                                        // ProfileInfo::cProfileID_08A
    GetResNum(cRes_08B),                                        // ProfileInfo::cProfileID_08B
    GetResNum(cRes_08C),                                        // ProfileInfo::cProfileID_08C
    GetResNum(cRes_08D),                                        // ProfileInfo::cProfileID_08D
    GetResNum(cRes_08E),                                        // ProfileInfo::cProfileID_08E
    GetResNum(cRes_08F),                                        // ProfileInfo::cProfileID_08F
    GetResNum(cRes_090),                                        // ProfileInfo::cProfileID_090
    GetResNum(cRes_091),                                        // ProfileInfo::cProfileID_091
    GetResNum(cRes_092),                                        // ProfileInfo::cProfileID_092
    GetResNum(cRes_093),                                        // ProfileInfo::cProfileID_093
    GetResNum(cRes_094),                                        // ProfileInfo::cProfileID_094
    GetResNum(cRes_095),                                        // ProfileInfo::cProfileID_095
    GetResNum(cRes_096),                                        // ProfileInfo::cProfileID_096
    GetResNum(cRes_097),                                        // ProfileInfo::cProfileID_097
    GetResNum(cRes_098),                                        // ProfileInfo::cProfileID_098
    GetResNum(cRes_099),                                        // ProfileInfo::cProfileID_099
    0,                                                          // ProfileInfo::cProfileID_09A
    GetResNum(cRes_09B),                                        // ProfileInfo::cProfileID_09B
    GetResNum(cRes_09C),                                        // ProfileInfo::cProfileID_09C
    GetResNum(cRes_09D),                                        // ProfileInfo::cProfileID_09D
    GetResNum(cRes_09E),                                        // ProfileInfo::cProfileID_09E
    GetResNum(cRes_09F),                                        // ProfileInfo::cProfileID_09F
    GetResNum(cRes_0A0),                                        // ProfileInfo::cProfileID_0A0
    GetResNum(cRes_0A1),                                        // ProfileInfo::cProfileID_0A1
    GetResNum(cRes_0A2),                                        // ProfileInfo::cProfileID_0A2
    GetResNum(cRes_0A3),                                        // ProfileInfo::cProfileID_0A3
    GetResNum(cRes_0A4),                                        // ProfileInfo::cProfileID_0A4
    GetResNum(cRes_0A5),                                        // ProfileInfo::cProfileID_0A5
    GetResNum(cRes_0A6),                                        // ProfileInfo::cProfileID_0A6
    GetResNum(cRes_0A7),                                        // ProfileInfo::cProfileID_0A7
    GetResNum(cRes_0A8),                                        // ProfileInfo::cProfileID_0A8
    GetResNum(cRes_0A9),                                        // ProfileInfo::cProfileID_0A9
    GetResNum(cRes_0AA),                                        // ProfileInfo::cProfileID_0AA
    GetResNum(cRes_0AB),                                        // ProfileInfo::cProfileID_0AB
    GetResNum(cRes_0AC),                                        // ProfileInfo::cProfileID_0AC
    GetResNum(cRes_0AD),                                        // ProfileInfo::cProfileID_0AD
    GetResNum(cRes_0AE),                                        // ProfileInfo::cProfileID_0AE
    GetResNum(cRes_0AF),                                        // ProfileInfo::cProfileID_0AF
    GetResNum(cRes_0B0),                                        // ProfileInfo::cProfileID_0B0
    GetResNum(cRes_0B1),                                        // ProfileInfo::cProfileID_0B1
    GetResNum(cRes_0B2),                                        // ProfileInfo::cProfileID_0B2
    GetResNum(cRes_0B3),                                        // ProfileInfo::cProfileID_0B3
    GetResNum(cRes_0B4),                                        // ProfileInfo::cProfileID_0B4
    GetResNum(cRes_0B5),                                        // ProfileInfo::cProfileID_0B5
    GetResNum(cRes_0B6),                                        // ProfileInfo::cProfileID_0B6
    GetResNum(cRes_0B7),                                        // ProfileInfo::cProfileID_0B7
    GetResNum(cRes_LineSpinLift),                               // ProfileInfo::cProfileID_LineSpinLift
    GetResNum(cRes_LineSpinLiftParentRDash),                    // ProfileInfo::cProfileID_LineSpinLiftParentRDash
    GetResNum(cRes_LineSpinLiftChildRDash),                     // ProfileInfo::cProfileID_LineSpinLiftChildRDash
    GetResNum(cRes_0BB),                                        // ProfileInfo::cProfileID_0BB
    GetResNum(cRes_0BC),                                        // ProfileInfo::cProfileID_0BC
    GetResNum(cRes_0BD),                                        // ProfileInfo::cProfileID_0BD
    GetResNum(cRes_0BE),                                        // ProfileInfo::cProfileID_0BE
    GetResNum(cRes_0BF),                                        // ProfileInfo::cProfileID_0BF
    GetResNum(cRes_0C0),                                        // ProfileInfo::cProfileID_0C0
    GetResNum(cRes_0C1),                                        // ProfileInfo::cProfileID_0C1
    GetResNum(cRes_SnakeBlock),                                 // ProfileInfo::cProfileID_SnakeBlock
    GetResNum(cRes_0C3),                                        // ProfileInfo::cProfileID_0C3
    GetResNum(cRes_0C4),                                        // ProfileInfo::cProfileID_0C4
    GetResNum(cRes_0C5),                                        // ProfileInfo::cProfileID_0C5
    GetResNum(cRes_0C6),                                        // ProfileInfo::cProfileID_0C6
    GetResNum(cRes_0C7),                                        // ProfileInfo::cProfileID_0C7
    GetResNum(cRes_0C8),                                        // ProfileInfo::cProfileID_0C8
    GetResNum(cRes_0C9),                                        // ProfileInfo::cProfileID_0C9
    GetResNum(cRes_0CA),                                        // ProfileInfo::cProfileID_0CA
    GetResNum(cRes_0CB),                                        // ProfileInfo::cProfileID_0CB
    GetResNum(cRes_0CC),                                        // ProfileInfo::cProfileID_0CC
    GetResNum(cRes_0CD),                                        // ProfileInfo::cProfileID_0CD
    GetResNum(cRes_0CE),                                        // ProfileInfo::cProfileID_0CE
    GetResNum(cRes_0CF),                                        // ProfileInfo::cProfileID_0CF
    GetResNum(cRes_0D0),                                        // ProfileInfo::cProfileID_0D0
    GetResNum(cRes_0D1),                                        // ProfileInfo::cProfileID_0D1
    GetResNum(cRes_FloorHoleDokan),                             // ProfileInfo::cProfileID_FloorHoleDokan
    GetResNum(cRes_0D3),                                        // ProfileInfo::cProfileID_0D3
    GetResNum(cRes_0D4),                                        // ProfileInfo::cProfileID_0D4
    GetResNum(cRes_0D5),                                        // ProfileInfo::cProfileID_0D5
    GetResNum(cRes_0D6),                                        // ProfileInfo::cProfileID_0D6
    GetResNum(cRes_0D7),                                        // ProfileInfo::cProfileID_0D7
    GetResNum(cRes_0D8),                                        // ProfileInfo::cProfileID_0D8
    GetResNum(cRes_0D9),                                        // ProfileInfo::cProfileID_0D9
    GetResNum(cRes_0DA),                                        // ProfileInfo::cProfileID_0DA
    GetResNum(cRes_0DB),                                        // ProfileInfo::cProfileID_0DB
    GetResNum(cRes_0DC),                                        // ProfileInfo::cProfileID_0DC
    GetResNum(cRes_0DD),                                        // ProfileInfo::cProfileID_0DD
    GetResNum(cRes_0DE),                                        // ProfileInfo::cProfileID_0DE
    GetResNum(cRes_0DF),                                        // ProfileInfo::cProfileID_0DF
    GetResNum(cRes_Burner),                                     // ProfileInfo::cProfileID_Burner
    GetResNum(cRes_0E1),                                        // ProfileInfo::cProfileID_0E1
    GetResNum(cRes_0E2),                                        // ProfileInfo::cProfileID_0E2
    GetResNum(cRes_0E3),                                        // ProfileInfo::cProfileID_0E3
    GetResNum(cRes_0E4),                                        // ProfileInfo::cProfileID_0E4
    GetResNum(cRes_0E5),                                        // ProfileInfo::cProfileID_0E5
    GetResNum(cRes_0E6),                                        // ProfileInfo::cProfileID_0E6
    GetResNum(cRes_0E7),                                        // ProfileInfo::cProfileID_0E7
    GetResNum(cRes_0E8),                                        // ProfileInfo::cProfileID_0E8
    GetResNum(cRes_0E9),                                        // ProfileInfo::cProfileID_0E9
    GetResNum(cRes_0EA),                                        // ProfileInfo::cProfileID_0EA
    GetResNum(cRes_0EB),                                        // ProfileInfo::cProfileID_0EB
    GetResNum(cRes_0EC),                                        // ProfileInfo::cProfileID_0EC
    GetResNum(cRes_PlyIce),                                     // ProfileInfo::cProfileID_PlyIce
    GetResNum(cRes_TarzanIvy),                                  // ProfileInfo::cProfileID_TarzanIvy
    GetResNum(cRes_0EF),                                        // ProfileInfo::cProfileID_0EF
    GetResNum(cRes_0F0),                                        // ProfileInfo::cProfileID_0F0
    GetResNum(cRes_0F1),                                        // ProfileInfo::cProfileID_0F1
    GetResNum(cRes_0F2),                                        // ProfileInfo::cProfileID_0F2
    GetResNum(cRes_0F3),                                        // ProfileInfo::cProfileID_0F3
    GetResNum(cRes_0F4),                                        // ProfileInfo::cProfileID_0F4
    0,                                                          // ProfileInfo::cProfileID_0F5
    GetResNum(cRes_0F6),                                        // ProfileInfo::cProfileID_0F6
    GetResNum(cRes_0F7),                                        // ProfileInfo::cProfileID_0F7
    GetResNum(cRes_0F8),                                        // ProfileInfo::cProfileID_0F8
    GetResNum(cRes_0F9),                                        // ProfileInfo::cProfileID_0F9
    GetResNum(cRes_0FA),                                        // ProfileInfo::cProfileID_0FA
    GetResNum(cRes_0FB),                                        // ProfileInfo::cProfileID_0FB
    GetResNum(cRes_0FC),                                        // ProfileInfo::cProfileID_0FC
    GetResNum(cRes_0FD),                                        // ProfileInfo::cProfileID_0FD
    GetResNum(cRes_0FE),                                        // ProfileInfo::cProfileID_0FE
    GetResNum(cRes_0FF),                                        // ProfileInfo::cProfileID_0FF
    GetResNum(cRes_100),                                        // ProfileInfo::cProfileID_100
    GetResNum(cRes_101),                                        // ProfileInfo::cProfileID_101
    GetResNum(cRes_102),                                        // ProfileInfo::cProfileID_102
    GetResNum(cRes_103),                                        // ProfileInfo::cProfileID_103
    GetResNum(cRes_104),                                        // ProfileInfo::cProfileID_104
    GetResNum(cRes_ShuffleBlock),                               // ProfileInfo::cProfileID_ShuffleBlock
    GetResNum(cRes_KokoopaShipWarpCannon),                      // ProfileInfo::cProfileID_KokoopaShipWarpCannon
    GetResNum(cRes_107),                                        // ProfileInfo::cProfileID_107
    GetResNum(cRes_108),                                        // ProfileInfo::cProfileID_108
    GetResNum(cRes_KoopaShutter),                               // ProfileInfo::cProfileID_KoopaShutter
    GetResNum(cRes_10A),                                        // ProfileInfo::cProfileID_10A
    GetResNum(cRes_10B),                                        // ProfileInfo::cProfileID_10B
    GetResNum(cRes_10C),                                        // ProfileInfo::cProfileID_10C
    GetResNum(cRes_PeachFinalCastleKoopaJrLift),                // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLift
    GetResNum(cRes_PeachFinalCastleKoopaJrLiftHmove),           // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftHmove
    GetResNum(cRes_PeachFinalCastleKoopaJrLiftPairObj),         // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftPairObj
    GetResNum(cRes_RoyLiftWakiStep),                            // ProfileInfo::cProfileID_RoyLiftWakiStep
    GetResNum(cRes_WendyFloor),                                 // ProfileInfo::cProfileID_WendyFloor
    GetResNum(cRes_IggyRoom),                                   // ProfileInfo::cProfileID_IggyRoom
    GetResNum(cRes_113),                                        // ProfileInfo::cProfileID_113
    GetResNum(cRes_114),                                        // ProfileInfo::cProfileID_114
    GetResNum(cRes_115),                                        // ProfileInfo::cProfileID_115
    GetResNum(cRes_116),                                        // ProfileInfo::cProfileID_116
    0,                                                          // ProfileInfo::cProfileID_117
    GetResNum(cRes_118),                                        // ProfileInfo::cProfileID_118
    GetResNum(cRes_119),                                        // ProfileInfo::cProfileID_119
    GetResNum(cRes_11A),                                        // ProfileInfo::cProfileID_11A
    GetResNum(cRes_11B),                                        // ProfileInfo::cProfileID_11B
    0,                                                          // ProfileInfo::cProfileID_11C
    GetResNum(cRes_11D),                                        // ProfileInfo::cProfileID_11D
    GetResNum(cRes_11E),                                        // ProfileInfo::cProfileID_11E
    0,                                                          // ProfileInfo::cProfileID_Block
    0,                                                          // ProfileInfo::cProfileID_120
    0,                                                          // ProfileInfo::cProfileID_121
    0,                                                          // ProfileInfo::cProfileID_122
    0,                                                          // ProfileInfo::cProfileID_ActorBlockRenga
    0,                                                          // ProfileInfo::cProfileID_124
    0,                                                          // ProfileInfo::cProfileID_125
    0,                                                          // ProfileInfo::cProfileID_126
    0,                                                          // ProfileInfo::cProfileID_127
    0,                                                          // ProfileInfo::cProfileID_128
    0,                                                          // ProfileInfo::cProfileID_129
    0,                                                          // ProfileInfo::cProfileID_12A
    0,                                                          // ProfileInfo::cProfileID_12B
    0,                                                          // ProfileInfo::cProfileID_12C
    0,                                                          // ProfileInfo::cProfileID_12D
    0,                                                          // ProfileInfo::cProfileID_12E
    0,                                                          // ProfileInfo::cProfileID_12F
    0,                                                          // ProfileInfo::cProfileID_130
    0,                                                          // ProfileInfo::cProfileID_131
    0,                                                          // ProfileInfo::cProfileID_132
    0,                                                          // ProfileInfo::cProfileID_133
    0,                                                          // ProfileInfo::cProfileID_134
    GetResNum(cRes_ActorBlockMakeDRC),                          // ProfileInfo::cProfileID_ActorBlockMakeDRC
    GetResNum(cRes_136),                                        // ProfileInfo::cProfileID_136
    0,                                                          // ProfileInfo::cProfileID_137
    GetResNum(cRes_138),                                        // ProfileInfo::cProfileID_138
    0,                                                          // ProfileInfo::cProfileID_139
    GetResNum(cRes_13A),                                        // ProfileInfo::cProfileID_13A
    GetResNum(cRes_13B),                                        // ProfileInfo::cProfileID_13B
    GetResNum(cRes_13C),                                        // ProfileInfo::cProfileID_13C
    0,                                                          // ProfileInfo::cProfileID_13D
    0,                                                          // ProfileInfo::cProfileID_13E
    0,                                                          // ProfileInfo::cProfileID_13F
    GetResNum(cRes_140),                                        // ProfileInfo::cProfileID_140
    GetResNum(cRes_141),                                        // ProfileInfo::cProfileID_141
    GetResNum(cRes_142),                                        // ProfileInfo::cProfileID_142
    GetResNum(cRes_143),                                        // ProfileInfo::cProfileID_143
    GetResNum(cRes_144),                                        // ProfileInfo::cProfileID_144
    GetResNum(cRes_145),                                        // ProfileInfo::cProfileID_145
    GetResNum(cRes_146),                                        // ProfileInfo::cProfileID_146
    GetResNum(cRes_147),                                        // ProfileInfo::cProfileID_147
    GetResNum(cRes_148),                                        // ProfileInfo::cProfileID_148
    GetResNum(cRes_149),                                        // ProfileInfo::cProfileID_149
    GetResNum(cRes_14A),                                        // ProfileInfo::cProfileID_14A
    GetResNum(cRes_14B),                                        // ProfileInfo::cProfileID_14B
    0,                                                          // ProfileInfo::cProfileID_14C
    GetResNum(cRes_14D),                                        // ProfileInfo::cProfileID_14D
    GetResNum(cRes_14E),                                        // ProfileInfo::cProfileID_14E
    GetResNum(cRes_14F),                                        // ProfileInfo::cProfileID_14F
    GetResNum(cRes_ObjPipeDown),                                // ProfileInfo::cProfileID_ObjPipeDown
    GetResNum(cRes_151),                                        // ProfileInfo::cProfileID_151
    GetResNum(cRes_152),                                        // ProfileInfo::cProfileID_152
    GetResNum(cRes_153),                                        // ProfileInfo::cProfileID_153
    GetResNum(cRes_ObjPipeDownGroup),                           // ProfileInfo::cProfileID_ObjPipeDownGroup
    GetResNum(cRes_155),                                        // ProfileInfo::cProfileID_155
    GetResNum(cRes_156),                                        // ProfileInfo::cProfileID_156
    GetResNum(cRes_157),                                        // ProfileInfo::cProfileID_157
    GetResNum(cRes_SwitchHatenaButton),                         // ProfileInfo::cProfileID_SwitchHatenaButton
    GetResNum(cRes_SwitchPbutton),                              // ProfileInfo::cProfileID_SwitchPbutton
    GetResNum(cRes_SwitchPbuttonRDash),                         // ProfileInfo::cProfileID_SwitchPbuttonRDash
    GetResNum(cRes_SwitchPbuttonNoWallKick),                    // ProfileInfo::cProfileID_SwitchPbuttonNoWallKick
    0,                                                          // ProfileInfo::cProfileID_15C
    GetResNum(cRes_15D),                                        // ProfileInfo::cProfileID_15D
    GetResNum(cRes_IcicleBig),                                  // ProfileInfo::cProfileID_IcicleBig
    GetResNum(cRes_LemmyBall),                                  // ProfileInfo::cProfileID_LemmyBall
    GetResNum(cRes_LemmyBomb),                                  // ProfileInfo::cProfileID_LemmyBomb
    GetResNum(cRes_161),                                        // ProfileInfo::cProfileID_161
    0,                                                          // ProfileInfo::cProfileID_162
    GetResNum(cRes_163),                                        // ProfileInfo::cProfileID_163
    GetResNum(cRes_164),                                        // ProfileInfo::cProfileID_164
    GetResNum(cRes_165),                                        // ProfileInfo::cProfileID_165
    GetResNum(cRes_166),                                        // ProfileInfo::cProfileID_166
    GetResNum(cRes_167),                                        // ProfileInfo::cProfileID_167
    GetResNum(cRes_168),                                        // ProfileInfo::cProfileID_168
    GetResNum(cRes_169),                                        // ProfileInfo::cProfileID_169
    GetResNum(cRes_PentaroIce),                                 // ProfileInfo::cProfileID_PentaroIce
    GetResNum(cRes_16B),                                        // ProfileInfo::cProfileID_16B
    GetResNum(cRes_16C),                                        // ProfileInfo::cProfileID_16C
    GetResNum(cRes_16D),                                        // ProfileInfo::cProfileID_16D
    GetResNum(cRes_16E),                                        // ProfileInfo::cProfileID_16E
    GetResNum(cRes_16F),                                        // ProfileInfo::cProfileID_16F
    GetResNum(cRes_KameckIce),                                  // ProfileInfo::cProfileID_KameckIce
    GetResNum(cRes_WendyIcicle),                                // ProfileInfo::cProfileID_WendyIcicle
    GetResNum(cRes_PeachFinalCastleKoopaJrClown),               // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrClown
    GetResNum(cRes_BoxingKoopaJrClown),                         // ProfileInfo::cProfileID_BoxingKoopaJrClown
    GetResNum(cRes_174),                                        // ProfileInfo::cProfileID_174
    GetResNum(cRes_FinalKoopaJrClown),                          // ProfileInfo::cProfileID_FinalKoopaJrClown
    GetResNum(cRes_FinalKoopa),                                 // ProfileInfo::cProfileID_FinalKoopa
    GetResNum(cRes_FireBar),                                    // ProfileInfo::cProfileID_FireBar
    GetResNum(cRes_FireBarSync),                                // ProfileInfo::cProfileID_FireBarSync
    GetResNum(cRes_179),                                        // ProfileInfo::cProfileID_179
    GetResNum(cRes_17A),                                        // ProfileInfo::cProfileID_17A
    GetResNum(cRes_17B),                                        // ProfileInfo::cProfileID_17B
    0,                                                          // ProfileInfo::cProfileID_17C
    GetResNum(cRes_17D),                                        // ProfileInfo::cProfileID_17D
    GetResNum(cRes_17E),                                        // ProfileInfo::cProfileID_17E
    GetResNum(cRes_17F),                                        // ProfileInfo::cProfileID_17F
    GetResNum(cRes_180),                                        // ProfileInfo::cProfileID_180
    GetResNum(cRes_181),                                        // ProfileInfo::cProfileID_181
    GetResNum(cRes_182),                                        // ProfileInfo::cProfileID_182
    GetResNum(cRes_183),                                        // ProfileInfo::cProfileID_183
    GetResNum(cRes_184),                                        // ProfileInfo::cProfileID_184
    GetResNum(cRes_185),                                        // ProfileInfo::cProfileID_185
    GetResNum(cRes_186),                                        // ProfileInfo::cProfileID_186
    GetResNum(cRes_187),                                        // ProfileInfo::cProfileID_187
    GetResNum(cRes_188),                                        // ProfileInfo::cProfileID_188
    GetResNum(cRes_189),                                        // ProfileInfo::cProfileID_189
    GetResNum(cRes_18A),                                        // ProfileInfo::cProfileID_18A
    GetResNum(cRes_ActorCoin),                                  // ProfileInfo::cProfileID_ActorCoin
    GetResNum(cRes_18C),                                        // ProfileInfo::cProfileID_18C
    GetResNum(cRes_18D),                                        // ProfileInfo::cProfileID_18D
    GetResNum(cRes_18E),                                        // ProfileInfo::cProfileID_18E
    GetResNum(cRes_18F),                                        // ProfileInfo::cProfileID_18F
    GetResNum(cRes_190),                                        // ProfileInfo::cProfileID_190
    GetResNum(cRes_191),                                        // ProfileInfo::cProfileID_191
    GetResNum(cRes_192),                                        // ProfileInfo::cProfileID_192
    GetResNum(cRes_193),                                        // ProfileInfo::cProfileID_193
    GetResNum(cRes_194),                                        // ProfileInfo::cProfileID_194
    GetResNum(cRes_195),                                        // ProfileInfo::cProfileID_195
    GetResNum(cRes_196),                                        // ProfileInfo::cProfileID_196
    GetResNum(cRes_197),                                        // ProfileInfo::cProfileID_197
    GetResNum(cRes_198),                                        // ProfileInfo::cProfileID_198
    GetResNum(cRes_199),                                        // ProfileInfo::cProfileID_199
    GetResNum(cRes_19A),                                        // ProfileInfo::cProfileID_19A
    0,                                                          // ProfileInfo::cProfileID_19B
    GetResNum(cRes_19C),                                        // ProfileInfo::cProfileID_19C
    GetResNum(cRes_19D),                                        // ProfileInfo::cProfileID_19D
    0,                                                          // ProfileInfo::cProfileID_19E
    GetResNum(cRes_19F),                                        // ProfileInfo::cProfileID_19F
    GetResNum(cRes_1A0),                                        // ProfileInfo::cProfileID_1A0
    GetResNum(cRes_1A1),                                        // ProfileInfo::cProfileID_1A1
    0,                                                          // ProfileInfo::cProfileID_1A2
    GetResNum(cRes_1A3),                                        // ProfileInfo::cProfileID_1A3
    GetResNum(cRes_1A4),                                        // ProfileInfo::cProfileID_1A4
    GetResNum(cRes_1A5),                                        // ProfileInfo::cProfileID_1A5
    GetResNum(cRes_1A6),                                        // ProfileInfo::cProfileID_1A6
    GetResNum(cRes_1A7),                                        // ProfileInfo::cProfileID_1A7
    GetResNum(cRes_1A8),                                        // ProfileInfo::cProfileID_1A8
    GetResNum(cRes_BlueCoin),                                   // ProfileInfo::cProfileID_BlueCoin
    GetResNum(cRes_1AA),                                        // ProfileInfo::cProfileID_1AA
    GetResNum(cRes_1AB),                                        // ProfileInfo::cProfileID_1AB
    GetResNum(cRes_1AC),                                        // ProfileInfo::cProfileID_1AC
    GetResNum(cRes_1AD),                                        // ProfileInfo::cProfileID_1AD
    GetResNum(cRes_1AE),                                        // ProfileInfo::cProfileID_1AE
    GetResNum(cRes_1AF),                                        // ProfileInfo::cProfileID_1AF
    GetResNum(cRes_1B0),                                        // ProfileInfo::cProfileID_1B0
    GetResNum(cRes_1B1),                                        // ProfileInfo::cProfileID_1B1
    GetResNum(cRes_1B2),                                        // ProfileInfo::cProfileID_1B2
    GetResNum(cRes_1B3),                                        // ProfileInfo::cProfileID_1B3
    0,                                                          // ProfileInfo::cProfileID_1B4
    0,                                                          // ProfileInfo::cProfileID_1B5
    GetResNum(cRes_CoinmakiCoin),                               // ProfileInfo::cProfileID_CoinmakiCoin
    0,                                                          // ProfileInfo::cProfileID_1B7
    0,                                                          // ProfileInfo::cProfileID_1B8
    GetResNum(cRes_1B9),                                        // ProfileInfo::cProfileID_1B9
    GetResNum(cRes_Yoshi),                                      // ProfileInfo::cProfileID_Yoshi
    GetResNum(cRes_TottenPlayer),                               // ProfileInfo::cProfileID_TottenPlayer
    GetResNum(cRes_PlayerObject),                               // ProfileInfo::cProfileID_PlayerObject
    GetResNum(cRes_1BD),                                        // ProfileInfo::cProfileID_1BD
    GetResNum(cRes_1BE),                                        // ProfileInfo::cProfileID_1BE
    GetResNum(cRes_1BF),                                        // ProfileInfo::cProfileID_1BF
    GetResNum(cRes_1C0),                                        // ProfileInfo::cProfileID_1C0
    GetResNum(cRes_1C1),                                        // ProfileInfo::cProfileID_1C1
    GetResNum(cRes_1C2),                                        // ProfileInfo::cProfileID_1C2
    GetResNum(cRes_1C3),                                        // ProfileInfo::cProfileID_1C3
    0,                                                          // ProfileInfo::cProfileID_1C4
    GetResNum(cRes_SlotYoshiChibi),                             // ProfileInfo::cProfileID_SlotYoshiChibi
    GetResNum(cRes_1C6),                                        // ProfileInfo::cProfileID_1C6
    0,                                                          // ProfileInfo::cProfileID_1C7
    GetResNum(cRes_1C8),                                        // ProfileInfo::cProfileID_1C8
    0,                                                          // ProfileInfo::cProfileID_1C9
    0,                                                          // ProfileInfo::cProfileID_1CA
    GetResNum(cRes_1CB),                                        // ProfileInfo::cProfileID_1CB
    GetResNum(cRes_1CC),                                        // ProfileInfo::cProfileID_1CC
    0,                                                          // ProfileInfo::cProfileID_1CD
    GetResNum(cRes_1CE),                                        // ProfileInfo::cProfileID_1CE
    GetResNum(cRes_QuestPrizeItem),                             // ProfileInfo::cProfileID_QuestPrizeItem
    GetResNum(cRes_1D0),                                        // ProfileInfo::cProfileID_1D0
    GetResNum(cRes_1D1),                                        // ProfileInfo::cProfileID_1D1
    GetResNum(cRes_1D2),                                        // ProfileInfo::cProfileID_1D2
    GetResNum(cRes_1D3),                                        // ProfileInfo::cProfileID_1D3
    GetResNum(cRes_1D4),                                        // ProfileInfo::cProfileID_1D4
    GetResNum(cRes_1D5),                                        // ProfileInfo::cProfileID_1D5
    GetResNum(cRes_1D6),                                        // ProfileInfo::cProfileID_1D6
    GetResNum(cRes_1D7),                                        // ProfileInfo::cProfileID_1D7
    GetResNum(cRes_1D8),                                        // ProfileInfo::cProfileID_1D8
    GetResNum(cRes_1D9),                                        // ProfileInfo::cProfileID_1D9
    0,                                                          // ProfileInfo::cProfileID_IceBall
    0,                                                          // ProfileInfo::cProfileID_IceBallPakkun
    0,                                                          // ProfileInfo::cProfileID_FireBallPlayer
    0,                                                          // ProfileInfo::cProfileID_FireBallPakkun
    0,                                                          // ProfileInfo::cProfileID_YoshiFire
    GetResNum(cRes_1DF),                                        // ProfileInfo::cProfileID_1DF
    GetResNum(cRes_1E0),                                        // ProfileInfo::cProfileID_1E0
    GetResNum(cRes_1E1),                                        // ProfileInfo::cProfileID_1E1
    GetResNum(cRes_1E2),                                        // ProfileInfo::cProfileID_1E2
    GetResNum(cRes_1E3),                                        // ProfileInfo::cProfileID_1E3
    GetResNum(cRes_1E4),                                        // ProfileInfo::cProfileID_1E4
    GetResNum(cRes_1E5),                                        // ProfileInfo::cProfileID_1E5
    GetResNum(cRes_1E6),                                        // ProfileInfo::cProfileID_1E6
    GetResNum(cRes_1E7),                                        // ProfileInfo::cProfileID_1E7
    GetResNum(cRes_1E8),                                        // ProfileInfo::cProfileID_1E8
    GetResNum(cRes_1E9),                                        // ProfileInfo::cProfileID_1E9
    GetResNum(cRes_1EA),                                        // ProfileInfo::cProfileID_1EA
    GetResNum(cRes_1EB),                                        // ProfileInfo::cProfileID_1EB
    GetResNum(cRes_1EC),                                        // ProfileInfo::cProfileID_1EC
    GetResNum(cRes_1ED),                                        // ProfileInfo::cProfileID_1ED
    GetResNum(cRes_1EE),                                        // ProfileInfo::cProfileID_1EE
    GetResNum(cRes_1EF),                                        // ProfileInfo::cProfileID_1EF
    GetResNum(cRes_1F0),                                        // ProfileInfo::cProfileID_1F0
    GetResNum(cRes_1F1),                                        // ProfileInfo::cProfileID_1F1
    GetResNum(cRes_1F2),                                        // ProfileInfo::cProfileID_1F2
    GetResNum(cRes_1F3),                                        // ProfileInfo::cProfileID_1F3
    GetResNum(cRes_1F4),                                        // ProfileInfo::cProfileID_1F4
    GetResNum(cRes_1F5),                                        // ProfileInfo::cProfileID_1F5
    GetResNum(cRes_1F6),                                        // ProfileInfo::cProfileID_1F6
    GetResNum(cRes_1F7),                                        // ProfileInfo::cProfileID_1F7
    GetResNum(cRes_1F8),                                        // ProfileInfo::cProfileID_1F8
    GetResNum(cRes_1F9),                                        // ProfileInfo::cProfileID_1F9
    GetResNum(cRes_1FA),                                        // ProfileInfo::cProfileID_1FA
    GetResNum(cRes_1FB),                                        // ProfileInfo::cProfileID_1FB
    GetResNum(cRes_1FC),                                        // ProfileInfo::cProfileID_1FC
    GetResNum(cRes_1FD),                                        // ProfileInfo::cProfileID_1FD
    GetResNum(cRes_1FE),                                        // ProfileInfo::cProfileID_1FE
    0,                                                          // ProfileInfo::cProfileID_1FF
    GetResNum(cRes_Nokonoko),                                   // ProfileInfo::cProfileID_Nokonoko
    GetResNum(cRes_201),                                        // ProfileInfo::cProfileID_201
    GetResNum(cRes_202),                                        // ProfileInfo::cProfileID_202
    GetResNum(cRes_203),                                        // ProfileInfo::cProfileID_203
    GetResNum(cRes_204),                                        // ProfileInfo::cProfileID_204
    GetResNum(cRes_205),                                        // ProfileInfo::cProfileID_205
    GetResNum(cRes_206),                                        // ProfileInfo::cProfileID_206
    GetResNum(cRes_207),                                        // ProfileInfo::cProfileID_207
    GetResNum(cRes_208),                                        // ProfileInfo::cProfileID_208
    GetResNum(cRes_209),                                        // ProfileInfo::cProfileID_209
    GetResNum(cRes_20A),                                        // ProfileInfo::cProfileID_20A
    GetResNum(cRes_20B),                                        // ProfileInfo::cProfileID_20B
    GetResNum(cRes_MechaKoopa),                                 // ProfileInfo::cProfileID_MechaKoopa
    GetResNum(cRes_20D),                                        // ProfileInfo::cProfileID_20D
    GetResNum(cRes_20E),                                        // ProfileInfo::cProfileID_20E
    GetResNum(cRes_20F),                                        // ProfileInfo::cProfileID_20F
    GetResNum(cRes_210),                                        // ProfileInfo::cProfileID_210
    GetResNum(cRes_211),                                        // ProfileInfo::cProfileID_211
    GetResNum(cRes_212),                                        // ProfileInfo::cProfileID_212
    GetResNum(cRes_213),                                        // ProfileInfo::cProfileID_213
    GetResNum(cRes_214),                                        // ProfileInfo::cProfileID_214
    GetResNum(cRes_215),                                        // ProfileInfo::cProfileID_215
    GetResNum(cRes_216),                                        // ProfileInfo::cProfileID_216
    GetResNum(cRes_217),                                        // ProfileInfo::cProfileID_217
    GetResNum(cRes_218),                                        // ProfileInfo::cProfileID_218
    GetResNum(cRes_219),                                        // ProfileInfo::cProfileID_219
    GetResNum(cRes_21A),                                        // ProfileInfo::cProfileID_21A
    GetResNum(cRes_21B),                                        // ProfileInfo::cProfileID_21B
    GetResNum(cRes_21C),                                        // ProfileInfo::cProfileID_21C
    GetResNum(cRes_21D),                                        // ProfileInfo::cProfileID_21D
    GetResNum(cRes_21E),                                        // ProfileInfo::cProfileID_21E
    GetResNum(cRes_21F),                                        // ProfileInfo::cProfileID_21F
    GetResNum(cRes_220),                                        // ProfileInfo::cProfileID_220
    GetResNum(cRes_221),                                        // ProfileInfo::cProfileID_221
    GetResNum(cRes_222),                                        // ProfileInfo::cProfileID_222
    GetResNum(cRes_223),                                        // ProfileInfo::cProfileID_223
    GetResNum(cRes_224),                                        // ProfileInfo::cProfileID_224
    GetResNum(cRes_225),                                        // ProfileInfo::cProfileID_225
    GetResNum(cRes_226),                                        // ProfileInfo::cProfileID_226
    GetResNum(cRes_227),                                        // ProfileInfo::cProfileID_227
    GetResNum(cRes_228),                                        // ProfileInfo::cProfileID_228
    GetResNum(cRes_229),                                        // ProfileInfo::cProfileID_229
    GetResNum(cRes_22A),                                        // ProfileInfo::cProfileID_22A
    GetResNum(cRes_22B),                                        // ProfileInfo::cProfileID_22B
    GetResNum(cRes_22C),                                        // ProfileInfo::cProfileID_22C
    GetResNum(cRes_22D),                                        // ProfileInfo::cProfileID_22D
    0,                                                          // ProfileInfo::cProfileID_FireBallKeronpa
    0,                                                          // ProfileInfo::cProfileID_FireBallKeronpaRDash
    GetResNum(cRes_230),                                        // ProfileInfo::cProfileID_230
    GetResNum(cRes_FireSnake),                                  // ProfileInfo::cProfileID_FireSnake
    GetResNum(cRes_232),                                        // ProfileInfo::cProfileID_232
    GetResNum(cRes_233),                                        // ProfileInfo::cProfileID_233
    GetResNum(cRes_234),                                        // ProfileInfo::cProfileID_234
    GetResNum(cRes_235),                                        // ProfileInfo::cProfileID_235
    GetResNum(cRes_236),                                        // ProfileInfo::cProfileID_236
    GetResNum(cRes_237),                                        // ProfileInfo::cProfileID_237
    GetResNum(cRes_238),                                        // ProfileInfo::cProfileID_238
    GetResNum(cRes_239),                                        // ProfileInfo::cProfileID_239
    GetResNum(cRes_23A),                                        // ProfileInfo::cProfileID_23A
    GetResNum(cRes_23B),                                        // ProfileInfo::cProfileID_23B
    GetResNum(cRes_23C),                                        // ProfileInfo::cProfileID_23C
    GetResNum(cRes_23D),                                        // ProfileInfo::cProfileID_23D
    GetResNum(cRes_Kazandan),                                   // ProfileInfo::cProfileID_Kazandan
    0,                                                          // ProfileInfo::cProfileID_23F
    0,                                                          // ProfileInfo::cProfileID_240
    0,                                                          // ProfileInfo::cProfileID_241
    0,                                                          // ProfileInfo::cProfileID_242
    0,                                                          // ProfileInfo::cProfileID_243
    0,                                                          // ProfileInfo::cProfileID_244
    0,                                                          // ProfileInfo::cProfileID_245
    0,                                                          // ProfileInfo::cProfileID_246
    0,                                                          // ProfileInfo::cProfileID_247
    0,                                                          // ProfileInfo::cProfileID_248
    0,                                                          // ProfileInfo::cProfileID_249
    0,                                                          // ProfileInfo::cProfileID_24A
    0,                                                          // ProfileInfo::cProfileID_BgCenter
    0,                                                          // ProfileInfo::cProfileID_24C
    0,                                                          // ProfileInfo::cProfileID_24D
    0,                                                          // ProfileInfo::cProfileID_24E
    GetResNum(cRes_Kinoko),                                     // ProfileInfo::cProfileID_Kinoko
    GetResNum(cRes_FireFlower),                                 // ProfileInfo::cProfileID_FireFlower
    GetResNum(cRes_MameKinoko),                                 // ProfileInfo::cProfileID_MameKinoko
    GetResNum(cRes_IceFlower),                                  // ProfileInfo::cProfileID_IceFlower
    GetResNum(cRes_Propeller),                                  // ProfileInfo::cProfileID_Propeller
    GetResNum(cRes_Penguin),                                    // ProfileInfo::cProfileID_Penguin
    GetResNum(cRes_OneUpKinoko),                                // ProfileInfo::cProfileID_OneUpKinoko
    GetResNum(cRes_Musasabi),                                   // ProfileInfo::cProfileID_Musasabi
    GetResNum(cRes_SuperMoon),                                  // ProfileInfo::cProfileID_SuperMoon
    GetResNum(cRes_TitleDemoItem),                              // ProfileInfo::cProfileID_TitleDemoItem
    GetResNum(cRes_259),                                        // ProfileInfo::cProfileID_259
    GetResNum(cRes_25A),                                        // ProfileInfo::cProfileID_25A
    GetResNum(cRes_25B),                                        // ProfileInfo::cProfileID_25B
    GetResNum(cRes_25C),                                        // ProfileInfo::cProfileID_25C
    GetResNum(cRes_25D),                                        // ProfileInfo::cProfileID_25D
    GetResNum(cRes_25E),                                        // ProfileInfo::cProfileID_25E
    GetResNum(cRes_25F),                                        // ProfileInfo::cProfileID_25F
    GetResNum(cRes_260),                                        // ProfileInfo::cProfileID_260
    GetResNum(cRes_261),                                        // ProfileInfo::cProfileID_261
    GetResNum(cRes_262),                                        // ProfileInfo::cProfileID_262
    GetResNum(cRes_263),                                        // ProfileInfo::cProfileID_263
    GetResNum(cRes_264),                                        // ProfileInfo::cProfileID_264
    GetResNum(cRes_265),                                        // ProfileInfo::cProfileID_265
    GetResNum(cRes_266),                                        // ProfileInfo::cProfileID_266
    GetResNum(cRes_267),                                        // ProfileInfo::cProfileID_267
    GetResNum(cRes_268),                                        // ProfileInfo::cProfileID_268
    GetResNum(cRes_Spanner),                                    // ProfileInfo::cProfileID_Spanner
    GetResNum(cRes_26A),                                        // ProfileInfo::cProfileID_26A
    GetResNum(cRes_26B),                                        // ProfileInfo::cProfileID_26B
    GetResNum(cRes_26C),                                        // ProfileInfo::cProfileID_26C
    GetResNum(cRes_26D),                                        // ProfileInfo::cProfileID_26D
    GetResNum(cRes_26E),                                        // ProfileInfo::cProfileID_26E
    GetResNum(cRes_26F),                                        // ProfileInfo::cProfileID_26F
    GetResNum(cRes_270),                                        // ProfileInfo::cProfileID_270
    GetResNum(cRes_271),                                        // ProfileInfo::cProfileID_271
    GetResNum(cRes_272),                                        // ProfileInfo::cProfileID_272
    0,                                                          // ProfileInfo::cProfileID_273
    0,                                                          // ProfileInfo::cProfileID_274
    0,                                                          // ProfileInfo::cProfileID_275
    0,                                                          // ProfileInfo::cProfileID_SearchKiller
    0,                                                          // ProfileInfo::cProfileID_277
    GetResNum(cRes_278),                                        // ProfileInfo::cProfileID_278
    GetResNum(cRes_279),                                        // ProfileInfo::cProfileID_279
    GetResNum(cRes_WakiSearchMagKiller),                        // ProfileInfo::cProfileID_WakiSearchMagKiller
    GetResNum(cRes_27B),                                        // ProfileInfo::cProfileID_27B
    GetResNum(cRes_27C),                                        // ProfileInfo::cProfileID_27C
    GetResNum(cRes_27D),                                        // ProfileInfo::cProfileID_27D
    GetResNum(cRes_27E),                                        // ProfileInfo::cProfileID_27E
    GetResNum(cRes_27F),                                        // ProfileInfo::cProfileID_27F
    GetResNum(cRes_GabonRock),                                  // ProfileInfo::cProfileID_GabonRock
    GetResNum(cRes_281),                                        // ProfileInfo::cProfileID_281
    GetResNum(cRes_282),                                        // ProfileInfo::cProfileID_282
    GetResNum(cRes_RockGabonRock),                              // ProfileInfo::cProfileID_RockGabonRock
    GetResNum(cRes_284),                                        // ProfileInfo::cProfileID_284
    GetResNum(cRes_SeichanSnowBall),                            // ProfileInfo::cProfileID_SeichanSnowBall
    GetResNum(cRes_286),                                        // ProfileInfo::cProfileID_286
    GetResNum(cRes_287),                                        // ProfileInfo::cProfileID_287
    GetResNum(cRes_288),                                        // ProfileInfo::cProfileID_288
    GetResNum(cRes_289),                                        // ProfileInfo::cProfileID_289
    GetResNum(cRes_Woochan),                                    // ProfileInfo::cProfileID_Woochan
    GetResNum(cRes_28B),                                        // ProfileInfo::cProfileID_28B
    GetResNum(cRes_28C),                                        // ProfileInfo::cProfileID_28C
    GetResNum(cRes_28D),                                        // ProfileInfo::cProfileID_28D
    GetResNum(cRes_Bubble),                                     // ProfileInfo::cProfileID_Bubble
    GetResNum(cRes_BubbleSync),                                 // ProfileInfo::cProfileID_BubbleSync
    GetResNum(cRes_BubbleRDash),                                // ProfileInfo::cProfileID_BubbleRDash
    GetResNum(cRes_BubbleSyncRDash),                            // ProfileInfo::cProfileID_BubbleSyncRDash
    GetResNum(cRes_292),                                        // ProfileInfo::cProfileID_292
    GetResNum(cRes_293),                                        // ProfileInfo::cProfileID_293
    GetResNum(cRes_294),                                        // ProfileInfo::cProfileID_294
    GetResNum(cRes_295),                                        // ProfileInfo::cProfileID_295
    GetResNum(cRes_296),                                        // ProfileInfo::cProfileID_296
    GetResNum(cRes_297),                                        // ProfileInfo::cProfileID_297
    GetResNum(cRes_298),                                        // ProfileInfo::cProfileID_298
    GetResNum(cRes_299),                                        // ProfileInfo::cProfileID_299
    GetResNum(cRes_29A),                                        // ProfileInfo::cProfileID_29A
    GetResNum(cRes_29B),                                        // ProfileInfo::cProfileID_29B
    0,                                                          // ProfileInfo::cProfileID_29C
    GetResNum(cRes_29D),                                        // ProfileInfo::cProfileID_29D
    GetResNum(cRes_29E),                                        // ProfileInfo::cProfileID_29E
    GetResNum(cRes_29F),                                        // ProfileInfo::cProfileID_29F
    GetResNum(cRes_2A0),                                        // ProfileInfo::cProfileID_2A0
    GetResNum(cRes_2A1),                                        // ProfileInfo::cProfileID_2A1
    GetResNum(cRes_2A2),                                        // ProfileInfo::cProfileID_2A2
    GetResNum(cRes_2A3),                                        // ProfileInfo::cProfileID_2A3
    GetResNum(cRes_2A4),                                        // ProfileInfo::cProfileID_2A4
    GetResNum(cRes_2A5),                                        // ProfileInfo::cProfileID_2A5
    GetResNum(cRes_Bun),                                        // ProfileInfo::cProfileID_Bun
    GetResNum(cRes_BunW2),                                      // ProfileInfo::cProfileID_BunW2
    GetResNum(cRes_BunW3),                                      // ProfileInfo::cProfileID_BunW3
    GetResNum(cRes_BunW4),                                      // ProfileInfo::cProfileID_BunW4
    GetResNum(cRes_BunW5),                                      // ProfileInfo::cProfileID_BunW5
    GetResNum(cRes_BunW6),                                      // ProfileInfo::cProfileID_BunW6
    GetResNum(cRes_BunDemo),                                    // ProfileInfo::cProfileID_BunDemo
    0,                                                          // ProfileInfo::cProfileID_KokoopaDemo
    0,                                                          // ProfileInfo::cProfileID_KoopaJrDemo
    0,                                                          // ProfileInfo::cProfileID_KameckDemo
    GetResNum(cRes_BossKKDemo),                                 // ProfileInfo::cProfileID_BossKKDemo
    0,                                                          // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrDemo
    GetResNum(cRes_KoopaDemo),                                  // ProfileInfo::cProfileID_KoopaDemo
    0,                                                          // ProfileInfo::cProfileID_FinalKoopaDemo
    0,                                                          // ProfileInfo::cProfileID_PeachDemo
    GetResNum(cRes_Larry),                                      // ProfileInfo::cProfileID_Larry
    GetResNum(cRes_KokoopaSearchFire),                          // ProfileInfo::cProfileID_KokoopaSearchFire
    GetResNum(cRes_Lemmy),                                      // ProfileInfo::cProfileID_Lemmy
    GetResNum(cRes_Morton),                                     // ProfileInfo::cProfileID_Morton
    GetResNum(cRes_MortonSanbo),                                // ProfileInfo::cProfileID_MortonSanbo
    GetResNum(cRes_MortonSanboParts),                           // ProfileInfo::cProfileID_MortonSanboParts
    GetResNum(cRes_Wendy),                                      // ProfileInfo::cProfileID_Wendy
    GetResNum(cRes_WendyRing),                                  // ProfileInfo::cProfileID_WendyRing
    GetResNum(cRes_Ludwig),                                     // ProfileInfo::cProfileID_Ludwig
    GetResNum(cRes_LudwigAlterEgo),                             // ProfileInfo::cProfileID_LudwigAlterEgo
    GetResNum(cRes_Iggy),                                       // ProfileInfo::cProfileID_Iggy
    0,                                                          // ProfileInfo::cProfileID_IggyMagic
    GetResNum(cRes_Woogan),                                     // ProfileInfo::cProfileID_Woogan
    GetResNum(cRes_Roy),                                        // ProfileInfo::cProfileID_Roy
    GetResNum(cRes_RoyLiftWaki),                                // ProfileInfo::cProfileID_RoyLiftWaki
    GetResNum(cRes_BossKK),                                     // ProfileInfo::cProfileID_BossKK
    0,                                                          // ProfileInfo::cProfileID_BossKKThunder
    GetResNum(cRes_Kameck),                                     // ProfileInfo::cProfileID_Kameck
    0,                                                          // ProfileInfo::cProfileID_KameckIceConfig
    0,                                                          // ProfileInfo::cProfileID_KameckWarpPos
    0,                                                          // ProfileInfo::cProfileID_KameckMagic
    GetResNum(cRes_PeachFinalCastleKoopaJr),                    // ProfileInfo::cProfileID_PeachFinalCastleKoopaJr
    GetResNum(cRes_Koopa),                                      // ProfileInfo::cProfileID_Koopa
    GetResNum(cRes_KoopaFireWaki),                              // ProfileInfo::cProfileID_KoopaFireWaki
    GetResNum(cRes_KoopaFire),                                  // ProfileInfo::cProfileID_KoopaFire
    GetResNum(cRes_DemoKoopaJrClown),                           // ProfileInfo::cProfileID_DemoKoopaJrClown
    GetResNum(cRes_DemoKoopaJr),                                // ProfileInfo::cProfileID_DemoKoopaJr
    GetResNum(cRes_BunDemoKameck),                              // ProfileInfo::cProfileID_BunDemoKameck
    GetResNum(cRes_KoopaDemoKameck),                            // ProfileInfo::cProfileID_KoopaDemoKameck
    GetResNum(cRes_BossKKDemoKameck),                           // ProfileInfo::cProfileID_BossKKDemoKameck
    GetResNum(cRes_BossKKDemoKK),                               // ProfileInfo::cProfileID_BossKKDemoKK
    GetResNum(cRes_FinalKoopaFire),                             // ProfileInfo::cProfileID_FinalKoopaFire
    GetResNum(cRes_FinalKoopaJr),                               // ProfileInfo::cProfileID_FinalKoopaJr
    0,                                                          // ProfileInfo::cProfileID_FinalKoopaJrFire
    GetResNum(cRes_FinalBomhei),                                // ProfileInfo::cProfileID_FinalBomhei
    GetResNum(cRes_KokoopaShipLemmy),                           // ProfileInfo::cProfileID_KokoopaShipLemmy
    GetResNum(cRes_KokoopaShipMorton),                          // ProfileInfo::cProfileID_KokoopaShipMorton
    GetResNum(cRes_KokoopaShipLarry),                           // ProfileInfo::cProfileID_KokoopaShipLarry
    GetResNum(cRes_KokoopaShipWendy),                           // ProfileInfo::cProfileID_KokoopaShipWendy
    GetResNum(cRes_KokoopaShipIggy),                            // ProfileInfo::cProfileID_KokoopaShipIggy
    GetResNum(cRes_KokoopaShipRoy),                             // ProfileInfo::cProfileID_KokoopaShipRoy
    GetResNum(cRes_KokoopaShipLudwig),                          // ProfileInfo::cProfileID_KokoopaShipLudwig
    GetResNum(cRes_Peach),                                      // ProfileInfo::cProfileID_Peach
    GetResNum(cRes_2E0),                                        // ProfileInfo::cProfileID_2E0
    0,                                                          // ProfileInfo::cProfileID_FinalDVPeach
    0,                                                          // ProfileInfo::cProfileID_FinalDVShutter
    GetResNum(cRes_2E3),                                        // ProfileInfo::cProfileID_2E3
    GetResNum(cRes_2E4),                                        // ProfileInfo::cProfileID_2E4
    GetResNum(cRes_2E5),                                        // ProfileInfo::cProfileID_2E5
    GetResNum(cRes_2E6),                                        // ProfileInfo::cProfileID_2E6
    GetResNum(cRes_2E7),                                        // ProfileInfo::cProfileID_2E7
    GetResNum(cRes_2E8),                                        // ProfileInfo::cProfileID_2E8
    0,                                                          // ProfileInfo::cProfileID_2E9
    0,                                                          // ProfileInfo::cProfileID_2EA
    0,                                                          // ProfileInfo::cProfileID_2EB
    0,                                                          // ProfileInfo::cProfileID_2EC
    0,                                                          // ProfileInfo::cProfileID_2ED
    GetResNum(cRes_2EE),                                        // ProfileInfo::cProfileID_2EE
    GetResNum(cRes_2EF),                                        // ProfileInfo::cProfileID_2EF
    GetResNum(cRes_2F0),                                        // ProfileInfo::cProfileID_2F0
    GetResNum(cRes_2F1),                                        // ProfileInfo::cProfileID_2F1
    GetResNum(cRes_2F2),                                        // ProfileInfo::cProfileID_2F2
    GetResNum(cRes_2F3),                                        // ProfileInfo::cProfileID_2F3
    GetResNum(cRes_2F4),                                        // ProfileInfo::cProfileID_2F4
    GetResNum(cRes_2F5),                                        // ProfileInfo::cProfileID_2F5
    GetResNum(cRes_Hammer),                                     // ProfileInfo::cProfileID_Hammer
    GetResNum(cRes_2F7),                                        // ProfileInfo::cProfileID_2F7
    GetResNum(cRes_Boomerang),                                  // ProfileInfo::cProfileID_Boomerang
    GetResNum(cRes_2F9),                                        // ProfileInfo::cProfileID_2F9
    0,                                                          // ProfileInfo::cProfileID_FireBallBros
    GetResNum(cRes_2FB),                                        // ProfileInfo::cProfileID_2FB
    0,                                                          // ProfileInfo::cProfileID_IceBallBros
    GetResNum(cRes_2FD),                                        // ProfileInfo::cProfileID_2FD
    GetResNum(cRes_MegaHammer),                                 // ProfileInfo::cProfileID_MegaHammer
    GetResNum(cRes_2FF),                                        // ProfileInfo::cProfileID_2FF
    GetResNum(cRes_300),                                        // ProfileInfo::cProfileID_300
    GetResNum(cRes_301),                                        // ProfileInfo::cProfileID_301
    GetResNum(cRes_302),                                        // ProfileInfo::cProfileID_302
    GetResNum(cRes_303),                                        // ProfileInfo::cProfileID_303
    GetResNum(cRes_304),                                        // ProfileInfo::cProfileID_304
    GetResNum(cRes_305),                                        // ProfileInfo::cProfileID_305
    GetResNum(cRes_306),                                        // ProfileInfo::cProfileID_306
    GetResNum(cRes_307),                                        // ProfileInfo::cProfileID_307
    GetResNum(cRes_308),                                        // ProfileInfo::cProfileID_308
    GetResNum(cRes_309),                                        // ProfileInfo::cProfileID_309
    GetResNum(cRes_30A),                                        // ProfileInfo::cProfileID_30A
    GetResNum(cRes_30B),                                        // ProfileInfo::cProfileID_30B
    GetResNum(cRes_30C),                                        // ProfileInfo::cProfileID_30C
    GetResNum(cRes_30D),                                        // ProfileInfo::cProfileID_30D
    0,                                                          // ProfileInfo::cProfileID_30E
    GetResNum(cRes_30F),                                        // ProfileInfo::cProfileID_30F
    GetResNum(cRes_310),                                        // ProfileInfo::cProfileID_310
    GetResNum(cRes_311),                                        // ProfileInfo::cProfileID_311
    GetResNum(cRes_312),                                        // ProfileInfo::cProfileID_312
    GetResNum(cRes_313),                                        // ProfileInfo::cProfileID_313
    GetResNum(cRes_314),                                        // ProfileInfo::cProfileID_314
    GetResNum(cRes_315),                                        // ProfileInfo::cProfileID_315
    GetResNum(cRes_316),                                        // ProfileInfo::cProfileID_316
    GetResNum(cRes_317),                                        // ProfileInfo::cProfileID_317
    GetResNum(cRes_318),                                        // ProfileInfo::cProfileID_318
    0,                                                          // ProfileInfo::cProfileID_319
    0,                                                          // ProfileInfo::cProfileID_31A
    0,                                                          // ProfileInfo::cProfileID_31B
    GetResNum(cRes_31C),                                        // ProfileInfo::cProfileID_31C
    GetResNum(cRes_31D),                                        // ProfileInfo::cProfileID_31D
    0,                                                          // ProfileInfo::cProfileID_31E
    GetResNum(cRes_31F),                                        // ProfileInfo::cProfileID_31F
    GetResNum(cRes_320),                                        // ProfileInfo::cProfileID_320
    GetResNum(cRes_321),                                        // ProfileInfo::cProfileID_321
    GetResNum(cRes_322),                                        // ProfileInfo::cProfileID_322
    GetResNum(cRes_323),                                        // ProfileInfo::cProfileID_323
    GetResNum(cRes_324),                                        // ProfileInfo::cProfileID_324
    GetResNum(cRes_325),                                        // ProfileInfo::cProfileID_325
    GetResNum(cRes_326),                                        // ProfileInfo::cProfileID_326
    GetResNum(cRes_327),                                        // ProfileInfo::cProfileID_327
    0,                                                          // ProfileInfo::cProfileID_328
    GetResNum(cRes_BattleItem),                                 // ProfileInfo::cProfileID_BattleItem
    GetResNum(cRes_32A),                                        // ProfileInfo::cProfileID_32A
    GetResNum(cRes_VsBattleItem),                               // ProfileInfo::cProfileID_VsBattleItem
    GetResNum(cRes_32C),                                        // ProfileInfo::cProfileID_32C
    GetResNum(cRes_32D),                                        // ProfileInfo::cProfileID_32D
    0,                                                          // ProfileInfo::cProfileID_32E
    GetResNum(cRes_32F),                                        // ProfileInfo::cProfileID_32F
    GetResNum(cRes_330),                                        // ProfileInfo::cProfileID_330
    GetResNum(cRes_331),                                        // ProfileInfo::cProfileID_331
    GetResNum(cRes_KoopaJrFire),                                // ProfileInfo::cProfileID_KoopaJrFire
    GetResNum(cRes_KoopaJrBall),                                // ProfileInfo::cProfileID_KoopaJrBall
    GetResNum(cRes_UnderwaterKoopaJr),                          // ProfileInfo::cProfileID_UnderwaterKoopaJr
    GetResNum(cRes_UnderwaterKoopaJrClown),                     // ProfileInfo::cProfileID_UnderwaterKoopaJrClown
    GetResNum(cRes_UnderwaterKoopaJrRetreatPos),                // ProfileInfo::cProfileID_UnderwaterKoopaJrRetreatPos
    GetResNum(cRes_BoxingKoopaJr),                              // ProfileInfo::cProfileID_BoxingKoopaJr
    GetResNum(cRes_BoxingKoopaJrPostBattleDemo),                // ProfileInfo::cProfileID_BoxingKoopaJrPostBattleDemo
    GetResNum(cRes_BoxingKoopaJrClownPostBattleDemo),           // ProfileInfo::cProfileID_BoxingKoopaJrClownPostBattleDemo
    GetResNum(cRes_MiniGamePanelItem),                          // ProfileInfo::cProfileID_MiniGamePanelItem
    GetResNum(cRes_SlotItem),                                   // ProfileInfo::cProfileID_SlotItem
    GetResNum(cRes_CoinmakiCannon),                             // ProfileInfo::cProfileID_CoinmakiCannon
    GetResNum(cRes_CoinmakiItem),                               // ProfileInfo::cProfileID_CoinmakiItem
    GetResNum(cRes_MiniGameKinopio),                            // ProfileInfo::cProfileID_MiniGameKinopio
    GetResNum(cRes_33F),                                        // ProfileInfo::cProfileID_33F
    GetResNum(cRes_340),                                        // ProfileInfo::cProfileID_340
    GetResNum(cRes_341),                                        // ProfileInfo::cProfileID_341
    GetResNum(cRes_342),                                        // ProfileInfo::cProfileID_342
    0,                                                          // ProfileInfo::cProfileID_343
    0,                                                          // ProfileInfo::cProfileID_344
    0,                                                          // ProfileInfo::cProfileID_345
    0,                                                          // ProfileInfo::cProfileID_346
    0,                                                          // ProfileInfo::cProfileID_347
    GetResNum(cRes_StaffCreditChibiYoshiABC),                   // ProfileInfo::cProfileID_StaffCreditChibiYoshiABC
    GetResNum(cRes_StaffCreditChibiYoshiBalloon),               // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloon
    GetResNum(cRes_StaffCreditChibiYoshiBalloonCheer),          // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloonCheer
    GetResNum(cRes_StaffCreditChibiYoshiLight),                 // ProfileInfo::cProfileID_StaffCreditChibiYoshiLight
    GetResNum(cRes_StaffCreditChibiYoshiLightCheer),            // ProfileInfo::cProfileID_StaffCreditChibiYoshiLightCheer
    GetResNum(cRes_StaffCreditSoapABC),                         // ProfileInfo::cProfileID_StaffCreditSoapABC
    GetResNum(cRes_StaffCreditSoapCoin),                        // ProfileInfo::cProfileID_StaffCreditSoapCoin
    GetResNum(cRes_StaffCreditTottenKun),                       // ProfileInfo::cProfileID_StaffCreditTottenKun
    0,                                                          // ProfileInfo::cProfileID_350
    0,                                                          // ProfileInfo::cProfileID_351
    0,                                                          // ProfileInfo::cProfileID_352
    0,                                                          // ProfileInfo::cProfileID_353
    GetResNum(cRes_RealizeFeverStar),                           // ProfileInfo::cProfileID_RealizeFeverStar
    GetResNum(cRes_Star),                                       // ProfileInfo::cProfileID_Star
    GetResNum(cRes_CourseSelectPlayer),                         // ProfileInfo::cProfileID_CourseSelectPlayer
    GetResNum(cRes_CourseSelectPlayer2PSub),                    // ProfileInfo::cProfileID_CourseSelectPlayer2PSub
    GetResNum(cRes_CourseSelectChibiYoshi),                     // ProfileInfo::cProfileID_CourseSelectChibiYoshi
    0,                                                          // ProfileInfo::cProfileID_CourseSelectCamera
    GetResNum(cRes_CourseSelectCastle),                         // ProfileInfo::cProfileID_CourseSelectCastle
    GetResNum(cRes_CourseSelectToride),                         // ProfileInfo::cProfileID_CourseSelectToride
    GetResNum(cRes_CourseSelectKinokoHouse1up),                 // ProfileInfo::cProfileID_CourseSelectKinokoHouse1up
    GetResNum(cRes_CourseSelectKinokoHouseShuffle),             // ProfileInfo::cProfileID_CourseSelectKinokoHouseShuffle
    GetResNum(cRes_CourseSelectKinokoHouseSlot),                // ProfileInfo::cProfileID_CourseSelectKinokoHouseSlot
    GetResNum(cRes_CourseSelectPeachGates1st),                  // ProfileInfo::cProfileID_CourseSelectPeachGates1st
    GetResNum(cRes_CourseSelectPeachGates2nd),                  // ProfileInfo::cProfileID_CourseSelectPeachGates2nd
    GetResNum(cRes_CourseSelectCoursePoint),                    // ProfileInfo::cProfileID_CourseSelectCoursePoint
    GetResNum(cRes_CourseSelectWorldMoveDokan),                 // ProfileInfo::cProfileID_CourseSelectWorldMoveDokan
    0,                                                          // ProfileInfo::cProfileID_CourseSelectW8Cloud
    GetResNum(cRes_CourseSelectGhost),                          // ProfileInfo::cProfileID_CourseSelectGhost
    GetResNum(cRes_CourseSelectW2Bros),                         // ProfileInfo::cProfileID_CourseSelectW2Bros
    GetResNum(cRes_CourseSelectShipW1),                         // ProfileInfo::cProfileID_CourseSelectShipW1
    GetResNum(cRes_CourseSelectShipW2),                         // ProfileInfo::cProfileID_CourseSelectShipW2
    GetResNum(cRes_CourseSelectShipW3),                         // ProfileInfo::cProfileID_CourseSelectShipW3
    GetResNum(cRes_CourseSelectShipW4),                         // ProfileInfo::cProfileID_CourseSelectShipW4
    GetResNum(cRes_CourseSelectShipW5),                         // ProfileInfo::cProfileID_CourseSelectShipW5
    GetResNum(cRes_CourseSelectShipW6),                         // ProfileInfo::cProfileID_CourseSelectShipW6
    GetResNum(cRes_CourseSelectShipW7),                         // ProfileInfo::cProfileID_CourseSelectShipW7
    GetResNum(cRes_CourseSelectShipW8),                         // ProfileInfo::cProfileID_CourseSelectShipW8
    GetResNum(cRes_CourseSelectShipW8Broken),                   // ProfileInfo::cProfileID_CourseSelectShipW8Broken
    GetResNum(cRes_CourseSelectSurrender),                      // ProfileInfo::cProfileID_CourseSelectSurrender
    GetResNum(cRes_CourseSelectSwitchA),                        // ProfileInfo::cProfileID_CourseSelectSwitchA
    GetResNum(cRes_CourseSelectSwitchB),                        // ProfileInfo::cProfileID_CourseSelectSwitchB
    GetResNum(cRes_CourseSelectTeresa),                         // ProfileInfo::cProfileID_CourseSelectTeresa
    GetResNum(cRes_CourseSelectOpeningKameck),                  // ProfileInfo::cProfileID_CourseSelectOpeningKameck
    GetResNum(cRes_CourseSelectTorideBoss),                     // ProfileInfo::cProfileID_CourseSelectTorideBoss
    GetResNum(cRes_CourseSelectPakkun),                         // ProfileInfo::cProfileID_CourseSelectPakkun
    GetResNum(cRes_CourseSelectShadowFirstDemoKinopio),         // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoKinopio
    GetResNum(cRes_CourseSelectTobiPuku),                       // ProfileInfo::cProfileID_CourseSelectTobiPuku
    GetResNum(cRes_CourseSelectChorobon),                       // ProfileInfo::cProfileID_CourseSelectChorobon
    GetResNum(cRes_CourseSelectW7Item),                         // ProfileInfo::cProfileID_CourseSelectW7Item
    GetResNum(cRes_CourseSelectW5Teresa),                       // ProfileInfo::cProfileID_CourseSelectW5Teresa
    GetResNum(cRes_CourseSelectFlag),                           // ProfileInfo::cProfileID_CourseSelectFlag
    GetResNum(cRes_CourseSelectMusasabi),                       // ProfileInfo::cProfileID_CourseSelectMusasabi
    GetResNum(cRes_CourseSelectWPillar),                        // ProfileInfo::cProfileID_CourseSelectWPillar
    GetResNum(cRes_CourseSelectW7Bridge),                       // ProfileInfo::cProfileID_CourseSelectW7Bridge
    GetResNum(cRes_CourseSelectMiiBalloon),                     // ProfileInfo::cProfileID_CourseSelectMiiBalloon
    GetResNum(cRes_CourseSelectPenguin),                        // ProfileInfo::cProfileID_CourseSelectPenguin
    GetResNum(cRes_CourseSelectW4Item),                         // ProfileInfo::cProfileID_CourseSelectW4Item
    GetResNum(cRes_CourseSelectW2Kuribo),                       // ProfileInfo::cProfileID_CourseSelectW2Kuribo
    GetResNum(cRes_CourseSelectPakkunBig),                      // ProfileInfo::cProfileID_CourseSelectPakkunBig
    GetResNum(cRes_CourseSelectShadowKunIcon),                  // ProfileInfo::cProfileID_CourseSelectShadowKunIcon
    GetResNum(cRes_CourseSelectDekaUnira),                      // ProfileInfo::cProfileID_CourseSelectDekaUnira
    GetResNum(cRes_CourseSelectTomb),                           // ProfileInfo::cProfileID_CourseSelectTomb
    GetResNum(cRes_CourseSelectShadowFirstDemoShadowKun),       // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoShadowKun
    GetResNum(cRes_CourseSelectKotsuCoaster),                   // ProfileInfo::cProfileID_CourseSelectKotsuCoaster
    GetResNum(cRes_CourseSelectKoopaJr),                        // ProfileInfo::cProfileID_CourseSelectKoopaJr
    GetResNum(cRes_CourseSelectPeach),                          // ProfileInfo::cProfileID_CourseSelectPeach
    GetResNum(cRes_CourseSelectW1Item),                         // ProfileInfo::cProfileID_CourseSelectW1Item
    GetResNum(cRes_CourseSelectStarGate),                       // ProfileInfo::cProfileID_CourseSelectStarGate
    0,                                                          // ProfileInfo::cProfileID_CourseSelectEventAssistant
    GetResNum(cRes_38E),                                        // Profile 910
    GetResNum(cRes_38F),                                        // Profile 911
    0                                                           // Profile 912
};

// -----------------------------------------  ResList ----------------------------------------- //

const sead::SafeString* ProfileInfo::cResList[cProfileID_Max] = {
    nullptr,                                        // ProfileInfo::cProfileID_000
    nullptr,                                        // ProfileInfo::cProfileID_001
    nullptr,                                        // ProfileInfo::cProfileID_002
    nullptr,                                        // ProfileInfo::cProfileID_003
    nullptr,                                        // ProfileInfo::cProfileID_004
    nullptr,                                        // ProfileInfo::cProfileID_005
    nullptr,                                        // ProfileInfo::cProfileID_006
    nullptr,                                        // ProfileInfo::cProfileID_007
    nullptr,                                        // ProfileInfo::cProfileID_008
    nullptr,                                        // ProfileInfo::cProfileID_009
    nullptr,                                        // ProfileInfo::cProfileID_00A
    nullptr,                                        // ProfileInfo::cProfileID_00B
    nullptr,                                        // ProfileInfo::cProfileID_00C
    nullptr,                                        // ProfileInfo::cProfileID_00D
    nullptr,                                        // ProfileInfo::cProfileID_00E
    nullptr,                                        // ProfileInfo::cProfileID_00F
    nullptr,                                        // ProfileInfo::cProfileID_010
    nullptr,                                        // ProfileInfo::cProfileID_011
    nullptr,                                        // ProfileInfo::cProfileID_012
    nullptr,                                        // ProfileInfo::cProfileID_013
    nullptr,                                        // ProfileInfo::cProfileID_014
    cRes_015,                                       // ProfileInfo::cProfileID_015
    cRes_016,                                       // ProfileInfo::cProfileID_016
    cRes_017,                                       // ProfileInfo::cProfileID_017
    cRes_MiniGameMgr,                               // ProfileInfo::cProfileID_MiniGameMgr
    cRes_MiniGameMgrRDash,                          // ProfileInfo::cProfileID_MiniGameMgrRDash
    nullptr,                                        // ProfileInfo::cProfileID_ShuffleBlockMgr
    nullptr,                                        // ProfileInfo::cProfileID_SlotMgr
    nullptr,                                        // ProfileInfo::cProfileID_CoinmakiMgr
    nullptr,                                        // ProfileInfo::cProfileID_01D
    nullptr,                                        // ProfileInfo::cProfileID_01E
    nullptr,                                        // ProfileInfo::cProfileID_01F
    nullptr,                                        // ProfileInfo::cProfileID_020
    cRes_ShootingStar,                              // ProfileInfo::cProfileID_ShootingStar
    cRes_StaffRollMgr,                              // ProfileInfo::cProfileID_StaffRollMgr
    cRes_StaffRollMgrRDash,                         // ProfileInfo::cProfileID_StaffRollMgrRDash
    cRes_024,                                       // ProfileInfo::cProfileID_024
    nullptr,                                        // ProfileInfo::cProfileID_025
    cRes_026,                                       // ProfileInfo::cProfileID_026
    nullptr,                                        // ProfileInfo::cProfileID_027
    nullptr,                                        // ProfileInfo::cProfileID_028
    nullptr,                                        // ProfileInfo::cProfileID_029
    nullptr,                                        // ProfileInfo::cProfileID_02A
    cRes_02B,                                       // ProfileInfo::cProfileID_02B
    cRes_02C,                                       // ProfileInfo::cProfileID_02C
    cRes_02D,                                       // ProfileInfo::cProfileID_02D
    cRes_02E,                                       // ProfileInfo::cProfileID_02E
    nullptr,                                        // ProfileInfo::cProfileID_02F
    nullptr,                                        // ProfileInfo::cProfileID_030
    nullptr,                                        // ProfileInfo::cProfileID_031
    cRes_032,                                       // ProfileInfo::cProfileID_032
    cRes_033,                                       // ProfileInfo::cProfileID_033
    nullptr,                                        // ProfileInfo::cProfileID_ElasticKinokoParent
    cRes_FloorGyration,                             // ProfileInfo::cProfileID_FloorGyration
    cRes_036,                                       // ProfileInfo::cProfileID_036
    cRes_037,                                       // ProfileInfo::cProfileID_037
    cRes_038,                                       // ProfileInfo::cProfileID_038
    cRes_039,                                       // ProfileInfo::cProfileID_039
    cRes_03A,                                       // ProfileInfo::cProfileID_03A
    cRes_03B,                                       // ProfileInfo::cProfileID_03B
    cRes_PairObjChild,                              // ProfileInfo::cProfileID_PairObjChild
    cRes_03D,                                       // ProfileInfo::cProfileID_03D
    cRes_03E,                                       // ProfileInfo::cProfileID_03E
    cRes_03F,                                       // ProfileInfo::cProfileID_03F
    cRes_040,                                       // ProfileInfo::cProfileID_040
    cRes_041,                                       // ProfileInfo::cProfileID_041
    cRes_042,                                       // ProfileInfo::cProfileID_042
    cRes_043,                                       // ProfileInfo::cProfileID_043
    cRes_044,                                       // ProfileInfo::cProfileID_044
    cRes_045,                                       // ProfileInfo::cProfileID_045
    cRes_046,                                       // ProfileInfo::cProfileID_046
    cRes_047,                                       // ProfileInfo::cProfileID_047
    cRes_048,                                       // ProfileInfo::cProfileID_048
    cRes_049,                                       // ProfileInfo::cProfileID_049
    cRes_04A,                                       // ProfileInfo::cProfileID_04A
    cRes_04B,                                       // ProfileInfo::cProfileID_04B
    cRes_04C,                                       // ProfileInfo::cProfileID_04C
    cRes_KinokoLift,                                // ProfileInfo::cProfileID_KinokoLift
    cRes_KinokoLiftColor,                           // ProfileInfo::cProfileID_KinokoLiftColor
    cRes_LiftZenStar,                               // ProfileInfo::cProfileID_LiftZenStar
    cRes_050,                                       // ProfileInfo::cProfileID_050
    cRes_051,                                       // ProfileInfo::cProfileID_051
    cRes_052,                                       // ProfileInfo::cProfileID_052
    cRes_053,                                       // ProfileInfo::cProfileID_053
    cRes_054,                                       // ProfileInfo::cProfileID_054
    cRes_055,                                       // ProfileInfo::cProfileID_055
    cRes_056,                                       // ProfileInfo::cProfileID_056
    cRes_057,                                       // ProfileInfo::cProfileID_057
    cRes_058,                                       // ProfileInfo::cProfileID_058
    cRes_059,                                       // ProfileInfo::cProfileID_059
    cRes_BgActorYukaMario,                          // ProfileInfo::cProfileID_BgActorYukaMario
    cRes_05B,                                       // ProfileInfo::cProfileID_05B
    cRes_05C,                                       // ProfileInfo::cProfileID_05C
    nullptr,                                        // ProfileInfo::cProfileID_05D
    nullptr,                                        // ProfileInfo::cProfileID_05E
    cRes_05F,                                       // ProfileInfo::cProfileID_05F
    cRes_060,                                       // ProfileInfo::cProfileID_060
    cRes_061,                                       // ProfileInfo::cProfileID_061
    cRes_062,                                       // ProfileInfo::cProfileID_062
    cRes_063,                                       // ProfileInfo::cProfileID_063
    cRes_064,                                       // ProfileInfo::cProfileID_064
    cRes_KillerHoudai,                              // ProfileInfo::cProfileID_KillerHoudai
    cRes_StretchKillerHoudai,                       // ProfileInfo::cProfileID_StretchKillerHoudai
    cRes_MagnumKillerHoudai,                        // ProfileInfo::cProfileID_MagnumKillerHoudai
    cRes_MagnumKillerHoudaiDown,                    // ProfileInfo::cProfileID_MagnumKillerHoudaiDown
    cRes_SearchKillerHoudai,                        // ProfileInfo::cProfileID_SearchKillerHoudai
    cRes_SearchMagnumKillerHoudai,                  // ProfileInfo::cProfileID_SearchMagnumKillerHoudai
    cRes_SearchMagnumKillerHoudaiDown,              // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDown
    cRes_MagnumKillerHoudaiRDash,                   // ProfileInfo::cProfileID_MagnumKillerHoudaiRDash
    cRes_MagnumKillerHoudaiDownRDash,               // ProfileInfo::cProfileID_MagnumKillerHoudaiDownRDash
    cRes_SearchMagnumKillerHoudaiRDash,             // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiRDash
    cRes_SearchMagnumKillerHoudaiDownRDash,         // ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDownRDash
    cRes_070,                                       // ProfileInfo::cProfileID_070
    cRes_071,                                       // ProfileInfo::cProfileID_071
    cRes_072,                                       // ProfileInfo::cProfileID_072
    cRes_073,                                       // ProfileInfo::cProfileID_073
    cRes_074,                                       // ProfileInfo::cProfileID_074
    cRes_075,                                       // ProfileInfo::cProfileID_075
    cRes_076,                                       // ProfileInfo::cProfileID_076
    cRes_077,                                       // ProfileInfo::cProfileID_077
    nullptr,                                        // ProfileInfo::cProfileID_078
    cRes_Intermittent,                              // ProfileInfo::cProfileID_Intermittent
    cRes_IntermittentPermanent,                     // ProfileInfo::cProfileID_IntermittentPermanent
    cRes_WaterIntermittent,                         // ProfileInfo::cProfileID_WaterIntermittent
    cRes_WaterIntermittentPermanent,                // ProfileInfo::cProfileID_WaterIntermittentPermanent
    cRes_WaterIntermittentPermanentRD3_3,           // ProfileInfo::cProfileID_WaterIntermittentPermanentRD3_3
    cRes_07E,                                       // ProfileInfo::cProfileID_07E
    cRes_WaterIntermittentBossChild,                // ProfileInfo::cProfileID_WaterIntermittentBossChild
    cRes_YoganIntermittent,                         // ProfileInfo::cProfileID_YoganIntermittent
    cRes_081,                                       // ProfileInfo::cProfileID_081
    cRes_082,                                       // ProfileInfo::cProfileID_082
    cRes_083,                                       // ProfileInfo::cProfileID_083
    cRes_084,                                       // ProfileInfo::cProfileID_084
    cRes_085,                                       // ProfileInfo::cProfileID_085
    cRes_ObjPipeDownNG,                             // ProfileInfo::cProfileID_ObjPipeDownNG
    cRes_087,                                       // ProfileInfo::cProfileID_087
    cRes_088,                                       // ProfileInfo::cProfileID_088
    cRes_089,                                       // ProfileInfo::cProfileID_089
    cRes_08A,                                       // ProfileInfo::cProfileID_08A
    cRes_08B,                                       // ProfileInfo::cProfileID_08B
    cRes_08C,                                       // ProfileInfo::cProfileID_08C
    cRes_08D,                                       // ProfileInfo::cProfileID_08D
    cRes_08E,                                       // ProfileInfo::cProfileID_08E
    cRes_08F,                                       // ProfileInfo::cProfileID_08F
    cRes_090,                                       // ProfileInfo::cProfileID_090
    cRes_091,                                       // ProfileInfo::cProfileID_091
    cRes_092,                                       // ProfileInfo::cProfileID_092
    cRes_093,                                       // ProfileInfo::cProfileID_093
    cRes_094,                                       // ProfileInfo::cProfileID_094
    cRes_095,                                       // ProfileInfo::cProfileID_095
    cRes_096,                                       // ProfileInfo::cProfileID_096
    cRes_097,                                       // ProfileInfo::cProfileID_097
    cRes_098,                                       // ProfileInfo::cProfileID_098
    cRes_099,                                       // ProfileInfo::cProfileID_099
    nullptr,                                        // ProfileInfo::cProfileID_09A
    cRes_09B,                                       // ProfileInfo::cProfileID_09B
    cRes_09C,                                       // ProfileInfo::cProfileID_09C
    cRes_09D,                                       // ProfileInfo::cProfileID_09D
    cRes_09E,                                       // ProfileInfo::cProfileID_09E
    cRes_09F,                                       // ProfileInfo::cProfileID_09F
    cRes_0A0,                                       // ProfileInfo::cProfileID_0A0
    cRes_0A1,                                       // ProfileInfo::cProfileID_0A1
    cRes_0A2,                                       // ProfileInfo::cProfileID_0A2
    cRes_0A3,                                       // ProfileInfo::cProfileID_0A3
    cRes_0A4,                                       // ProfileInfo::cProfileID_0A4
    cRes_0A5,                                       // ProfileInfo::cProfileID_0A5
    cRes_0A6,                                       // ProfileInfo::cProfileID_0A6
    cRes_0A7,                                       // ProfileInfo::cProfileID_0A7
    cRes_0A8,                                       // ProfileInfo::cProfileID_0A8
    cRes_0A9,                                       // ProfileInfo::cProfileID_0A9
    cRes_0AA,                                       // ProfileInfo::cProfileID_0AA
    cRes_0AB,                                       // ProfileInfo::cProfileID_0AB
    cRes_0AC,                                       // ProfileInfo::cProfileID_0AC
    cRes_0AD,                                       // ProfileInfo::cProfileID_0AD
    cRes_0AE,                                       // ProfileInfo::cProfileID_0AE
    cRes_0AF,                                       // ProfileInfo::cProfileID_0AF
    cRes_0B0,                                       // ProfileInfo::cProfileID_0B0
    cRes_0B1,                                       // ProfileInfo::cProfileID_0B1
    cRes_0B2,                                       // ProfileInfo::cProfileID_0B2
    cRes_0B3,                                       // ProfileInfo::cProfileID_0B3
    cRes_0B4,                                       // ProfileInfo::cProfileID_0B4
    cRes_0B5,                                       // ProfileInfo::cProfileID_0B5
    cRes_0B6,                                       // ProfileInfo::cProfileID_0B6
    cRes_0B7,                                       // ProfileInfo::cProfileID_0B7
    cRes_LineSpinLift,                              // ProfileInfo::cProfileID_LineSpinLift
    cRes_LineSpinLiftParentRDash,                   // ProfileInfo::cProfileID_LineSpinLiftParentRDash
    cRes_LineSpinLiftChildRDash,                    // ProfileInfo::cProfileID_LineSpinLiftChildRDash
    cRes_0BB,                                       // ProfileInfo::cProfileID_0BB
    cRes_0BC,                                       // ProfileInfo::cProfileID_0BC
    cRes_0BD,                                       // ProfileInfo::cProfileID_0BD
    cRes_0BE,                                       // ProfileInfo::cProfileID_0BE
    cRes_0BF,                                       // ProfileInfo::cProfileID_0BF
    cRes_0C0,                                       // ProfileInfo::cProfileID_0C0
    cRes_0C1,                                       // ProfileInfo::cProfileID_0C1
    cRes_SnakeBlock,                                // ProfileInfo::cProfileID_SnakeBlock
    cRes_0C3,                                       // ProfileInfo::cProfileID_0C3
    cRes_0C4,                                       // ProfileInfo::cProfileID_0C4
    cRes_0C5,                                       // ProfileInfo::cProfileID_0C5
    cRes_0C6,                                       // ProfileInfo::cProfileID_0C6
    cRes_0C7,                                       // ProfileInfo::cProfileID_0C7
    cRes_0C8,                                       // ProfileInfo::cProfileID_0C8
    cRes_0C9,                                       // ProfileInfo::cProfileID_0C9
    cRes_0CA,                                       // ProfileInfo::cProfileID_0CA
    cRes_0CB,                                       // ProfileInfo::cProfileID_0CB
    cRes_0CC,                                       // ProfileInfo::cProfileID_0CC
    cRes_0CD,                                       // ProfileInfo::cProfileID_0CD
    cRes_0CE,                                       // ProfileInfo::cProfileID_0CE
    cRes_0CF,                                       // ProfileInfo::cProfileID_0CF
    cRes_0D0,                                       // ProfileInfo::cProfileID_0D0
    cRes_0D1,                                       // ProfileInfo::cProfileID_0D1
    cRes_FloorHoleDokan,                            // ProfileInfo::cProfileID_FloorHoleDokan
    cRes_0D3,                                       // ProfileInfo::cProfileID_0D3
    cRes_0D4,                                       // ProfileInfo::cProfileID_0D4
    cRes_0D5,                                       // ProfileInfo::cProfileID_0D5
    cRes_0D6,                                       // ProfileInfo::cProfileID_0D6
    cRes_0D7,                                       // ProfileInfo::cProfileID_0D7
    cRes_0D8,                                       // ProfileInfo::cProfileID_0D8
    cRes_0D9,                                       // ProfileInfo::cProfileID_0D9
    cRes_0DA,                                       // ProfileInfo::cProfileID_0DA
    cRes_0DB,                                       // ProfileInfo::cProfileID_0DB
    cRes_0DC,                                       // ProfileInfo::cProfileID_0DC
    cRes_0DD,                                       // ProfileInfo::cProfileID_0DD
    cRes_0DE,                                       // ProfileInfo::cProfileID_0DE
    cRes_0DF,                                       // ProfileInfo::cProfileID_0DF
    cRes_Burner,                                    // ProfileInfo::cProfileID_Burner
    cRes_0E1,                                       // ProfileInfo::cProfileID_0E1
    cRes_0E2,                                       // ProfileInfo::cProfileID_0E2
    cRes_0E3,                                       // ProfileInfo::cProfileID_0E3
    cRes_0E4,                                       // ProfileInfo::cProfileID_0E4
    cRes_0E5,                                       // ProfileInfo::cProfileID_0E5
    cRes_0E6,                                       // ProfileInfo::cProfileID_0E6
    cRes_0E7,                                       // ProfileInfo::cProfileID_0E7
    cRes_0E8,                                       // ProfileInfo::cProfileID_0E8
    cRes_0E9,                                       // ProfileInfo::cProfileID_0E9
    cRes_0EA,                                       // ProfileInfo::cProfileID_0EA
    cRes_0EB,                                       // ProfileInfo::cProfileID_0EB
    cRes_0EC,                                       // ProfileInfo::cProfileID_0EC
    cRes_PlyIce,                                    // ProfileInfo::cProfileID_PlyIce
    cRes_TarzanIvy,                                 // ProfileInfo::cProfileID_TarzanIvy
    cRes_0EF,                                       // ProfileInfo::cProfileID_0EF
    cRes_0F0,                                       // ProfileInfo::cProfileID_0F0
    cRes_0F1,                                       // ProfileInfo::cProfileID_0F1
    cRes_0F2,                                       // ProfileInfo::cProfileID_0F2
    cRes_0F3,                                       // ProfileInfo::cProfileID_0F3
    cRes_0F4,                                       // ProfileInfo::cProfileID_0F4
    nullptr,                                        // ProfileInfo::cProfileID_0F5
    cRes_0F6,                                       // ProfileInfo::cProfileID_0F6
    cRes_0F7,                                       // ProfileInfo::cProfileID_0F7
    cRes_0F8,                                       // ProfileInfo::cProfileID_0F8
    cRes_0F9,                                       // ProfileInfo::cProfileID_0F9
    cRes_0FA,                                       // ProfileInfo::cProfileID_0FA
    cRes_0FB,                                       // ProfileInfo::cProfileID_0FB
    cRes_0FC,                                       // ProfileInfo::cProfileID_0FC
    cRes_0FD,                                       // ProfileInfo::cProfileID_0FD
    cRes_0FE,                                       // ProfileInfo::cProfileID_0FE
    cRes_0FF,                                       // ProfileInfo::cProfileID_0FF
    cRes_100,                                       // ProfileInfo::cProfileID_100
    cRes_101,                                       // ProfileInfo::cProfileID_101
    cRes_102,                                       // ProfileInfo::cProfileID_102
    cRes_103,                                       // ProfileInfo::cProfileID_103
    cRes_104,                                       // ProfileInfo::cProfileID_104
    cRes_ShuffleBlock,                              // ProfileInfo::cProfileID_ShuffleBlock
    cRes_KokoopaShipWarpCannon,                     // ProfileInfo::cProfileID_KokoopaShipWarpCannon
    cRes_107,                                       // ProfileInfo::cProfileID_107
    cRes_108,                                       // ProfileInfo::cProfileID_108
    cRes_KoopaShutter,                              // ProfileInfo::cProfileID_KoopaShutter
    cRes_10A,                                       // ProfileInfo::cProfileID_10A
    cRes_10B,                                       // ProfileInfo::cProfileID_10B
    cRes_10C,                                       // ProfileInfo::cProfileID_10C
    cRes_PeachFinalCastleKoopaJrLift,               // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLift
    cRes_PeachFinalCastleKoopaJrLiftHmove,          // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftHmove
    cRes_PeachFinalCastleKoopaJrLiftPairObj,        // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftPairObj
    cRes_RoyLiftWakiStep,                           // ProfileInfo::cProfileID_RoyLiftWakiStep
    cRes_WendyFloor,                                // ProfileInfo::cProfileID_WendyFloor
    cRes_IggyRoom,                                  // ProfileInfo::cProfileID_IggyRoom
    cRes_113,                                       // ProfileInfo::cProfileID_113
    cRes_114,                                       // ProfileInfo::cProfileID_114
    cRes_115,                                       // ProfileInfo::cProfileID_115
    cRes_116,                                       // ProfileInfo::cProfileID_116
    nullptr,                                        // ProfileInfo::cProfileID_117
    cRes_118,                                       // ProfileInfo::cProfileID_118
    cRes_119,                                       // ProfileInfo::cProfileID_119
    cRes_11A,                                       // ProfileInfo::cProfileID_11A
    cRes_11B,                                       // ProfileInfo::cProfileID_11B
    nullptr,                                        // ProfileInfo::cProfileID_11C
    cRes_11D,                                       // ProfileInfo::cProfileID_11D
    cRes_11E,                                       // ProfileInfo::cProfileID_11E
    nullptr,                                        // ProfileInfo::cProfileID_Block
    nullptr,                                        // ProfileInfo::cProfileID_120
    nullptr,                                        // ProfileInfo::cProfileID_121
    nullptr,                                        // ProfileInfo::cProfileID_122
    nullptr,                                        // ProfileInfo::cProfileID_ActorBlockRenga
    nullptr,                                        // ProfileInfo::cProfileID_124
    nullptr,                                        // ProfileInfo::cProfileID_125
    nullptr,                                        // ProfileInfo::cProfileID_126
    nullptr,                                        // ProfileInfo::cProfileID_127
    nullptr,                                        // ProfileInfo::cProfileID_128
    nullptr,                                        // ProfileInfo::cProfileID_129
    nullptr,                                        // ProfileInfo::cProfileID_12A
    nullptr,                                        // ProfileInfo::cProfileID_12B
    nullptr,                                        // ProfileInfo::cProfileID_12C
    nullptr,                                        // ProfileInfo::cProfileID_12D
    nullptr,                                        // ProfileInfo::cProfileID_12E
    nullptr,                                        // ProfileInfo::cProfileID_12F
    nullptr,                                        // ProfileInfo::cProfileID_130
    nullptr,                                        // ProfileInfo::cProfileID_131
    nullptr,                                        // ProfileInfo::cProfileID_132
    nullptr,                                        // ProfileInfo::cProfileID_133
    nullptr,                                        // ProfileInfo::cProfileID_134
    cRes_ActorBlockMakeDRC,                         // ProfileInfo::cProfileID_ActorBlockMakeDRC
    cRes_136,                                       // ProfileInfo::cProfileID_136
    nullptr,                                        // ProfileInfo::cProfileID_137
    cRes_138,                                       // ProfileInfo::cProfileID_138
    nullptr,                                        // ProfileInfo::cProfileID_139
    cRes_13A,                                       // ProfileInfo::cProfileID_13A
    cRes_13B,                                       // ProfileInfo::cProfileID_13B
    cRes_13C,                                       // ProfileInfo::cProfileID_13C
    nullptr,                                        // ProfileInfo::cProfileID_13D
    nullptr,                                        // ProfileInfo::cProfileID_13E
    nullptr,                                        // ProfileInfo::cProfileID_13F
    cRes_140,                                       // ProfileInfo::cProfileID_140
    cRes_141,                                       // ProfileInfo::cProfileID_141
    cRes_142,                                       // ProfileInfo::cProfileID_142
    cRes_143,                                       // ProfileInfo::cProfileID_143
    cRes_144,                                       // ProfileInfo::cProfileID_144
    cRes_145,                                       // ProfileInfo::cProfileID_145
    cRes_146,                                       // ProfileInfo::cProfileID_146
    cRes_147,                                       // ProfileInfo::cProfileID_147
    cRes_148,                                       // ProfileInfo::cProfileID_148
    cRes_149,                                       // ProfileInfo::cProfileID_149
    cRes_14A,                                       // ProfileInfo::cProfileID_14A
    cRes_14B,                                       // ProfileInfo::cProfileID_14B
    nullptr,                                        // ProfileInfo::cProfileID_14C
    cRes_14D,                                       // ProfileInfo::cProfileID_14D
    cRes_14E,                                       // ProfileInfo::cProfileID_14E
    cRes_14F,                                       // ProfileInfo::cProfileID_14F
    cRes_ObjPipeDown,                               // ProfileInfo::cProfileID_ObjPipeDown
    cRes_151,                                       // ProfileInfo::cProfileID_151
    cRes_152,                                       // ProfileInfo::cProfileID_152
    cRes_153,                                       // ProfileInfo::cProfileID_153
    cRes_ObjPipeDownGroup,                          // ProfileInfo::cProfileID_ObjPipeDownGroup
    cRes_155,                                       // ProfileInfo::cProfileID_155
    cRes_156,                                       // ProfileInfo::cProfileID_156
    cRes_157,                                       // ProfileInfo::cProfileID_157
    cRes_SwitchHatenaButton,                        // ProfileInfo::cProfileID_SwitchHatenaButton
    cRes_SwitchPbutton,                             // ProfileInfo::cProfileID_SwitchPbutton
    cRes_SwitchPbuttonRDash,                        // ProfileInfo::cProfileID_SwitchPbuttonRDash
    cRes_SwitchPbuttonNoWallKick,                   // ProfileInfo::cProfileID_SwitchPbuttonNoWallKick
    nullptr,                                        // ProfileInfo::cProfileID_15C
    cRes_15D,                                       // ProfileInfo::cProfileID_15D
    cRes_IcicleBig,                                 // ProfileInfo::cProfileID_IcicleBig
    cRes_LemmyBall,                                 // ProfileInfo::cProfileID_LemmyBall
    cRes_LemmyBomb,                                 // ProfileInfo::cProfileID_LemmyBomb
    cRes_161,                                       // ProfileInfo::cProfileID_161
    nullptr,                                        // ProfileInfo::cProfileID_162
    cRes_163,                                       // ProfileInfo::cProfileID_163
    cRes_164,                                       // ProfileInfo::cProfileID_164
    cRes_165,                                       // ProfileInfo::cProfileID_165
    cRes_166,                                       // ProfileInfo::cProfileID_166
    cRes_167,                                       // ProfileInfo::cProfileID_167
    cRes_168,                                       // ProfileInfo::cProfileID_168
    cRes_169,                                       // ProfileInfo::cProfileID_169
    cRes_PentaroIce,                                // ProfileInfo::cProfileID_PentaroIce
    cRes_16B,                                       // ProfileInfo::cProfileID_16B
    cRes_16C,                                       // ProfileInfo::cProfileID_16C
    cRes_16D,                                       // ProfileInfo::cProfileID_16D
    cRes_16E,                                       // ProfileInfo::cProfileID_16E
    cRes_16F,                                       // ProfileInfo::cProfileID_16F
    cRes_KameckIce,                                 // ProfileInfo::cProfileID_KameckIce
    cRes_WendyIcicle,                               // ProfileInfo::cProfileID_WendyIcicle
    cRes_PeachFinalCastleKoopaJrClown,              // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrClown
    cRes_BoxingKoopaJrClown,                        // ProfileInfo::cProfileID_BoxingKoopaJrClown
    cRes_174,                                       // ProfileInfo::cProfileID_174
    cRes_FinalKoopaJrClown,                         // ProfileInfo::cProfileID_FinalKoopaJrClown
    cRes_FinalKoopa,                                // ProfileInfo::cProfileID_FinalKoopa
    cRes_FireBar,                                   // ProfileInfo::cProfileID_FireBar
    cRes_FireBarSync,                               // ProfileInfo::cProfileID_FireBarSync
    cRes_179,                                       // ProfileInfo::cProfileID_179
    cRes_17A,                                       // ProfileInfo::cProfileID_17A
    cRes_17B,                                       // ProfileInfo::cProfileID_17B
    nullptr,                                        // ProfileInfo::cProfileID_17C
    cRes_17D,                                       // ProfileInfo::cProfileID_17D
    cRes_17E,                                       // ProfileInfo::cProfileID_17E
    cRes_17F,                                       // ProfileInfo::cProfileID_17F
    cRes_180,                                       // ProfileInfo::cProfileID_180
    cRes_181,                                       // ProfileInfo::cProfileID_181
    cRes_182,                                       // ProfileInfo::cProfileID_182
    cRes_183,                                       // ProfileInfo::cProfileID_183
    cRes_184,                                       // ProfileInfo::cProfileID_184
    cRes_185,                                       // ProfileInfo::cProfileID_185
    cRes_186,                                       // ProfileInfo::cProfileID_186
    cRes_187,                                       // ProfileInfo::cProfileID_187
    cRes_188,                                       // ProfileInfo::cProfileID_188
    cRes_189,                                       // ProfileInfo::cProfileID_189
    cRes_18A,                                       // ProfileInfo::cProfileID_18A
    cRes_ActorCoin,                                 // ProfileInfo::cProfileID_ActorCoin
    cRes_18C,                                       // ProfileInfo::cProfileID_18C
    cRes_18D,                                       // ProfileInfo::cProfileID_18D
    cRes_18E,                                       // ProfileInfo::cProfileID_18E
    cRes_18F,                                       // ProfileInfo::cProfileID_18F
    cRes_190,                                       // ProfileInfo::cProfileID_190
    cRes_191,                                       // ProfileInfo::cProfileID_191
    cRes_192,                                       // ProfileInfo::cProfileID_192
    cRes_193,                                       // ProfileInfo::cProfileID_193
    cRes_194,                                       // ProfileInfo::cProfileID_194
    cRes_195,                                       // ProfileInfo::cProfileID_195
    cRes_196,                                       // ProfileInfo::cProfileID_196
    cRes_197,                                       // ProfileInfo::cProfileID_197
    cRes_198,                                       // ProfileInfo::cProfileID_198
    cRes_199,                                       // ProfileInfo::cProfileID_199
    cRes_19A,                                       // ProfileInfo::cProfileID_19A
    nullptr,                                        // ProfileInfo::cProfileID_19B
    cRes_19C,                                       // ProfileInfo::cProfileID_19C
    cRes_19D,                                       // ProfileInfo::cProfileID_19D
    nullptr,                                        // ProfileInfo::cProfileID_19E
    cRes_19F,                                       // ProfileInfo::cProfileID_19F
    cRes_1A0,                                       // ProfileInfo::cProfileID_1A0
    cRes_1A1,                                       // ProfileInfo::cProfileID_1A1
    nullptr,                                        // ProfileInfo::cProfileID_1A2
    cRes_1A3,                                       // ProfileInfo::cProfileID_1A3
    cRes_1A4,                                       // ProfileInfo::cProfileID_1A4
    cRes_1A5,                                       // ProfileInfo::cProfileID_1A5
    cRes_1A6,                                       // ProfileInfo::cProfileID_1A6
    cRes_1A7,                                       // ProfileInfo::cProfileID_1A7
    cRes_1A8,                                       // ProfileInfo::cProfileID_1A8
    cRes_BlueCoin,                                  // ProfileInfo::cProfileID_BlueCoin
    cRes_1AA,                                       // ProfileInfo::cProfileID_1AA
    cRes_1AB,                                       // ProfileInfo::cProfileID_1AB
    cRes_1AC,                                       // ProfileInfo::cProfileID_1AC
    cRes_1AD,                                       // ProfileInfo::cProfileID_1AD
    cRes_1AE,                                       // ProfileInfo::cProfileID_1AE
    cRes_1AF,                                       // ProfileInfo::cProfileID_1AF
    cRes_1B0,                                       // ProfileInfo::cProfileID_1B0
    cRes_1B1,                                       // ProfileInfo::cProfileID_1B1
    cRes_1B2,                                       // ProfileInfo::cProfileID_1B2
    cRes_1B3,                                       // ProfileInfo::cProfileID_1B3
    nullptr,                                        // ProfileInfo::cProfileID_1B4
    nullptr,                                        // ProfileInfo::cProfileID_1B5
    cRes_CoinmakiCoin,                              // ProfileInfo::cProfileID_CoinmakiCoin
    nullptr,                                        // ProfileInfo::cProfileID_1B7
    nullptr,                                        // ProfileInfo::cProfileID_1B8
    cRes_1B9,                                       // ProfileInfo::cProfileID_1B9
    cRes_Yoshi,                                     // ProfileInfo::cProfileID_Yoshi
    cRes_TottenPlayer,                              // ProfileInfo::cProfileID_TottenPlayer
    cRes_PlayerObject,                              // ProfileInfo::cProfileID_PlayerObject
    cRes_1BD,                                       // ProfileInfo::cProfileID_1BD
    cRes_1BE,                                       // ProfileInfo::cProfileID_1BE
    cRes_1BF,                                       // ProfileInfo::cProfileID_1BF
    cRes_1C0,                                       // ProfileInfo::cProfileID_1C0
    cRes_1C1,                                       // ProfileInfo::cProfileID_1C1
    cRes_1C2,                                       // ProfileInfo::cProfileID_1C2
    cRes_1C3,                                       // ProfileInfo::cProfileID_1C3
    nullptr,                                        // ProfileInfo::cProfileID_1C4
    cRes_SlotYoshiChibi,                            // ProfileInfo::cProfileID_SlotYoshiChibi
    cRes_1C6,                                       // ProfileInfo::cProfileID_1C6
    nullptr,                                        // ProfileInfo::cProfileID_1C7
    cRes_1C8,                                       // ProfileInfo::cProfileID_1C8
    nullptr,                                        // ProfileInfo::cProfileID_1C9
    nullptr,                                        // ProfileInfo::cProfileID_1CA
    cRes_1CB,                                       // ProfileInfo::cProfileID_1CB
    cRes_1CC,                                       // ProfileInfo::cProfileID_1CC
    nullptr,                                        // ProfileInfo::cProfileID_1CD
    cRes_1CE,                                       // ProfileInfo::cProfileID_1CE
    cRes_QuestPrizeItem,                            // ProfileInfo::cProfileID_QuestPrizeItem
    cRes_1D0,                                       // ProfileInfo::cProfileID_1D0
    cRes_1D1,                                       // ProfileInfo::cProfileID_1D1
    cRes_1D2,                                       // ProfileInfo::cProfileID_1D2
    cRes_1D3,                                       // ProfileInfo::cProfileID_1D3
    cRes_1D4,                                       // ProfileInfo::cProfileID_1D4
    cRes_1D5,                                       // ProfileInfo::cProfileID_1D5
    cRes_1D6,                                       // ProfileInfo::cProfileID_1D6
    cRes_1D7,                                       // ProfileInfo::cProfileID_1D7
    cRes_1D8,                                       // ProfileInfo::cProfileID_1D8
    cRes_1D9,                                       // ProfileInfo::cProfileID_1D9
    nullptr,                                        // ProfileInfo::cProfileID_IceBall
    nullptr,                                        // ProfileInfo::cProfileID_IceBallPakkun
    nullptr,                                        // ProfileInfo::cProfileID_FireBallPlayer
    nullptr,                                        // ProfileInfo::cProfileID_FireBallPakkun
    nullptr,                                        // ProfileInfo::cProfileID_YoshiFire
    cRes_1DF,                                       // ProfileInfo::cProfileID_1DF
    cRes_1E0,                                       // ProfileInfo::cProfileID_1E0
    cRes_1E1,                                       // ProfileInfo::cProfileID_1E1
    cRes_1E2,                                       // ProfileInfo::cProfileID_1E2
    cRes_1E3,                                       // ProfileInfo::cProfileID_1E3
    cRes_1E4,                                       // ProfileInfo::cProfileID_1E4
    cRes_1E5,                                       // ProfileInfo::cProfileID_1E5
    cRes_1E6,                                       // ProfileInfo::cProfileID_1E6
    cRes_1E7,                                       // ProfileInfo::cProfileID_1E7
    cRes_1E8,                                       // ProfileInfo::cProfileID_1E8
    cRes_1E9,                                       // ProfileInfo::cProfileID_1E9
    cRes_1EA,                                       // ProfileInfo::cProfileID_1EA
    cRes_1EB,                                       // ProfileInfo::cProfileID_1EB
    cRes_1EC,                                       // ProfileInfo::cProfileID_1EC
    cRes_1ED,                                       // ProfileInfo::cProfileID_1ED
    cRes_1EE,                                       // ProfileInfo::cProfileID_1EE
    cRes_1EF,                                       // ProfileInfo::cProfileID_1EF
    cRes_1F0,                                       // ProfileInfo::cProfileID_1F0
    cRes_1F1,                                       // ProfileInfo::cProfileID_1F1
    cRes_1F2,                                       // ProfileInfo::cProfileID_1F2
    cRes_1F3,                                       // ProfileInfo::cProfileID_1F3
    cRes_1F4,                                       // ProfileInfo::cProfileID_1F4
    cRes_1F5,                                       // ProfileInfo::cProfileID_1F5
    cRes_1F6,                                       // ProfileInfo::cProfileID_1F6
    cRes_1F7,                                       // ProfileInfo::cProfileID_1F7
    cRes_1F8,                                       // ProfileInfo::cProfileID_1F8
    cRes_1F9,                                       // ProfileInfo::cProfileID_1F9
    cRes_1FA,                                       // ProfileInfo::cProfileID_1FA
    cRes_1FB,                                       // ProfileInfo::cProfileID_1FB
    cRes_1FC,                                       // ProfileInfo::cProfileID_1FC
    cRes_1FD,                                       // ProfileInfo::cProfileID_1FD
    cRes_1FE,                                       // ProfileInfo::cProfileID_1FE
    nullptr,                                        // ProfileInfo::cProfileID_1FF
    cRes_Nokonoko,                                  // ProfileInfo::cProfileID_Nokonoko
    cRes_201,                                       // ProfileInfo::cProfileID_201
    cRes_202,                                       // ProfileInfo::cProfileID_202
    cRes_203,                                       // ProfileInfo::cProfileID_203
    cRes_204,                                       // ProfileInfo::cProfileID_204
    cRes_205,                                       // ProfileInfo::cProfileID_205
    cRes_206,                                       // ProfileInfo::cProfileID_206
    cRes_207,                                       // ProfileInfo::cProfileID_207
    cRes_208,                                       // ProfileInfo::cProfileID_208
    cRes_209,                                       // ProfileInfo::cProfileID_209
    cRes_20A,                                       // ProfileInfo::cProfileID_20A
    cRes_20B,                                       // ProfileInfo::cProfileID_20B
    cRes_MechaKoopa,                                // ProfileInfo::cProfileID_MechaKoopa
    cRes_20D,                                       // ProfileInfo::cProfileID_20D
    cRes_20E,                                       // ProfileInfo::cProfileID_20E
    cRes_20F,                                       // ProfileInfo::cProfileID_20F
    cRes_210,                                       // ProfileInfo::cProfileID_210
    cRes_211,                                       // ProfileInfo::cProfileID_211
    cRes_212,                                       // ProfileInfo::cProfileID_212
    cRes_213,                                       // ProfileInfo::cProfileID_213
    cRes_214,                                       // ProfileInfo::cProfileID_214
    cRes_215,                                       // ProfileInfo::cProfileID_215
    cRes_216,                                       // ProfileInfo::cProfileID_216
    cRes_217,                                       // ProfileInfo::cProfileID_217
    cRes_218,                                       // ProfileInfo::cProfileID_218
    cRes_219,                                       // ProfileInfo::cProfileID_219
    cRes_21A,                                       // ProfileInfo::cProfileID_21A
    cRes_21B,                                       // ProfileInfo::cProfileID_21B
    cRes_21C,                                       // ProfileInfo::cProfileID_21C
    cRes_21D,                                       // ProfileInfo::cProfileID_21D
    cRes_21E,                                       // ProfileInfo::cProfileID_21E
    cRes_21F,                                       // ProfileInfo::cProfileID_21F
    cRes_220,                                       // ProfileInfo::cProfileID_220
    cRes_221,                                       // ProfileInfo::cProfileID_221
    cRes_222,                                       // ProfileInfo::cProfileID_222
    cRes_223,                                       // ProfileInfo::cProfileID_223
    cRes_224,                                       // ProfileInfo::cProfileID_224
    cRes_225,                                       // ProfileInfo::cProfileID_225
    cRes_226,                                       // ProfileInfo::cProfileID_226
    cRes_227,                                       // ProfileInfo::cProfileID_227
    cRes_228,                                       // ProfileInfo::cProfileID_228
    cRes_229,                                       // ProfileInfo::cProfileID_229
    cRes_22A,                                       // ProfileInfo::cProfileID_22A
    cRes_22B,                                       // ProfileInfo::cProfileID_22B
    cRes_22C,                                       // ProfileInfo::cProfileID_22C
    cRes_22D,                                       // ProfileInfo::cProfileID_22D
    nullptr,                                        // ProfileInfo::cProfileID_FireBallKeronpa
    nullptr,                                        // ProfileInfo::cProfileID_FireBallKeronpaRDash
    cRes_230,                                       // ProfileInfo::cProfileID_230
    cRes_FireSnake,                                 // ProfileInfo::cProfileID_FireSnake
    cRes_232,                                       // ProfileInfo::cProfileID_232
    cRes_233,                                       // ProfileInfo::cProfileID_233
    cRes_234,                                       // ProfileInfo::cProfileID_234
    cRes_235,                                       // ProfileInfo::cProfileID_235
    cRes_236,                                       // ProfileInfo::cProfileID_236
    cRes_237,                                       // ProfileInfo::cProfileID_237
    cRes_238,                                       // ProfileInfo::cProfileID_238
    cRes_239,                                       // ProfileInfo::cProfileID_239
    cRes_23A,                                       // ProfileInfo::cProfileID_23A
    cRes_23B,                                       // ProfileInfo::cProfileID_23B
    cRes_23C,                                       // ProfileInfo::cProfileID_23C
    cRes_23D,                                       // ProfileInfo::cProfileID_23D
    cRes_Kazandan,                                  // ProfileInfo::cProfileID_Kazandan
    nullptr,                                        // ProfileInfo::cProfileID_23F
    nullptr,                                        // ProfileInfo::cProfileID_240
    nullptr,                                        // ProfileInfo::cProfileID_241
    nullptr,                                        // ProfileInfo::cProfileID_242
    nullptr,                                        // ProfileInfo::cProfileID_243
    nullptr,                                        // ProfileInfo::cProfileID_244
    nullptr,                                        // ProfileInfo::cProfileID_245
    nullptr,                                        // ProfileInfo::cProfileID_246
    nullptr,                                        // ProfileInfo::cProfileID_247
    nullptr,                                        // ProfileInfo::cProfileID_248
    nullptr,                                        // ProfileInfo::cProfileID_249
    nullptr,                                        // ProfileInfo::cProfileID_24A
    nullptr,                                        // ProfileInfo::cProfileID_BgCenter
    nullptr,                                        // ProfileInfo::cProfileID_24C
    nullptr,                                        // ProfileInfo::cProfileID_24D
    nullptr,                                        // ProfileInfo::cProfileID_24E
    cRes_Kinoko,                                    // ProfileInfo::cProfileID_Kinoko
    cRes_FireFlower,                                // ProfileInfo::cProfileID_FireFlower
    cRes_MameKinoko,                                // ProfileInfo::cProfileID_MameKinoko
    cRes_IceFlower,                                 // ProfileInfo::cProfileID_IceFlower
    cRes_Propeller,                                 // ProfileInfo::cProfileID_Propeller
    cRes_Penguin,                                   // ProfileInfo::cProfileID_Penguin
    cRes_OneUpKinoko,                               // ProfileInfo::cProfileID_OneUpKinoko
    cRes_Musasabi,                                  // ProfileInfo::cProfileID_Musasabi
    cRes_SuperMoon,                                 // ProfileInfo::cProfileID_SuperMoon
    cRes_TitleDemoItem,                             // ProfileInfo::cProfileID_TitleDemoItem
    cRes_259,                                       // ProfileInfo::cProfileID_259
    cRes_25A,                                       // ProfileInfo::cProfileID_25A
    cRes_25B,                                       // ProfileInfo::cProfileID_25B
    cRes_25C,                                       // ProfileInfo::cProfileID_25C
    cRes_25D,                                       // ProfileInfo::cProfileID_25D
    cRes_25E,                                       // ProfileInfo::cProfileID_25E
    cRes_25F,                                       // ProfileInfo::cProfileID_25F
    cRes_260,                                       // ProfileInfo::cProfileID_260
    cRes_261,                                       // ProfileInfo::cProfileID_261
    cRes_262,                                       // ProfileInfo::cProfileID_262
    cRes_263,                                       // ProfileInfo::cProfileID_263
    cRes_264,                                       // ProfileInfo::cProfileID_264
    cRes_265,                                       // ProfileInfo::cProfileID_265
    cRes_266,                                       // ProfileInfo::cProfileID_266
    cRes_267,                                       // ProfileInfo::cProfileID_267
    cRes_268,                                       // ProfileInfo::cProfileID_268
    cRes_Spanner,                                   // ProfileInfo::cProfileID_Spanner
    cRes_26A,                                       // ProfileInfo::cProfileID_26A
    cRes_26B,                                       // ProfileInfo::cProfileID_26B
    cRes_26C,                                       // ProfileInfo::cProfileID_26C
    cRes_26D,                                       // ProfileInfo::cProfileID_26D
    cRes_26E,                                       // ProfileInfo::cProfileID_26E
    cRes_26F,                                       // ProfileInfo::cProfileID_26F
    cRes_270,                                       // ProfileInfo::cProfileID_270
    cRes_271,                                       // ProfileInfo::cProfileID_271
    cRes_272,                                       // ProfileInfo::cProfileID_272
    nullptr,                                        // ProfileInfo::cProfileID_273
    nullptr,                                        // ProfileInfo::cProfileID_274
    nullptr,                                        // ProfileInfo::cProfileID_275
    nullptr,                                        // ProfileInfo::cProfileID_SearchKiller
    nullptr,                                        // ProfileInfo::cProfileID_277
    cRes_278,                                       // ProfileInfo::cProfileID_278
    cRes_279,                                       // ProfileInfo::cProfileID_279
    cRes_WakiSearchMagKiller,                       // ProfileInfo::cProfileID_WakiSearchMagKiller
    cRes_27B,                                       // ProfileInfo::cProfileID_27B
    cRes_27C,                                       // ProfileInfo::cProfileID_27C
    cRes_27D,                                       // ProfileInfo::cProfileID_27D
    cRes_27E,                                       // ProfileInfo::cProfileID_27E
    cRes_27F,                                       // ProfileInfo::cProfileID_27F
    cRes_GabonRock,                                 // ProfileInfo::cProfileID_GabonRock
    cRes_281,                                       // ProfileInfo::cProfileID_281
    cRes_282,                                       // ProfileInfo::cProfileID_282
    cRes_RockGabonRock,                             // ProfileInfo::cProfileID_RockGabonRock
    cRes_284,                                       // ProfileInfo::cProfileID_284
    cRes_SeichanSnowBall,                           // ProfileInfo::cProfileID_SeichanSnowBall
    cRes_286,                                       // ProfileInfo::cProfileID_286
    cRes_287,                                       // ProfileInfo::cProfileID_287
    cRes_288,                                       // ProfileInfo::cProfileID_288
    cRes_289,                                       // ProfileInfo::cProfileID_289
    cRes_Woochan,                                   // ProfileInfo::cProfileID_Woochan
    cRes_28B,                                       // ProfileInfo::cProfileID_28B
    cRes_28C,                                       // ProfileInfo::cProfileID_28C
    cRes_28D,                                       // ProfileInfo::cProfileID_28D
    cRes_Bubble,                                    // ProfileInfo::cProfileID_Bubble
    cRes_BubbleSync,                                // ProfileInfo::cProfileID_BubbleSync
    cRes_BubbleRDash,                               // ProfileInfo::cProfileID_BubbleRDash
    cRes_BubbleSyncRDash,                           // ProfileInfo::cProfileID_BubbleSyncRDash
    cRes_292,                                       // ProfileInfo::cProfileID_292
    cRes_293,                                       // ProfileInfo::cProfileID_293
    cRes_294,                                       // ProfileInfo::cProfileID_294
    cRes_295,                                       // ProfileInfo::cProfileID_295
    cRes_296,                                       // ProfileInfo::cProfileID_296
    cRes_297,                                       // ProfileInfo::cProfileID_297
    cRes_298,                                       // ProfileInfo::cProfileID_298
    cRes_299,                                       // ProfileInfo::cProfileID_299
    cRes_29A,                                       // ProfileInfo::cProfileID_29A
    cRes_29B,                                       // ProfileInfo::cProfileID_29B
    nullptr,                                        // ProfileInfo::cProfileID_29C
    cRes_29D,                                       // ProfileInfo::cProfileID_29D
    cRes_29E,                                       // ProfileInfo::cProfileID_29E
    cRes_29F,                                       // ProfileInfo::cProfileID_29F
    cRes_2A0,                                       // ProfileInfo::cProfileID_2A0
    cRes_2A1,                                       // ProfileInfo::cProfileID_2A1
    cRes_2A2,                                       // ProfileInfo::cProfileID_2A2
    cRes_2A3,                                       // ProfileInfo::cProfileID_2A3
    cRes_2A4,                                       // ProfileInfo::cProfileID_2A4
    cRes_2A5,                                       // ProfileInfo::cProfileID_2A5
    cRes_Bun,                                       // ProfileInfo::cProfileID_Bun
    cRes_BunW2,                                     // ProfileInfo::cProfileID_BunW2
    cRes_BunW3,                                     // ProfileInfo::cProfileID_BunW3
    cRes_BunW4,                                     // ProfileInfo::cProfileID_BunW4
    cRes_BunW5,                                     // ProfileInfo::cProfileID_BunW5
    cRes_BunW6,                                     // ProfileInfo::cProfileID_BunW6
    cRes_BunDemo,                                   // ProfileInfo::cProfileID_BunDemo
    nullptr,                                        // ProfileInfo::cProfileID_KokoopaDemo
    nullptr,                                        // ProfileInfo::cProfileID_KoopaJrDemo
    nullptr,                                        // ProfileInfo::cProfileID_KameckDemo
    cRes_BossKKDemo,                                // ProfileInfo::cProfileID_BossKKDemo
    nullptr,                                        // ProfileInfo::cProfileID_PeachFinalCastleKoopaJrDemo
    cRes_KoopaDemo,                                 // ProfileInfo::cProfileID_KoopaDemo
    nullptr,                                        // ProfileInfo::cProfileID_FinalKoopaDemo
    nullptr,                                        // ProfileInfo::cProfileID_PeachDemo
    cRes_Larry,                                     // ProfileInfo::cProfileID_Larry
    cRes_KokoopaSearchFire,                         // ProfileInfo::cProfileID_KokoopaSearchFire
    cRes_Lemmy,                                     // ProfileInfo::cProfileID_Lemmy
    cRes_Morton,                                    // ProfileInfo::cProfileID_Morton
    cRes_MortonSanbo,                               // ProfileInfo::cProfileID_MortonSanbo
    cRes_MortonSanboParts,                          // ProfileInfo::cProfileID_MortonSanboParts
    cRes_Wendy,                                     // ProfileInfo::cProfileID_Wendy
    cRes_WendyRing,                                 // ProfileInfo::cProfileID_WendyRing
    cRes_Ludwig,                                    // ProfileInfo::cProfileID_Ludwig
    cRes_LudwigAlterEgo,                            // ProfileInfo::cProfileID_LudwigAlterEgo
    cRes_Iggy,                                      // ProfileInfo::cProfileID_Iggy
    nullptr,                                        // ProfileInfo::cProfileID_IggyMagic
    cRes_Woogan,                                    // ProfileInfo::cProfileID_Woogan
    cRes_Roy,                                       // ProfileInfo::cProfileID_Roy
    cRes_RoyLiftWaki,                               // ProfileInfo::cProfileID_RoyLiftWaki
    cRes_BossKK,                                    // ProfileInfo::cProfileID_BossKK
    nullptr,                                        // ProfileInfo::cProfileID_BossKKThunder
    cRes_Kameck,                                    // ProfileInfo::cProfileID_Kameck
    nullptr,                                        // ProfileInfo::cProfileID_KameckIceConfig
    nullptr,                                        // ProfileInfo::cProfileID_KameckWarpPos
    nullptr,                                        // ProfileInfo::cProfileID_KameckMagic
    cRes_PeachFinalCastleKoopaJr,                   // ProfileInfo::cProfileID_PeachFinalCastleKoopaJr
    cRes_Koopa,                                     // ProfileInfo::cProfileID_Koopa
    cRes_KoopaFireWaki,                             // ProfileInfo::cProfileID_KoopaFireWaki
    cRes_KoopaFire,                                 // ProfileInfo::cProfileID_KoopaFire
    cRes_DemoKoopaJrClown,                          // ProfileInfo::cProfileID_DemoKoopaJrClown
    cRes_DemoKoopaJr,                               // ProfileInfo::cProfileID_DemoKoopaJr
    cRes_BunDemoKameck,                             // ProfileInfo::cProfileID_BunDemoKameck
    cRes_KoopaDemoKameck,                           // ProfileInfo::cProfileID_KoopaDemoKameck
    cRes_BossKKDemoKameck,                          // ProfileInfo::cProfileID_BossKKDemoKameck
    cRes_BossKKDemoKK,                              // ProfileInfo::cProfileID_BossKKDemoKK
    cRes_FinalKoopaFire,                            // ProfileInfo::cProfileID_FinalKoopaFire
    cRes_FinalKoopaJr,                              // ProfileInfo::cProfileID_FinalKoopaJr
    nullptr,                                        // ProfileInfo::cProfileID_FinalKoopaJrFire
    cRes_FinalBomhei,                               // ProfileInfo::cProfileID_FinalBomhei
    cRes_KokoopaShipLemmy,                          // ProfileInfo::cProfileID_KokoopaShipLemmy
    cRes_KokoopaShipMorton,                         // ProfileInfo::cProfileID_KokoopaShipMorton
    cRes_KokoopaShipLarry,                          // ProfileInfo::cProfileID_KokoopaShipLarry
    cRes_KokoopaShipWendy,                          // ProfileInfo::cProfileID_KokoopaShipWendy
    cRes_KokoopaShipIggy,                           // ProfileInfo::cProfileID_KokoopaShipIggy
    cRes_KokoopaShipRoy,                            // ProfileInfo::cProfileID_KokoopaShipRoy
    cRes_KokoopaShipLudwig,                         // ProfileInfo::cProfileID_KokoopaShipLudwig
    cRes_Peach,                                     // ProfileInfo::cProfileID_Peach
    cRes_2E0,                                       // ProfileInfo::cProfileID_2E0
    nullptr,                                        // ProfileInfo::cProfileID_FinalDVPeach
    nullptr,                                        // ProfileInfo::cProfileID_FinalDVShutter
    cRes_2E3,                                       // ProfileInfo::cProfileID_2E3
    cRes_2E4,                                       // ProfileInfo::cProfileID_2E4
    cRes_2E5,                                       // ProfileInfo::cProfileID_2E5
    cRes_2E6,                                       // ProfileInfo::cProfileID_2E6
    cRes_2E7,                                       // ProfileInfo::cProfileID_2E7
    cRes_2E8,                                       // ProfileInfo::cProfileID_2E8
    nullptr,                                        // ProfileInfo::cProfileID_2E9
    nullptr,                                        // ProfileInfo::cProfileID_2EA
    nullptr,                                        // ProfileInfo::cProfileID_2EB
    nullptr,                                        // ProfileInfo::cProfileID_2EC
    nullptr,                                        // ProfileInfo::cProfileID_2ED
    cRes_2EE,                                       // ProfileInfo::cProfileID_2EE
    cRes_2EF,                                       // ProfileInfo::cProfileID_2EF
    cRes_2F0,                                       // ProfileInfo::cProfileID_2F0
    cRes_2F1,                                       // ProfileInfo::cProfileID_2F1
    cRes_2F2,                                       // ProfileInfo::cProfileID_2F2
    cRes_2F3,                                       // ProfileInfo::cProfileID_2F3
    cRes_2F4,                                       // ProfileInfo::cProfileID_2F4
    cRes_2F5,                                       // ProfileInfo::cProfileID_2F5
    cRes_Hammer,                                    // ProfileInfo::cProfileID_Hammer
    cRes_2F7,                                       // ProfileInfo::cProfileID_2F7
    cRes_Boomerang,                                 // ProfileInfo::cProfileID_Boomerang
    cRes_2F9,                                       // ProfileInfo::cProfileID_2F9
    nullptr,                                        // ProfileInfo::cProfileID_FireBallBros
    cRes_2FB,                                       // ProfileInfo::cProfileID_2FB
    nullptr,                                        // ProfileInfo::cProfileID_IceBallBros
    cRes_2FD,                                       // ProfileInfo::cProfileID_2FD
    cRes_MegaHammer,                                // ProfileInfo::cProfileID_MegaHammer
    cRes_2FF,                                       // ProfileInfo::cProfileID_2FF
    cRes_300,                                       // ProfileInfo::cProfileID_300
    cRes_301,                                       // ProfileInfo::cProfileID_301
    cRes_302,                                       // ProfileInfo::cProfileID_302
    cRes_303,                                       // ProfileInfo::cProfileID_303
    cRes_304,                                       // ProfileInfo::cProfileID_304
    cRes_305,                                       // ProfileInfo::cProfileID_305
    cRes_306,                                       // ProfileInfo::cProfileID_306
    cRes_307,                                       // ProfileInfo::cProfileID_307
    cRes_308,                                       // ProfileInfo::cProfileID_308
    cRes_309,                                       // ProfileInfo::cProfileID_309
    cRes_30A,                                       // ProfileInfo::cProfileID_30A
    cRes_30B,                                       // ProfileInfo::cProfileID_30B
    cRes_30C,                                       // ProfileInfo::cProfileID_30C
    cRes_30D,                                       // ProfileInfo::cProfileID_30D
    nullptr,                                        // ProfileInfo::cProfileID_30E
    cRes_30F,                                       // ProfileInfo::cProfileID_30F
    cRes_310,                                       // ProfileInfo::cProfileID_310
    cRes_311,                                       // ProfileInfo::cProfileID_311
    cRes_312,                                       // ProfileInfo::cProfileID_312
    cRes_313,                                       // ProfileInfo::cProfileID_313
    cRes_314,                                       // ProfileInfo::cProfileID_314
    cRes_315,                                       // ProfileInfo::cProfileID_315
    cRes_316,                                       // ProfileInfo::cProfileID_316
    cRes_317,                                       // ProfileInfo::cProfileID_317
    cRes_318,                                       // ProfileInfo::cProfileID_318
    nullptr,                                        // ProfileInfo::cProfileID_319
    nullptr,                                        // ProfileInfo::cProfileID_31A
    nullptr,                                        // ProfileInfo::cProfileID_31B
    cRes_31C,                                       // ProfileInfo::cProfileID_31C
    cRes_31D,                                       // ProfileInfo::cProfileID_31D
    nullptr,                                        // ProfileInfo::cProfileID_31E
    cRes_31F,                                       // ProfileInfo::cProfileID_31F
    cRes_320,                                       // ProfileInfo::cProfileID_320
    cRes_321,                                       // ProfileInfo::cProfileID_321
    cRes_322,                                       // ProfileInfo::cProfileID_322
    cRes_323,                                       // ProfileInfo::cProfileID_323
    cRes_324,                                       // ProfileInfo::cProfileID_324
    cRes_325,                                       // ProfileInfo::cProfileID_325
    cRes_326,                                       // ProfileInfo::cProfileID_326
    cRes_327,                                       // ProfileInfo::cProfileID_327
    nullptr,                                        // ProfileInfo::cProfileID_328
    cRes_BattleItem,                                // ProfileInfo::cProfileID_BattleItem
    cRes_32A,                                       // ProfileInfo::cProfileID_32A
    cRes_VsBattleItem,                              // ProfileInfo::cProfileID_VsBattleItem
    cRes_32C,                                       // ProfileInfo::cProfileID_32C
    cRes_32D,                                       // ProfileInfo::cProfileID_32D
    nullptr,                                        // ProfileInfo::cProfileID_32E
    cRes_32F,                                       // ProfileInfo::cProfileID_32F
    cRes_330,                                       // ProfileInfo::cProfileID_330
    cRes_331,                                       // ProfileInfo::cProfileID_331
    cRes_KoopaJrFire,                               // ProfileInfo::cProfileID_KoopaJrFire
    cRes_KoopaJrBall,                               // ProfileInfo::cProfileID_KoopaJrBall
    cRes_UnderwaterKoopaJr,                         // ProfileInfo::cProfileID_UnderwaterKoopaJr
    cRes_UnderwaterKoopaJrClown,                    // ProfileInfo::cProfileID_UnderwaterKoopaJrClown
    cRes_UnderwaterKoopaJrRetreatPos,               // ProfileInfo::cProfileID_UnderwaterKoopaJrRetreatPos
    cRes_BoxingKoopaJr,                             // ProfileInfo::cProfileID_BoxingKoopaJr
    cRes_BoxingKoopaJrPostBattleDemo,               // ProfileInfo::cProfileID_BoxingKoopaJrPostBattleDemo
    cRes_BoxingKoopaJrClownPostBattleDemo,          // ProfileInfo::cProfileID_BoxingKoopaJrClownPostBattleDemo
    cRes_MiniGamePanelItem,                         // ProfileInfo::cProfileID_MiniGamePanelItem
    cRes_SlotItem,                                  // ProfileInfo::cProfileID_SlotItem
    cRes_CoinmakiCannon,                            // ProfileInfo::cProfileID_CoinmakiCannon
    cRes_CoinmakiItem,                              // ProfileInfo::cProfileID_CoinmakiItem
    cRes_MiniGameKinopio,                           // ProfileInfo::cProfileID_MiniGameKinopio
    cRes_33F,                                       // ProfileInfo::cProfileID_33F
    cRes_340,                                       // ProfileInfo::cProfileID_340
    cRes_341,                                       // ProfileInfo::cProfileID_341
    cRes_342,                                       // ProfileInfo::cProfileID_342
    nullptr,                                        // ProfileInfo::cProfileID_343
    nullptr,                                        // ProfileInfo::cProfileID_344
    nullptr,                                        // ProfileInfo::cProfileID_345
    nullptr,                                        // ProfileInfo::cProfileID_346
    nullptr,                                        // ProfileInfo::cProfileID_347
    cRes_StaffCreditChibiYoshiABC,                  // ProfileInfo::cProfileID_StaffCreditChibiYoshiABC
    cRes_StaffCreditChibiYoshiBalloon,              // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloon
    cRes_StaffCreditChibiYoshiBalloonCheer,         // ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloonCheer
    cRes_StaffCreditChibiYoshiLight,                // ProfileInfo::cProfileID_StaffCreditChibiYoshiLight
    cRes_StaffCreditChibiYoshiLightCheer,           // ProfileInfo::cProfileID_StaffCreditChibiYoshiLightCheer
    cRes_StaffCreditSoapABC,                        // ProfileInfo::cProfileID_StaffCreditSoapABC
    cRes_StaffCreditSoapCoin,                       // ProfileInfo::cProfileID_StaffCreditSoapCoin
    cRes_StaffCreditTottenKun,                      // ProfileInfo::cProfileID_StaffCreditTottenKun
    nullptr,                                        // ProfileInfo::cProfileID_350
    nullptr,                                        // ProfileInfo::cProfileID_351
    nullptr,                                        // ProfileInfo::cProfileID_352
    nullptr,                                        // ProfileInfo::cProfileID_353
    cRes_RealizeFeverStar,                          // ProfileInfo::cProfileID_RealizeFeverStar
    cRes_Star,                                      // ProfileInfo::cProfileID_Star
    cRes_CourseSelectPlayer,                        // ProfileInfo::cProfileID_CourseSelectPlayer
    cRes_CourseSelectPlayer2PSub,                   // ProfileInfo::cProfileID_CourseSelectPlayer2PSub
    cRes_CourseSelectChibiYoshi,                    // ProfileInfo::cProfileID_CourseSelectChibiYoshi
    nullptr,                                        // ProfileInfo::cProfileID_CourseSelectCamera
    cRes_CourseSelectCastle,                        // ProfileInfo::cProfileID_CourseSelectCastle
    cRes_CourseSelectToride,                        // ProfileInfo::cProfileID_CourseSelectToride
    cRes_CourseSelectKinokoHouse1up,                // ProfileInfo::cProfileID_CourseSelectKinokoHouse1up
    cRes_CourseSelectKinokoHouseShuffle,            // ProfileInfo::cProfileID_CourseSelectKinokoHouseShuffle
    cRes_CourseSelectKinokoHouseSlot,               // ProfileInfo::cProfileID_CourseSelectKinokoHouseSlot
    cRes_CourseSelectPeachGates1st,                 // ProfileInfo::cProfileID_CourseSelectPeachGates1st
    cRes_CourseSelectPeachGates2nd,                 // ProfileInfo::cProfileID_CourseSelectPeachGates2nd
    cRes_CourseSelectCoursePoint,                   // ProfileInfo::cProfileID_CourseSelectCoursePoint
    cRes_CourseSelectWorldMoveDokan,                // ProfileInfo::cProfileID_CourseSelectWorldMoveDokan
    nullptr,                                        // ProfileInfo::cProfileID_CourseSelectW8Cloud
    cRes_CourseSelectGhost,                         // ProfileInfo::cProfileID_CourseSelectGhost
    cRes_CourseSelectW2Bros,                        // ProfileInfo::cProfileID_CourseSelectW2Bros
    cRes_CourseSelectShipW1,                        // ProfileInfo::cProfileID_CourseSelectShipW1
    cRes_CourseSelectShipW2,                        // ProfileInfo::cProfileID_CourseSelectShipW2
    cRes_CourseSelectShipW3,                        // ProfileInfo::cProfileID_CourseSelectShipW3
    cRes_CourseSelectShipW4,                        // ProfileInfo::cProfileID_CourseSelectShipW4
    cRes_CourseSelectShipW5,                        // ProfileInfo::cProfileID_CourseSelectShipW5
    cRes_CourseSelectShipW6,                        // ProfileInfo::cProfileID_CourseSelectShipW6
    cRes_CourseSelectShipW7,                        // ProfileInfo::cProfileID_CourseSelectShipW7
    cRes_CourseSelectShipW8,                        // ProfileInfo::cProfileID_CourseSelectShipW8
    cRes_CourseSelectShipW8Broken,                  // ProfileInfo::cProfileID_CourseSelectShipW8Broken
    cRes_CourseSelectSurrender,                     // ProfileInfo::cProfileID_CourseSelectSurrender
    cRes_CourseSelectSwitchA,                       // ProfileInfo::cProfileID_CourseSelectSwitchA
    cRes_CourseSelectSwitchB,                       // ProfileInfo::cProfileID_CourseSelectSwitchB
    cRes_CourseSelectTeresa,                        // ProfileInfo::cProfileID_CourseSelectTeresa
    cRes_CourseSelectOpeningKameck,                 // ProfileInfo::cProfileID_CourseSelectOpeningKameck
    cRes_CourseSelectTorideBoss,                    // ProfileInfo::cProfileID_CourseSelectTorideBoss
    cRes_CourseSelectPakkun,                        // ProfileInfo::cProfileID_CourseSelectPakkun
    cRes_CourseSelectShadowFirstDemoKinopio,        // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoKinopio
    cRes_CourseSelectTobiPuku,                      // ProfileInfo::cProfileID_CourseSelectTobiPuku
    cRes_CourseSelectChorobon,                      // ProfileInfo::cProfileID_CourseSelectChorobon
    cRes_CourseSelectW7Item,                        // ProfileInfo::cProfileID_CourseSelectW7Item
    cRes_CourseSelectW5Teresa,                      // ProfileInfo::cProfileID_CourseSelectW5Teresa
    cRes_CourseSelectFlag,                          // ProfileInfo::cProfileID_CourseSelectFlag
    cRes_CourseSelectMusasabi,                      // ProfileInfo::cProfileID_CourseSelectMusasabi
    cRes_CourseSelectWPillar,                       // ProfileInfo::cProfileID_CourseSelectWPillar
    cRes_CourseSelectW7Bridge,                      // ProfileInfo::cProfileID_CourseSelectW7Bridge
    cRes_CourseSelectMiiBalloon,                    // ProfileInfo::cProfileID_CourseSelectMiiBalloon
    cRes_CourseSelectPenguin,                       // ProfileInfo::cProfileID_CourseSelectPenguin
    cRes_CourseSelectW4Item,                        // ProfileInfo::cProfileID_CourseSelectW4Item
    cRes_CourseSelectW2Kuribo,                      // ProfileInfo::cProfileID_CourseSelectW2Kuribo
    cRes_CourseSelectPakkunBig,                     // ProfileInfo::cProfileID_CourseSelectPakkunBig
    cRes_CourseSelectShadowKunIcon,                 // ProfileInfo::cProfileID_CourseSelectShadowKunIcon
    cRes_CourseSelectDekaUnira,                     // ProfileInfo::cProfileID_CourseSelectDekaUnira
    cRes_CourseSelectTomb,                          // ProfileInfo::cProfileID_CourseSelectTomb
    cRes_CourseSelectShadowFirstDemoShadowKun,      // ProfileInfo::cProfileID_CourseSelectShadowFirstDemoShadowKun
    cRes_CourseSelectKotsuCoaster,                  // ProfileInfo::cProfileID_CourseSelectKotsuCoaster
    cRes_CourseSelectKoopaJr,                       // ProfileInfo::cProfileID_CourseSelectKoopaJr
    cRes_CourseSelectPeach,                         // ProfileInfo::cProfileID_CourseSelectPeach
    cRes_CourseSelectW1Item,                        // ProfileInfo::cProfileID_CourseSelectW1Item
    cRes_CourseSelectStarGate,                      // ProfileInfo::cProfileID_CourseSelectStarGate
    nullptr,                                        // ProfileInfo::cProfileID_CourseSelectEventAssistant
    cRes_38E,                                       // Profile 910
    cRes_38F,                                       // Profile 911
    nullptr                                         // Profile 912
};

// -------------------------------------------- ID -------------------------------------------- //

const s32 ProfileInfo::cProfileID_000                                       =   0;
const s32 ProfileInfo::cProfileID_001                                       =   1;
const s32 ProfileInfo::cProfileID_002                                       =   2;
const s32 ProfileInfo::cProfileID_003                                       =   3;
const s32 ProfileInfo::cProfileID_004                                       =   4;
const s32 ProfileInfo::cProfileID_005                                       =   5;
const s32 ProfileInfo::cProfileID_006                                       =   6;
const s32 ProfileInfo::cProfileID_007                                       =   7;
const s32 ProfileInfo::cProfileID_008                                       =   8;
const s32 ProfileInfo::cProfileID_009                                       =   9;
const s32 ProfileInfo::cProfileID_00A                                       =  10;
const s32 ProfileInfo::cProfileID_00B                                       =  11;
const s32 ProfileInfo::cProfileID_00C                                       =  12;
const s32 ProfileInfo::cProfileID_00D                                       =  13;
const s32 ProfileInfo::cProfileID_00E                                       =  14;
const s32 ProfileInfo::cProfileID_00F                                       =  15;
const s32 ProfileInfo::cProfileID_010                                       =  16;
const s32 ProfileInfo::cProfileID_011                                       =  17;
const s32 ProfileInfo::cProfileID_012                                       =  18;
const s32 ProfileInfo::cProfileID_013                                       =  19;
const s32 ProfileInfo::cProfileID_014                                       =  20;
const s32 ProfileInfo::cProfileID_015                                       =  21;
const s32 ProfileInfo::cProfileID_016                                       =  22;
const s32 ProfileInfo::cProfileID_017                                       =  23;
const s32 ProfileInfo::cProfileID_MiniGameMgr                               =  24;
const s32 ProfileInfo::cProfileID_MiniGameMgrRDash                          =  25;
const s32 ProfileInfo::cProfileID_ShuffleBlockMgr                           =  26;
const s32 ProfileInfo::cProfileID_SlotMgr                                   =  27;
const s32 ProfileInfo::cProfileID_CoinmakiMgr                               =  28;
const s32 ProfileInfo::cProfileID_01D                                       =  29;
const s32 ProfileInfo::cProfileID_01E                                       =  30;
const s32 ProfileInfo::cProfileID_01F                                       =  31;
const s32 ProfileInfo::cProfileID_020                                       =  32;
const s32 ProfileInfo::cProfileID_ShootingStar                              =  33;
const s32 ProfileInfo::cProfileID_StaffRollMgr                              =  34;
const s32 ProfileInfo::cProfileID_StaffRollMgrRDash                         =  35;
const s32 ProfileInfo::cProfileID_024                                       =  36;
const s32 ProfileInfo::cProfileID_025                                       =  37;
const s32 ProfileInfo::cProfileID_026                                       =  38;
const s32 ProfileInfo::cProfileID_027                                       =  39;
const s32 ProfileInfo::cProfileID_028                                       =  40;
const s32 ProfileInfo::cProfileID_029                                       =  41;
const s32 ProfileInfo::cProfileID_02A                                       =  42;
const s32 ProfileInfo::cProfileID_02B                                       =  43;
const s32 ProfileInfo::cProfileID_02C                                       =  44;
const s32 ProfileInfo::cProfileID_02D                                       =  45;
const s32 ProfileInfo::cProfileID_02E                                       =  46;
const s32 ProfileInfo::cProfileID_02F                                       =  47;
const s32 ProfileInfo::cProfileID_030                                       =  48;
const s32 ProfileInfo::cProfileID_031                                       =  49;
const s32 ProfileInfo::cProfileID_032                                       =  50;
const s32 ProfileInfo::cProfileID_033                                       =  51;
const s32 ProfileInfo::cProfileID_ElasticKinokoParent                       =  52;
const s32 ProfileInfo::cProfileID_FloorGyration                             =  53;
const s32 ProfileInfo::cProfileID_036                                       =  54;
const s32 ProfileInfo::cProfileID_037                                       =  55;
const s32 ProfileInfo::cProfileID_038                                       =  56;
const s32 ProfileInfo::cProfileID_039                                       =  57;
const s32 ProfileInfo::cProfileID_03A                                       =  58;
const s32 ProfileInfo::cProfileID_03B                                       =  59;
const s32 ProfileInfo::cProfileID_PairObjChild                              =  60;
const s32 ProfileInfo::cProfileID_03D                                       =  61;
const s32 ProfileInfo::cProfileID_03E                                       =  62;
const s32 ProfileInfo::cProfileID_03F                                       =  63;
const s32 ProfileInfo::cProfileID_040                                       =  64;
const s32 ProfileInfo::cProfileID_041                                       =  65;
const s32 ProfileInfo::cProfileID_042                                       =  66;
const s32 ProfileInfo::cProfileID_043                                       =  67;
const s32 ProfileInfo::cProfileID_044                                       =  68;
const s32 ProfileInfo::cProfileID_045                                       =  69;
const s32 ProfileInfo::cProfileID_046                                       =  70;
const s32 ProfileInfo::cProfileID_047                                       =  71;
const s32 ProfileInfo::cProfileID_048                                       =  72;
const s32 ProfileInfo::cProfileID_049                                       =  73;
const s32 ProfileInfo::cProfileID_04A                                       =  74;
const s32 ProfileInfo::cProfileID_04B                                       =  75;
const s32 ProfileInfo::cProfileID_04C                                       =  76;
const s32 ProfileInfo::cProfileID_KinokoLift                                =  77;
const s32 ProfileInfo::cProfileID_KinokoLiftColor                           =  78;
const s32 ProfileInfo::cProfileID_LiftZenStar                               =  79;
const s32 ProfileInfo::cProfileID_050                                       =  80;
const s32 ProfileInfo::cProfileID_051                                       =  81;
const s32 ProfileInfo::cProfileID_052                                       =  82;
const s32 ProfileInfo::cProfileID_053                                       =  83;
const s32 ProfileInfo::cProfileID_054                                       =  84;
const s32 ProfileInfo::cProfileID_055                                       =  85;
const s32 ProfileInfo::cProfileID_056                                       =  86;
const s32 ProfileInfo::cProfileID_057                                       =  87;
const s32 ProfileInfo::cProfileID_058                                       =  88;
const s32 ProfileInfo::cProfileID_059                                       =  89;
const s32 ProfileInfo::cProfileID_BgActorYukaMario                          =  90;
const s32 ProfileInfo::cProfileID_05B                                       =  91;
const s32 ProfileInfo::cProfileID_05C                                       =  92;
const s32 ProfileInfo::cProfileID_05D                                       =  93;
const s32 ProfileInfo::cProfileID_05E                                       =  94;
const s32 ProfileInfo::cProfileID_05F                                       =  95;
const s32 ProfileInfo::cProfileID_060                                       =  96;
const s32 ProfileInfo::cProfileID_061                                       =  97;
const s32 ProfileInfo::cProfileID_062                                       =  98;
const s32 ProfileInfo::cProfileID_063                                       =  99;
const s32 ProfileInfo::cProfileID_064                                       = 100;
const s32 ProfileInfo::cProfileID_KillerHoudai                              = 101;
const s32 ProfileInfo::cProfileID_StretchKillerHoudai                       = 102;
const s32 ProfileInfo::cProfileID_MagnumKillerHoudai                        = 103;
const s32 ProfileInfo::cProfileID_MagnumKillerHoudaiDown                    = 104;
const s32 ProfileInfo::cProfileID_SearchKillerHoudai                        = 105;
const s32 ProfileInfo::cProfileID_SearchMagnumKillerHoudai                  = 106;
const s32 ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDown              = 107;
const s32 ProfileInfo::cProfileID_MagnumKillerHoudaiRDash                   = 108;
const s32 ProfileInfo::cProfileID_MagnumKillerHoudaiDownRDash               = 109;
const s32 ProfileInfo::cProfileID_SearchMagnumKillerHoudaiRDash             = 110;
const s32 ProfileInfo::cProfileID_SearchMagnumKillerHoudaiDownRDash         = 111;
const s32 ProfileInfo::cProfileID_070                                       = 112;
const s32 ProfileInfo::cProfileID_071                                       = 113;
const s32 ProfileInfo::cProfileID_072                                       = 114;
const s32 ProfileInfo::cProfileID_073                                       = 115;
const s32 ProfileInfo::cProfileID_074                                       = 116;
const s32 ProfileInfo::cProfileID_075                                       = 117;
const s32 ProfileInfo::cProfileID_076                                       = 118;
const s32 ProfileInfo::cProfileID_077                                       = 119;
const s32 ProfileInfo::cProfileID_078                                       = 120;
const s32 ProfileInfo::cProfileID_Intermittent                              = 121;
const s32 ProfileInfo::cProfileID_IntermittentPermanent                     = 122;
const s32 ProfileInfo::cProfileID_WaterIntermittent                         = 123;
const s32 ProfileInfo::cProfileID_WaterIntermittentPermanent                = 124;
const s32 ProfileInfo::cProfileID_WaterIntermittentPermanentRD3_3           = 125;
const s32 ProfileInfo::cProfileID_07E                                       = 126;
const s32 ProfileInfo::cProfileID_WaterIntermittentBossChild                = 127;
const s32 ProfileInfo::cProfileID_YoganIntermittent                         = 128;
const s32 ProfileInfo::cProfileID_081                                       = 129;
const s32 ProfileInfo::cProfileID_082                                       = 130;
const s32 ProfileInfo::cProfileID_083                                       = 131;
const s32 ProfileInfo::cProfileID_084                                       = 132;
const s32 ProfileInfo::cProfileID_085                                       = 133;
const s32 ProfileInfo::cProfileID_ObjPipeDownNG                             = 134;
const s32 ProfileInfo::cProfileID_087                                       = 135;
const s32 ProfileInfo::cProfileID_088                                       = 136;
const s32 ProfileInfo::cProfileID_089                                       = 137;
const s32 ProfileInfo::cProfileID_08A                                       = 138;
const s32 ProfileInfo::cProfileID_08B                                       = 139;
const s32 ProfileInfo::cProfileID_08C                                       = 140;
const s32 ProfileInfo::cProfileID_08D                                       = 141;
const s32 ProfileInfo::cProfileID_08E                                       = 142;
const s32 ProfileInfo::cProfileID_08F                                       = 143;
const s32 ProfileInfo::cProfileID_090                                       = 144;
const s32 ProfileInfo::cProfileID_091                                       = 145;
const s32 ProfileInfo::cProfileID_092                                       = 146;
const s32 ProfileInfo::cProfileID_093                                       = 147;
const s32 ProfileInfo::cProfileID_094                                       = 148;
const s32 ProfileInfo::cProfileID_095                                       = 149;
const s32 ProfileInfo::cProfileID_096                                       = 150;
const s32 ProfileInfo::cProfileID_097                                       = 151;
const s32 ProfileInfo::cProfileID_098                                       = 152;
const s32 ProfileInfo::cProfileID_099                                       = 153;
const s32 ProfileInfo::cProfileID_09A                                       = 154;
const s32 ProfileInfo::cProfileID_09B                                       = 155;
const s32 ProfileInfo::cProfileID_09C                                       = 156;
const s32 ProfileInfo::cProfileID_09D                                       = 157;
const s32 ProfileInfo::cProfileID_09E                                       = 158;
const s32 ProfileInfo::cProfileID_09F                                       = 159;
const s32 ProfileInfo::cProfileID_0A0                                       = 160;
const s32 ProfileInfo::cProfileID_0A1                                       = 161;
const s32 ProfileInfo::cProfileID_0A2                                       = 162;
const s32 ProfileInfo::cProfileID_0A3                                       = 163;
const s32 ProfileInfo::cProfileID_0A4                                       = 164;
const s32 ProfileInfo::cProfileID_0A5                                       = 165;
const s32 ProfileInfo::cProfileID_0A6                                       = 166;
const s32 ProfileInfo::cProfileID_0A7                                       = 167;
const s32 ProfileInfo::cProfileID_0A8                                       = 168;
const s32 ProfileInfo::cProfileID_0A9                                       = 169;
const s32 ProfileInfo::cProfileID_0AA                                       = 170;
const s32 ProfileInfo::cProfileID_0AB                                       = 171;
const s32 ProfileInfo::cProfileID_0AC                                       = 172;
const s32 ProfileInfo::cProfileID_0AD                                       = 173;
const s32 ProfileInfo::cProfileID_0AE                                       = 174;
const s32 ProfileInfo::cProfileID_0AF                                       = 175;
const s32 ProfileInfo::cProfileID_0B0                                       = 176;
const s32 ProfileInfo::cProfileID_0B1                                       = 177;
const s32 ProfileInfo::cProfileID_0B2                                       = 178;
const s32 ProfileInfo::cProfileID_0B3                                       = 179;
const s32 ProfileInfo::cProfileID_0B4                                       = 180;
const s32 ProfileInfo::cProfileID_0B5                                       = 181;
const s32 ProfileInfo::cProfileID_0B6                                       = 182;
const s32 ProfileInfo::cProfileID_0B7                                       = 183;
const s32 ProfileInfo::cProfileID_LineSpinLift                              = 184;
const s32 ProfileInfo::cProfileID_LineSpinLiftParentRDash                   = 185;
const s32 ProfileInfo::cProfileID_LineSpinLiftChildRDash                    = 186;
const s32 ProfileInfo::cProfileID_0BB                                       = 187;
const s32 ProfileInfo::cProfileID_0BC                                       = 188;
const s32 ProfileInfo::cProfileID_0BD                                       = 189;
const s32 ProfileInfo::cProfileID_0BE                                       = 190;
const s32 ProfileInfo::cProfileID_0BF                                       = 191;
const s32 ProfileInfo::cProfileID_0C0                                       = 192;
const s32 ProfileInfo::cProfileID_0C1                                       = 193;
const s32 ProfileInfo::cProfileID_SnakeBlock                                = 194;
const s32 ProfileInfo::cProfileID_0C3                                       = 195;
const s32 ProfileInfo::cProfileID_0C4                                       = 196;
const s32 ProfileInfo::cProfileID_0C5                                       = 197;
const s32 ProfileInfo::cProfileID_0C6                                       = 198;
const s32 ProfileInfo::cProfileID_0C7                                       = 199;
const s32 ProfileInfo::cProfileID_0C8                                       = 200;
const s32 ProfileInfo::cProfileID_0C9                                       = 201;
const s32 ProfileInfo::cProfileID_0CA                                       = 202;
const s32 ProfileInfo::cProfileID_0CB                                       = 203;
const s32 ProfileInfo::cProfileID_0CC                                       = 204;
const s32 ProfileInfo::cProfileID_0CD                                       = 205;
const s32 ProfileInfo::cProfileID_0CE                                       = 206;
const s32 ProfileInfo::cProfileID_0CF                                       = 207;
const s32 ProfileInfo::cProfileID_0D0                                       = 208;
const s32 ProfileInfo::cProfileID_0D1                                       = 209;
const s32 ProfileInfo::cProfileID_FloorHoleDokan                            = 210;
const s32 ProfileInfo::cProfileID_0D3                                       = 211;
const s32 ProfileInfo::cProfileID_0D4                                       = 212;
const s32 ProfileInfo::cProfileID_0D5                                       = 213;
const s32 ProfileInfo::cProfileID_0D6                                       = 214;
const s32 ProfileInfo::cProfileID_0D7                                       = 215;
const s32 ProfileInfo::cProfileID_0D8                                       = 216;
const s32 ProfileInfo::cProfileID_0D9                                       = 217;
const s32 ProfileInfo::cProfileID_0DA                                       = 218;
const s32 ProfileInfo::cProfileID_0DB                                       = 219;
const s32 ProfileInfo::cProfileID_0DC                                       = 220;
const s32 ProfileInfo::cProfileID_0DD                                       = 221;
const s32 ProfileInfo::cProfileID_0DE                                       = 222;
const s32 ProfileInfo::cProfileID_0DF                                       = 223;
const s32 ProfileInfo::cProfileID_Burner                                    = 224;
const s32 ProfileInfo::cProfileID_0E1                                       = 225;
const s32 ProfileInfo::cProfileID_0E2                                       = 226;
const s32 ProfileInfo::cProfileID_0E3                                       = 227;
const s32 ProfileInfo::cProfileID_0E4                                       = 228;
const s32 ProfileInfo::cProfileID_0E5                                       = 229;
const s32 ProfileInfo::cProfileID_0E6                                       = 230;
const s32 ProfileInfo::cProfileID_0E7                                       = 231;
const s32 ProfileInfo::cProfileID_0E8                                       = 232;
const s32 ProfileInfo::cProfileID_0E9                                       = 233;
const s32 ProfileInfo::cProfileID_0EA                                       = 234;
const s32 ProfileInfo::cProfileID_0EB                                       = 235;
const s32 ProfileInfo::cProfileID_0EC                                       = 236;
const s32 ProfileInfo::cProfileID_PlyIce                                    = 237;
const s32 ProfileInfo::cProfileID_TarzanIvy                                 = 238;
const s32 ProfileInfo::cProfileID_0EF                                       = 239;
const s32 ProfileInfo::cProfileID_0F0                                       = 240;
const s32 ProfileInfo::cProfileID_0F1                                       = 241;
const s32 ProfileInfo::cProfileID_0F2                                       = 242;
const s32 ProfileInfo::cProfileID_0F3                                       = 243;
const s32 ProfileInfo::cProfileID_0F4                                       = 244;
const s32 ProfileInfo::cProfileID_0F5                                       = 245;
const s32 ProfileInfo::cProfileID_0F6                                       = 246;
const s32 ProfileInfo::cProfileID_0F7                                       = 247;
const s32 ProfileInfo::cProfileID_0F8                                       = 248;
const s32 ProfileInfo::cProfileID_0F9                                       = 249;
const s32 ProfileInfo::cProfileID_0FA                                       = 250;
const s32 ProfileInfo::cProfileID_0FB                                       = 251;
const s32 ProfileInfo::cProfileID_0FC                                       = 252;
const s32 ProfileInfo::cProfileID_0FD                                       = 253;
const s32 ProfileInfo::cProfileID_0FE                                       = 254;
const s32 ProfileInfo::cProfileID_0FF                                       = 255;
const s32 ProfileInfo::cProfileID_100                                       = 256;
const s32 ProfileInfo::cProfileID_101                                       = 257;
const s32 ProfileInfo::cProfileID_102                                       = 258;
const s32 ProfileInfo::cProfileID_103                                       = 259;
const s32 ProfileInfo::cProfileID_104                                       = 260;
const s32 ProfileInfo::cProfileID_ShuffleBlock                              = 261;
const s32 ProfileInfo::cProfileID_KokoopaShipWarpCannon                     = 262;
const s32 ProfileInfo::cProfileID_107                                       = 263;
const s32 ProfileInfo::cProfileID_108                                       = 264;
const s32 ProfileInfo::cProfileID_KoopaShutter                              = 265;
const s32 ProfileInfo::cProfileID_10A                                       = 266;
const s32 ProfileInfo::cProfileID_10B                                       = 267;
const s32 ProfileInfo::cProfileID_10C                                       = 268;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLift               = 269;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftHmove          = 270;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJrLiftPairObj        = 271;
const s32 ProfileInfo::cProfileID_RoyLiftWakiStep                           = 272;
const s32 ProfileInfo::cProfileID_WendyFloor                                = 273;
const s32 ProfileInfo::cProfileID_IggyRoom                                  = 274;
const s32 ProfileInfo::cProfileID_113                                       = 275;
const s32 ProfileInfo::cProfileID_114                                       = 276;
const s32 ProfileInfo::cProfileID_115                                       = 277;
const s32 ProfileInfo::cProfileID_116                                       = 278;
const s32 ProfileInfo::cProfileID_117                                       = 279;
const s32 ProfileInfo::cProfileID_118                                       = 280;
const s32 ProfileInfo::cProfileID_119                                       = 281;
const s32 ProfileInfo::cProfileID_11A                                       = 282;
const s32 ProfileInfo::cProfileID_11B                                       = 283;
const s32 ProfileInfo::cProfileID_11C                                       = 284;
const s32 ProfileInfo::cProfileID_11D                                       = 285;
const s32 ProfileInfo::cProfileID_11E                                       = 286;
const s32 ProfileInfo::cProfileID_Block                                     = 287;
const s32 ProfileInfo::cProfileID_120                                       = 288;
const s32 ProfileInfo::cProfileID_121                                       = 289;
const s32 ProfileInfo::cProfileID_122                                       = 290;
const s32 ProfileInfo::cProfileID_ActorBlockRenga                           = 291;
const s32 ProfileInfo::cProfileID_124                                       = 292;
const s32 ProfileInfo::cProfileID_125                                       = 293;
const s32 ProfileInfo::cProfileID_126                                       = 294;
const s32 ProfileInfo::cProfileID_127                                       = 295;
const s32 ProfileInfo::cProfileID_128                                       = 296;
const s32 ProfileInfo::cProfileID_129                                       = 297;
const s32 ProfileInfo::cProfileID_12A                                       = 298;
const s32 ProfileInfo::cProfileID_12B                                       = 299;
const s32 ProfileInfo::cProfileID_12C                                       = 300;
const s32 ProfileInfo::cProfileID_12D                                       = 301;
const s32 ProfileInfo::cProfileID_12E                                       = 302;
const s32 ProfileInfo::cProfileID_12F                                       = 303;
const s32 ProfileInfo::cProfileID_130                                       = 304;
const s32 ProfileInfo::cProfileID_131                                       = 305;
const s32 ProfileInfo::cProfileID_132                                       = 306;
const s32 ProfileInfo::cProfileID_133                                       = 307;
const s32 ProfileInfo::cProfileID_134                                       = 308;
const s32 ProfileInfo::cProfileID_ActorBlockMakeDRC                         = 309;
const s32 ProfileInfo::cProfileID_136                                       = 310;
const s32 ProfileInfo::cProfileID_137                                       = 311;
const s32 ProfileInfo::cProfileID_138                                       = 312;
const s32 ProfileInfo::cProfileID_139                                       = 313;
const s32 ProfileInfo::cProfileID_13A                                       = 314;
const s32 ProfileInfo::cProfileID_13B                                       = 315;
const s32 ProfileInfo::cProfileID_13C                                       = 316;
const s32 ProfileInfo::cProfileID_13D                                       = 317;
const s32 ProfileInfo::cProfileID_13E                                       = 318;
const s32 ProfileInfo::cProfileID_13F                                       = 319;
const s32 ProfileInfo::cProfileID_140                                       = 320;
const s32 ProfileInfo::cProfileID_141                                       = 321;
const s32 ProfileInfo::cProfileID_142                                       = 322;
const s32 ProfileInfo::cProfileID_143                                       = 323;
const s32 ProfileInfo::cProfileID_144                                       = 324;
const s32 ProfileInfo::cProfileID_145                                       = 325;
const s32 ProfileInfo::cProfileID_146                                       = 326;
const s32 ProfileInfo::cProfileID_147                                       = 327;
const s32 ProfileInfo::cProfileID_148                                       = 328;
const s32 ProfileInfo::cProfileID_149                                       = 329;
const s32 ProfileInfo::cProfileID_14A                                       = 330;
const s32 ProfileInfo::cProfileID_14B                                       = 331;
const s32 ProfileInfo::cProfileID_14C                                       = 332;
const s32 ProfileInfo::cProfileID_14D                                       = 333;
const s32 ProfileInfo::cProfileID_14E                                       = 334;
const s32 ProfileInfo::cProfileID_14F                                       = 335;
const s32 ProfileInfo::cProfileID_ObjPipeDown                               = 336;
const s32 ProfileInfo::cProfileID_151                                       = 337;
const s32 ProfileInfo::cProfileID_152                                       = 338;
const s32 ProfileInfo::cProfileID_153                                       = 339;
const s32 ProfileInfo::cProfileID_ObjPipeDownGroup                          = 340;
const s32 ProfileInfo::cProfileID_155                                       = 341;
const s32 ProfileInfo::cProfileID_156                                       = 342;
const s32 ProfileInfo::cProfileID_157                                       = 343;
const s32 ProfileInfo::cProfileID_SwitchHatenaButton                        = 344;
const s32 ProfileInfo::cProfileID_SwitchPbutton                             = 345;
const s32 ProfileInfo::cProfileID_SwitchPbuttonRDash                        = 346;
const s32 ProfileInfo::cProfileID_SwitchPbuttonNoWallKick                   = 347;
const s32 ProfileInfo::cProfileID_15C                                       = 348;
const s32 ProfileInfo::cProfileID_15D                                       = 349;
const s32 ProfileInfo::cProfileID_IcicleBig                                 = 350;
const s32 ProfileInfo::cProfileID_LemmyBall                                 = 351;
const s32 ProfileInfo::cProfileID_LemmyBomb                                 = 352;
const s32 ProfileInfo::cProfileID_161                                       = 353;
const s32 ProfileInfo::cProfileID_162                                       = 354;
const s32 ProfileInfo::cProfileID_163                                       = 355;
const s32 ProfileInfo::cProfileID_164                                       = 356;
const s32 ProfileInfo::cProfileID_165                                       = 357;
const s32 ProfileInfo::cProfileID_166                                       = 358;
const s32 ProfileInfo::cProfileID_167                                       = 359;
const s32 ProfileInfo::cProfileID_168                                       = 360;
const s32 ProfileInfo::cProfileID_169                                       = 361;
const s32 ProfileInfo::cProfileID_PentaroIce                                = 362;
const s32 ProfileInfo::cProfileID_16B                                       = 363;
const s32 ProfileInfo::cProfileID_16C                                       = 364;
const s32 ProfileInfo::cProfileID_16D                                       = 365;
const s32 ProfileInfo::cProfileID_16E                                       = 366;
const s32 ProfileInfo::cProfileID_16F                                       = 367;
const s32 ProfileInfo::cProfileID_KameckIce                                 = 368;
const s32 ProfileInfo::cProfileID_WendyIcicle                               = 369;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJrClown              = 370;
const s32 ProfileInfo::cProfileID_BoxingKoopaJrClown                        = 371;
const s32 ProfileInfo::cProfileID_174                                       = 372;
const s32 ProfileInfo::cProfileID_FinalKoopaJrClown                         = 373;
const s32 ProfileInfo::cProfileID_FinalKoopa                                = 374;
const s32 ProfileInfo::cProfileID_FireBar                                   = 375;
const s32 ProfileInfo::cProfileID_FireBarSync                               = 376;
const s32 ProfileInfo::cProfileID_179                                       = 377;
const s32 ProfileInfo::cProfileID_17A                                       = 378;
const s32 ProfileInfo::cProfileID_17B                                       = 379;
const s32 ProfileInfo::cProfileID_17C                                       = 380;
const s32 ProfileInfo::cProfileID_17D                                       = 381;
const s32 ProfileInfo::cProfileID_17E                                       = 382;
const s32 ProfileInfo::cProfileID_17F                                       = 383;
const s32 ProfileInfo::cProfileID_180                                       = 384;
const s32 ProfileInfo::cProfileID_181                                       = 385;
const s32 ProfileInfo::cProfileID_182                                       = 386;
const s32 ProfileInfo::cProfileID_183                                       = 387;
const s32 ProfileInfo::cProfileID_184                                       = 388;
const s32 ProfileInfo::cProfileID_185                                       = 389;
const s32 ProfileInfo::cProfileID_186                                       = 390;
const s32 ProfileInfo::cProfileID_187                                       = 391;
const s32 ProfileInfo::cProfileID_188                                       = 392;
const s32 ProfileInfo::cProfileID_189                                       = 393;
const s32 ProfileInfo::cProfileID_18A                                       = 394;
const s32 ProfileInfo::cProfileID_ActorCoin                                 = 395;
const s32 ProfileInfo::cProfileID_18C                                       = 396;
const s32 ProfileInfo::cProfileID_18D                                       = 397;
const s32 ProfileInfo::cProfileID_18E                                       = 398;
const s32 ProfileInfo::cProfileID_18F                                       = 399;
const s32 ProfileInfo::cProfileID_190                                       = 400;
const s32 ProfileInfo::cProfileID_191                                       = 401;
const s32 ProfileInfo::cProfileID_192                                       = 402;
const s32 ProfileInfo::cProfileID_193                                       = 403;
const s32 ProfileInfo::cProfileID_194                                       = 404;
const s32 ProfileInfo::cProfileID_195                                       = 405;
const s32 ProfileInfo::cProfileID_196                                       = 406;
const s32 ProfileInfo::cProfileID_197                                       = 407;
const s32 ProfileInfo::cProfileID_198                                       = 408;
const s32 ProfileInfo::cProfileID_199                                       = 409;
const s32 ProfileInfo::cProfileID_19A                                       = 410;
const s32 ProfileInfo::cProfileID_19B                                       = 411;
const s32 ProfileInfo::cProfileID_19C                                       = 412;
const s32 ProfileInfo::cProfileID_19D                                       = 413;
const s32 ProfileInfo::cProfileID_19E                                       = 414;
const s32 ProfileInfo::cProfileID_19F                                       = 415;
const s32 ProfileInfo::cProfileID_1A0                                       = 416;
const s32 ProfileInfo::cProfileID_1A1                                       = 417;
const s32 ProfileInfo::cProfileID_1A2                                       = 418;
const s32 ProfileInfo::cProfileID_1A3                                       = 419;
const s32 ProfileInfo::cProfileID_1A4                                       = 420;
const s32 ProfileInfo::cProfileID_1A5                                       = 421;
const s32 ProfileInfo::cProfileID_1A6                                       = 422;
const s32 ProfileInfo::cProfileID_1A7                                       = 423;
const s32 ProfileInfo::cProfileID_1A8                                       = 424;
const s32 ProfileInfo::cProfileID_BlueCoin                                  = 425;
const s32 ProfileInfo::cProfileID_1AA                                       = 426;
const s32 ProfileInfo::cProfileID_1AB                                       = 427;
const s32 ProfileInfo::cProfileID_1AC                                       = 428;
const s32 ProfileInfo::cProfileID_1AD                                       = 429;
const s32 ProfileInfo::cProfileID_1AE                                       = 430;
const s32 ProfileInfo::cProfileID_1AF                                       = 431;
const s32 ProfileInfo::cProfileID_1B0                                       = 432;
const s32 ProfileInfo::cProfileID_1B1                                       = 433;
const s32 ProfileInfo::cProfileID_1B2                                       = 434;
const s32 ProfileInfo::cProfileID_1B3                                       = 435;
const s32 ProfileInfo::cProfileID_1B4                                       = 436;
const s32 ProfileInfo::cProfileID_1B5                                       = 437;
const s32 ProfileInfo::cProfileID_CoinmakiCoin                              = 438;
const s32 ProfileInfo::cProfileID_1B7                                       = 439;
const s32 ProfileInfo::cProfileID_1B8                                       = 440;
const s32 ProfileInfo::cProfileID_1B9                                       = 441;
const s32 ProfileInfo::cProfileID_Yoshi                                     = 442;
const s32 ProfileInfo::cProfileID_TottenPlayer                              = 443;
const s32 ProfileInfo::cProfileID_PlayerObject                              = 444;
const s32 ProfileInfo::cProfileID_1BD                                       = 445;
const s32 ProfileInfo::cProfileID_1BE                                       = 446;
const s32 ProfileInfo::cProfileID_1BF                                       = 447;
const s32 ProfileInfo::cProfileID_1C0                                       = 448;
const s32 ProfileInfo::cProfileID_1C1                                       = 449;
const s32 ProfileInfo::cProfileID_1C2                                       = 450;
const s32 ProfileInfo::cProfileID_1C3                                       = 451;
const s32 ProfileInfo::cProfileID_1C4                                       = 452;
const s32 ProfileInfo::cProfileID_SlotYoshiChibi                            = 453;
const s32 ProfileInfo::cProfileID_1C6                                       = 454;
const s32 ProfileInfo::cProfileID_1C7                                       = 455;
const s32 ProfileInfo::cProfileID_1C8                                       = 456;
const s32 ProfileInfo::cProfileID_1C9                                       = 457;
const s32 ProfileInfo::cProfileID_1CA                                       = 458;
const s32 ProfileInfo::cProfileID_1CB                                       = 459;
const s32 ProfileInfo::cProfileID_1CC                                       = 460;
const s32 ProfileInfo::cProfileID_1CD                                       = 461;
const s32 ProfileInfo::cProfileID_1CE                                       = 462;
const s32 ProfileInfo::cProfileID_QuestPrizeItem                            = 463;
const s32 ProfileInfo::cProfileID_1D0                                       = 464;
const s32 ProfileInfo::cProfileID_1D1                                       = 465;
const s32 ProfileInfo::cProfileID_1D2                                       = 466;
const s32 ProfileInfo::cProfileID_1D3                                       = 467;
const s32 ProfileInfo::cProfileID_1D4                                       = 468;
const s32 ProfileInfo::cProfileID_1D5                                       = 469;
const s32 ProfileInfo::cProfileID_1D6                                       = 470;
const s32 ProfileInfo::cProfileID_1D7                                       = 471;
const s32 ProfileInfo::cProfileID_1D8                                       = 472;
const s32 ProfileInfo::cProfileID_1D9                                       = 473;
const s32 ProfileInfo::cProfileID_IceBall                                   = 474;
const s32 ProfileInfo::cProfileID_IceBallPakkun                             = 475;
const s32 ProfileInfo::cProfileID_FireBallPlayer                            = 476;
const s32 ProfileInfo::cProfileID_FireBallPakkun                            = 477;
const s32 ProfileInfo::cProfileID_YoshiFire                                 = 478;
const s32 ProfileInfo::cProfileID_1DF                                       = 479;
const s32 ProfileInfo::cProfileID_1E0                                       = 480;
const s32 ProfileInfo::cProfileID_1E1                                       = 481;
const s32 ProfileInfo::cProfileID_1E2                                       = 482;
const s32 ProfileInfo::cProfileID_1E3                                       = 483;
const s32 ProfileInfo::cProfileID_1E4                                       = 484;
const s32 ProfileInfo::cProfileID_1E5                                       = 485;
const s32 ProfileInfo::cProfileID_1E6                                       = 486;
const s32 ProfileInfo::cProfileID_1E7                                       = 487;
const s32 ProfileInfo::cProfileID_1E8                                       = 488;
const s32 ProfileInfo::cProfileID_1E9                                       = 489;
const s32 ProfileInfo::cProfileID_1EA                                       = 490;
const s32 ProfileInfo::cProfileID_1EB                                       = 491;
const s32 ProfileInfo::cProfileID_1EC                                       = 492;
const s32 ProfileInfo::cProfileID_1ED                                       = 493;
const s32 ProfileInfo::cProfileID_1EE                                       = 494;
const s32 ProfileInfo::cProfileID_1EF                                       = 495;
const s32 ProfileInfo::cProfileID_1F0                                       = 496;
const s32 ProfileInfo::cProfileID_1F1                                       = 497;
const s32 ProfileInfo::cProfileID_1F2                                       = 498;
const s32 ProfileInfo::cProfileID_1F3                                       = 499;
const s32 ProfileInfo::cProfileID_1F4                                       = 500;
const s32 ProfileInfo::cProfileID_1F5                                       = 501;
const s32 ProfileInfo::cProfileID_1F6                                       = 502;
const s32 ProfileInfo::cProfileID_1F7                                       = 503;
const s32 ProfileInfo::cProfileID_1F8                                       = 504;
const s32 ProfileInfo::cProfileID_1F9                                       = 505;
const s32 ProfileInfo::cProfileID_1FA                                       = 506;
const s32 ProfileInfo::cProfileID_1FB                                       = 507;
const s32 ProfileInfo::cProfileID_1FC                                       = 508;
const s32 ProfileInfo::cProfileID_1FD                                       = 509;
const s32 ProfileInfo::cProfileID_1FE                                       = 510;
const s32 ProfileInfo::cProfileID_1FF                                       = 511;
const s32 ProfileInfo::cProfileID_Nokonoko                                  = 512;
const s32 ProfileInfo::cProfileID_201                                       = 513;
const s32 ProfileInfo::cProfileID_202                                       = 514;
const s32 ProfileInfo::cProfileID_203                                       = 515;
const s32 ProfileInfo::cProfileID_204                                       = 516;
const s32 ProfileInfo::cProfileID_205                                       = 517;
const s32 ProfileInfo::cProfileID_206                                       = 518;
const s32 ProfileInfo::cProfileID_207                                       = 519;
const s32 ProfileInfo::cProfileID_208                                       = 520;
const s32 ProfileInfo::cProfileID_209                                       = 521;
const s32 ProfileInfo::cProfileID_20A                                       = 522;
const s32 ProfileInfo::cProfileID_20B                                       = 523;
const s32 ProfileInfo::cProfileID_MechaKoopa                                = 524;
const s32 ProfileInfo::cProfileID_20D                                       = 525;
const s32 ProfileInfo::cProfileID_20E                                       = 526;
const s32 ProfileInfo::cProfileID_20F                                       = 527;
const s32 ProfileInfo::cProfileID_210                                       = 528;
const s32 ProfileInfo::cProfileID_211                                       = 529;
const s32 ProfileInfo::cProfileID_212                                       = 530;
const s32 ProfileInfo::cProfileID_213                                       = 531;
const s32 ProfileInfo::cProfileID_214                                       = 532;
const s32 ProfileInfo::cProfileID_215                                       = 533;
const s32 ProfileInfo::cProfileID_216                                       = 534;
const s32 ProfileInfo::cProfileID_217                                       = 535;
const s32 ProfileInfo::cProfileID_218                                       = 536;
const s32 ProfileInfo::cProfileID_219                                       = 537;
const s32 ProfileInfo::cProfileID_21A                                       = 538;
const s32 ProfileInfo::cProfileID_21B                                       = 539;
const s32 ProfileInfo::cProfileID_21C                                       = 540;
const s32 ProfileInfo::cProfileID_21D                                       = 541;
const s32 ProfileInfo::cProfileID_21E                                       = 542;
const s32 ProfileInfo::cProfileID_21F                                       = 543;
const s32 ProfileInfo::cProfileID_220                                       = 544;
const s32 ProfileInfo::cProfileID_221                                       = 545;
const s32 ProfileInfo::cProfileID_222                                       = 546;
const s32 ProfileInfo::cProfileID_223                                       = 547;
const s32 ProfileInfo::cProfileID_224                                       = 548;
const s32 ProfileInfo::cProfileID_225                                       = 549;
const s32 ProfileInfo::cProfileID_226                                       = 550;
const s32 ProfileInfo::cProfileID_227                                       = 551;
const s32 ProfileInfo::cProfileID_228                                       = 552;
const s32 ProfileInfo::cProfileID_229                                       = 553;
const s32 ProfileInfo::cProfileID_22A                                       = 554;
const s32 ProfileInfo::cProfileID_22B                                       = 555;
const s32 ProfileInfo::cProfileID_22C                                       = 556;
const s32 ProfileInfo::cProfileID_22D                                       = 557;
const s32 ProfileInfo::cProfileID_FireBallKeronpa                           = 558;
const s32 ProfileInfo::cProfileID_FireBallKeronpaRDash                      = 559;
const s32 ProfileInfo::cProfileID_230                                       = 560;
const s32 ProfileInfo::cProfileID_FireSnake                                 = 561;
const s32 ProfileInfo::cProfileID_232                                       = 562;
const s32 ProfileInfo::cProfileID_233                                       = 563;
const s32 ProfileInfo::cProfileID_234                                       = 564;
const s32 ProfileInfo::cProfileID_235                                       = 565;
const s32 ProfileInfo::cProfileID_236                                       = 566;
const s32 ProfileInfo::cProfileID_237                                       = 567;
const s32 ProfileInfo::cProfileID_238                                       = 568;
const s32 ProfileInfo::cProfileID_239                                       = 569;
const s32 ProfileInfo::cProfileID_23A                                       = 570;
const s32 ProfileInfo::cProfileID_23B                                       = 571;
const s32 ProfileInfo::cProfileID_23C                                       = 572;
const s32 ProfileInfo::cProfileID_23D                                       = 573;
const s32 ProfileInfo::cProfileID_Kazandan                                  = 574;
const s32 ProfileInfo::cProfileID_23F                                       = 575;
const s32 ProfileInfo::cProfileID_240                                       = 576;
const s32 ProfileInfo::cProfileID_241                                       = 577;
const s32 ProfileInfo::cProfileID_242                                       = 578;
const s32 ProfileInfo::cProfileID_243                                       = 579;
const s32 ProfileInfo::cProfileID_244                                       = 580;
const s32 ProfileInfo::cProfileID_245                                       = 581;
const s32 ProfileInfo::cProfileID_246                                       = 582;
const s32 ProfileInfo::cProfileID_247                                       = 583;
const s32 ProfileInfo::cProfileID_248                                       = 584;
const s32 ProfileInfo::cProfileID_249                                       = 585;
const s32 ProfileInfo::cProfileID_24A                                       = 586;
const s32 ProfileInfo::cProfileID_BgCenter                                  = 587;
const s32 ProfileInfo::cProfileID_24C                                       = 588;
const s32 ProfileInfo::cProfileID_24D                                       = 589;
const s32 ProfileInfo::cProfileID_24E                                       = 590;
const s32 ProfileInfo::cProfileID_Kinoko                                    = 591;
const s32 ProfileInfo::cProfileID_FireFlower                                = 592;
const s32 ProfileInfo::cProfileID_MameKinoko                                = 593;
const s32 ProfileInfo::cProfileID_IceFlower                                 = 594;
const s32 ProfileInfo::cProfileID_Propeller                                 = 595;
const s32 ProfileInfo::cProfileID_Penguin                                   = 596;
const s32 ProfileInfo::cProfileID_OneUpKinoko                               = 597;
const s32 ProfileInfo::cProfileID_Musasabi                                  = 598;
const s32 ProfileInfo::cProfileID_SuperMoon                                 = 599;
const s32 ProfileInfo::cProfileID_TitleDemoItem                             = 600;
const s32 ProfileInfo::cProfileID_259                                       = 601;
const s32 ProfileInfo::cProfileID_25A                                       = 602;
const s32 ProfileInfo::cProfileID_25B                                       = 603;
const s32 ProfileInfo::cProfileID_25C                                       = 604;
const s32 ProfileInfo::cProfileID_25D                                       = 605;
const s32 ProfileInfo::cProfileID_25E                                       = 606;
const s32 ProfileInfo::cProfileID_25F                                       = 607;
const s32 ProfileInfo::cProfileID_260                                       = 608;
const s32 ProfileInfo::cProfileID_261                                       = 609;
const s32 ProfileInfo::cProfileID_262                                       = 610;
const s32 ProfileInfo::cProfileID_263                                       = 611;
const s32 ProfileInfo::cProfileID_264                                       = 612;
const s32 ProfileInfo::cProfileID_265                                       = 613;
const s32 ProfileInfo::cProfileID_266                                       = 614;
const s32 ProfileInfo::cProfileID_267                                       = 615;
const s32 ProfileInfo::cProfileID_268                                       = 616;
const s32 ProfileInfo::cProfileID_Spanner                                   = 617;
const s32 ProfileInfo::cProfileID_26A                                       = 618;
const s32 ProfileInfo::cProfileID_26B                                       = 619;
const s32 ProfileInfo::cProfileID_26C                                       = 620;
const s32 ProfileInfo::cProfileID_26D                                       = 621;
const s32 ProfileInfo::cProfileID_26E                                       = 622;
const s32 ProfileInfo::cProfileID_26F                                       = 623;
const s32 ProfileInfo::cProfileID_270                                       = 624;
const s32 ProfileInfo::cProfileID_271                                       = 625;
const s32 ProfileInfo::cProfileID_272                                       = 626;
const s32 ProfileInfo::cProfileID_273                                       = 627;
const s32 ProfileInfo::cProfileID_274                                       = 628;
const s32 ProfileInfo::cProfileID_275                                       = 629;
const s32 ProfileInfo::cProfileID_SearchKiller                              = 630;
const s32 ProfileInfo::cProfileID_277                                       = 631;
const s32 ProfileInfo::cProfileID_278                                       = 632;
const s32 ProfileInfo::cProfileID_279                                       = 633;
const s32 ProfileInfo::cProfileID_WakiSearchMagKiller                       = 634;
const s32 ProfileInfo::cProfileID_27B                                       = 635;
const s32 ProfileInfo::cProfileID_27C                                       = 636;
const s32 ProfileInfo::cProfileID_27D                                       = 637;
const s32 ProfileInfo::cProfileID_27E                                       = 638;
const s32 ProfileInfo::cProfileID_27F                                       = 639;
const s32 ProfileInfo::cProfileID_GabonRock                                 = 640;
const s32 ProfileInfo::cProfileID_281                                       = 641;
const s32 ProfileInfo::cProfileID_282                                       = 642;
const s32 ProfileInfo::cProfileID_RockGabonRock                             = 643;
const s32 ProfileInfo::cProfileID_284                                       = 644;
const s32 ProfileInfo::cProfileID_SeichanSnowBall                           = 645;
const s32 ProfileInfo::cProfileID_286                                       = 646;
const s32 ProfileInfo::cProfileID_287                                       = 647;
const s32 ProfileInfo::cProfileID_288                                       = 648;
const s32 ProfileInfo::cProfileID_289                                       = 649;
const s32 ProfileInfo::cProfileID_Woochan                                   = 650;
const s32 ProfileInfo::cProfileID_28B                                       = 651;
const s32 ProfileInfo::cProfileID_28C                                       = 652;
const s32 ProfileInfo::cProfileID_28D                                       = 653;
const s32 ProfileInfo::cProfileID_Bubble                                    = 654;
const s32 ProfileInfo::cProfileID_BubbleSync                                = 655;
const s32 ProfileInfo::cProfileID_BubbleRDash                               = 656;
const s32 ProfileInfo::cProfileID_BubbleSyncRDash                           = 657;
const s32 ProfileInfo::cProfileID_292                                       = 658;
const s32 ProfileInfo::cProfileID_293                                       = 659;
const s32 ProfileInfo::cProfileID_294                                       = 660;
const s32 ProfileInfo::cProfileID_295                                       = 661;
const s32 ProfileInfo::cProfileID_296                                       = 662;
const s32 ProfileInfo::cProfileID_297                                       = 663;
const s32 ProfileInfo::cProfileID_298                                       = 664;
const s32 ProfileInfo::cProfileID_299                                       = 665;
const s32 ProfileInfo::cProfileID_29A                                       = 666;
const s32 ProfileInfo::cProfileID_29B                                       = 667;
const s32 ProfileInfo::cProfileID_29C                                       = 668;
const s32 ProfileInfo::cProfileID_29D                                       = 669;
const s32 ProfileInfo::cProfileID_29E                                       = 670;
const s32 ProfileInfo::cProfileID_29F                                       = 671;
const s32 ProfileInfo::cProfileID_2A0                                       = 672;
const s32 ProfileInfo::cProfileID_2A1                                       = 673;
const s32 ProfileInfo::cProfileID_2A2                                       = 674;
const s32 ProfileInfo::cProfileID_2A3                                       = 675;
const s32 ProfileInfo::cProfileID_2A4                                       = 676;
const s32 ProfileInfo::cProfileID_2A5                                       = 677;
const s32 ProfileInfo::cProfileID_Bun                                       = 678;
const s32 ProfileInfo::cProfileID_BunW2                                     = 679;
const s32 ProfileInfo::cProfileID_BunW3                                     = 680;
const s32 ProfileInfo::cProfileID_BunW4                                     = 681;
const s32 ProfileInfo::cProfileID_BunW5                                     = 682;
const s32 ProfileInfo::cProfileID_BunW6                                     = 683;
const s32 ProfileInfo::cProfileID_BunDemo                                   = 684;
const s32 ProfileInfo::cProfileID_KokoopaDemo                               = 685;
const s32 ProfileInfo::cProfileID_KoopaJrDemo                               = 686;
const s32 ProfileInfo::cProfileID_KameckDemo                                = 687;
const s32 ProfileInfo::cProfileID_BossKKDemo                                = 688;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJrDemo               = 689;
const s32 ProfileInfo::cProfileID_KoopaDemo                                 = 690;
const s32 ProfileInfo::cProfileID_FinalKoopaDemo                            = 691;
const s32 ProfileInfo::cProfileID_PeachDemo                                 = 692;
const s32 ProfileInfo::cProfileID_Larry                                     = 693;
const s32 ProfileInfo::cProfileID_KokoopaSearchFire                         = 694;
const s32 ProfileInfo::cProfileID_Lemmy                                     = 695;
const s32 ProfileInfo::cProfileID_Morton                                    = 696;
const s32 ProfileInfo::cProfileID_MortonSanbo                               = 697;
const s32 ProfileInfo::cProfileID_MortonSanboParts                          = 698;
const s32 ProfileInfo::cProfileID_Wendy                                     = 699;
const s32 ProfileInfo::cProfileID_WendyRing                                 = 700;
const s32 ProfileInfo::cProfileID_Ludwig                                    = 701;
const s32 ProfileInfo::cProfileID_LudwigAlterEgo                            = 702;
const s32 ProfileInfo::cProfileID_Iggy                                      = 703;
const s32 ProfileInfo::cProfileID_IggyMagic                                 = 704;
const s32 ProfileInfo::cProfileID_Woogan                                    = 705;
const s32 ProfileInfo::cProfileID_Roy                                       = 706;
const s32 ProfileInfo::cProfileID_RoyLiftWaki                               = 707;
const s32 ProfileInfo::cProfileID_BossKK                                    = 708;
const s32 ProfileInfo::cProfileID_BossKKThunder                             = 709;
const s32 ProfileInfo::cProfileID_Kameck                                    = 710;
const s32 ProfileInfo::cProfileID_KameckIceConfig                           = 711;
const s32 ProfileInfo::cProfileID_KameckWarpPos                             = 712;
const s32 ProfileInfo::cProfileID_KameckMagic                               = 713;
const s32 ProfileInfo::cProfileID_PeachFinalCastleKoopaJr                   = 714;
const s32 ProfileInfo::cProfileID_Koopa                                     = 715;
const s32 ProfileInfo::cProfileID_KoopaFireWaki                             = 716;
const s32 ProfileInfo::cProfileID_KoopaFire                                 = 717;
const s32 ProfileInfo::cProfileID_DemoKoopaJrClown                          = 718;
const s32 ProfileInfo::cProfileID_DemoKoopaJr                               = 719;
const s32 ProfileInfo::cProfileID_BunDemoKameck                             = 720;
const s32 ProfileInfo::cProfileID_KoopaDemoKameck                           = 721;
const s32 ProfileInfo::cProfileID_BossKKDemoKameck                          = 722;
const s32 ProfileInfo::cProfileID_BossKKDemoKK                              = 723;
const s32 ProfileInfo::cProfileID_FinalKoopaFire                            = 724;
const s32 ProfileInfo::cProfileID_FinalKoopaJr                              = 725;
const s32 ProfileInfo::cProfileID_FinalKoopaJrFire                          = 726;
const s32 ProfileInfo::cProfileID_FinalBomhei                               = 727;
const s32 ProfileInfo::cProfileID_KokoopaShipLemmy                          = 728;
const s32 ProfileInfo::cProfileID_KokoopaShipMorton                         = 729;
const s32 ProfileInfo::cProfileID_KokoopaShipLarry                          = 730;
const s32 ProfileInfo::cProfileID_KokoopaShipWendy                          = 731;
const s32 ProfileInfo::cProfileID_KokoopaShipIggy                           = 732;
const s32 ProfileInfo::cProfileID_KokoopaShipRoy                            = 733;
const s32 ProfileInfo::cProfileID_KokoopaShipLudwig                         = 734;
const s32 ProfileInfo::cProfileID_Peach                                     = 735;
const s32 ProfileInfo::cProfileID_2E0                                       = 736;
const s32 ProfileInfo::cProfileID_FinalDVPeach                              = 737;
const s32 ProfileInfo::cProfileID_FinalDVShutter                            = 738;
const s32 ProfileInfo::cProfileID_2E3                                       = 739;
const s32 ProfileInfo::cProfileID_2E4                                       = 740;
const s32 ProfileInfo::cProfileID_2E5                                       = 741;
const s32 ProfileInfo::cProfileID_2E6                                       = 742;
const s32 ProfileInfo::cProfileID_2E7                                       = 743;
const s32 ProfileInfo::cProfileID_2E8                                       = 744;
const s32 ProfileInfo::cProfileID_2E9                                       = 745;
const s32 ProfileInfo::cProfileID_2EA                                       = 746;
const s32 ProfileInfo::cProfileID_2EB                                       = 747;
const s32 ProfileInfo::cProfileID_2EC                                       = 748;
const s32 ProfileInfo::cProfileID_2ED                                       = 749;
const s32 ProfileInfo::cProfileID_2EE                                       = 750;
const s32 ProfileInfo::cProfileID_2EF                                       = 751;
const s32 ProfileInfo::cProfileID_2F0                                       = 752;
const s32 ProfileInfo::cProfileID_2F1                                       = 753;
const s32 ProfileInfo::cProfileID_2F2                                       = 754;
const s32 ProfileInfo::cProfileID_2F3                                       = 755;
const s32 ProfileInfo::cProfileID_2F4                                       = 756;
const s32 ProfileInfo::cProfileID_2F5                                       = 757;
const s32 ProfileInfo::cProfileID_Hammer                                    = 758;
const s32 ProfileInfo::cProfileID_2F7                                       = 759;
const s32 ProfileInfo::cProfileID_Boomerang                                 = 760;
const s32 ProfileInfo::cProfileID_2F9                                       = 761;
const s32 ProfileInfo::cProfileID_FireBallBros                              = 762;
const s32 ProfileInfo::cProfileID_2FB                                       = 763;
const s32 ProfileInfo::cProfileID_IceBallBros                               = 764;
const s32 ProfileInfo::cProfileID_2FD                                       = 765;
const s32 ProfileInfo::cProfileID_MegaHammer                                = 766;
const s32 ProfileInfo::cProfileID_2FF                                       = 767;
const s32 ProfileInfo::cProfileID_300                                       = 768;
const s32 ProfileInfo::cProfileID_301                                       = 769;
const s32 ProfileInfo::cProfileID_302                                       = 770;
const s32 ProfileInfo::cProfileID_303                                       = 771;
const s32 ProfileInfo::cProfileID_304                                       = 772;
const s32 ProfileInfo::cProfileID_305                                       = 773;
const s32 ProfileInfo::cProfileID_306                                       = 774;
const s32 ProfileInfo::cProfileID_307                                       = 775;
const s32 ProfileInfo::cProfileID_308                                       = 776;
const s32 ProfileInfo::cProfileID_309                                       = 777;
const s32 ProfileInfo::cProfileID_30A                                       = 778;
const s32 ProfileInfo::cProfileID_30B                                       = 779;
const s32 ProfileInfo::cProfileID_30C                                       = 780;
const s32 ProfileInfo::cProfileID_30D                                       = 781;
const s32 ProfileInfo::cProfileID_30E                                       = 782;
const s32 ProfileInfo::cProfileID_30F                                       = 783;
const s32 ProfileInfo::cProfileID_310                                       = 784;
const s32 ProfileInfo::cProfileID_311                                       = 785;
const s32 ProfileInfo::cProfileID_312                                       = 786;
const s32 ProfileInfo::cProfileID_313                                       = 787;
const s32 ProfileInfo::cProfileID_314                                       = 788;
const s32 ProfileInfo::cProfileID_315                                       = 789;
const s32 ProfileInfo::cProfileID_316                                       = 790;
const s32 ProfileInfo::cProfileID_317                                       = 791;
const s32 ProfileInfo::cProfileID_318                                       = 792;
const s32 ProfileInfo::cProfileID_319                                       = 793;
const s32 ProfileInfo::cProfileID_31A                                       = 794;
const s32 ProfileInfo::cProfileID_31B                                       = 795;
const s32 ProfileInfo::cProfileID_31C                                       = 796;
const s32 ProfileInfo::cProfileID_31D                                       = 797;
const s32 ProfileInfo::cProfileID_31E                                       = 798;
const s32 ProfileInfo::cProfileID_31F                                       = 799;
const s32 ProfileInfo::cProfileID_320                                       = 800;
const s32 ProfileInfo::cProfileID_321                                       = 801;
const s32 ProfileInfo::cProfileID_322                                       = 802;
const s32 ProfileInfo::cProfileID_323                                       = 803;
const s32 ProfileInfo::cProfileID_324                                       = 804;
const s32 ProfileInfo::cProfileID_325                                       = 805;
const s32 ProfileInfo::cProfileID_326                                       = 806;
const s32 ProfileInfo::cProfileID_327                                       = 807;
const s32 ProfileInfo::cProfileID_328                                       = 808;
const s32 ProfileInfo::cProfileID_BattleItem                                = 809;
const s32 ProfileInfo::cProfileID_32A                                       = 810;
const s32 ProfileInfo::cProfileID_VsBattleItem                              = 811;
const s32 ProfileInfo::cProfileID_32C                                       = 812;
const s32 ProfileInfo::cProfileID_32D                                       = 813;
const s32 ProfileInfo::cProfileID_32E                                       = 814;
const s32 ProfileInfo::cProfileID_32F                                       = 815;
const s32 ProfileInfo::cProfileID_330                                       = 816;
const s32 ProfileInfo::cProfileID_331                                       = 817;
const s32 ProfileInfo::cProfileID_KoopaJrFire                               = 818;
const s32 ProfileInfo::cProfileID_KoopaJrBall                               = 819;
const s32 ProfileInfo::cProfileID_UnderwaterKoopaJr                         = 820;
const s32 ProfileInfo::cProfileID_UnderwaterKoopaJrClown                    = 821;
const s32 ProfileInfo::cProfileID_UnderwaterKoopaJrRetreatPos               = 822;
const s32 ProfileInfo::cProfileID_BoxingKoopaJr                             = 823;
const s32 ProfileInfo::cProfileID_BoxingKoopaJrPostBattleDemo               = 824;
const s32 ProfileInfo::cProfileID_BoxingKoopaJrClownPostBattleDemo          = 825;
const s32 ProfileInfo::cProfileID_MiniGamePanelItem                         = 826;
const s32 ProfileInfo::cProfileID_SlotItem                                  = 827;
const s32 ProfileInfo::cProfileID_CoinmakiCannon                            = 828;
const s32 ProfileInfo::cProfileID_CoinmakiItem                              = 829;
const s32 ProfileInfo::cProfileID_MiniGameKinopio                           = 830;
const s32 ProfileInfo::cProfileID_33F                                       = 831;
const s32 ProfileInfo::cProfileID_340                                       = 832;
const s32 ProfileInfo::cProfileID_341                                       = 833;
const s32 ProfileInfo::cProfileID_342                                       = 834;
const s32 ProfileInfo::cProfileID_343                                       = 835;
const s32 ProfileInfo::cProfileID_344                                       = 836;
const s32 ProfileInfo::cProfileID_345                                       = 837;
const s32 ProfileInfo::cProfileID_346                                       = 838;
const s32 ProfileInfo::cProfileID_347                                       = 839;
const s32 ProfileInfo::cProfileID_StaffCreditChibiYoshiABC                  = 840;
const s32 ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloon              = 841;
const s32 ProfileInfo::cProfileID_StaffCreditChibiYoshiBalloonCheer         = 842;
const s32 ProfileInfo::cProfileID_StaffCreditChibiYoshiLight                = 843;
const s32 ProfileInfo::cProfileID_StaffCreditChibiYoshiLightCheer           = 844;
const s32 ProfileInfo::cProfileID_StaffCreditSoapABC                        = 845;
const s32 ProfileInfo::cProfileID_StaffCreditSoapCoin                       = 846;
const s32 ProfileInfo::cProfileID_StaffCreditTottenKun                      = 847;
const s32 ProfileInfo::cProfileID_350                                       = 848;
const s32 ProfileInfo::cProfileID_351                                       = 849;
const s32 ProfileInfo::cProfileID_352                                       = 850;
const s32 ProfileInfo::cProfileID_353                                       = 851;
const s32 ProfileInfo::cProfileID_RealizeFeverStar                          = 852;
const s32 ProfileInfo::cProfileID_Star                                      = 853;
const s32 ProfileInfo::cProfileID_CourseSelectPlayer                        = 854;
const s32 ProfileInfo::cProfileID_CourseSelectPlayer2PSub                   = 855;
const s32 ProfileInfo::cProfileID_CourseSelectChibiYoshi                    = 856;
const s32 ProfileInfo::cProfileID_CourseSelectCamera                        = 857;
const s32 ProfileInfo::cProfileID_CourseSelectCastle                        = 858;
const s32 ProfileInfo::cProfileID_CourseSelectToride                        = 859;
const s32 ProfileInfo::cProfileID_CourseSelectKinokoHouse1up                = 860;
const s32 ProfileInfo::cProfileID_CourseSelectKinokoHouseShuffle            = 861;
const s32 ProfileInfo::cProfileID_CourseSelectKinokoHouseSlot               = 862;
const s32 ProfileInfo::cProfileID_CourseSelectPeachGates1st                 = 863;
const s32 ProfileInfo::cProfileID_CourseSelectPeachGates2nd                 = 864;
const s32 ProfileInfo::cProfileID_CourseSelectCoursePoint                   = 865;
const s32 ProfileInfo::cProfileID_CourseSelectWorldMoveDokan                = 866;
const s32 ProfileInfo::cProfileID_CourseSelectW8Cloud                       = 867;
const s32 ProfileInfo::cProfileID_CourseSelectGhost                         = 868;
const s32 ProfileInfo::cProfileID_CourseSelectW2Bros                        = 869;
const s32 ProfileInfo::cProfileID_CourseSelectShipW1                        = 870;
const s32 ProfileInfo::cProfileID_CourseSelectShipW2                        = 871;
const s32 ProfileInfo::cProfileID_CourseSelectShipW3                        = 872;
const s32 ProfileInfo::cProfileID_CourseSelectShipW4                        = 873;
const s32 ProfileInfo::cProfileID_CourseSelectShipW5                        = 874;
const s32 ProfileInfo::cProfileID_CourseSelectShipW6                        = 875;
const s32 ProfileInfo::cProfileID_CourseSelectShipW7                        = 876;
const s32 ProfileInfo::cProfileID_CourseSelectShipW8                        = 877;
const s32 ProfileInfo::cProfileID_CourseSelectShipW8Broken                  = 878;
const s32 ProfileInfo::cProfileID_CourseSelectSurrender                     = 879;
const s32 ProfileInfo::cProfileID_CourseSelectSwitchA                       = 880;
const s32 ProfileInfo::cProfileID_CourseSelectSwitchB                       = 881;
const s32 ProfileInfo::cProfileID_CourseSelectTeresa                        = 882;
const s32 ProfileInfo::cProfileID_CourseSelectOpeningKameck                 = 883;
const s32 ProfileInfo::cProfileID_CourseSelectTorideBoss                    = 884;
const s32 ProfileInfo::cProfileID_CourseSelectPakkun                        = 885;
const s32 ProfileInfo::cProfileID_CourseSelectShadowFirstDemoKinopio        = 886;
const s32 ProfileInfo::cProfileID_CourseSelectTobiPuku                      = 887;
const s32 ProfileInfo::cProfileID_CourseSelectChorobon                      = 888;
const s32 ProfileInfo::cProfileID_CourseSelectW7Item                        = 889;
const s32 ProfileInfo::cProfileID_CourseSelectW5Teresa                      = 890;
const s32 ProfileInfo::cProfileID_CourseSelectFlag                          = 891;
const s32 ProfileInfo::cProfileID_CourseSelectMusasabi                      = 892;
const s32 ProfileInfo::cProfileID_CourseSelectWPillar                       = 893;
const s32 ProfileInfo::cProfileID_CourseSelectW7Bridge                      = 894;
const s32 ProfileInfo::cProfileID_CourseSelectMiiBalloon                    = 895;
const s32 ProfileInfo::cProfileID_CourseSelectPenguin                       = 896;
const s32 ProfileInfo::cProfileID_CourseSelectW4Item                        = 897;
const s32 ProfileInfo::cProfileID_CourseSelectW2Kuribo                      = 898;
const s32 ProfileInfo::cProfileID_CourseSelectPakkunBig                     = 899;
const s32 ProfileInfo::cProfileID_CourseSelectShadowKunIcon                 = 900;
const s32 ProfileInfo::cProfileID_CourseSelectDekaUnira                     = 901;
const s32 ProfileInfo::cProfileID_CourseSelectTomb                          = 902;
const s32 ProfileInfo::cProfileID_CourseSelectShadowFirstDemoShadowKun      = 903;
const s32 ProfileInfo::cProfileID_CourseSelectKotsuCoaster                  = 904;
const s32 ProfileInfo::cProfileID_CourseSelectKoopaJr                       = 905;
const s32 ProfileInfo::cProfileID_CourseSelectPeach                         = 906;
const s32 ProfileInfo::cProfileID_CourseSelectW1Item                        = 907;
const s32 ProfileInfo::cProfileID_CourseSelectStarGate                      = 908;
const s32 ProfileInfo::cProfileID_CourseSelectEventAssistant                = 909;
