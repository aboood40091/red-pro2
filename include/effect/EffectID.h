#pragma once

#include <basis/seadTypes.h>

enum EffectID
{
    // RP_1upGet
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_1upGet_0 = 0x060, // Translation: (0.0, 8.0, 0.0)
    RP_1upGet_1 = 0x061, // Scale Factor: 0.8, Translation: (0.0, 5.0, 0.0)
    RP_1upGet_2 = 0x062, // Scale Factor: 0.5, Translation: (0.0, 4.0, 0.0)

    // rp_ankou_LightGlow
    // User Data: 0x00000000
    // Emitter Count: 1
    rp_ankou_LightGlow = 0x271,

    // RP_AssistBlock_Burst_Blue
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_AssistBlock_Burst_Blue = 0x240, // Translation: (0.0, 0.0, 1000.0)

    // RP_AssistBlock_Burst_Green
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_AssistBlock_Burst_Green = 0x23F, // Translation: (0.0, 0.0, 1000.0)

    // RP_AssistBlock_Burst_Purple
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_AssistBlock_Burst_Purple = 0x241, // Translation: (0.0, 0.0, 1000.0)

    // RP_AssistBlock_Burst_Red
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_AssistBlock_Burst_Red = 0x23E, // Translation: (0.0, 0.0, 1000.0)

    // RP_AssistBlock_Burst_White
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_AssistBlock_Burst_White = 0x242,

    // RP_AssistBlock_MarkDisapp
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_AssistBlock_MarkDisapp = 0x489,

    // RP_AssistBlock_MarkLine
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_AssistBlock_MarkLine = 0x48A,

    // RP_Bakubaku_bubble
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Bakubaku_bubble = 0x498,

    // RP_Bakubaku_vacuum
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Bakubaku_vacuum = 0x497,

    // RP_Balloon_Burst
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Balloon_Burst_0 = 0x1B8, // Scale Factor: 1.25
    RP_Balloon_Burst_1 = 0x1BC, // Scale Factor: 1.25

    // RP_Balloon_Burst_b
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Balloon_Burst_b = 0x393, // Scale Factor: 1.25

    // RP_Balloon_Burst_g
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Balloon_Burst_g = 0x392, // Scale Factor: 1.25

    // RP_Balloon_Burst_r
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Balloon_Burst_r = 0x391, // Scale Factor: 1.25

    // RP_Balloon_Burst_s
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Balloon_Burst_s_0 = 0x1B9, // Scale Factor: 0.8
    RP_Balloon_Burst_s_1 = 0x1BB, // Scale Factor: 1.25

    // RP_Balloon_Burst_wtr
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Balloon_Burst_wtr = 0x1BA,

    // RP_Balloon_Burst_y
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Balloon_Burst_y = 0x394, // Scale Factor: 1.25

    // RP_Birikyu_Elec
    // User Data: 0x20000000
    // Emitter Count: 6
    RP_Birikyu_Elec = 0x022,

    // RP_Block_break
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Block_break_0 = 0x366,
    RP_Block_break_1 = 0x47C,

    // RP_Block_break_chika
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Block_break_chika = 0x47B,

    // RP_Block_break_yougan2
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Block_break_yougan2 = 0x47D,

    // RP_Bombhei_Ignite
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_Bombhei_Ignite = 0x280,

    // RP_BossCannon_Shoot
    // User Data: 0x40000000
    // Emitter Count: 6
    RP_BossCannon_Shoot = 0x3B4,

    // RP_bosskk_damage_nml
    // User Data: 0x00040000
    // Emitter Count: 4

    // RP_BossKK_ElecBall
    // User Data: 0x00040000
    // Emitter Count: 5
    RP_BossKK_ElecBall_0 = 0x023,
    RP_BossKK_ElecBall_1 = 0x3C4, // Scale Factor: 0.7

    // RP_BossKK_ElecBall_Hit
    // User Data: 0x00040000
    // Emitter Count: 4
    RP_BossKK_ElecBall_Hit_0 = 0x025,
    RP_BossKK_ElecBall_Hit_1 = 0x3C6, // Scale Factor: 0.7

    // RP_BossKK_ElecBall_HitSplit
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_BossKK_ElecBall_HitSplit_0 = 0x024,
    RP_BossKK_ElecBall_HitSplit_1 = 0x3C5, // Scale Factor: 0.7

    // RP_BossKK_Landing_nml
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_BossKK_Landing_nml = 0x3CB,

    // RP_BossKK_Piyori
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_BossKK_Piyori = 0x3EF, // Translation: (0.0, 65.0, 0.0)

    // RP_BossKK_Shiko
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_BossKK_Shiko = 0x3C9,

    // RP_BossShip_PlayerIn
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_BossShip_PlayerIn_0 = 0x4C6, // Scale Factor: 1.5
    RP_BossShip_PlayerIn_1 = 0x4C7, // Scale Factor: 2.4
    RP_BossShip_PlayerIn_2 = 0x4C8, // Scale Factor: 1.8
    RP_BossShip_PlayerIn_3 = 0x4C9, // Scale Factor: 1.8
    RP_BossShip_PlayerIn_4 = 0x4CA, // Scale Factor: 1.8
    RP_BossShip_PlayerIn_5 = 0x4CB, // Scale Factor: 2.0
    RP_BossShip_PlayerIn_6 = 0x4CC, // Scale Factor: 2.0

    // RP_boss_ChangeShell
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_boss_ChangeShell_0 = 0x0F9, // Translation: (0.0, 6.0, 0.0)
    RP_boss_ChangeShell_1 = 0x142, // Scale Factor: 1.5, Translation: (0.0, 12.0, 0.0)
    RP_boss_ChangeShell_2 = 0x187, // Scale Factor: 1.4, Translation: (0.0, 30.0, 0.0)
    RP_boss_ChangeShell_3 = 0x304, // Scale Factor: 1.2, Translation: (0.0, 9.0, 0.0)
    RP_boss_ChangeShell_4 = 0x31B, // Scale Factor: 1.2, Translation: (0.0, 9.0, 0.0)
    RP_boss_ChangeShell_5 = 0x3F6, // Scale Factor: 1.2, Translation: (0.0, 9.0, 0.0)
    RP_boss_ChangeShell_6 = 0x406, // Scale Factor: 1.2, Translation: (0.0, 9.0, 0.0)
    RP_boss_ChangeShell_7 = 0x410, // Scale Factor: 1.2, Translation: (0.0, 10.0, 0.0)
    RP_boss_ChangeShell_8 = 0x439, // Translation: (0.0, 15.0, 0.0)

    // RP_boss_damage_end
    // User Data: 0x40040000
    // Emitter Count: 4
    RP_boss_damage_end_00 = 0x027, // Scale Factor: 1.5
    RP_boss_damage_end_01 = 0x0FD, // Scale Factor: 0.8
    RP_boss_damage_end_02 = 0x147,
    RP_boss_damage_end_03 = 0x18D,
    RP_boss_damage_end_04 = 0x300,
    RP_boss_damage_end_05 = 0x320,
    RP_boss_damage_end_06 = 0x3FB,
    RP_boss_damage_end_07 = 0x40B,
    RP_boss_damage_end_08 = 0x415,
    RP_boss_damage_end_09 = 0x427,
    RP_boss_damage_end_10 = 0x435,
    RP_boss_damage_end_11 = 0x4B0, // Scale Factor: 1.2

    // RP_boss_damage_nml
    // User Data: 0x00040000
    // Emitter Count: 6
    RP_boss_damage_nml_00 = 0x026, // Scale Factor: 1.5
    RP_boss_damage_nml_01 = 0x0FC, // Scale Factor: 0.8
    RP_boss_damage_nml_02 = 0x146,
    RP_boss_damage_nml_03 = 0x18C,
    RP_boss_damage_nml_04 = 0x2FF,
    RP_boss_damage_nml_05 = 0x31F,
    RP_boss_damage_nml_06 = 0x3FA,
    RP_boss_damage_nml_07 = 0x40A,
    RP_boss_damage_nml_08 = 0x414,
    RP_boss_damage_nml_09 = 0x426,
    RP_boss_damage_nml_10 = 0x434, // Scale Factor: 1.5
    RP_boss_damage_nml_11 = 0x451,
    RP_boss_damage_nml_12 = 0x493, // Scale Factor: 0.8
    RP_boss_damage_nml_13 = 0x495,
    RP_boss_damage_nml_14 = 0x4AF, // Scale Factor: 1.2

    // RP_boss_notice
    // User Data: 0x40000000
    // Emitter Count: 2
    RP_boss_notice_0 = 0x13C, // Translation: (-4.0, 20.0, 0.0)
    RP_boss_notice_1 = 0x13E, // Translation: (-18.0, 38.0, 0.0)
    RP_boss_notice_2 = 0x18A, // Translation: (-10.0, 35.0, 0.0)
    RP_boss_notice_3 = 0x2F5, // Translation: (-6.0, 25.0, 0.0)
    RP_boss_notice_4 = 0x312, // Translation: (-5.0, 25.0, 0.0)
    RP_boss_notice_5 = 0x3F3, // Translation: (-6.0, 35.0, 100000.0)
    RP_boss_notice_6 = 0x40E, // Translation: (-10.0, 30.0, 0.0)

    // RP_boss_shell_land_ice
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_boss_shell_land_ice = 0x31C,

    // RP_boss_shell_land_nml
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_boss_shell_land_nml_00 = 0x0FA,
    RP_boss_shell_land_nml_01 = 0x105, // Scale Factor: 1.2, Translation: (0.0, 12.0, 0.0)
    RP_boss_shell_land_nml_02 = 0x143, // Scale Factor: 1.2
    RP_boss_shell_land_nml_03 = 0x186, // Scale Factor: 1.5
    RP_boss_shell_land_nml_04 = 0x2FA,
    RP_boss_shell_land_nml_05 = 0x3F7,
    RP_boss_shell_land_nml_06 = 0x407, // Scale Factor: 1.2
    RP_boss_shell_land_nml_07 = 0x411, // Scale Factor: 1.2
    RP_boss_shell_land_nml_08 = 0x43A, // Scale Factor: 1.2
    RP_boss_shell_land_nml_09 = 0x44E,
    RP_boss_shell_land_nml_10 = 0x4AC, // Scale Factor: 1.5, Translation: (0.0, 20.0, 0.0)

    // RP_boss_shell_land_pwl
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_boss_shell_land_pwl = 0x2FB,

    // RP_boss_shell_move_nml
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_boss_shell_move_nml_0 = 0x103,
    RP_boss_shell_move_nml_1 = 0x145,

    // RP_BrosMega_HipDrop
    // User Data: 0x00080000
    // Emitter Count: 6
    RP_BrosMega_HipDrop = 0x284,

    // RP_BrosMega_HipDropBlur
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_BrosMega_HipDropBlur = 0x285,

    // RP_BrosMega_WalkSmoke
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_BrosMega_WalkSmoke = 0x286,

    // RP_Bubble_Dead
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Bubble_Dead = 0x290,

    // RP_Bubble_inWtr
    // User Data: 0x20000000
    // Emitter Count: 1
    RP_Bubble_inWtr = 0x2EF,

    // RP_Bubble_Tail
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Bubble_Tail = 0x28F,

    // RP_Bunbun_DashIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Bunbun_DashIce = 0x195, // Scale Factor: 1.4

    // RP_Bunbun_DashShallow
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Bunbun_DashShallow = 0x196, // Scale Factor: 1.4

    // RP_Bunbun_DashSmoke
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Bunbun_DashSmoke_0 = 0x194, // Scale Factor: 1.4
    RP_Bunbun_DashSmoke_1 = 0x4B3, // Scale Factor: 1.6

    // RP_Bunbun_DownIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Bunbun_DownIce = 0x192, // Scale Factor: 1.4

    // RP_Bunbun_DownShallow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Bunbun_DownShallow = 0x193, // Scale Factor: 1.4

    // RP_Bunbun_DownSmoke
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Bunbun_DownSmoke_0 = 0x191, // Scale Factor: 1.4
    RP_Bunbun_DownSmoke_1 = 0x4B2, // Scale Factor: 1.6

    // RP_Bunbun_HandBlur_L1
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Bunbun_HandBlur_L1 = 0x182,

    // RP_Bunbun_HandBlur_L2
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Bunbun_HandBlur_L2_0 = 0x184,
    RP_Bunbun_HandBlur_L2_1 = 0x4AA, // Scale Factor: 1.6

    // RP_Bunbun_HandBlur_R1
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Bunbun_HandBlur_R1 = 0x183,

    // RP_Bunbun_HandBlur_R2
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Bunbun_HandBlur_R2_0 = 0x185,
    RP_Bunbun_HandBlur_R2_1 = 0x4AB, // Scale Factor: 1.6

    // RP_Bunbun_LandingIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Bunbun_LandingIce = 0x18F, // Scale Factor: 1.4

    // RP_Bunbun_LandingShallow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Bunbun_LandingShallow = 0x190, // Scale Factor: 1.4

    // RP_Bunbun_LandingSmoke
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Bunbun_LandingSmoke_0 = 0x18E, // Scale Factor: 1.4
    RP_Bunbun_LandingSmoke_1 = 0x287,
    RP_Bunbun_LandingSmoke_2 = 0x4B1, // Scale Factor: 1.6

    // RP_Bunbun_OpSpin
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Bunbun_OpSpin = 0x4B4,

    // RP_Bunbun_Piyori
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Bunbun_Piyori_0 = 0x188, // Translation: (0.0, 15.0, 0.0)
    RP_Bunbun_Piyori_1 = 0x4AD, // Scale Factor: 1.6, Translation: (0.0, 24.0, 0.0)

    // RP_Bunbun_Pun
    // User Data: 0x00080000
    // Emitter Count: 4
    RP_Bunbun_Pun = 0x18B, // Scale Factor: 0.6, Translation: (-5.0, 3.0, 100.0)

    // RP_Bunbun_Pun2
    // User Data: 0x00080000
    // Emitter Count: 4
    RP_Bunbun_Pun2_0 = 0x4B5, // Scale Factor: 0.7, Translation: (0.0, 0.0, 100.0)
    RP_Bunbun_Pun2_1 = 0x4B6, // Scale Factor: 1.2, Translation: (0.0, 15.0, 100.0)

    // RP_Bunbun_ScaleUp
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Bunbun_ScaleUp_0 = 0x499, // Translation: (0.0, 0.0, 1500.0)
    RP_Bunbun_ScaleUp_1 = 0x49A, // Translation: (0.0, 5.0, -2500.0)

    // RP_Bunbun_Spin
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Bunbun_Spin_0 = 0x189,
    RP_Bunbun_Spin_1 = 0x4AE, // Scale Factor: 1.6

    // RP_BurnerSign
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_BurnerSign = 0x020,

    // RP_Burner_Flame
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_Burner_Flame = 0x25D,

    // RP_CanonShootA
    // User Data: 0x40000000
    // Emitter Count: 4
    RP_CanonShootA = 0x14E,

    // RP_ChangeBlock_Change
    // User Data: 0x40000000
    // Emitter Count: 1
    RP_ChangeBlock_Change = 0x477,

    // rp_Chorobon_Drop
    // User Data: 0x00000000
    // Emitter Count: 1
    rp_Chorobon_Drop_0 = 0x251,
    rp_Chorobon_Drop_1 = 0x473,

