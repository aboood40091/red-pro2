#include <actor/Profile.h>

s16 Profile::getDrawPriority(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return -1;

    return cDrawPriority[id];
}

Profile::ResType Profile::getResType(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return cResType_Boot;

    return ResType(cResType[id]);
}

u32 Profile::getResNum(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return 0;

    return cResNum[id];
}

const sead::SafeString* Profile::getResList(s32 id)
{
    if (static_cast<u32>(id) >= cProfileID_Max)
        return nullptr;

    return cResList[id];
}

// --------------------------------------- DrawPriority --------------------------------------- //

const s16 Profile::cDrawPriority[cProfileID_Max] = {
     17 - 0x3ff,    // ProfileID::c000
     18 - 0x3ff,    // ProfileID::c001
     19 - 0x3ff,    // ProfileID::c002
     20 - 0x3ff,    // ProfileID::c003
     21 - 0x3ff,    // ProfileID::c004
     22 - 0x3ff,    // ProfileID::c005
     23 - 0x3ff,    // ProfileID::c006
     24 - 0x3ff,    // ProfileID::c007
     25 - 0x3ff,    // ProfileID::c008
     26 - 0x3ff,    // ProfileID::c009
     71 - 0x3ff,    // ProfileID::c00A
     27 - 0x3ff,    // ProfileID::c00B
     28 - 0x3ff,    // ProfileID::c00C
     29 - 0x3ff,    // ProfileID::c00D
     51 - 0x3ff,    // ProfileID::c00E
     52 - 0x3ff,    // ProfileID::c00F
     53 - 0x3ff,    // ProfileID::c010
     65 - 0x3ff,    // ProfileID::c011
     66 - 0x3ff,    // ProfileID::c012
     92 - 0x3ff,    // ProfileID::c013
     72 - 0x3ff,    // ProfileID::c014
     75 - 0x3ff,    // ProfileID::c015
     76 - 0x3ff,    // ProfileID::c016
     77 - 0x3ff,    // ProfileID::c017
     78 - 0x3ff,    // ProfileID::cMiniGameMgr
     79 - 0x3ff,    // ProfileID::cMiniGameMgrRDash
     80 - 0x3ff,    // ProfileID::cShuffleBlockMgr
     81 - 0x3ff,    // ProfileID::cSlotMgr
     82 - 0x3ff,    // ProfileID::cCoinmakiMgr
     86 - 0x3ff,    // ProfileID::c01D
     87 - 0x3ff,    // ProfileID::c01E
     88 - 0x3ff,    // ProfileID::c01F
     91 - 0x3ff,    // ProfileID::c020
     95 - 0x3ff,    // ProfileID::cShootingStar
    727,            // ProfileID::cStaffRollMgr
    728,            // ProfileID::cStaffRollMgrRDash
    105 - 0x3ff,    // ProfileID::c024
    689,            // ProfileID::c025
     41 - 0x3ff,    // ProfileID::c026
     30 - 0x3ff,    // ProfileID::c027
     31 - 0x3ff,    // ProfileID::c028
     32 - 0x3ff,    // ProfileID::c029
     33 - 0x3ff,    // ProfileID::c02A
    308,            // ProfileID::c02B
    309,            // ProfileID::c02C
     49 - 0x3ff,    // ProfileID::c02D
     50 - 0x3ff,    // ProfileID::c02E
     67 - 0x3ff,    // ProfileID::c02F
     68 - 0x3ff,    // ProfileID::c030
     73 - 0x3ff,    // ProfileID::c031
    416,            // ProfileID::c032
    218,            // ProfileID::c033
    533,            // ProfileID::c034
    613,            // ProfileID::c035
    267,            // ProfileID::c036
    268,            // ProfileID::c037
    269,            // ProfileID::c038
    270,            // ProfileID::c039
    271,            // ProfileID::c03A
    272,            // ProfileID::c03B
    273,            // ProfileID::c03C
    274,            // ProfileID::c03D
    275,            // ProfileID::c03E
    276,            // ProfileID::c03F
    277,            // ProfileID::c040
    278,            // ProfileID::c041
    279,            // ProfileID::c042
    280,            // ProfileID::c043
    281,            // ProfileID::c044
    282,            // ProfileID::c045
    283,            // ProfileID::c046
    284,            // ProfileID::c047
    285,            // ProfileID::c048
    286,            // ProfileID::c049
    287,            // ProfileID::c04A
    288,            // ProfileID::c04B
    289,            // ProfileID::c04C
    215,            // ProfileID::c04D
    216,            // ProfileID::c04E
    217,            // ProfileID::c04F
    224,            // ProfileID::c050
    226,            // ProfileID::c051
    435,            // ProfileID::c052
    436,            // ProfileID::c053
    697,            // ProfileID::c054
    698,            // ProfileID::c055
    699,            // ProfileID::c056
    700,            // ProfileID::c057
    701,            // ProfileID::c058
    702,            // ProfileID::c059
    703,            // ProfileID::c05A
    704,            // ProfileID::c05B
     80,            // ProfileID::c05C
     81,            // ProfileID::c05D
     82,            // ProfileID::c05E
     72,            // ProfileID::c05F
     73,            // ProfileID::c060
     74,            // ProfileID::c061
     78,            // ProfileID::c062
     79,            // ProfileID::c063
     83,            // ProfileID::c064
    440,            // ProfileID::c065
    441,            // ProfileID::c066
    442,            // ProfileID::c067
    443,            // ProfileID::c068
    444,            // ProfileID::c069
    445,            // ProfileID::c06A
    446,            // ProfileID::c06B
    447,            // ProfileID::c06C
    448,            // ProfileID::c06D
    449,            // ProfileID::c06E
    450,            // ProfileID::c06F
    451,            // ProfileID::c070
    452,            // ProfileID::c071
    453,            // ProfileID::c072
    454,            // ProfileID::c073
    455,            // ProfileID::c074
    457,            // ProfileID::c075
    328,            // ProfileID::c076
    329,            // ProfileID::c077
    330,            // ProfileID::c078
    496,            // ProfileID::c079
    497,            // ProfileID::c07A
    498,            // ProfileID::c07B
    499,            // ProfileID::c07C
    500,            // ProfileID::c07D
    501,            // ProfileID::c07E
    502,            // ProfileID::c07F
    503,            // ProfileID::c080
    528,            // ProfileID::c081
     56,            // ProfileID::c082
     57,            // ProfileID::c083
     58,            // ProfileID::c084
     59,            // ProfileID::c085
     63,            // ProfileID::c086
     64,            // ProfileID::c087
     65,            // ProfileID::c088
     66,            // ProfileID::c089
     67,            // ProfileID::c08A
     68,            // ProfileID::c08B
     69,            // ProfileID::c08C
     70,            // ProfileID::c08D
     71,            // ProfileID::c08E
     76,            // ProfileID::c08F
     77,            // ProfileID::c090
     84,            // ProfileID::c091
     85,            // ProfileID::c092
    529,            // ProfileID::c093
    530,            // ProfileID::c094
    531,            // ProfileID::c095
    532,            // ProfileID::c096
    266,            // ProfileID::c097
    546,            // ProfileID::c098
    547,            // ProfileID::c099
    548,            // ProfileID::c09A
    549,            // ProfileID::c09B
    550,            // ProfileID::c09C
    551,            // ProfileID::c09D
    552,            // ProfileID::c09E
    553,            // ProfileID::c09F
    560,            // ProfileID::c0A0
    554,            // ProfileID::c0A1
    555,            // ProfileID::c0A2
    556,            // ProfileID::c0A3
    557,            // ProfileID::c0A4
    558,            // ProfileID::c0A5
    559,            // ProfileID::c0A6
    561,            // ProfileID::c0A7
    562,            // ProfileID::c0A8
    563,            // ProfileID::c0A9
    564,            // ProfileID::c0AA
    565,            // ProfileID::c0AB
    566,            // ProfileID::c0AC
    219,            // ProfileID::c0AD
    220,            // ProfileID::c0AE
    221,            // ProfileID::c0AF
    222,            // ProfileID::c0B0
    223,            // ProfileID::c0B1
    514,            // ProfileID::c0B2
    517,            // ProfileID::c0B3
    520,            // ProfileID::c0B4
    521,            // ProfileID::c0B5
    522,            // ProfileID::c0B6
    523,            // ProfileID::c0B7
    524,            // ProfileID::c0B8
    525,            // ProfileID::c0B9
    526,            // ProfileID::c0BA
    569,            // ProfileID::c0BB
    527,            // ProfileID::c0BC
    568,            // ProfileID::c0BD
    567,            // ProfileID::c0BE
    336,            // ProfileID::c0BF
    337,            // ProfileID::c0C0
    338,            // ProfileID::c0C1
    482,            // ProfileID::c0C2
    483,            // ProfileID::c0C3
    484,            // ProfileID::c0C4
    437,            // ProfileID::c0C5
    438,            // ProfileID::c0C6
    488,            // ProfileID::c0C7
    485,            // ProfileID::c0C8
    617,            // ProfileID::c0C9
    618,            // ProfileID::c0CA
    534,            // ProfileID::c0CB
    535,            // ProfileID::c0CC
    620,            // ProfileID::c0CD
    621,            // ProfileID::c0CE
    622,            // ProfileID::c0CF
    615,            // ProfileID::c0D0
    616,            // ProfileID::c0D1
    614,            // ProfileID::cFloorHoleDokan
    571,            // ProfileID::c0D3
    573,            // ProfileID::c0D4
    574,            // ProfileID::c0D5
    572,            // ProfileID::c0D6
    575,            // ProfileID::c0D7
    576,            // ProfileID::c0D8
    577,            // ProfileID::c0D9
    578,            // ProfileID::c0DA
    579,            // ProfileID::c0DB
    581,            // ProfileID::c0DC
    582,            // ProfileID::c0DD
    610,            // ProfileID::c0DE
    611,            // ProfileID::c0DF
    132,            // ProfileID::c0E0
    133,            // ProfileID::c0E1
    134,            // ProfileID::c0E2
    135,            // ProfileID::c0E3
    380,            // ProfileID::c0E4
    489,            // ProfileID::c0E5
    538,            // ProfileID::c0E6
    536,            // ProfileID::c0E7
    537,            // ProfileID::c0E8
    587,            // ProfileID::c0E9
    539,            // ProfileID::c0EA
    136,            // ProfileID::c0EB
    612,            // ProfileID::c0EC
    645,            // ProfileID::c0ED
    479,            // ProfileID::c0EE
    480,            // ProfileID::c0EF
    481,            // ProfileID::c0F0
    651,            // ProfileID::c0F1
    652,            // ProfileID::c0F2
    639,            // ProfileID::c0F3
    640,            // ProfileID::c0F4
    381,            // ProfileID::c0F5
    382,            // ProfileID::c0F6
    383,            // ProfileID::c0F7
    384,            // ProfileID::c0F8
    385,            // ProfileID::c0F9
    583,            // ProfileID::c0FA
    584,            // ProfileID::c0FB
    705,            // ProfileID::c0FC
    706,            // ProfileID::c0FD
    707,            // ProfileID::c0FE
    708,            // ProfileID::c0FF
    515,            // ProfileID::c100
    516,            // ProfileID::c101
     75,            // ProfileID::c102
    580,            // ProfileID::c103
    593,            // ProfileID::c104
    712,            // ProfileID::cShuffleBlock
    673,            // ProfileID::cKokoopaShipWarpCannon
    619,            // ProfileID::c107
    685,            // ProfileID::c108
    205,            // ProfileID::cKoopaShutter
    721,            // ProfileID::c10A
    722,            // ProfileID::c10B
    723,            // ProfileID::c10C
    199,            // ProfileID::cPeachFinalCastleKoopaJrLift
    200,            // ProfileID::cPeachFinalCastleKoopaJrLiftHmove
    201,            // ProfileID::cPeachFinalCastleKoopaJrLiftPairObj
    202,            // ProfileID::cRoyLiftWakiStep
    180,            // ProfileID::cWendyFloor
    187,            // ProfileID::cIggyRoom
    291,            // ProfileID::c113
    292,            // ProfileID::c114
    293,            // ProfileID::c115
    294,            // ProfileID::c116
    490,            // ProfileID::c117
    724,            // ProfileID::c118
    683,            // ProfileID::c119
    684,            // ProfileID::c11A
     47,            // ProfileID::c11B
    111 - 0x3ff,    // ProfileID::c11C
    608,            // ProfileID::c11D
    609,            // ProfileID::c11E
    229,            // ProfileID::c11F
      1 - 0x3ff,    // ProfileID::c120
    352,            // ProfileID::c121
    353,            // ProfileID::c122
    354,            // ProfileID::c123
    355,            // ProfileID::c124
    356,            // ProfileID::c125
    357,            // ProfileID::c126
    358,            // ProfileID::c127
    359,            // ProfileID::c128
    360,            // ProfileID::c129
    361,            // ProfileID::c12A
    362,            // ProfileID::c12B
    363,            // ProfileID::c12C
    364,            // ProfileID::c12D
    365,            // ProfileID::c12E
    366,            // ProfileID::c12F
    367,            // ProfileID::c130
    368,            // ProfileID::c131
    369,            // ProfileID::c132
    370,            // ProfileID::c133
    371,            // ProfileID::c134
    374,            // ProfileID::c135
    375,            // ProfileID::c136
    376,            // ProfileID::c137
    377,            // ProfileID::c138
    386,            // ProfileID::c139
    378,            // ProfileID::c13A
    379,            // ProfileID::c13B
    387,            // ProfileID::c13C
    388,            // ProfileID::c13D
    389,            // ProfileID::c13E
    372,            // ProfileID::c13F
    373,            // ProfileID::c140
    390,            // ProfileID::c141
    391,            // ProfileID::c142
    392,            // ProfileID::c143
    647,            // ProfileID::c144
    648,            // ProfileID::c145
    649,            // ProfileID::c146
    650,            // ProfileID::c147
    680,            // ProfileID::c148
    681,            // ProfileID::c149
    682,            // ProfileID::c14A
    393,            // ProfileID::c14B
    115 - 0x3ff,    // ProfileID::c14C
     48,            // ProfileID::c14D
     49,            // ProfileID::c14E
     50,            // ProfileID::c14F
     51,            // ProfileID::c150
     52,            // ProfileID::c151
     53,            // ProfileID::c152
     54,            // ProfileID::c153
     55,            // ProfileID::c154
     60,            // ProfileID::c155
     61,            // ProfileID::c156
     62,            // ProfileID::c157
    466,            // ProfileID::c158
    467,            // ProfileID::c159
    468,            // ProfileID::c15A
    469,            // ProfileID::c15B
    470,            // ProfileID::c15C
    471,            // ProfileID::c15D
    598,            // ProfileID::c15E
    173,            // ProfileID::cLemmyBall
    171,            // ProfileID::cLemmyBomb
    636,            // ProfileID::c161
    585,            // ProfileID::c162
    605,            // ProfileID::c163
    606,            // ProfileID::c164
    607,            // ProfileID::c165
    492,            // ProfileID::c166
     74 - 0x3ff,    // ProfileID::c167
    637,            // ProfileID::c168
    638,            // ProfileID::c169
    104,            // ProfileID::c16A
    518,            // ProfileID::c16B
    519,            // ProfileID::c16C
    228,            // ProfileID::c16D
    594,            // ProfileID::c16E
    595,            // ProfileID::c16F
    195,            // ProfileID::cKameckIce
    179,            // ProfileID::cWendyIcicle
    198,            // ProfileID::cPeachFinalCastleKoopaJrClown
    694,            // ProfileID::cBoxingKoopaJrClown
    688,            // ProfileID::c174
    212,            // ProfileID::cFinalKoopaJrClown
    209,            // ProfileID::cFinalKoopa
    128,            // ProfileID::c177
    129,            // ProfileID::c178
    130,            // ProfileID::c179
    131,            // ProfileID::c17A
    725,            // ProfileID::c17B
    225,            // ProfileID::c17C
     92,            // ProfileID::c17D
     93,            // ProfileID::c17E
    120,            // ProfileID::c17F
    121,            // ProfileID::c180
    122,            // ProfileID::c181
    123,            // ProfileID::c182
    248,            // ProfileID::c183
    249,            // ProfileID::c184
    250,            // ProfileID::c185
    251,            // ProfileID::c186
    253,            // ProfileID::c187
    290,            // ProfileID::c188
     34 - 0x3ff,    // ProfileID::c189
     35 - 0x3ff,    // ProfileID::c18A
    394,            // ProfileID::c18B
    395,            // ProfileID::c18C
    396,            // ProfileID::c18D
    397,            // ProfileID::c18E
    398,            // ProfileID::c18F
    399,            // ProfileID::c190
    400,            // ProfileID::c191
    401,            // ProfileID::c192
    402,            // ProfileID::c193
    403,            // ProfileID::c194
    404,            // ProfileID::c195
    405,            // ProfileID::c196
    406,            // ProfileID::c197
    407,            // ProfileID::c198
    408,            // ProfileID::c199
    409,            // ProfileID::c19A
    410,            // ProfileID::c19B
    411,            // ProfileID::c19C
    412,            // ProfileID::c19D
    413,            // ProfileID::c19E
    415,            // ProfileID::c19F
    414,            // ProfileID::c1A0
    417,            // ProfileID::c1A1
    418,            // ProfileID::c1A2
    419,            // ProfileID::c1A3
    420,            // ProfileID::c1A4
    421,            // ProfileID::c1A5
    422,            // ProfileID::c1A6
    423,            // ProfileID::c1A7
    424,            // ProfileID::c1A8
    425,            // ProfileID::c1A9
    318,            // ProfileID::c1AA
    319,            // ProfileID::c1AB
    320,            // ProfileID::c1AC
    321,            // ProfileID::c1AD
    322,            // ProfileID::c1AE
    323,            // ProfileID::c1AF
    324,            // ProfileID::c1B0
    325,            // ProfileID::c1B1
    326,            // ProfileID::c1B2
    327,            // ProfileID::c1B3
    332,            // ProfileID::c1B4
    331,            // ProfileID::c1B5
    713,            // ProfileID::cCoinmakiCoin
    117 - 0x3ff,    // ProfileID::c1B7
    112 - 0x3ff,    // ProfileID::c1B8
      0,            // ProfileID::c1B9
      3,            // ProfileID::cYoshi
      2,            // ProfileID::cTottenPlayer
      1,            // ProfileID::cPlayerObject
      4,            // ProfileID::c1BD
    230,            // ProfileID::c1BE
    231,            // ProfileID::c1BF
    234,            // ProfileID::c1C0
    235,            // ProfileID::c1C1
    236,            // ProfileID::c1C2
    233,            // ProfileID::c1C3
    232,            // ProfileID::c1C4
    709,            // ProfileID::cSlotYoshiChibi
     83 - 0x3ff,    // ProfileID::c1C6
    237,            // ProfileID::c1C7
    238,            // ProfileID::c1C8
    239,            // ProfileID::c1C9
    240,            // ProfileID::c1CA
    241,            // ProfileID::c1CB
    242,            // ProfileID::c1CC
    243,            // ProfileID::c1CD
    244,            // ProfileID::c1CE
    245,            // ProfileID::cQuestPrizeItem
    246,            // ProfileID::c1D0
    247,            // ProfileID::c1D1
    679,            // ProfileID::c1D2
      5,            // ProfileID::c1D3
      6,            // ProfileID::c1D4
      7,            // ProfileID::c1D5
      8,            // ProfileID::c1D6
      9,            // ProfileID::c1D7
     10,            // ProfileID::c1D8
     11,            // ProfileID::c1D9
     12,            // ProfileID::cIceBall
     13,            // ProfileID::cIceBallPakkun
     14,            // ProfileID::cFireBallPlayer
     15,            // ProfileID::cFireBallPakkun
     16,            // ProfileID::c1DE
     17,            // ProfileID::c1DF
     18,            // ProfileID::c1E0
     19,            // ProfileID::c1E1
     20,            // ProfileID::c1E2
     26,            // ProfileID::c1E3
     27,            // ProfileID::c1E4
     28,            // ProfileID::c1E5
     29,            // ProfileID::c1E6
     30,            // ProfileID::c1E7
     31,            // ProfileID::c1E8
     32,            // ProfileID::c1E9
     33,            // ProfileID::c1EA
     34,            // ProfileID::c1EB
     35,            // ProfileID::c1EC
     36,            // ProfileID::c1ED
     37,            // ProfileID::c1EE
     38,            // ProfileID::c1EF
     39,            // ProfileID::c1F0
     40,            // ProfileID::c1F1
     41,            // ProfileID::c1F2
     42,            // ProfileID::c1F3
     43,            // ProfileID::c1F4
     44,            // ProfileID::c1F5
     45,            // ProfileID::c1F6
     46,            // ProfileID::c1F7
    591,            // ProfileID::c1F8
    427,            // ProfileID::c1F9
    428,            // ProfileID::c1FA
    429,            // ProfileID::c1FB
    430,            // ProfileID::c1FC
    431,            // ProfileID::c1FD
    432,            // ProfileID::c1FE
     86,            // ProfileID::c1FF
     87,            // ProfileID::c200
     88,            // ProfileID::c201
     89,            // ProfileID::c202
     90,            // ProfileID::c203
     91,            // ProfileID::c204
     94,            // ProfileID::c205
     95,            // ProfileID::c206
     97,            // ProfileID::c207
     96,            // ProfileID::c208
     98,            // ProfileID::c209
     99,            // ProfileID::c20A
    100,            // ProfileID::c20B
    101,            // ProfileID::c20C
    102,            // ProfileID::c20D
    103,            // ProfileID::c20E
     48 - 0x3ff,    // ProfileID::c20F
    105,            // ProfileID::c210
    106,            // ProfileID::c211
    107,            // ProfileID::c212
    108,            // ProfileID::c213
    109,            // ProfileID::c214
    110,            // ProfileID::c215
    111,            // ProfileID::c216
    112,            // ProfileID::c217
    113,            // ProfileID::c218
    114,            // ProfileID::c219
    115,            // ProfileID::c21A
    116,            // ProfileID::c21B
    117,            // ProfileID::c21C
    118,            // ProfileID::c21D
     38 - 0x3ff,    // ProfileID::c21E
     39 - 0x3ff,    // ProfileID::c21F
     40 - 0x3ff,    // ProfileID::c220
     46 - 0x3ff,    // ProfileID::c221
     47 - 0x3ff,    // ProfileID::c222
     42 - 0x3ff,    // ProfileID::c223
    119,            // ProfileID::c224
    124,            // ProfileID::c225
    125,            // ProfileID::c226
     97 - 0x3ff,    // ProfileID::c227
     98 - 0x3ff,    // ProfileID::c228
    126,            // ProfileID::c229
    127,            // ProfileID::c22A
    252,            // ProfileID::c22B
    137,            // ProfileID::c22C
    138,            // ProfileID::c22D
    139,            // ProfileID::cFireBallKeronpa
    140,            // ProfileID::cFireBallKeronpaRDash
    107 - 0x3ff,    // ProfileID::c230
    141,            // ProfileID::c231
    152,            // ProfileID::c232
    153,            // ProfileID::c233
    154,            // ProfileID::c234
    227,            // ProfileID::c235
    155,            // ProfileID::c236
    156,            // ProfileID::c237
    157,            // ProfileID::c238
    158,            // ProfileID::c239
    159,            // ProfileID::c23A
    160,            // ProfileID::c23B
    161,            // ProfileID::c23C
    162,            // ProfileID::c23D
    163,            // ProfileID::c23E
      2 - 0x3ff,    // ProfileID::c23F
      3 - 0x3ff,    // ProfileID::c240
      4 - 0x3ff,    // ProfileID::c241
      5 - 0x3ff,    // ProfileID::c242
      6 - 0x3ff,    // ProfileID::c243
      7 - 0x3ff,    // ProfileID::c244
      8 - 0x3ff,    // ProfileID::c245
      9 - 0x3ff,    // ProfileID::c246
     10 - 0x3ff,    // ProfileID::c247
     11 - 0x3ff,    // ProfileID::c248
     12 - 0x3ff,    // ProfileID::c249
     13 - 0x3ff,    // ProfileID::c24A
     14 - 0x3ff,    // ProfileID::cBgCenter
     15 - 0x3ff,    // ProfileID::c24C
    106 - 0x3ff,    // ProfileID::c24D
     16 - 0x3ff,    // ProfileID::c24E
    254,            // ProfileID::cKinoko
    255,            // ProfileID::cFireFlower
    258,            // ProfileID::cMameKinoko
    259,            // ProfileID::cIceFlower
    260,            // ProfileID::cPropeller
    261,            // ProfileID::cPenguin
    262,            // ProfileID::cOneUpKinoko
    263,            // ProfileID::cMusasabi
    264,            // ProfileID::cSuperMoon
    265,            // ProfileID::cTitleDemoItem
    302,            // ProfileID::c259
    310,            // ProfileID::c25A
    311,            // ProfileID::c25B
    312,            // ProfileID::c25C
    313,            // ProfileID::c25D
    314,            // ProfileID::c25E
    315,            // ProfileID::c25F
    316,            // ProfileID::c260
    317,            // ProfileID::c261
    333,            // ProfileID::c262
    334,            // ProfileID::c263
    426,            // ProfileID::c264
    439,            // ProfileID::c265
     37 - 0x3ff,    // ProfileID::c266
     36 - 0x3ff,    // ProfileID::c267
    505,            // ProfileID::c268
    506,            // ProfileID::cSpanner
    507,            // ProfileID::c26A
    508,            // ProfileID::c26B
    509,            // ProfileID::c26C
    510,            // ProfileID::c26D
    511,            // ProfileID::c26E
    512,            // ProfileID::c26F
    513,            // ProfileID::c270
     44 - 0x3ff,    // ProfileID::c271
     45 - 0x3ff,    // ProfileID::c272
    456,            // ProfileID::c273
    458,            // ProfileID::c274
    459,            // ProfileID::c275
    460,            // ProfileID::c276
    461,            // ProfileID::c277
    462,            // ProfileID::c278
    463,            // ProfileID::c279
     84 - 0x3ff,    // ProfileID::cWakiSearchMagKiller
    464,            // ProfileID::c27B
    465,            // ProfileID::c27C
    142,            // ProfileID::c27D
    143,            // ProfileID::c27E
    144,            // ProfileID::c27F
    145,            // ProfileID::cGabonRock
    146,            // ProfileID::c281
    147,            // ProfileID::c282
    148,            // ProfileID::cRockGabonRock
    149,            // ProfileID::c284
    150,            // ProfileID::cSeichanSnowBall
    151,            // ProfileID::c286
    540,            // ProfileID::c287
    541,            // ProfileID::c288
    542,            // ProfileID::c289
    504,            // ProfileID::c28A
    543,            // ProfileID::c28B
    544,            // ProfileID::c28C
    545,            // ProfileID::c28D
    623,            // ProfileID::c28E
    624,            // ProfileID::c28F
    625,            // ProfileID::c290
    626,            // ProfileID::c291
    627,            // ProfileID::c292
    628,            // ProfileID::c293
    629,            // ProfileID::c294
    630,            // ProfileID::c295
    108 - 0x3ff,    // ProfileID::c296
    109 - 0x3ff,    // ProfileID::c297
    631,            // ProfileID::c298
    632,            // ProfileID::c299
    633,            // ProfileID::c29A
    634,            // ProfileID::c29B
    635,            // ProfileID::c29C
    596,            // ProfileID::c29D
    588,            // ProfileID::c29E
    586,            // ProfileID::c29F
    103 - 0x3ff,    // ProfileID::c2A0
    589,            // ProfileID::c2A1
    590,            // ProfileID::c2A2
    592,            // ProfileID::c2A3
    657,            // ProfileID::c2A4
    658,            // ProfileID::c2A5
    164,            // ProfileID::cBun
    165,            // ProfileID::cBunW2
    166,            // ProfileID::cBunW3
    167,            // ProfileID::cBunW4
    168,            // ProfileID::cBunW5
    169,            // ProfileID::cBunW6
     54 - 0x3ff,    // ProfileID::cBunDemo
     55 - 0x3ff,    // ProfileID::cKokoopaDemo
     56 - 0x3ff,    // ProfileID::cKoopaJrDemo
     57 - 0x3ff,    // ProfileID::cKameckDemo
     58 - 0x3ff,    // ProfileID::cBossKKDemo
     59 - 0x3ff,    // ProfileID::cPeachFinalCastleKoopaJrDemo
     60 - 0x3ff,    // ProfileID::cKoopaDemo
     61 - 0x3ff,    // ProfileID::cFinalKoopaDemo
     62 - 0x3ff,    // ProfileID::cPeachDemo
    181,            // ProfileID::cLarry
    182,            // ProfileID::cKokoopaSearchFire
    172,            // ProfileID::cLemmy
    174,            // ProfileID::cMorton
    175,            // ProfileID::cMortonSanbo
    176,            // ProfileID::cMortonSanboParts
    177,            // ProfileID::cWendy
    178,            // ProfileID::cWendyRing
    183,            // ProfileID::cLudwig
    184,            // ProfileID::cLudwigAlterEgo
    185,            // ProfileID::cIggy
    186,            // ProfileID::cIggyMagic
    188,            // ProfileID::cWoogan
    189,            // ProfileID::cRoy
    102 - 0x3ff,    // ProfileID::cRoyLiftWaki
    190,            // ProfileID::cBossKK
    191,            // ProfileID::cBossKKThunder
    194,            // ProfileID::cKameck
     63 - 0x3ff,    // ProfileID::cKameckIceConfig
     64 - 0x3ff,    // ProfileID::cKameckWarpPos
    196,            // ProfileID::cKameckMagic
    197,            // ProfileID::cPeachFinalCastleKoopaJr
    203,            // ProfileID::cKoopa
     89 - 0x3ff,    // ProfileID::cKoopaFireWaki
    204,            // ProfileID::cKoopaFire
    207,            // ProfileID::cDemoKoopaJrClown
    206,            // ProfileID::cDemoKoopaJr
    170,            // ProfileID::cBunDemoKameck
    208,            // ProfileID::cKoopaDemoKameck
    192,            // ProfileID::cBossKKDemoKameck
    193,            // ProfileID::cBossKKDemoKK
    210,            // ProfileID::cFinalKoopaFire
    211,            // ProfileID::cFinalKoopaJr
    213,            // ProfileID::cFinalKoopaJrFire
    214,            // ProfileID::cFinalBomhei
    666,            // ProfileID::cKokoopaShipLemmy
    667,            // ProfileID::cKokoopaShipMorton
    668,            // ProfileID::cKokoopaShipLarry
    669,            // ProfileID::cKokoopaShipWendy
    670,            // ProfileID::cKokoopaShipIggy
    671,            // ProfileID::cKokoopaShipRoy
    672,            // ProfileID::cKokoopaShipLudwig
    674,            // ProfileID::cPeach
    675,            // ProfileID::c2E0
    676,            // ProfileID::cFinalDVPeach
    677,            // ProfileID::cFinalDVShutter
    678,            // ProfileID::c2E3
    295,            // ProfileID::c2E4
    296,            // ProfileID::c2E5
    297,            // ProfileID::c2E6
    298,            // ProfileID::c2E7
    299,            // ProfileID::c2E8
    300,            // ProfileID::c2E9
    301,            // ProfileID::c2EA
     43 - 0x3ff,    // ProfileID::c2EB
     69 - 0x3ff,    // ProfileID::c2EC
     70 - 0x3ff,    // ProfileID::c2ED
    303,            // ProfileID::c2EE
    304,            // ProfileID::c2EF
    305,            // ProfileID::c2F0
    306,            // ProfileID::c2F1
    307,            // ProfileID::c2F2
    335,            // ProfileID::c2F3
    493,            // ProfileID::c2F4
    340,            // ProfileID::c2F5
    339,            // ProfileID::cHammer
    342,            // ProfileID::c2F7
    341,            // ProfileID::cBoomerang
    344,            // ProfileID::c2F9
    343,            // ProfileID::cFireBallBros
    346,            // ProfileID::c2FB
    345,            // ProfileID::cIceBallBros
    348,            // ProfileID::c2FD
    347,            // ProfileID::cMegaHammer
    349,            // ProfileID::c2FF
    350,            // ProfileID::c300
    351,            // ProfileID::c301
     96 - 0x3ff,    // ProfileID::c302
    494,            // ProfileID::c303
    495,            // ProfileID::c304
     21,            // ProfileID::c305
     22,            // ProfileID::c306
     23,            // ProfileID::c307
     24,            // ProfileID::c308
     25,            // ProfileID::c309
    597,            // ProfileID::c30A
    599,            // ProfileID::c30B
    600,            // ProfileID::c30C
    601,            // ProfileID::c30D
    602,            // ProfileID::c30E
    603,            // ProfileID::c30F
    604,            // ProfileID::c310
    433,            // ProfileID::c311
    434,            // ProfileID::c312
    472,            // ProfileID::c313
    473,            // ProfileID::c314
    474,            // ProfileID::c315
    475,            // ProfileID::c316
    476,            // ProfileID::c317
    477,            // ProfileID::c318
    478,            // ProfileID::c319
     90 - 0x3ff,    // ProfileID::c31A
     93 - 0x3ff,    // ProfileID::c31B
     94 - 0x3ff,    // ProfileID::c31C
    487,            // ProfileID::c31D
    486,            // ProfileID::c31E
    491,            // ProfileID::c31F
    570,            // ProfileID::c320
    659,            // ProfileID::c321
    641,            // ProfileID::c322
    642,            // ProfileID::c323
    643,            // ProfileID::c324
    644,            // ProfileID::c325
    646,            // ProfileID::c326
    653,            // ProfileID::c327
    654,            // ProfileID::c328
    655,            // ProfileID::cBattleItem
    665,            // ProfileID::c32A
    656,            // ProfileID::cVsBattleItem
    660,            // ProfileID::c32C
    661,            // ProfileID::c32D
     85 - 0x3ff,    // ProfileID::c32E
    662,            // ProfileID::c32F
    663,            // ProfileID::c330
    664,            // ProfileID::c331
    686,            // ProfileID::cKoopaJrFire
    687,            // ProfileID::cKoopaJrBall
    690,            // ProfileID::cUnderwaterKoopaJr
    691,            // ProfileID::cUnderwaterKoopaJrClown
    692,            // ProfileID::cUnderwaterKoopaJrRetreatPos
    693,            // ProfileID::cBoxingKoopaJr
    695,            // ProfileID::cBoxingKoopaJrPostBattleDemo
    696,            // ProfileID::cBoxingKoopaJrClownPostBattleDemo
    710,            // ProfileID::cMiniGamePanelItem
    711,            // ProfileID::cSlotItem
    715,            // ProfileID::cCoinmakiCannon
    714,            // ProfileID::cCoinmakiItem
    716,            // ProfileID::cMiniGameKinopio
    717,            // ProfileID::c33F
    718,            // ProfileID::c340
    719,            // ProfileID::c341
    720,            // ProfileID::c342
     99 - 0x3ff,    // ProfileID::c343
    100 - 0x3ff,    // ProfileID::c344
    101 - 0x3ff,    // ProfileID::c345
    104 - 0x3ff,    // ProfileID::c346
    116 - 0x3ff,    // ProfileID::c347
    729,            // ProfileID::cStaffCreditChibiYoshiABC
    730,            // ProfileID::cStaffCreditChibiYoshiBalloon
    731,            // ProfileID::cStaffCreditChibiYoshiBalloonCheer
    732,            // ProfileID::cStaffCreditChibiYoshiLight
    733,            // ProfileID::cStaffCreditChibiYoshiLightCheer
    734,            // ProfileID::cStaffCreditSoapABC
    735,            // ProfileID::cStaffCreditSoapCoin
    736,            // ProfileID::cStaffCreditTottenKun
    726,            // ProfileID::c350
    110 - 0x3ff,    // ProfileID::c351
    113 - 0x3ff,    // ProfileID::c352
    114 - 0x3ff,    // ProfileID::c353
    256,            // ProfileID::cRealizeFeverStar
    257,            // ProfileID::cStar
    737,            // ProfileID::cCourseSelectPlayer
    738,            // ProfileID::cCourseSelectPlayer2PSub
    739,            // ProfileID::cCourseSelectChibiYoshi
    740,            // ProfileID::cCourseSelectCamera
    741,            // ProfileID::cCourseSelectCastle
    742,            // ProfileID::cCourseSelectToride
    743,            // ProfileID::cCourseSelectKinokoHouse1up
    744,            // ProfileID::cCourseSelectKinokoHouseShuffle
    745,            // ProfileID::cCourseSelectKinokoHouseSlot
    746,            // ProfileID::cCourseSelectPeachGates1st
    747,            // ProfileID::cCourseSelectPeachGates2nd
    748,            // ProfileID::cCourseSelectCoursePoint
    749,            // ProfileID::cCourseSelectWorldMoveDokan
    751,            // ProfileID::cCourseSelectW8Cloud
    750,            // ProfileID::cCourseSelectGhost
    752,            // ProfileID::cCourseSelectW2Bros
    754,            // ProfileID::cCourseSelectShipW1
    755,            // ProfileID::cCourseSelectShipW2
    756,            // ProfileID::cCourseSelectShipW3
    757,            // ProfileID::cCourseSelectShipW4
    758,            // ProfileID::cCourseSelectShipW5
    759,            // ProfileID::cCourseSelectShipW6
    760,            // ProfileID::cCourseSelectShipW7
    761,            // ProfileID::cCourseSelectShipW8
    762,            // ProfileID::cCourseSelectShipW8Broken
    763,            // ProfileID::cCourseSelectSurrender
    764,            // ProfileID::cCourseSelectSwitchA
    765,            // ProfileID::cCourseSelectSwitchB
    766,            // ProfileID::cCourseSelectTeresa
    767,            // ProfileID::cCourseSelectOpeningKameck
    768,            // ProfileID::cCourseSelectTorideBoss
    769,            // ProfileID::cCourseSelectPakkun
    770,            // ProfileID::cCourseSelectShadowFirstDemoKinopio
    771,            // ProfileID::cCourseSelectTobiPuku
    772,            // ProfileID::cCourseSelectChorobon
    773,            // ProfileID::cCourseSelectW7Item
    774,            // ProfileID::cCourseSelectW5Teresa
    775,            // ProfileID::cCourseSelectFlag
    777,            // ProfileID::cCourseSelectMusasabi
    778,            // ProfileID::cCourseSelectWPillar
    779,            // ProfileID::cCourseSelectW7Bridge
    780,            // ProfileID::cCourseSelectMiiBalloon
    781,            // ProfileID::cCourseSelectPenguin
    782,            // ProfileID::cCourseSelectW4Item
    783,            // ProfileID::cCourseSelectW2Kuribo
    784,            // ProfileID::cCourseSelectPakkunBig
    785,            // ProfileID::cCourseSelectShadowKunIcon
    786,            // ProfileID::cCourseSelectDekaUnira
    787,            // ProfileID::cCourseSelectTomb
    788,            // ProfileID::cCourseSelectShadowFirstDemoShadowKun
    789,            // ProfileID::cCourseSelectKotsuCoaster
    790,            // ProfileID::cCourseSelectKoopaJr
    791,            // ProfileID::cCourseSelectPeach
    792,            // ProfileID::cCourseSelectW1Item
    793,            // ProfileID::cCourseSelectStarGate
    753,            // ProfileID::cCourseSelectEventAssistant
    794,            // Profile 910
    795,            // Profile 911
      0 - 0x3ff     // Profile 912
};

