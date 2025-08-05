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

enum DrawPriority
{
    cDrawPriority_1B9                                       =   0,
    cDrawPriority_PlayerObject                              =   1,
    cDrawPriority_TottenPlayer                              =   2,
    cDrawPriority_Yoshi                                     =   3,
    cDrawPriority_1BD                                       =   4,
    cDrawPriority_1D3                                       =   5,
    cDrawPriority_1D4                                       =   6,
    cDrawPriority_1D5                                       =   7,
    cDrawPriority_1D6                                       =   8,
    cDrawPriority_1D7                                       =   9,
    cDrawPriority_1D8                                       =  10,
    cDrawPriority_1D9                                       =  11,
    cDrawPriority_IceBall                                   =  12,
    cDrawPriority_IceBallPakkun                             =  13,
    cDrawPriority_FireBallPlayer                            =  14,
    cDrawPriority_FireBallPakkun                            =  15,
    cDrawPriority_YoshiFire                                 =  16,
    cDrawPriority_1DF                                       =  17,
    cDrawPriority_1E0                                       =  18,
    cDrawPriority_1E1                                       =  19,
    cDrawPriority_1E2                                       =  20,
    cDrawPriority_305                                       =  21,
    cDrawPriority_306                                       =  22,
    cDrawPriority_307                                       =  23,
    cDrawPriority_308                                       =  24,
    cDrawPriority_309                                       =  25,
    cDrawPriority_1E3                                       =  26,
    cDrawPriority_1E4                                       =  27,
    cDrawPriority_1E5                                       =  28,
    cDrawPriority_1E6                                       =  29,
    cDrawPriority_1E7                                       =  30,
    cDrawPriority_1E8                                       =  31,
    cDrawPriority_1E9                                       =  32,
    cDrawPriority_1EA                                       =  33,
    cDrawPriority_1EB                                       =  34,
    cDrawPriority_1EC                                       =  35,
    cDrawPriority_1ED                                       =  36,
    cDrawPriority_1EE                                       =  37,
    cDrawPriority_1EF                                       =  38,
    cDrawPriority_1F0                                       =  39,
    cDrawPriority_1F1                                       =  40,
    cDrawPriority_1F2                                       =  41,
    cDrawPriority_1F3                                       =  42,
    cDrawPriority_1F4                                       =  43,
    cDrawPriority_1F5                                       =  44,
    cDrawPriority_1F6                                       =  45,
    cDrawPriority_1F7                                       =  46,
    cDrawPriority_11B                                       =  47,
    cDrawPriority_14D                                       =  48,
    cDrawPriority_14E                                       =  49,
    cDrawPriority_14F                                       =  50,
    cDrawPriority_150                                       =  51,
    cDrawPriority_151                                       =  52,
    cDrawPriority_152                                       =  53,
    cDrawPriority_153                                       =  54,
    cDrawPriority_154                                       =  55,
    cDrawPriority_082                                       =  56,
    cDrawPriority_083                                       =  57,
    cDrawPriority_084                                       =  58,
    cDrawPriority_085                                       =  59,
    cDrawPriority_155                                       =  60,
    cDrawPriority_156                                       =  61,
    cDrawPriority_157                                       =  62,
    cDrawPriority_086                                       =  63,
    cDrawPriority_087                                       =  64,
    cDrawPriority_088                                       =  65,
    cDrawPriority_089                                       =  66,
    cDrawPriority_08A                                       =  67,
    cDrawPriority_08B                                       =  68,
    cDrawPriority_08C                                       =  69,
    cDrawPriority_08D                                       =  70,
    cDrawPriority_08E                                       =  71,
    cDrawPriority_05F                                       =  72,
    cDrawPriority_060                                       =  73,
    cDrawPriority_061                                       =  74,
    cDrawPriority_102                                       =  75,
    cDrawPriority_08F                                       =  76,
    cDrawPriority_090                                       =  77,
    cDrawPriority_062                                       =  78,
    cDrawPriority_063                                       =  79,
    cDrawPriority_05C                                       =  80,
    cDrawPriority_05D                                       =  81,
    cDrawPriority_05E                                       =  82,
    cDrawPriority_064                                       =  83,
    cDrawPriority_091                                       =  84,
    cDrawPriority_092                                       =  85,
    cDrawPriority_1FF                                       =  86,
    cDrawPriority_Nokonoko                                  =  87,
    cDrawPriority_201                                       =  88,
    cDrawPriority_202                                       =  89,
    cDrawPriority_203                                       =  90,
    cDrawPriority_204                                       =  91,
    cDrawPriority_17D                                       =  92,
    cDrawPriority_17E                                       =  93,
    cDrawPriority_205                                       =  94,
    cDrawPriority_206                                       =  95,
    cDrawPriority_208                                       =  96,
    cDrawPriority_207                                       =  97,
    cDrawPriority_209                                       =  98,
    cDrawPriority_20A                                       =  99,
    cDrawPriority_20B                                       = 100,
    cDrawPriority_MechaKoopa                                = 101,
    cDrawPriority_20D                                       = 102,
    cDrawPriority_20E                                       = 103,
    cDrawPriority_16A                                       = 104,
    cDrawPriority_210                                       = 105,
    cDrawPriority_211                                       = 106,
    cDrawPriority_212                                       = 107,
    cDrawPriority_213                                       = 108,
    cDrawPriority_214                                       = 109,
    cDrawPriority_215                                       = 110,
    cDrawPriority_216                                       = 111,
    cDrawPriority_217                                       = 112,
    cDrawPriority_218                                       = 113,
    cDrawPriority_219                                       = 114,
    cDrawPriority_21A                                       = 115,
    cDrawPriority_21B                                       = 116,
    cDrawPriority_21C                                       = 117,
    cDrawPriority_21D                                       = 118,
    cDrawPriority_224                                       = 119,
    cDrawPriority_17F                                       = 120,
    cDrawPriority_180                                       = 121,
    cDrawPriority_181                                       = 122,
    cDrawPriority_182                                       = 123,
    cDrawPriority_225                                       = 124,
    cDrawPriority_226                                       = 125,
    cDrawPriority_229                                       = 126,
    cDrawPriority_22A                                       = 127,
    cDrawPriority_FireBar                                   = 128,
    cDrawPriority_FireBarSync                               = 129,
    cDrawPriority_179                                       = 130,
    cDrawPriority_17A                                       = 131,
    cDrawPriority_Burner                                    = 132,
    cDrawPriority_0E1                                       = 133,
    cDrawPriority_0E2                                       = 134,
    cDrawPriority_0E3                                       = 135,
    cDrawPriority_0EB                                       = 136,
    cDrawPriority_22C                                       = 137,
    cDrawPriority_22D                                       = 138,
    cDrawPriority_FireBallKeronpa                           = 139,
    cDrawPriority_FireBallKeronpaRDash                      = 140,
    cDrawPriority_FireSnake                                 = 141,
    cDrawPriority_27D                                       = 142,
    cDrawPriority_27E                                       = 143,
    cDrawPriority_27F                                       = 144,
    cDrawPriority_GabonRock                                 = 145,
    cDrawPriority_281                                       = 146,
    cDrawPriority_282                                       = 147,
    cDrawPriority_RockGabonRock                             = 148,
    cDrawPriority_284                                       = 149,
    cDrawPriority_SeichanSnowBall                           = 150,
    cDrawPriority_286                                       = 151,
    cDrawPriority_232                                       = 152,
    cDrawPriority_233                                       = 153,
    cDrawPriority_234                                       = 154,
    cDrawPriority_236                                       = 155,
    cDrawPriority_237                                       = 156,
    cDrawPriority_238                                       = 157,
    cDrawPriority_239                                       = 158,
    cDrawPriority_23A                                       = 159,
    cDrawPriority_23B                                       = 160,
    cDrawPriority_23C                                       = 161,
    cDrawPriority_23D                                       = 162,
    cDrawPriority_Kazandan                                  = 163,
    cDrawPriority_Bun                                       = 164,
    cDrawPriority_BunW2                                     = 165,
    cDrawPriority_BunW3                                     = 166,
    cDrawPriority_BunW4                                     = 167,
    cDrawPriority_BunW5                                     = 168,
    cDrawPriority_BunW6                                     = 169,
    cDrawPriority_BunDemoKameck                             = 170,
    cDrawPriority_LemmyBomb                                 = 171,
    cDrawPriority_Lemmy                                     = 172,
    cDrawPriority_LemmyBall                                 = 173,
    cDrawPriority_Morton                                    = 174,
    cDrawPriority_MortonSanbo                               = 175,
    cDrawPriority_MortonSanboParts                          = 176,
    cDrawPriority_Wendy                                     = 177,
    cDrawPriority_WendyRing                                 = 178,
    cDrawPriority_WendyIcicle                               = 179,
    cDrawPriority_WendyFloor                                = 180,
    cDrawPriority_Larry                                     = 181,
    cDrawPriority_KokoopaSearchFire                         = 182,
    cDrawPriority_Ludwig                                    = 183,
    cDrawPriority_LudwigAlterEgo                            = 184,
    cDrawPriority_Iggy                                      = 185,
    cDrawPriority_IggyMagic                                 = 186,
    cDrawPriority_IggyRoom                                  = 187,
    cDrawPriority_Woogan                                    = 188,
    cDrawPriority_Roy                                       = 189,
    cDrawPriority_BossKK                                    = 190,
    cDrawPriority_BossKKThunder                             = 191,
    cDrawPriority_BossKKDemoKameck                          = 192,
    cDrawPriority_BossKKDemoKK                              = 193,
    cDrawPriority_Kameck                                    = 194,
    cDrawPriority_KameckIce                                 = 195,
    cDrawPriority_KameckMagic                               = 196,
    cDrawPriority_PeachFinalCastleKoopaJr                   = 197,
    cDrawPriority_PeachFinalCastleKoopaJrClown              = 198,
    cDrawPriority_PeachFinalCastleKoopaJrLift               = 199,
    cDrawPriority_PeachFinalCastleKoopaJrLiftHmove          = 200,
    cDrawPriority_PeachFinalCastleKoopaJrLiftPairObj        = 201,
    cDrawPriority_RoyLiftWakiStep                           = 202,
    cDrawPriority_Koopa                                     = 203,
    cDrawPriority_KoopaFire                                 = 204,
    cDrawPriority_KoopaShutter                              = 205,
    cDrawPriority_DemoKoopaJr                               = 206,
    cDrawPriority_DemoKoopaJrClown                          = 207,
    cDrawPriority_KoopaDemoKameck                           = 208,
    cDrawPriority_FinalKoopa                                = 209,
    cDrawPriority_FinalKoopaFire                            = 210,
    cDrawPriority_FinalKoopaJr                              = 211,
    cDrawPriority_FinalKoopaJrClown                         = 212,
    cDrawPriority_FinalKoopaJrFire                          = 213,
    cDrawPriority_FinalBomhei                               = 214,
    cDrawPriority_KinokoLift                                = 215,
    cDrawPriority_KinokoLiftColor                           = 216,
    cDrawPriority_04F                                       = 217,
    cDrawPriority_033                                       = 218,
    cDrawPriority_0AD                                       = 219,
    cDrawPriority_0AE                                       = 220,
    cDrawPriority_0AF                                       = 221,
    cDrawPriority_0B0                                       = 222,
    cDrawPriority_0B1                                       = 223,
    cDrawPriority_050                                       = 224,
    cDrawPriority_17C                                       = 225,
    cDrawPriority_051                                       = 226,
    cDrawPriority_235                                       = 227,
    cDrawPriority_16D                                       = 228,
    cDrawPriority_Block                                     = 229,
    cDrawPriority_1BE                                       = 230,
    cDrawPriority_1BF                                       = 231,
    cDrawPriority_1C4                                       = 232,
    cDrawPriority_1C3                                       = 233,
    cDrawPriority_1C0                                       = 234,
    cDrawPriority_1C1                                       = 235,
    cDrawPriority_1C2                                       = 236,
    cDrawPriority_1C7                                       = 237,
    cDrawPriority_1C8                                       = 238,
    cDrawPriority_1C9                                       = 239,
    cDrawPriority_1CA                                       = 240,
    cDrawPriority_1CB                                       = 241,
    cDrawPriority_1CC                                       = 242,
    cDrawPriority_1CD                                       = 243,
    cDrawPriority_1CE                                       = 244,
    cDrawPriority_QuestPrizeItem                            = 245,
    cDrawPriority_1D0                                       = 246,
    cDrawPriority_1D1                                       = 247,
    cDrawPriority_183                                       = 248,
    cDrawPriority_184                                       = 249,
    cDrawPriority_185                                       = 250,
    cDrawPriority_186                                       = 251,
    cDrawPriority_22B                                       = 252,
    cDrawPriority_187                                       = 253,
    cDrawPriority_Kinoko                                    = 254,
    cDrawPriority_FireFlower                                = 255,
    cDrawPriority_RealizeFeverStar                          = 256,
    cDrawPriority_Star                                      = 257,
    cDrawPriority_MameKinoko                                = 258,
    cDrawPriority_IceFlower                                 = 259,
    cDrawPriority_Propeller                                 = 260,
    cDrawPriority_Penguin                                   = 261,
    cDrawPriority_OneUpKinoko                               = 262,
    cDrawPriority_Musasabi                                  = 263,
    cDrawPriority_SuperMoon                                 = 264,
    cDrawPriority_TitleDemoItem                             = 265,
    cDrawPriority_097                                       = 266,
    cDrawPriority_036                                       = 267,
    cDrawPriority_037                                       = 268,
    cDrawPriority_038                                       = 269,
    cDrawPriority_039                                       = 270,
    cDrawPriority_03A                                       = 271,
    cDrawPriority_03B                                       = 272,
    cDrawPriority_PairObjChild                              = 273,
    cDrawPriority_03D                                       = 274,
    cDrawPriority_03E                                       = 275,
    cDrawPriority_03F                                       = 276,
    cDrawPriority_040                                       = 277,
    cDrawPriority_041                                       = 278,
    cDrawPriority_042                                       = 279,
    cDrawPriority_043                                       = 280,
    cDrawPriority_044                                       = 281,
    cDrawPriority_045                                       = 282,
    cDrawPriority_046                                       = 283,
    cDrawPriority_047                                       = 284,
    cDrawPriority_048                                       = 285,
    cDrawPriority_049                                       = 286,
    cDrawPriority_04A                                       = 287,
    cDrawPriority_04B                                       = 288,
    cDrawPriority_04C                                       = 289,
    cDrawPriority_188                                       = 290,
    cDrawPriority_113                                       = 291,
    cDrawPriority_114                                       = 292,
    cDrawPriority_115                                       = 293,
    cDrawPriority_116                                       = 294,
    cDrawPriority_2E4                                       = 295,
    cDrawPriority_2E5                                       = 296,
    cDrawPriority_2E6                                       = 297,
    cDrawPriority_2E7                                       = 298,
    cDrawPriority_2E8                                       = 299,
    cDrawPriority_2E9                                       = 300,
    cDrawPriority_2EA                                       = 301,
    cDrawPriority_259                                       = 302,
    cDrawPriority_2EE                                       = 303,
    cDrawPriority_2EF                                       = 304,
    cDrawPriority_2F0                                       = 305,
    cDrawPriority_2F1                                       = 306,
    cDrawPriority_2F2                                       = 307,
    cDrawPriority_02B                                       = 308,
    cDrawPriority_02C                                       = 309,
    cDrawPriority_25A                                       = 310,
    cDrawPriority_25B                                       = 311,
    cDrawPriority_25C                                       = 312,
    cDrawPriority_25D                                       = 313,
    cDrawPriority_25E                                       = 314,
    cDrawPriority_25F                                       = 315,
    cDrawPriority_260                                       = 316,
    cDrawPriority_261                                       = 317,
    cDrawPriority_1AA                                       = 318,
    cDrawPriority_1AB                                       = 319,
    cDrawPriority_1AC                                       = 320,
    cDrawPriority_1AD                                       = 321,
    cDrawPriority_1AE                                       = 322,
    cDrawPriority_1AF                                       = 323,
    cDrawPriority_1B0                                       = 324,
    cDrawPriority_1B1                                       = 325,
    cDrawPriority_1B2                                       = 326,
    cDrawPriority_1B3                                       = 327,
    cDrawPriority_076                                       = 328,
    cDrawPriority_077                                       = 329,
    cDrawPriority_078                                       = 330,
    cDrawPriority_1B5                                       = 331,
    cDrawPriority_1B4                                       = 332,
    cDrawPriority_262                                       = 333,
    cDrawPriority_263                                       = 334,
    cDrawPriority_2F3                                       = 335,
    cDrawPriority_0BF                                       = 336,
    cDrawPriority_0C0                                       = 337,
    cDrawPriority_0C1                                       = 338,
    cDrawPriority_Hammer                                    = 339,
    cDrawPriority_2F5                                       = 340,
    cDrawPriority_Boomerang                                 = 341,
    cDrawPriority_2F7                                       = 342,
    cDrawPriority_FireBallBros                              = 343,
    cDrawPriority_2F9                                       = 344,
    cDrawPriority_IceBallBros                               = 345,
    cDrawPriority_2FB                                       = 346,
    cDrawPriority_MegaHammer                                = 347,
    cDrawPriority_2FD                                       = 348,
    cDrawPriority_2FF                                       = 349,
    cDrawPriority_300                                       = 350,
    cDrawPriority_301                                       = 351,
    cDrawPriority_121                                       = 352,
    cDrawPriority_122                                       = 353,
    cDrawPriority_ActorBlockRenga                           = 354,
    cDrawPriority_124                                       = 355,
    cDrawPriority_125                                       = 356,
    cDrawPriority_126                                       = 357,
    cDrawPriority_127                                       = 358,
    cDrawPriority_128                                       = 359,
    cDrawPriority_129                                       = 360,
    cDrawPriority_12A                                       = 361,
    cDrawPriority_12B                                       = 362,
    cDrawPriority_12C                                       = 363,
    cDrawPriority_12D                                       = 364,
    cDrawPriority_12E                                       = 365,
    cDrawPriority_12F                                       = 366,
    cDrawPriority_130                                       = 367,
    cDrawPriority_131                                       = 368,
    cDrawPriority_132                                       = 369,
    cDrawPriority_133                                       = 370,
    cDrawPriority_134                                       = 371,
    cDrawPriority_13F                                       = 372,
    cDrawPriority_140                                       = 373,
    cDrawPriority_135                                       = 374,
    cDrawPriority_136                                       = 375,
    cDrawPriority_137                                       = 376,
    cDrawPriority_138                                       = 377,
    cDrawPriority_13A                                       = 378,
    cDrawPriority_13B                                       = 379,
    cDrawPriority_0E4                                       = 380,
    cDrawPriority_0F5                                       = 381,
    cDrawPriority_0F6                                       = 382,
    cDrawPriority_0F7                                       = 383,
    cDrawPriority_0F8                                       = 384,
    cDrawPriority_0F9                                       = 385,
    cDrawPriority_139                                       = 386,
    cDrawPriority_13C                                       = 387,
    cDrawPriority_13D                                       = 388,
    cDrawPriority_13E                                       = 389,
    cDrawPriority_141                                       = 390,
    cDrawPriority_142                                       = 391,
    cDrawPriority_143                                       = 392,
    cDrawPriority_14B                                       = 393,
    cDrawPriority_ActorCoin                                 = 394,
    cDrawPriority_18C                                       = 395,
    cDrawPriority_18D                                       = 396,
    cDrawPriority_18E                                       = 397,
    cDrawPriority_18F                                       = 398,
    cDrawPriority_190                                       = 399,
    cDrawPriority_191                                       = 400,
    cDrawPriority_192                                       = 401,
    cDrawPriority_193                                       = 402,
    cDrawPriority_194                                       = 403,
    cDrawPriority_195                                       = 404,
    cDrawPriority_196                                       = 405,
    cDrawPriority_197                                       = 406,
    cDrawPriority_198                                       = 407,
    cDrawPriority_199                                       = 408,
    cDrawPriority_19A                                       = 409,
    cDrawPriority_19B                                       = 410,
    cDrawPriority_19C                                       = 411,
    cDrawPriority_19D                                       = 412,
    cDrawPriority_19E                                       = 413,
    cDrawPriority_1A0                                       = 414,
    cDrawPriority_19F                                       = 415,
    cDrawPriority_032                                       = 416,
    cDrawPriority_1A1                                       = 417,
    cDrawPriority_1A2                                       = 418,
    cDrawPriority_1A3                                       = 419,
    cDrawPriority_1A4                                       = 420,
    cDrawPriority_1A5                                       = 421,
    cDrawPriority_1A6                                       = 422,
    cDrawPriority_1A7                                       = 423,
    cDrawPriority_1A8                                       = 424,
    cDrawPriority_BlueCoin                                  = 425,
    cDrawPriority_264                                       = 426,
    cDrawPriority_1F9                                       = 427,
    cDrawPriority_1FA                                       = 428,
    cDrawPriority_1FB                                       = 429,
    cDrawPriority_1FC                                       = 430,
    cDrawPriority_1FD                                       = 431,
    cDrawPriority_1FE                                       = 432,
    cDrawPriority_311                                       = 433,
    cDrawPriority_312                                       = 434,
    cDrawPriority_052                                       = 435,
    cDrawPriority_053                                       = 436,
    cDrawPriority_0C5                                       = 437,
    cDrawPriority_0C6                                       = 438,
    cDrawPriority_265                                       = 439,
    cDrawPriority_KillerHoudai                              = 440,
    cDrawPriority_StretchKillerHoudai                       = 441,
    cDrawPriority_MagnumKillerHoudai                        = 442,
    cDrawPriority_MagnumKillerHoudaiDown                    = 443,
    cDrawPriority_SearchKillerHoudai                        = 444,
    cDrawPriority_SearchMagnumKillerHoudai                  = 445,
    cDrawPriority_SearchMagnumKillerHoudaiDown              = 446,
    cDrawPriority_MagnumKillerHoudaiRDash                   = 447,
    cDrawPriority_MagnumKillerHoudaiDownRDash               = 448,
    cDrawPriority_SearchMagnumKillerHoudaiRDash             = 449,
    cDrawPriority_SearchMagnumKillerHoudaiDownRDash         = 450,
    cDrawPriority_070                                       = 451,
    cDrawPriority_071                                       = 452,
    cDrawPriority_072                                       = 453,
    cDrawPriority_073                                       = 454,
    cDrawPriority_074                                       = 455,
    cDrawPriority_273                                       = 456,
    cDrawPriority_075                                       = 457,
    cDrawPriority_274                                       = 458,
    cDrawPriority_275                                       = 459,
    cDrawPriority_SearchKiller                              = 460,
    cDrawPriority_277                                       = 461,
    cDrawPriority_278                                       = 462,
    cDrawPriority_279                                       = 463,
    cDrawPriority_27B                                       = 464,
    cDrawPriority_27C                                       = 465,
    cDrawPriority_SwitchHatenaButton                        = 466,
    cDrawPriority_SwitchPbutton                             = 467,
    cDrawPriority_SwitchPbuttonRDash                        = 468,
    cDrawPriority_SwitchPbuttonNoWallKick                   = 469,
    cDrawPriority_15C                                       = 470,
    cDrawPriority_15D                                       = 471,
    cDrawPriority_313                                       = 472,
    cDrawPriority_314                                       = 473,
    cDrawPriority_315                                       = 474,
    cDrawPriority_316                                       = 475,
    cDrawPriority_317                                       = 476,
    cDrawPriority_318                                       = 477,
    cDrawPriority_319                                       = 478,
    cDrawPriority_TarzanIvy                                 = 479,
    cDrawPriority_0EF                                       = 480,
    cDrawPriority_0F0                                       = 481,
    cDrawPriority_SnakeBlock                                = 482,
    cDrawPriority_0C3                                       = 483,
    cDrawPriority_0C4                                       = 484,
    cDrawPriority_0C8                                       = 485,
    cDrawPriority_31E                                       = 486,
    cDrawPriority_31D                                       = 487,
    cDrawPriority_0C7                                       = 488,
    cDrawPriority_0E5                                       = 489,
    cDrawPriority_117                                       = 490,
    cDrawPriority_31F                                       = 491,
    cDrawPriority_166                                       = 492,
    cDrawPriority_2F4                                       = 493,
    cDrawPriority_303                                       = 494,
    cDrawPriority_304                                       = 495,
    cDrawPriority_079                                       = 496,
    cDrawPriority_07A                                       = 497,
    cDrawPriority_07B                                       = 498,
    cDrawPriority_07C                                       = 499,
    cDrawPriority_07D                                       = 500,
    cDrawPriority_07E                                       = 501,
    cDrawPriority_07F                                       = 502,
    cDrawPriority_YoganIntermittent                         = 503,
    cDrawPriority_Woochan                                   = 504,
    cDrawPriority_268                                       = 505,
    cDrawPriority_Spanner                                   = 506,
    cDrawPriority_26A                                       = 507,
    cDrawPriority_26B                                       = 508,
    cDrawPriority_26C                                       = 509,
    cDrawPriority_26D                                       = 510,
    cDrawPriority_26E                                       = 511,
    cDrawPriority_26F                                       = 512,
    cDrawPriority_270                                       = 513,
    cDrawPriority_0B2                                       = 514,
    cDrawPriority_100                                       = 515,
    cDrawPriority_101                                       = 516,
    cDrawPriority_0B3                                       = 517,
    cDrawPriority_16B                                       = 518,
    cDrawPriority_16C                                       = 519,
    cDrawPriority_0B4                                       = 520,
    cDrawPriority_0B5                                       = 521,
    cDrawPriority_0B6                                       = 522,
    cDrawPriority_0B7                                       = 523,
    cDrawPriority_0B8                                       = 524,
    cDrawPriority_0B9                                       = 525,
    cDrawPriority_0BA                                       = 526,
    cDrawPriority_0BC                                       = 527,
    cDrawPriority_081                                       = 528,
    cDrawPriority_093                                       = 529,
    cDrawPriority_094                                       = 530,
    cDrawPriority_095                                       = 531,
    cDrawPriority_096                                       = 532,
    cDrawPriority_ElasticKinokoParent                       = 533,
    cDrawPriority_0CB                                       = 534,
    cDrawPriority_0CC                                       = 535,
    cDrawPriority_0E7                                       = 536,
    cDrawPriority_0E8                                       = 537,
    cDrawPriority_0E6                                       = 538,
    cDrawPriority_0EA                                       = 539,
    cDrawPriority_287                                       = 540,
    cDrawPriority_288                                       = 541,
    cDrawPriority_289                                       = 542,
    cDrawPriority_28B                                       = 543,
    cDrawPriority_28C                                       = 544,
    cDrawPriority_28D                                       = 545,
    cDrawPriority_098                                       = 546,
    cDrawPriority_099                                       = 547,
    cDrawPriority_09A                                       = 548,
    cDrawPriority_09B                                       = 549,
    cDrawPriority_09C                                       = 550,
    cDrawPriority_09D                                       = 551,
    cDrawPriority_09E                                       = 552,
    cDrawPriority_09F                                       = 553,
    cDrawPriority_0A1                                       = 554,
    cDrawPriority_0A2                                       = 555,
    cDrawPriority_0A3                                       = 556,
    cDrawPriority_0A4                                       = 557,
    cDrawPriority_0A5                                       = 558,
    cDrawPriority_0A6                                       = 559,
    cDrawPriority_0A0                                       = 560,
    cDrawPriority_0A7                                       = 561,
    cDrawPriority_0A8                                       = 562,
    cDrawPriority_0A9                                       = 563,
    cDrawPriority_0AA                                       = 564,
    cDrawPriority_0AB                                       = 565,
    cDrawPriority_0AC                                       = 566,
    cDrawPriority_0BE                                       = 567,
    cDrawPriority_0BD                                       = 568,
    cDrawPriority_0BB                                       = 569,
    cDrawPriority_320                                       = 570,
    cDrawPriority_0D3                                       = 571,
    cDrawPriority_0D6                                       = 572,
    cDrawPriority_0D4                                       = 573,
    cDrawPriority_0D5                                       = 574,
    cDrawPriority_0D7                                       = 575,
    cDrawPriority_0D8                                       = 576,
    cDrawPriority_0D9                                       = 577,
    cDrawPriority_0DA                                       = 578,
    cDrawPriority_0DB                                       = 579,
    cDrawPriority_103                                       = 580,
    cDrawPriority_0DC                                       = 581,
    cDrawPriority_0DD                                       = 582,
    cDrawPriority_0FA                                       = 583,
    cDrawPriority_0FB                                       = 584,
    cDrawPriority_162                                       = 585,
    cDrawPriority_29F                                       = 586,
    cDrawPriority_0E9                                       = 587,
    cDrawPriority_29E                                       = 588,
    cDrawPriority_2A1                                       = 589,
    cDrawPriority_2A2                                       = 590,
    cDrawPriority_1F8                                       = 591,
    cDrawPriority_2A3                                       = 592,
    cDrawPriority_104                                       = 593,
    cDrawPriority_16E                                       = 594,
    cDrawPriority_16F                                       = 595,
    cDrawPriority_29D                                       = 596,
    cDrawPriority_30A                                       = 597,
    cDrawPriority_15E                                       = 598,
    cDrawPriority_30B                                       = 599,
    cDrawPriority_30C                                       = 600,
    cDrawPriority_30D                                       = 601,
    cDrawPriority_30E                                       = 602,
    cDrawPriority_30F                                       = 603,
    cDrawPriority_310                                       = 604,
    cDrawPriority_163                                       = 605,
    cDrawPriority_164                                       = 606,
    cDrawPriority_165                                       = 607,
    cDrawPriority_11D                                       = 608,
    cDrawPriority_11E                                       = 609,
    cDrawPriority_0DE                                       = 610,
    cDrawPriority_0DF                                       = 611,
    cDrawPriority_0EC                                       = 612,
    cDrawPriority_FloorGyration                             = 613,
    cDrawPriority_FloorHoleDokan                            = 614,
    cDrawPriority_0D0                                       = 615,
    cDrawPriority_0D1                                       = 616,
    cDrawPriority_0C9                                       = 617,
    cDrawPriority_0CA                                       = 618,
    cDrawPriority_107                                       = 619,
    cDrawPriority_0CD                                       = 620,
    cDrawPriority_0CE                                       = 621,
    cDrawPriority_0CF                                       = 622,
    cDrawPriority_Bubble                                    = 623,
    cDrawPriority_BubbleSync                                = 624,
    cDrawPriority_BubbleRDash                               = 625,
    cDrawPriority_BubbleSyncRDash                           = 626,
    cDrawPriority_292                                       = 627,
    cDrawPriority_293                                       = 628,
    cDrawPriority_294                                       = 629,
    cDrawPriority_295                                       = 630,
    cDrawPriority_298                                       = 631,
    cDrawPriority_299                                       = 632,
    cDrawPriority_29A                                       = 633,
    cDrawPriority_29B                                       = 634,
    cDrawPriority_29C                                       = 635,
    cDrawPriority_161                                       = 636,
    cDrawPriority_168                                       = 637,
    cDrawPriority_169                                       = 638,
    cDrawPriority_0F3                                       = 639,
    cDrawPriority_0F4                                       = 640,
    cDrawPriority_322                                       = 641,
    cDrawPriority_323                                       = 642,
    cDrawPriority_324                                       = 643,
    cDrawPriority_325                                       = 644,
    cDrawPriority_0ED                                       = 645,
    cDrawPriority_326                                       = 646,
    cDrawPriority_144                                       = 647,
    cDrawPriority_145                                       = 648,
    cDrawPriority_146                                       = 649,
    cDrawPriority_147                                       = 650,
    cDrawPriority_0F1                                       = 651,
    cDrawPriority_0F2                                       = 652,
    cDrawPriority_327                                       = 653,
    cDrawPriority_328                                       = 654,
    cDrawPriority_BattleItem                                = 655,
    cDrawPriority_VsBattleItem                              = 656,
    cDrawPriority_2A4                                       = 657,
    cDrawPriority_2A5                                       = 658,
    cDrawPriority_321                                       = 659,
    cDrawPriority_32C                                       = 660,
    cDrawPriority_32D                                       = 661,
    cDrawPriority_32F                                       = 662,
    cDrawPriority_330                                       = 663,
    cDrawPriority_331                                       = 664,
    cDrawPriority_32A                                       = 665,
    cDrawPriority_KokoopaShipLemmy                          = 666,
    cDrawPriority_KokoopaShipMorton                         = 667,
    cDrawPriority_KokoopaShipLarry                          = 668,
    cDrawPriority_KokoopaShipWendy                          = 669,
    cDrawPriority_KokoopaShipIggy                           = 670,
    cDrawPriority_KokoopaShipRoy                            = 671,
    cDrawPriority_KokoopaShipLudwig                         = 672,
    cDrawPriority_KokoopaShipWarpCannon                     = 673,
    cDrawPriority_Peach                                     = 674,
    cDrawPriority_2E0                                       = 675,
    cDrawPriority_FinalDVPeach                              = 676,
    cDrawPriority_FinalDVShutter                            = 677,
    cDrawPriority_2E3                                       = 678,
    cDrawPriority_1D2                                       = 679,
    cDrawPriority_148                                       = 680,
    cDrawPriority_149                                       = 681,
    cDrawPriority_14A                                       = 682,
    cDrawPriority_119                                       = 683,
    cDrawPriority_11A                                       = 684,
    cDrawPriority_108                                       = 685,
    cDrawPriority_KoopaJrFire                               = 686,
    cDrawPriority_KoopaJrBall                               = 687,
    cDrawPriority_174                                       = 688,
    cDrawPriority_025                                       = 689,
    cDrawPriority_UnderwaterKoopaJr                         = 690,
    cDrawPriority_UnderwaterKoopaJrClown                    = 691,
    cDrawPriority_UnderwaterKoopaJrRetreatPos               = 692,
    cDrawPriority_BoxingKoopaJr                             = 693,
    cDrawPriority_BoxingKoopaJrClown                        = 694,
    cDrawPriority_BoxingKoopaJrPostBattleDemo               = 695,
    cDrawPriority_BoxingKoopaJrClownPostBattleDemo          = 696,
    cDrawPriority_054                                       = 697,
    cDrawPriority_055                                       = 698,
    cDrawPriority_056                                       = 699,
    cDrawPriority_057                                       = 700,
    cDrawPriority_058                                       = 701,
    cDrawPriority_059                                       = 702,
    cDrawPriority_05A                                       = 703,
    cDrawPriority_05B                                       = 704,
    cDrawPriority_0FC                                       = 705,
    cDrawPriority_0FD                                       = 706,
    cDrawPriority_0FE                                       = 707,
    cDrawPriority_0FF                                       = 708,
    cDrawPriority_SlotYoshiChibi                            = 709,
    cDrawPriority_MiniGamePanelItem                         = 710,
    cDrawPriority_SlotItem                                  = 711,
    cDrawPriority_ShuffleBlock                              = 712,
    cDrawPriority_CoinmakiCoin                              = 713,
    cDrawPriority_CoinmakiItem                              = 714,
    cDrawPriority_CoinmakiCannon                            = 715,
    cDrawPriority_MiniGameKinopio                           = 716,
    cDrawPriority_33F                                       = 717,
    cDrawPriority_340                                       = 718,
    cDrawPriority_341                                       = 719,
    cDrawPriority_342                                       = 720,
    cDrawPriority_10A                                       = 721,
    cDrawPriority_10B                                       = 722,
    cDrawPriority_10C                                       = 723,
    cDrawPriority_118                                       = 724,
    cDrawPriority_17B                                       = 725,
    cDrawPriority_350                                       = 726,
    cDrawPriority_StaffRollMgr                              = 727,
    cDrawPriority_StaffRollMgrRDash                         = 728,
    cDrawPriority_StaffCreditChibiYoshiABC                  = 729,
    cDrawPriority_StaffCreditChibiYoshiBalloon              = 730,
    cDrawPriority_StaffCreditChibiYoshiBalloonCheer         = 731,
    cDrawPriority_StaffCreditChibiYoshiLight                = 732,
    cDrawPriority_StaffCreditChibiYoshiLightCheer           = 733,
    cDrawPriority_StaffCreditSoapABC                        = 734,
    cDrawPriority_StaffCreditSoapCoin                       = 735,
    cDrawPriority_StaffCreditTottenKun                      = 736,
    cDrawPriority_CourseSelectPlayer                        = 737,
    cDrawPriority_CourseSelectPlayer2PSub                   = 738,
    cDrawPriority_CourseSelectChibiYoshi                    = 739,
    cDrawPriority_CourseSelectCamera                        = 740,
    cDrawPriority_CourseSelectCastle                        = 741,
    cDrawPriority_CourseSelectToride                        = 742,
    cDrawPriority_CourseSelectKinokoHouse1up                = 743,
    cDrawPriority_CourseSelectKinokoHouseShuffle            = 744,
    cDrawPriority_CourseSelectKinokoHouseSlot               = 745,
    cDrawPriority_CourseSelectPeachGates1st                 = 746,
    cDrawPriority_CourseSelectPeachGates2nd                 = 747,
    cDrawPriority_CourseSelectCoursePoint                   = 748,
    cDrawPriority_CourseSelectWorldMoveDokan                = 749,
    cDrawPriority_CourseSelectGhost                         = 750,
    cDrawPriority_CourseSelectW8Cloud                       = 751,
    cDrawPriority_CourseSelectW2Bros                        = 752,
    cDrawPriority_CourseSelectEventAssistant                = 753,
    cDrawPriority_CourseSelectShipW1                        = 754,
    cDrawPriority_CourseSelectShipW2                        = 755,
    cDrawPriority_CourseSelectShipW3                        = 756,
    cDrawPriority_CourseSelectShipW4                        = 757,
    cDrawPriority_CourseSelectShipW5                        = 758,
    cDrawPriority_CourseSelectShipW6                        = 759,
    cDrawPriority_CourseSelectShipW7                        = 760,
    cDrawPriority_CourseSelectShipW8                        = 761,
    cDrawPriority_CourseSelectShipW8Broken                  = 762,
    cDrawPriority_CourseSelectSurrender                     = 763,
    cDrawPriority_CourseSelectSwitchA                       = 764,
    cDrawPriority_CourseSelectSwitchB                       = 765,
    cDrawPriority_CourseSelectTeresa                        = 766,
    cDrawPriority_CourseSelectOpeningKameck                 = 767,
    cDrawPriority_CourseSelectTorideBoss                    = 768,
    cDrawPriority_CourseSelectPakkun                        = 769,
    cDrawPriority_CourseSelectShadowFirstDemoKinopio        = 770,
    cDrawPriority_CourseSelectTobiPuku                      = 771,
    cDrawPriority_CourseSelectChorobon                      = 772,
    cDrawPriority_CourseSelectW7Item                        = 773,
    cDrawPriority_CourseSelectW5Teresa                      = 774,
    cDrawPriority_CourseSelectFlag                          = 775,
    cDrawPriority_CourseSelectMusasabi                      = 777,
    cDrawPriority_CourseSelectWPillar                       = 778,
    cDrawPriority_CourseSelectW7Bridge                      = 779,
    cDrawPriority_CourseSelectMiiBalloon                    = 780,
    cDrawPriority_CourseSelectPenguin                       = 781,
    cDrawPriority_CourseSelectW4Item                        = 782,
    cDrawPriority_CourseSelectW2Kuribo                      = 783,
    cDrawPriority_CourseSelectPakkunBig                     = 784,
    cDrawPriority_CourseSelectShadowKunIcon                 = 785,
    cDrawPriority_CourseSelectDekaUnira                     = 786,
    cDrawPriority_CourseSelectTomb                          = 787,
    cDrawPriority_CourseSelectShadowFirstDemoShadowKun      = 788,
    cDrawPriority_CourseSelectKotsuCoaster                  = 789,
    cDrawPriority_CourseSelectKoopaJr                       = 790,
    cDrawPriority_CourseSelectPeach                         = 791,
    cDrawPriority_CourseSelectW1Item                        = 792,
    cDrawPriority_CourseSelectStarGate                      = 793,
    cDrawPriority_38E                                       = 794,
    cDrawPriority_38F                                       = 795,