    // RP_Choropoo_App
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_Choropoo_App = 0x021,

    // RP_Choropoo_AppSign
    // User Data: 0x00040000
    // Emitter Count: 2
    RP_Choropoo_AppSign = 0x06C,

    // RP_Choropoo_ManholeClose
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Choropoo_ManholeClose = 0x26F, // Translation: (0.0, -2.0, 10.0)

    // RP_Choropoo_SpannerBlur
    // User Data: 0x00040000
    // Emitter Count: 1
    RP_Choropoo_SpannerBlur = 0x270,

    // RP_Cmn_AppSmokeM
    // User Data: 0x40000000
    // Emitter Count: 2
    RP_Cmn_AppSmokeM_0 = 0x028, // Scale Factor: 0.85, Translation: (0.0, 14.0, 0.0)
    RP_Cmn_AppSmokeM_1 = 0x029, // Scale Factor: 0.7, Translation: (0.0, 9.0, 0.0)

    // RP_Cmn_DashIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_DashIce_0 = 0x0AA,
    RP_Cmn_DashIce_1 = 0x0AB, // Scale Factor: 0.8
    RP_Cmn_DashIce_2 = 0x0AC, // Scale Factor: 0.5
    RP_Cmn_DashIce_3 = 0x0AD,
    RP_Cmn_DashIce_4 = 0x248,
    RP_Cmn_DashIce_5 = 0x35F, // Translation: (0.0, -8.0, 0.0)

    // RP_Cmn_DashPillarWtr
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_DashPillarWtr_0 = 0x0C3,
    RP_Cmn_DashPillarWtr_1 = 0x0C4, // Scale Factor: 0.8
    RP_Cmn_DashPillarWtr_2 = 0x0C5, // Scale Factor: 0.5
    RP_Cmn_DashPillarWtr_3 = 0x0C6,
    RP_Cmn_DashPillarWtr_4 = 0x249,

    // RP_Cmn_DashSand
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_DashSand_0 = 0x078,
    RP_Cmn_DashSand_1 = 0x079, // Scale Factor: 0.8
    RP_Cmn_DashSand_2 = 0x07A, // Scale Factor: 0.5
    RP_Cmn_DashSand_3 = 0x07B,

    // RP_Cmn_DashSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Cmn_DashSmoke_0 = 0x030,
    RP_Cmn_DashSmoke_1 = 0x031, // Scale Factor: 0.8
    RP_Cmn_DashSmoke_2 = 0x032, // Scale Factor: 0.5
    RP_Cmn_DashSmoke_3 = 0x045,
    RP_Cmn_DashSmoke_4 = 0x245,

    // RP_Cmn_DashSnow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_DashSnow_0 = 0x091,
    RP_Cmn_DashSnow_1 = 0x092, // Scale Factor: 0.8
    RP_Cmn_DashSnow_2 = 0x093, // Scale Factor: 0.5
    RP_Cmn_DashSnow_3 = 0x094,
    RP_Cmn_DashSnow_4 = 0x247,
    RP_Cmn_DashSnow_5 = 0x372, // Translation: (0.0, -8.0, 0.0)

    // RP_Cmn_EnemyBurst
    // User Data: 0x80000000
    // Emitter Count: 6
    RP_Cmn_EnemyBurst_00 = 0x11B, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_01 = 0x12C, // Scale Factor: 0.7, Translation: (0.0, 2.0, 0.0)
    RP_Cmn_EnemyBurst_02 = 0x12D, // Scale Factor: 0.7, Translation: (0.0, 8.0, 0.0)
    RP_Cmn_EnemyBurst_03 = 0x166, // Translation: (0.0, 5.0, 0.0)
    RP_Cmn_EnemyBurst_04 = 0x167, // Scale Factor: 0.5
    RP_Cmn_EnemyBurst_05 = 0x168, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_06 = 0x169,
    RP_Cmn_EnemyBurst_07 = 0x16A, // Scale Factor: 0.7, Translation: (0.0, 8.0, 0.0)
    RP_Cmn_EnemyBurst_08 = 0x16B, // Scale Factor: 0.5
    RP_Cmn_EnemyBurst_09 = 0x16C, // Scale Factor: 0.7, Translation: (0.0, 8.0, 0.0)
    RP_Cmn_EnemyBurst_10 = 0x1FD, // Translation: (0.0, 5.0, 0.0)
    RP_Cmn_EnemyBurst_11 = 0x1FE, // Translation: (0.0, 10.0, 0.0)
    RP_Cmn_EnemyBurst_12 = 0x211, // Scale Factor: 0.8
    RP_Cmn_EnemyBurst_13 = 0x212, // Scale Factor: 0.5
    RP_Cmn_EnemyBurst_14 = 0x213, // Scale Factor: 0.5
    RP_Cmn_EnemyBurst_15 = 0x221, // Scale Factor: 0.6
    RP_Cmn_EnemyBurst_16 = 0x22C,
    RP_Cmn_EnemyBurst_17 = 0x231,
    RP_Cmn_EnemyBurst_18 = 0x234, // Scale Factor: 0.5
    RP_Cmn_EnemyBurst_19 = 0x235, // Scale Factor: 0.75
    RP_Cmn_EnemyBurst_20 = 0x23D, // Scale Factor: 0.6
    RP_Cmn_EnemyBurst_21 = 0x252, // Scale Factor: 0.8
    RP_Cmn_EnemyBurst_22 = 0x281, // Scale Factor: 1.1
    RP_Cmn_EnemyBurst_23 = 0x282, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_24 = 0x283, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_25 = 0x288,
    RP_Cmn_EnemyBurst_26 = 0x296, // Translation: (0.0, 15.0, 0.0)
    RP_Cmn_EnemyBurst_27 = 0x2B2, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_28 = 0x2B8, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_29 = 0x2BA, // Scale Factor: 0.8
    RP_Cmn_EnemyBurst_30 = 0x2C3, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_31 = 0x362,
    RP_Cmn_EnemyBurst_32 = 0x365,
    RP_Cmn_EnemyBurst_33 = 0x367, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_34 = 0x368, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_35 = 0x36E, // Scale Factor: 0.9
    RP_Cmn_EnemyBurst_36 = 0x39D, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_37 = 0x3D5,
    RP_Cmn_EnemyBurst_38 = 0x48E, // Scale Factor: 0.8
    RP_Cmn_EnemyBurst_39 = 0x48F, // Scale Factor: 1.6
    RP_Cmn_EnemyBurst_40 = 0x490, // Translation: (0.0, -4.0, 0.0)
    RP_Cmn_EnemyBurst_41 = 0x491, // Scale Factor: 0.8, Translation: (0.0, -4.0, 0.0)
    RP_Cmn_EnemyBurst_42 = 0x492, // Scale Factor: 0.8
    RP_Cmn_EnemyBurst_43 = 0x4CD, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_44 = 0x4CE, // Scale Factor: 0.9, Translation: (0.0, 4.0, 0.0)
    RP_Cmn_EnemyBurst_45 = 0x4CF, // Scale Factor: 0.7
    RP_Cmn_EnemyBurst_46 = 0x4D1, // Scale Factor: 0.45

    // RP_Cmn_Explosion
    // User Data: 0x00000000
    // Emitter Count: 9
    RP_Cmn_Explosion_0 = 0x00D,
    RP_Cmn_Explosion_1 = 0x00E,
    RP_Cmn_Explosion_2 = 0x014,
    RP_Cmn_Explosion_3 = 0x45F, // Scale Factor: 2.25

    // RP_Cmn_FeatherFall
    // User Data: 0x00040000
    // Emitter Count: 2
    RP_Cmn_FeatherFall_0 = 0x112, // Scale Factor: 0.9
    RP_Cmn_FeatherFall_1 = 0x12E, // Scale Factor: 0.9
    RP_Cmn_FeatherFall_2 = 0x1E8, // Scale Factor: 1.25

    // RP_Cmn_Fireball
    // User Data: 0x80040000
    // Emitter Count: 6
    RP_Cmn_Fireball = 0x000,

    // RP_Cmn_FireballHit
    // User Data: 0x80000000
    // Emitter Count: 6
    RP_Cmn_FireballHit = 0x004,

    // RP_Cmn_HitEX
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Cmn_HitEX = 0x179, // Scale Factor: 1.2, Translation: (0.0, 5.0, 0.0)

    // RP_Cmn_HitNormal
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Cmn_HitNormal = 0x015, // Scale Factor: 0.85

    // RP_Cmn_Iceball
    // User Data: 0x80040000
    // Emitter Count: 8
    RP_Cmn_Iceball_0 = 0x005,
    RP_Cmn_Iceball_1 = 0x006,
    RP_Cmn_Iceball_2 = 0x007,
    RP_Cmn_Iceball_3 = 0x008,

    // RP_Cmn_IceballHit
    // User Data: 0x80080000
    // Emitter Count: 5
    RP_Cmn_IceballHit = 0x009,

    // RP_Cmn_LandingIce
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Cmn_LandingIce_00 = 0x0B7,
    RP_Cmn_LandingIce_01 = 0x0B8, // Scale Factor: 0.8
    RP_Cmn_LandingIce_02 = 0x0B9, // Scale Factor: 0.5
    RP_Cmn_LandingIce_03 = 0x0BA,
    RP_Cmn_LandingIce_04 = 0x10D, // Scale Factor: 0.7
    RP_Cmn_LandingIce_05 = 0x11F, // Scale Factor: 0.8
    RP_Cmn_LandingIce_06 = 0x15F, // Scale Factor: 0.8
    RP_Cmn_LandingIce_07 = 0x1B3, // Scale Factor: 0.8
    RP_Cmn_LandingIce_08 = 0x1F0, // Scale Factor: 1.2
    RP_Cmn_LandingIce_09 = 0x202, // Translation: (0.0, 2.0, 10.0)
    RP_Cmn_LandingIce_10 = 0x207,
    RP_Cmn_LandingIce_11 = 0x24D,
    RP_Cmn_LandingIce_12 = 0x26A,
    RP_Cmn_LandingIce_13 = 0x27B, // Scale Factor: 0.8
    RP_Cmn_LandingIce_14 = 0x2A0,
    RP_Cmn_LandingIce_15 = 0x2AD,
    RP_Cmn_LandingIce_16 = 0x2BE, // Scale Factor: 0.8
    RP_Cmn_LandingIce_17 = 0x2CD,
    RP_Cmn_LandingIce_18 = 0x315,
    RP_Cmn_LandingIce_19 = 0x36C,
    RP_Cmn_LandingIce_20 = 0x3AB, // Scale Factor: 0.8

    // RP_Cmn_LandingPillarWtr
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Cmn_LandingPillarWtr_00 = 0x0D0,
    RP_Cmn_LandingPillarWtr_01 = 0x0D1, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_02 = 0x0D2, // Scale Factor: 0.5
    RP_Cmn_LandingPillarWtr_03 = 0x0D3,
    RP_Cmn_LandingPillarWtr_04 = 0x10E, // Scale Factor: 0.7
    RP_Cmn_LandingPillarWtr_05 = 0x120, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_06 = 0x160, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_07 = 0x1B4, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_08 = 0x1F1, // Scale Factor: 1.2
    RP_Cmn_LandingPillarWtr_09 = 0x203, // Translation: (0.0, 2.0, 10.0)
    RP_Cmn_LandingPillarWtr_10 = 0x208,
    RP_Cmn_LandingPillarWtr_11 = 0x24E,
    RP_Cmn_LandingPillarWtr_12 = 0x26B,
    RP_Cmn_LandingPillarWtr_13 = 0x27C, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_14 = 0x2A1,
    RP_Cmn_LandingPillarWtr_15 = 0x2AE,
    RP_Cmn_LandingPillarWtr_16 = 0x2BF, // Scale Factor: 0.8
    RP_Cmn_LandingPillarWtr_17 = 0x2CE,
    RP_Cmn_LandingPillarWtr_18 = 0x2F8,
    RP_Cmn_LandingPillarWtr_19 = 0x3AC, // Scale Factor: 0.8

    // RP_Cmn_LandingSand
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Cmn_LandingSand_00 = 0x085,
    RP_Cmn_LandingSand_01 = 0x086, // Scale Factor: 0.8
    RP_Cmn_LandingSand_02 = 0x087, // Scale Factor: 0.5
    RP_Cmn_LandingSand_03 = 0x088,
    RP_Cmn_LandingSand_04 = 0x10B, // Scale Factor: 0.7
    RP_Cmn_LandingSand_05 = 0x11D, // Scale Factor: 0.8
    RP_Cmn_LandingSand_06 = 0x15D, // Scale Factor: 0.8
    RP_Cmn_LandingSand_07 = 0x1B1, // Scale Factor: 0.8
    RP_Cmn_LandingSand_08 = 0x1EE, // Scale Factor: 1.2
    RP_Cmn_LandingSand_09 = 0x200, // Translation: (0.0, 2.0, 10.0)
    RP_Cmn_LandingSand_10 = 0x205,
    RP_Cmn_LandingSand_11 = 0x24B,
    RP_Cmn_LandingSand_12 = 0x268,
    RP_Cmn_LandingSand_13 = 0x279, // Scale Factor: 0.8
    RP_Cmn_LandingSand_14 = 0x29E,
    RP_Cmn_LandingSand_15 = 0x2AB,
    RP_Cmn_LandingSand_16 = 0x2BC, // Scale Factor: 0.8
    RP_Cmn_LandingSand_17 = 0x2CB,
    RP_Cmn_LandingSand_18 = 0x3A9, // Scale Factor: 0.8

    // RP_Cmn_LandingSmoke
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Cmn_LandingSmoke_00 = 0x036,
    RP_Cmn_LandingSmoke_01 = 0x037, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_02 = 0x038, // Scale Factor: 0.5
    RP_Cmn_LandingSmoke_03 = 0x047,
    RP_Cmn_LandingSmoke_04 = 0x06F,
    RP_Cmn_LandingSmoke_05 = 0x0F5, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_06 = 0x0F7,
    RP_Cmn_LandingSmoke_07 = 0x0F8, // Scale Factor: 0.7
    RP_Cmn_LandingSmoke_08 = 0x10A, // Scale Factor: 0.7
    RP_Cmn_LandingSmoke_09 = 0x113, // Scale Factor: 1.75
    RP_Cmn_LandingSmoke_10 = 0x114, // Translation: (0.0, 0.0, 5.0)
    RP_Cmn_LandingSmoke_11 = 0x116,
    RP_Cmn_LandingSmoke_12 = 0x117, // Scale Factor: 0.75, Translation: (0.0, 0.0, 5.0)
    RP_Cmn_LandingSmoke_13 = 0x11C, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_14 = 0x140, // Scale Factor: 1.4
    RP_Cmn_LandingSmoke_15 = 0x141, // Translation: (0.0, -3.0, 0.0)
    RP_Cmn_LandingSmoke_16 = 0x15C, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_17 = 0x1B0, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_18 = 0x1ED, // Scale Factor: 1.2
    RP_Cmn_LandingSmoke_19 = 0x1FF, // Translation: (0.0, 2.0, 10.0)
    RP_Cmn_LandingSmoke_20 = 0x204,
    RP_Cmn_LandingSmoke_21 = 0x24A,
    RP_Cmn_LandingSmoke_22 = 0x278, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_23 = 0x29D,
    RP_Cmn_LandingSmoke_24 = 0x2AA,
    RP_Cmn_LandingSmoke_25 = 0x2B9, // Translation: (0.0, 0.0, 10.0)
    RP_Cmn_LandingSmoke_26 = 0x2BB, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_27 = 0x2C7,
    RP_Cmn_LandingSmoke_28 = 0x2C8, // Scale Factor: 0.6
    RP_Cmn_LandingSmoke_29 = 0x2CA,
    RP_Cmn_LandingSmoke_30 = 0x2D7, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_31 = 0x2D8, // Scale Factor: 0.6
    RP_Cmn_LandingSmoke_32 = 0x2F6,
    RP_Cmn_LandingSmoke_33 = 0x2F7, // Scale Factor: 0.7
    RP_Cmn_LandingSmoke_34 = 0x363,
    RP_Cmn_LandingSmoke_35 = 0x369,
    RP_Cmn_LandingSmoke_36 = 0x36A,
    RP_Cmn_LandingSmoke_37 = 0x3A8, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_38 = 0x3C8, // Translation: (0.0, 0.0, 5000.0)
    RP_Cmn_LandingSmoke_39 = 0x3CA, // Scale Factor: 2.0, Translation: (0.0, 0.0, 5000.0)
    RP_Cmn_LandingSmoke_40 = 0x3F4,
    RP_Cmn_LandingSmoke_41 = 0x403, // Scale Factor: 1.2
    RP_Cmn_LandingSmoke_42 = 0x404, // Scale Factor: 0.8
    RP_Cmn_LandingSmoke_43 = 0x40F, // Scale Factor: 1.2
    RP_Cmn_LandingSmoke_44 = 0x428, // Scale Factor: 1.2
    RP_Cmn_LandingSmoke_45 = 0x438,
    RP_Cmn_LandingSmoke_46 = 0x440,
    RP_Cmn_LandingSmoke_47 = 0x4B9, // Scale Factor: 1.2