// -----------------------------------------  ResType ----------------------------------------- //

const s8 Profile::cResType[cProfileID_Max] = {
    Profile::cResType_Boot,         // ProfileID::c000
    Profile::cResType_Boot,         // ProfileID::c001
    Profile::cResType_Boot,         // ProfileID::c002
    Profile::cResType_Boot,         // ProfileID::c003
    Profile::cResType_Boot,         // ProfileID::c004
    Profile::cResType_Boot,         // ProfileID::c005
    Profile::cResType_Boot,         // ProfileID::c006
    Profile::cResType_Boot,         // ProfileID::c007
    Profile::cResType_Boot,         // ProfileID::c008
    Profile::cResType_Boot,         // ProfileID::c009
    Profile::cResType_Boot,         // ProfileID::c00A
    Profile::cResType_Boot,         // ProfileID::c00B
    Profile::cResType_Boot,         // ProfileID::c00C
    Profile::cResType_Boot,         // ProfileID::c00D
    Profile::cResType_Boot,         // ProfileID::c00E
    Profile::cResType_Boot,         // ProfileID::c00F
    Profile::cResType_Boot,         // ProfileID::c010
    Profile::cResType_Boot,         // ProfileID::c011
    Profile::cResType_Boot,         // ProfileID::c012
    Profile::cResType_Boot,         // ProfileID::c013
    Profile::cResType_Boot,         // ProfileID::c014
    Profile::cResType_Course,       // ProfileID::c015
    Profile::cResType_Course,       // ProfileID::c016
    Profile::cResType_Course,       // ProfileID::c017
    Profile::cResType_Course,       // ProfileID::cMiniGameMgr
    Profile::cResType_Course,       // ProfileID::cMiniGameMgrRDash
    Profile::cResType_Boot,         // ProfileID::cShuffleBlockMgr
    Profile::cResType_Boot,         // ProfileID::cSlotMgr
    Profile::cResType_Boot,         // ProfileID::cCoinmakiMgr
    Profile::cResType_Boot,         // ProfileID::c01D
    Profile::cResType_Boot,         // ProfileID::c01E
    Profile::cResType_Boot,         // ProfileID::c01F
    Profile::cResType_Course,       // ProfileID::c020
    Profile::cResType_Course,       // ProfileID::cShootingStar
    Profile::cResType_Course,       // ProfileID::cStaffRollMgr
    Profile::cResType_Course,       // ProfileID::cStaffRollMgrRDash
    Profile::cResType_Course,       // ProfileID::c024
    Profile::cResType_Boot,         // ProfileID::c025
    Profile::cResType_Course,       // ProfileID::c026
    Profile::cResType_Boot,         // ProfileID::c027
    Profile::cResType_Boot,         // ProfileID::c028
    Profile::cResType_Boot,         // ProfileID::c029
    Profile::cResType_Boot,         // ProfileID::c02A
    Profile::cResType_Course,       // ProfileID::c02B
    Profile::cResType_Course,       // ProfileID::c02C
    Profile::cResType_Boot,         // ProfileID::c02D
    Profile::cResType_Boot,         // ProfileID::c02E
    Profile::cResType_Boot,         // ProfileID::c02F
    Profile::cResType_Boot,         // ProfileID::c030
    Profile::cResType_Boot,         // ProfileID::c031
    Profile::cResType_Course,       // ProfileID::c032
    Profile::cResType_Course,       // ProfileID::c033
    Profile::cResType_Course,       // ProfileID::c034
    Profile::cResType_Course,       // ProfileID::c035
    Profile::cResType_Course,       // ProfileID::c036
    Profile::cResType_Course,       // ProfileID::c037
    Profile::cResType_Course,       // ProfileID::c038
    Profile::cResType_Course,       // ProfileID::c039
    Profile::cResType_Course,       // ProfileID::c03A
    Profile::cResType_Course,       // ProfileID::c03B
    Profile::cResType_Course,       // ProfileID::c03C
    Profile::cResType_Course,       // ProfileID::c03D
    Profile::cResType_Course,       // ProfileID::c03E
    Profile::cResType_Course,       // ProfileID::c03F
    Profile::cResType_Course,       // ProfileID::c040
    Profile::cResType_Course,       // ProfileID::c041
    Profile::cResType_Course,       // ProfileID::c042
    Profile::cResType_Course,       // ProfileID::c043
    Profile::cResType_Course,       // ProfileID::c044
    Profile::cResType_Course,       // ProfileID::c045
    Profile::cResType_Course,       // ProfileID::c046
    Profile::cResType_Course,       // ProfileID::c047
    Profile::cResType_Course,       // ProfileID::c048
    Profile::cResType_Course,       // ProfileID::c049
    Profile::cResType_Course,       // ProfileID::c04A
    Profile::cResType_Course,       // ProfileID::c04B
    Profile::cResType_Course,       // ProfileID::c04C
    Profile::cResType_Course,       // ProfileID::c04D
    Profile::cResType_Course,       // ProfileID::c04E
    Profile::cResType_Course,       // ProfileID::c04F
    Profile::cResType_Course,       // ProfileID::c050
    Profile::cResType_Course,       // ProfileID::c051
    Profile::cResType_Course,       // ProfileID::c052
    Profile::cResType_Course,       // ProfileID::c053
    Profile::cResType_Course,       // ProfileID::c054
    Profile::cResType_Course,       // ProfileID::c055
    Profile::cResType_Course,       // ProfileID::c056
    Profile::cResType_Course,       // ProfileID::c057
    Profile::cResType_Course,       // ProfileID::c058
    Profile::cResType_Boot,         // ProfileID::c059
    Profile::cResType_Course,       // ProfileID::c05A
    Profile::cResType_Course,       // ProfileID::c05B
    Profile::cResType_Course,       // ProfileID::c05C
    Profile::cResType_Course,       // ProfileID::c05D
    Profile::cResType_Course,       // ProfileID::c05E
    Profile::cResType_Course,       // ProfileID::c05F
    Profile::cResType_Course,       // ProfileID::c060
    Profile::cResType_Course,       // ProfileID::c061
    Profile::cResType_Course,       // ProfileID::c062
    Profile::cResType_Course,       // ProfileID::c063
    Profile::cResType_Course,       // ProfileID::c064
    Profile::cResType_Course,       // ProfileID::c065
    Profile::cResType_Course,       // ProfileID::c066
    Profile::cResType_Course,       // ProfileID::c067
    Profile::cResType_Course,       // ProfileID::c068
    Profile::cResType_Course,       // ProfileID::c069
    Profile::cResType_Course,       // ProfileID::c06A
    Profile::cResType_Course,       // ProfileID::c06B
    Profile::cResType_Course,       // ProfileID::c06C
    Profile::cResType_Course,       // ProfileID::c06D
    Profile::cResType_Course,       // ProfileID::c06E
    Profile::cResType_Course,       // ProfileID::c06F
    Profile::cResType_Course,       // ProfileID::c070
    Profile::cResType_Course,       // ProfileID::c071
    Profile::cResType_Course,       // ProfileID::c072
    Profile::cResType_Course,       // ProfileID::c073
    Profile::cResType_Course,       // ProfileID::c074
    Profile::cResType_Course,       // ProfileID::c075
    Profile::cResType_Course,       // ProfileID::c076
    Profile::cResType_Course,       // ProfileID::c077
    Profile::cResType_Course,       // ProfileID::c078
    Profile::cResType_Course,       // ProfileID::c079
    Profile::cResType_Course,       // ProfileID::c07A
    Profile::cResType_Course,       // ProfileID::c07B
    Profile::cResType_Course,       // ProfileID::c07C
    Profile::cResType_Course,       // ProfileID::c07D
    Profile::cResType_Course,       // ProfileID::c07E
    Profile::cResType_Course,       // ProfileID::c07F
    Profile::cResType_Course,       // ProfileID::c080
    Profile::cResType_Course,       // ProfileID::c081
    Profile::cResType_Course,       // ProfileID::c082
    Profile::cResType_Course,       // ProfileID::c083
    Profile::cResType_Course,       // ProfileID::c084
    Profile::cResType_Course,       // ProfileID::c085
    Profile::cResType_Course,       // ProfileID::c086
    Profile::cResType_Course,       // ProfileID::c087
    Profile::cResType_Course,       // ProfileID::c088
    Profile::cResType_Course,       // ProfileID::c089
    Profile::cResType_Course,       // ProfileID::c08A
    Profile::cResType_Course,       // ProfileID::c08B
    Profile::cResType_Course,       // ProfileID::c08C
    Profile::cResType_Course,       // ProfileID::c08D
    Profile::cResType_Course,       // ProfileID::c08E
    Profile::cResType_Course,       // ProfileID::c08F
    Profile::cResType_Course,       // ProfileID::c090
    Profile::cResType_Course,       // ProfileID::c091
    Profile::cResType_Course,       // ProfileID::c092
    Profile::cResType_Course,       // ProfileID::c093
    Profile::cResType_Course,       // ProfileID::c094
    Profile::cResType_Course,       // ProfileID::c095
    Profile::cResType_Course,       // ProfileID::c096
    Profile::cResType_Course,       // ProfileID::c097
    Profile::cResType_Course,       // ProfileID::c098
    Profile::cResType_Course,       // ProfileID::c099
    Profile::cResType_Course,       // ProfileID::c09A
    Profile::cResType_Course,       // ProfileID::c09B
    Profile::cResType_Course,       // ProfileID::c09C
    Profile::cResType_Course,       // ProfileID::c09D
    Profile::cResType_Course,       // ProfileID::c09E
    Profile::cResType_Course,       // ProfileID::c09F
    Profile::cResType_Course,       // ProfileID::c0A0
    Profile::cResType_Course,       // ProfileID::c0A1
    Profile::cResType_Course,       // ProfileID::c0A2
    Profile::cResType_Course,       // ProfileID::c0A3
    Profile::cResType_Course,       // ProfileID::c0A4
    Profile::cResType_Course,       // ProfileID::c0A5
    Profile::cResType_Course,       // ProfileID::c0A6
    Profile::cResType_Course,       // ProfileID::c0A7
    Profile::cResType_Course,       // ProfileID::c0A8
    Profile::cResType_Course,       // ProfileID::c0A9
    Profile::cResType_Course,       // ProfileID::c0AA
    Profile::cResType_Course,       // ProfileID::c0AB
    Profile::cResType_Course,       // ProfileID::c0AC
    Profile::cResType_Course,       // ProfileID::c0AD
    Profile::cResType_Course,       // ProfileID::c0AE
    Profile::cResType_Course,       // ProfileID::c0AF
    Profile::cResType_Course,       // ProfileID::c0B0
    Profile::cResType_Course,       // ProfileID::c0B1
    Profile::cResType_Course,       // ProfileID::c0B2
    Profile::cResType_Course,       // ProfileID::c0B3
    Profile::cResType_Course,       // ProfileID::c0B4
    Profile::cResType_Course,       // ProfileID::c0B5
    Profile::cResType_Course,       // ProfileID::c0B6
    Profile::cResType_Course,       // ProfileID::c0B7
    Profile::cResType_Course,       // ProfileID::c0B8
    Profile::cResType_Course,       // ProfileID::c0B9
    Profile::cResType_Course,       // ProfileID::c0BA
    Profile::cResType_Course,       // ProfileID::c0BB
    Profile::cResType_Course,       // ProfileID::c0BC
    Profile::cResType_Boot,         // ProfileID::c0BD
    Profile::cResType_Course,       // ProfileID::c0BE
    Profile::cResType_Course,       // ProfileID::c0BF
    Profile::cResType_Course,       // ProfileID::c0C0
    Profile::cResType_Course,       // ProfileID::c0C1
    Profile::cResType_Course,       // ProfileID::c0C2
    Profile::cResType_Course,       // ProfileID::c0C3
    Profile::cResType_Course,       // ProfileID::c0C4
    Profile::cResType_Course,       // ProfileID::c0C5
    Profile::cResType_Course,       // ProfileID::c0C6
    Profile::cResType_Course,       // ProfileID::c0C7
    Profile::cResType_Course,       // ProfileID::c0C8
    Profile::cResType_Course,       // ProfileID::c0C9
    Profile::cResType_Course,       // ProfileID::c0CA
    Profile::cResType_Course,       // ProfileID::c0CB
    Profile::cResType_Course,       // ProfileID::c0CC
    Profile::cResType_Course,       // ProfileID::c0CD
    Profile::cResType_Course,       // ProfileID::c0CE
    Profile::cResType_Course,       // ProfileID::c0CF
    Profile::cResType_Course,       // ProfileID::c0D0
    Profile::cResType_Course,       // ProfileID::c0D1
    Profile::cResType_Course,       // ProfileID::cFloorHoleDokan
    Profile::cResType_Course,       // ProfileID::c0D3
    Profile::cResType_Course,       // ProfileID::c0D4
    Profile::cResType_Course,       // ProfileID::c0D5
    Profile::cResType_Course,       // ProfileID::c0D6
    Profile::cResType_Course,       // ProfileID::c0D7
    Profile::cResType_Course,       // ProfileID::c0D8
    Profile::cResType_Course,       // ProfileID::c0D9
    Profile::cResType_Course,       // ProfileID::c0DA
    Profile::cResType_Course,       // ProfileID::c0DB
    Profile::cResType_Course,       // ProfileID::c0DC
    Profile::cResType_Course,       // ProfileID::c0DD
    Profile::cResType_Course,       // ProfileID::c0DE
    Profile::cResType_Course,       // ProfileID::c0DF
    Profile::cResType_Course,       // ProfileID::c0E0
    Profile::cResType_Course,       // ProfileID::c0E1
    Profile::cResType_Course,       // ProfileID::c0E2
    Profile::cResType_Course,       // ProfileID::c0E3
    Profile::cResType_Course,       // ProfileID::c0E4
    Profile::cResType_Course,       // ProfileID::c0E5
    Profile::cResType_Course,       // ProfileID::c0E6
    Profile::cResType_Course,       // ProfileID::c0E7
    Profile::cResType_Course,       // ProfileID::c0E8
    Profile::cResType_Course,       // ProfileID::c0E9
    Profile::cResType_Course,       // ProfileID::c0EA
    Profile::cResType_Course,       // ProfileID::c0EB
    Profile::cResType_Course,       // ProfileID::c0EC
    Profile::cResType_Boot,         // ProfileID::c0ED
    Profile::cResType_Course,       // ProfileID::c0EE
    Profile::cResType_Course,       // ProfileID::c0EF
    Profile::cResType_Course,       // ProfileID::c0F0
    Profile::cResType_Course,       // ProfileID::c0F1
    Profile::cResType_Course,       // ProfileID::c0F2
    Profile::cResType_Course,       // ProfileID::c0F3
    Profile::cResType_Course,       // ProfileID::c0F4
    Profile::cResType_Course,       // ProfileID::c0F5
    Profile::cResType_Course,       // ProfileID::c0F6
    Profile::cResType_Course,       // ProfileID::c0F7
    Profile::cResType_Course,       // ProfileID::c0F8
    Profile::cResType_Course,       // ProfileID::c0F9
    Profile::cResType_Course,       // ProfileID::c0FA
    Profile::cResType_Course,       // ProfileID::c0FB
    Profile::cResType_Course,       // ProfileID::c0FC
    Profile::cResType_Course,       // ProfileID::c0FD
    Profile::cResType_Course,       // ProfileID::c0FE
    Profile::cResType_Course,       // ProfileID::c0FF
    Profile::cResType_Course,       // ProfileID::c100
    Profile::cResType_Course,       // ProfileID::c101
    Profile::cResType_Course,       // ProfileID::c102
    Profile::cResType_Course,       // ProfileID::c103
    Profile::cResType_Course,       // ProfileID::c104
    Profile::cResType_Course,       // ProfileID::cShuffleBlock
    Profile::cResType_Course,       // ProfileID::cKokoopaShipWarpCannon
    Profile::cResType_Course,       // ProfileID::c107
    Profile::cResType_Course,       // ProfileID::c108
    Profile::cResType_Course,       // ProfileID::cKoopaShutter
    Profile::cResType_Course,       // ProfileID::c10A
    Profile::cResType_Course,       // ProfileID::c10B
    Profile::cResType_Course,       // ProfileID::c10C
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJrLift
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJrLiftHmove
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJrLiftPairObj
    Profile::cResType_Course,       // ProfileID::cRoyLiftWakiStep
    Profile::cResType_Course,       // ProfileID::cWendyFloor
    Profile::cResType_Course,       // ProfileID::cIggyRoom
    Profile::cResType_Course,       // ProfileID::c113
    Profile::cResType_Course,       // ProfileID::c114
    Profile::cResType_Course,       // ProfileID::c115
    Profile::cResType_Course,       // ProfileID::c116
    Profile::cResType_Course,       // ProfileID::c117
    Profile::cResType_Course,       // ProfileID::c118
    Profile::cResType_Course,       // ProfileID::c119
    Profile::cResType_Course,       // ProfileID::c11A
    Profile::cResType_Boot,         // ProfileID::c11B
    Profile::cResType_Boot,         // ProfileID::c11C
    Profile::cResType_Course,       // ProfileID::c11D
    Profile::cResType_Course,       // ProfileID::c11E
    Profile::cResType_Boot,         // ProfileID::c11F
    Profile::cResType_Boot,         // ProfileID::c120
    Profile::cResType_Boot,         // ProfileID::c121
    Profile::cResType_Boot,         // ProfileID::c122
    Profile::cResType_Boot,         // ProfileID::c123
    Profile::cResType_Boot,         // ProfileID::c124
    Profile::cResType_Boot,         // ProfileID::c125
    Profile::cResType_Boot,         // ProfileID::c126
    Profile::cResType_Boot,         // ProfileID::c127
    Profile::cResType_Boot,         // ProfileID::c128
    Profile::cResType_Boot,         // ProfileID::c129
    Profile::cResType_Boot,         // ProfileID::c12A
    Profile::cResType_Boot,         // ProfileID::c12B
    Profile::cResType_Boot,         // ProfileID::c12C
    Profile::cResType_Boot,         // ProfileID::c12D
    Profile::cResType_Boot,         // ProfileID::c12E
    Profile::cResType_Boot,         // ProfileID::c12F
    Profile::cResType_Boot,         // ProfileID::c130
    Profile::cResType_Boot,         // ProfileID::c131
    Profile::cResType_Boot,         // ProfileID::c132
    Profile::cResType_Boot,         // ProfileID::c133
    Profile::cResType_Boot,         // ProfileID::c134
    Profile::cResType_Boot,         // ProfileID::c135
    Profile::cResType_Course,       // ProfileID::c136
    Profile::cResType_Boot,         // ProfileID::c137
    Profile::cResType_Course,       // ProfileID::c138
    Profile::cResType_Boot,         // ProfileID::c139
    Profile::cResType_Course,       // ProfileID::c13A
    Profile::cResType_Course,       // ProfileID::c13B
    Profile::cResType_Course,       // ProfileID::c13C
    Profile::cResType_Course,       // ProfileID::c13D
    Profile::cResType_Course,       // ProfileID::c13E
    Profile::cResType_Boot,         // ProfileID::c13F
    Profile::cResType_Course,       // ProfileID::c140
    Profile::cResType_Course,       // ProfileID::c141
    Profile::cResType_Boot,         // ProfileID::c142
    Profile::cResType_Course,       // ProfileID::c143
    Profile::cResType_Course,       // ProfileID::c144
    Profile::cResType_Course,       // ProfileID::c145
    Profile::cResType_Course,       // ProfileID::c146
    Profile::cResType_Course,       // ProfileID::c147
    Profile::cResType_Course,       // ProfileID::c148
    Profile::cResType_Course,       // ProfileID::c149
    Profile::cResType_Course,       // ProfileID::c14A
    Profile::cResType_Course,       // ProfileID::c14B
    Profile::cResType_Course,       // ProfileID::c14C
    Profile::cResType_Course,       // ProfileID::c14D
    Profile::cResType_Course,       // ProfileID::c14E
    Profile::cResType_Course,       // ProfileID::c14F
    Profile::cResType_Course,       // ProfileID::c150
    Profile::cResType_Course,       // ProfileID::c151
    Profile::cResType_Course,       // ProfileID::c152
    Profile::cResType_Course,       // ProfileID::c153
    Profile::cResType_Course,       // ProfileID::c154
    Profile::cResType_Course,       // ProfileID::c155
    Profile::cResType_Course,       // ProfileID::c156
    Profile::cResType_Course,       // ProfileID::c157
    Profile::cResType_Course,       // ProfileID::c158
    Profile::cResType_Course,       // ProfileID::c159
    Profile::cResType_Course,       // ProfileID::c15A
    Profile::cResType_Course,       // ProfileID::c15B
    Profile::cResType_Course,       // ProfileID::c15C
    Profile::cResType_Course,       // ProfileID::c15D
    Profile::cResType_Course,       // ProfileID::c15E
    Profile::cResType_Course,       // ProfileID::cLemmyBall
    Profile::cResType_Course,       // ProfileID::cLemmyBomb
    Profile::cResType_Course,       // ProfileID::c161
    Profile::cResType_Course,       // ProfileID::c162
    Profile::cResType_Course,       // ProfileID::c163
    Profile::cResType_Course,       // ProfileID::c164
    Profile::cResType_Course,       // ProfileID::c165
    Profile::cResType_Course,       // ProfileID::c166
    Profile::cResType_Course,       // ProfileID::c167
    Profile::cResType_Course,       // ProfileID::c168
    Profile::cResType_Course,       // ProfileID::c169
    Profile::cResType_Course,       // ProfileID::c16A
    Profile::cResType_Course,       // ProfileID::c16B
    Profile::cResType_Course,       // ProfileID::c16C
    Profile::cResType_Course,       // ProfileID::c16D
    Profile::cResType_Course,       // ProfileID::c16E
    Profile::cResType_Course,       // ProfileID::c16F
    Profile::cResType_Course,       // ProfileID::cKameckIce
    Profile::cResType_Course,       // ProfileID::cWendyIcicle
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJrClown
    Profile::cResType_Course,       // ProfileID::cBoxingKoopaJrClown
    Profile::cResType_Course,       // ProfileID::c174
    Profile::cResType_Course,       // ProfileID::cFinalKoopaJrClown
    Profile::cResType_Course,       // ProfileID::cFinalKoopa
    Profile::cResType_Course,       // ProfileID::c177
    Profile::cResType_Course,       // ProfileID::c178
    Profile::cResType_Course,       // ProfileID::c179
    Profile::cResType_Course,       // ProfileID::c17A
    Profile::cResType_Course,       // ProfileID::c17B
    Profile::cResType_Course,       // ProfileID::c17C
    Profile::cResType_Course,       // ProfileID::c17D
    Profile::cResType_Course,       // ProfileID::c17E
    Profile::cResType_Course,       // ProfileID::c17F
    Profile::cResType_Course,       // ProfileID::c180
    Profile::cResType_Course,       // ProfileID::c181
    Profile::cResType_Course,       // ProfileID::c182
    Profile::cResType_Course,       // ProfileID::c183
    Profile::cResType_Course,       // ProfileID::c184
    Profile::cResType_Course,       // ProfileID::c185
    Profile::cResType_Course,       // ProfileID::c186
    Profile::cResType_Course,       // ProfileID::c187
    Profile::cResType_Boot,         // ProfileID::c188
    Profile::cResType_Boot,         // ProfileID::c189
    Profile::cResType_Boot,         // ProfileID::c18A
    Profile::cResType_Boot,         // ProfileID::c18B
    Profile::cResType_Boot,         // ProfileID::c18C
    Profile::cResType_Course,       // ProfileID::c18D
    Profile::cResType_Boot,         // ProfileID::c18E
    Profile::cResType_Boot,         // ProfileID::c18F
    Profile::cResType_Boot,         // ProfileID::c190
    Profile::cResType_Boot,         // ProfileID::c191
    Profile::cResType_Boot,         // ProfileID::c192
    Profile::cResType_Boot,         // ProfileID::c193
    Profile::cResType_Boot,         // ProfileID::c194
    Profile::cResType_Boot,         // ProfileID::c195
    Profile::cResType_Boot,         // ProfileID::c196
    Profile::cResType_Boot,         // ProfileID::c197
    Profile::cResType_Boot,         // ProfileID::c198
    Profile::cResType_Course,       // ProfileID::c199
    Profile::cResType_Boot,         // ProfileID::c19A
    Profile::cResType_Boot,         // ProfileID::c19B
    Profile::cResType_Boot,         // ProfileID::c19C
    Profile::cResType_Boot,         // ProfileID::c19D
    Profile::cResType_Boot,         // ProfileID::c19E
    Profile::cResType_Boot,         // ProfileID::c19F
    Profile::cResType_Boot,         // ProfileID::c1A0
    Profile::cResType_Boot,         // ProfileID::c1A1
    Profile::cResType_Course,       // ProfileID::c1A2
    Profile::cResType_Boot,         // ProfileID::c1A3
    Profile::cResType_Boot,         // ProfileID::c1A4
    Profile::cResType_Boot,         // ProfileID::c1A5
    Profile::cResType_Boot,         // ProfileID::c1A6
    Profile::cResType_Boot,         // ProfileID::c1A7
    Profile::cResType_Boot,         // ProfileID::c1A8
    Profile::cResType_Boot,         // ProfileID::c1A9
    Profile::cResType_Course,       // ProfileID::c1AA
    Profile::cResType_Course,       // ProfileID::c1AB
    Profile::cResType_Course,       // ProfileID::c1AC
    Profile::cResType_Course,       // ProfileID::c1AD
    Profile::cResType_Course,       // ProfileID::c1AE
    Profile::cResType_Course,       // ProfileID::c1AF
    Profile::cResType_Course,       // ProfileID::c1B0
    Profile::cResType_Course,       // ProfileID::c1B1
    Profile::cResType_Course,       // ProfileID::c1B2
    Profile::cResType_Course,       // ProfileID::c1B3
    Profile::cResType_Course,       // ProfileID::c1B4
    Profile::cResType_Course,       // ProfileID::c1B5
    Profile::cResType_Course,       // ProfileID::cCoinmakiCoin
    Profile::cResType_Boot,         // ProfileID::c1B7
    Profile::cResType_Boot,         // ProfileID::c1B8
    Profile::cResType_Boot,         // ProfileID::c1B9
    Profile::cResType_Boot,         // ProfileID::cYoshi
    Profile::cResType_Boot,         // ProfileID::cTottenPlayer
    Profile::cResType_Boot,         // ProfileID::cPlayerObject
    Profile::cResType_Boot,         // ProfileID::c1BD
    Profile::cResType_Boot,         // ProfileID::c1BE
    Profile::cResType_Boot,         // ProfileID::c1BF
    Profile::cResType_Boot,         // ProfileID::c1C0
    Profile::cResType_Boot,         // ProfileID::c1C1
    Profile::cResType_Boot,         // ProfileID::c1C2
    Profile::cResType_Boot,         // ProfileID::c1C3
    Profile::cResType_Course,       // ProfileID::c1C4
    Profile::cResType_Course,       // ProfileID::cSlotYoshiChibi
    Profile::cResType_Course,       // ProfileID::c1C6
    Profile::cResType_Course,       // ProfileID::c1C7
    Profile::cResType_Course,       // ProfileID::c1C8
    Profile::cResType_Course,       // ProfileID::c1C9
    Profile::cResType_Course,       // ProfileID::c1CA
    Profile::cResType_Course,       // ProfileID::c1CB
    Profile::cResType_Course,       // ProfileID::c1CC
    Profile::cResType_Course,       // ProfileID::c1CD
    Profile::cResType_Course,       // ProfileID::c1CE
    Profile::cResType_Boot,         // ProfileID::cQuestPrizeItem
    Profile::cResType_Course,       // ProfileID::c1D0
    Profile::cResType_Course,       // ProfileID::c1D1
    Profile::cResType_Course,       // ProfileID::c1D2
    Profile::cResType_Course,       // ProfileID::c1D3
    Profile::cResType_Course,       // ProfileID::c1D4
    Profile::cResType_Course,       // ProfileID::c1D5
    Profile::cResType_Course,       // ProfileID::c1D6
    Profile::cResType_Course,       // ProfileID::c1D7
    Profile::cResType_Course,       // ProfileID::c1D8
    Profile::cResType_Course,       // ProfileID::c1D9
    Profile::cResType_Boot,         // ProfileID::cIceBall
    Profile::cResType_Boot,         // ProfileID::cIceBallPakkun
    Profile::cResType_Boot,         // ProfileID::cFireBallPlayer
    Profile::cResType_Boot,         // ProfileID::cFireBallPakkun
    Profile::cResType_Boot,         // ProfileID::c1DE
    Profile::cResType_Course,       // ProfileID::c1DF
    Profile::cResType_Course,       // ProfileID::c1E0
    Profile::cResType_Course,       // ProfileID::c1E1
    Profile::cResType_Course,       // ProfileID::c1E2
    Profile::cResType_Course,       // ProfileID::c1E3
    Profile::cResType_Course,       // ProfileID::c1E4
    Profile::cResType_Course,       // ProfileID::c1E5
    Profile::cResType_Course,       // ProfileID::c1E6
    Profile::cResType_Course,       // ProfileID::c1E7
    Profile::cResType_Course,       // ProfileID::c1E8
    Profile::cResType_Course,       // ProfileID::c1E9
    Profile::cResType_Course,       // ProfileID::c1EA
    Profile::cResType_Course,       // ProfileID::c1EB
    Profile::cResType_Course,       // ProfileID::c1EC
    Profile::cResType_Course,       // ProfileID::c1ED
    Profile::cResType_Course,       // ProfileID::c1EE
    Profile::cResType_Course,       // ProfileID::c1EF
    Profile::cResType_Course,       // ProfileID::c1F0
    Profile::cResType_Course,       // ProfileID::c1F1
    Profile::cResType_Course,       // ProfileID::c1F2
    Profile::cResType_Course,       // ProfileID::c1F3
    Profile::cResType_Course,       // ProfileID::c1F4
    Profile::cResType_Course,       // ProfileID::c1F5
    Profile::cResType_Course,       // ProfileID::c1F6
    Profile::cResType_Course,       // ProfileID::c1F7
    Profile::cResType_Course,       // ProfileID::c1F8
    Profile::cResType_Course,       // ProfileID::c1F9
    Profile::cResType_Course,       // ProfileID::c1FA
    Profile::cResType_Course,       // ProfileID::c1FB
    Profile::cResType_Course,       // ProfileID::c1FC
    Profile::cResType_Course,       // ProfileID::c1FD
    Profile::cResType_Course,       // ProfileID::c1FE
    Profile::cResType_Boot,         // ProfileID::c1FF
    Profile::cResType_Course,       // ProfileID::c200
    Profile::cResType_Course,       // ProfileID::c201
    Profile::cResType_Course,       // ProfileID::c202
    Profile::cResType_Course,       // ProfileID::c203
    Profile::cResType_Course,       // ProfileID::c204
    Profile::cResType_Course,       // ProfileID::c205
    Profile::cResType_Course,       // ProfileID::c206
    Profile::cResType_Course,       // ProfileID::c207
    Profile::cResType_Course,       // ProfileID::c208
    Profile::cResType_Course,       // ProfileID::c209
    Profile::cResType_Course,       // ProfileID::c20A
    Profile::cResType_Course,       // ProfileID::c20B
    Profile::cResType_Course,       // ProfileID::c20C
    Profile::cResType_Course,       // ProfileID::c20D
    Profile::cResType_Course,       // ProfileID::c20E
    Profile::cResType_Course,       // ProfileID::c20F
    Profile::cResType_Course,       // ProfileID::c210
    Profile::cResType_Course,       // ProfileID::c211
    Profile::cResType_Course,       // ProfileID::c212
    Profile::cResType_Course,       // ProfileID::c213
    Profile::cResType_Course,       // ProfileID::c214
    Profile::cResType_Course,       // ProfileID::c215
    Profile::cResType_Course,       // ProfileID::c216
    Profile::cResType_Course,       // ProfileID::c217
    Profile::cResType_Course,       // ProfileID::c218
    Profile::cResType_Course,       // ProfileID::c219
    Profile::cResType_Course,       // ProfileID::c21A
    Profile::cResType_Course,       // ProfileID::c21B
    Profile::cResType_Course,       // ProfileID::c21C
    Profile::cResType_Course,       // ProfileID::c21D
    Profile::cResType_Course,       // ProfileID::c21E
    Profile::cResType_Course,       // ProfileID::c21F
    Profile::cResType_Course,       // ProfileID::c220
    Profile::cResType_Course,       // ProfileID::c221
    Profile::cResType_Course,       // ProfileID::c222
    Profile::cResType_Course,       // ProfileID::c223
    Profile::cResType_Course,       // ProfileID::c224
    Profile::cResType_Course,       // ProfileID::c225
    Profile::cResType_Course,       // ProfileID::c226
    Profile::cResType_Course,       // ProfileID::c227
    Profile::cResType_Course,       // ProfileID::c228
    Profile::cResType_Course,       // ProfileID::c229
    Profile::cResType_Course,       // ProfileID::c22A
    Profile::cResType_Boot,         // ProfileID::c22B
    Profile::cResType_Course,       // ProfileID::c22C
    Profile::cResType_Course,       // ProfileID::c22D
    Profile::cResType_Course,       // ProfileID::cFireBallKeronpa
    Profile::cResType_Course,       // ProfileID::cFireBallKeronpaRDash
    Profile::cResType_Course,       // ProfileID::c230
    Profile::cResType_Course,       // ProfileID::c231
    Profile::cResType_Course,       // ProfileID::c232
    Profile::cResType_Course,       // ProfileID::c233
    Profile::cResType_Course,       // ProfileID::c234
    Profile::cResType_Course,       // ProfileID::c235
    Profile::cResType_Course,       // ProfileID::c236
    Profile::cResType_Course,       // ProfileID::c237
    Profile::cResType_Course,       // ProfileID::c238
    Profile::cResType_Course,       // ProfileID::c239
    Profile::cResType_Course,       // ProfileID::c23A
    Profile::cResType_Course,       // ProfileID::c23B
    Profile::cResType_Course,       // ProfileID::c23C
    Profile::cResType_Course,       // ProfileID::c23D
    Profile::cResType_Course,       // ProfileID::c23E
    Profile::cResType_Boot,         // ProfileID::c23F
    Profile::cResType_Boot,         // ProfileID::c240
    Profile::cResType_Boot,         // ProfileID::c241
    Profile::cResType_Boot,         // ProfileID::c242
    Profile::cResType_Boot,         // ProfileID::c243
    Profile::cResType_Boot,         // ProfileID::c244
    Profile::cResType_Boot,         // ProfileID::c245
    Profile::cResType_Boot,         // ProfileID::c246
    Profile::cResType_Boot,         // ProfileID::c247
    Profile::cResType_Boot,         // ProfileID::c248
    Profile::cResType_Boot,         // ProfileID::c249
    Profile::cResType_Boot,         // ProfileID::c24A
    Profile::cResType_Boot,         // ProfileID::cBgCenter
    Profile::cResType_Boot,         // ProfileID::c24C
    Profile::cResType_Boot,         // ProfileID::c24D
    Profile::cResType_Boot,         // ProfileID::c24E
    Profile::cResType_Boot,         // ProfileID::cKinoko
    Profile::cResType_Boot,         // ProfileID::cFireFlower
    Profile::cResType_Boot,         // ProfileID::cMameKinoko
    Profile::cResType_Boot,         // ProfileID::cIceFlower
    Profile::cResType_Boot,         // ProfileID::cPropeller
    Profile::cResType_Boot,         // ProfileID::cPenguin
    Profile::cResType_Boot,         // ProfileID::cOneUpKinoko
    Profile::cResType_Boot,         // ProfileID::cMusasabi
    Profile::cResType_Boot,         // ProfileID::cSuperMoon
    Profile::cResType_Boot,         // ProfileID::cTitleDemoItem
    Profile::cResType_Course,       // ProfileID::c259
    Profile::cResType_Course,       // ProfileID::c25A
    Profile::cResType_Course,       // ProfileID::c25B
    Profile::cResType_Course,       // ProfileID::c25C
    Profile::cResType_Course,       // ProfileID::c25D
    Profile::cResType_Course,       // ProfileID::c25E
    Profile::cResType_Course,       // ProfileID::c25F
    Profile::cResType_Course,       // ProfileID::c260
    Profile::cResType_Course,       // ProfileID::c261
    Profile::cResType_Course,       // ProfileID::c262
    Profile::cResType_Course,       // ProfileID::c263
    Profile::cResType_Course,       // ProfileID::c264
    Profile::cResType_Course,       // ProfileID::c265
    Profile::cResType_Course,       // ProfileID::c266
    Profile::cResType_Course,       // ProfileID::c267
    Profile::cResType_Course,       // ProfileID::c268
    Profile::cResType_Course,       // ProfileID::cSpanner
    Profile::cResType_Course,       // ProfileID::c26A
    Profile::cResType_Course,       // ProfileID::c26B
    Profile::cResType_Course,       // ProfileID::c26C
    Profile::cResType_Course,       // ProfileID::c26D
    Profile::cResType_Course,       // ProfileID::c26E
    Profile::cResType_Course,       // ProfileID::c26F
    Profile::cResType_Course,       // ProfileID::c270
    Profile::cResType_Course,       // ProfileID::c271
    Profile::cResType_Course,       // ProfileID::c272
    Profile::cResType_Boot,         // ProfileID::c273
    Profile::cResType_Boot,         // ProfileID::c274
    Profile::cResType_Boot,         // ProfileID::c275
    Profile::cResType_Boot,         // ProfileID::c276
    Profile::cResType_Boot,         // ProfileID::c277
    Profile::cResType_Course,       // ProfileID::c278
    Profile::cResType_Course,       // ProfileID::c279
    Profile::cResType_Course,       // ProfileID::cWakiSearchMagKiller
    Profile::cResType_Course,       // ProfileID::c27B
    Profile::cResType_Course,       // ProfileID::c27C
    Profile::cResType_Course,       // ProfileID::c27D
    Profile::cResType_Course,       // ProfileID::c27E
    Profile::cResType_Course,       // ProfileID::c27F
    Profile::cResType_Course,       // ProfileID::cGabonRock
    Profile::cResType_Course,       // ProfileID::c281
    Profile::cResType_Course,       // ProfileID::c282
    Profile::cResType_Course,       // ProfileID::cRockGabonRock
    Profile::cResType_Course,       // ProfileID::c284
    Profile::cResType_Course,       // ProfileID::cSeichanSnowBall
    Profile::cResType_Course,       // ProfileID::c286
    Profile::cResType_Course,       // ProfileID::c287
    Profile::cResType_Course,       // ProfileID::c288
    Profile::cResType_Course,       // ProfileID::c289
    Profile::cResType_Course,       // ProfileID::c28A
    Profile::cResType_Course,       // ProfileID::c28B
    Profile::cResType_Course,       // ProfileID::c28C
    Profile::cResType_Course,       // ProfileID::c28D
    Profile::cResType_Course,       // ProfileID::c28E
    Profile::cResType_Course,       // ProfileID::c28F
    Profile::cResType_Course,       // ProfileID::c290
    Profile::cResType_Course,       // ProfileID::c291
    Profile::cResType_Course,       // ProfileID::c292
    Profile::cResType_Course,       // ProfileID::c293
    Profile::cResType_Course,       // ProfileID::c294
    Profile::cResType_Course,       // ProfileID::c295
    Profile::cResType_Course,       // ProfileID::c296
    Profile::cResType_Course,       // ProfileID::c297
    Profile::cResType_Course,       // ProfileID::c298
    Profile::cResType_Course,       // ProfileID::c299
    Profile::cResType_Course,       // ProfileID::c29A
    Profile::cResType_Course,       // ProfileID::c29B
    Profile::cResType_Course,       // ProfileID::c29C
    Profile::cResType_Course,       // ProfileID::c29D
    Profile::cResType_Course,       // ProfileID::c29E
    Profile::cResType_Course,       // ProfileID::c29F
    Profile::cResType_Course,       // ProfileID::c2A0
    Profile::cResType_Course,       // ProfileID::c2A1
    Profile::cResType_Course,       // ProfileID::c2A2
    Profile::cResType_Course,       // ProfileID::c2A3
    Profile::cResType_Course,       // ProfileID::c2A4
    Profile::cResType_Course,       // ProfileID::c2A5
    Profile::cResType_Course,       // ProfileID::cBun
    Profile::cResType_Course,       // ProfileID::cBunW2
    Profile::cResType_Course,       // ProfileID::cBunW3
    Profile::cResType_Course,       // ProfileID::cBunW4
    Profile::cResType_Course,       // ProfileID::cBunW5
    Profile::cResType_Course,       // ProfileID::cBunW6
    Profile::cResType_Course,       // ProfileID::cBunDemo
    Profile::cResType_Course,       // ProfileID::cKokoopaDemo
    Profile::cResType_Course,       // ProfileID::cKoopaJrDemo
    Profile::cResType_Course,       // ProfileID::cKameckDemo
    Profile::cResType_Course,       // ProfileID::cBossKKDemo
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJrDemo
    Profile::cResType_Course,       // ProfileID::cKoopaDemo
    Profile::cResType_Course,       // ProfileID::cFinalKoopaDemo
    Profile::cResType_Course,       // ProfileID::cPeachDemo
    Profile::cResType_Course,       // ProfileID::cLarry
    Profile::cResType_Course,       // ProfileID::cKokoopaSearchFire
    Profile::cResType_Course,       // ProfileID::cLemmy
    Profile::cResType_Course,       // ProfileID::cMorton
    Profile::cResType_Course,       // ProfileID::cMortonSanbo
    Profile::cResType_Course,       // ProfileID::cMortonSanboParts
    Profile::cResType_Course,       // ProfileID::cWendy
    Profile::cResType_Course,       // ProfileID::cWendyRing
    Profile::cResType_Course,       // ProfileID::cLudwig
    Profile::cResType_Course,       // ProfileID::cLudwigAlterEgo
    Profile::cResType_Course,       // ProfileID::cIggy
    Profile::cResType_Course,       // ProfileID::cIggyMagic
    Profile::cResType_Course,       // ProfileID::cWoogan
    Profile::cResType_Course,       // ProfileID::cRoy
    Profile::cResType_Course,       // ProfileID::cRoyLiftWaki
    Profile::cResType_Course,       // ProfileID::cBossKK
    Profile::cResType_Course,       // ProfileID::cBossKKThunder
    Profile::cResType_Course,       // ProfileID::cKameck
    Profile::cResType_Course,       // ProfileID::cKameckIceConfig
    Profile::cResType_Course,       // ProfileID::cKameckWarpPos
    Profile::cResType_Course,       // ProfileID::cKameckMagic
    Profile::cResType_Course,       // ProfileID::cPeachFinalCastleKoopaJr
    Profile::cResType_Course,       // ProfileID::cKoopa
    Profile::cResType_Course,       // ProfileID::cKoopaFireWaki
    Profile::cResType_Course,       // ProfileID::cKoopaFire
    Profile::cResType_Course,       // ProfileID::cDemoKoopaJrClown
    Profile::cResType_Course,       // ProfileID::cDemoKoopaJr
    Profile::cResType_Course,       // ProfileID::cBunDemoKameck
    Profile::cResType_Course,       // ProfileID::cKoopaDemoKameck
    Profile::cResType_Course,       // ProfileID::cBossKKDemoKameck
    Profile::cResType_Course,       // ProfileID::cBossKKDemoKK
    Profile::cResType_Course,       // ProfileID::cFinalKoopaFire
    Profile::cResType_Course,       // ProfileID::cFinalKoopaJr
    Profile::cResType_Course,       // ProfileID::cFinalKoopaJrFire
    Profile::cResType_Course,       // ProfileID::cFinalBomhei
    Profile::cResType_Course,       // ProfileID::cKokoopaShipLemmy
    Profile::cResType_Course,       // ProfileID::cKokoopaShipMorton
    Profile::cResType_Course,       // ProfileID::cKokoopaShipLarry
    Profile::cResType_Course,       // ProfileID::cKokoopaShipWendy
    Profile::cResType_Course,       // ProfileID::cKokoopaShipIggy
    Profile::cResType_Course,       // ProfileID::cKokoopaShipRoy
    Profile::cResType_Course,       // ProfileID::cKokoopaShipLudwig
    Profile::cResType_Course,       // ProfileID::cPeach
    Profile::cResType_Course,       // ProfileID::c2E0
    Profile::cResType_Course,       // ProfileID::cFinalDVPeach
    Profile::cResType_Course,       // ProfileID::cFinalDVShutter
    Profile::cResType_Course,       // ProfileID::c2E3
    Profile::cResType_Course,       // ProfileID::c2E4
    Profile::cResType_Course,       // ProfileID::c2E5
    Profile::cResType_Course,       // ProfileID::c2E6
    Profile::cResType_Course,       // ProfileID::c2E7
    Profile::cResType_Course,       // ProfileID::c2E8
    Profile::cResType_Course,       // ProfileID::c2E9
    Profile::cResType_Course,       // ProfileID::c2EA
    Profile::cResType_Boot,         // ProfileID::c2EB
    Profile::cResType_Boot,         // ProfileID::c2EC
    Profile::cResType_Boot,         // ProfileID::c2ED
    Profile::cResType_Course,       // ProfileID::c2EE
    Profile::cResType_Course,       // ProfileID::c2EF
    Profile::cResType_Course,       // ProfileID::c2F0
    Profile::cResType_Course,       // ProfileID::c2F1
    Profile::cResType_Course,       // ProfileID::c2F2
    Profile::cResType_Course,       // ProfileID::c2F3
    Profile::cResType_Course,       // ProfileID::c2F4
    Profile::cResType_Course,       // ProfileID::c2F5
    Profile::cResType_Course,       // ProfileID::cHammer
    Profile::cResType_Course,       // ProfileID::c2F7
    Profile::cResType_Course,       // ProfileID::cBoomerang
    Profile::cResType_Course,       // ProfileID::c2F9
    Profile::cResType_Course,       // ProfileID::cFireBallBros
    Profile::cResType_Course,       // ProfileID::c2FB
    Profile::cResType_Course,       // ProfileID::cIceBallBros
    Profile::cResType_Course,       // ProfileID::c2FD
    Profile::cResType_Course,       // ProfileID::cMegaHammer
    Profile::cResType_Course,       // ProfileID::c2FF
    Profile::cResType_Course,       // ProfileID::c300
    Profile::cResType_Course,       // ProfileID::c301
    Profile::cResType_Course,       // ProfileID::c302
    Profile::cResType_Course,       // ProfileID::c303
    Profile::cResType_Course,       // ProfileID::c304
    Profile::cResType_Course,       // ProfileID::c305
    Profile::cResType_Course,       // ProfileID::c306
    Profile::cResType_Course,       // ProfileID::c307
    Profile::cResType_Course,       // ProfileID::c308
    Profile::cResType_Course,       // ProfileID::c309
    Profile::cResType_Course,       // ProfileID::c30A
    Profile::cResType_Course,       // ProfileID::c30B
    Profile::cResType_Course,       // ProfileID::c30C
    Profile::cResType_Course,       // ProfileID::c30D
    Profile::cResType_Boot,         // ProfileID::c30E
    Profile::cResType_Course,       // ProfileID::c30F
    Profile::cResType_Course,       // ProfileID::c310
    Profile::cResType_Course,       // ProfileID::c311
    Profile::cResType_Course,       // ProfileID::c312
    Profile::cResType_Course,       // ProfileID::c313
    Profile::cResType_Course,       // ProfileID::c314
    Profile::cResType_Course,       // ProfileID::c315
    Profile::cResType_Boot,         // ProfileID::c316
    Profile::cResType_Boot,         // ProfileID::c317
    Profile::cResType_Boot,         // ProfileID::c318
    Profile::cResType_Course,       // ProfileID::c319
    Profile::cResType_Course,       // ProfileID::c31A
    Profile::cResType_Course,       // ProfileID::c31B
    Profile::cResType_Course,       // ProfileID::c31C
    Profile::cResType_Course,       // ProfileID::c31D
    Profile::cResType_Course,       // ProfileID::c31E
    Profile::cResType_Course,       // ProfileID::c31F
    Profile::cResType_Course,       // ProfileID::c320
    Profile::cResType_Course,       // ProfileID::c321
    Profile::cResType_Course,       // ProfileID::c322
    Profile::cResType_Course,       // ProfileID::c323
    Profile::cResType_Course,       // ProfileID::c324
    Profile::cResType_Course,       // ProfileID::c325
    Profile::cResType_Course,       // ProfileID::c326
    Profile::cResType_Boot,         // ProfileID::c327
    Profile::cResType_Course,       // ProfileID::c328
    Profile::cResType_Boot,         // ProfileID::cBattleItem
    Profile::cResType_Boot,         // ProfileID::c32A
    Profile::cResType_Boot,         // ProfileID::cVsBattleItem
    Profile::cResType_Course,       // ProfileID::c32C
    Profile::cResType_Course,       // ProfileID::c32D
    Profile::cResType_Course,       // ProfileID::c32E
    Profile::cResType_Course,       // ProfileID::c32F
    Profile::cResType_Course,       // ProfileID::c330
    Profile::cResType_Course,       // ProfileID::c331
    Profile::cResType_Course,       // ProfileID::cKoopaJrFire
    Profile::cResType_Course,       // ProfileID::cKoopaJrBall
    Profile::cResType_Course,       // ProfileID::cUnderwaterKoopaJr
    Profile::cResType_Course,       // ProfileID::cUnderwaterKoopaJrClown
    Profile::cResType_Course,       // ProfileID::cUnderwaterKoopaJrRetreatPos
    Profile::cResType_Course,       // ProfileID::cBoxingKoopaJr
    Profile::cResType_Course,       // ProfileID::cBoxingKoopaJrPostBattleDemo
    Profile::cResType_Course,       // ProfileID::cBoxingKoopaJrClownPostBattleDemo
    Profile::cResType_Course,       // ProfileID::cMiniGamePanelItem
    Profile::cResType_Course,       // ProfileID::cSlotItem
    Profile::cResType_Course,       // ProfileID::cCoinmakiCannon
    Profile::cResType_Course,       // ProfileID::cCoinmakiItem
    Profile::cResType_Course,       // ProfileID::cMiniGameKinopio
    Profile::cResType_Course,       // ProfileID::c33F
    Profile::cResType_Course,       // ProfileID::c340
    Profile::cResType_Course,       // ProfileID::c341
    Profile::cResType_Course,       // ProfileID::c342
    Profile::cResType_Course,       // ProfileID::c343
    Profile::cResType_Course,       // ProfileID::c344
    Profile::cResType_Course,       // ProfileID::c345
    Profile::cResType_Course,       // ProfileID::c346
    Profile::cResType_Course,       // ProfileID::c347
    Profile::cResType_Course,       // ProfileID::cStaffCreditChibiYoshiABC
    Profile::cResType_Course,       // ProfileID::cStaffCreditChibiYoshiBalloon
    Profile::cResType_Course,       // ProfileID::cStaffCreditChibiYoshiBalloonCheer
    Profile::cResType_Course,       // ProfileID::cStaffCreditChibiYoshiLight
    Profile::cResType_Course,       // ProfileID::cStaffCreditChibiYoshiLightCheer
    Profile::cResType_Course,       // ProfileID::cStaffCreditSoapABC
    Profile::cResType_Course,       // ProfileID::cStaffCreditSoapCoin
    Profile::cResType_Course,       // ProfileID::cStaffCreditTottenKun
    Profile::cResType_Course,       // ProfileID::c350
    Profile::cResType_Course,       // ProfileID::c351
    Profile::cResType_Boot,         // ProfileID::c352
    Profile::cResType_Course,       // ProfileID::c353
    Profile::cResType_Boot,         // ProfileID::cRealizeFeverStar
    Profile::cResType_Boot,         // ProfileID::cStar
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPlayer
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPlayer2PSub
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectChibiYoshi
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectCamera
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectCastle
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectToride
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectKinokoHouse1up
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectKinokoHouseShuffle
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectKinokoHouseSlot
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPeachGates1st
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPeachGates2nd
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectCoursePoint
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectWorldMoveDokan
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW8Cloud
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectGhost
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW2Bros
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW1
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW2
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW3
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW4
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW5
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW6
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW7
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW8
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShipW8Broken
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectSurrender
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectSwitchA
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectSwitchB
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectTeresa
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectOpeningKameck
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectTorideBoss
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPakkun
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShadowFirstDemoKinopio
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectTobiPuku
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectChorobon
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW7Item
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW5Teresa
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectFlag
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectMusasabi
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectWPillar
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW7Bridge
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectMiiBalloon
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPenguin
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW4Item
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW2Kuribo
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPakkunBig
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShadowKunIcon
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectDekaUnira
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectTomb
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectShadowFirstDemoShadowKun
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectKotsuCoaster
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectKoopaJr
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectPeach
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectW1Item
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectStarGate
    Profile::cResType_CourseSelect, // ProfileID::cCourseSelectEventAssistant
    Profile::cResType_Course,       // Profile 910
    Profile::cResType_Course,       // Profile 911
    Profile::cResType_Course        // Profile 912
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

static const sead::SafeString cRes_035[]  = {
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

static const sead::SafeString cRes_03C[]  = {
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

static const sead::SafeString cRes_04D[]  = {
    "lift_kinoko_sora"
};

static const sead::SafeString cRes_04E[]  = {
    "lift_kinoko_sora"
};

static const sead::SafeString cRes_04F[]  = {
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

static const sead::SafeString cRes_05A[]  = {
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

static const sead::SafeString cRes_065[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_066[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_067[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_068[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_069[]  = {
    "killer_houdai",
    "killer"
};

static const sead::SafeString cRes_06A[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_06B[]  = {
    "killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_06C[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_06D[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_06E[]  = {
    "R_killer_mag_houdai",
    "killer_mag"
};

static const sead::SafeString cRes_06F[]  = {
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

static const sead::SafeString cRes_079[]  = {
    "sandpillar"
};

static const sead::SafeString cRes_07A[]  = {
    "sandpillar"
};

static const sead::SafeString cRes_07B[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_07C[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_07D[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_07E[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_07F[]  = {
    "waterpillar"
};

static const sead::SafeString cRes_080[]  = {
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

static const sead::SafeString cRes_086[]  = {
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

static const sead::SafeString cRes_0B8[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_0B9[]  = {
    "lift_torokko"
};

static const sead::SafeString cRes_0BA[]  = {
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

static const sead::SafeString cRes_0C2[]  = {
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

static const sead::SafeString cRes_0E0[]  = {
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

static const sead::SafeString cRes_0ED[]  = {
    "ice"
};

static const sead::SafeString cRes_0EE[]  = {
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

static const sead::SafeString cRes_135[]  = {
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

static const sead::SafeString cRes_150[]  = {
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

static const sead::SafeString cRes_154[]  = {
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

static const sead::SafeString cRes_158[]  = {
    "switch"
};

static const sead::SafeString cRes_159[]  = {
    "switch"
};

static const sead::SafeString cRes_15A[]  = {
    "switch"
};

static const sead::SafeString cRes_15B[]  = {
    "switch"
};

static const sead::SafeString cRes_15D[]  = {
    "switch_koopa"
};

static const sead::SafeString cRes_15E[]  = {
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

static const sead::SafeString cRes_16A[]  = {
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

static const sead::SafeString cRes_177[]  = {
    "center_firebar",
    "firebar_L"
};

static const sead::SafeString cRes_178[]  = {
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

static const sead::SafeString cRes_18B[]  = {
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

static const sead::SafeString cRes_1A9[]  = {
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

static const sead::SafeString cRes_200[]  = {
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

static const sead::SafeString cRes_20C[]  = {
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

static const sead::SafeString cRes_231[]  = {
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

static const sead::SafeString cRes_23E[]  = {
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

static const sead::SafeString cRes_28A[]  = {
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

static const sead::SafeString cRes_28E[]  = {
    "bubble"
};

static const sead::SafeString cRes_28F[]  = {
    "bubble"
};

static const sead::SafeString cRes_290[]  = {
    "bubble"
};

static const sead::SafeString cRes_291[]  = {
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

const u8 Profile::cResNum[cProfileID_Max] = {
    0,                                                          // ProfileID::c000
    0,                                                          // ProfileID::c001
    0,                                                          // ProfileID::c002
    0,                                                          // ProfileID::c003
    0,                                                          // ProfileID::c004
    0,                                                          // ProfileID::c005
    0,                                                          // ProfileID::c006
    0,                                                          // ProfileID::c007
    0,                                                          // ProfileID::c008
    0,                                                          // ProfileID::c009
    0,                                                          // ProfileID::c00A
    0,                                                          // ProfileID::c00B
    0,                                                          // ProfileID::c00C
    0,                                                          // ProfileID::c00D
    0,                                                          // ProfileID::c00E
    0,                                                          // ProfileID::c00F
    0,                                                          // ProfileID::c010
    0,                                                          // ProfileID::c011
    0,                                                          // ProfileID::c012
    0,                                                          // ProfileID::c013
    0,                                                          // ProfileID::c014
    GetResNum(cRes_015),                                        // ProfileID::c015
    GetResNum(cRes_016),                                        // ProfileID::c016
    GetResNum(cRes_017),                                        // ProfileID::c017
    GetResNum(cRes_MiniGameMgr),                                // ProfileID::cMiniGameMgr
    GetResNum(cRes_MiniGameMgrRDash),                           // ProfileID::cMiniGameMgrRDash
    0,                                                          // ProfileID::cShuffleBlockMgr
    0,                                                          // ProfileID::cSlotMgr
    0,                                                          // ProfileID::cCoinmakiMgr
    0,                                                          // ProfileID::c01D
    0,                                                          // ProfileID::c01E
    0,                                                          // ProfileID::c01F
    0,                                                          // ProfileID::c020
    GetResNum(cRes_ShootingStar),                               // ProfileID::cShootingStar
    GetResNum(cRes_StaffRollMgr),                               // ProfileID::cStaffRollMgr
    GetResNum(cRes_StaffRollMgrRDash),                          // ProfileID::cStaffRollMgrRDash
    GetResNum(cRes_024),                                        // ProfileID::c024
    0,                                                          // ProfileID::c025
    GetResNum(cRes_026),                                        // ProfileID::c026
    0,                                                          // ProfileID::c027
    0,                                                          // ProfileID::c028
    0,                                                          // ProfileID::c029
    0,                                                          // ProfileID::c02A
    GetResNum(cRes_02B),                                        // ProfileID::c02B
    GetResNum(cRes_02C),                                        // ProfileID::c02C
    GetResNum(cRes_02D),                                        // ProfileID::c02D
    GetResNum(cRes_02E),                                        // ProfileID::c02E
    0,                                                          // ProfileID::c02F
    0,                                                          // ProfileID::c030
    0,                                                          // ProfileID::c031
    GetResNum(cRes_032),                                        // ProfileID::c032
    GetResNum(cRes_033),                                        // ProfileID::c033
    0,                                                          // ProfileID::c034
    GetResNum(cRes_035),                                        // ProfileID::c035
    GetResNum(cRes_036),                                        // ProfileID::c036
    GetResNum(cRes_037),                                        // ProfileID::c037
    GetResNum(cRes_038),                                        // ProfileID::c038
    GetResNum(cRes_039),                                        // ProfileID::c039
    GetResNum(cRes_03A),                                        // ProfileID::c03A
    GetResNum(cRes_03B),                                        // ProfileID::c03B
    GetResNum(cRes_03C),                                        // ProfileID::c03C
    GetResNum(cRes_03D),                                        // ProfileID::c03D
    GetResNum(cRes_03E),                                        // ProfileID::c03E
    GetResNum(cRes_03F),                                        // ProfileID::c03F
    GetResNum(cRes_040),                                        // ProfileID::c040
    GetResNum(cRes_041),                                        // ProfileID::c041
    GetResNum(cRes_042),                                        // ProfileID::c042
    GetResNum(cRes_043),                                        // ProfileID::c043
    GetResNum(cRes_044),                                        // ProfileID::c044
    GetResNum(cRes_045),                                        // ProfileID::c045
    GetResNum(cRes_046),                                        // ProfileID::c046
    GetResNum(cRes_047),                                        // ProfileID::c047
    GetResNum(cRes_048),                                        // ProfileID::c048
    GetResNum(cRes_049),                                        // ProfileID::c049
    GetResNum(cRes_04A),                                        // ProfileID::c04A
    GetResNum(cRes_04B),                                        // ProfileID::c04B
    GetResNum(cRes_04C),                                        // ProfileID::c04C
    GetResNum(cRes_04D),                                        // ProfileID::c04D
    GetResNum(cRes_04E),                                        // ProfileID::c04E
    GetResNum(cRes_04F),                                        // ProfileID::c04F
    GetResNum(cRes_050),                                        // ProfileID::c050
    GetResNum(cRes_051),                                        // ProfileID::c051
    GetResNum(cRes_052),                                        // ProfileID::c052
    GetResNum(cRes_053),                                        // ProfileID::c053
    GetResNum(cRes_054),                                        // ProfileID::c054
    GetResNum(cRes_055),                                        // ProfileID::c055
    GetResNum(cRes_056),                                        // ProfileID::c056
    GetResNum(cRes_057),                                        // ProfileID::c057
    GetResNum(cRes_058),                                        // ProfileID::c058
    GetResNum(cRes_059),                                        // ProfileID::c059
    GetResNum(cRes_05A),                                        // ProfileID::c05A
    GetResNum(cRes_05B),                                        // ProfileID::c05B
    GetResNum(cRes_05C),                                        // ProfileID::c05C
    0,                                                          // ProfileID::c05D
    0,                                                          // ProfileID::c05E
    GetResNum(cRes_05F),                                        // ProfileID::c05F
    GetResNum(cRes_060),                                        // ProfileID::c060
    GetResNum(cRes_061),                                        // ProfileID::c061
    GetResNum(cRes_062),                                        // ProfileID::c062
    GetResNum(cRes_063),                                        // ProfileID::c063
    GetResNum(cRes_064),                                        // ProfileID::c064
    GetResNum(cRes_065),                                        // ProfileID::c065
    GetResNum(cRes_066),                                        // ProfileID::c066
    GetResNum(cRes_067),                                        // ProfileID::c067
    GetResNum(cRes_068),                                        // ProfileID::c068
    GetResNum(cRes_069),                                        // ProfileID::c069
    GetResNum(cRes_06A),                                        // ProfileID::c06A
    GetResNum(cRes_06B),                                        // ProfileID::c06B
    GetResNum(cRes_06C),                                        // ProfileID::c06C
    GetResNum(cRes_06D),                                        // ProfileID::c06D
    GetResNum(cRes_06E),                                        // ProfileID::c06E
    GetResNum(cRes_06F),                                        // ProfileID::c06F
    GetResNum(cRes_070),                                        // ProfileID::c070
    GetResNum(cRes_071),                                        // ProfileID::c071
    GetResNum(cRes_072),                                        // ProfileID::c072
    GetResNum(cRes_073),                                        // ProfileID::c073
    GetResNum(cRes_074),                                        // ProfileID::c074
    GetResNum(cRes_075),                                        // ProfileID::c075
    GetResNum(cRes_076),                                        // ProfileID::c076
    GetResNum(cRes_077),                                        // ProfileID::c077
    0,                                                          // ProfileID::c078
    GetResNum(cRes_079),                                        // ProfileID::c079
    GetResNum(cRes_07A),                                        // ProfileID::c07A
    GetResNum(cRes_07B),                                        // ProfileID::c07B
    GetResNum(cRes_07C),                                        // ProfileID::c07C
    GetResNum(cRes_07D),                                        // ProfileID::c07D
    GetResNum(cRes_07E),                                        // ProfileID::c07E
    GetResNum(cRes_07F),                                        // ProfileID::c07F
    GetResNum(cRes_080),                                        // ProfileID::c080
    GetResNum(cRes_081),                                        // ProfileID::c081
    GetResNum(cRes_082),                                        // ProfileID::c082
    GetResNum(cRes_083),                                        // ProfileID::c083
    GetResNum(cRes_084),                                        // ProfileID::c084
    GetResNum(cRes_085),                                        // ProfileID::c085
    GetResNum(cRes_086),                                        // ProfileID::c086
    GetResNum(cRes_087),                                        // ProfileID::c087
    GetResNum(cRes_088),                                        // ProfileID::c088
    GetResNum(cRes_089),                                        // ProfileID::c089
    GetResNum(cRes_08A),                                        // ProfileID::c08A
    GetResNum(cRes_08B),                                        // ProfileID::c08B
    GetResNum(cRes_08C),                                        // ProfileID::c08C
    GetResNum(cRes_08D),                                        // ProfileID::c08D
    GetResNum(cRes_08E),                                        // ProfileID::c08E
    GetResNum(cRes_08F),                                        // ProfileID::c08F
    GetResNum(cRes_090),                                        // ProfileID::c090
    GetResNum(cRes_091),                                        // ProfileID::c091
    GetResNum(cRes_092),                                        // ProfileID::c092
    GetResNum(cRes_093),                                        // ProfileID::c093
    GetResNum(cRes_094),                                        // ProfileID::c094
    GetResNum(cRes_095),                                        // ProfileID::c095
    GetResNum(cRes_096),                                        // ProfileID::c096
    GetResNum(cRes_097),                                        // ProfileID::c097
    GetResNum(cRes_098),                                        // ProfileID::c098
    GetResNum(cRes_099),                                        // ProfileID::c099
    0,                                                          // ProfileID::c09A
    GetResNum(cRes_09B),                                        // ProfileID::c09B
    GetResNum(cRes_09C),                                        // ProfileID::c09C
    GetResNum(cRes_09D),                                        // ProfileID::c09D
    GetResNum(cRes_09E),                                        // ProfileID::c09E
    GetResNum(cRes_09F),                                        // ProfileID::c09F
    GetResNum(cRes_0A0),                                        // ProfileID::c0A0
    GetResNum(cRes_0A1),                                        // ProfileID::c0A1
    GetResNum(cRes_0A2),                                        // ProfileID::c0A2
    GetResNum(cRes_0A3),                                        // ProfileID::c0A3
    GetResNum(cRes_0A4),                                        // ProfileID::c0A4
    GetResNum(cRes_0A5),                                        // ProfileID::c0A5
    GetResNum(cRes_0A6),                                        // ProfileID::c0A6
    GetResNum(cRes_0A7),                                        // ProfileID::c0A7
    GetResNum(cRes_0A8),                                        // ProfileID::c0A8
    GetResNum(cRes_0A9),                                        // ProfileID::c0A9
    GetResNum(cRes_0AA),                                        // ProfileID::c0AA
    GetResNum(cRes_0AB),                                        // ProfileID::c0AB
    GetResNum(cRes_0AC),                                        // ProfileID::c0AC
    GetResNum(cRes_0AD),                                        // ProfileID::c0AD
    GetResNum(cRes_0AE),                                        // ProfileID::c0AE
    GetResNum(cRes_0AF),                                        // ProfileID::c0AF
    GetResNum(cRes_0B0),                                        // ProfileID::c0B0
    GetResNum(cRes_0B1),                                        // ProfileID::c0B1
    GetResNum(cRes_0B2),                                        // ProfileID::c0B2
    GetResNum(cRes_0B3),                                        // ProfileID::c0B3
    GetResNum(cRes_0B4),                                        // ProfileID::c0B4
    GetResNum(cRes_0B5),                                        // ProfileID::c0B5
    GetResNum(cRes_0B6),                                        // ProfileID::c0B6
    GetResNum(cRes_0B7),                                        // ProfileID::c0B7
    GetResNum(cRes_0B8),                                        // ProfileID::c0B8
    GetResNum(cRes_0B9),                                        // ProfileID::c0B9
    GetResNum(cRes_0BA),                                        // ProfileID::c0BA
    GetResNum(cRes_0BB),                                        // ProfileID::c0BB
    GetResNum(cRes_0BC),                                        // ProfileID::c0BC
    GetResNum(cRes_0BD),                                        // ProfileID::c0BD
    GetResNum(cRes_0BE),                                        // ProfileID::c0BE
    GetResNum(cRes_0BF),                                        // ProfileID::c0BF
    GetResNum(cRes_0C0),                                        // ProfileID::c0C0
    GetResNum(cRes_0C1),                                        // ProfileID::c0C1
    GetResNum(cRes_0C2),                                        // ProfileID::c0C2
    GetResNum(cRes_0C3),                                        // ProfileID::c0C3
    GetResNum(cRes_0C4),                                        // ProfileID::c0C4
    GetResNum(cRes_0C5),                                        // ProfileID::c0C5
    GetResNum(cRes_0C6),                                        // ProfileID::c0C6
    GetResNum(cRes_0C7),                                        // ProfileID::c0C7
    GetResNum(cRes_0C8),                                        // ProfileID::c0C8
    GetResNum(cRes_0C9),                                        // ProfileID::c0C9
    GetResNum(cRes_0CA),                                        // ProfileID::c0CA
    GetResNum(cRes_0CB),                                        // ProfileID::c0CB
    GetResNum(cRes_0CC),                                        // ProfileID::c0CC
    GetResNum(cRes_0CD),                                        // ProfileID::c0CD
    GetResNum(cRes_0CE),                                        // ProfileID::c0CE
    GetResNum(cRes_0CF),                                        // ProfileID::c0CF
    GetResNum(cRes_0D0),                                        // ProfileID::c0D0
    GetResNum(cRes_0D1),                                        // ProfileID::c0D1
    GetResNum(cRes_FloorHoleDokan),                             // ProfileID::cFloorHoleDokan
    GetResNum(cRes_0D3),                                        // ProfileID::c0D3
    GetResNum(cRes_0D4),                                        // ProfileID::c0D4
    GetResNum(cRes_0D5),                                        // ProfileID::c0D5
    GetResNum(cRes_0D6),                                        // ProfileID::c0D6
    GetResNum(cRes_0D7),                                        // ProfileID::c0D7
    GetResNum(cRes_0D8),                                        // ProfileID::c0D8
    GetResNum(cRes_0D9),                                        // ProfileID::c0D9
    GetResNum(cRes_0DA),                                        // ProfileID::c0DA
    GetResNum(cRes_0DB),                                        // ProfileID::c0DB
    GetResNum(cRes_0DC),                                        // ProfileID::c0DC
    GetResNum(cRes_0DD),                                        // ProfileID::c0DD
    GetResNum(cRes_0DE),                                        // ProfileID::c0DE
    GetResNum(cRes_0DF),                                        // ProfileID::c0DF
    GetResNum(cRes_0E0),                                        // ProfileID::c0E0
    GetResNum(cRes_0E1),                                        // ProfileID::c0E1
    GetResNum(cRes_0E2),                                        // ProfileID::c0E2
    GetResNum(cRes_0E3),                                        // ProfileID::c0E3
    GetResNum(cRes_0E4),                                        // ProfileID::c0E4
    GetResNum(cRes_0E5),                                        // ProfileID::c0E5
    GetResNum(cRes_0E6),                                        // ProfileID::c0E6
    GetResNum(cRes_0E7),                                        // ProfileID::c0E7
    GetResNum(cRes_0E8),                                        // ProfileID::c0E8
    GetResNum(cRes_0E9),                                        // ProfileID::c0E9
    GetResNum(cRes_0EA),                                        // ProfileID::c0EA
    GetResNum(cRes_0EB),                                        // ProfileID::c0EB
    GetResNum(cRes_0EC),                                        // ProfileID::c0EC
    GetResNum(cRes_0ED),                                        // ProfileID::c0ED
    GetResNum(cRes_0EE),                                        // ProfileID::c0EE
    GetResNum(cRes_0EF),                                        // ProfileID::c0EF
    GetResNum(cRes_0F0),                                        // ProfileID::c0F0
    GetResNum(cRes_0F1),                                        // ProfileID::c0F1
    GetResNum(cRes_0F2),                                        // ProfileID::c0F2
    GetResNum(cRes_0F3),                                        // ProfileID::c0F3
    GetResNum(cRes_0F4),                                        // ProfileID::c0F4
    0,                                                          // ProfileID::c0F5
    GetResNum(cRes_0F6),                                        // ProfileID::c0F6
    GetResNum(cRes_0F7),                                        // ProfileID::c0F7
    GetResNum(cRes_0F8),                                        // ProfileID::c0F8
    GetResNum(cRes_0F9),                                        // ProfileID::c0F9
    GetResNum(cRes_0FA),                                        // ProfileID::c0FA
    GetResNum(cRes_0FB),                                        // ProfileID::c0FB
    GetResNum(cRes_0FC),                                        // ProfileID::c0FC
    GetResNum(cRes_0FD),                                        // ProfileID::c0FD
    GetResNum(cRes_0FE),                                        // ProfileID::c0FE
    GetResNum(cRes_0FF),                                        // ProfileID::c0FF
    GetResNum(cRes_100),                                        // ProfileID::c100
    GetResNum(cRes_101),                                        // ProfileID::c101
    GetResNum(cRes_102),                                        // ProfileID::c102
    GetResNum(cRes_103),                                        // ProfileID::c103
    GetResNum(cRes_104),                                        // ProfileID::c104
    GetResNum(cRes_ShuffleBlock),                               // ProfileID::cShuffleBlock
    GetResNum(cRes_KokoopaShipWarpCannon),                      // ProfileID::cKokoopaShipWarpCannon
    GetResNum(cRes_107),                                        // ProfileID::c107
    GetResNum(cRes_108),                                        // ProfileID::c108
    GetResNum(cRes_KoopaShutter),                               // ProfileID::cKoopaShutter
    GetResNum(cRes_10A),                                        // ProfileID::c10A
    GetResNum(cRes_10B),                                        // ProfileID::c10B
    GetResNum(cRes_10C),                                        // ProfileID::c10C
    GetResNum(cRes_PeachFinalCastleKoopaJrLift),                // ProfileID::cPeachFinalCastleKoopaJrLift
    GetResNum(cRes_PeachFinalCastleKoopaJrLiftHmove),           // ProfileID::cPeachFinalCastleKoopaJrLiftHmove
    GetResNum(cRes_PeachFinalCastleKoopaJrLiftPairObj),         // ProfileID::cPeachFinalCastleKoopaJrLiftPairObj
    GetResNum(cRes_RoyLiftWakiStep),                            // ProfileID::cRoyLiftWakiStep
    GetResNum(cRes_WendyFloor),                                 // ProfileID::cWendyFloor
    GetResNum(cRes_IggyRoom),                                   // ProfileID::cIggyRoom
    GetResNum(cRes_113),                                        // ProfileID::c113
    GetResNum(cRes_114),                                        // ProfileID::c114
    GetResNum(cRes_115),                                        // ProfileID::c115
    GetResNum(cRes_116),                                        // ProfileID::c116
    0,                                                          // ProfileID::c117
    GetResNum(cRes_118),                                        // ProfileID::c118
    GetResNum(cRes_119),                                        // ProfileID::c119
    GetResNum(cRes_11A),                                        // ProfileID::c11A
    GetResNum(cRes_11B),                                        // ProfileID::c11B
    0,                                                          // ProfileID::c11C
    GetResNum(cRes_11D),                                        // ProfileID::c11D
    GetResNum(cRes_11E),                                        // ProfileID::c11E
    0,                                                          // ProfileID::c11F
    0,                                                          // ProfileID::c120
    0,                                                          // ProfileID::c121
    0,                                                          // ProfileID::c122
    0,                                                          // ProfileID::c123
    0,                                                          // ProfileID::c124
    0,                                                          // ProfileID::c125
    0,                                                          // ProfileID::c126
    0,                                                          // ProfileID::c127
    0,                                                          // ProfileID::c128
    0,                                                          // ProfileID::c129
    0,                                                          // ProfileID::c12A
    0,                                                          // ProfileID::c12B
    0,                                                          // ProfileID::c12C
    0,                                                          // ProfileID::c12D
    0,                                                          // ProfileID::c12E
    0,                                                          // ProfileID::c12F
    0,                                                          // ProfileID::c130
    0,                                                          // ProfileID::c131
    0,                                                          // ProfileID::c132
    0,                                                          // ProfileID::c133
    0,                                                          // ProfileID::c134
    GetResNum(cRes_135),                                        // ProfileID::c135
    GetResNum(cRes_136),                                        // ProfileID::c136
    0,                                                          // ProfileID::c137
    GetResNum(cRes_138),                                        // ProfileID::c138
    0,                                                          // ProfileID::c139
    GetResNum(cRes_13A),                                        // ProfileID::c13A
    GetResNum(cRes_13B),                                        // ProfileID::c13B
    GetResNum(cRes_13C),                                        // ProfileID::c13C
    0,                                                          // ProfileID::c13D
    0,                                                          // ProfileID::c13E
    0,                                                          // ProfileID::c13F
    GetResNum(cRes_140),                                        // ProfileID::c140
    GetResNum(cRes_141),                                        // ProfileID::c141
    GetResNum(cRes_142),                                        // ProfileID::c142
    GetResNum(cRes_143),                                        // ProfileID::c143
    GetResNum(cRes_144),                                        // ProfileID::c144
    GetResNum(cRes_145),                                        // ProfileID::c145
    GetResNum(cRes_146),                                        // ProfileID::c146
    GetResNum(cRes_147),                                        // ProfileID::c147
    GetResNum(cRes_148),                                        // ProfileID::c148
    GetResNum(cRes_149),                                        // ProfileID::c149
    GetResNum(cRes_14A),                                        // ProfileID::c14A
    GetResNum(cRes_14B),                                        // ProfileID::c14B
    0,                                                          // ProfileID::c14C
    GetResNum(cRes_14D),                                        // ProfileID::c14D
    GetResNum(cRes_14E),                                        // ProfileID::c14E
    GetResNum(cRes_14F),                                        // ProfileID::c14F
    GetResNum(cRes_150),                                        // ProfileID::c150
    GetResNum(cRes_151),                                        // ProfileID::c151
    GetResNum(cRes_152),                                        // ProfileID::c152
    GetResNum(cRes_153),                                        // ProfileID::c153
    GetResNum(cRes_154),                                        // ProfileID::c154
    GetResNum(cRes_155),                                        // ProfileID::c155
    GetResNum(cRes_156),                                        // ProfileID::c156
    GetResNum(cRes_157),                                        // ProfileID::c157
    GetResNum(cRes_158),                                        // ProfileID::c158
    GetResNum(cRes_159),                                        // ProfileID::c159
    GetResNum(cRes_15A),                                        // ProfileID::c15A
    GetResNum(cRes_15B),                                        // ProfileID::c15B
    0,                                                          // ProfileID::c15C
    GetResNum(cRes_15D),                                        // ProfileID::c15D
    GetResNum(cRes_15E),                                        // ProfileID::c15E
    GetResNum(cRes_LemmyBall),                                  // ProfileID::cLemmyBall
    GetResNum(cRes_LemmyBomb),                                  // ProfileID::cLemmyBomb
    GetResNum(cRes_161),                                        // ProfileID::c161
    0,                                                          // ProfileID::c162
    GetResNum(cRes_163),                                        // ProfileID::c163
    GetResNum(cRes_164),                                        // ProfileID::c164
    GetResNum(cRes_165),                                        // ProfileID::c165
    GetResNum(cRes_166),                                        // ProfileID::c166
    GetResNum(cRes_167),                                        // ProfileID::c167
    GetResNum(cRes_168),                                        // ProfileID::c168
    GetResNum(cRes_169),                                        // ProfileID::c169
    GetResNum(cRes_16A),                                        // ProfileID::c16A
    GetResNum(cRes_16B),                                        // ProfileID::c16B
    GetResNum(cRes_16C),                                        // ProfileID::c16C
    GetResNum(cRes_16D),                                        // ProfileID::c16D
    GetResNum(cRes_16E),                                        // ProfileID::c16E
    GetResNum(cRes_16F),                                        // ProfileID::c16F
    GetResNum(cRes_KameckIce),                                  // ProfileID::cKameckIce
    GetResNum(cRes_WendyIcicle),                                // ProfileID::cWendyIcicle
    GetResNum(cRes_PeachFinalCastleKoopaJrClown),               // ProfileID::cPeachFinalCastleKoopaJrClown
    GetResNum(cRes_BoxingKoopaJrClown),                         // ProfileID::cBoxingKoopaJrClown
    GetResNum(cRes_174),                                        // ProfileID::c174
    GetResNum(cRes_FinalKoopaJrClown),                          // ProfileID::cFinalKoopaJrClown
    GetResNum(cRes_FinalKoopa),                                 // ProfileID::cFinalKoopa
    GetResNum(cRes_177),                                        // ProfileID::c177
    GetResNum(cRes_178),                                        // ProfileID::c178
    GetResNum(cRes_179),                                        // ProfileID::c179
    GetResNum(cRes_17A),                                        // ProfileID::c17A
    GetResNum(cRes_17B),                                        // ProfileID::c17B
    0,                                                          // ProfileID::c17C
    GetResNum(cRes_17D),                                        // ProfileID::c17D
    GetResNum(cRes_17E),                                        // ProfileID::c17E
    GetResNum(cRes_17F),                                        // ProfileID::c17F
    GetResNum(cRes_180),                                        // ProfileID::c180
    GetResNum(cRes_181),                                        // ProfileID::c181
    GetResNum(cRes_182),                                        // ProfileID::c182
    GetResNum(cRes_183),                                        // ProfileID::c183
    GetResNum(cRes_184),                                        // ProfileID::c184
    GetResNum(cRes_185),                                        // ProfileID::c185
    GetResNum(cRes_186),                                        // ProfileID::c186
    GetResNum(cRes_187),                                        // ProfileID::c187
    GetResNum(cRes_188),                                        // ProfileID::c188
    GetResNum(cRes_189),                                        // ProfileID::c189
    GetResNum(cRes_18A),                                        // ProfileID::c18A
    GetResNum(cRes_18B),                                        // ProfileID::c18B
    GetResNum(cRes_18C),                                        // ProfileID::c18C
    GetResNum(cRes_18D),                                        // ProfileID::c18D
    GetResNum(cRes_18E),                                        // ProfileID::c18E
    GetResNum(cRes_18F),                                        // ProfileID::c18F
    GetResNum(cRes_190),                                        // ProfileID::c190
    GetResNum(cRes_191),                                        // ProfileID::c191
    GetResNum(cRes_192),                                        // ProfileID::c192
    GetResNum(cRes_193),                                        // ProfileID::c193
    GetResNum(cRes_194),                                        // ProfileID::c194
    GetResNum(cRes_195),                                        // ProfileID::c195
    GetResNum(cRes_196),                                        // ProfileID::c196
    GetResNum(cRes_197),                                        // ProfileID::c197
    GetResNum(cRes_198),                                        // ProfileID::c198
    GetResNum(cRes_199),                                        // ProfileID::c199
    GetResNum(cRes_19A),                                        // ProfileID::c19A
    0,                                                          // ProfileID::c19B
    GetResNum(cRes_19C),                                        // ProfileID::c19C
    GetResNum(cRes_19D),                                        // ProfileID::c19D
    0,                                                          // ProfileID::c19E
    GetResNum(cRes_19F),                                        // ProfileID::c19F
    GetResNum(cRes_1A0),                                        // ProfileID::c1A0
    GetResNum(cRes_1A1),                                        // ProfileID::c1A1
    0,                                                          // ProfileID::c1A2
    GetResNum(cRes_1A3),                                        // ProfileID::c1A3
    GetResNum(cRes_1A4),                                        // ProfileID::c1A4
    GetResNum(cRes_1A5),                                        // ProfileID::c1A5
    GetResNum(cRes_1A6),                                        // ProfileID::c1A6
    GetResNum(cRes_1A7),                                        // ProfileID::c1A7
    GetResNum(cRes_1A8),                                        // ProfileID::c1A8
    GetResNum(cRes_1A9),                                        // ProfileID::c1A9
    GetResNum(cRes_1AA),                                        // ProfileID::c1AA
    GetResNum(cRes_1AB),                                        // ProfileID::c1AB
    GetResNum(cRes_1AC),                                        // ProfileID::c1AC
    GetResNum(cRes_1AD),                                        // ProfileID::c1AD
    GetResNum(cRes_1AE),                                        // ProfileID::c1AE
    GetResNum(cRes_1AF),                                        // ProfileID::c1AF
    GetResNum(cRes_1B0),                                        // ProfileID::c1B0
    GetResNum(cRes_1B1),                                        // ProfileID::c1B1
    GetResNum(cRes_1B2),                                        // ProfileID::c1B2
    GetResNum(cRes_1B3),                                        // ProfileID::c1B3
    0,                                                          // ProfileID::c1B4
    0,                                                          // ProfileID::c1B5
    GetResNum(cRes_CoinmakiCoin),                               // ProfileID::cCoinmakiCoin
    0,                                                          // ProfileID::c1B7
    0,                                                          // ProfileID::c1B8
    GetResNum(cRes_1B9),                                        // ProfileID::c1B9
    GetResNum(cRes_Yoshi),                                      // ProfileID::cYoshi
    GetResNum(cRes_TottenPlayer),                               // ProfileID::cTottenPlayer
    GetResNum(cRes_PlayerObject),                               // ProfileID::cPlayerObject
    GetResNum(cRes_1BD),                                        // ProfileID::c1BD
    GetResNum(cRes_1BE),                                        // ProfileID::c1BE
    GetResNum(cRes_1BF),                                        // ProfileID::c1BF
    GetResNum(cRes_1C0),                                        // ProfileID::c1C0
    GetResNum(cRes_1C1),                                        // ProfileID::c1C1
    GetResNum(cRes_1C2),                                        // ProfileID::c1C2
    GetResNum(cRes_1C3),                                        // ProfileID::c1C3
    0,                                                          // ProfileID::c1C4
    GetResNum(cRes_SlotYoshiChibi),                             // ProfileID::cSlotYoshiChibi
    GetResNum(cRes_1C6),                                        // ProfileID::c1C6
    0,                                                          // ProfileID::c1C7
    GetResNum(cRes_1C8),                                        // ProfileID::c1C8
    0,                                                          // ProfileID::c1C9
    0,                                                          // ProfileID::c1CA
    GetResNum(cRes_1CB),                                        // ProfileID::c1CB
    GetResNum(cRes_1CC),                                        // ProfileID::c1CC
    0,                                                          // ProfileID::c1CD
    GetResNum(cRes_1CE),                                        // ProfileID::c1CE
    GetResNum(cRes_QuestPrizeItem),                             // ProfileID::cQuestPrizeItem
    GetResNum(cRes_1D0),                                        // ProfileID::c1D0
    GetResNum(cRes_1D1),                                        // ProfileID::c1D1
    GetResNum(cRes_1D2),                                        // ProfileID::c1D2
    GetResNum(cRes_1D3),                                        // ProfileID::c1D3
    GetResNum(cRes_1D4),                                        // ProfileID::c1D4
    GetResNum(cRes_1D5),                                        // ProfileID::c1D5
    GetResNum(cRes_1D6),                                        // ProfileID::c1D6
    GetResNum(cRes_1D7),                                        // ProfileID::c1D7
    GetResNum(cRes_1D8),                                        // ProfileID::c1D8
    GetResNum(cRes_1D9),                                        // ProfileID::c1D9
    0,                                                          // ProfileID::cIceBall
    0,                                                          // ProfileID::cIceBallPakkun
    0,                                                          // ProfileID::cFireBallPlayer
    0,                                                          // ProfileID::cFireBallPakkun
    0,                                                          // ProfileID::c1DE
    GetResNum(cRes_1DF),                                        // ProfileID::c1DF
    GetResNum(cRes_1E0),                                        // ProfileID::c1E0
    GetResNum(cRes_1E1),                                        // ProfileID::c1E1
    GetResNum(cRes_1E2),                                        // ProfileID::c1E2
    GetResNum(cRes_1E3),                                        // ProfileID::c1E3
    GetResNum(cRes_1E4),                                        // ProfileID::c1E4
    GetResNum(cRes_1E5),                                        // ProfileID::c1E5
    GetResNum(cRes_1E6),                                        // ProfileID::c1E6
    GetResNum(cRes_1E7),                                        // ProfileID::c1E7
    GetResNum(cRes_1E8),                                        // ProfileID::c1E8
    GetResNum(cRes_1E9),                                        // ProfileID::c1E9
    GetResNum(cRes_1EA),                                        // ProfileID::c1EA
    GetResNum(cRes_1EB),                                        // ProfileID::c1EB
    GetResNum(cRes_1EC),                                        // ProfileID::c1EC
    GetResNum(cRes_1ED),                                        // ProfileID::c1ED
    GetResNum(cRes_1EE),                                        // ProfileID::c1EE
    GetResNum(cRes_1EF),                                        // ProfileID::c1EF
    GetResNum(cRes_1F0),                                        // ProfileID::c1F0
    GetResNum(cRes_1F1),                                        // ProfileID::c1F1
    GetResNum(cRes_1F2),                                        // ProfileID::c1F2
    GetResNum(cRes_1F3),                                        // ProfileID::c1F3
    GetResNum(cRes_1F4),                                        // ProfileID::c1F4
    GetResNum(cRes_1F5),                                        // ProfileID::c1F5
    GetResNum(cRes_1F6),                                        // ProfileID::c1F6
    GetResNum(cRes_1F7),                                        // ProfileID::c1F7
    GetResNum(cRes_1F8),                                        // ProfileID::c1F8
    GetResNum(cRes_1F9),                                        // ProfileID::c1F9
    GetResNum(cRes_1FA),                                        // ProfileID::c1FA
    GetResNum(cRes_1FB),                                        // ProfileID::c1FB
    GetResNum(cRes_1FC),                                        // ProfileID::c1FC
    GetResNum(cRes_1FD),                                        // ProfileID::c1FD
    GetResNum(cRes_1FE),                                        // ProfileID::c1FE
    0,                                                          // ProfileID::c1FF
    GetResNum(cRes_200),                                        // ProfileID::c200
    GetResNum(cRes_201),                                        // ProfileID::c201
    GetResNum(cRes_202),                                        // ProfileID::c202
    GetResNum(cRes_203),                                        // ProfileID::c203
    GetResNum(cRes_204),                                        // ProfileID::c204
    GetResNum(cRes_205),                                        // ProfileID::c205
    GetResNum(cRes_206),                                        // ProfileID::c206
    GetResNum(cRes_207),                                        // ProfileID::c207
    GetResNum(cRes_208),                                        // ProfileID::c208
    GetResNum(cRes_209),                                        // ProfileID::c209
    GetResNum(cRes_20A),                                        // ProfileID::c20A
    GetResNum(cRes_20B),                                        // ProfileID::c20B
    GetResNum(cRes_20C),                                        // ProfileID::c20C
    GetResNum(cRes_20D),                                        // ProfileID::c20D
    GetResNum(cRes_20E),                                        // ProfileID::c20E
    GetResNum(cRes_20F),                                        // ProfileID::c20F
    GetResNum(cRes_210),                                        // ProfileID::c210
    GetResNum(cRes_211),                                        // ProfileID::c211
    GetResNum(cRes_212),                                        // ProfileID::c212
    GetResNum(cRes_213),                                        // ProfileID::c213
    GetResNum(cRes_214),                                        // ProfileID::c214
    GetResNum(cRes_215),                                        // ProfileID::c215
    GetResNum(cRes_216),                                        // ProfileID::c216
    GetResNum(cRes_217),                                        // ProfileID::c217
    GetResNum(cRes_218),                                        // ProfileID::c218
    GetResNum(cRes_219),                                        // ProfileID::c219
    GetResNum(cRes_21A),                                        // ProfileID::c21A
    GetResNum(cRes_21B),                                        // ProfileID::c21B
    GetResNum(cRes_21C),                                        // ProfileID::c21C
    GetResNum(cRes_21D),                                        // ProfileID::c21D
    GetResNum(cRes_21E),                                        // ProfileID::c21E
    GetResNum(cRes_21F),                                        // ProfileID::c21F
    GetResNum(cRes_220),                                        // ProfileID::c220
    GetResNum(cRes_221),                                        // ProfileID::c221
    GetResNum(cRes_222),                                        // ProfileID::c222
    GetResNum(cRes_223),                                        // ProfileID::c223
    GetResNum(cRes_224),                                        // ProfileID::c224
    GetResNum(cRes_225),                                        // ProfileID::c225
    GetResNum(cRes_226),                                        // ProfileID::c226
    GetResNum(cRes_227),                                        // ProfileID::c227
    GetResNum(cRes_228),                                        // ProfileID::c228
    GetResNum(cRes_229),                                        // ProfileID::c229
    GetResNum(cRes_22A),                                        // ProfileID::c22A
    GetResNum(cRes_22B),                                        // ProfileID::c22B
    GetResNum(cRes_22C),                                        // ProfileID::c22C
    GetResNum(cRes_22D),                                        // ProfileID::c22D
    0,                                                          // ProfileID::cFireBallKeronpa
    0,                                                          // ProfileID::cFireBallKeronpaRDash
    GetResNum(cRes_230),                                        // ProfileID::c230
    GetResNum(cRes_231),                                        // ProfileID::c231
    GetResNum(cRes_232),                                        // ProfileID::c232
    GetResNum(cRes_233),                                        // ProfileID::c233
    GetResNum(cRes_234),                                        // ProfileID::c234
    GetResNum(cRes_235),                                        // ProfileID::c235
    GetResNum(cRes_236),                                        // ProfileID::c236
    GetResNum(cRes_237),                                        // ProfileID::c237
    GetResNum(cRes_238),                                        // ProfileID::c238
    GetResNum(cRes_239),                                        // ProfileID::c239
    GetResNum(cRes_23A),                                        // ProfileID::c23A
    GetResNum(cRes_23B),                                        // ProfileID::c23B
    GetResNum(cRes_23C),                                        // ProfileID::c23C
    GetResNum(cRes_23D),                                        // ProfileID::c23D
    GetResNum(cRes_23E),                                        // ProfileID::c23E
    0,                                                          // ProfileID::c23F
    0,                                                          // ProfileID::c240
    0,                                                          // ProfileID::c241
    0,                                                          // ProfileID::c242
    0,                                                          // ProfileID::c243
    0,                                                          // ProfileID::c244
    0,                                                          // ProfileID::c245
    0,                                                          // ProfileID::c246
    0,                                                          // ProfileID::c247
    0,                                                          // ProfileID::c248
    0,                                                          // ProfileID::c249
    0,                                                          // ProfileID::c24A
    0,                                                          // ProfileID::cBgCenter
    0,                                                          // ProfileID::c24C
    0,                                                          // ProfileID::c24D
    0,                                                          // ProfileID::c24E
    GetResNum(cRes_Kinoko),                                     // ProfileID::cKinoko
    GetResNum(cRes_FireFlower),                                 // ProfileID::cFireFlower
    GetResNum(cRes_MameKinoko),                                 // ProfileID::cMameKinoko
    GetResNum(cRes_IceFlower),                                  // ProfileID::cIceFlower
    GetResNum(cRes_Propeller),                                  // ProfileID::cPropeller
    GetResNum(cRes_Penguin),                                    // ProfileID::cPenguin
    GetResNum(cRes_OneUpKinoko),                                // ProfileID::cOneUpKinoko
    GetResNum(cRes_Musasabi),                                   // ProfileID::cMusasabi
    GetResNum(cRes_SuperMoon),                                  // ProfileID::cSuperMoon
    GetResNum(cRes_TitleDemoItem),                              // ProfileID::cTitleDemoItem
    GetResNum(cRes_259),                                        // ProfileID::c259
    GetResNum(cRes_25A),                                        // ProfileID::c25A
    GetResNum(cRes_25B),                                        // ProfileID::c25B
    GetResNum(cRes_25C),                                        // ProfileID::c25C
    GetResNum(cRes_25D),                                        // ProfileID::c25D
    GetResNum(cRes_25E),                                        // ProfileID::c25E
    GetResNum(cRes_25F),                                        // ProfileID::c25F
    GetResNum(cRes_260),                                        // ProfileID::c260
    GetResNum(cRes_261),                                        // ProfileID::c261
    GetResNum(cRes_262),                                        // ProfileID::c262
    GetResNum(cRes_263),                                        // ProfileID::c263
    GetResNum(cRes_264),                                        // ProfileID::c264
    GetResNum(cRes_265),                                        // ProfileID::c265
    GetResNum(cRes_266),                                        // ProfileID::c266
    GetResNum(cRes_267),                                        // ProfileID::c267
    GetResNum(cRes_268),                                        // ProfileID::c268
    GetResNum(cRes_Spanner),                                    // ProfileID::cSpanner
    GetResNum(cRes_26A),                                        // ProfileID::c26A
    GetResNum(cRes_26B),                                        // ProfileID::c26B
    GetResNum(cRes_26C),                                        // ProfileID::c26C
    GetResNum(cRes_26D),                                        // ProfileID::c26D
    GetResNum(cRes_26E),                                        // ProfileID::c26E
    GetResNum(cRes_26F),                                        // ProfileID::c26F
    GetResNum(cRes_270),                                        // ProfileID::c270
    GetResNum(cRes_271),                                        // ProfileID::c271
    GetResNum(cRes_272),                                        // ProfileID::c272
    0,                                                          // ProfileID::c273
    0,                                                          // ProfileID::c274
    0,                                                          // ProfileID::c275
    0,                                                          // ProfileID::c276
    0,                                                          // ProfileID::c277
    GetResNum(cRes_278),                                        // ProfileID::c278
    GetResNum(cRes_279),                                        // ProfileID::c279
    GetResNum(cRes_WakiSearchMagKiller),                        // ProfileID::cWakiSearchMagKiller
    GetResNum(cRes_27B),                                        // ProfileID::c27B
    GetResNum(cRes_27C),                                        // ProfileID::c27C
    GetResNum(cRes_27D),                                        // ProfileID::c27D
    GetResNum(cRes_27E),                                        // ProfileID::c27E
    GetResNum(cRes_27F),                                        // ProfileID::c27F
    GetResNum(cRes_GabonRock),                                  // ProfileID::cGabonRock
    GetResNum(cRes_281),                                        // ProfileID::c281
    GetResNum(cRes_282),                                        // ProfileID::c282
    GetResNum(cRes_RockGabonRock),                              // ProfileID::cRockGabonRock
    GetResNum(cRes_284),                                        // ProfileID::c284
    GetResNum(cRes_SeichanSnowBall),                            // ProfileID::cSeichanSnowBall
    GetResNum(cRes_286),                                        // ProfileID::c286
    GetResNum(cRes_287),                                        // ProfileID::c287
    GetResNum(cRes_288),                                        // ProfileID::c288
    GetResNum(cRes_289),                                        // ProfileID::c289
    GetResNum(cRes_28A),                                        // ProfileID::c28A
    GetResNum(cRes_28B),                                        // ProfileID::c28B
    GetResNum(cRes_28C),                                        // ProfileID::c28C
    GetResNum(cRes_28D),                                        // ProfileID::c28D
    GetResNum(cRes_28E),                                        // ProfileID::c28E
    GetResNum(cRes_28F),                                        // ProfileID::c28F
    GetResNum(cRes_290),                                        // ProfileID::c290
    GetResNum(cRes_291),                                        // ProfileID::c291
    GetResNum(cRes_292),                                        // ProfileID::c292
    GetResNum(cRes_293),                                        // ProfileID::c293
    GetResNum(cRes_294),                                        // ProfileID::c294
    GetResNum(cRes_295),                                        // ProfileID::c295
    GetResNum(cRes_296),                                        // ProfileID::c296
    GetResNum(cRes_297),                                        // ProfileID::c297
    GetResNum(cRes_298),                                        // ProfileID::c298
    GetResNum(cRes_299),                                        // ProfileID::c299
    GetResNum(cRes_29A),                                        // ProfileID::c29A
    GetResNum(cRes_29B),                                        // ProfileID::c29B
    0,                                                          // ProfileID::c29C
    GetResNum(cRes_29D),                                        // ProfileID::c29D
    GetResNum(cRes_29E),                                        // ProfileID::c29E
    GetResNum(cRes_29F),                                        // ProfileID::c29F
    GetResNum(cRes_2A0),                                        // ProfileID::c2A0
    GetResNum(cRes_2A1),                                        // ProfileID::c2A1
    GetResNum(cRes_2A2),                                        // ProfileID::c2A2
    GetResNum(cRes_2A3),                                        // ProfileID::c2A3
    GetResNum(cRes_2A4),                                        // ProfileID::c2A4
    GetResNum(cRes_2A5),                                        // ProfileID::c2A5
    GetResNum(cRes_Bun),                                        // ProfileID::cBun
    GetResNum(cRes_BunW2),                                      // ProfileID::cBunW2
    GetResNum(cRes_BunW3),                                      // ProfileID::cBunW3
    GetResNum(cRes_BunW4),                                      // ProfileID::cBunW4
    GetResNum(cRes_BunW5),                                      // ProfileID::cBunW5
    GetResNum(cRes_BunW6),                                      // ProfileID::cBunW6
    GetResNum(cRes_BunDemo),                                    // ProfileID::cBunDemo
    0,                                                          // ProfileID::cKokoopaDemo
    0,                                                          // ProfileID::cKoopaJrDemo
    0,                                                          // ProfileID::cKameckDemo
    GetResNum(cRes_BossKKDemo),                                 // ProfileID::cBossKKDemo
    0,                                                          // ProfileID::cPeachFinalCastleKoopaJrDemo
    GetResNum(cRes_KoopaDemo),                                  // ProfileID::cKoopaDemo
    0,                                                          // ProfileID::cFinalKoopaDemo
    0,                                                          // ProfileID::cPeachDemo
    GetResNum(cRes_Larry),                                      // ProfileID::cLarry
    GetResNum(cRes_KokoopaSearchFire),                          // ProfileID::cKokoopaSearchFire
    GetResNum(cRes_Lemmy),                                      // ProfileID::cLemmy
    GetResNum(cRes_Morton),                                     // ProfileID::cMorton
    GetResNum(cRes_MortonSanbo),                                // ProfileID::cMortonSanbo
    GetResNum(cRes_MortonSanboParts),                           // ProfileID::cMortonSanboParts
    GetResNum(cRes_Wendy),                                      // ProfileID::cWendy
    GetResNum(cRes_WendyRing),                                  // ProfileID::cWendyRing
    GetResNum(cRes_Ludwig),                                     // ProfileID::cLudwig
    GetResNum(cRes_LudwigAlterEgo),                             // ProfileID::cLudwigAlterEgo
    GetResNum(cRes_Iggy),                                       // ProfileID::cIggy
    0,                                                          // ProfileID::cIggyMagic
    GetResNum(cRes_Woogan),                                     // ProfileID::cWoogan
    GetResNum(cRes_Roy),                                        // ProfileID::cRoy
    GetResNum(cRes_RoyLiftWaki),                                // ProfileID::cRoyLiftWaki
    GetResNum(cRes_BossKK),                                     // ProfileID::cBossKK
    0,                                                          // ProfileID::cBossKKThunder
    GetResNum(cRes_Kameck),                                     // ProfileID::cKameck
    0,                                                          // ProfileID::cKameckIceConfig
    0,                                                          // ProfileID::cKameckWarpPos
    0,                                                          // ProfileID::cKameckMagic
    GetResNum(cRes_PeachFinalCastleKoopaJr),                    // ProfileID::cPeachFinalCastleKoopaJr
    GetResNum(cRes_Koopa),                                      // ProfileID::cKoopa
    GetResNum(cRes_KoopaFireWaki),                              // ProfileID::cKoopaFireWaki
    GetResNum(cRes_KoopaFire),                                  // ProfileID::cKoopaFire
    GetResNum(cRes_DemoKoopaJrClown),                           // ProfileID::cDemoKoopaJrClown
    GetResNum(cRes_DemoKoopaJr),                                // ProfileID::cDemoKoopaJr
    GetResNum(cRes_BunDemoKameck),                              // ProfileID::cBunDemoKameck
    GetResNum(cRes_KoopaDemoKameck),                            // ProfileID::cKoopaDemoKameck
    GetResNum(cRes_BossKKDemoKameck),                           // ProfileID::cBossKKDemoKameck
    GetResNum(cRes_BossKKDemoKK),                               // ProfileID::cBossKKDemoKK
    GetResNum(cRes_FinalKoopaFire),                             // ProfileID::cFinalKoopaFire
    GetResNum(cRes_FinalKoopaJr),                               // ProfileID::cFinalKoopaJr
    0,                                                          // ProfileID::cFinalKoopaJrFire
    GetResNum(cRes_FinalBomhei),                                // ProfileID::cFinalBomhei
    GetResNum(cRes_KokoopaShipLemmy),                           // ProfileID::cKokoopaShipLemmy
    GetResNum(cRes_KokoopaShipMorton),                          // ProfileID::cKokoopaShipMorton
    GetResNum(cRes_KokoopaShipLarry),                           // ProfileID::cKokoopaShipLarry
    GetResNum(cRes_KokoopaShipWendy),                           // ProfileID::cKokoopaShipWendy
    GetResNum(cRes_KokoopaShipIggy),                            // ProfileID::cKokoopaShipIggy
    GetResNum(cRes_KokoopaShipRoy),                             // ProfileID::cKokoopaShipRoy
    GetResNum(cRes_KokoopaShipLudwig),                          // ProfileID::cKokoopaShipLudwig
    GetResNum(cRes_Peach),                                      // ProfileID::cPeach
    GetResNum(cRes_2E0),                                        // ProfileID::c2E0
    0,                                                          // ProfileID::cFinalDVPeach
    0,                                                          // ProfileID::cFinalDVShutter
    GetResNum(cRes_2E3),                                        // ProfileID::c2E3
    GetResNum(cRes_2E4),                                        // ProfileID::c2E4
    GetResNum(cRes_2E5),                                        // ProfileID::c2E5
    GetResNum(cRes_2E6),                                        // ProfileID::c2E6
    GetResNum(cRes_2E7),                                        // ProfileID::c2E7
    GetResNum(cRes_2E8),                                        // ProfileID::c2E8
    0,                                                          // ProfileID::c2E9
    0,                                                          // ProfileID::c2EA
    0,                                                          // ProfileID::c2EB
    0,                                                          // ProfileID::c2EC
    0,                                                          // ProfileID::c2ED
    GetResNum(cRes_2EE),                                        // ProfileID::c2EE
    GetResNum(cRes_2EF),                                        // ProfileID::c2EF
    GetResNum(cRes_2F0),                                        // ProfileID::c2F0
    GetResNum(cRes_2F1),                                        // ProfileID::c2F1
    GetResNum(cRes_2F2),                                        // ProfileID::c2F2
    GetResNum(cRes_2F3),                                        // ProfileID::c2F3
    GetResNum(cRes_2F4),                                        // ProfileID::c2F4
    GetResNum(cRes_2F5),                                        // ProfileID::c2F5
    GetResNum(cRes_Hammer),                                     // ProfileID::cHammer
    GetResNum(cRes_2F7),                                        // ProfileID::c2F7
    GetResNum(cRes_Boomerang),                                  // ProfileID::cBoomerang
    GetResNum(cRes_2F9),                                        // ProfileID::c2F9
    0,                                                          // ProfileID::cFireBallBros
    GetResNum(cRes_2FB),                                        // ProfileID::c2FB
    0,                                                          // ProfileID::cIceBallBros
    GetResNum(cRes_2FD),                                        // ProfileID::c2FD
    GetResNum(cRes_MegaHammer),                                 // ProfileID::cMegaHammer
    GetResNum(cRes_2FF),                                        // ProfileID::c2FF
    GetResNum(cRes_300),                                        // ProfileID::c300
    GetResNum(cRes_301),                                        // ProfileID::c301
    GetResNum(cRes_302),                                        // ProfileID::c302
    GetResNum(cRes_303),                                        // ProfileID::c303
    GetResNum(cRes_304),                                        // ProfileID::c304
    GetResNum(cRes_305),                                        // ProfileID::c305
    GetResNum(cRes_306),                                        // ProfileID::c306
    GetResNum(cRes_307),                                        // ProfileID::c307
    GetResNum(cRes_308),                                        // ProfileID::c308
    GetResNum(cRes_309),                                        // ProfileID::c309
    GetResNum(cRes_30A),                                        // ProfileID::c30A
    GetResNum(cRes_30B),                                        // ProfileID::c30B
    GetResNum(cRes_30C),                                        // ProfileID::c30C
    GetResNum(cRes_30D),                                        // ProfileID::c30D
    0,                                                          // ProfileID::c30E
    GetResNum(cRes_30F),                                        // ProfileID::c30F
    GetResNum(cRes_310),                                        // ProfileID::c310
    GetResNum(cRes_311),                                        // ProfileID::c311
    GetResNum(cRes_312),                                        // ProfileID::c312
    GetResNum(cRes_313),                                        // ProfileID::c313
    GetResNum(cRes_314),                                        // ProfileID::c314
    GetResNum(cRes_315),                                        // ProfileID::c315
    GetResNum(cRes_316),                                        // ProfileID::c316
    GetResNum(cRes_317),                                        // ProfileID::c317
    GetResNum(cRes_318),                                        // ProfileID::c318
    0,                                                          // ProfileID::c319
    0,                                                          // ProfileID::c31A
    0,                                                          // ProfileID::c31B
    GetResNum(cRes_31C),                                        // ProfileID::c31C
    GetResNum(cRes_31D),                                        // ProfileID::c31D
    0,                                                          // ProfileID::c31E
    GetResNum(cRes_31F),                                        // ProfileID::c31F
    GetResNum(cRes_320),                                        // ProfileID::c320
    GetResNum(cRes_321),                                        // ProfileID::c321
    GetResNum(cRes_322),                                        // ProfileID::c322
    GetResNum(cRes_323),                                        // ProfileID::c323
    GetResNum(cRes_324),                                        // ProfileID::c324
    GetResNum(cRes_325),                                        // ProfileID::c325
    GetResNum(cRes_326),                                        // ProfileID::c326
    GetResNum(cRes_327),                                        // ProfileID::c327
    0,                                                          // ProfileID::c328
    GetResNum(cRes_BattleItem),                                 // ProfileID::cBattleItem
    GetResNum(cRes_32A),                                        // ProfileID::c32A
    GetResNum(cRes_VsBattleItem),                               // ProfileID::cVsBattleItem
    GetResNum(cRes_32C),                                        // ProfileID::c32C
    GetResNum(cRes_32D),                                        // ProfileID::c32D
    0,                                                          // ProfileID::c32E
    GetResNum(cRes_32F),                                        // ProfileID::c32F
    GetResNum(cRes_330),                                        // ProfileID::c330
    GetResNum(cRes_331),                                        // ProfileID::c331
    GetResNum(cRes_KoopaJrFire),                                // ProfileID::cKoopaJrFire
    GetResNum(cRes_KoopaJrBall),                                // ProfileID::cKoopaJrBall
    GetResNum(cRes_UnderwaterKoopaJr),                          // ProfileID::cUnderwaterKoopaJr
    GetResNum(cRes_UnderwaterKoopaJrClown),                     // ProfileID::cUnderwaterKoopaJrClown
    GetResNum(cRes_UnderwaterKoopaJrRetreatPos),                // ProfileID::cUnderwaterKoopaJrRetreatPos
    GetResNum(cRes_BoxingKoopaJr),                              // ProfileID::cBoxingKoopaJr
    GetResNum(cRes_BoxingKoopaJrPostBattleDemo),                // ProfileID::cBoxingKoopaJrPostBattleDemo
    GetResNum(cRes_BoxingKoopaJrClownPostBattleDemo),           // ProfileID::cBoxingKoopaJrClownPostBattleDemo
    GetResNum(cRes_MiniGamePanelItem),                          // ProfileID::cMiniGamePanelItem
    GetResNum(cRes_SlotItem),                                   // ProfileID::cSlotItem
    GetResNum(cRes_CoinmakiCannon),                             // ProfileID::cCoinmakiCannon
    GetResNum(cRes_CoinmakiItem),                               // ProfileID::cCoinmakiItem
    GetResNum(cRes_MiniGameKinopio),                            // ProfileID::cMiniGameKinopio
    GetResNum(cRes_33F),                                        // ProfileID::c33F
    GetResNum(cRes_340),                                        // ProfileID::c340
    GetResNum(cRes_341),                                        // ProfileID::c341
    GetResNum(cRes_342),                                        // ProfileID::c342
    0,                                                          // ProfileID::c343
    0,                                                          // ProfileID::c344
    0,                                                          // ProfileID::c345
    0,                                                          // ProfileID::c346
    0,                                                          // ProfileID::c347
    GetResNum(cRes_StaffCreditChibiYoshiABC),                   // ProfileID::cStaffCreditChibiYoshiABC
    GetResNum(cRes_StaffCreditChibiYoshiBalloon),               // ProfileID::cStaffCreditChibiYoshiBalloon
    GetResNum(cRes_StaffCreditChibiYoshiBalloonCheer),          // ProfileID::cStaffCreditChibiYoshiBalloonCheer
    GetResNum(cRes_StaffCreditChibiYoshiLight),                 // ProfileID::cStaffCreditChibiYoshiLight
    GetResNum(cRes_StaffCreditChibiYoshiLightCheer),            // ProfileID::cStaffCreditChibiYoshiLightCheer
    GetResNum(cRes_StaffCreditSoapABC),                         // ProfileID::cStaffCreditSoapABC
    GetResNum(cRes_StaffCreditSoapCoin),                        // ProfileID::cStaffCreditSoapCoin
    GetResNum(cRes_StaffCreditTottenKun),                       // ProfileID::cStaffCreditTottenKun
    0,                                                          // ProfileID::c350
    0,                                                          // ProfileID::c351
    0,                                                          // ProfileID::c352
    0,                                                          // ProfileID::c353
    GetResNum(cRes_RealizeFeverStar),                           // ProfileID::cRealizeFeverStar
    GetResNum(cRes_Star),                                       // ProfileID::cStar
    GetResNum(cRes_CourseSelectPlayer),                         // ProfileID::cCourseSelectPlayer
    GetResNum(cRes_CourseSelectPlayer2PSub),                    // ProfileID::cCourseSelectPlayer2PSub
    GetResNum(cRes_CourseSelectChibiYoshi),                     // ProfileID::cCourseSelectChibiYoshi
    0,                                                          // ProfileID::cCourseSelectCamera
    GetResNum(cRes_CourseSelectCastle),                         // ProfileID::cCourseSelectCastle
    GetResNum(cRes_CourseSelectToride),                         // ProfileID::cCourseSelectToride
    GetResNum(cRes_CourseSelectKinokoHouse1up),                 // ProfileID::cCourseSelectKinokoHouse1up
    GetResNum(cRes_CourseSelectKinokoHouseShuffle),             // ProfileID::cCourseSelectKinokoHouseShuffle
    GetResNum(cRes_CourseSelectKinokoHouseSlot),                // ProfileID::cCourseSelectKinokoHouseSlot
    GetResNum(cRes_CourseSelectPeachGates1st),                  // ProfileID::cCourseSelectPeachGates1st
    GetResNum(cRes_CourseSelectPeachGates2nd),                  // ProfileID::cCourseSelectPeachGates2nd
    GetResNum(cRes_CourseSelectCoursePoint),                    // ProfileID::cCourseSelectCoursePoint
    GetResNum(cRes_CourseSelectWorldMoveDokan),                 // ProfileID::cCourseSelectWorldMoveDokan
    0,                                                          // ProfileID::cCourseSelectW8Cloud
    GetResNum(cRes_CourseSelectGhost),                          // ProfileID::cCourseSelectGhost
    GetResNum(cRes_CourseSelectW2Bros),                         // ProfileID::cCourseSelectW2Bros
    GetResNum(cRes_CourseSelectShipW1),                         // ProfileID::cCourseSelectShipW1
    GetResNum(cRes_CourseSelectShipW2),                         // ProfileID::cCourseSelectShipW2
    GetResNum(cRes_CourseSelectShipW3),                         // ProfileID::cCourseSelectShipW3
    GetResNum(cRes_CourseSelectShipW4),                         // ProfileID::cCourseSelectShipW4
    GetResNum(cRes_CourseSelectShipW5),                         // ProfileID::cCourseSelectShipW5
    GetResNum(cRes_CourseSelectShipW6),                         // ProfileID::cCourseSelectShipW6
    GetResNum(cRes_CourseSelectShipW7),                         // ProfileID::cCourseSelectShipW7
    GetResNum(cRes_CourseSelectShipW8),                         // ProfileID::cCourseSelectShipW8
    GetResNum(cRes_CourseSelectShipW8Broken),                   // ProfileID::cCourseSelectShipW8Broken
    GetResNum(cRes_CourseSelectSurrender),                      // ProfileID::cCourseSelectSurrender
    GetResNum(cRes_CourseSelectSwitchA),                        // ProfileID::cCourseSelectSwitchA
    GetResNum(cRes_CourseSelectSwitchB),                        // ProfileID::cCourseSelectSwitchB
    GetResNum(cRes_CourseSelectTeresa),                         // ProfileID::cCourseSelectTeresa
    GetResNum(cRes_CourseSelectOpeningKameck),                  // ProfileID::cCourseSelectOpeningKameck
    GetResNum(cRes_CourseSelectTorideBoss),                     // ProfileID::cCourseSelectTorideBoss
    GetResNum(cRes_CourseSelectPakkun),                         // ProfileID::cCourseSelectPakkun
    GetResNum(cRes_CourseSelectShadowFirstDemoKinopio),         // ProfileID::cCourseSelectShadowFirstDemoKinopio
    GetResNum(cRes_CourseSelectTobiPuku),                       // ProfileID::cCourseSelectTobiPuku
    GetResNum(cRes_CourseSelectChorobon),                       // ProfileID::cCourseSelectChorobon
    GetResNum(cRes_CourseSelectW7Item),                         // ProfileID::cCourseSelectW7Item
    GetResNum(cRes_CourseSelectW5Teresa),                       // ProfileID::cCourseSelectW5Teresa
    GetResNum(cRes_CourseSelectFlag),                           // ProfileID::cCourseSelectFlag
    GetResNum(cRes_CourseSelectMusasabi),                       // ProfileID::cCourseSelectMusasabi
    GetResNum(cRes_CourseSelectWPillar),                        // ProfileID::cCourseSelectWPillar
    GetResNum(cRes_CourseSelectW7Bridge),                       // ProfileID::cCourseSelectW7Bridge
    GetResNum(cRes_CourseSelectMiiBalloon),                     // ProfileID::cCourseSelectMiiBalloon
    GetResNum(cRes_CourseSelectPenguin),                        // ProfileID::cCourseSelectPenguin
    GetResNum(cRes_CourseSelectW4Item),                         // ProfileID::cCourseSelectW4Item
    GetResNum(cRes_CourseSelectW2Kuribo),                       // ProfileID::cCourseSelectW2Kuribo
    GetResNum(cRes_CourseSelectPakkunBig),                      // ProfileID::cCourseSelectPakkunBig
    GetResNum(cRes_CourseSelectShadowKunIcon),                  // ProfileID::cCourseSelectShadowKunIcon
    GetResNum(cRes_CourseSelectDekaUnira),                      // ProfileID::cCourseSelectDekaUnira
    GetResNum(cRes_CourseSelectTomb),                           // ProfileID::cCourseSelectTomb
    GetResNum(cRes_CourseSelectShadowFirstDemoShadowKun),       // ProfileID::cCourseSelectShadowFirstDemoShadowKun
    GetResNum(cRes_CourseSelectKotsuCoaster),                   // ProfileID::cCourseSelectKotsuCoaster
    GetResNum(cRes_CourseSelectKoopaJr),                        // ProfileID::cCourseSelectKoopaJr
    GetResNum(cRes_CourseSelectPeach),                          // ProfileID::cCourseSelectPeach
    GetResNum(cRes_CourseSelectW1Item),                         // ProfileID::cCourseSelectW1Item
    GetResNum(cRes_CourseSelectStarGate),                       // ProfileID::cCourseSelectStarGate
    0,                                                          // ProfileID::cCourseSelectEventAssistant
    GetResNum(cRes_38E),                                        // Profile 910
    GetResNum(cRes_38F),                                        // Profile 911
    0                                                           // Profile 912
};

// -----------------------------------------  ResList ----------------------------------------- //

const sead::SafeString* Profile::cResList[cProfileID_Max] = {
    nullptr,                                        // ProfileID::c000
    nullptr,                                        // ProfileID::c001
    nullptr,                                        // ProfileID::c002
    nullptr,                                        // ProfileID::c003
    nullptr,                                        // ProfileID::c004
    nullptr,                                        // ProfileID::c005
    nullptr,                                        // ProfileID::c006
    nullptr,                                        // ProfileID::c007
    nullptr,                                        // ProfileID::c008
    nullptr,                                        // ProfileID::c009
    nullptr,                                        // ProfileID::c00A
    nullptr,                                        // ProfileID::c00B
    nullptr,                                        // ProfileID::c00C
    nullptr,                                        // ProfileID::c00D
    nullptr,                                        // ProfileID::c00E
    nullptr,                                        // ProfileID::c00F
    nullptr,                                        // ProfileID::c010
    nullptr,                                        // ProfileID::c011
    nullptr,                                        // ProfileID::c012
    nullptr,                                        // ProfileID::c013
    nullptr,                                        // ProfileID::c014
    cRes_015,                                       // ProfileID::c015
    cRes_016,                                       // ProfileID::c016
    cRes_017,                                       // ProfileID::c017
    cRes_MiniGameMgr,                               // ProfileID::cMiniGameMgr
    cRes_MiniGameMgrRDash,                          // ProfileID::cMiniGameMgrRDash
    nullptr,                                        // ProfileID::cShuffleBlockMgr
    nullptr,                                        // ProfileID::cSlotMgr
    nullptr,                                        // ProfileID::cCoinmakiMgr
    nullptr,                                        // ProfileID::c01D
    nullptr,                                        // ProfileID::c01E
    nullptr,                                        // ProfileID::c01F
    nullptr,                                        // ProfileID::c020
    cRes_ShootingStar,                              // ProfileID::cShootingStar
    cRes_StaffRollMgr,                              // ProfileID::cStaffRollMgr
    cRes_StaffRollMgrRDash,                         // ProfileID::cStaffRollMgrRDash
    cRes_024,                                       // ProfileID::c024
    nullptr,                                        // ProfileID::c025
    cRes_026,                                       // ProfileID::c026
    nullptr,                                        // ProfileID::c027
    nullptr,                                        // ProfileID::c028
    nullptr,                                        // ProfileID::c029
    nullptr,                                        // ProfileID::c02A
    cRes_02B,                                       // ProfileID::c02B
    cRes_02C,                                       // ProfileID::c02C
    cRes_02D,                                       // ProfileID::c02D
    cRes_02E,                                       // ProfileID::c02E
    nullptr,                                        // ProfileID::c02F
    nullptr,                                        // ProfileID::c030
    nullptr,                                        // ProfileID::c031
    cRes_032,                                       // ProfileID::c032
    cRes_033,                                       // ProfileID::c033
    nullptr,                                        // ProfileID::c034
    cRes_035,                                       // ProfileID::c035
    cRes_036,                                       // ProfileID::c036
    cRes_037,                                       // ProfileID::c037
    cRes_038,                                       // ProfileID::c038
    cRes_039,                                       // ProfileID::c039
    cRes_03A,                                       // ProfileID::c03A
    cRes_03B,                                       // ProfileID::c03B
    cRes_03C,                                       // ProfileID::c03C
    cRes_03D,                                       // ProfileID::c03D
    cRes_03E,                                       // ProfileID::c03E
    cRes_03F,                                       // ProfileID::c03F
    cRes_040,                                       // ProfileID::c040
    cRes_041,                                       // ProfileID::c041
    cRes_042,                                       // ProfileID::c042
    cRes_043,                                       // ProfileID::c043
    cRes_044,                                       // ProfileID::c044
    cRes_045,                                       // ProfileID::c045
    cRes_046,                                       // ProfileID::c046
    cRes_047,                                       // ProfileID::c047
    cRes_048,                                       // ProfileID::c048
    cRes_049,                                       // ProfileID::c049
    cRes_04A,                                       // ProfileID::c04A
    cRes_04B,                                       // ProfileID::c04B
    cRes_04C,                                       // ProfileID::c04C
    cRes_04D,                                       // ProfileID::c04D
    cRes_04E,                                       // ProfileID::c04E
    cRes_04F,                                       // ProfileID::c04F
    cRes_050,                                       // ProfileID::c050
    cRes_051,                                       // ProfileID::c051
    cRes_052,                                       // ProfileID::c052
    cRes_053,                                       // ProfileID::c053
    cRes_054,                                       // ProfileID::c054
    cRes_055,                                       // ProfileID::c055
    cRes_056,                                       // ProfileID::c056
    cRes_057,                                       // ProfileID::c057
    cRes_058,                                       // ProfileID::c058
    cRes_059,                                       // ProfileID::c059
    cRes_05A,                                       // ProfileID::c05A
    cRes_05B,                                       // ProfileID::c05B
    cRes_05C,                                       // ProfileID::c05C
    nullptr,                                        // ProfileID::c05D
    nullptr,                                        // ProfileID::c05E
    cRes_05F,                                       // ProfileID::c05F
    cRes_060,                                       // ProfileID::c060
    cRes_061,                                       // ProfileID::c061
    cRes_062,                                       // ProfileID::c062
    cRes_063,                                       // ProfileID::c063
    cRes_064,                                       // ProfileID::c064
    cRes_065,                                       // ProfileID::c065
    cRes_066,                                       // ProfileID::c066
    cRes_067,                                       // ProfileID::c067
    cRes_068,                                       // ProfileID::c068
    cRes_069,                                       // ProfileID::c069
    cRes_06A,                                       // ProfileID::c06A
    cRes_06B,                                       // ProfileID::c06B
    cRes_06C,                                       // ProfileID::c06C
    cRes_06D,                                       // ProfileID::c06D
    cRes_06E,                                       // ProfileID::c06E
    cRes_06F,                                       // ProfileID::c06F
    cRes_070,                                       // ProfileID::c070
    cRes_071,                                       // ProfileID::c071
    cRes_072,                                       // ProfileID::c072
    cRes_073,                                       // ProfileID::c073
    cRes_074,                                       // ProfileID::c074
    cRes_075,                                       // ProfileID::c075
    cRes_076,                                       // ProfileID::c076
    cRes_077,                                       // ProfileID::c077
    nullptr,                                        // ProfileID::c078
    cRes_079,                                       // ProfileID::c079
    cRes_07A,                                       // ProfileID::c07A
    cRes_07B,                                       // ProfileID::c07B
    cRes_07C,                                       // ProfileID::c07C
    cRes_07D,                                       // ProfileID::c07D
    cRes_07E,                                       // ProfileID::c07E
    cRes_07F,                                       // ProfileID::c07F
    cRes_080,                                       // ProfileID::c080
    cRes_081,                                       // ProfileID::c081
    cRes_082,                                       // ProfileID::c082
    cRes_083,                                       // ProfileID::c083
    cRes_084,                                       // ProfileID::c084
    cRes_085,                                       // ProfileID::c085
    cRes_086,                                       // ProfileID::c086
    cRes_087,                                       // ProfileID::c087
    cRes_088,                                       // ProfileID::c088
    cRes_089,                                       // ProfileID::c089
    cRes_08A,                                       // ProfileID::c08A
    cRes_08B,                                       // ProfileID::c08B
    cRes_08C,                                       // ProfileID::c08C
    cRes_08D,                                       // ProfileID::c08D
    cRes_08E,                                       // ProfileID::c08E
    cRes_08F,                                       // ProfileID::c08F
    cRes_090,                                       // ProfileID::c090
    cRes_091,                                       // ProfileID::c091
    cRes_092,                                       // ProfileID::c092
    cRes_093,                                       // ProfileID::c093
    cRes_094,                                       // ProfileID::c094
    cRes_095,                                       // ProfileID::c095
    cRes_096,                                       // ProfileID::c096
    cRes_097,                                       // ProfileID::c097
    cRes_098,                                       // ProfileID::c098
    cRes_099,                                       // ProfileID::c099
    nullptr,                                        // ProfileID::c09A
    cRes_09B,                                       // ProfileID::c09B
    cRes_09C,                                       // ProfileID::c09C
    cRes_09D,                                       // ProfileID::c09D
    cRes_09E,                                       // ProfileID::c09E
    cRes_09F,                                       // ProfileID::c09F
    cRes_0A0,                                       // ProfileID::c0A0
    cRes_0A1,                                       // ProfileID::c0A1
    cRes_0A2,                                       // ProfileID::c0A2
    cRes_0A3,                                       // ProfileID::c0A3
    cRes_0A4,                                       // ProfileID::c0A4
    cRes_0A5,                                       // ProfileID::c0A5
    cRes_0A6,                                       // ProfileID::c0A6
    cRes_0A7,                                       // ProfileID::c0A7
    cRes_0A8,                                       // ProfileID::c0A8
    cRes_0A9,                                       // ProfileID::c0A9
    cRes_0AA,                                       // ProfileID::c0AA
    cRes_0AB,                                       // ProfileID::c0AB
    cRes_0AC,                                       // ProfileID::c0AC
    cRes_0AD,                                       // ProfileID::c0AD
    cRes_0AE,                                       // ProfileID::c0AE
    cRes_0AF,                                       // ProfileID::c0AF
    cRes_0B0,                                       // ProfileID::c0B0
    cRes_0B1,                                       // ProfileID::c0B1
    cRes_0B2,                                       // ProfileID::c0B2
    cRes_0B3,                                       // ProfileID::c0B3
    cRes_0B4,                                       // ProfileID::c0B4
    cRes_0B5,                                       // ProfileID::c0B5
    cRes_0B6,                                       // ProfileID::c0B6
    cRes_0B7,                                       // ProfileID::c0B7
    cRes_0B8,                                       // ProfileID::c0B8
    cRes_0B9,                                       // ProfileID::c0B9
    cRes_0BA,                                       // ProfileID::c0BA
    cRes_0BB,                                       // ProfileID::c0BB
    cRes_0BC,                                       // ProfileID::c0BC
    cRes_0BD,                                       // ProfileID::c0BD
    cRes_0BE,                                       // ProfileID::c0BE
    cRes_0BF,                                       // ProfileID::c0BF
    cRes_0C0,                                       // ProfileID::c0C0
    cRes_0C1,                                       // ProfileID::c0C1
    cRes_0C2,                                       // ProfileID::c0C2
    cRes_0C3,                                       // ProfileID::c0C3
    cRes_0C4,                                       // ProfileID::c0C4
    cRes_0C5,                                       // ProfileID::c0C5
    cRes_0C6,                                       // ProfileID::c0C6
    cRes_0C7,                                       // ProfileID::c0C7
    cRes_0C8,                                       // ProfileID::c0C8
    cRes_0C9,                                       // ProfileID::c0C9
    cRes_0CA,                                       // ProfileID::c0CA
    cRes_0CB,                                       // ProfileID::c0CB
    cRes_0CC,                                       // ProfileID::c0CC
    cRes_0CD,                                       // ProfileID::c0CD
    cRes_0CE,                                       // ProfileID::c0CE
    cRes_0CF,                                       // ProfileID::c0CF
    cRes_0D0,                                       // ProfileID::c0D0
    cRes_0D1,                                       // ProfileID::c0D1
    cRes_FloorHoleDokan,                            // ProfileID::cFloorHoleDokan
    cRes_0D3,                                       // ProfileID::c0D3
    cRes_0D4,                                       // ProfileID::c0D4
    cRes_0D5,                                       // ProfileID::c0D5
    cRes_0D6,                                       // ProfileID::c0D6
    cRes_0D7,                                       // ProfileID::c0D7
    cRes_0D8,                                       // ProfileID::c0D8
    cRes_0D9,                                       // ProfileID::c0D9
    cRes_0DA,                                       // ProfileID::c0DA
    cRes_0DB,                                       // ProfileID::c0DB
    cRes_0DC,                                       // ProfileID::c0DC
    cRes_0DD,                                       // ProfileID::c0DD
    cRes_0DE,                                       // ProfileID::c0DE
    cRes_0DF,                                       // ProfileID::c0DF
    cRes_0E0,                                       // ProfileID::c0E0
    cRes_0E1,                                       // ProfileID::c0E1
    cRes_0E2,                                       // ProfileID::c0E2
    cRes_0E3,                                       // ProfileID::c0E3
    cRes_0E4,                                       // ProfileID::c0E4
    cRes_0E5,                                       // ProfileID::c0E5
    cRes_0E6,                                       // ProfileID::c0E6
    cRes_0E7,                                       // ProfileID::c0E7
    cRes_0E8,                                       // ProfileID::c0E8
    cRes_0E9,                                       // ProfileID::c0E9
    cRes_0EA,                                       // ProfileID::c0EA
    cRes_0EB,                                       // ProfileID::c0EB
    cRes_0EC,                                       // ProfileID::c0EC
    cRes_0ED,                                       // ProfileID::c0ED
    cRes_0EE,                                       // ProfileID::c0EE
    cRes_0EF,                                       // ProfileID::c0EF
    cRes_0F0,                                       // ProfileID::c0F0
    cRes_0F1,                                       // ProfileID::c0F1
    cRes_0F2,                                       // ProfileID::c0F2
    cRes_0F3,                                       // ProfileID::c0F3
    cRes_0F4,                                       // ProfileID::c0F4
    nullptr,                                        // ProfileID::c0F5
    cRes_0F6,                                       // ProfileID::c0F6
    cRes_0F7,                                       // ProfileID::c0F7
    cRes_0F8,                                       // ProfileID::c0F8
    cRes_0F9,                                       // ProfileID::c0F9
    cRes_0FA,                                       // ProfileID::c0FA
    cRes_0FB,                                       // ProfileID::c0FB
    cRes_0FC,                                       // ProfileID::c0FC
    cRes_0FD,                                       // ProfileID::c0FD
    cRes_0FE,                                       // ProfileID::c0FE
    cRes_0FF,                                       // ProfileID::c0FF
    cRes_100,                                       // ProfileID::c100
    cRes_101,                                       // ProfileID::c101
    cRes_102,                                       // ProfileID::c102
    cRes_103,                                       // ProfileID::c103
    cRes_104,                                       // ProfileID::c104
    cRes_ShuffleBlock,                              // ProfileID::cShuffleBlock
    cRes_KokoopaShipWarpCannon,                     // ProfileID::cKokoopaShipWarpCannon
    cRes_107,                                       // ProfileID::c107
    cRes_108,                                       // ProfileID::c108
    cRes_KoopaShutter,                              // ProfileID::cKoopaShutter
    cRes_10A,                                       // ProfileID::c10A
    cRes_10B,                                       // ProfileID::c10B
    cRes_10C,                                       // ProfileID::c10C
    cRes_PeachFinalCastleKoopaJrLift,               // ProfileID::cPeachFinalCastleKoopaJrLift
    cRes_PeachFinalCastleKoopaJrLiftHmove,          // ProfileID::cPeachFinalCastleKoopaJrLiftHmove
    cRes_PeachFinalCastleKoopaJrLiftPairObj,        // ProfileID::cPeachFinalCastleKoopaJrLiftPairObj
    cRes_RoyLiftWakiStep,                           // ProfileID::cRoyLiftWakiStep
    cRes_WendyFloor,                                // ProfileID::cWendyFloor
    cRes_IggyRoom,                                  // ProfileID::cIggyRoom
    cRes_113,                                       // ProfileID::c113
    cRes_114,                                       // ProfileID::c114
    cRes_115,                                       // ProfileID::c115
    cRes_116,                                       // ProfileID::c116
    nullptr,                                        // ProfileID::c117
    cRes_118,                                       // ProfileID::c118
    cRes_119,                                       // ProfileID::c119
    cRes_11A,                                       // ProfileID::c11A
    cRes_11B,                                       // ProfileID::c11B
    nullptr,                                        // ProfileID::c11C
    cRes_11D,                                       // ProfileID::c11D
    cRes_11E,                                       // ProfileID::c11E
    nullptr,                                        // ProfileID::c11F
    nullptr,                                        // ProfileID::c120
    nullptr,                                        // ProfileID::c121
    nullptr,                                        // ProfileID::c122
    nullptr,                                        // ProfileID::c123
    nullptr,                                        // ProfileID::c124
    nullptr,                                        // ProfileID::c125
    nullptr,                                        // ProfileID::c126
    nullptr,                                        // ProfileID::c127
    nullptr,                                        // ProfileID::c128
    nullptr,                                        // ProfileID::c129
    nullptr,                                        // ProfileID::c12A
    nullptr,                                        // ProfileID::c12B
    nullptr,                                        // ProfileID::c12C
    nullptr,                                        // ProfileID::c12D
    nullptr,                                        // ProfileID::c12E
    nullptr,                                        // ProfileID::c12F
    nullptr,                                        // ProfileID::c130
    nullptr,                                        // ProfileID::c131
    nullptr,                                        // ProfileID::c132
    nullptr,                                        // ProfileID::c133
    nullptr,                                        // ProfileID::c134
    cRes_135,                                       // ProfileID::c135
    cRes_136,                                       // ProfileID::c136
    nullptr,                                        // ProfileID::c137
    cRes_138,                                       // ProfileID::c138
    nullptr,                                        // ProfileID::c139
    cRes_13A,                                       // ProfileID::c13A
    cRes_13B,                                       // ProfileID::c13B
    cRes_13C,                                       // ProfileID::c13C
    nullptr,                                        // ProfileID::c13D
    nullptr,                                        // ProfileID::c13E
    nullptr,                                        // ProfileID::c13F
    cRes_140,                                       // ProfileID::c140
    cRes_141,                                       // ProfileID::c141
    cRes_142,                                       // ProfileID::c142
    cRes_143,                                       // ProfileID::c143
    cRes_144,                                       // ProfileID::c144
    cRes_145,                                       // ProfileID::c145
    cRes_146,                                       // ProfileID::c146
    cRes_147,                                       // ProfileID::c147
    cRes_148,                                       // ProfileID::c148
    cRes_149,                                       // ProfileID::c149
    cRes_14A,                                       // ProfileID::c14A
    cRes_14B,                                       // ProfileID::c14B
    nullptr,                                        // ProfileID::c14C
    cRes_14D,                                       // ProfileID::c14D
    cRes_14E,                                       // ProfileID::c14E
    cRes_14F,                                       // ProfileID::c14F
    cRes_150,                                       // ProfileID::c150
    cRes_151,                                       // ProfileID::c151
    cRes_152,                                       // ProfileID::c152
    cRes_153,                                       // ProfileID::c153
    cRes_154,                                       // ProfileID::c154
    cRes_155,                                       // ProfileID::c155
    cRes_156,                                       // ProfileID::c156
    cRes_157,                                       // ProfileID::c157
    cRes_158,                                       // ProfileID::c158
    cRes_159,                                       // ProfileID::c159
    cRes_15A,                                       // ProfileID::c15A
    cRes_15B,                                       // ProfileID::c15B
    nullptr,                                        // ProfileID::c15C
    cRes_15D,                                       // ProfileID::c15D
    cRes_15E,                                       // ProfileID::c15E
    cRes_LemmyBall,                                 // ProfileID::cLemmyBall
    cRes_LemmyBomb,                                 // ProfileID::cLemmyBomb
    cRes_161,                                       // ProfileID::c161
    nullptr,                                        // ProfileID::c162
    cRes_163,                                       // ProfileID::c163
    cRes_164,                                       // ProfileID::c164
    cRes_165,                                       // ProfileID::c165
    cRes_166,                                       // ProfileID::c166
    cRes_167,                                       // ProfileID::c167
    cRes_168,                                       // ProfileID::c168
    cRes_169,                                       // ProfileID::c169
    cRes_16A,                                       // ProfileID::c16A
    cRes_16B,                                       // ProfileID::c16B
    cRes_16C,                                       // ProfileID::c16C
    cRes_16D,                                       // ProfileID::c16D
    cRes_16E,                                       // ProfileID::c16E
    cRes_16F,                                       // ProfileID::c16F
    cRes_KameckIce,                                 // ProfileID::cKameckIce
    cRes_WendyIcicle,                               // ProfileID::cWendyIcicle
    cRes_PeachFinalCastleKoopaJrClown,              // ProfileID::cPeachFinalCastleKoopaJrClown
    cRes_BoxingKoopaJrClown,                        // ProfileID::cBoxingKoopaJrClown
    cRes_174,                                       // ProfileID::c174
    cRes_FinalKoopaJrClown,                         // ProfileID::cFinalKoopaJrClown
    cRes_FinalKoopa,                                // ProfileID::cFinalKoopa
    cRes_177,                                       // ProfileID::c177
    cRes_178,                                       // ProfileID::c178
    cRes_179,                                       // ProfileID::c179
    cRes_17A,                                       // ProfileID::c17A
    cRes_17B,                                       // ProfileID::c17B
    nullptr,                                        // ProfileID::c17C
    cRes_17D,                                       // ProfileID::c17D
    cRes_17E,                                       // ProfileID::c17E
    cRes_17F,                                       // ProfileID::c17F
    cRes_180,                                       // ProfileID::c180
    cRes_181,                                       // ProfileID::c181
    cRes_182,                                       // ProfileID::c182
    cRes_183,                                       // ProfileID::c183
    cRes_184,                                       // ProfileID::c184
    cRes_185,                                       // ProfileID::c185
    cRes_186,                                       // ProfileID::c186
    cRes_187,                                       // ProfileID::c187
    cRes_188,                                       // ProfileID::c188
    cRes_189,                                       // ProfileID::c189
    cRes_18A,                                       // ProfileID::c18A
    cRes_18B,                                       // ProfileID::c18B
    cRes_18C,                                       // ProfileID::c18C
    cRes_18D,                                       // ProfileID::c18D
    cRes_18E,                                       // ProfileID::c18E
    cRes_18F,                                       // ProfileID::c18F
    cRes_190,                                       // ProfileID::c190
    cRes_191,                                       // ProfileID::c191
    cRes_192,                                       // ProfileID::c192
    cRes_193,                                       // ProfileID::c193
    cRes_194,                                       // ProfileID::c194
    cRes_195,                                       // ProfileID::c195
    cRes_196,                                       // ProfileID::c196
    cRes_197,                                       // ProfileID::c197
    cRes_198,                                       // ProfileID::c198
    cRes_199,                                       // ProfileID::c199
    cRes_19A,                                       // ProfileID::c19A
    nullptr,                                        // ProfileID::c19B
    cRes_19C,                                       // ProfileID::c19C
    cRes_19D,                                       // ProfileID::c19D
    nullptr,                                        // ProfileID::c19E
    cRes_19F,                                       // ProfileID::c19F
    cRes_1A0,                                       // ProfileID::c1A0
    cRes_1A1,                                       // ProfileID::c1A1
    nullptr,                                        // ProfileID::c1A2
    cRes_1A3,                                       // ProfileID::c1A3
    cRes_1A4,                                       // ProfileID::c1A4
    cRes_1A5,                                       // ProfileID::c1A5
    cRes_1A6,                                       // ProfileID::c1A6
    cRes_1A7,                                       // ProfileID::c1A7
    cRes_1A8,                                       // ProfileID::c1A8
    cRes_1A9,                                       // ProfileID::c1A9
    cRes_1AA,                                       // ProfileID::c1AA
    cRes_1AB,                                       // ProfileID::c1AB
    cRes_1AC,                                       // ProfileID::c1AC
    cRes_1AD,                                       // ProfileID::c1AD
    cRes_1AE,                                       // ProfileID::c1AE
    cRes_1AF,                                       // ProfileID::c1AF
    cRes_1B0,                                       // ProfileID::c1B0
    cRes_1B1,                                       // ProfileID::c1B1
    cRes_1B2,                                       // ProfileID::c1B2
    cRes_1B3,                                       // ProfileID::c1B3
    nullptr,                                        // ProfileID::c1B4
    nullptr,                                        // ProfileID::c1B5
    cRes_CoinmakiCoin,                              // ProfileID::cCoinmakiCoin
    nullptr,                                        // ProfileID::c1B7
    nullptr,                                        // ProfileID::c1B8
    cRes_1B9,                                       // ProfileID::c1B9
    cRes_Yoshi,                                     // ProfileID::cYoshi
    cRes_TottenPlayer,                              // ProfileID::cTottenPlayer
    cRes_PlayerObject,                              // ProfileID::cPlayerObject
    cRes_1BD,                                       // ProfileID::c1BD
    cRes_1BE,                                       // ProfileID::c1BE
    cRes_1BF,                                       // ProfileID::c1BF
    cRes_1C0,                                       // ProfileID::c1C0
    cRes_1C1,                                       // ProfileID::c1C1
    cRes_1C2,                                       // ProfileID::c1C2
    cRes_1C3,                                       // ProfileID::c1C3
    nullptr,                                        // ProfileID::c1C4
    cRes_SlotYoshiChibi,                            // ProfileID::cSlotYoshiChibi
    cRes_1C6,                                       // ProfileID::c1C6
    nullptr,                                        // ProfileID::c1C7
    cRes_1C8,                                       // ProfileID::c1C8
    nullptr,                                        // ProfileID::c1C9
    nullptr,                                        // ProfileID::c1CA
    cRes_1CB,                                       // ProfileID::c1CB
    cRes_1CC,                                       // ProfileID::c1CC
    nullptr,                                        // ProfileID::c1CD
    cRes_1CE,                                       // ProfileID::c1CE
    cRes_QuestPrizeItem,                            // ProfileID::cQuestPrizeItem
    cRes_1D0,                                       // ProfileID::c1D0
    cRes_1D1,                                       // ProfileID::c1D1
    cRes_1D2,                                       // ProfileID::c1D2
    cRes_1D3,                                       // ProfileID::c1D3
    cRes_1D4,                                       // ProfileID::c1D4
    cRes_1D5,                                       // ProfileID::c1D5
    cRes_1D6,                                       // ProfileID::c1D6
    cRes_1D7,                                       // ProfileID::c1D7
    cRes_1D8,                                       // ProfileID::c1D8
    cRes_1D9,                                       // ProfileID::c1D9
    nullptr,                                        // ProfileID::cIceBall
    nullptr,                                        // ProfileID::cIceBallPakkun
    nullptr,                                        // ProfileID::cFireBallPlayer
    nullptr,                                        // ProfileID::cFireBallPakkun
    nullptr,                                        // ProfileID::c1DE
    cRes_1DF,                                       // ProfileID::c1DF
    cRes_1E0,                                       // ProfileID::c1E0
    cRes_1E1,                                       // ProfileID::c1E1
    cRes_1E2,                                       // ProfileID::c1E2
    cRes_1E3,                                       // ProfileID::c1E3
    cRes_1E4,                                       // ProfileID::c1E4
    cRes_1E5,                                       // ProfileID::c1E5
    cRes_1E6,                                       // ProfileID::c1E6
    cRes_1E7,                                       // ProfileID::c1E7
    cRes_1E8,                                       // ProfileID::c1E8
    cRes_1E9,                                       // ProfileID::c1E9
    cRes_1EA,                                       // ProfileID::c1EA
    cRes_1EB,                                       // ProfileID::c1EB
    cRes_1EC,                                       // ProfileID::c1EC
    cRes_1ED,                                       // ProfileID::c1ED
    cRes_1EE,                                       // ProfileID::c1EE
    cRes_1EF,                                       // ProfileID::c1EF
    cRes_1F0,                                       // ProfileID::c1F0
    cRes_1F1,                                       // ProfileID::c1F1
    cRes_1F2,                                       // ProfileID::c1F2
    cRes_1F3,                                       // ProfileID::c1F3
    cRes_1F4,                                       // ProfileID::c1F4
    cRes_1F5,                                       // ProfileID::c1F5
    cRes_1F6,                                       // ProfileID::c1F6
    cRes_1F7,                                       // ProfileID::c1F7
    cRes_1F8,                                       // ProfileID::c1F8
    cRes_1F9,                                       // ProfileID::c1F9
    cRes_1FA,                                       // ProfileID::c1FA
    cRes_1FB,                                       // ProfileID::c1FB
    cRes_1FC,                                       // ProfileID::c1FC
    cRes_1FD,                                       // ProfileID::c1FD
    cRes_1FE,                                       // ProfileID::c1FE
    nullptr,                                        // ProfileID::c1FF
    cRes_200,                                       // ProfileID::c200
    cRes_201,                                       // ProfileID::c201
    cRes_202,                                       // ProfileID::c202
    cRes_203,                                       // ProfileID::c203
    cRes_204,                                       // ProfileID::c204
    cRes_205,                                       // ProfileID::c205
    cRes_206,                                       // ProfileID::c206
    cRes_207,                                       // ProfileID::c207
    cRes_208,                                       // ProfileID::c208
    cRes_209,                                       // ProfileID::c209
    cRes_20A,                                       // ProfileID::c20A
    cRes_20B,                                       // ProfileID::c20B
    cRes_20C,                                       // ProfileID::c20C
    cRes_20D,                                       // ProfileID::c20D
    cRes_20E,                                       // ProfileID::c20E
    cRes_20F,                                       // ProfileID::c20F
    cRes_210,                                       // ProfileID::c210
    cRes_211,                                       // ProfileID::c211
    cRes_212,                                       // ProfileID::c212
    cRes_213,                                       // ProfileID::c213
    cRes_214,                                       // ProfileID::c214
    cRes_215,                                       // ProfileID::c215
    cRes_216,                                       // ProfileID::c216
    cRes_217,                                       // ProfileID::c217
    cRes_218,                                       // ProfileID::c218
    cRes_219,                                       // ProfileID::c219
    cRes_21A,                                       // ProfileID::c21A
    cRes_21B,                                       // ProfileID::c21B
    cRes_21C,                                       // ProfileID::c21C
    cRes_21D,                                       // ProfileID::c21D
    cRes_21E,                                       // ProfileID::c21E
    cRes_21F,                                       // ProfileID::c21F
    cRes_220,                                       // ProfileID::c220
    cRes_221,                                       // ProfileID::c221
    cRes_222,                                       // ProfileID::c222
    cRes_223,                                       // ProfileID::c223
    cRes_224,                                       // ProfileID::c224
    cRes_225,                                       // ProfileID::c225
    cRes_226,                                       // ProfileID::c226
    cRes_227,                                       // ProfileID::c227
    cRes_228,                                       // ProfileID::c228
    cRes_229,                                       // ProfileID::c229
    cRes_22A,                                       // ProfileID::c22A
    cRes_22B,                                       // ProfileID::c22B
    cRes_22C,                                       // ProfileID::c22C
    cRes_22D,                                       // ProfileID::c22D
    nullptr,                                        // ProfileID::cFireBallKeronpa
    nullptr,                                        // ProfileID::cFireBallKeronpaRDash
    cRes_230,                                       // ProfileID::c230
    cRes_231,                                       // ProfileID::c231
    cRes_232,                                       // ProfileID::c232
    cRes_233,                                       // ProfileID::c233
    cRes_234,                                       // ProfileID::c234
    cRes_235,                                       // ProfileID::c235
    cRes_236,                                       // ProfileID::c236
    cRes_237,                                       // ProfileID::c237
    cRes_238,                                       // ProfileID::c238
    cRes_239,                                       // ProfileID::c239
    cRes_23A,                                       // ProfileID::c23A
    cRes_23B,                                       // ProfileID::c23B
    cRes_23C,                                       // ProfileID::c23C
    cRes_23D,                                       // ProfileID::c23D
    cRes_23E,                                       // ProfileID::c23E
    nullptr,                                        // ProfileID::c23F
    nullptr,                                        // ProfileID::c240
    nullptr,                                        // ProfileID::c241
    nullptr,                                        // ProfileID::c242
    nullptr,                                        // ProfileID::c243
    nullptr,                                        // ProfileID::c244
    nullptr,                                        // ProfileID::c245
    nullptr,                                        // ProfileID::c246
    nullptr,                                        // ProfileID::c247
    nullptr,                                        // ProfileID::c248
    nullptr,                                        // ProfileID::c249
    nullptr,                                        // ProfileID::c24A
    nullptr,                                        // ProfileID::cBgCenter
    nullptr,                                        // ProfileID::c24C
    nullptr,                                        // ProfileID::c24D
    nullptr,                                        // ProfileID::c24E
    cRes_Kinoko,                                    // ProfileID::cKinoko
    cRes_FireFlower,                                // ProfileID::cFireFlower
    cRes_MameKinoko,                                // ProfileID::cMameKinoko
    cRes_IceFlower,                                 // ProfileID::cIceFlower
    cRes_Propeller,                                 // ProfileID::cPropeller
    cRes_Penguin,                                   // ProfileID::cPenguin
    cRes_OneUpKinoko,                               // ProfileID::cOneUpKinoko
    cRes_Musasabi,                                  // ProfileID::cMusasabi
    cRes_SuperMoon,                                 // ProfileID::cSuperMoon
    cRes_TitleDemoItem,                             // ProfileID::cTitleDemoItem
    cRes_259,                                       // ProfileID::c259
    cRes_25A,                                       // ProfileID::c25A
    cRes_25B,                                       // ProfileID::c25B
    cRes_25C,                                       // ProfileID::c25C
    cRes_25D,                                       // ProfileID::c25D
    cRes_25E,                                       // ProfileID::c25E
    cRes_25F,                                       // ProfileID::c25F
    cRes_260,                                       // ProfileID::c260
    cRes_261,                                       // ProfileID::c261
    cRes_262,                                       // ProfileID::c262
    cRes_263,                                       // ProfileID::c263
    cRes_264,                                       // ProfileID::c264
    cRes_265,                                       // ProfileID::c265
    cRes_266,                                       // ProfileID::c266
    cRes_267,                                       // ProfileID::c267
    cRes_268,                                       // ProfileID::c268
    cRes_Spanner,                                   // ProfileID::cSpanner
    cRes_26A,                                       // ProfileID::c26A
    cRes_26B,                                       // ProfileID::c26B
    cRes_26C,                                       // ProfileID::c26C
    cRes_26D,                                       // ProfileID::c26D
    cRes_26E,                                       // ProfileID::c26E
    cRes_26F,                                       // ProfileID::c26F
    cRes_270,                                       // ProfileID::c270
    cRes_271,                                       // ProfileID::c271
    cRes_272,                                       // ProfileID::c272
    nullptr,                                        // ProfileID::c273
    nullptr,                                        // ProfileID::c274
    nullptr,                                        // ProfileID::c275
    nullptr,                                        // ProfileID::c276
    nullptr,                                        // ProfileID::c277
    cRes_278,                                       // ProfileID::c278
    cRes_279,                                       // ProfileID::c279
    cRes_WakiSearchMagKiller,                       // ProfileID::cWakiSearchMagKiller
    cRes_27B,                                       // ProfileID::c27B
    cRes_27C,                                       // ProfileID::c27C
    cRes_27D,                                       // ProfileID::c27D
    cRes_27E,                                       // ProfileID::c27E
    cRes_27F,                                       // ProfileID::c27F
    cRes_GabonRock,                                 // ProfileID::cGabonRock
    cRes_281,                                       // ProfileID::c281
    cRes_282,                                       // ProfileID::c282
    cRes_RockGabonRock,                             // ProfileID::cRockGabonRock
    cRes_284,                                       // ProfileID::c284
    cRes_SeichanSnowBall,                           // ProfileID::cSeichanSnowBall
    cRes_286,                                       // ProfileID::c286
    cRes_287,                                       // ProfileID::c287
    cRes_288,                                       // ProfileID::c288
    cRes_289,                                       // ProfileID::c289
    cRes_28A,                                       // ProfileID::c28A
    cRes_28B,                                       // ProfileID::c28B
    cRes_28C,                                       // ProfileID::c28C
    cRes_28D,                                       // ProfileID::c28D
    cRes_28E,                                       // ProfileID::c28E
    cRes_28F,                                       // ProfileID::c28F
    cRes_290,                                       // ProfileID::c290
    cRes_291,                                       // ProfileID::c291
    cRes_292,                                       // ProfileID::c292
    cRes_293,                                       // ProfileID::c293
    cRes_294,                                       // ProfileID::c294
    cRes_295,                                       // ProfileID::c295
    cRes_296,                                       // ProfileID::c296
    cRes_297,                                       // ProfileID::c297
    cRes_298,                                       // ProfileID::c298
    cRes_299,                                       // ProfileID::c299
    cRes_29A,                                       // ProfileID::c29A
    cRes_29B,                                       // ProfileID::c29B
    nullptr,                                        // ProfileID::c29C
    cRes_29D,                                       // ProfileID::c29D
    cRes_29E,                                       // ProfileID::c29E
    cRes_29F,                                       // ProfileID::c29F
    cRes_2A0,                                       // ProfileID::c2A0
    cRes_2A1,                                       // ProfileID::c2A1
    cRes_2A2,                                       // ProfileID::c2A2
    cRes_2A3,                                       // ProfileID::c2A3
    cRes_2A4,                                       // ProfileID::c2A4
    cRes_2A5,                                       // ProfileID::c2A5
    cRes_Bun,                                       // ProfileID::cBun
    cRes_BunW2,                                     // ProfileID::cBunW2
    cRes_BunW3,                                     // ProfileID::cBunW3
    cRes_BunW4,                                     // ProfileID::cBunW4
    cRes_BunW5,                                     // ProfileID::cBunW5
    cRes_BunW6,                                     // ProfileID::cBunW6
    cRes_BunDemo,                                   // ProfileID::cBunDemo
    nullptr,                                        // ProfileID::cKokoopaDemo
    nullptr,                                        // ProfileID::cKoopaJrDemo
    nullptr,                                        // ProfileID::cKameckDemo
    cRes_BossKKDemo,                                // ProfileID::cBossKKDemo
    nullptr,                                        // ProfileID::cPeachFinalCastleKoopaJrDemo
    cRes_KoopaDemo,                                 // ProfileID::cKoopaDemo
    nullptr,                                        // ProfileID::cFinalKoopaDemo
    nullptr,                                        // ProfileID::cPeachDemo
    cRes_Larry,                                     // ProfileID::cLarry
    cRes_KokoopaSearchFire,                         // ProfileID::cKokoopaSearchFire
    cRes_Lemmy,                                     // ProfileID::cLemmy
    cRes_Morton,                                    // ProfileID::cMorton
    cRes_MortonSanbo,                               // ProfileID::cMortonSanbo
    cRes_MortonSanboParts,                          // ProfileID::cMortonSanboParts
    cRes_Wendy,                                     // ProfileID::cWendy
    cRes_WendyRing,                                 // ProfileID::cWendyRing
    cRes_Ludwig,                                    // ProfileID::cLudwig
    cRes_LudwigAlterEgo,                            // ProfileID::cLudwigAlterEgo
    cRes_Iggy,                                      // ProfileID::cIggy
    nullptr,                                        // ProfileID::cIggyMagic
    cRes_Woogan,                                    // ProfileID::cWoogan
    cRes_Roy,                                       // ProfileID::cRoy
    cRes_RoyLiftWaki,                               // ProfileID::cRoyLiftWaki
    cRes_BossKK,                                    // ProfileID::cBossKK
    nullptr,                                        // ProfileID::cBossKKThunder
    cRes_Kameck,                                    // ProfileID::cKameck
    nullptr,                                        // ProfileID::cKameckIceConfig
    nullptr,                                        // ProfileID::cKameckWarpPos
    nullptr,                                        // ProfileID::cKameckMagic
    cRes_PeachFinalCastleKoopaJr,                   // ProfileID::cPeachFinalCastleKoopaJr
    cRes_Koopa,                                     // ProfileID::cKoopa
    cRes_KoopaFireWaki,                             // ProfileID::cKoopaFireWaki
    cRes_KoopaFire,                                 // ProfileID::cKoopaFire
    cRes_DemoKoopaJrClown,                          // ProfileID::cDemoKoopaJrClown
    cRes_DemoKoopaJr,                               // ProfileID::cDemoKoopaJr
    cRes_BunDemoKameck,                             // ProfileID::cBunDemoKameck
    cRes_KoopaDemoKameck,                           // ProfileID::cKoopaDemoKameck
    cRes_BossKKDemoKameck,                          // ProfileID::cBossKKDemoKameck
    cRes_BossKKDemoKK,                              // ProfileID::cBossKKDemoKK
    cRes_FinalKoopaFire,                            // ProfileID::cFinalKoopaFire
    cRes_FinalKoopaJr,                              // ProfileID::cFinalKoopaJr
    nullptr,                                        // ProfileID::cFinalKoopaJrFire
    cRes_FinalBomhei,                               // ProfileID::cFinalBomhei
    cRes_KokoopaShipLemmy,                          // ProfileID::cKokoopaShipLemmy
    cRes_KokoopaShipMorton,                         // ProfileID::cKokoopaShipMorton
    cRes_KokoopaShipLarry,                          // ProfileID::cKokoopaShipLarry
    cRes_KokoopaShipWendy,                          // ProfileID::cKokoopaShipWendy
    cRes_KokoopaShipIggy,                           // ProfileID::cKokoopaShipIggy
    cRes_KokoopaShipRoy,                            // ProfileID::cKokoopaShipRoy
    cRes_KokoopaShipLudwig,                         // ProfileID::cKokoopaShipLudwig
    cRes_Peach,                                     // ProfileID::cPeach
    cRes_2E0,                                       // ProfileID::c2E0
    nullptr,                                        // ProfileID::cFinalDVPeach
    nullptr,                                        // ProfileID::cFinalDVShutter
    cRes_2E3,                                       // ProfileID::c2E3
    cRes_2E4,                                       // ProfileID::c2E4
    cRes_2E5,                                       // ProfileID::c2E5
    cRes_2E6,                                       // ProfileID::c2E6
    cRes_2E7,                                       // ProfileID::c2E7
    cRes_2E8,                                       // ProfileID::c2E8
    nullptr,                                        // ProfileID::c2E9
    nullptr,                                        // ProfileID::c2EA
    nullptr,                                        // ProfileID::c2EB
    nullptr,                                        // ProfileID::c2EC
    nullptr,                                        // ProfileID::c2ED
    cRes_2EE,                                       // ProfileID::c2EE
    cRes_2EF,                                       // ProfileID::c2EF
    cRes_2F0,                                       // ProfileID::c2F0
    cRes_2F1,                                       // ProfileID::c2F1
    cRes_2F2,                                       // ProfileID::c2F2
    cRes_2F3,                                       // ProfileID::c2F3
    cRes_2F4,                                       // ProfileID::c2F4
    cRes_2F5,                                       // ProfileID::c2F5
    cRes_Hammer,                                    // ProfileID::cHammer
    cRes_2F7,                                       // ProfileID::c2F7
    cRes_Boomerang,                                 // ProfileID::cBoomerang
    cRes_2F9,                                       // ProfileID::c2F9
    nullptr,                                        // ProfileID::cFireBallBros
    cRes_2FB,                                       // ProfileID::c2FB
    nullptr,                                        // ProfileID::cIceBallBros
    cRes_2FD,                                       // ProfileID::c2FD
    cRes_MegaHammer,                                // ProfileID::cMegaHammer
    cRes_2FF,                                       // ProfileID::c2FF
    cRes_300,                                       // ProfileID::c300
    cRes_301,                                       // ProfileID::c301
    cRes_302,                                       // ProfileID::c302
    cRes_303,                                       // ProfileID::c303
    cRes_304,                                       // ProfileID::c304
    cRes_305,                                       // ProfileID::c305
    cRes_306,                                       // ProfileID::c306
    cRes_307,                                       // ProfileID::c307
    cRes_308,                                       // ProfileID::c308
    cRes_309,                                       // ProfileID::c309
    cRes_30A,                                       // ProfileID::c30A
    cRes_30B,                                       // ProfileID::c30B
    cRes_30C,                                       // ProfileID::c30C
    cRes_30D,                                       // ProfileID::c30D
    nullptr,                                        // ProfileID::c30E
    cRes_30F,                                       // ProfileID::c30F
    cRes_310,                                       // ProfileID::c310
    cRes_311,                                       // ProfileID::c311
    cRes_312,                                       // ProfileID::c312
    cRes_313,                                       // ProfileID::c313
    cRes_314,                                       // ProfileID::c314
    cRes_315,                                       // ProfileID::c315
    cRes_316,                                       // ProfileID::c316
    cRes_317,                                       // ProfileID::c317
    cRes_318,                                       // ProfileID::c318
    nullptr,                                        // ProfileID::c319
    nullptr,                                        // ProfileID::c31A
    nullptr,                                        // ProfileID::c31B
    cRes_31C,                                       // ProfileID::c31C
    cRes_31D,                                       // ProfileID::c31D
    nullptr,                                        // ProfileID::c31E
    cRes_31F,                                       // ProfileID::c31F
    cRes_320,                                       // ProfileID::c320
    cRes_321,                                       // ProfileID::c321
    cRes_322,                                       // ProfileID::c322
    cRes_323,                                       // ProfileID::c323
    cRes_324,                                       // ProfileID::c324
    cRes_325,                                       // ProfileID::c325
    cRes_326,                                       // ProfileID::c326
    cRes_327,                                       // ProfileID::c327
    nullptr,                                        // ProfileID::c328
    cRes_BattleItem,                                // ProfileID::cBattleItem
    cRes_32A,                                       // ProfileID::c32A
    cRes_VsBattleItem,                              // ProfileID::cVsBattleItem
    cRes_32C,                                       // ProfileID::c32C
    cRes_32D,                                       // ProfileID::c32D
    nullptr,                                        // ProfileID::c32E
    cRes_32F,                                       // ProfileID::c32F
    cRes_330,                                       // ProfileID::c330
    cRes_331,                                       // ProfileID::c331
    cRes_KoopaJrFire,                               // ProfileID::cKoopaJrFire
    cRes_KoopaJrBall,                               // ProfileID::cKoopaJrBall
    cRes_UnderwaterKoopaJr,                         // ProfileID::cUnderwaterKoopaJr
    cRes_UnderwaterKoopaJrClown,                    // ProfileID::cUnderwaterKoopaJrClown
    cRes_UnderwaterKoopaJrRetreatPos,               // ProfileID::cUnderwaterKoopaJrRetreatPos
    cRes_BoxingKoopaJr,                             // ProfileID::cBoxingKoopaJr
    cRes_BoxingKoopaJrPostBattleDemo,               // ProfileID::cBoxingKoopaJrPostBattleDemo
    cRes_BoxingKoopaJrClownPostBattleDemo,          // ProfileID::cBoxingKoopaJrClownPostBattleDemo
    cRes_MiniGamePanelItem,                         // ProfileID::cMiniGamePanelItem
    cRes_SlotItem,                                  // ProfileID::cSlotItem
    cRes_CoinmakiCannon,                            // ProfileID::cCoinmakiCannon
    cRes_CoinmakiItem,                              // ProfileID::cCoinmakiItem
    cRes_MiniGameKinopio,                           // ProfileID::cMiniGameKinopio
    cRes_33F,                                       // ProfileID::c33F
    cRes_340,                                       // ProfileID::c340
    cRes_341,                                       // ProfileID::c341
    cRes_342,                                       // ProfileID::c342
    nullptr,                                        // ProfileID::c343
    nullptr,                                        // ProfileID::c344
    nullptr,                                        // ProfileID::c345
    nullptr,                                        // ProfileID::c346
    nullptr,                                        // ProfileID::c347
    cRes_StaffCreditChibiYoshiABC,                  // ProfileID::cStaffCreditChibiYoshiABC
    cRes_StaffCreditChibiYoshiBalloon,              // ProfileID::cStaffCreditChibiYoshiBalloon
    cRes_StaffCreditChibiYoshiBalloonCheer,         // ProfileID::cStaffCreditChibiYoshiBalloonCheer
    cRes_StaffCreditChibiYoshiLight,                // ProfileID::cStaffCreditChibiYoshiLight
    cRes_StaffCreditChibiYoshiLightCheer,           // ProfileID::cStaffCreditChibiYoshiLightCheer
    cRes_StaffCreditSoapABC,                        // ProfileID::cStaffCreditSoapABC
    cRes_StaffCreditSoapCoin,                       // ProfileID::cStaffCreditSoapCoin
    cRes_StaffCreditTottenKun,                      // ProfileID::cStaffCreditTottenKun
    nullptr,                                        // ProfileID::c350
    nullptr,                                        // ProfileID::c351
    nullptr,                                        // ProfileID::c352
    nullptr,                                        // ProfileID::c353
    cRes_RealizeFeverStar,                          // ProfileID::cRealizeFeverStar
    cRes_Star,                                      // ProfileID::cStar
    cRes_CourseSelectPlayer,                        // ProfileID::cCourseSelectPlayer
    cRes_CourseSelectPlayer2PSub,                   // ProfileID::cCourseSelectPlayer2PSub
    cRes_CourseSelectChibiYoshi,                    // ProfileID::cCourseSelectChibiYoshi
    nullptr,                                        // ProfileID::cCourseSelectCamera
    cRes_CourseSelectCastle,                        // ProfileID::cCourseSelectCastle
    cRes_CourseSelectToride,                        // ProfileID::cCourseSelectToride
    cRes_CourseSelectKinokoHouse1up,                // ProfileID::cCourseSelectKinokoHouse1up
    cRes_CourseSelectKinokoHouseShuffle,            // ProfileID::cCourseSelectKinokoHouseShuffle
    cRes_CourseSelectKinokoHouseSlot,               // ProfileID::cCourseSelectKinokoHouseSlot
    cRes_CourseSelectPeachGates1st,                 // ProfileID::cCourseSelectPeachGates1st
    cRes_CourseSelectPeachGates2nd,                 // ProfileID::cCourseSelectPeachGates2nd
    cRes_CourseSelectCoursePoint,                   // ProfileID::cCourseSelectCoursePoint
    cRes_CourseSelectWorldMoveDokan,                // ProfileID::cCourseSelectWorldMoveDokan
    nullptr,                                        // ProfileID::cCourseSelectW8Cloud
    cRes_CourseSelectGhost,                         // ProfileID::cCourseSelectGhost
    cRes_CourseSelectW2Bros,                        // ProfileID::cCourseSelectW2Bros
    cRes_CourseSelectShipW1,                        // ProfileID::cCourseSelectShipW1
    cRes_CourseSelectShipW2,                        // ProfileID::cCourseSelectShipW2
    cRes_CourseSelectShipW3,                        // ProfileID::cCourseSelectShipW3
    cRes_CourseSelectShipW4,                        // ProfileID::cCourseSelectShipW4
    cRes_CourseSelectShipW5,                        // ProfileID::cCourseSelectShipW5
    cRes_CourseSelectShipW6,                        // ProfileID::cCourseSelectShipW6
    cRes_CourseSelectShipW7,                        // ProfileID::cCourseSelectShipW7
    cRes_CourseSelectShipW8,                        // ProfileID::cCourseSelectShipW8
    cRes_CourseSelectShipW8Broken,                  // ProfileID::cCourseSelectShipW8Broken
    cRes_CourseSelectSurrender,                     // ProfileID::cCourseSelectSurrender
    cRes_CourseSelectSwitchA,                       // ProfileID::cCourseSelectSwitchA
    cRes_CourseSelectSwitchB,                       // ProfileID::cCourseSelectSwitchB
    cRes_CourseSelectTeresa,                        // ProfileID::cCourseSelectTeresa
    cRes_CourseSelectOpeningKameck,                 // ProfileID::cCourseSelectOpeningKameck
    cRes_CourseSelectTorideBoss,                    // ProfileID::cCourseSelectTorideBoss
    cRes_CourseSelectPakkun,                        // ProfileID::cCourseSelectPakkun
    cRes_CourseSelectShadowFirstDemoKinopio,        // ProfileID::cCourseSelectShadowFirstDemoKinopio
    cRes_CourseSelectTobiPuku,                      // ProfileID::cCourseSelectTobiPuku
    cRes_CourseSelectChorobon,                      // ProfileID::cCourseSelectChorobon
    cRes_CourseSelectW7Item,                        // ProfileID::cCourseSelectW7Item
    cRes_CourseSelectW5Teresa,                      // ProfileID::cCourseSelectW5Teresa
    cRes_CourseSelectFlag,                          // ProfileID::cCourseSelectFlag
    cRes_CourseSelectMusasabi,                      // ProfileID::cCourseSelectMusasabi
    cRes_CourseSelectWPillar,                       // ProfileID::cCourseSelectWPillar
    cRes_CourseSelectW7Bridge,                      // ProfileID::cCourseSelectW7Bridge
    cRes_CourseSelectMiiBalloon,                    // ProfileID::cCourseSelectMiiBalloon
    cRes_CourseSelectPenguin,                       // ProfileID::cCourseSelectPenguin
    cRes_CourseSelectW4Item,                        // ProfileID::cCourseSelectW4Item
    cRes_CourseSelectW2Kuribo,                      // ProfileID::cCourseSelectW2Kuribo
    cRes_CourseSelectPakkunBig,                     // ProfileID::cCourseSelectPakkunBig
    cRes_CourseSelectShadowKunIcon,                 // ProfileID::cCourseSelectShadowKunIcon
    cRes_CourseSelectDekaUnira,                     // ProfileID::cCourseSelectDekaUnira
    cRes_CourseSelectTomb,                          // ProfileID::cCourseSelectTomb
    cRes_CourseSelectShadowFirstDemoShadowKun,      // ProfileID::cCourseSelectShadowFirstDemoShadowKun
    cRes_CourseSelectKotsuCoaster,                  // ProfileID::cCourseSelectKotsuCoaster
    cRes_CourseSelectKoopaJr,                       // ProfileID::cCourseSelectKoopaJr
    cRes_CourseSelectPeach,                         // ProfileID::cCourseSelectPeach
    cRes_CourseSelectW1Item,                        // ProfileID::cCourseSelectW1Item
    cRes_CourseSelectStarGate,                      // ProfileID::cCourseSelectStarGate
    nullptr,                                        // ProfileID::cCourseSelectEventAssistant
    cRes_38E,                                       // Profile 910
    cRes_38F,                                       // Profile 911
    nullptr                                         // Profile 912
};