    // No Draw
    cDrawPriority_390                                       =   0 - 0x3ff,
    cDrawPriority_120                                       =   1 - 0x3ff,
    cDrawPriority_23F                                       =   2 - 0x3ff,
    cDrawPriority_240                                       =   3 - 0x3ff,
    cDrawPriority_241                                       =   4 - 0x3ff,
    cDrawPriority_242                                       =   5 - 0x3ff,
    cDrawPriority_243                                       =   6 - 0x3ff,
    cDrawPriority_244                                       =   7 - 0x3ff,
    cDrawPriority_245                                       =   8 - 0x3ff,
    cDrawPriority_246                                       =   9 - 0x3ff,
    cDrawPriority_247                                       =  10 - 0x3ff,
    cDrawPriority_248                                       =  11 - 0x3ff,
    cDrawPriority_249                                       =  12 - 0x3ff,
    cDrawPriority_24A                                       =  13 - 0x3ff,
    cDrawPriority_BgCenter                                  =  14 - 0x3ff,
    cDrawPriority_24C                                       =  15 - 0x3ff,
    cDrawPriority_24E                                       =  16 - 0x3ff,
    cDrawPriority_000                                       =  17 - 0x3ff,
    cDrawPriority_001                                       =  18 - 0x3ff,
    cDrawPriority_002                                       =  19 - 0x3ff,
    cDrawPriority_003                                       =  20 - 0x3ff,
    cDrawPriority_004                                       =  21 - 0x3ff,
    cDrawPriority_005                                       =  22 - 0x3ff,
    cDrawPriority_006                                       =  23 - 0x3ff,
    cDrawPriority_007                                       =  24 - 0x3ff,
    cDrawPriority_008                                       =  25 - 0x3ff,
    cDrawPriority_009                                       =  26 - 0x3ff,
    cDrawPriority_00B                                       =  27 - 0x3ff,
    cDrawPriority_00C                                       =  28 - 0x3ff,
    cDrawPriority_00D                                       =  29 - 0x3ff,
    cDrawPriority_027                                       =  30 - 0x3ff,
    cDrawPriority_028                                       =  31 - 0x3ff,
    cDrawPriority_029                                       =  32 - 0x3ff,
    cDrawPriority_02A                                       =  33 - 0x3ff,
    cDrawPriority_189                                       =  34 - 0x3ff,
    cDrawPriority_18A                                       =  35 - 0x3ff,
    cDrawPriority_267                                       =  36 - 0x3ff,
    cDrawPriority_266                                       =  37 - 0x3ff,
    cDrawPriority_21E                                       =  38 - 0x3ff,
    cDrawPriority_21F                                       =  39 - 0x3ff,
    cDrawPriority_220                                       =  40 - 0x3ff,
    cDrawPriority_026                                       =  41 - 0x3ff,
    cDrawPriority_223                                       =  42 - 0x3ff,
    cDrawPriority_2EB                                       =  43 - 0x3ff,
    cDrawPriority_271                                       =  44 - 0x3ff,
    cDrawPriority_272                                       =  45 - 0x3ff,
    cDrawPriority_221                                       =  46 - 0x3ff,
    cDrawPriority_222                                       =  47 - 0x3ff,
    cDrawPriority_20F                                       =  48 - 0x3ff,
    cDrawPriority_02D                                       =  49 - 0x3ff,
    cDrawPriority_02E                                       =  50 - 0x3ff,
    cDrawPriority_00E                                       =  51 - 0x3ff,
    cDrawPriority_00F                                       =  52 - 0x3ff,
    cDrawPriority_010                                       =  53 - 0x3ff,
    cDrawPriority_BunDemo                                   =  54 - 0x3ff,
    cDrawPriority_KokoopaDemo                               =  55 - 0x3ff,
    cDrawPriority_KoopaJrDemo                               =  56 - 0x3ff,
    cDrawPriority_KameckDemo                                =  57 - 0x3ff,
    cDrawPriority_BossKKDemo                                =  58 - 0x3ff,
    cDrawPriority_PeachFinalCastleKoopaJrDemo               =  59 - 0x3ff,
    cDrawPriority_KoopaDemo                                 =  60 - 0x3ff,
    cDrawPriority_FinalKoopaDemo                            =  61 - 0x3ff,
    cDrawPriority_PeachDemo                                 =  62 - 0x3ff,
    cDrawPriority_KameckIceConfig                           =  63 - 0x3ff,
    cDrawPriority_KameckWarpPos                             =  64 - 0x3ff,
    cDrawPriority_011                                       =  65 - 0x3ff,
    cDrawPriority_012                                       =  66 - 0x3ff,
    cDrawPriority_02F                                       =  67 - 0x3ff,
    cDrawPriority_030                                       =  68 - 0x3ff,
    cDrawPriority_2EC                                       =  69 - 0x3ff,
    cDrawPriority_2ED                                       =  70 - 0x3ff,
    cDrawPriority_00A                                       =  71 - 0x3ff,
    cDrawPriority_014                                       =  72 - 0x3ff,
    cDrawPriority_031                                       =  73 - 0x3ff,
    cDrawPriority_167                                       =  74 - 0x3ff,
    cDrawPriority_015                                       =  75 - 0x3ff,
    cDrawPriority_016                                       =  76 - 0x3ff,
    cDrawPriority_017                                       =  77 - 0x3ff,
    cDrawPriority_MiniGameMgr                               =  78 - 0x3ff,
    cDrawPriority_MiniGameMgrRDash                          =  79 - 0x3ff,
    cDrawPriority_ShuffleBlockMgr                           =  80 - 0x3ff,
    cDrawPriority_SlotMgr                                   =  81 - 0x3ff,
    cDrawPriority_CoinmakiMgr                               =  82 - 0x3ff,
    cDrawPriority_1C6                                       =  83 - 0x3ff,
    cDrawPriority_WakiSearchMagKiller                       =  84 - 0x3ff,
    cDrawPriority_32E                                       =  85 - 0x3ff,
    cDrawPriority_01D                                       =  86 - 0x3ff,
    cDrawPriority_01E                                       =  87 - 0x3ff,
    cDrawPriority_01F                                       =  88 - 0x3ff,
    cDrawPriority_KoopaFireWaki                             =  89 - 0x3ff,
    cDrawPriority_31A                                       =  90 - 0x3ff,
    cDrawPriority_020                                       =  91 - 0x3ff,
    cDrawPriority_013                                       =  92 - 0x3ff,
    cDrawPriority_31B                                       =  93 - 0x3ff,
    cDrawPriority_31C                                       =  94 - 0x3ff,
    cDrawPriority_ShootingStar                              =  95 - 0x3ff,
    cDrawPriority_302                                       =  96 - 0x3ff,
    cDrawPriority_227                                       =  97 - 0x3ff,
    cDrawPriority_228                                       =  98 - 0x3ff,
    cDrawPriority_343                                       =  99 - 0x3ff,
    cDrawPriority_344                                       = 100 - 0x3ff,
    cDrawPriority_345                                       = 101 - 0x3ff,
    cDrawPriority_RoyLiftWaki                               = 102 - 0x3ff,
    cDrawPriority_2A0                                       = 103 - 0x3ff,
    cDrawPriority_346                                       = 104 - 0x3ff,
    cDrawPriority_024                                       = 105 - 0x3ff,
    cDrawPriority_24D                                       = 106 - 0x3ff,
    cDrawPriority_230                                       = 107 - 0x3ff,
    cDrawPriority_296                                       = 108 - 0x3ff,
    cDrawPriority_297                                       = 109 - 0x3ff,
    cDrawPriority_351                                       = 110 - 0x3ff,
    cDrawPriority_11C                                       = 111 - 0x3ff,
    cDrawPriority_1B8                                       = 112 - 0x3ff,
    cDrawPriority_352                                       = 113 - 0x3ff,
    cDrawPriority_353                                       = 114 - 0x3ff,
    cDrawPriority_14C                                       = 115 - 0x3ff,
    cDrawPriority_347                                       = 116 - 0x3ff,
    cDrawPriority_1B7                                       = 117 - 0x3ff
};