    // RP_Cmn_LandingSnow
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Cmn_LandingSnow_00 = 0x09E,
    RP_Cmn_LandingSnow_01 = 0x09F, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_02 = 0x0A0, // Scale Factor: 0.5
    RP_Cmn_LandingSnow_03 = 0x0A1,
    RP_Cmn_LandingSnow_04 = 0x10C, // Scale Factor: 0.7
    RP_Cmn_LandingSnow_05 = 0x11E, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_06 = 0x15E, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_07 = 0x1B2, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_08 = 0x1EF, // Scale Factor: 1.2
    RP_Cmn_LandingSnow_09 = 0x201, // Translation: (0.0, 2.0, 10.0)
    RP_Cmn_LandingSnow_10 = 0x206,
    RP_Cmn_LandingSnow_11 = 0x24C,
    RP_Cmn_LandingSnow_12 = 0x269,
    RP_Cmn_LandingSnow_13 = 0x27A, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_14 = 0x29F,
    RP_Cmn_LandingSnow_15 = 0x2AC,
    RP_Cmn_LandingSnow_16 = 0x2BD, // Scale Factor: 0.8
    RP_Cmn_LandingSnow_17 = 0x2CC,
    RP_Cmn_LandingSnow_18 = 0x36B,
    RP_Cmn_LandingSnow_19 = 0x3AA, // Scale Factor: 0.8

    // RP_Cmn_LavaSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Cmn_LavaSplash_00 = 0x0EC, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_01 = 0x0ED, // Scale Factor: 0.9
    RP_Cmn_LavaSplash_02 = 0x0EE, // Scale Factor: 0.7
    RP_Cmn_LavaSplash_03 = 0x0EF, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_04 = 0x111, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_05 = 0x123,
    RP_Cmn_LavaSplash_06 = 0x163,
    RP_Cmn_LavaSplash_07 = 0x1B7, // Scale Factor: 0.9
    RP_Cmn_LavaSplash_08 = 0x1F4, // Scale Factor: 1.2
    RP_Cmn_LavaSplash_09 = 0x20B, // Scale Factor: 1.2
    RP_Cmn_LavaSplash_10 = 0x228,
    RP_Cmn_LavaSplash_11 = 0x22F,
    RP_Cmn_LavaSplash_12 = 0x238,
    RP_Cmn_LavaSplash_13 = 0x23B,
    RP_Cmn_LavaSplash_14 = 0x26E,
    RP_Cmn_LavaSplash_15 = 0x274,
    RP_Cmn_LavaSplash_16 = 0x27F, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_17 = 0x291,
    RP_Cmn_LavaSplash_18 = 0x292,
    RP_Cmn_LavaSplash_19 = 0x2A4,
    RP_Cmn_LavaSplash_20 = 0x2B1,
    RP_Cmn_LavaSplash_21 = 0x2C2, // Scale Factor: 0.9
    RP_Cmn_LavaSplash_22 = 0x2D1,
    RP_Cmn_LavaSplash_23 = 0x2D5, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_24 = 0x2D6, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_25 = 0x2D9, // Scale Factor: 0.7
    RP_Cmn_LavaSplash_26 = 0x2DA, // Scale Factor: 0.7
    RP_Cmn_LavaSplash_27 = 0x2DB, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_28 = 0x344, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_29 = 0x348, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_30 = 0x34C,
    RP_Cmn_LavaSplash_31 = 0x350, // Scale Factor: 1.25
    RP_Cmn_LavaSplash_32 = 0x354, // Scale Factor: 1.25
    RP_Cmn_LavaSplash_33 = 0x38C, // Scale Factor: 0.5
    RP_Cmn_LavaSplash_34 = 0x3AF,
    RP_Cmn_LavaSplash_35 = 0x3CE, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_36 = 0x3D8, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_37 = 0x3DB, // Scale Factor: 1.3
    RP_Cmn_LavaSplash_38 = 0x3DE,
    RP_Cmn_LavaSplash_39 = 0x3E1, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_40 = 0x3E5, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_41 = 0x3E7, // Scale Factor: 1.1
    RP_Cmn_LavaSplash_42 = 0x3E9, // Scale Factor: 1.2
    RP_Cmn_LavaSplash_43 = 0x3EA, // Scale Factor: 1.4
    RP_Cmn_LavaSplash_44 = 0x3EB, // Scale Factor: 0.8
    RP_Cmn_LavaSplash_45 = 0x401,
    RP_Cmn_LavaSplash_46 = 0x42C, // Scale Factor: 1.5
    RP_Cmn_LavaSplash_47 = 0x453, // Scale Factor: 1.4, Translation: (0.0, 0.0, 100.0)

    // RP_Cmn_LavaSplash2
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Cmn_LavaSplash2_00 = 0x337, // Scale Factor: 0.8
    RP_Cmn_LavaSplash2_01 = 0x338, // Scale Factor: 0.8
    RP_Cmn_LavaSplash2_02 = 0x339,
    RP_Cmn_LavaSplash2_03 = 0x33A,
    RP_Cmn_LavaSplash2_04 = 0x33B, // Scale Factor: 1.1
    RP_Cmn_LavaSplash2_05 = 0x33C, // Scale Factor: 0.9
    RP_Cmn_LavaSplash2_06 = 0x33D, // Scale Factor: 0.7
    RP_Cmn_LavaSplash2_07 = 0x33E, // Scale Factor: 1.1
    RP_Cmn_LavaSplash2_08 = 0x33F, // Scale Factor: 0.9
    RP_Cmn_LavaSplash2_09 = 0x340, // Scale Factor: 0.7
    RP_Cmn_LavaSplash2_10 = 0x341, // Scale Factor: 0.9
    RP_Cmn_LavaSplash2_11 = 0x345, // Scale Factor: 0.8
    RP_Cmn_LavaSplash2_12 = 0x349, // Scale Factor: 0.8
    RP_Cmn_LavaSplash2_13 = 0x34D,
    RP_Cmn_LavaSplash2_14 = 0x351, // Scale Factor: 1.25
    RP_Cmn_LavaSplash2_15 = 0x355, // Scale Factor: 1.25
    RP_Cmn_LavaSplash2_16 = 0x3B0,
    RP_Cmn_LavaSplash2_17 = 0x3CF, // Scale Factor: 0.8

    // RP_Cmn_LavaSplashL
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Cmn_LavaSplashL_0 = 0x0F0, // Scale Factor: 1.1
    RP_Cmn_LavaSplashL_1 = 0x0F1, // Scale Factor: 0.9
    RP_Cmn_LavaSplashL_2 = 0x0F2, // Scale Factor: 0.7
    RP_Cmn_LavaSplashL_3 = 0x0F3, // Scale Factor: 1.1

    // RP_Cmn_LavaSplashS
    // User Data: 0x00000000
    // Emitter Count: 2

    // RP_Cmn_PoisonSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Cmn_PoisonSplash_00 = 0x0E4, // Scale Factor: 1.1
    RP_Cmn_PoisonSplash_01 = 0x0E5, // Scale Factor: 0.9
    RP_Cmn_PoisonSplash_02 = 0x0E6, // Scale Factor: 0.7
    RP_Cmn_PoisonSplash_03 = 0x0E7, // Scale Factor: 1.1
    RP_Cmn_PoisonSplash_04 = 0x110, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_05 = 0x122,
    RP_Cmn_PoisonSplash_06 = 0x162,
    RP_Cmn_PoisonSplash_07 = 0x1B6, // Scale Factor: 0.9
    RP_Cmn_PoisonSplash_08 = 0x1F3, // Scale Factor: 1.2
    RP_Cmn_PoisonSplash_09 = 0x20A, // Scale Factor: 1.2
    RP_Cmn_PoisonSplash_10 = 0x227,
    RP_Cmn_PoisonSplash_11 = 0x22E,
    RP_Cmn_PoisonSplash_12 = 0x237,
    RP_Cmn_PoisonSplash_13 = 0x23A,
    RP_Cmn_PoisonSplash_14 = 0x26D,
    RP_Cmn_PoisonSplash_15 = 0x273,
    RP_Cmn_PoisonSplash_16 = 0x27E, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_17 = 0x2A3,
    RP_Cmn_PoisonSplash_18 = 0x2B0,
    RP_Cmn_PoisonSplash_19 = 0x2C1, // Scale Factor: 0.9
    RP_Cmn_PoisonSplash_20 = 0x2D0,
    RP_Cmn_PoisonSplash_21 = 0x343, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_22 = 0x347, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_23 = 0x34B,
    RP_Cmn_PoisonSplash_24 = 0x34F, // Scale Factor: 1.25
    RP_Cmn_PoisonSplash_25 = 0x353, // Scale Factor: 1.25
    RP_Cmn_PoisonSplash_26 = 0x35C, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_27 = 0x35D, // Scale Factor: 1.25
    RP_Cmn_PoisonSplash_28 = 0x395,
    RP_Cmn_PoisonSplash_29 = 0x3AE,
    RP_Cmn_PoisonSplash_30 = 0x3CD, // Scale Factor: 0.8
    RP_Cmn_PoisonSplash_31 = 0x3D0,
    RP_Cmn_PoisonSplash_32 = 0x3D7, // Scale Factor: 1.1
    RP_Cmn_PoisonSplash_33 = 0x3DA, // Scale Factor: 1.3
    RP_Cmn_PoisonSplash_34 = 0x3DC, // Scale Factor: 0.5
    RP_Cmn_PoisonSplash_35 = 0x3DD,
    RP_Cmn_PoisonSplash_36 = 0x3E0, // Scale Factor: 1.1
    RP_Cmn_PoisonSplash_37 = 0x3E4, // Scale Factor: 1.1

    // RP_Cmn_PoisonSplashL
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Cmn_PoisonSplashL_0 = 0x0E8, // Scale Factor: 1.1
    RP_Cmn_PoisonSplashL_1 = 0x0E9, // Scale Factor: 0.9
    RP_Cmn_PoisonSplashL_2 = 0x0EA, // Scale Factor: 0.7
    RP_Cmn_PoisonSplashL_3 = 0x0EB, // Scale Factor: 1.1

    // RP_Cmn_PoisonSplashS
    // User Data: 0x00000000
    // Emitter Count: 2

    // RP_Cmn_RunIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_RunIce_0 = 0x0A6,
    RP_Cmn_RunIce_1 = 0x0A7, // Scale Factor: 0.8
    RP_Cmn_RunIce_2 = 0x0A8, // Scale Factor: 0.5
    RP_Cmn_RunIce_3 = 0x0A9,
    RP_Cmn_RunIce_4 = 0x1AA,
    RP_Cmn_RunIce_5 = 0x266, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_RunIce_6 = 0x40D, // Scale Factor: 0.8

    // RP_Cmn_RunPillarWtr
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_RunPillarWtr_0 = 0x0BF,
    RP_Cmn_RunPillarWtr_1 = 0x0C0, // Scale Factor: 0.8
    RP_Cmn_RunPillarWtr_2 = 0x0C1, // Scale Factor: 0.5
    RP_Cmn_RunPillarWtr_3 = 0x0C2,
    RP_Cmn_RunPillarWtr_4 = 0x1AB,
    RP_Cmn_RunPillarWtr_5 = 0x267, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_RunSand
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_RunSand_0 = 0x074,
    RP_Cmn_RunSand_1 = 0x076, // Scale Factor: 0.5
    RP_Cmn_RunSand_2 = 0x077,
    RP_Cmn_RunSand_3 = 0x1A8,
    RP_Cmn_RunSand_4 = 0x246,
    RP_Cmn_RunSand_5 = 0x264, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_RunSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Cmn_RunSmoke_0 = 0x06E, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_RunSmoke_1 = 0x1A7,
    RP_Cmn_RunSmoke_2 = 0x3F5, // Scale Factor: 1.2

    // RP_Cmn_RunSnow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_RunSnow_0 = 0x08D,
    RP_Cmn_RunSnow_1 = 0x08E, // Scale Factor: 0.8
    RP_Cmn_RunSnow_2 = 0x08F, // Scale Factor: 0.5
    RP_Cmn_RunSnow_3 = 0x090,
    RP_Cmn_RunSnow_4 = 0x1A9,
    RP_Cmn_RunSnow_5 = 0x265, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_SlipIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_SlipIce_0 = 0x0AE, // Translation: (0.0, -2.0, 0.0)
    RP_Cmn_SlipIce_1 = 0x0AF, // Scale Factor: 0.8, Translation: (0.0, -1.5, 0.0)
    RP_Cmn_SlipIce_2 = 0x0B0, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_Cmn_SlipIce_3 = 0x0B1, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipIce_4 = 0x0B2, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_SlipPillarWtr
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_SlipPillarWtr_0 = 0x0C7, // Translation: (0.0, -2.0, 0.0)
    RP_Cmn_SlipPillarWtr_1 = 0x0C8, // Scale Factor: 0.8, Translation: (0.0, -1.5, 0.0)
    RP_Cmn_SlipPillarWtr_2 = 0x0C9, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_Cmn_SlipPillarWtr_3 = 0x0CA, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipPillarWtr_4 = 0x0CB, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_SlipSand
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_SlipSand_0 = 0x075, // Scale Factor: 0.8
    RP_Cmn_SlipSand_1 = 0x07C, // Translation: (0.0, -2.0, 0.0)
    RP_Cmn_SlipSand_2 = 0x07D, // Scale Factor: 0.8, Translation: (0.0, -1.5, 0.0)
    RP_Cmn_SlipSand_3 = 0x07E, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_Cmn_SlipSand_4 = 0x07F, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipSand_5 = 0x080, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_SlipSmoke
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Cmn_SlipSmoke_0 = 0x02D,
    RP_Cmn_SlipSmoke_1 = 0x02E, // Scale Factor: 0.8
    RP_Cmn_SlipSmoke_2 = 0x02F, // Scale Factor: 0.5
    RP_Cmn_SlipSmoke_3 = 0x033, // Translation: (0.0, -2.0, 0.0)
    RP_Cmn_SlipSmoke_4 = 0x034, // Scale Factor: 0.8
    RP_Cmn_SlipSmoke_5 = 0x035, // Scale Factor: 0.5
    RP_Cmn_SlipSmoke_6 = 0x046, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipSmoke_7 = 0x073, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipSmoke_8 = 0x405,

