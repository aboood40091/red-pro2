#include <player/PlayerBase.h>

static const GameAudio::SoundID cFootSound[] = {
    "SE_PLY_FOOTNOTE_ROCK",
    "SE_PLY_FOOTNOTE_SNOW",
    "SE_PLY_FOOTNOTE_SAND",
    "SE_PLY_FOOTNOTE_ROCK",
    "SE_PLY_FOOTNOTE_DIRT",
    "SE_PLY_FOOTNOTE_WATER",
    "SE_PLY_FOOTNOTE_CLOUD",
    "SE_PLY_FOOTNOTE_BLOWSAND",
    "SE_PLY_FOOTNOTE_MANTA",
    "SE_PLY_FOOTNOTE_SAND",
    "SE_PLY_FOOTNOTE_CARPET",
    "SE_PLY_FOOTNOTE_LEAF",
    "SE_PLY_FOOTNOTE_WOOD",
    "SE_PLY_FOOTNOTE_WATER"
};
static_assert((sizeof(cFootSound) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

static const GameAudio::SoundID cLandSound[] = {
    "SE_PLY_LAND_ROCK",
    "SE_PLY_LAND_SNOW",
    "SE_PLY_LAND_SAND",
    "SE_PLY_LAND_ROCK",
    "SE_PLY_LAND_DIRT",
    "SE_PLY_LAND_WATER",
    "SE_PLY_LAND_CLOUD",
    "SE_PLY_LAND_BLOWSAND",
    "SE_PLY_LAND_MANTA",
    "SE_PLY_LAND_SAND",
    "SE_PLY_LAND_CARPET",
    "SE_PLY_LAND_LEAF",
    "SE_PLY_LAND_ROCK",
    "SE_PLY_LAND_WATER"
};
static_assert((sizeof(cLandSound) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

static const GameAudio::SoundID cSlipSound[] = {
    "SE_PLY_SLIP",
    "SE_PLY_SLIP_SNOW",
    "SE_PLY_SLIP_SAND",
    "SE_PLY_SLIP_ICE",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP_SAND",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP_SAND",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP",
    "SE_PLY_SLIP"
};
static_assert((sizeof(cSlipSound) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);
