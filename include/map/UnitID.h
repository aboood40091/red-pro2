#pragma once

#include <basis/seadTypes.h>

enum UnitID
{
    cUnitID_Invalid = -1,
    cUnitID_Null = 0,

    cUnitID_InvBlockSolid,
    cUnitID_InvVineStopper,
    cUnitID_InvBlockCoin,
    cUnitID_InvBlockFireFlower,
    cUnitID_InvBlockStar,
    cUnitID_InvBlock1UP,
    cUnitID_InvBlockVine,
    cUnitID_InvBlockMiniMushroom,
    cUnitID_InvBlockPropeller,
    cUnitID_InvBlockPenguin,
    cUnitID_InvBlockSolidOnTop,
    cUnitID_InvBlockSolidHalf,
    cUnitID_InvBlockIceFlower,
    cUnitID_InvClimbablePole,
    cUnitID_InvRope, // Not functional?
    cUnitID_InvBlockAcorn = 29,
    cUnitID_InvMuncher = 45,

    cUnitID_BrickBlockFireFlower = 16,
    cUnitID_BrickBlockStar,
    cUnitID_BrickBlock1UP,
    cUnitID_BrickBlockVine,
    cUnitID_BrickBlockMiniMushroom,
    cUnitID_BrickBlockPropeller,
    cUnitID_BrickBlockPenguin,
    cUnitID_BrickBlockIceFlower,
    cUnitID_BrickBlockAcorn,
    cUnitID_BrickBlockYoshiEgg,
    cUnitID_BrickBlockCoin,
    cUnitID_BrickBlockCoin10,
    cUnitID_BrickBlock = 48,

    cUnitID_CoinDashMultiplayer = 28,
    cUnitID_Coin = 30,
    cUnitID_CoinDash,

    cUnitID_QBlockFireFlower,
    cUnitID_QBlockStar,
    cUnitID_QBlockCoinStar,
    cUnitID_QBlockVine,
    cUnitID_QBlockMiniMushroom,
    cUnitID_QBlockPropeller,
    cUnitID_QBlockPenguin,
    cUnitID_QBlockIceFlower,
    cUnitID_QBlockAcorn,
    cUnitID_QBlockYoshiEgg,
    cUnitID_QBlockSpring,
    cUnitID_QBlock = 49,

    cUnitID_Bridge = 43,
    cUnitID_MiniPassage,

    cUnitID_BlueCoin = 46,
    cUnitID_BlueCoin_CoreCoin,

    cUnitID_BlockUsed = 50,
    cUnitID_BlockWood,
    cUnitID_BlockStone,
    cUnitID_BlockBlue,
    cUnitID_BlockDonutLift,
    cUnitID_BlockRed = 208,

    cUnitID_Fragment_BrickBlock_0 = 55,
    cUnitID_Fragment_BrickBlock_1,
    cUnitID_Fragment_BrickBlock_2,

    cUnitID_Fragment_QBlock_0,
    cUnitID_Fragment_QBlock_1,
    cUnitID_Fragment_QBlock_2,

    cUnitID_Fragment_BlockRed_0,
    cUnitID_Fragment_BlockRed_1,
    cUnitID_Fragment_BlockRed_2,

    cUnitID_Fragment_BlockUsed_0 = 71,
    cUnitID_Fragment_BlockUsed_1,
    cUnitID_Fragment_BlockUsed_2,

    cUnitID_Fragment_BlockWood_0,
    cUnitID_Fragment_BlockWood_1,
    cUnitID_Fragment_BlockWood_2,

    cUnitID_Fragment_BlockStone_0,
    cUnitID_Fragment_BlockStone_1,
    cUnitID_Fragment_BlockStone_2,

    // ...

    cUnitID_ConveyorRight_0 = 144,
    cUnitID_ConveyorRight_1,
    cUnitID_ConveyorRight_2,

    cUnitID_ConveyorLeft_0,
    cUnitID_ConveyorLeft_1,
    cUnitID_ConveyorLeft_2,

    cUnitID_ConveyorRightFast_0 = 160,
    cUnitID_ConveyorRightFast_1,
    cUnitID_ConveyorRightFast_2,

    cUnitID_ConveyorLeftFast_0,
    cUnitID_ConveyorLeftFast_1,
    cUnitID_ConveyorLeftFast_2,

    // ...

    cUnitID_Pa0_Unit_Num = 256,
    cUnitID_Pa1_Unit_Num = 256 + cUnitID_Pa0_Unit_Num,
    cUnitID_Pa2_Unit_Num = 256 + cUnitID_Pa1_Unit_Num,
    cUnitID_Pa3_Unit_Num = 256 + cUnitID_Pa2_Unit_Num
};