    // RP_Cmn_SlipSnow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Cmn_SlipSnow_0 = 0x095, // Translation: (0.0, -2.0, 0.0)
    RP_Cmn_SlipSnow_1 = 0x096, // Scale Factor: 0.8, Translation: (0.0, -1.5, 0.0)
    RP_Cmn_SlipSnow_2 = 0x097, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_Cmn_SlipSnow_3 = 0x098, // Translation: (0.0, -5.0, 0.0)
    RP_Cmn_SlipSnow_4 = 0x099, // Translation: (0.0, -5.0, 0.0)

    // RP_Cmn_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Cmn_WaterSplash_00 = 0x0DC, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_01 = 0x0DD, // Scale Factor: 0.9
    RP_Cmn_WaterSplash_02 = 0x0DE, // Scale Factor: 0.7
    RP_Cmn_WaterSplash_03 = 0x0DF, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_04 = 0x10F, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_05 = 0x121,
    RP_Cmn_WaterSplash_06 = 0x161,
    RP_Cmn_WaterSplash_07 = 0x1B5, // Scale Factor: 0.9
    RP_Cmn_WaterSplash_08 = 0x1F2, // Scale Factor: 1.2
    RP_Cmn_WaterSplash_09 = 0x209, // Scale Factor: 1.2
    RP_Cmn_WaterSplash_10 = 0x226,
    RP_Cmn_WaterSplash_11 = 0x22D,
    RP_Cmn_WaterSplash_12 = 0x236,
    RP_Cmn_WaterSplash_13 = 0x239,
    RP_Cmn_WaterSplash_14 = 0x26C,
    RP_Cmn_WaterSplash_15 = 0x272, // Translation: (0.0, 0.8, 0.0)
    RP_Cmn_WaterSplash_16 = 0x27D, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_17 = 0x2A2,
    RP_Cmn_WaterSplash_18 = 0x2AF,
    RP_Cmn_WaterSplash_19 = 0x2C0, // Scale Factor: 0.9
    RP_Cmn_WaterSplash_20 = 0x2CF,
    RP_Cmn_WaterSplash_21 = 0x2F9, // Scale Factor: 1.2
    RP_Cmn_WaterSplash_22 = 0x335,
    RP_Cmn_WaterSplash_23 = 0x336,
    RP_Cmn_WaterSplash_24 = 0x342, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_25 = 0x346, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_26 = 0x34A,
    RP_Cmn_WaterSplash_27 = 0x34E, // Scale Factor: 1.25
    RP_Cmn_WaterSplash_28 = 0x352, // Scale Factor: 1.25
    RP_Cmn_WaterSplash_29 = 0x36D,
    RP_Cmn_WaterSplash_30 = 0x39E,
    RP_Cmn_WaterSplash_31 = 0x3AD,
    RP_Cmn_WaterSplash_32 = 0x3CC, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_33 = 0x3D6, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_34 = 0x3D9, // Scale Factor: 1.3
    RP_Cmn_WaterSplash_35 = 0x3DF, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_36 = 0x3E2, // Scale Factor: 1.5
    RP_Cmn_WaterSplash_37 = 0x3E3, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_38 = 0x3E6, // Scale Factor: 1.1
    RP_Cmn_WaterSplash_39 = 0x3E8, // Scale Factor: 1.2
    RP_Cmn_WaterSplash_40 = 0x3EC, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_41 = 0x4C2, // Scale Factor: 0.8
    RP_Cmn_WaterSplash_42 = 0x4C3, // Scale Factor: 0.8

    // RP_Cmn_WaterSplashFW
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Cmn_WaterSplashFW = 0x452,

    // RP_Cmn_WaterSplashL
    // User Data: 0x00200000
    // Emitter Count: 5
    RP_Cmn_WaterSplashL_0 = 0x0E0, // Scale Factor: 1.1
    RP_Cmn_WaterSplashL_1 = 0x0E1, // Scale Factor: 0.9
    RP_Cmn_WaterSplashL_2 = 0x0E2, // Scale Factor: 0.7
    RP_Cmn_WaterSplashL_3 = 0x0E3, // Scale Factor: 1.1

    // RP_Cmn_WaterSplashS
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Cmn_WaterSplashS_0 = 0x0D9, // Scale Factor: 1.1
    RP_Cmn_WaterSplashS_1 = 0x0DA, // Scale Factor: 0.9
    RP_Cmn_WaterSplashS_2 = 0x0DB, // Scale Factor: 0.7

    // RP_CoinBattle_ResultTop
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_CoinBattle_ResultTop = 0x102,

    // RP_CoinBattle_Result_CoinGet
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_CoinBattle_Result_CoinGet = 0x463, // Scale Factor: 3.0

    // RP_CoinBattle_Result_StarCoinGet
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_CoinBattle_Result_StarCoinGet = 0x464, // Scale Factor: 3.0

    // RP_CoinBlueGet
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_CoinBlueGet = 0x04E, // Scale Factor: 1.2

    // RP_Coinedit_Coin_on
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Coinedit_Coin_on = 0x45C,

    // RP_Coinedit_StarCoin_on
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Coinedit_StarCoin_on = 0x45D,

    // RP_CoinGet_Mask
    // User Data: 0x00400000
    // Emitter Count: 1
    RP_CoinGet_Mask_0 = 0x050, // Scale Factor: 2.0
    RP_CoinGet_Mask_1 = 0x052, // Scale Factor: 4.0

    // RP_CoinGreenGet
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_CoinGreenGet = 0x04F, // Scale Factor: 1.2

    // RP_CoinNormalGet
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_CoinNormalGet = 0x04C, // Scale Factor: 1.2

    // RP_CoinNormalTail
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CoinNormalTail = 0x165,

    // RP_CoinRedGet
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_CoinRedGet = 0x04D, // Scale Factor: 1.2

    // RP_CoinStarGet
    // User Data: 0x00000000
    // Emitter Count: 8
    RP_CoinStarGet = 0x051,

    // RP_Crasher_PunchSwing
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Crasher_PunchSwing = 0x293,

    // RP_Crasher_PunchSwingLeft
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Crasher_PunchSwingLeft = 0x2DE,

    // RP_Crasher_PunchSwingRight
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Crasher_PunchSwingRight = 0x2DD,

    // RP_CSelect_AppSmoke
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_AppSmoke_0 = 0x46E, // Scale Factor: 2.0
    RP_CSelect_AppSmoke_1 = 0x46F, // Scale Factor: 2.0
    RP_CSelect_AppSmoke_2 = 0x470, // Scale Factor: 2.0
    RP_CSelect_AppSmoke_3 = 0x471, // Scale Factor: 2.0
    RP_CSelect_AppSmoke_4 = 0x4BD, // Scale Factor: 0.6, Translation: (0.0, 8.0, 0.0)

    // RP_CSelect_CannonShoot
    // User Data: 0x40000000
    // Emitter Count: 4
    RP_CSelect_CannonShoot = 0x385,

    // RP_CSelect_Chorobon_Disapp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_CSelect_Chorobon_Disapp = 0x472, // Scale Factor: 2.0

    // RP_CSelect_EnemyBurst
    // User Data: 0x80000000
    // Emitter Count: 5
    RP_CSelect_EnemyBurst = 0x387, // Scale Factor: 2.0

    // RP_CSelect_FlyingSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_FlyingSmoke_0 = 0x37C,
    RP_CSelect_FlyingSmoke_1 = 0x37D, // Scale Factor: 0.8
    RP_CSelect_FlyingSmoke_2 = 0x37E, // Scale Factor: 0.6

    // RP_CSelect_HitNormal
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_CSelect_HitNormal = 0x386, // Scale Factor: 3.0

    // RP_CSelect_HouseBound
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_CSelect_HouseBound = 0x383, // Scale Factor: 2.0

    // RP_CSelect_HouseDisapp
    // User Data: 0x40000000
    // Emitter Count: 2
    RP_CSelect_HouseDisapp = 0x382,

    // RP_CSelect_JrClown_Enter
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_JrClown_Enter = 0x476, // Scale Factor: 2.0

    // RP_CSelect_Kameck_Magic
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_CSelect_Kameck_Magic = 0x4C0,

    // RP_CSelect_LandingSmoke
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_CSelect_LandingSmoke_0 = 0x379,
    RP_CSelect_LandingSmoke_1 = 0x37A, // Scale Factor: 0.8
    RP_CSelect_LandingSmoke_2 = 0x37B, // Scale Factor: 0.5
    RP_CSelect_LandingSmoke_3 = 0x465, // Scale Factor: 1.3

    // RP_CSelect_Mario_PMusa
    // User Data: 0x00800000
    // Emitter Count: 2
    RP_CSelect_Mario_PMusa = 0x2EE, // Scale Factor: 2.3, Translation: (0.0, 40.0, 0.0)

    // RP_CSelect_Mario_Star
    // User Data: 0x00800000
    // Emitter Count: 4
    RP_CSelect_Mario_Star_0 = 0x2DF, // Scale Factor: 2.3, Translation: (0.0, 40.0, 0.0)
    RP_CSelect_Mario_Star_1 = 0x2E0, // Scale Factor: 1.84, Translation: (0.0, 25.0, 0.0)
    RP_CSelect_Mario_Star_2 = 0x2E1, // Scale Factor: 1.1, Translation: (0.0, 16.0, 0.0)

    // RP_CSelect_Penta_Glide_ice
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_CSelect_Penta_Glide_ice = 0x388,

    // RP_CSelect_PointChange
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_CSelect_PointChange = 0x37F,

    // RP_CSelect_Puku_Splash
    // User Data: 0x00200000
    // Emitter Count: 7
    RP_CSelect_Puku_Splash = 0x389,

    // RP_CSelect_Puku_WaterDrop
    // User Data: 0x00200000
    // Emitter Count: 1
    RP_CSelect_Puku_WaterDrop = 0x38A,

    // RP_CSelect_RunSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_RunSmoke_0 = 0x373,
    RP_CSelect_RunSmoke_1 = 0x374, // Scale Factor: 0.8
    RP_CSelect_RunSmoke_2 = 0x375, // Scale Factor: 0.5
    RP_CSelect_RunSmoke_3 = 0x474, // Scale Factor: 1.25
    RP_CSelect_RunSmoke_4 = 0x475, // Scale Factor: 1.25

    // RP_CSelect_ShadowCourseIn
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_CSelect_ShadowCourseIn = 0x384, // Scale Factor: 1.5

    // RP_CSelect_ShipAttack
    // User Data: 0x80000000
    // Emitter Count: 6
    RP_CSelect_ShipAttack = 0x380, // Scale Factor: 2.5

    // RP_CSelect_ShipJr_Crash
    // User Data: 0x00080000
    // Emitter Count: 5
    RP_CSelect_ShipJr_Crash = 0x46A, // Scale Factor: 1.8

    // RP_CSelect_ShipJr_CrashSmoke
    // User Data: 0x00000000
    // Emitter Count: 3

    // RP_CSelect_ShipJr_Explosion
    // User Data: 0x00000000
    // Emitter Count: 10
    RP_CSelect_ShipJr_Explosion = 0x468,

    // RP_CSelect_ShipJr_FallSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_ShipJr_FallSmoke = 0x469, // Scale Factor: 5.0

    // RP_CSelect_ShipJr_Hover_a
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_ShipJr_Hover_a = 0x466,

    // RP_CSelect_ShipJr_Hover_b
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_ShipJr_Hover_b = 0x467,

    // RP_CSelect_ShipSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_ShipSmoke = 0x381, // Scale Factor: 1.5

    // RP_CSelect_ShootingStar
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_ShootingStar = 0x4C4,

    // RP_CSelect_SlipSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_SlipSmoke_0 = 0x376,
    RP_CSelect_SlipSmoke_1 = 0x377, // Scale Factor: 0.8
    RP_CSelect_SlipSmoke_2 = 0x378, // Scale Factor: 0.5

    // RP_CSelect_SnowFall
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_SnowFall = 0x38B,

    // RP_CSelect_StarCoin_Open
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_CSelect_StarCoin_Open = 0x46C,

    // RP_CSelect_StarGate_Enter
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_StarGate_Enter = 0x46D,

    // RP_CSelect_StarGate_Fall
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_StarGate_Fall = 0x4BF,

    // RP_CSelect_StarGate_Landing
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_StarGate_Landing = 0x46B,

    // RP_CSelect_WaterPillar_bottom
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_WaterPillar_bottom = 0x3D4,

    // RP_CSelect_WaterPillar_sign
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_CSelect_WaterPillar_sign = 0x3D2,

    // RP_CSelect_WaterPillar_top
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_CSelect_WaterPillar_top = 0x3D3,

    // RP_Daikonbou_Hit
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_Daikonbou_Hit = 0x398,

    // RP_Demo_CannonHit
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Demo_CannonHit_0 = 0x218, // Scale Factor: 1.3
    RP_Demo_CannonHit_1 = 0x219, // Scale Factor: 1.5

    // RP_Demo_CannonHit_DV
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Demo_CannonHit_DV = 0x25C, // Scale Factor: 0.25

    // RP_Demo_CannonShoot
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_Demo_CannonShoot_0 = 0x21A, // Scale Factor: 0.55, Translation: (0.0, 0.0, 100.0)
    RP_Demo_CannonShoot_1 = 0x21B, // Scale Factor: 0.55, Translation: (0.0, 0.0, 100.0)

    // RP_Demo_CannonShoot_DV
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_Demo_CannonShoot_DV = 0x25B, // Scale Factor: 1.25

    // RP_Demo_DashSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Demo_DashSmoke_0 = 0x328, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_DashSmoke_1 = 0x329, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_DashSmoke_2 = 0x32A, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_DashSmoke_3 = 0x32B, // Translation: (0.0, 0.0, 300.0)

    // RP_Demo_DongriTreeLeaf
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Demo_DongriTreeLeaf = 0x21D,

    // RP_Demo_Koopa_down
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Demo_Koopa_down = 0x32C, // Scale Factor: 1.3

    // RP_Demo_KPHandHit
    // User Data: 0x00080000
    // Emitter Count: 5
    RP_Demo_KPHandHit = 0x21C,

    // RP_Demo_LandingSmoke
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Demo_LandingSmoke_0 = 0x17E, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_LandingSmoke_1 = 0x322, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_LandingSmoke_2 = 0x323, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_LandingSmoke_3 = 0x324, // Translation: (0.0, 0.0, 300.0)

    // RP_Demo_ShipCrash
    // User Data: 0x00080000
    // Emitter Count: 10
    RP_Demo_ShipCrash = 0x257, // Scale Factor: 1.2