const s16 Profile::cDrawPriority[cProfileID_Max] = {
    cDrawPriority_000,                                      // ProfileID::c000
    cDrawPriority_001,                                      // ProfileID::c001
    cDrawPriority_002,                                      // ProfileID::c002
    cDrawPriority_003,                                      // ProfileID::c003
    cDrawPriority_004,                                      // ProfileID::c004
    cDrawPriority_005,                                      // ProfileID::c005
    cDrawPriority_006,                                      // ProfileID::c006
    cDrawPriority_007,                                      // ProfileID::c007
    cDrawPriority_008,                                      // ProfileID::c008
    cDrawPriority_009,                                      // ProfileID::c009
    cDrawPriority_00A,                                      // ProfileID::c00A
    cDrawPriority_00B,                                      // ProfileID::c00B
    cDrawPriority_00C,                                      // ProfileID::c00C
    cDrawPriority_00D,                                      // ProfileID::c00D
    cDrawPriority_00E,                                      // ProfileID::c00E
    cDrawPriority_00F,                                      // ProfileID::c00F
    cDrawPriority_010,                                      // ProfileID::c010
    cDrawPriority_011,                                      // ProfileID::c011
    cDrawPriority_012,                                      // ProfileID::c012
    cDrawPriority_013,                                      // ProfileID::c013
    cDrawPriority_014,                                      // ProfileID::c014
    cDrawPriority_015,                                      // ProfileID::c015
    cDrawPriority_016,                                      // ProfileID::c016
    cDrawPriority_017,                                      // ProfileID::c017
    cDrawPriority_MiniGameMgr,                              // ProfileID::cMiniGameMgr
    cDrawPriority_MiniGameMgrRDash,                         // ProfileID::cMiniGameMgrRDash
    cDrawPriority_ShuffleBlockMgr,                          // ProfileID::cShuffleBlockMgr
    cDrawPriority_SlotMgr,                                  // ProfileID::cSlotMgr
    cDrawPriority_CoinmakiMgr,                              // ProfileID::cCoinmakiMgr
    cDrawPriority_01D,                                      // ProfileID::c01D
    cDrawPriority_01E,                                      // ProfileID::c01E
    cDrawPriority_01F,                                      // ProfileID::c01F
    cDrawPriority_020,                                      // ProfileID::c020
    cDrawPriority_ShootingStar,                             // ProfileID::cShootingStar
    cDrawPriority_StaffRollMgr,                             // ProfileID::cStaffRollMgr
    cDrawPriority_StaffRollMgrRDash,                        // ProfileID::cStaffRollMgrRDash
    cDrawPriority_024,                                      // ProfileID::c024
    cDrawPriority_025,                                      // ProfileID::c025
    cDrawPriority_026,                                      // ProfileID::c026
    cDrawPriority_027,                                      // ProfileID::c027
    cDrawPriority_028,                                      // ProfileID::c028
    cDrawPriority_029,                                      // ProfileID::c029
    cDrawPriority_02A,                                      // ProfileID::c02A
    cDrawPriority_02B,                                      // ProfileID::c02B
    cDrawPriority_02C,                                      // ProfileID::c02C
    cDrawPriority_02D,                                      // ProfileID::c02D
    cDrawPriority_02E,                                      // ProfileID::c02E
    cDrawPriority_02F,                                      // ProfileID::c02F
    cDrawPriority_030,                                      // ProfileID::c030
    cDrawPriority_031,                                      // ProfileID::c031
    cDrawPriority_032,                                      // ProfileID::c032
    cDrawPriority_033,                                      // ProfileID::c033
    cDrawPriority_ElasticKinokoParent,                      // ProfileID::cElasticKinokoParent
    cDrawPriority_FloorGyration,                            // ProfileID::cFloorGyration
    cDrawPriority_036,                                      // ProfileID::c036
    cDrawPriority_037,                                      // ProfileID::c037
    cDrawPriority_038,                                      // ProfileID::c038
    cDrawPriority_039,                                      // ProfileID::c039
    cDrawPriority_03A,                                      // ProfileID::c03A
    cDrawPriority_03B,                                      // ProfileID::c03B
    cDrawPriority_PairObjChild,                             // ProfileID::cPairObjChild
    cDrawPriority_03D,                                      // ProfileID::c03D
    cDrawPriority_03E,                                      // ProfileID::c03E
    cDrawPriority_03F,                                      // ProfileID::c03F
    cDrawPriority_040,                                      // ProfileID::c040
    cDrawPriority_041,                                      // ProfileID::c041
    cDrawPriority_042,                                      // ProfileID::c042
    cDrawPriority_043,                                      // ProfileID::c043
    cDrawPriority_044,                                      // ProfileID::c044
    cDrawPriority_045,                                      // ProfileID::c045
    cDrawPriority_046,                                      // ProfileID::c046
    cDrawPriority_047,                                      // ProfileID::c047
    cDrawPriority_048,                                      // ProfileID::c048
    cDrawPriority_049,                                      // ProfileID::c049
    cDrawPriority_04A,                                      // ProfileID::c04A
    cDrawPriority_04B,                                      // ProfileID::c04B
    cDrawPriority_04C,                                      // ProfileID::c04C
    cDrawPriority_KinokoLift,                               // ProfileID::cKinokoLift
    cDrawPriority_KinokoLiftColor,                          // ProfileID::cKinokoLiftColor
    cDrawPriority_04F,                                      // ProfileID::c04F
    cDrawPriority_050,                                      // ProfileID::c050
    cDrawPriority_051,                                      // ProfileID::c051
    cDrawPriority_052,                                      // ProfileID::c052
    cDrawPriority_053,                                      // ProfileID::c053
    cDrawPriority_054,                                      // ProfileID::c054
    cDrawPriority_055,                                      // ProfileID::c055
    cDrawPriority_056,                                      // ProfileID::c056
    cDrawPriority_057,                                      // ProfileID::c057
    cDrawPriority_058,                                      // ProfileID::c058
    cDrawPriority_059,                                      // ProfileID::c059
    cDrawPriority_05A,                                      // ProfileID::c05A
    cDrawPriority_05B,                                      // ProfileID::c05B
    cDrawPriority_05C,                                      // ProfileID::c05C
    cDrawPriority_05D,                                      // ProfileID::c05D
    cDrawPriority_05E,                                      // ProfileID::c05E
    cDrawPriority_05F,                                      // ProfileID::c05F
    cDrawPriority_060,                                      // ProfileID::c060
    cDrawPriority_061,                                      // ProfileID::c061
    cDrawPriority_062,                                      // ProfileID::c062
    cDrawPriority_063,                                      // ProfileID::c063
    cDrawPriority_064,                                      // ProfileID::c064
    cDrawPriority_KillerHoudai,                             // ProfileID::cKillerHoudai
    cDrawPriority_StretchKillerHoudai,                      // ProfileID::cStretchKillerHoudai
    cDrawPriority_MagnumKillerHoudai,                       // ProfileID::cMagnumKillerHoudai
    cDrawPriority_MagnumKillerHoudaiDown,                   // ProfileID::cMagnumKillerHoudaiDown
    cDrawPriority_SearchKillerHoudai,                       // ProfileID::cSearchKillerHoudai
    cDrawPriority_SearchMagnumKillerHoudai,                 // ProfileID::cSearchMagnumKillerHoudai
    cDrawPriority_SearchMagnumKillerHoudaiDown,             // ProfileID::cSearchMagnumKillerHoudaiDown
    cDrawPriority_MagnumKillerHoudaiRDash,                  // ProfileID::cMagnumKillerHoudaiRDash
    cDrawPriority_MagnumKillerHoudaiDownRDash,              // ProfileID::cMagnumKillerHoudaiDownRDash
    cDrawPriority_SearchMagnumKillerHoudaiRDash,            // ProfileID::cSearchMagnumKillerHoudaiRDash
    cDrawPriority_SearchMagnumKillerHoudaiDownRDash,        // ProfileID::cSearchMagnumKillerHoudaiDownRDash
    cDrawPriority_070,                                      // ProfileID::c070
    cDrawPriority_071,                                      // ProfileID::c071
    cDrawPriority_072,                                      // ProfileID::c072
    cDrawPriority_073,                                      // ProfileID::c073
    cDrawPriority_074,                                      // ProfileID::c074
    cDrawPriority_075,                                      // ProfileID::c075
    cDrawPriority_076,                                      // ProfileID::c076
    cDrawPriority_077,                                      // ProfileID::c077
    cDrawPriority_078,                                      // ProfileID::c078
    cDrawPriority_079,                                      // ProfileID::c079
    cDrawPriority_07A,                                      // ProfileID::c07A
    cDrawPriority_07B,                                      // ProfileID::c07B
    cDrawPriority_07C,                                      // ProfileID::c07C
    cDrawPriority_07D,                                      // ProfileID::c07D
    cDrawPriority_07E,                                      // ProfileID::c07E
    cDrawPriority_07F,                                      // ProfileID::c07F
    cDrawPriority_YoganIntermittent,                        // ProfileID::cYoganIntermittent
    cDrawPriority_081,                                      // ProfileID::c081
    cDrawPriority_082,                                      // ProfileID::c082
    cDrawPriority_083,                                      // ProfileID::c083
    cDrawPriority_084,                                      // ProfileID::c084
    cDrawPriority_085,                                      // ProfileID::c085
    cDrawPriority_086,                                      // ProfileID::c086
    cDrawPriority_087,                                      // ProfileID::c087
    cDrawPriority_088,                                      // ProfileID::c088
    cDrawPriority_089,                                      // ProfileID::c089
    cDrawPriority_08A,                                      // ProfileID::c08A
    cDrawPriority_08B,                                      // ProfileID::c08B
    cDrawPriority_08C,                                      // ProfileID::c08C
    cDrawPriority_08D,                                      // ProfileID::c08D
    cDrawPriority_08E,                                      // ProfileID::c08E
    cDrawPriority_08F,                                      // ProfileID::c08F
    cDrawPriority_090,                                      // ProfileID::c090
    cDrawPriority_091,                                      // ProfileID::c091
    cDrawPriority_092,                                      // ProfileID::c092
    cDrawPriority_093,                                      // ProfileID::c093
    cDrawPriority_094,                                      // ProfileID::c094
    cDrawPriority_095,                                      // ProfileID::c095
    cDrawPriority_096,                                      // ProfileID::c096
    cDrawPriority_097,                                      // ProfileID::c097
    cDrawPriority_098,                                      // ProfileID::c098
    cDrawPriority_099,                                      // ProfileID::c099
    cDrawPriority_09A,                                      // ProfileID::c09A
    cDrawPriority_09B,                                      // ProfileID::c09B
    cDrawPriority_09C,                                      // ProfileID::c09C
    cDrawPriority_09D,                                      // ProfileID::c09D
    cDrawPriority_09E,                                      // ProfileID::c09E
    cDrawPriority_09F,                                      // ProfileID::c09F
    cDrawPriority_0A0,                                      // ProfileID::c0A0
    cDrawPriority_0A1,                                      // ProfileID::c0A1
    cDrawPriority_0A2,                                      // ProfileID::c0A2
    cDrawPriority_0A3,                                      // ProfileID::c0A3
    cDrawPriority_0A4,                                      // ProfileID::c0A4
    cDrawPriority_0A5,                                      // ProfileID::c0A5
    cDrawPriority_0A6,                                      // ProfileID::c0A6
    cDrawPriority_0A7,                                      // ProfileID::c0A7
    cDrawPriority_0A8,                                      // ProfileID::c0A8
    cDrawPriority_0A9,                                      // ProfileID::c0A9
    cDrawPriority_0AA,                                      // ProfileID::c0AA
    cDrawPriority_0AB,                                      // ProfileID::c0AB
    cDrawPriority_0AC,                                      // ProfileID::c0AC
    cDrawPriority_0AD,                                      // ProfileID::c0AD
    cDrawPriority_0AE,                                      // ProfileID::c0AE
    cDrawPriority_0AF,                                      // ProfileID::c0AF
    cDrawPriority_0B0,                                      // ProfileID::c0B0
    cDrawPriority_0B1,                                      // ProfileID::c0B1
    cDrawPriority_0B2,                                      // ProfileID::c0B2
    cDrawPriority_0B3,                                      // ProfileID::c0B3
    cDrawPriority_0B4,                                      // ProfileID::c0B4
    cDrawPriority_0B5,                                      // ProfileID::c0B5
    cDrawPriority_0B6,                                      // ProfileID::c0B6
    cDrawPriority_0B7,                                      // ProfileID::c0B7
    cDrawPriority_0B8,                                      // ProfileID::c0B8
    cDrawPriority_0B9,                                      // ProfileID::c0B9
    cDrawPriority_0BA,                                      // ProfileID::c0BA
    cDrawPriority_0BB,                                      // ProfileID::c0BB
    cDrawPriority_0BC,                                      // ProfileID::c0BC
    cDrawPriority_0BD,                                      // ProfileID::c0BD
    cDrawPriority_0BE,                                      // ProfileID::c0BE
    cDrawPriority_0BF,                                      // ProfileID::c0BF
    cDrawPriority_0C0,                                      // ProfileID::c0C0
    cDrawPriority_0C1,                                      // ProfileID::c0C1
    cDrawPriority_SnakeBlock,                               // ProfileID::cSnakeBlock
    cDrawPriority_0C3,                                      // ProfileID::c0C3
    cDrawPriority_0C4,                                      // ProfileID::c0C4
    cDrawPriority_0C5,                                      // ProfileID::c0C5
    cDrawPriority_0C6,                                      // ProfileID::c0C6
    cDrawPriority_0C7,                                      // ProfileID::c0C7
    cDrawPriority_0C8,                                      // ProfileID::c0C8
    cDrawPriority_0C9,                                      // ProfileID::c0C9
    cDrawPriority_0CA,                                      // ProfileID::c0CA
    cDrawPriority_0CB,                                      // ProfileID::c0CB
    cDrawPriority_0CC,                                      // ProfileID::c0CC
    cDrawPriority_0CD,                                      // ProfileID::c0CD
    cDrawPriority_0CE,                                      // ProfileID::c0CE
    cDrawPriority_0CF,                                      // ProfileID::c0CF
    cDrawPriority_0D0,                                      // ProfileID::c0D0
    cDrawPriority_0D1,                                      // ProfileID::c0D1
    cDrawPriority_FloorHoleDokan,                           // ProfileID::cFloorHoleDokan
    cDrawPriority_0D3,                                      // ProfileID::c0D3
    cDrawPriority_0D4,                                      // ProfileID::c0D4
    cDrawPriority_0D5,                                      // ProfileID::c0D5
    cDrawPriority_0D6,                                      // ProfileID::c0D6
    cDrawPriority_0D7,                                      // ProfileID::c0D7
    cDrawPriority_0D8,                                      // ProfileID::c0D8
    cDrawPriority_0D9,                                      // ProfileID::c0D9
    cDrawPriority_0DA,                                      // ProfileID::c0DA
    cDrawPriority_0DB,                                      // ProfileID::c0DB
    cDrawPriority_0DC,                                      // ProfileID::c0DC
    cDrawPriority_0DD,                                      // ProfileID::c0DD
    cDrawPriority_0DE,                                      // ProfileID::c0DE
    cDrawPriority_0DF,                                      // ProfileID::c0DF
    cDrawPriority_Burner,                                   // ProfileID::cBurner
    cDrawPriority_0E1,                                      // ProfileID::c0E1
    cDrawPriority_0E2,                                      // ProfileID::c0E2
    cDrawPriority_0E3,                                      // ProfileID::c0E3
    cDrawPriority_0E4,                                      // ProfileID::c0E4
    cDrawPriority_0E5,                                      // ProfileID::c0E5
    cDrawPriority_0E6,                                      // ProfileID::c0E6
    cDrawPriority_0E7,                                      // ProfileID::c0E7
    cDrawPriority_0E8,                                      // ProfileID::c0E8
    cDrawPriority_0E9,                                      // ProfileID::c0E9
    cDrawPriority_0EA,                                      // ProfileID::c0EA
    cDrawPriority_0EB,                                      // ProfileID::c0EB
    cDrawPriority_0EC,                                      // ProfileID::c0EC
    cDrawPriority_0ED,                                      // ProfileID::c0ED
    cDrawPriority_TarzanIvy,                                // ProfileID::cTarzanIvy
    cDrawPriority_0EF,                                      // ProfileID::c0EF
    cDrawPriority_0F0,                                      // ProfileID::c0F0
    cDrawPriority_0F1,                                      // ProfileID::c0F1
    cDrawPriority_0F2,                                      // ProfileID::c0F2
    cDrawPriority_0F3,                                      // ProfileID::c0F3
    cDrawPriority_0F4,                                      // ProfileID::c0F4
    cDrawPriority_0F5,                                      // ProfileID::c0F5
    cDrawPriority_0F6,                                      // ProfileID::c0F6
    cDrawPriority_0F7,                                      // ProfileID::c0F7
    cDrawPriority_0F8,                                      // ProfileID::c0F8
    cDrawPriority_0F9,                                      // ProfileID::c0F9
    cDrawPriority_0FA,                                      // ProfileID::c0FA
    cDrawPriority_0FB,                                      // ProfileID::c0FB
    cDrawPriority_0FC,                                      // ProfileID::c0FC
    cDrawPriority_0FD,                                      // ProfileID::c0FD
    cDrawPriority_0FE,                                      // ProfileID::c0FE
    cDrawPriority_0FF,                                      // ProfileID::c0FF
    cDrawPriority_100,                                      // ProfileID::c100
    cDrawPriority_101,                                      // ProfileID::c101
    cDrawPriority_102,                                      // ProfileID::c102
    cDrawPriority_103,                                      // ProfileID::c103
    cDrawPriority_104,                                      // ProfileID::c104
    cDrawPriority_ShuffleBlock,                             // ProfileID::cShuffleBlock
    cDrawPriority_KokoopaShipWarpCannon,                    // ProfileID::cKokoopaShipWarpCannon
    cDrawPriority_107,                                      // ProfileID::c107
    cDrawPriority_108,                                      // ProfileID::c108
    cDrawPriority_KoopaShutter,                             // ProfileID::cKoopaShutter
    cDrawPriority_10A,                                      // ProfileID::c10A
    cDrawPriority_10B,                                      // ProfileID::c10B
    cDrawPriority_10C,                                      // ProfileID::c10C
    cDrawPriority_PeachFinalCastleKoopaJrLift,              // ProfileID::cPeachFinalCastleKoopaJrLift
    cDrawPriority_PeachFinalCastleKoopaJrLiftHmove,         // ProfileID::cPeachFinalCastleKoopaJrLiftHmove
    cDrawPriority_PeachFinalCastleKoopaJrLiftPairObj,       // ProfileID::cPeachFinalCastleKoopaJrLiftPairObj
    cDrawPriority_RoyLiftWakiStep,                          // ProfileID::cRoyLiftWakiStep
    cDrawPriority_WendyFloor,                               // ProfileID::cWendyFloor
    cDrawPriority_IggyRoom,                                 // ProfileID::cIggyRoom
    cDrawPriority_113,                                      // ProfileID::c113
    cDrawPriority_114,                                      // ProfileID::c114
    cDrawPriority_115,                                      // ProfileID::c115
    cDrawPriority_116,                                      // ProfileID::c116
    cDrawPriority_117,                                      // ProfileID::c117
    cDrawPriority_118,                                      // ProfileID::c118
    cDrawPriority_119,                                      // ProfileID::c119
    cDrawPriority_11A,                                      // ProfileID::c11A
    cDrawPriority_11B,                                      // ProfileID::c11B
    cDrawPriority_11C,                                      // ProfileID::c11C
    cDrawPriority_11D,                                      // ProfileID::c11D
    cDrawPriority_11E,                                      // ProfileID::c11E
    cDrawPriority_Block,                                    // ProfileID::cBlock
    cDrawPriority_120,                                      // ProfileID::c120
    cDrawPriority_121,                                      // ProfileID::c121
    cDrawPriority_122,                                      // ProfileID::c122
    cDrawPriority_ActorBlockRenga,                          // ProfileID::cActorBlockRenga
    cDrawPriority_124,                                      // ProfileID::c124
    cDrawPriority_125,                                      // ProfileID::c125
    cDrawPriority_126,                                      // ProfileID::c126
    cDrawPriority_127,                                      // ProfileID::c127
    cDrawPriority_128,                                      // ProfileID::c128
    cDrawPriority_129,                                      // ProfileID::c129
    cDrawPriority_12A,                                      // ProfileID::c12A
    cDrawPriority_12B,                                      // ProfileID::c12B
    cDrawPriority_12C,                                      // ProfileID::c12C
    cDrawPriority_12D,                                      // ProfileID::c12D
    cDrawPriority_12E,                                      // ProfileID::c12E
    cDrawPriority_12F,                                      // ProfileID::c12F
    cDrawPriority_130,                                      // ProfileID::c130
    cDrawPriority_131,                                      // ProfileID::c131
    cDrawPriority_132,                                      // ProfileID::c132
    cDrawPriority_133,                                      // ProfileID::c133
    cDrawPriority_134,                                      // ProfileID::c134
    cDrawPriority_135,                                      // ProfileID::c135
    cDrawPriority_136,                                      // ProfileID::c136
    cDrawPriority_137,                                      // ProfileID::c137
    cDrawPriority_138,                                      // ProfileID::c138
    cDrawPriority_139,                                      // ProfileID::c139
    cDrawPriority_13A,                                      // ProfileID::c13A
    cDrawPriority_13B,                                      // ProfileID::c13B
    cDrawPriority_13C,                                      // ProfileID::c13C
    cDrawPriority_13D,                                      // ProfileID::c13D
    cDrawPriority_13E,                                      // ProfileID::c13E
    cDrawPriority_13F,                                      // ProfileID::c13F
    cDrawPriority_140,                                      // ProfileID::c140
    cDrawPriority_141,                                      // ProfileID::c141
    cDrawPriority_142,                                      // ProfileID::c142
    cDrawPriority_143,                                      // ProfileID::c143
    cDrawPriority_144,                                      // ProfileID::c144
    cDrawPriority_145,                                      // ProfileID::c145
    cDrawPriority_146,                                      // ProfileID::c146
    cDrawPriority_147,                                      // ProfileID::c147
    cDrawPriority_148,                                      // ProfileID::c148
    cDrawPriority_149,                                      // ProfileID::c149
    cDrawPriority_14A,                                      // ProfileID::c14A
    cDrawPriority_14B,                                      // ProfileID::c14B
    cDrawPriority_14C,                                      // ProfileID::c14C
    cDrawPriority_14D,                                      // ProfileID::c14D
    cDrawPriority_14E,                                      // ProfileID::c14E
    cDrawPriority_14F,                                      // ProfileID::c14F
    cDrawPriority_150,                                      // ProfileID::c150
    cDrawPriority_151,                                      // ProfileID::c151
    cDrawPriority_152,                                      // ProfileID::c152
    cDrawPriority_153,                                      // ProfileID::c153
    cDrawPriority_154,                                      // ProfileID::c154
    cDrawPriority_155,                                      // ProfileID::c155
    cDrawPriority_156,                                      // ProfileID::c156
    cDrawPriority_157,                                      // ProfileID::c157
    cDrawPriority_SwitchHatenaButton,                       // ProfileID::cSwitchHatenaButton
    cDrawPriority_SwitchPbutton,                            // ProfileID::cSwitchPbutton
    cDrawPriority_SwitchPbuttonRDash,                       // ProfileID::cSwitchPbuttonRDash
    cDrawPriority_SwitchPbuttonNoWallKick,                  // ProfileID::cSwitchPbuttonNoWallKick
    cDrawPriority_15C,                                      // ProfileID::c15C
    cDrawPriority_15D,                                      // ProfileID::c15D
    cDrawPriority_15E,                                      // ProfileID::c15E
    cDrawPriority_LemmyBall,                                // ProfileID::cLemmyBall
    cDrawPriority_LemmyBomb,                                // ProfileID::cLemmyBomb
    cDrawPriority_161,                                      // ProfileID::c161
    cDrawPriority_162,                                      // ProfileID::c162
    cDrawPriority_163,                                      // ProfileID::c163
    cDrawPriority_164,                                      // ProfileID::c164
    cDrawPriority_165,                                      // ProfileID::c165
    cDrawPriority_166,                                      // ProfileID::c166
    cDrawPriority_167,                                      // ProfileID::c167
    cDrawPriority_168,                                      // ProfileID::c168
    cDrawPriority_169,                                      // ProfileID::c169
    cDrawPriority_16A,                                      // ProfileID::c16A
    cDrawPriority_16B,                                      // ProfileID::c16B
    cDrawPriority_16C,                                      // ProfileID::c16C
    cDrawPriority_16D,                                      // ProfileID::c16D
    cDrawPriority_16E,                                      // ProfileID::c16E
    cDrawPriority_16F,                                      // ProfileID::c16F
    cDrawPriority_KameckIce,                                // ProfileID::cKameckIce
    cDrawPriority_WendyIcicle,                              // ProfileID::cWendyIcicle
    cDrawPriority_PeachFinalCastleKoopaJrClown,             // ProfileID::cPeachFinalCastleKoopaJrClown
    cDrawPriority_BoxingKoopaJrClown,                       // ProfileID::cBoxingKoopaJrClown
    cDrawPriority_174,                                      // ProfileID::c174
    cDrawPriority_FinalKoopaJrClown,                        // ProfileID::cFinalKoopaJrClown
    cDrawPriority_FinalKoopa,                               // ProfileID::cFinalKoopa
    cDrawPriority_FireBar,                                  // ProfileID::cFireBar
    cDrawPriority_FireBarSync,                              // ProfileID::cFireBarSync
    cDrawPriority_179,                                      // ProfileID::c179
    cDrawPriority_17A,                                      // ProfileID::c17A
    cDrawPriority_17B,                                      // ProfileID::c17B
    cDrawPriority_17C,                                      // ProfileID::c17C
    cDrawPriority_17D,                                      // ProfileID::c17D
    cDrawPriority_17E,                                      // ProfileID::c17E
    cDrawPriority_17F,                                      // ProfileID::c17F
    cDrawPriority_180,                                      // ProfileID::c180
    cDrawPriority_181,                                      // ProfileID::c181
    cDrawPriority_182,                                      // ProfileID::c182
    cDrawPriority_183,                                      // ProfileID::c183
    cDrawPriority_184,                                      // ProfileID::c184
    cDrawPriority_185,                                      // ProfileID::c185
    cDrawPriority_186,                                      // ProfileID::c186
    cDrawPriority_187,                                      // ProfileID::c187
    cDrawPriority_188,                                      // ProfileID::c188
    cDrawPriority_189,                                      // ProfileID::c189
    cDrawPriority_18A,                                      // ProfileID::c18A
    cDrawPriority_ActorCoin,                                // ProfileID::cActorCoin
    cDrawPriority_18C,                                      // ProfileID::c18C
    cDrawPriority_18D,                                      // ProfileID::c18D
    cDrawPriority_18E,                                      // ProfileID::c18E
    cDrawPriority_18F,                                      // ProfileID::c18F
    cDrawPriority_190,                                      // ProfileID::c190
    cDrawPriority_191,                                      // ProfileID::c191
    cDrawPriority_192,                                      // ProfileID::c192
    cDrawPriority_193,                                      // ProfileID::c193
    cDrawPriority_194,                                      // ProfileID::c194
    cDrawPriority_195,                                      // ProfileID::c195
    cDrawPriority_196,                                      // ProfileID::c196
    cDrawPriority_197,                                      // ProfileID::c197
    cDrawPriority_198,                                      // ProfileID::c198
    cDrawPriority_199,                                      // ProfileID::c199
    cDrawPriority_19A,                                      // ProfileID::c19A
    cDrawPriority_19B,                                      // ProfileID::c19B
    cDrawPriority_19C,                                      // ProfileID::c19C
    cDrawPriority_19D,                                      // ProfileID::c19D
    cDrawPriority_19E,                                      // ProfileID::c19E
    cDrawPriority_19F,                                      // ProfileID::c19F
    cDrawPriority_1A0,                                      // ProfileID::c1A0
    cDrawPriority_1A1,                                      // ProfileID::c1A1
    cDrawPriority_1A2,                                      // ProfileID::c1A2
    cDrawPriority_1A3,                                      // ProfileID::c1A3
    cDrawPriority_1A4,                                      // ProfileID::c1A4
    cDrawPriority_1A5,                                      // ProfileID::c1A5
    cDrawPriority_1A6,                                      // ProfileID::c1A6
    cDrawPriority_1A7,                                      // ProfileID::c1A7
    cDrawPriority_1A8,                                      // ProfileID::c1A8
    cDrawPriority_BlueCoin,                                 // ProfileID::cBlueCoin
    cDrawPriority_1AA,                                      // ProfileID::c1AA
    cDrawPriority_1AB,                                      // ProfileID::c1AB
    cDrawPriority_1AC,                                      // ProfileID::c1AC
    cDrawPriority_1AD,                                      // ProfileID::c1AD
    cDrawPriority_1AE,                                      // ProfileID::c1AE
    cDrawPriority_1AF,                                      // ProfileID::c1AF
    cDrawPriority_1B0,                                      // ProfileID::c1B0
    cDrawPriority_1B1,                                      // ProfileID::c1B1
    cDrawPriority_1B2,                                      // ProfileID::c1B2
    cDrawPriority_1B3,                                      // ProfileID::c1B3
    cDrawPriority_1B4,                                      // ProfileID::c1B4
    cDrawPriority_1B5,                                      // ProfileID::c1B5
    cDrawPriority_CoinmakiCoin,                             // ProfileID::cCoinmakiCoin
    cDrawPriority_1B7,                                      // ProfileID::c1B7
    cDrawPriority_1B8,                                      // ProfileID::c1B8
    cDrawPriority_1B9,                                      // ProfileID::c1B9
    cDrawPriority_Yoshi,                                    // ProfileID::cYoshi
    cDrawPriority_TottenPlayer,                             // ProfileID::cTottenPlayer
    cDrawPriority_PlayerObject,                             // ProfileID::cPlayerObject
    cDrawPriority_1BD,                                      // ProfileID::c1BD
    cDrawPriority_1BE,                                      // ProfileID::c1BE
    cDrawPriority_1BF,                                      // ProfileID::c1BF
    cDrawPriority_1C0,                                      // ProfileID::c1C0
    cDrawPriority_1C1,                                      // ProfileID::c1C1
    cDrawPriority_1C2,                                      // ProfileID::c1C2
    cDrawPriority_1C3,                                      // ProfileID::c1C3
    cDrawPriority_1C4,                                      // ProfileID::c1C4
    cDrawPriority_SlotYoshiChibi,                           // ProfileID::cSlotYoshiChibi
    cDrawPriority_1C6,                                      // ProfileID::c1C6
    cDrawPriority_1C7,                                      // ProfileID::c1C7
    cDrawPriority_1C8,                                      // ProfileID::c1C8
    cDrawPriority_1C9,                                      // ProfileID::c1C9
    cDrawPriority_1CA,                                      // ProfileID::c1CA
    cDrawPriority_1CB,                                      // ProfileID::c1CB
    cDrawPriority_1CC,                                      // ProfileID::c1CC
    cDrawPriority_1CD,                                      // ProfileID::c1CD
    cDrawPriority_1CE,                                      // ProfileID::c1CE
    cDrawPriority_QuestPrizeItem,                           // ProfileID::cQuestPrizeItem
    cDrawPriority_1D0,                                      // ProfileID::c1D0
    cDrawPriority_1D1,                                      // ProfileID::c1D1
    cDrawPriority_1D2,                                      // ProfileID::c1D2
    cDrawPriority_1D3,                                      // ProfileID::c1D3
    cDrawPriority_1D4,                                      // ProfileID::c1D4
    cDrawPriority_1D5,                                      // ProfileID::c1D5
    cDrawPriority_1D6,                                      // ProfileID::c1D6
    cDrawPriority_1D7,                                      // ProfileID::c1D7
    cDrawPriority_1D8,                                      // ProfileID::c1D8
    cDrawPriority_1D9,                                      // ProfileID::c1D9
    cDrawPriority_IceBall,                                  // ProfileID::cIceBall
    cDrawPriority_IceBallPakkun,                            // ProfileID::cIceBallPakkun
    cDrawPriority_FireBallPlayer,                           // ProfileID::cFireBallPlayer
    cDrawPriority_FireBallPakkun,                           // ProfileID::cFireBallPakkun
    cDrawPriority_YoshiFire,                                // ProfileID::cYoshiFire
    cDrawPriority_1DF,                                      // ProfileID::c1DF
    cDrawPriority_1E0,                                      // ProfileID::c1E0
    cDrawPriority_1E1,                                      // ProfileID::c1E1
    cDrawPriority_1E2,                                      // ProfileID::c1E2
    cDrawPriority_1E3,                                      // ProfileID::c1E3
    cDrawPriority_1E4,                                      // ProfileID::c1E4
    cDrawPriority_1E5,                                      // ProfileID::c1E5
    cDrawPriority_1E6,                                      // ProfileID::c1E6
    cDrawPriority_1E7,                                      // ProfileID::c1E7
    cDrawPriority_1E8,                                      // ProfileID::c1E8
    cDrawPriority_1E9,                                      // ProfileID::c1E9
    cDrawPriority_1EA,                                      // ProfileID::c1EA
    cDrawPriority_1EB,                                      // ProfileID::c1EB
    cDrawPriority_1EC,                                      // ProfileID::c1EC
    cDrawPriority_1ED,                                      // ProfileID::c1ED
    cDrawPriority_1EE,                                      // ProfileID::c1EE
    cDrawPriority_1EF,                                      // ProfileID::c1EF
    cDrawPriority_1F0,                                      // ProfileID::c1F0
    cDrawPriority_1F1,                                      // ProfileID::c1F1
    cDrawPriority_1F2,                                      // ProfileID::c1F2
    cDrawPriority_1F3,                                      // ProfileID::c1F3
    cDrawPriority_1F4,                                      // ProfileID::c1F4
    cDrawPriority_1F5,                                      // ProfileID::c1F5
    cDrawPriority_1F6,                                      // ProfileID::c1F6
    cDrawPriority_1F7,                                      // ProfileID::c1F7
    cDrawPriority_1F8,                                      // ProfileID::c1F8
    cDrawPriority_1F9,                                      // ProfileID::c1F9
    cDrawPriority_1FA,                                      // ProfileID::c1FA
    cDrawPriority_1FB,                                      // ProfileID::c1FB
    cDrawPriority_1FC,                                      // ProfileID::c1FC
    cDrawPriority_1FD,                                      // ProfileID::c1FD
    cDrawPriority_1FE,                                      // ProfileID::c1FE
    cDrawPriority_1FF,                                      // ProfileID::c1FF
    cDrawPriority_Nokonoko,                                 // ProfileID::cNokonoko
    cDrawPriority_201,                                      // ProfileID::c201
    cDrawPriority_202,                                      // ProfileID::c202
    cDrawPriority_203,                                      // ProfileID::c203
    cDrawPriority_204,                                      // ProfileID::c204
    cDrawPriority_205,                                      // ProfileID::c205
    cDrawPriority_206,                                      // ProfileID::c206
    cDrawPriority_207,                                      // ProfileID::c207
    cDrawPriority_208,                                      // ProfileID::c208
    cDrawPriority_209,                                      // ProfileID::c209
    cDrawPriority_20A,                                      // ProfileID::c20A
    cDrawPriority_20B,                                      // ProfileID::c20B
    cDrawPriority_MechaKoopa,                               // ProfileID::cMechaKoopa
    cDrawPriority_20D,                                      // ProfileID::c20D
    cDrawPriority_20E,                                      // ProfileID::c20E
    cDrawPriority_20F,                                      // ProfileID::c20F
    cDrawPriority_210,                                      // ProfileID::c210
    cDrawPriority_211,                                      // ProfileID::c211
    cDrawPriority_212,                                      // ProfileID::c212
    cDrawPriority_213,                                      // ProfileID::c213
    cDrawPriority_214,                                      // ProfileID::c214
    cDrawPriority_215,                                      // ProfileID::c215
    cDrawPriority_216,                                      // ProfileID::c216
    cDrawPriority_217,                                      // ProfileID::c217
    cDrawPriority_218,                                      // ProfileID::c218
    cDrawPriority_219,                                      // ProfileID::c219
    cDrawPriority_21A,                                      // ProfileID::c21A
    cDrawPriority_21B,                                      // ProfileID::c21B
    cDrawPriority_21C,                                      // ProfileID::c21C
    cDrawPriority_21D,                                      // ProfileID::c21D
    cDrawPriority_21E,                                      // ProfileID::c21E
    cDrawPriority_21F,                                      // ProfileID::c21F
    cDrawPriority_220,                                      // ProfileID::c220
    cDrawPriority_221,                                      // ProfileID::c221
    cDrawPriority_222,                                      // ProfileID::c222
    cDrawPriority_223,                                      // ProfileID::c223
    cDrawPriority_224,                                      // ProfileID::c224
    cDrawPriority_225,                                      // ProfileID::c225
    cDrawPriority_226,                                      // ProfileID::c226
    cDrawPriority_227,                                      // ProfileID::c227
    cDrawPriority_228,                                      // ProfileID::c228
    cDrawPriority_229,                                      // ProfileID::c229
    cDrawPriority_22A,                                      // ProfileID::c22A
    cDrawPriority_22B,                                      // ProfileID::c22B
    cDrawPriority_22C,                                      // ProfileID::c22C
    cDrawPriority_22D,                                      // ProfileID::c22D
    cDrawPriority_FireBallKeronpa,                          // ProfileID::cFireBallKeronpa
    cDrawPriority_FireBallKeronpaRDash,                     // ProfileID::cFireBallKeronpaRDash
    cDrawPriority_230,                                      // ProfileID::c230
    cDrawPriority_FireSnake,                                // ProfileID::cFireSnake
    cDrawPriority_232,                                      // ProfileID::c232
    cDrawPriority_233,                                      // ProfileID::c233
    cDrawPriority_234,                                      // ProfileID::c234
    cDrawPriority_235,                                      // ProfileID::c235
    cDrawPriority_236,                                      // ProfileID::c236
    cDrawPriority_237,                                      // ProfileID::c237
    cDrawPriority_238,                                      // ProfileID::c238
    cDrawPriority_239,                                      // ProfileID::c239
    cDrawPriority_23A,                                      // ProfileID::c23A
    cDrawPriority_23B,                                      // ProfileID::c23B
    cDrawPriority_23C,                                      // ProfileID::c23C
    cDrawPriority_23D,                                      // ProfileID::c23D
    cDrawPriority_Kazandan,                                 // ProfileID::cKazandan
    cDrawPriority_23F,                                      // ProfileID::c23F
    cDrawPriority_240,                                      // ProfileID::c240
    cDrawPriority_241,                                      // ProfileID::c241
    cDrawPriority_242,                                      // ProfileID::c242
    cDrawPriority_243,                                      // ProfileID::c243
    cDrawPriority_244,                                      // ProfileID::c244
    cDrawPriority_245,                                      // ProfileID::c245
    cDrawPriority_246,                                      // ProfileID::c246
    cDrawPriority_247,                                      // ProfileID::c247
    cDrawPriority_248,                                      // ProfileID::c248
    cDrawPriority_249,                                      // ProfileID::c249
    cDrawPriority_24A,                                      // ProfileID::c24A
    cDrawPriority_BgCenter,                                 // ProfileID::cBgCenter
    cDrawPriority_24C,                                      // ProfileID::c24C
    cDrawPriority_24D,                                      // ProfileID::c24D
    cDrawPriority_24E,                                      // ProfileID::c24E
    cDrawPriority_Kinoko,                                   // ProfileID::cKinoko
    cDrawPriority_FireFlower,                               // ProfileID::cFireFlower
    cDrawPriority_MameKinoko,                               // ProfileID::cMameKinoko
    cDrawPriority_IceFlower,                                // ProfileID::cIceFlower
    cDrawPriority_Propeller,                                // ProfileID::cPropeller
    cDrawPriority_Penguin,                                  // ProfileID::cPenguin
    cDrawPriority_OneUpKinoko,                              // ProfileID::cOneUpKinoko
    cDrawPriority_Musasabi,                                 // ProfileID::cMusasabi
    cDrawPriority_SuperMoon,                                // ProfileID::cSuperMoon
    cDrawPriority_TitleDemoItem,                            // ProfileID::cTitleDemoItem
    cDrawPriority_259,                                      // ProfileID::c259
    cDrawPriority_25A,                                      // ProfileID::c25A
    cDrawPriority_25B,                                      // ProfileID::c25B
    cDrawPriority_25C,                                      // ProfileID::c25C
    cDrawPriority_25D,                                      // ProfileID::c25D
    cDrawPriority_25E,                                      // ProfileID::c25E
    cDrawPriority_25F,                                      // ProfileID::c25F
    cDrawPriority_260,                                      // ProfileID::c260
    cDrawPriority_261,                                      // ProfileID::c261
    cDrawPriority_262,                                      // ProfileID::c262
    cDrawPriority_263,                                      // ProfileID::c263
    cDrawPriority_264,                                      // ProfileID::c264
    cDrawPriority_265,                                      // ProfileID::c265
    cDrawPriority_266,                                      // ProfileID::c266
    cDrawPriority_267,                                      // ProfileID::c267
    cDrawPriority_268,                                      // ProfileID::c268
    cDrawPriority_Spanner,                                  // ProfileID::cSpanner
    cDrawPriority_26A,                                      // ProfileID::c26A
    cDrawPriority_26B,                                      // ProfileID::c26B
    cDrawPriority_26C,                                      // ProfileID::c26C
    cDrawPriority_26D,                                      // ProfileID::c26D
    cDrawPriority_26E,                                      // ProfileID::c26E
    cDrawPriority_26F,                                      // ProfileID::c26F
    cDrawPriority_270,                                      // ProfileID::c270
    cDrawPriority_271,                                      // ProfileID::c271
    cDrawPriority_272,                                      // ProfileID::c272
    cDrawPriority_273,                                      // ProfileID::c273
    cDrawPriority_274,                                      // ProfileID::c274
    cDrawPriority_275,                                      // ProfileID::c275
    cDrawPriority_SearchKiller,                             // ProfileID::cSearchKiller
    cDrawPriority_277,                                      // ProfileID::c277
    cDrawPriority_278,                                      // ProfileID::c278
    cDrawPriority_279,                                      // ProfileID::c279
    cDrawPriority_WakiSearchMagKiller,                      // ProfileID::cWakiSearchMagKiller
    cDrawPriority_27B,                                      // ProfileID::c27B
    cDrawPriority_27C,                                      // ProfileID::c27C
    cDrawPriority_27D,                                      // ProfileID::c27D
    cDrawPriority_27E,                                      // ProfileID::c27E
    cDrawPriority_27F,                                      // ProfileID::c27F
    cDrawPriority_GabonRock,                                // ProfileID::cGabonRock
    cDrawPriority_281,                                      // ProfileID::c281
    cDrawPriority_282,                                      // ProfileID::c282
    cDrawPriority_RockGabonRock,                            // ProfileID::cRockGabonRock
    cDrawPriority_284,                                      // ProfileID::c284
    cDrawPriority_SeichanSnowBall,                          // ProfileID::cSeichanSnowBall
    cDrawPriority_286,                                      // ProfileID::c286
    cDrawPriority_287,                                      // ProfileID::c287
    cDrawPriority_288,                                      // ProfileID::c288
    cDrawPriority_289,                                      // ProfileID::c289
    cDrawPriority_Woochan,                                  // ProfileID::cWoochan
    cDrawPriority_28B,                                      // ProfileID::c28B
    cDrawPriority_28C,                                      // ProfileID::c28C
    cDrawPriority_28D,                                      // ProfileID::c28D
    cDrawPriority_Bubble,                                   // ProfileID::cBubble
    cDrawPriority_BubbleSync,                               // ProfileID::cBubbleSync
    cDrawPriority_BubbleRDash,                              // ProfileID::cBubbleRDash
    cDrawPriority_BubbleSyncRDash,                          // ProfileID::cBubbleSyncRDash
    cDrawPriority_292,                                      // ProfileID::c292
    cDrawPriority_293,                                      // ProfileID::c293
    cDrawPriority_294,                                      // ProfileID::c294
    cDrawPriority_295,                                      // ProfileID::c295
    cDrawPriority_296,                                      // ProfileID::c296
    cDrawPriority_297,                                      // ProfileID::c297
    cDrawPriority_298,                                      // ProfileID::c298
    cDrawPriority_299,                                      // ProfileID::c299
    cDrawPriority_29A,                                      // ProfileID::c29A
    cDrawPriority_29B,                                      // ProfileID::c29B
    cDrawPriority_29C,                                      // ProfileID::c29C
    cDrawPriority_29D,                                      // ProfileID::c29D
    cDrawPriority_29E,                                      // ProfileID::c29E
    cDrawPriority_29F,                                      // ProfileID::c29F
    cDrawPriority_2A0,                                      // ProfileID::c2A0
    cDrawPriority_2A1,                                      // ProfileID::c2A1
    cDrawPriority_2A2,                                      // ProfileID::c2A2
    cDrawPriority_2A3,                                      // ProfileID::c2A3
    cDrawPriority_2A4,                                      // ProfileID::c2A4
    cDrawPriority_2A5,                                      // ProfileID::c2A5
    cDrawPriority_Bun,                                      // ProfileID::cBun
    cDrawPriority_BunW2,                                    // ProfileID::cBunW2
    cDrawPriority_BunW3,                                    // ProfileID::cBunW3
    cDrawPriority_BunW4,                                    // ProfileID::cBunW4
    cDrawPriority_BunW5,                                    // ProfileID::cBunW5
    cDrawPriority_BunW6,                                    // ProfileID::cBunW6
    cDrawPriority_BunDemo,                                  // ProfileID::cBunDemo
    cDrawPriority_KokoopaDemo,                              // ProfileID::cKokoopaDemo
    cDrawPriority_KoopaJrDemo,                              // ProfileID::cKoopaJrDemo
    cDrawPriority_KameckDemo,                               // ProfileID::cKameckDemo
    cDrawPriority_BossKKDemo,                               // ProfileID::cBossKKDemo
    cDrawPriority_PeachFinalCastleKoopaJrDemo,              // ProfileID::cPeachFinalCastleKoopaJrDemo
    cDrawPriority_KoopaDemo,                                // ProfileID::cKoopaDemo
    cDrawPriority_FinalKoopaDemo,                           // ProfileID::cFinalKoopaDemo
    cDrawPriority_PeachDemo,                                // ProfileID::cPeachDemo
    cDrawPriority_Larry,                                    // ProfileID::cLarry
    cDrawPriority_KokoopaSearchFire,                        // ProfileID::cKokoopaSearchFire
    cDrawPriority_Lemmy,                                    // ProfileID::cLemmy
    cDrawPriority_Morton,                                   // ProfileID::cMorton
    cDrawPriority_MortonSanbo,                              // ProfileID::cMortonSanbo
    cDrawPriority_MortonSanboParts,                         // ProfileID::cMortonSanboParts
    cDrawPriority_Wendy,                                    // ProfileID::cWendy
    cDrawPriority_WendyRing,                                // ProfileID::cWendyRing
    cDrawPriority_Ludwig,                                   // ProfileID::cLudwig
    cDrawPriority_LudwigAlterEgo,                           // ProfileID::cLudwigAlterEgo
    cDrawPriority_Iggy,                                     // ProfileID::cIggy
    cDrawPriority_IggyMagic,                                // ProfileID::cIggyMagic
    cDrawPriority_Woogan,                                   // ProfileID::cWoogan
    cDrawPriority_Roy,                                      // ProfileID::cRoy
    cDrawPriority_RoyLiftWaki,                              // ProfileID::cRoyLiftWaki
    cDrawPriority_BossKK,                                   // ProfileID::cBossKK
    cDrawPriority_BossKKThunder,                            // ProfileID::cBossKKThunder
    cDrawPriority_Kameck,                                   // ProfileID::cKameck
    cDrawPriority_KameckIceConfig,                          // ProfileID::cKameckIceConfig
    cDrawPriority_KameckWarpPos,                            // ProfileID::cKameckWarpPos
    cDrawPriority_KameckMagic,                              // ProfileID::cKameckMagic
    cDrawPriority_PeachFinalCastleKoopaJr,                  // ProfileID::cPeachFinalCastleKoopaJr
    cDrawPriority_Koopa,                                    // ProfileID::cKoopa
    cDrawPriority_KoopaFireWaki,                            // ProfileID::cKoopaFireWaki
    cDrawPriority_KoopaFire,                                // ProfileID::cKoopaFire
    cDrawPriority_DemoKoopaJrClown,                         // ProfileID::cDemoKoopaJrClown
    cDrawPriority_DemoKoopaJr,                              // ProfileID::cDemoKoopaJr
    cDrawPriority_BunDemoKameck,                            // ProfileID::cBunDemoKameck
    cDrawPriority_KoopaDemoKameck,                          // ProfileID::cKoopaDemoKameck
    cDrawPriority_BossKKDemoKameck,                         // ProfileID::cBossKKDemoKameck
    cDrawPriority_BossKKDemoKK,                             // ProfileID::cBossKKDemoKK
    cDrawPriority_FinalKoopaFire,                           // ProfileID::cFinalKoopaFire
    cDrawPriority_FinalKoopaJr,                             // ProfileID::cFinalKoopaJr
    cDrawPriority_FinalKoopaJrFire,                         // ProfileID::cFinalKoopaJrFire
    cDrawPriority_FinalBomhei,                              // ProfileID::cFinalBomhei
    cDrawPriority_KokoopaShipLemmy,                         // ProfileID::cKokoopaShipLemmy
    cDrawPriority_KokoopaShipMorton,                        // ProfileID::cKokoopaShipMorton
    cDrawPriority_KokoopaShipLarry,                         // ProfileID::cKokoopaShipLarry
    cDrawPriority_KokoopaShipWendy,                         // ProfileID::cKokoopaShipWendy
    cDrawPriority_KokoopaShipIggy,                          // ProfileID::cKokoopaShipIggy
    cDrawPriority_KokoopaShipRoy,                           // ProfileID::cKokoopaShipRoy
    cDrawPriority_KokoopaShipLudwig,                        // ProfileID::cKokoopaShipLudwig
    cDrawPriority_Peach,                                    // ProfileID::cPeach
    cDrawPriority_2E0,                                      // ProfileID::c2E0
    cDrawPriority_FinalDVPeach,                             // ProfileID::cFinalDVPeach
    cDrawPriority_FinalDVShutter,                           // ProfileID::cFinalDVShutter
    cDrawPriority_2E3,                                      // ProfileID::c2E3
    cDrawPriority_2E4,                                      // ProfileID::c2E4
    cDrawPriority_2E5,                                      // ProfileID::c2E5
    cDrawPriority_2E6,                                      // ProfileID::c2E6
    cDrawPriority_2E7,                                      // ProfileID::c2E7
    cDrawPriority_2E8,                                      // ProfileID::c2E8
    cDrawPriority_2E9,                                      // ProfileID::c2E9
    cDrawPriority_2EA,                                      // ProfileID::c2EA
    cDrawPriority_2EB,                                      // ProfileID::c2EB
    cDrawPriority_2EC,                                      // ProfileID::c2EC
    cDrawPriority_2ED,                                      // ProfileID::c2ED
    cDrawPriority_2EE,                                      // ProfileID::c2EE
    cDrawPriority_2EF,                                      // ProfileID::c2EF
    cDrawPriority_2F0,                                      // ProfileID::c2F0
    cDrawPriority_2F1,                                      // ProfileID::c2F1
    cDrawPriority_2F2,                                      // ProfileID::c2F2
    cDrawPriority_2F3,                                      // ProfileID::c2F3
    cDrawPriority_2F4,                                      // ProfileID::c2F4
    cDrawPriority_2F5,                                      // ProfileID::c2F5
    cDrawPriority_Hammer,                                   // ProfileID::cHammer
    cDrawPriority_2F7,                                      // ProfileID::c2F7
    cDrawPriority_Boomerang,                                // ProfileID::cBoomerang
    cDrawPriority_2F9,                                      // ProfileID::c2F9
    cDrawPriority_FireBallBros,                             // ProfileID::cFireBallBros
    cDrawPriority_2FB,                                      // ProfileID::c2FB
    cDrawPriority_IceBallBros,                              // ProfileID::cIceBallBros
    cDrawPriority_2FD,                                      // ProfileID::c2FD
    cDrawPriority_MegaHammer,                               // ProfileID::cMegaHammer
    cDrawPriority_2FF,                                      // ProfileID::c2FF
    cDrawPriority_300,                                      // ProfileID::c300
    cDrawPriority_301,                                      // ProfileID::c301
    cDrawPriority_302,                                      // ProfileID::c302
    cDrawPriority_303,                                      // ProfileID::c303
    cDrawPriority_304,                                      // ProfileID::c304
    cDrawPriority_305,                                      // ProfileID::c305
    cDrawPriority_306,                                      // ProfileID::c306
    cDrawPriority_307,                                      // ProfileID::c307
    cDrawPriority_308,                                      // ProfileID::c308
    cDrawPriority_309,                                      // ProfileID::c309
    cDrawPriority_30A,                                      // ProfileID::c30A
    cDrawPriority_30B,                                      // ProfileID::c30B
    cDrawPriority_30C,                                      // ProfileID::c30C
    cDrawPriority_30D,                                      // ProfileID::c30D
    cDrawPriority_30E,                                      // ProfileID::c30E
    cDrawPriority_30F,                                      // ProfileID::c30F
    cDrawPriority_310,                                      // ProfileID::c310
    cDrawPriority_311,                                      // ProfileID::c311
    cDrawPriority_312,                                      // ProfileID::c312
    cDrawPriority_313,                                      // ProfileID::c313
    cDrawPriority_314,                                      // ProfileID::c314
    cDrawPriority_315,                                      // ProfileID::c315
    cDrawPriority_316,                                      // ProfileID::c316
    cDrawPriority_317,                                      // ProfileID::c317
    cDrawPriority_318,                                      // ProfileID::c318
    cDrawPriority_319,                                      // ProfileID::c319
    cDrawPriority_31A,                                      // ProfileID::c31A
    cDrawPriority_31B,                                      // ProfileID::c31B
    cDrawPriority_31C,                                      // ProfileID::c31C
    cDrawPriority_31D,                                      // ProfileID::c31D
    cDrawPriority_31E,                                      // ProfileID::c31E
    cDrawPriority_31F,                                      // ProfileID::c31F
    cDrawPriority_320,                                      // ProfileID::c320
    cDrawPriority_321,                                      // ProfileID::c321
    cDrawPriority_322,                                      // ProfileID::c322
    cDrawPriority_323,                                      // ProfileID::c323
    cDrawPriority_324,                                      // ProfileID::c324
    cDrawPriority_325,                                      // ProfileID::c325
    cDrawPriority_326,                                      // ProfileID::c326
    cDrawPriority_327,                                      // ProfileID::c327
    cDrawPriority_328,                                      // ProfileID::c328
    cDrawPriority_BattleItem,                               // ProfileID::cBattleItem
    cDrawPriority_32A,                                      // ProfileID::c32A
    cDrawPriority_VsBattleItem,                             // ProfileID::cVsBattleItem
    cDrawPriority_32C,                                      // ProfileID::c32C
    cDrawPriority_32D,                                      // ProfileID::c32D
    cDrawPriority_32E,                                      // ProfileID::c32E
    cDrawPriority_32F,                                      // ProfileID::c32F
    cDrawPriority_330,                                      // ProfileID::c330
    cDrawPriority_331,                                      // ProfileID::c331
    cDrawPriority_KoopaJrFire,                              // ProfileID::cKoopaJrFire
    cDrawPriority_KoopaJrBall,                              // ProfileID::cKoopaJrBall
    cDrawPriority_UnderwaterKoopaJr,                        // ProfileID::cUnderwaterKoopaJr
    cDrawPriority_UnderwaterKoopaJrClown,                   // ProfileID::cUnderwaterKoopaJrClown
    cDrawPriority_UnderwaterKoopaJrRetreatPos,              // ProfileID::cUnderwaterKoopaJrRetreatPos
    cDrawPriority_BoxingKoopaJr,                            // ProfileID::cBoxingKoopaJr
    cDrawPriority_BoxingKoopaJrPostBattleDemo,              // ProfileID::cBoxingKoopaJrPostBattleDemo
    cDrawPriority_BoxingKoopaJrClownPostBattleDemo,         // ProfileID::cBoxingKoopaJrClownPostBattleDemo
    cDrawPriority_MiniGamePanelItem,                        // ProfileID::cMiniGamePanelItem
    cDrawPriority_SlotItem,                                 // ProfileID::cSlotItem
    cDrawPriority_CoinmakiCannon,                           // ProfileID::cCoinmakiCannon
    cDrawPriority_CoinmakiItem,                             // ProfileID::cCoinmakiItem
    cDrawPriority_MiniGameKinopio,                          // ProfileID::cMiniGameKinopio
    cDrawPriority_33F,                                      // ProfileID::c33F
    cDrawPriority_340,                                      // ProfileID::c340
    cDrawPriority_341,                                      // ProfileID::c341
    cDrawPriority_342,                                      // ProfileID::c342
    cDrawPriority_343,                                      // ProfileID::c343
    cDrawPriority_344,                                      // ProfileID::c344
    cDrawPriority_345,                                      // ProfileID::c345
    cDrawPriority_346,                                      // ProfileID::c346
    cDrawPriority_347,                                      // ProfileID::c347
    cDrawPriority_StaffCreditChibiYoshiABC,                 // ProfileID::cStaffCreditChibiYoshiABC
    cDrawPriority_StaffCreditChibiYoshiBalloon,             // ProfileID::cStaffCreditChibiYoshiBalloon
    cDrawPriority_StaffCreditChibiYoshiBalloonCheer,        // ProfileID::cStaffCreditChibiYoshiBalloonCheer
    cDrawPriority_StaffCreditChibiYoshiLight,               // ProfileID::cStaffCreditChibiYoshiLight
    cDrawPriority_StaffCreditChibiYoshiLightCheer,          // ProfileID::cStaffCreditChibiYoshiLightCheer
    cDrawPriority_StaffCreditSoapABC,                       // ProfileID::cStaffCreditSoapABC
    cDrawPriority_StaffCreditSoapCoin,                      // ProfileID::cStaffCreditSoapCoin
    cDrawPriority_StaffCreditTottenKun,                     // ProfileID::cStaffCreditTottenKun
    cDrawPriority_350,                                      // ProfileID::c350
    cDrawPriority_351,                                      // ProfileID::c351
    cDrawPriority_352,                                      // ProfileID::c352
    cDrawPriority_353,                                      // ProfileID::c353
    cDrawPriority_RealizeFeverStar,                         // ProfileID::cRealizeFeverStar
    cDrawPriority_Star,                                     // ProfileID::cStar
    cDrawPriority_CourseSelectPlayer,                       // ProfileID::cCourseSelectPlayer
    cDrawPriority_CourseSelectPlayer2PSub,                  // ProfileID::cCourseSelectPlayer2PSub
    cDrawPriority_CourseSelectChibiYoshi,                   // ProfileID::cCourseSelectChibiYoshi
    cDrawPriority_CourseSelectCamera,                       // ProfileID::cCourseSelectCamera
    cDrawPriority_CourseSelectCastle,                       // ProfileID::cCourseSelectCastle
    cDrawPriority_CourseSelectToride,                       // ProfileID::cCourseSelectToride
    cDrawPriority_CourseSelectKinokoHouse1up,               // ProfileID::cCourseSelectKinokoHouse1up
    cDrawPriority_CourseSelectKinokoHouseShuffle,           // ProfileID::cCourseSelectKinokoHouseShuffle
    cDrawPriority_CourseSelectKinokoHouseSlot,              // ProfileID::cCourseSelectKinokoHouseSlot
    cDrawPriority_CourseSelectPeachGates1st,                // ProfileID::cCourseSelectPeachGates1st
    cDrawPriority_CourseSelectPeachGates2nd,                // ProfileID::cCourseSelectPeachGates2nd
    cDrawPriority_CourseSelectCoursePoint,                  // ProfileID::cCourseSelectCoursePoint
    cDrawPriority_CourseSelectWorldMoveDokan,               // ProfileID::cCourseSelectWorldMoveDokan
    cDrawPriority_CourseSelectW8Cloud,                      // ProfileID::cCourseSelectW8Cloud
    cDrawPriority_CourseSelectGhost,                        // ProfileID::cCourseSelectGhost
    cDrawPriority_CourseSelectW2Bros,                       // ProfileID::cCourseSelectW2Bros
    cDrawPriority_CourseSelectShipW1,                       // ProfileID::cCourseSelectShipW1
    cDrawPriority_CourseSelectShipW2,                       // ProfileID::cCourseSelectShipW2
    cDrawPriority_CourseSelectShipW3,                       // ProfileID::cCourseSelectShipW3
    cDrawPriority_CourseSelectShipW4,                       // ProfileID::cCourseSelectShipW4
    cDrawPriority_CourseSelectShipW5,                       // ProfileID::cCourseSelectShipW5
    cDrawPriority_CourseSelectShipW6,                       // ProfileID::cCourseSelectShipW6
    cDrawPriority_CourseSelectShipW7,                       // ProfileID::cCourseSelectShipW7
    cDrawPriority_CourseSelectShipW8,                       // ProfileID::cCourseSelectShipW8
    cDrawPriority_CourseSelectShipW8Broken,                 // ProfileID::cCourseSelectShipW8Broken
    cDrawPriority_CourseSelectSurrender,                    // ProfileID::cCourseSelectSurrender
    cDrawPriority_CourseSelectSwitchA,                      // ProfileID::cCourseSelectSwitchA
    cDrawPriority_CourseSelectSwitchB,                      // ProfileID::cCourseSelectSwitchB
    cDrawPriority_CourseSelectTeresa,                       // ProfileID::cCourseSelectTeresa
    cDrawPriority_CourseSelectOpeningKameck,                // ProfileID::cCourseSelectOpeningKameck
    cDrawPriority_CourseSelectTorideBoss,                   // ProfileID::cCourseSelectTorideBoss
    cDrawPriority_CourseSelectPakkun,                       // ProfileID::cCourseSelectPakkun
    cDrawPriority_CourseSelectShadowFirstDemoKinopio,       // ProfileID::cCourseSelectShadowFirstDemoKinopio
    cDrawPriority_CourseSelectTobiPuku,                     // ProfileID::cCourseSelectTobiPuku
    cDrawPriority_CourseSelectChorobon,                     // ProfileID::cCourseSelectChorobon
    cDrawPriority_CourseSelectW7Item,                       // ProfileID::cCourseSelectW7Item
    cDrawPriority_CourseSelectW5Teresa,                     // ProfileID::cCourseSelectW5Teresa
    cDrawPriority_CourseSelectFlag,                         // ProfileID::cCourseSelectFlag
    cDrawPriority_CourseSelectMusasabi,                     // ProfileID::cCourseSelectMusasabi
    cDrawPriority_CourseSelectWPillar,                      // ProfileID::cCourseSelectWPillar
    cDrawPriority_CourseSelectW7Bridge,                     // ProfileID::cCourseSelectW7Bridge
    cDrawPriority_CourseSelectMiiBalloon,                   // ProfileID::cCourseSelectMiiBalloon
    cDrawPriority_CourseSelectPenguin,                      // ProfileID::cCourseSelectPenguin
    cDrawPriority_CourseSelectW4Item,                       // ProfileID::cCourseSelectW4Item
    cDrawPriority_CourseSelectW2Kuribo,                     // ProfileID::cCourseSelectW2Kuribo
    cDrawPriority_CourseSelectPakkunBig,                    // ProfileID::cCourseSelectPakkunBig
    cDrawPriority_CourseSelectShadowKunIcon,                // ProfileID::cCourseSelectShadowKunIcon
    cDrawPriority_CourseSelectDekaUnira,                    // ProfileID::cCourseSelectDekaUnira
    cDrawPriority_CourseSelectTomb,                         // ProfileID::cCourseSelectTomb
    cDrawPriority_CourseSelectShadowFirstDemoShadowKun,     // ProfileID::cCourseSelectShadowFirstDemoShadowKun
    cDrawPriority_CourseSelectKotsuCoaster,                 // ProfileID::cCourseSelectKotsuCoaster
    cDrawPriority_CourseSelectKoopaJr,                      // ProfileID::cCourseSelectKoopaJr
    cDrawPriority_CourseSelectPeach,                        // ProfileID::cCourseSelectPeach
    cDrawPriority_CourseSelectW1Item,                       // ProfileID::cCourseSelectW1Item
    cDrawPriority_CourseSelectStarGate,                     // ProfileID::cCourseSelectStarGate
    cDrawPriority_CourseSelectEventAssistant,               // ProfileID::cCourseSelectEventAssistant
    cDrawPriority_38E,                                      // Profile 910
    cDrawPriority_38F,                                      // Profile 911
    cDrawPriority_390                                       // Profile 912
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
    Profile::cResType_Course,       // ProfileID::cElasticKinokoParent
    Profile::cResType_Course,       // ProfileID::cFloorGyration
    Profile::cResType_Course,       // ProfileID::c036
    Profile::cResType_Course,       // ProfileID::c037
    Profile::cResType_Course,       // ProfileID::c038
    Profile::cResType_Course,       // ProfileID::c039
    Profile::cResType_Course,       // ProfileID::c03A
    Profile::cResType_Course,       // ProfileID::c03B
    Profile::cResType_Course,       // ProfileID::cPairObjChild
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
    Profile::cResType_Course,       // ProfileID::cKinokoLift
    Profile::cResType_Course,       // ProfileID::cKinokoLiftColor
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
    Profile::cResType_Course,       // ProfileID::cKillerHoudai
    Profile::cResType_Course,       // ProfileID::cStretchKillerHoudai
    Profile::cResType_Course,       // ProfileID::cMagnumKillerHoudai
    Profile::cResType_Course,       // ProfileID::cMagnumKillerHoudaiDown
    Profile::cResType_Course,       // ProfileID::cSearchKillerHoudai
    Profile::cResType_Course,       // ProfileID::cSearchMagnumKillerHoudai
    Profile::cResType_Course,       // ProfileID::cSearchMagnumKillerHoudaiDown
    Profile::cResType_Course,       // ProfileID::cMagnumKillerHoudaiRDash
    Profile::cResType_Course,       // ProfileID::cMagnumKillerHoudaiDownRDash
    Profile::cResType_Course,       // ProfileID::cSearchMagnumKillerHoudaiRDash
    Profile::cResType_Course,       // ProfileID::cSearchMagnumKillerHoudaiDownRDash
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
    Profile::cResType_Course,       // ProfileID::cYoganIntermittent
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
    Profile::cResType_Course,       // ProfileID::cSnakeBlock
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
    Profile::cResType_Course,       // ProfileID::cBurner
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
    Profile::cResType_Course,       // ProfileID::cTarzanIvy
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
    Profile::cResType_Boot,         // ProfileID::cBlock
    Profile::cResType_Boot,         // ProfileID::c120
    Profile::cResType_Boot,         // ProfileID::c121
    Profile::cResType_Boot,         // ProfileID::c122
    Profile::cResType_Boot,         // ProfileID::cActorBlockRenga
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
    Profile::cResType_Course,       // ProfileID::cSwitchHatenaButton
    Profile::cResType_Course,       // ProfileID::cSwitchPbutton
    Profile::cResType_Course,       // ProfileID::cSwitchPbuttonRDash
    Profile::cResType_Course,       // ProfileID::cSwitchPbuttonNoWallKick
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
    Profile::cResType_Course,       // ProfileID::cFireBar
    Profile::cResType_Course,       // ProfileID::cFireBarSync
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
    Profile::cResType_Boot,         // ProfileID::cActorCoin
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
    Profile::cResType_Boot,         // ProfileID::cBlueCoin
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
    Profile::cResType_Boot,         // ProfileID::cYoshiFire
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
    Profile::cResType_Course,       // ProfileID::cNokonoko
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
    Profile::cResType_Course,       // ProfileID::cMechaKoopa
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
    Profile::cResType_Course,       // ProfileID::cFireSnake
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
    Profile::cResType_Course,       // ProfileID::cKazandan
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
    Profile::cResType_Boot,         // ProfileID::cSearchKiller
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
    Profile::cResType_Course,       // ProfileID::cWoochan
    Profile::cResType_Course,       // ProfileID::c28B
    Profile::cResType_Course,       // ProfileID::c28C
    Profile::cResType_Course,       // ProfileID::c28D
    Profile::cResType_Course,       // ProfileID::cBubble
    Profile::cResType_Course,       // ProfileID::cBubbleSync
    Profile::cResType_Course,       // ProfileID::cBubbleRDash
    Profile::cResType_Course,       // ProfileID::cBubbleSyncRDash
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

static const sead::SafeString cRes_0ED[]  = {
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
    0,                                                          // ProfileID::cElasticKinokoParent
    GetResNum(cRes_FloorGyration),                              // ProfileID::cFloorGyration
    GetResNum(cRes_036),                                        // ProfileID::c036
    GetResNum(cRes_037),                                        // ProfileID::c037
    GetResNum(cRes_038),                                        // ProfileID::c038
    GetResNum(cRes_039),                                        // ProfileID::c039
    GetResNum(cRes_03A),                                        // ProfileID::c03A
    GetResNum(cRes_03B),                                        // ProfileID::c03B
    GetResNum(cRes_PairObjChild),                               // ProfileID::cPairObjChild
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
    GetResNum(cRes_KinokoLift),                                 // ProfileID::cKinokoLift
    GetResNum(cRes_KinokoLiftColor),                            // ProfileID::cKinokoLiftColor
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
    GetResNum(cRes_KillerHoudai),                               // ProfileID::cKillerHoudai
    GetResNum(cRes_StretchKillerHoudai),                        // ProfileID::cStretchKillerHoudai
    GetResNum(cRes_MagnumKillerHoudai),                         // ProfileID::cMagnumKillerHoudai
    GetResNum(cRes_MagnumKillerHoudaiDown),                     // ProfileID::cMagnumKillerHoudaiDown
    GetResNum(cRes_SearchKillerHoudai),                         // ProfileID::cSearchKillerHoudai
    GetResNum(cRes_SearchMagnumKillerHoudai),                   // ProfileID::cSearchMagnumKillerHoudai
    GetResNum(cRes_SearchMagnumKillerHoudaiDown),               // ProfileID::cSearchMagnumKillerHoudaiDown
    GetResNum(cRes_MagnumKillerHoudaiRDash),                    // ProfileID::cMagnumKillerHoudaiRDash
    GetResNum(cRes_MagnumKillerHoudaiDownRDash),                // ProfileID::cMagnumKillerHoudaiDownRDash
    GetResNum(cRes_SearchMagnumKillerHoudaiRDash),              // ProfileID::cSearchMagnumKillerHoudaiRDash
    GetResNum(cRes_SearchMagnumKillerHoudaiDownRDash),          // ProfileID::cSearchMagnumKillerHoudaiDownRDash
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
    GetResNum(cRes_YoganIntermittent),                          // ProfileID::cYoganIntermittent
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
    GetResNum(cRes_SnakeBlock),                                 // ProfileID::cSnakeBlock
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
    GetResNum(cRes_Burner),                                     // ProfileID::cBurner
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
    GetResNum(cRes_TarzanIvy),                                  // ProfileID::cTarzanIvy
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
    0,                                                          // ProfileID::cBlock
    0,                                                          // ProfileID::c120
    0,                                                          // ProfileID::c121
    0,                                                          // ProfileID::c122
    0,                                                          // ProfileID::cActorBlockRenga
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
    GetResNum(cRes_SwitchHatenaButton),                         // ProfileID::cSwitchHatenaButton
    GetResNum(cRes_SwitchPbutton),                              // ProfileID::cSwitchPbutton
    GetResNum(cRes_SwitchPbuttonRDash),                         // ProfileID::cSwitchPbuttonRDash
    GetResNum(cRes_SwitchPbuttonNoWallKick),                    // ProfileID::cSwitchPbuttonNoWallKick
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
    GetResNum(cRes_FireBar),                                    // ProfileID::cFireBar
    GetResNum(cRes_FireBarSync),                                // ProfileID::cFireBarSync
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
    GetResNum(cRes_ActorCoin),                                  // ProfileID::cActorCoin
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
    GetResNum(cRes_BlueCoin),                                   // ProfileID::cBlueCoin
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
    0,                                                          // ProfileID::cYoshiFire
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
    GetResNum(cRes_Nokonoko),                                   // ProfileID::cNokonoko
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
    GetResNum(cRes_MechaKoopa),                                 // ProfileID::cMechaKoopa
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
    GetResNum(cRes_FireSnake),                                  // ProfileID::cFireSnake
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
    GetResNum(cRes_Kazandan),                                   // ProfileID::cKazandan
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
    0,                                                          // ProfileID::cSearchKiller
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
    GetResNum(cRes_Woochan),                                    // ProfileID::cWoochan
    GetResNum(cRes_28B),                                        // ProfileID::c28B
    GetResNum(cRes_28C),                                        // ProfileID::c28C
    GetResNum(cRes_28D),                                        // ProfileID::c28D
    GetResNum(cRes_Bubble),                                     // ProfileID::cBubble
    GetResNum(cRes_BubbleSync),                                 // ProfileID::cBubbleSync
    GetResNum(cRes_BubbleRDash),                                // ProfileID::cBubbleRDash
    GetResNum(cRes_BubbleSyncRDash),                            // ProfileID::cBubbleSyncRDash
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
    nullptr,                                        // ProfileID::cElasticKinokoParent
    cRes_FloorGyration,                             // ProfileID::cFloorGyration
    cRes_036,                                       // ProfileID::c036
    cRes_037,                                       // ProfileID::c037
    cRes_038,                                       // ProfileID::c038
    cRes_039,                                       // ProfileID::c039
    cRes_03A,                                       // ProfileID::c03A
    cRes_03B,                                       // ProfileID::c03B
    cRes_PairObjChild,                              // ProfileID::cPairObjChild
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
    cRes_KinokoLift,                                // ProfileID::cKinokoLift
    cRes_KinokoLiftColor,                           // ProfileID::cKinokoLiftColor
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
    cRes_KillerHoudai,                              // ProfileID::cKillerHoudai
    cRes_StretchKillerHoudai,                       // ProfileID::cStretchKillerHoudai
    cRes_MagnumKillerHoudai,                        // ProfileID::cMagnumKillerHoudai
    cRes_MagnumKillerHoudaiDown,                    // ProfileID::cMagnumKillerHoudaiDown
    cRes_SearchKillerHoudai,                        // ProfileID::cSearchKillerHoudai
    cRes_SearchMagnumKillerHoudai,                  // ProfileID::cSearchMagnumKillerHoudai
    cRes_SearchMagnumKillerHoudaiDown,              // ProfileID::cSearchMagnumKillerHoudaiDown
    cRes_MagnumKillerHoudaiRDash,                   // ProfileID::cMagnumKillerHoudaiRDash
    cRes_MagnumKillerHoudaiDownRDash,               // ProfileID::cMagnumKillerHoudaiDownRDash
    cRes_SearchMagnumKillerHoudaiRDash,             // ProfileID::cSearchMagnumKillerHoudaiRDash
    cRes_SearchMagnumKillerHoudaiDownRDash,         // ProfileID::cSearchMagnumKillerHoudaiDownRDash
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
    cRes_YoganIntermittent,                         // ProfileID::cYoganIntermittent
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
    cRes_SnakeBlock,                                // ProfileID::cSnakeBlock
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
    cRes_Burner,                                    // ProfileID::cBurner
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
    cRes_TarzanIvy,                                 // ProfileID::cTarzanIvy
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
    nullptr,                                        // ProfileID::cBlock
    nullptr,                                        // ProfileID::c120
    nullptr,                                        // ProfileID::c121
    nullptr,                                        // ProfileID::c122
    nullptr,                                        // ProfileID::cActorBlockRenga
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
    cRes_SwitchHatenaButton,                        // ProfileID::cSwitchHatenaButton
    cRes_SwitchPbutton,                             // ProfileID::cSwitchPbutton
    cRes_SwitchPbuttonRDash,                        // ProfileID::cSwitchPbuttonRDash
    cRes_SwitchPbuttonNoWallKick,                   // ProfileID::cSwitchPbuttonNoWallKick
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
    cRes_FireBar,                                   // ProfileID::cFireBar
    cRes_FireBarSync,                               // ProfileID::cFireBarSync
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
    cRes_ActorCoin,                                 // ProfileID::cActorCoin
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
    cRes_BlueCoin,                                  // ProfileID::cBlueCoin
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
    nullptr,                                        // ProfileID::cYoshiFire
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
    cRes_Nokonoko,                                  // ProfileID::cNokonoko
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
    cRes_MechaKoopa,                                // ProfileID::cMechaKoopa
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
    cRes_FireSnake,                                 // ProfileID::cFireSnake
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
    cRes_Kazandan,                                  // ProfileID::cKazandan
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
    nullptr,                                        // ProfileID::cSearchKiller
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
    cRes_Woochan,                                   // ProfileID::cWoochan
    cRes_28B,                                       // ProfileID::c28B
    cRes_28C,                                       // ProfileID::c28C
    cRes_28D,                                       // ProfileID::c28D
    cRes_Bubble,                                    // ProfileID::cBubble
    cRes_BubbleSync,                                // ProfileID::cBubbleSync
    cRes_BubbleRDash,                               // ProfileID::cBubbleRDash
    cRes_BubbleSyncRDash,                           // ProfileID::cBubbleSyncRDash
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