    // RP_Demo_ShipDamage
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Demo_ShipDamage = 0x32E, // Scale Factor: 3.0

    // RP_Demo_ShipDamage_DV
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Demo_ShipDamage_DV = 0x32F, // Scale Factor: 3.0

    // RP_Demo_ShipParts
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_Demo_ShipParts = 0x32D, // Scale Factor: 0.7

    // RP_Demo_ShipSmoke
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Demo_ShipSmoke = 0x25A,

    // RP_Demo_SlipSmoke
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Demo_SlipSmoke_0 = 0x17F, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_SlipSmoke_1 = 0x325, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_SlipSmoke_2 = 0x326, // Translation: (0.0, 0.0, 300.0)
    RP_Demo_SlipSmoke_3 = 0x327, // Translation: (0.0, 0.0, 300.0)

    // RP_Dokan_WtrStream
    // User Data: 0x20000000
    // Emitter Count: 2
    RP_Dokan_WtrStream = 0x19C,

    // RP_Dosun_Blur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Dosun_Blur_0 = 0x16E,
    RP_Dosun_Blur_1 = 0x170, // Scale Factor: 0.55, Translation: (0.0, -2.5, 0.0)

    // RP_Dosun_Landing
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Dosun_Landing_0 = 0x16D,
    RP_Dosun_Landing_1 = 0x16F, // Scale Factor: 0.6

    // RP_DRCStar
    // User Data: 0x00040000
    // Emitter Count: 4
    RP_DRCStar = 0x48D,

    // RP_DRCStar_CountFlash
    // User Data: 0x00000000
    // Emitter Count: 9
    RP_DRCStar_CountFlash = 0x48B,

    // RP_DRCStar_LandingIce
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_DRCStar_LandingIce = 0x4A4,

    // RP_DRCStar_LandingPillarWtr
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_DRCStar_LandingPillarWtr = 0x4A5,

    // RP_DRCStar_LandingSand
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_DRCStar_LandingSand = 0x4A2,

    // RP_DRCStar_LandingSmoke
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_DRCStar_LandingSmoke = 0x4A1,

    // RP_DRCStar_LandingSnow
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_DRCStar_LandingSnow = 0x4A3,

    // RP_DRCStar_LavaSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_DRCStar_LavaSplash = 0x4A8, // Scale Factor: 1.2

    // RP_DRCStar_LavaSplash2
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_DRCStar_LavaSplash2 = 0x4A9, // Scale Factor: 1.2

    // RP_DRCStar_PoisonSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_DRCStar_PoisonSplash = 0x4A7, // Scale Factor: 1.2

    // RP_DRCStar_TouchGet
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_DRCStar_TouchGet = 0x494,

    // RP_DRCStar_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_DRCStar_WaterSplash = 0x4A6, // Scale Factor: 1.2

    // RP_DRCStar_WaterSplashFW
    // User Data: 0x00200000
    // Emitter Count: 3

    // RP_DV_TorchA
    // User Data: 0x20000000
    // Emitter Count: 2
    RP_DV_TorchA = 0x072,

    // RP_DV_TorchB
    // User Data: 0x20000000
    // Emitter Count: 2
    RP_DV_TorchB = 0x0D8,

    // RP_EggCY_blue
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggCY_blue = 0x1A3,

    // RP_EggCY_red
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggCY_red = 0x1A4,

    // RP_EggCY_yellow
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggCY_yellow = 0x1A5,

    // RP_EggY_blue
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggY_blue = 0x1A0,

    // RP_EggY_green
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggY_green = 0x19F,

    // RP_EggY_red
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggY_red = 0x1A1,

    // RP_EggY_yellow
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_EggY_yellow = 0x1A2,

    // RP_Enm_Collision
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Enm_Collision_0 = 0x06D,
    RP_Enm_Collision_1 = 0x129,
    RP_Enm_Collision_2 = 0x149,
    RP_Enm_Collision_3 = 0x1FA,
    RP_Enm_Collision_4 = 0x47A, // Scale Factor: 1.5
    RP_Enm_Collision_5 = 0x480,

    // RP_Enm_DashSmoke
    // User Data: 0x00000000
    // Emitter Count: 1

    // RP_Enm_Fireball
    // User Data: 0x80040000
    // Emitter Count: 4
    RP_Enm_Fireball = 0x003,

    // RP_Enm_ShellMoveIce
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Enm_ShellMoveIce_0 = 0x127,
    RP_Enm_ShellMoveIce_1 = 0x128,
    RP_Enm_ShellMoveIce_2 = 0x1F8, // Scale Factor: 1.2
    RP_Enm_ShellMoveIce_3 = 0x1F9, // Scale Factor: 1.2
    RP_Enm_ShellMoveIce_4 = 0x20F,
    RP_Enm_ShellMoveIce_5 = 0x210,
    RP_Enm_ShellMoveIce_6 = 0x2A8,
    RP_Enm_ShellMoveIce_7 = 0x31D,

    // RP_Enm_ShellMoveNml
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Enm_ShellMoveNml_00 = 0x124,
    RP_Enm_ShellMoveNml_01 = 0x1F5, // Scale Factor: 1.2
    RP_Enm_ShellMoveNml_02 = 0x20C,
    RP_Enm_ShellMoveNml_03 = 0x295,
    RP_Enm_ShellMoveNml_04 = 0x2A5,
    RP_Enm_ShellMoveNml_05 = 0x2FC,
    RP_Enm_ShellMoveNml_06 = 0x3F8,
    RP_Enm_ShellMoveNml_07 = 0x408,
    RP_Enm_ShellMoveNml_08 = 0x412,
    RP_Enm_ShellMoveNml_09 = 0x43B,
    RP_Enm_ShellMoveNml_10 = 0x44F,

    // RP_Enm_ShellMovePillaWtr
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Enm_ShellMovePillaWtr_0 = 0x2A9,
    RP_Enm_ShellMovePillaWtr_1 = 0x2FD,

    // RP_Enm_ShellMoveSand
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Enm_ShellMoveSand_0 = 0x125,
    RP_Enm_ShellMoveSand_1 = 0x1F6, // Scale Factor: 1.2
    RP_Enm_ShellMoveSand_2 = 0x20D,
    RP_Enm_ShellMoveSand_3 = 0x2A6,

    // RP_Enm_ShellMoveSnow
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Enm_ShellMoveSnow_0 = 0x126,
    RP_Enm_ShellMoveSnow_1 = 0x1F7, // Scale Factor: 1.2
    RP_Enm_ShellMoveSnow_2 = 0x20E,
    RP_Enm_ShellMoveSnow_3 = 0x2A7,

    // RP_Firebar
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Firebar = 0x456, // Translation: (0.0, 0.0, -800.0)

    // RP_Firesnake_Body_Dead
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Firesnake_Body_Dead = 0x29A,

    // RP_Firesnake_Body_Firechip
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Firesnake_Body_Firechip = 0x298,

    // RP_Firesnake_Head_Dead
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_Firesnake_Head_Dead = 0x299,

    // RP_Firesnake_Head_Firechip
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Firesnake_Head_Firechip = 0x297,

    // RP_FlagPass
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_FlagPass_0 = 0x063, // Translation: (0.0, 16.0, 0.0)
    RP_FlagPass_1 = 0x064, // Scale Factor: 0.8, Translation: (0.0, 10.0, 0.0)
    RP_FlagPass_2 = 0x065, // Scale Factor: 0.5, Translation: (0.0, 8.0, 0.0)

    // RP_FloatBox_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_FloatBox_WaterSplash = 0x49E,

    // RP_FPillar_Bottom
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_FPillar_Bottom = 0x01F,

    // RP_FPillar_Top
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_FPillar_Top = 0x01E,

    // RP_Fugu_SwimSplash
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Fugu_SwimSplash = 0x356,

    // RP_Fugu_WaterDrop
    // User Data: 0x00200000
    // Emitter Count: 1
    RP_Fugu_WaterDrop = 0x357,

    // RP_Fugu_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_Fugu_WaterSplash_0 = 0x358,
    RP_Fugu_WaterSplash_1 = 0x359,

    // RP_Gabon_BallA_Break
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_Gabon_BallA_Break = 0x29B,

    // RP_Gabon_BallB_Break
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_Gabon_BallB_Break = 0x29C,

    // rp_Gesso_SwimInk
    // User Data: 0x00000000
    // Emitter Count: 2
    rp_Gesso_SwimInk = 0x23C,

    // RP_GoalFlagKP2_Disapp
    // User Data: 0x80000000
    // Emitter Count: 3

    // RP_GoalFlagKP_Disapp
    // User Data: 0x80000000
    // Emitter Count: 3

    // RP_GoalFlagPLY_App
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_GoalFlagPLY_App_0 = 0x253, // Scale Factor: 1.25, Translation: (-12.0, 0.0, 10.0)
    RP_GoalFlagPLY_App_1 = 0x254, // Scale Factor: 1.25, Translation: (-12.0, 0.0, 10.0)
    RP_GoalFlagPLY_App_2 = 0x3B1, // Scale Factor: 1.25, Translation: (-12.0, 0.0, 10.0)

    // RP_Goal_Fireworks_1up
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Goal_Fireworks_1up = 0x1BD,

    // RP_Goal_Fireworks_blue
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Goal_Fireworks_blue_0 = 0x1C0,
    RP_Goal_Fireworks_blue_1 = 0x330,

    // RP_Goal_Fireworks_green
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Goal_Fireworks_green_0 = 0x1C1,
    RP_Goal_Fireworks_green_1 = 0x331,

    // RP_Goal_Fireworks_kinoko
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Goal_Fireworks_kinoko = 0x1BE,

    // RP_Goal_Fireworks_pink
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Goal_Fireworks_pink_0 = 0x1C2,
    RP_Goal_Fireworks_pink_1 = 0x332,

    // RP_Goal_Fireworks_star
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Goal_Fireworks_star = 0x1BF,

    // RP_Goal_Fireworks_yellow
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Goal_Fireworks_yellow_0 = 0x1C3,
    RP_Goal_Fireworks_yellow_1 = 0x333,

    // RP_Gorogoro_move
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_Gorogoro_move_0 = 0x481, // Scale Factor: 0.7
    RP_Gorogoro_move_1 = 0x482,

    // RP_HalfSpin
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_HalfSpin_0 = 0x133, // Translation: (0.0, 16.0, 0.0)
    RP_HalfSpin_1 = 0x134, // Translation: (0.0, 10.0, 0.0)
    RP_HalfSpin_2 = 0x135, // Scale Factor: 0.6, Translation: (0.0, 5.0, 0.0)

    // RP_Hana_Petal
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Hana_Petal = 0x35A,

    // RP_Hana_PoisonSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Hana_PoisonSplash = 0x35E,

    // RP_Hana_Pun
    // User Data: 0x00080000
    // Emitter Count: 3
    RP_Hana_Pun = 0x35B, // Scale Factor: 0.6, Translation: (0.0, 0.0, 100.0)

    // RP_HipDrop
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_HipDrop_0 = 0x039,
    RP_HipDrop_1 = 0x03A, // Scale Factor: 0.8
    RP_HipDrop_2 = 0x03B, // Scale Factor: 0.5
    RP_HipDrop_3 = 0x048,

    // RP_HipDropBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_HipDropBlur_0 = 0x12F,
    RP_HipDropBlur_1 = 0x130, // Scale Factor: 0.85, Translation: (0.0, -2.0, 0.0)
    RP_HipDropBlur_2 = 0x131, // Scale Factor: 0.6, Translation: (0.0, -2.0, 0.0)
    RP_HipDropBlur_3 = 0x132,

    // RP_HipDropEX
    // User Data: 0x00080000
    // Emitter Count: 4
    RP_HipDropEX_0 = 0x17A,
    RP_HipDropEX_1 = 0x17B, // Scale Factor: 0.8
    RP_HipDropEX_2 = 0x17C, // Scale Factor: 0.5
    RP_HipDropEX_3 = 0x17D,

    // RP_HipDropHit
    // User Data: 0x00200000
    // Emitter Count: 5
    RP_HipDropHit_0 = 0x017,
    RP_HipDropHit_1 = 0x018,

    // RP_HipDrop_Ice
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_HipDrop_Ice_0 = 0x0BB, // Translation: (0.0, -3.0, 0.0)
    RP_HipDrop_Ice_1 = 0x0BC, // Scale Factor: 0.8, Translation: (0.0, -2.0, 0.0)
    RP_HipDrop_Ice_2 = 0x0BD, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_HipDrop_Ice_3 = 0x0BE, // Translation: (0.0, -3.0, 0.0)

    // RP_HipDrop_Normal
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_HipDrop_Normal_0 = 0x03C,
    RP_HipDrop_Normal_1 = 0x03D, // Scale Factor: 0.8
    RP_HipDrop_Normal_2 = 0x03E, // Scale Factor: 0.5
    RP_HipDrop_Normal_3 = 0x049,

    // RP_HipDrop_PillarWtr
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_HipDrop_PillarWtr_0 = 0x0D4, // Translation: (0.0, -3.0, 0.0)
    RP_HipDrop_PillarWtr_1 = 0x0D5, // Scale Factor: 0.8, Translation: (0.0, -2.0, 0.0)
    RP_HipDrop_PillarWtr_2 = 0x0D6, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_HipDrop_PillarWtr_3 = 0x0D7, // Translation: (0.0, -3.0, 0.0)

    // RP_HipDrop_Sand
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_HipDrop_Sand_0 = 0x089,
    RP_HipDrop_Sand_1 = 0x08A, // Scale Factor: 0.8
    RP_HipDrop_Sand_2 = 0x08B, // Scale Factor: 0.5
    RP_HipDrop_Sand_3 = 0x08C,

    // RP_HipDrop_Snow
    // User Data: 0x00080000
    // Emitter Count: 3
    RP_HipDrop_Snow_0 = 0x0A2,
    RP_HipDrop_Snow_1 = 0x0A3, // Scale Factor: 0.8
    RP_HipDrop_Snow_2 = 0x0A4, // Scale Factor: 0.5
    RP_HipDrop_Snow_3 = 0x0A5,

    // RP_HoneCoaster_PoisonSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_HoneCoaster_PoisonSplash = 0x396,

    // RP_Huhu_body
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Huhu_body = 0x2B5,

    // RP_Huhu_BreathIn
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Huhu_BreathIn = 0x2B3,

    // RP_Huhu_BreathOut
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Huhu_BreathOut = 0x2B4,

    // RP_Huhu_dead01
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Huhu_dead01 = 0x2B6,

    // RP_Huhu_dead02
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Huhu_dead02 = 0x2B7,

    // RP_icecoin_melt
    // User Data: 0x00200000
    // Emitter Count: 1
    RP_icecoin_melt = 0x3A4,

    // RP_ice_A1_app
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A1_app_0 = 0x1C4,
    RP_ice_A1_app_1 = 0x1C5,
    RP_ice_A1_app_2 = 0x1C6,

    // RP_ice_A1_app_wtr
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A1_app_wtr_0 = 0x1CA,
    RP_ice_A1_app_wtr_1 = 0x1CB,
    RP_ice_A1_app_wtr_2 = 0x1CC,

    // RP_ice_A1_break
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_ice_A1_break_0 = 0x1DC,
    RP_ice_A1_break_1 = 0x1DD,
    RP_ice_A1_break_2 = 0x1DE,

    // RP_ice_A1_break_wtr
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A1_break_wtr_0 = 0x1E2,
    RP_ice_A1_break_wtr_1 = 0x1E3,
    RP_ice_A1_break_wtr_2 = 0x1E4,

    // RP_ice_A1_wait
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A1_wait_0 = 0x1D0,
    RP_ice_A1_wait_1 = 0x1D1,
    RP_ice_A1_wait_2 = 0x1D2,

    // RP_ice_A1_wait_wtr
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ice_A1_wait_wtr_0 = 0x1D6,
    RP_ice_A1_wait_wtr_1 = 0x1D7,
    RP_ice_A1_wait_wtr_2 = 0x1D8,

    // RP_ice_A2_app
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A2_app_0 = 0x1C7,
    RP_ice_A2_app_1 = 0x1C8,
    RP_ice_A2_app_2 = 0x1C9,

    // RP_ice_A2_app_wtr
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_ice_A2_app_wtr_0 = 0x1CD,
    RP_ice_A2_app_wtr_1 = 0x1CE,
    RP_ice_A2_app_wtr_2 = 0x1CF,

    // RP_ice_A2_break
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_ice_A2_break_0 = 0x1DF,
    RP_ice_A2_break_1 = 0x1E0,
    RP_ice_A2_break_2 = 0x1E1,

    // RP_ice_A2_break_wtr
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A2_break_wtr_0 = 0x1E5,
    RP_ice_A2_break_wtr_1 = 0x1E6,
    RP_ice_A2_break_wtr_2 = 0x1E7,

    // RP_ice_A2_wait
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ice_A2_wait_0 = 0x1D3,
    RP_ice_A2_wait_1 = 0x1D4,
    RP_ice_A2_wait_2 = 0x1D5,

    // RP_ice_A2_wait_wtr
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ice_A2_wait_wtr_0 = 0x1D9,
    RP_ice_A2_wait_wtr_1 = 0x1DA,
    RP_ice_A2_wait_wtr_2 = 0x1DB,

    // RP_ice_EnemyDead_wtr
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_ice_EnemyDead_wtr = 0x38D,

    // RP_Iggy_Magic_core
    // User Data: 0x00000000
    // Emitter Count: 9
    RP_Iggy_Magic_core = 0x3FD, // Scale Factor: 0.85

    // RP_Iggy_Magic_core2
    // User Data: 0x00000000
    // Emitter Count: 12
    RP_Iggy_Magic_core2 = 0x3FE, // Scale Factor: 0.85

    // RP_Iggy_Magic_hit
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_Iggy_Magic_hit_0 = 0x3FF,
    RP_Iggy_Magic_hit_1 = 0x458, // Scale Factor: 0.7

    // RP_Iggy_Magic_hit2
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_Iggy_Magic_hit2_0 = 0x400,
    RP_Iggy_Magic_hit2_1 = 0x459, // Scale Factor: 0.7

    // RP_Iggy_Magic_st
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Iggy_Magic_st = 0x3FC,

    // RP_Iggy_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Iggy_ShellBlur = 0x3F9,

    // RP_ItemApp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_ItemApp = 0x05A, // Translation: (0.0, 0.0, -10.0)

    // RP_ItemApp_Mask
    // User Data: 0x00400000
    // Emitter Count: 2
    RP_ItemApp_Mask = 0x05B,

    // RP_ItemGet
    // User Data: 0x40000000
    // Emitter Count: 4
    RP_ItemGet = 0x05C,

    // RP_ItemStar
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_ItemStar = 0x059,

    // RP_JrBlock_break1
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_JrBlock_break1 = 0x436,

    // RP_JrBlock_break2
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrBlock_break2 = 0x437,

    // RP_JrClown_Accele
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrClown_Accele = 0x479,

    // RP_JrClown_ArmApp
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_JrClown_ArmApp = 0x430,

    // RP_JrClown_damage_end
    // User Data: 0x40040000
    // Emitter Count: 2
    RP_JrClown_damage_end = 0x42F, // Scale Factor: 1.5

    // RP_JrClown_damage_nml
    // User Data: 0x00040000
    // Emitter Count: 6
    RP_JrClown_damage_nml = 0x42E, // Scale Factor: 1.5

    // RP_JrClown_FireflameHit
    // User Data: 0x80000000
    // Emitter Count: 5
    RP_JrClown_FireflameHit = 0x496, // Scale Factor: 2.0

    // RP_JrClown_GloveHit
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_JrClown_GloveHit = 0x431, // Translation: (1.0, 0.0, 0.0)

    // RP_JrClown_Hipdrop
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrClown_Hipdrop = 0x42A,

    // RP_JrClown_Hipdrop_landing_nml
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrClown_Hipdrop_landing_nml = 0x42B,

    // RP_JrClown_Pika
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_JrClown_Pika = 0x49B,

    // RP_JrClown_PunchHit
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrClown_PunchHit = 0x432,

    // RP_JrClown_PunchOff
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_JrClown_PunchOff = 0x433,

    // RP_JrClown_Screw
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_JrClown_Screw = 0x42D,

    // RP_JrClown_SwingHit
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_JrClown_SwingHit = 0x4BB,

    // rp_JrShip_EndExplosion
    // User Data: 0x00000000
    // Emitter Count: 10

    // rp_Jr_FireBall
    // User Data: 0x00000000
    // Emitter Count: 11
    rp_Jr_FireBall = 0x43D,

    // RP_Jr_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Jr_ShellBlur = 0x43C,

    // RP_Jugemu_Cloud
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Jugemu_Cloud = 0x159,

    // RP_Jugemu_CloudDisapp
    // User Data: 0x40040000
    // Emitter Count: 2
    RP_Jugemu_CloudDisapp = 0x15B,

    // RP_Jugemu_CloudRideOn
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Jugemu_CloudRideOn = 0x15A,

    // RP_KameckBlock_App
    // User Data: 0x40000000
    // Emitter Count: 1
    RP_KameckBlock_App = 0x429,

    // RP_KameckIce_App
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_KameckIce_App = 0x41E,

    // RP_KameckIce_Break
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_KameckIce_Break = 0x41F,

    // RP_KameckIce_DisApp
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_KameckIce_DisApp = 0x420,

    // RP_Kameck_App
    // User Data: 0x00040000
    // Emitter Count: 2
    RP_Kameck_App = 0x068,

    // RP_Kameck_AppSign
    // User Data: 0x00040000
    // Emitter Count: 1
    RP_Kameck_AppSign = 0x069,

    // RP_Kameck_DisApp
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_Kameck_DisApp = 0x421,

    // RP_Kameck_Magic
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Kameck_Magic = 0x321,

    // RP_Kameck_Magic2_st
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_Kameck_Magic2_st = 0x422,

    // RP_Kameck_Magic_core
    // User Data: 0x00000000
    // Emitter Count: 9
    RP_Kameck_Magic_core = 0x424,

    // RP_Kameck_Magic_hit
    // User Data: 0x00000000
    // Emitter Count: 8
    RP_Kameck_Magic_hit_0 = 0x425,
    RP_Kameck_Magic_hit_1 = 0x45B, // Scale Factor: 0.7

    // RP_Kameck_Magic_st
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Kameck_Magic_st = 0x423,

    // RP_Kanibo_RockBreak
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Kanibo_RockBreak = 0x2C4,

    // RP_Karon_EyeFlash
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Karon_EyeFlash = 0x2C9,

    // RP_KickHit
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_KickHit_0 = 0x016,
    RP_KickHit_1 = 0x294,

    // RP_KillerKing_FlySmoke
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_KillerKing_FlySmoke = 0x230,

    // RP_KillerMag_FlySmoke
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_KillerMag_FlySmoke = 0x22A,

    // RP_KillerMag_Search
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_KillerMag_Search = 0x22B,

    // RP_KillerMag_Shoot
    // User Data: 0x40000000
    // Emitter Count: 4
    RP_KillerMag_Shoot = 0x229,

    // RP_Killer_Collision
    // User Data: 0x00040000
    // Emitter Count: 3
    RP_Killer_Collision_0 = 0x220,
    RP_Killer_Collision_1 = 0x224,

    // RP_Killer_FlySmoke
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Killer_FlySmoke = 0x21F,

    // RP_Killer_Search
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Killer_Search = 0x225,

    // RP_Killer_Shoot
    // User Data: 0x40000000
    // Emitter Count: 4
    RP_Killer_Shoot_0 = 0x21E,
    RP_Killer_Shoot_1 = 0x232,
    RP_Killer_Shoot_2 = 0x233, // Scale Factor: 1.5

    // RP_KK_Shiko
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_KK_Shiko = 0x3C7,

    // RP_KoopaAshiba_Cut
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_KoopaAshiba_Cut = 0x478,

    // rp_KoopaL_Fire1
    // User Data: 0x00000000
    // Emitter Count: 10
    rp_KoopaL_Fire1 = 0x44B,

    // rp_KoopaL_Fire3
    // User Data: 0x00000000
    // Emitter Count: 10
    rp_KoopaL_Fire3 = 0x44C,

    // rp_KoopaL_Landing
    // User Data: 0x00080000
    // Emitter Count: 2
    rp_KoopaL_Landing = 0x449,

    // rp_KoopaL_OpRoar
    // User Data: 0x00000000
    // Emitter Count: 10
    rp_KoopaL_OpRoar = 0x44A,

    // rp_KoopaL_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 3
    rp_KoopaL_ShellBlur = 0x450,

    // rp_KoopaL_Stamp
    // User Data: 0x00000000
    // Emitter Count: 4
    rp_KoopaL_Stamp = 0x44D,

    // rp_Koopa_EndMagicGlow
    // User Data: 0x00000000
    // Emitter Count: 3
    rp_Koopa_EndMagicGlow = 0x447,

    // rp_Koopa_Fire1
    // User Data: 0x00000000
    // Emitter Count: 9
    rp_Koopa_Fire1 = 0x443,

    // rp_Koopa_Fire2
    // User Data: 0x00000000
    // Emitter Count: 9
    rp_Koopa_Fire2 = 0x444,

    // rp_Koopa_FireBall
    // User Data: 0x00000000
    // Emitter Count: 11
    rp_Koopa_FireBall = 0x243,

    // rp_Koopa_FireBallHit
    // User Data: 0x80000000
    // Emitter Count: 6
    rp_Koopa_FireBallHit_0 = 0x3BD,
    rp_Koopa_FireBallHit_1 = 0x43E,
    rp_Koopa_FireBallHit_2 = 0x446, // Scale Factor: 0.5

    // rp_Koopa_FireBallHit2
    // User Data: 0x80000000
    // Emitter Count: 5
    rp_Koopa_FireBallHit2_0 = 0x3BF,
    rp_Koopa_FireBallHit2_1 = 0x49D, // Scale Factor: 0.5

    // rp_Koopa_FireFlame
    // User Data: 0x00000000
    // Emitter Count: 9
    rp_Koopa_FireFlame_0 = 0x244,
    rp_Koopa_FireFlame_1 = 0x258,

    // rp_Koopa_FireFlame2
    // User Data: 0x00000000
    // Emitter Count: 6
    rp_Koopa_FireFlame2_0 = 0x250,
    rp_Koopa_FireFlame2_1 = 0x259,

    // rp_Koopa_Landing
    // User Data: 0x00080000
    // Emitter Count: 2
    rp_Koopa_Landing = 0x441,

    // rp_Koopa_OpRoar
    // User Data: 0x00000000
    // Emitter Count: 10
    rp_Koopa_OpRoar = 0x442,

    // rp_Koopa_Roar
    // User Data: 0x00000000
    // Emitter Count: 9
    rp_Koopa_Roar = 0x445,

    // rp_Koopa_Swing
    // User Data: 0x00000000
    // Emitter Count: 5
    rp_Koopa_Swing = 0x24F,

    // rp_Koopa_Walk
    // User Data: 0x00000000
    // Emitter Count: 1
    rp_Koopa_Walk = 0x448, // Scale Factor: 0.9

    // RP_Koton_Blur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Koton_Blur = 0x172,

    // RP_Koton_Landing
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Koton_Landing = 0x171,

    // RP_KPElec_Elec
    // User Data: 0x00040000
    // Emitter Count: 6
    RP_KPElec_Elec = 0x175,

    // RP_KPElec_ElecLine
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_KPElec_ElecLine = 0x174,

    // RP_Kuribo_BurnSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Kuribo_BurnSmoke = 0x11A,

    // RP_Kuribo_IgaFire
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Kuribo_IgaFire = 0x119,

    // RP_Kuribo_Split
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Kuribo_Split_0 = 0x115, // Translation: (0.0, 16.0, 0.0)
    RP_Kuribo_Split_1 = 0x118, // Scale Factor: 0.7, Translation: (0.0, 8.0, 0.0)

    // RP_Larry_Magic_core
    // User Data: 0x00000000
    // Emitter Count: 9
    RP_Larry_Magic_core = 0x302, // Scale Factor: 0.85

    // RP_Larry_Magic_hit
    // User Data: 0x00000000
    // Emitter Count: 7
    RP_Larry_Magic_hit_0 = 0x303,
    RP_Larry_Magic_hit_1 = 0x457, // Scale Factor: 0.7

    // RP_Larry_Magic_st
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Larry_Magic_st = 0x301,

    // RP_Larry_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Larry_ShellBlur = 0x2FE,

    // RP_Lemmy_BallApp
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Lemmy_BallApp = 0x100,

    // RP_Lemmy_BallBound
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Lemmy_BallBound = 0x101,

    // RP_Lemmy_BallSlip
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Lemmy_BallSlip = 0x0FF, // Scale Factor: 0.8, Translation: (0.0, 0.0, -10000.0)

    // RP_Lemmy_BallSlipSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Lemmy_BallSlipSmoke = 0x0FE,

    // RP_Lemmy_BombApp
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Lemmy_BombApp = 0x13D,

    // RP_Lemmy_BombDisapp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Lemmy_BombDisapp_0 = 0x0F6, // Scale Factor: 2.0
    RP_Lemmy_BombDisapp_1 = 0x4BA, // Scale Factor: 3.0

    // RP_Lemmy_BombExp
    // User Data: 0x00000000
    // Emitter Count: 10
    RP_Lemmy_BombExp_0 = 0x010, // Scale Factor: 1.25
    RP_Lemmy_BombExp_1 = 0x4B7, // Scale Factor: 1.5

    // RP_Lemmy_BombIgnite
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_Lemmy_BombIgnite_0 = 0x0F4, // Scale Factor: 2.0
    RP_Lemmy_BombIgnite_1 = 0x4B8, // Scale Factor: 3.0

    // RP_Lemmy_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Lemmy_ShellBlur = 0x0FB,

    // RP_LiftKoopa_LavaSplash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_LiftKoopa_LavaSplash = 0x4C5,

    // RP_LiftTenbin_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_LiftTenbin_WaterSplash = 0x4D0,

    // RP_Ludwig_Disapp
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Ludwig_Disapp = 0x41C, // Translation: (0.0, 10.0, 0.0)

    // RP_Ludwig_Magic_core
    // User Data: 0x00000000
    // Emitter Count: 10
    RP_Ludwig_Magic_core = 0x417,

    // RP_Ludwig_Magic_hit
    // User Data: 0x00000000
    // Emitter Count: 8
    RP_Ludwig_Magic_hit_0 = 0x418,
    RP_Ludwig_Magic_hit_1 = 0x45A, // Scale Factor: 0.7

    // RP_Ludwig_Magic_st
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Ludwig_Magic_st = 0x416,

    // RP_Ludwig_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Ludwig_ShellBlur = 0x413, // Scale Factor: 1.2

    // RP_Ludwig_SplitBlur
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Ludwig_SplitBlur = 0x41B, // Scale Factor: 1.6

    // RP_Ludwig_SplitCharge
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Ludwig_SplitCharge = 0x419, // Translation: (0.0, 18.0, 0.0)

    // RP_Ludwig_SplitSt
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Ludwig_SplitSt = 0x41A, // Scale Factor: 1.2, Translation: (0.0, 18.0, 0.0)

    // RP_MagicHand_Gu
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_MagicHand_Gu = 0x3A7,

    // RP_MagicHand_Gu_Landing
    // User Data: 0x00080000
    // Emitter Count: 4
    RP_MagicHand_Gu_Landing_0 = 0x3A6,
    RP_MagicHand_Gu_Landing_1 = 0x45E, // Scale Factor: 1.5

    // RP_MagicHand_Pa_Landing
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_MagicHand_Pa_Landing = 0x3A5,

    // RP_MarinSnow_inWtr
    // User Data: 0x20000000
    // Emitter Count: 2
    RP_MarinSnow_inWtr = 0x2F0,

    // RP_Mario_ElecShock
    // User Data: 0x00040000
    // Emitter Count: 5
    RP_Mario_ElecShock_0 = 0x275, // Scale Factor: 1.1
    RP_Mario_ElecShock_1 = 0x276, // Scale Factor: 0.9
    RP_Mario_ElecShock_2 = 0x277, // Scale Factor: 0.9

    // RP_Mario_Firejump_Smoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Mario_Firejump_Smoke_0 = 0x38E,
    RP_Mario_Firejump_Smoke_1 = 0x38F, // Scale Factor: 0.8
    RP_Mario_Firejump_Smoke_2 = 0x390, // Scale Factor: 0.5

    // RP_Mario_Shock
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Mario_Shock_0 = 0x289,
    RP_Mario_Shock_1 = 0x28A, // Scale Factor: 0.8
    RP_Mario_Shock_2 = 0x28B, // Scale Factor: 0.8

    // RP_Mario_Star
    // User Data: 0x00800000
    // Emitter Count: 4
    RP_Mario_Star_0 = 0x00A, // Translation: (0.0, 15.0, 0.0)
    RP_Mario_Star_1 = 0x00B, // Scale Factor: 0.8, Translation: (0.0, 10.0, 0.0)
    RP_Mario_Star_2 = 0x00C, // Scale Factor: 0.5, Translation: (0.0, 6.0, 0.0)
    RP_Mario_Star_3 = 0x460, // Scale Factor: 0.8, Translation: (0.0, 5.0, 0.0)

    // RP_MechaPuku_Screw
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_MechaPuku_Screw = 0x47F,

    // RP_MetHone_EyeFlash
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_MetHone_EyeFlash = 0x2D4,

    // RP_Met_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Met_ShellBlur_0 = 0x2D2, // Translation: (0.0, 7.6, 0.0)
    RP_Met_ShellBlur_1 = 0x2D3, // Scale Factor: -1.0, Translation: (0.0, 7.6, 0.0)
    RP_Met_ShellBlur_2 = 0x454, // Scale Factor: 2.0, Translation: (0.0, 15.2, 0.0)
    RP_Met_ShellBlur_3 = 0x455, // Scale Factor: -2.0, Translation: (0.0, 15.2, 0.0)

    // RP_MiddleFlag
    // User Data: 0x00040000
    // Emitter Count: 2
    RP_MiddleFlag = 0x066,

    // RP_MiddleFlag_Change
    // User Data: 0x00040000
    // Emitter Count: 4
    RP_MiddleFlag_Change = 0x067,

    // RP_MiniG_CannonFire
    // User Data: 0x40000000
    // Emitter Count: 5
    RP_MiniG_CannonFire = 0x104,

    // RP_MiniG_PanelGetFail
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_MiniG_PanelGetFail_0 = 0x108, // Scale Factor: 1.5
    RP_MiniG_PanelGetFail_1 = 0x109, // Scale Factor: 1.25

    // RP_MiniG_PanelOpne_Item
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_MiniG_PanelOpne_Item = 0x106,

    // RP_MiniG_PanelOpne_Koopa
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_MiniG_PanelOpne_Koopa = 0x107,

    // RP_Moai_Dosun
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Moai_Dosun = 0x3C3,

    // RP_Moai_SandSmoke
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Moai_SandSmoke = 0x3C2,

    // RP_Morton_DekaSanboApp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Morton_DekaSanboApp = 0x148,

    // RP_Morton_Hammer
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Morton_Hammer = 0x14B,

    // RP_Morton_HammerCharge
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Morton_HammerCharge = 0x14A,

    // RP_Morton_HammerHit
    // User Data: 0x00040000
    // Emitter Count: 7
    RP_Morton_HammerHit = 0x14C,

    // RP_Morton_LandingL
    // User Data: 0x00080000
    // Emitter Count: 7
    RP_Morton_LandingL = 0x13F,

    // RP_Morton_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Morton_ShellBlur = 0x144,

    // RP_Musa_FlyTest
    // User Data: 0x00000000
    // Emitter Count: 2

    // RP_Musa_FlyTest_off
    // User Data: 0x00000000
    // Emitter Count: 1

    // RP_Musa_Glide
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Musa_Glide = 0x19D,

    // RP_Musa_GlideUp
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Musa_GlideUp = 0x19E,

    // RP_Musa_GlideUpStart
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Musa_GlideUpStart = 0x216,

    // RP_Musa_WallCatch
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Musa_WallCatch_0 = 0x214, // Scale Factor: -1.0, Translation: (-8.0, 18.0, 0.0)
    RP_Musa_WallCatch_1 = 0x215, // Translation: (8.0, 18.0, 0.0)

    // RP_NokoLarge_ShellBlur_G
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_NokoLarge_ShellBlur_G_0 = 0x1E9, // Scale Factor: 2.0, Translation: (0.0, 15.0, 0.0)
    RP_NokoLarge_ShellBlur_G_1 = 0x1EB, // Scale Factor: -2.0, Translation: (0.0, 13.0, 0.0)

    // RP_NokoLarge_ShellBlur_R
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_NokoLarge_ShellBlur_R_0 = 0x1EA, // Scale Factor: 2.0, Translation: (0.0, 15.0, 0.0)
    RP_NokoLarge_ShellBlur_R_1 = 0x1EC, // Scale Factor: -2.0, Translation: (0.0, 13.0, 0.0)

    // RP_Noko_ShellBlur_G
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Noko_ShellBlur_G_0 = 0x06A, // Translation: (0.0, 7.6, 0.0)
    RP_Noko_ShellBlur_G_1 = 0x070, // Scale Factor: -1.0, Translation: (0.0, 7.6, 0.0)

    // RP_Noko_ShellBlur_R
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Noko_ShellBlur_R_0 = 0x06B, // Translation: (0.0, 7.6, 0.0)
    RP_Noko_ShellBlur_R_1 = 0x071, // Scale Factor: -1.0, Translation: (0.0, 7.6, 0.0)

    // RP_Noko_ShellCrash_PillarSnd
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Noko_ShellCrash_PillarSnd_0 = 0x12A, // Translation: (0.0, 8.0, 0.0)
    RP_Noko_ShellCrash_PillarSnd_1 = 0x1FB, // Translation: (0.0, 8.0, 0.0)

    // RP_Noko_ShellCrash_PillarWtr
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Noko_ShellCrash_PillarWtr_0 = 0x12B, // Translation: (0.0, 8.0, 0.0)
    RP_Noko_ShellCrash_PillarWtr_1 = 0x1FC, // Translation: (0.0, 8.0, 0.0)

    // RP_Npc_Hit
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Npc_Hit = 0x178,

    // RP_ObakeDoor_Disapp
    // User Data: 0x40000000
    // Emitter Count: 3
    RP_ObakeDoor_Disapp = 0x399,

    // RP_PakkunSead_Hatch
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_PakkunSead_Hatch = 0x164,

    // RP_Pakkun_Fireball
    // User Data: 0x80040000
    // Emitter Count: 4
    RP_Pakkun_Fireball = 0x002,

    // RP_Pakkun_FireballShoot
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Pakkun_FireballShoot = 0x153,

    // RP_Pakkun_IceballShoot
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Pakkun_IceballShoot = 0x154,

    // RP_ParmLeafNormal_l
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ParmLeafNormal_l = 0x14F,

    // RP_ParmLeafNormal_s
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ParmLeafNormal_s = 0x150,

    // RP_ParmLeafSand_l
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ParmLeafSand_l = 0x151,

    // RP_ParmLeafSand_s
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_ParmLeafSand_s = 0x152,

    // RP_PataBig_Sweat
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_PataBig_Sweat = 0x2DC,

    // RP_Penta_Sweat
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Penta_Sweat = 0x361,

    // RP_Penta_SwimSplash
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Penta_SwimSplash = 0x360, // Translation: (0.0, -8.0, 0.0)

    // RP_Pmusasabi
    // User Data: 0x00800000
    // Emitter Count: 2
    RP_Pmusasabi = 0x39F, // Translation: (0.0, 15.0, 0.0)

    // RP_Pmusasabi_Fly
    // User Data: 0x00800000
    // Emitter Count: 4
    RP_Pmusasabi_Fly = 0x3A0, // Translation: (0.0, 15.0, 0.0)

    // RP_Poltergeist_Blur
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Poltergeist_Blur = 0x39A,

    // RP_Poltergeist_Disapp
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Poltergeist_Disapp = 0x39C,

    // RP_Poltergeist_Spin
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Poltergeist_Spin = 0x39B,

    // RP_Pow
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Pow = 0x173,

    // RP_PowerUP
    // User Data: 0x00200000
    // Emitter Count: 4
    RP_PowerUP_0 = 0x05D, // Translation: (0.0, 16.0, 0.0)
    RP_PowerUP_1 = 0x05E, // Scale Factor: 0.8, Translation: (0.0, 8.0, 0.0)
    RP_PowerUP_2 = 0x05F, // Scale Factor: 0.5, Translation: (0.0, 8.0, 0.0)

    // RP_PoyoCloud_L_Ridden
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_PoyoCloud_L_Ridden = 0x49F,

    // RP_PoyoCloud_S_Ridden
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_PoyoCloud_S_Ridden = 0x4A0,

    // RP_Prop_Fall
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Prop_Fall = 0x13A,

    // RP_Prop_FallSpin
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Prop_FallSpin = 0x14D,

    // RP_Prop_Rise
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Prop_Rise = 0x139,

    // RP_Prop_SpinDrop
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Prop_SpinDrop = 0x13B,

    // RP_Puku_WaterDrop
    // User Data: 0x00200000
    // Emitter Count: 1
    RP_Puku_WaterDrop = 0x334,

    // RP_Ray_HWtr
    // User Data: 0x20000000
    // Emitter Count: 4
    RP_Ray_HWtr = 0x2F1,

    // RP_RingGet_Mask
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_RingGet_Mask = 0x058,

    // RP_RingGoalGet
    // User Data: 0xC0000000
    // Emitter Count: 2
    RP_RingGoalGet = 0x462,

    // RP_RingGreen
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_RingGreen = 0x055,

    // RP_RingGreenGet
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_RingGreenGet = 0x056,

    // RP_RingRed
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_RingRed = 0x053,

    // RP_RingRedGet
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_RingRedGet = 0x054,

    // RP_Ring_Mask
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Ring_Mask = 0x057,

    // RP_Roy_CannonShoot
    // User Data: 0x40000000
    // Emitter Count: 7
    RP_Roy_CannonShoot = 0x40C, // Scale Factor: 0.45

    // RP_Roy_LandingL
    // User Data: 0x00080000
    // Emitter Count: 5
    RP_Roy_LandingL = 0x402,

    // RP_Roy_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Roy_ShellBlur = 0x409, // Scale Factor: 1.4

    // RP_Sanbo_move_nml
    // User Data: 0x00000000
    // Emitter Count: 1

    // RP_Sanbo_move_sand
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_Sanbo_move_sand_0 = 0x3B2,
    RP_Sanbo_move_sand_1 = 0x3B3,

    // RP_Screen_FWtr_A
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_Screen_FWtr_A = 0x19B,

    // RP_Seidon_SnowBall_Break
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Seidon_SnowBall_Break = 0x36F,

    // RP_Shadowkun_brake_ice
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Shadowkun_brake_ice = 0x487,

    // RP_Shadowkun_brake_nml
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Shadowkun_brake_nml = 0x484,

    // RP_Shadowkun_brake_pw
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Shadowkun_brake_pw = 0x488,

    // RP_Shadowkun_brake_sand
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Shadowkun_brake_sand = 0x485,

    // RP_Shadowkun_brake_snow
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Shadowkun_brake_snow = 0x486,

    // RP_Shadowkun_notice
    // User Data: 0x40000000
    // Emitter Count: 2
    RP_Shadowkun_notice = 0x256,

    // RP_Shadowkun_Sweat
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_Shadowkun_Sweat = 0x255,

    // RP_Shadowkun_Sweat2
    // User Data: 0x80000000
    // Emitter Count: 2
    RP_Shadowkun_Sweat2 = 0x483,

    // RP_Spin
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Spin_0 = 0x136, // Translation: (0.0, 18.0, 0.0)
    RP_Spin_1 = 0x137, // Scale Factor: 0.8, Translation: (0.0, 9.0, 0.0)
    RP_Spin_2 = 0x138, // Scale Factor: 0.5, Translation: (0.0, 6.0, 0.0)

    // rp_swim
    // User Data: 0x00000000
    // Emitter Count: 2
    rp_swim_0 = 0x25E,
    rp_swim_1 = 0x25F, // Scale Factor: 0.8
    rp_swim_2 = 0x260, // Scale Factor: 1.2

    // rp_swimPaddle
    // User Data: 0x00000000
    // Emitter Count: 1
    rp_swimPaddle_0 = 0x261,
    rp_swimPaddle_1 = 0x262, // Scale Factor: 0.8
    rp_swimPaddle_2 = 0x263, // Scale Factor: 1.2

    // RP_Switch_Hatena_On
    // User Data: 0x00040000
    // Emitter Count: 1
    RP_Switch_Hatena_On = 0x181,

    // RP_Switch_Koopa_On
    // User Data: 0x00040000
    // Emitter Count: 5
    RP_Switch_Koopa_On = 0x3BE,

    // RP_Switch_P_On
    // User Data: 0x00040000
    // Emitter Count: 1
    RP_Switch_P_On = 0x180,

    // RP_Taru_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Taru_Break = 0x397,

    // RP_Teresa_Disapp
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Teresa_Disapp = 0x177,

    // RP_Teresa_Glow
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Teresa_Glow = 0x176,

    // RP_Teresa_Sweat
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Teresa_Sweat = 0x2C5,

    // RP_Teresa_SweatL
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Teresa_SweatL = 0x2C6,

    // RP_Torpedo_Exp
    // User Data: 0x40000000
    // Emitter Count: 12
    RP_Torpedo_Exp_0 = 0x00F, // Scale Factor: 1.3
    RP_Torpedo_Exp_1 = 0x223,

    // RP_Torpedo_Screw
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Torpedo_Screw = 0x222,

    // RP_TsuraraBig_Landing
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_TsuraraBig_Landing = 0x3A3, // Translation: (0.0, 0.0, 100.0)

    // RP_Tsurara_Break
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Tsurara_Break_0 = 0x3A1, // Translation: (0.0, -10.0, 0.0)
    RP_Tsurara_Break_1 = 0x3A2, // Scale Factor: 0.7, Translation: (0.0, -5.0, 0.0)
    RP_Tsurara_Break_2 = 0x3ED, // Translation: (0.0, -10.0, 0.0)

    // RP_TurnBrake
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_TurnBrake_0 = 0x03F, // Translation: (0.0, -3.0, 0.0)
    RP_TurnBrake_1 = 0x040, // Scale Factor: 0.8, Translation: (0.0, -2.0, 0.0)
    RP_TurnBrake_2 = 0x041, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_TurnBrake_3 = 0x04A, // Translation: (0.0, -5.0, 0.0)

    // RP_TurnBrakeIce
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_TurnBrakeIce_0 = 0x0B3, // Translation: (0.0, -5.0, 0.0)
    RP_TurnBrakeIce_1 = 0x0B4, // Scale Factor: 0.8, Translation: (0.0, -4.0, 0.0)
    RP_TurnBrakeIce_2 = 0x0B5, // Scale Factor: 0.5, Translation: (0.0, -2.5, 0.0)
    RP_TurnBrakeIce_3 = 0x0B6, // Translation: (0.0, -7.0, 0.0)

    // RP_TurnBrakePillarWtr
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_TurnBrakePillarWtr_0 = 0x0CC, // Translation: (0.0, -5.0, 0.0)
    RP_TurnBrakePillarWtr_1 = 0x0CD, // Scale Factor: 0.8, Translation: (0.0, -4.0, 0.0)
    RP_TurnBrakePillarWtr_2 = 0x0CE, // Scale Factor: 0.5, Translation: (0.0, -2.5, 0.0)
    RP_TurnBrakePillarWtr_3 = 0x0CF, // Translation: (0.0, -7.0, 0.0)

    // RP_TurnBrakeSand
    // User Data: 0x00080000
    // Emitter Count: 1
    RP_TurnBrakeSand_0 = 0x081, // Translation: (0.0, -3.0, 0.0)
    RP_TurnBrakeSand_1 = 0x082, // Scale Factor: 0.8, Translation: (0.0, -2.0, 0.0)
    RP_TurnBrakeSand_2 = 0x083, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_TurnBrakeSand_3 = 0x084, // Translation: (0.0, -5.0, 0.0)

    // RP_TurnBrakeSmoke
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_TurnBrakeSmoke_0 = 0x042,
    RP_TurnBrakeSmoke_1 = 0x043, // Scale Factor: 0.8
    RP_TurnBrakeSmoke_2 = 0x044, // Scale Factor: 0.5
    RP_TurnBrakeSmoke_3 = 0x04B, // Translation: (0.0, -3.0, 0.0)

    // RP_TurnBrakeSnow
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_TurnBrakeSnow_0 = 0x09A, // Translation: (0.0, -3.0, 0.0)
    RP_TurnBrakeSnow_1 = 0x09B, // Scale Factor: 0.8, Translation: (0.0, -2.0, 0.0)
    RP_TurnBrakeSnow_2 = 0x09C, // Scale Factor: 0.5, Translation: (0.0, -1.0, 0.0)
    RP_TurnBrakeSnow_3 = 0x09D, // Translation: (0.0, -5.0, 0.0)

    // rp_UI_BoostLine
    // User Data: 0x80000000
    // Emitter Count: 1
    rp_UI_BoostLine = 0x3D1,

    // RP_UI_BoostLine_loop
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_UI_BoostLine_loop = 0x4BE,

    // RP_UI_BoostLine_loop2
    // User Data: 0x80000000
    // Emitter Count: 1
    RP_UI_BoostLine_loop2 = 0x4C1,

    // RP_UI_Coin_GetCount
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_UI_Coin_GetCount = 0x28C,

    // RP_UI_CourseClear
    // User Data: 0x02000000
    // Emitter Count: 14
    RP_UI_CourseClear = 0x28E,

    // RP_UI_DRC_Touch
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_UI_DRC_Touch = 0x217,

    // RP_UI_DRC_Touch_Fever
    // User Data: 0x00000000
    // Emitter Count: 6
    RP_UI_DRC_Touch_Fever = 0x41D,

    // RP_UI_FeverMode
    // User Data: 0x00800000
    // Emitter Count: 8
    RP_UI_FeverMode = 0x43F,

    // RP_UI_ItemList_ItemDisapp
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_ItemList_ItemDisapp = 0x2ED,

    // RP_UI_ItemList_ItemDisapp_DRCMode
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_ItemList_ItemDisapp_DRCMode = 0x4BC,

    // RP_UI_ItemList_Landing
    // User Data: 0x10000000
    // Emitter Count: 1
    RP_UI_ItemList_Landing_0 = 0x2E2, // Scale Factor: 2.5
    RP_UI_ItemList_Landing_1 = 0x2E3, // Scale Factor: 3.0
    RP_UI_ItemList_Landing_2 = 0x2E4, // Scale Factor: 3.0
    RP_UI_ItemList_Landing_3 = 0x2E5, // Scale Factor: 2.0

    // RP_UI_ItemList_PMusa
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_ItemList_PMusa = 0x2EC, // Scale Factor: 5.0, Translation: (0.0, 80.0, 0.0)

    // RP_UI_ItemList_PowerUP
    // User Data: 0x10000000
    // Emitter Count: 5
    RP_UI_ItemList_PowerUP_0 = 0x305, // Scale Factor: 3.0, Translation: (0.0, 70.0, 0.0)
    RP_UI_ItemList_PowerUP_1 = 0x306, // Scale Factor: 3.0, Translation: (0.0, 50.0, 0.0)
    RP_UI_ItemList_PowerUP_2 = 0x307, // Scale Factor: 3.0, Translation: (0.0, 35.0, 0.0)

    // RP_UI_ItemList_Spin
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_ItemList_Spin_0 = 0x2E6, // Scale Factor: 3.0, Translation: (0.0, 20.0, 0.0)
    RP_UI_ItemList_Spin_1 = 0x2E7, // Scale Factor: 2.6, Translation: (0.0, 10.0, 0.0)
    RP_UI_ItemList_Spin_2 = 0x2E8, // Scale Factor: 1.8, Translation: (0.0, 5.0, 0.0)

    // RP_UI_ItemList_Star
    // User Data: 0x10000000
    // Emitter Count: 4
    RP_UI_ItemList_Star_0 = 0x2E9, // Scale Factor: 5.0, Translation: (0.0, 80.0, 0.0)
    RP_UI_ItemList_Star_1 = 0x2EA, // Scale Factor: 4.0, Translation: (0.0, 50.0, 0.0)
    RP_UI_ItemList_Star_2 = 0x2EB, // Scale Factor: 2.0, Translation: (0.0, 30.0, 0.0)

    // RP_UI_LandingSmoke
    // User Data: 0x90000000
    // Emitter Count: 1
    RP_UI_LandingSmoke_0 = 0x308,
    RP_UI_LandingSmoke_1 = 0x309, // Scale Factor: 0.8
    RP_UI_LandingSmoke_2 = 0x30A,

    // RP_UI_Player_1up
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_UI_Player_1up = 0x28D,

    // RP_UI_Player_PMusa
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_Player_PMusa = 0x311, // Translation: (0.0, 15.0, 0.0)

    // RP_UI_Player_Star
    // User Data: 0x10000000
    // Emitter Count: 4
    RP_UI_Player_Star_0 = 0x30E, // Translation: (0.0, 15.0, 0.0)
    RP_UI_Player_Star_1 = 0x30F, // Scale Factor: 0.8, Translation: (0.0, 10.0, 0.0)
    RP_UI_Player_Star_2 = 0x310, // Scale Factor: 0.75, Translation: (0.0, 15.0, 0.0)

    // RP_UI_Spin
    // User Data: 0x10000000
    // Emitter Count: 2
    RP_UI_Spin_0 = 0x30B, // Scale Factor: 0.9, Translation: (0.0, 18.0, 0.0)
    RP_UI_Spin_1 = 0x30C, // Scale Factor: 0.8, Translation: (0.0, 9.0, 0.0)
    RP_UI_Spin_2 = 0x30D, // Scale Factor: 0.7, Translation: (0.0, 6.0, 0.0)

    // RP_Unabon_bubble
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Unabon_bubble = 0x47E,

    // RP_Unabon_bubble_loop
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Unabon_bubble_loop = 0x49C,

    // RP_Unizo_Big_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Unizo_Big_WaterSplash = 0x3C1,

    // RP_Unizo_WaterSplash
    // User Data: 0x00200000
    // Emitter Count: 2
    RP_Unizo_WaterSplash = 0x3C0,

    // RP_WallKick
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WallKick_0 = 0x02A,
    RP_WallKick_1 = 0x02B, // Scale Factor: 0.8
    RP_WallKick_2 = 0x02C, // Scale Factor: 0.5

    // RP_Wanwan_Bite
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Wanwan_Bite = 0x364,

    // RP_WaterPakkun_BreathBall
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_WaterPakkun_BreathBall = 0x157,

    // RP_WaterPakkun_BreathMax
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_WaterPakkun_BreathMax = 0x155,

    // RP_WaterPakkun_BreathMin
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_WaterPakkun_BreathMin = 0x156,

    // RP_WaterPakkun_Sweat
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_WaterPakkun_Sweat = 0x158,

    // RP_Wendy_JumpSt
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_Wendy_JumpSt = 0x317,

    // RP_Wendy_LandingIce
    // User Data: 0x80000000
    // Emitter Count: 3
    RP_Wendy_LandingIce = 0x314,

    // RP_Wendy_OpSpin
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Wendy_OpSpin = 0x313,

    // RP_Wendy_Ring
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Wendy_Ring = 0x319,

    // RP_Wendy_RingHit
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Wendy_RingHit = 0x31A,

    // RP_Wendy_ShellBlur
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Wendy_ShellBlur = 0x31E,

    // RP_Wendy_SkatingKick
    // User Data: 0x80000000
    // Emitter Count: 4
    RP_Wendy_SkatingKick = 0x316,

    // RP_Wendy_SpinJump
    // User Data: 0x00000000
    // Emitter Count: 5
    RP_Wendy_SpinJump = 0x318,

    // RP_Wendy_SpinJump_W
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_Wendy_SpinJump_W = 0x3EE,

    // RP_WireHit
    // User Data: 0x00200000
    // Emitter Count: 3
    RP_WireHit = 0x2F4, // Scale Factor: 0.7

    // RP_Woochan_MoveSplash
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Woochan_MoveSplash = 0x371,

    // RP_Woochan_SinkSplash
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Woochan_SinkSplash = 0x370,

    // RP_WoodBox_blue2x2_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_blue2x2_Break = 0x3B9,

    // RP_WoodBox_blue2x4_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_blue2x4_Break = 0x3BA,

    // RP_WoodBox_blue4x2_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_blue4x2_Break = 0x3BB,

    // RP_WoodBox_blue4x4_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_blue4x4_Break = 0x3BC,

    // RP_WoodBox_nml2x2_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_nml2x2_Break = 0x3B5,

    // RP_WoodBox_nml2x4_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_nml2x4_Break = 0x3B6,

    // RP_WoodBox_nml4x2_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_nml4x2_Break = 0x3B7,

    // RP_WoodBox_nml4x4_Break
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_WoodBox_nml4x4_Break = 0x3B8,

    // RP_Woogan_AppSplash
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Woogan_AppSplash = 0x3F1,

    // RP_Woogan_Disapp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Woogan_Disapp = 0x48C,

    // RP_Woogan_MoveSplash
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Woogan_MoveSplash = 0x3F2,

    // RP_Woogan_RecallSplash
    // User Data: 0x00000000
    // Emitter Count: 4
    RP_Woogan_RecallSplash = 0x3F0,

    // RP_WtrCurrent_L4unit
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_WtrCurrent_L4unit = 0x199,

    // RP_WtrCurrent_M1unit
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_WtrCurrent_M1unit = 0x197,

    // RP_WtrCurrent_M4unit
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_WtrCurrent_M4unit = 0x198,

    // RP_WtrCurrent_R4unit
    // User Data: 0x20000000
    // Emitter Count: 3
    RP_WtrCurrent_R4unit = 0x19A,

    // RP_YoshiChibi_BlowUp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_YoshiChibi_BlowUp = 0x461,

    // RP_YoshiChibi_Flash
    // User Data: 0x00000000
    // Emitter Count: 2
    RP_YoshiChibi_Flash = 0x2F3,

    // RP_YoshiChibi_Sweat_Escape
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_YoshiChibi_Sweat_Escape = 0x2F2,

    // RP_Yoshi_Fireball
    // User Data: 0x80200000
    // Emitter Count: 4
    RP_Yoshi_Fireball = 0x001,

    // RP_Yoshi_Iceball
    // User Data: 0x80200000
    // Emitter Count: 2

    // RP_Yoshi_Stamp
    // User Data: 0x00000000
    // Emitter Count: 3
    RP_Yoshi_Stamp = 0x1AF,

    // RP_Yoshi_Sweat_Escape
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Yoshi_Sweat_Escape = 0x1A6,

    // RP_Yoshi_Sweat_Jump
    // User Data: 0x00000000
    // Emitter Count: 1
    RP_Yoshi_Sweat_Jump = 0x1AC,

    // RP_Yoshi_TongueGet
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Yoshi_TongueGet = 0x1AE,

    // RP_Yoshi_TongueHit
    // User Data: 0x00080000
    // Emitter Count: 2
    RP_Yoshi_TongueHit = 0x1AD,

    // Wm_en_keronpafire
    // User Data: 0x80040000
    // Emitter Count: 4
    Wm_en_keronpafire = 0x012,

    // Wm_en_keronpalight
    // User Data: 0x00040000
    // Emitter Count: 1
    Wm_en_keronpalight = 0x013,

    // Wm_en_keronpaTail
    // User Data: 0x80040000
    // Emitter Count: 3
    Wm_en_keronpaTail = 0x011,

    // Wm_mr_hardhit
    // User Data: 0x00200000
    // Emitter Count: 4

    // Wm_mr_softhit
    // User Data: 0x00200000
    // Emitter Count: 4

    // Wm_ob_sandpillar
    // User Data: 0x00200000
    // Emitter Count: 2
    Wm_ob_sandpillar = 0x019,

    // Wm_ob_spillarsign
    // User Data: 0x00200000
    // Emitter Count: 3
    Wm_ob_spillarsign = 0x01A,

    // Wm_ob_waterpillar
    // User Data: 0x00200000
    // Emitter Count: 1
    Wm_ob_waterpillar = 0x01B,

    // Wm_ob_wpillarout
    // User Data: 0x00200000
    // Emitter Count: 1
    Wm_ob_wpillarout = 0x01C,

    // Wm_ob_wpillarsign
    // User Data: 0x00200000
    // Emitter Count: 3
    Wm_ob_wpillarsign = 0x01D,

    cEffectID_None = 0xFFFFFFFF,
    cEffectID_Num = 0x4D2,
};
