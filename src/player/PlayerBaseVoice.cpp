#include <game/Info.h>
#include <input/SysControllerMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>

static const GameAudio::SoundID cFootSeID[] = {
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
static_assert((sizeof(cFootSeID) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

static const GameAudio::SoundID cLandSeID[] = {
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
static_assert((sizeof(cLandSeID) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

static const GameAudio::SoundID cSlipSeID[] = {
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
static_assert((sizeof(cSlipSeID) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

bool PlayerBase::isDisableSound(StartSoundType type)
{
    if (type == cStartSoundType_DisableInEnding && isStatus(cStatus_EndingDisableSound))
        return true;

    if (isStatus(cStatus_DisableSound))
        return true;

    if (Info::instance()->isTitle())
        return true;

    return false;
}

void PlayerBase::startSound(const char* label, StartSoundType type)
{
    if (isDisableSound(type))
        return;

    if (mPlayerNo != -1)
        mAudioObj.startSound(label, GameAudio::getRemotePlayer(mPlayerNo));
    else
        mAudioObj.startSound(label);
}

void PlayerBase::startSound(const char* label, s16 seq_var, StartSoundType type)
{
    if (isDisableSound(type))
        return;

    if (mPlayerNo != -1)
        mAudioObj.startSound(label, seq_var, GameAudio::getRemotePlayer(mPlayerNo));
    else
        mAudioObj.startSound(label, seq_var);
}

void PlayerBase::holdSound(const char* label, StartSoundType type)
{
    if (isDisableSound(type))
        return;

    if (mPlayerNo != -1)
        mAudioObj.holdSound(label, GameAudio::getRemotePlayer(mPlayerNo));
    else
        mAudioObj.holdSound(label);
}

void PlayerBase::holdSound(const char* label, s16 seq_var, StartSoundType type)
{
    if (isDisableSound(type))
        return;

    if (mPlayerNo != -1)
        mAudioObj.holdSound(label, seq_var, GameAudio::getRemotePlayer(mPlayerNo));
    else
        mAudioObj.holdSound(label, seq_var);
}

void PlayerBase::startVoiceSound(PlayerVoiceID voice_id, StartSoundType type)
{
    if (isDisableSound(type))
        return;

    if (SysControllerMgr::instance()->isURCC(mPlayerNo) && voice_id == BALLOON_HELP__RC)
        mAudioObj.startPlyVoiceSound(BALLOON_HELP__RC);
    else
    {
        u32 line_flag = 0;
        if (mPlayerNo != -1)
            line_flag = GameAudio::getRemotePlayer(mPlayerNo);
        mAudioObj.startPlyVoiceSound(voice_id, nw::snd::OutputLine(line_flag));
    }
}

void PlayerBase::setItemCompleteVoice()
{
    startVoiceSound(ITEM_COMPLETE);
}

void PlayerBase::setHitBlockSE()
{
    if (isNowBgCross(cBgCross_70))
        return;

    if (isNowBgCross(cBgCross_76))
        return;

    if (isNowBgCross(cBgCross_IsHold))
        return;

    u16 seq_var = 0;
    if (mMode == cPlayerMode_Mini)
        seq_var = 1;

    if (isNowBgCross(cBgCross_66))
    {
        startSound("SE_PLY_HIT_BLOCK_BOUND", seq_var);
    }
    else if (isNowBgCross(cBgCross_69))
    {
        if (isNowBgCross(cBgCross_71))
            startSound("SE_PLY_HIT_BLOCK", seq_var);
        else if (isNowBgCross(cBgCross_HitBgActorYuka))
            startSound("SE_PLY_HIT_BROS_FLR_BOUND", seq_var);
        else
            startSound("SE_PLY_HIT_GENERAL_OBJ", seq_var);
    }
    else
    {
        startSound("SE_PLY_HIT_BLOCK", seq_var);
    }
}

void PlayerBase::startFootSoundPlayer(const char* label)
{
    if (isDisableSound(cStartSoundType_DisableInEnding))
        return;

    u32 line_flag = 0;
    if (mPlayerNo != -1)
        line_flag = GameAudio::getRemotePlayer(mPlayerNo);
    mAudioObj.startFootSound(label, sead::Mathf::abs(mSpeedF), nw::snd::OutputLine(line_flag));
}

void PlayerBase::setFootSE(BgAttr attr)
{
    if (mpModelBaseMgr->isFootStepTiming())
    {
        const char* label = "SE_PLY_FOOTNOTE_PNGN";
        if (mMode != cPlayerMode_Penguin)
            label = cFootSeID[attr];
        startFootSoundPlayer(label);
    }
}

void PlayerBase::setFootSound()
{
    if (!(isDemoAll() || isNowBgCross(cBgCross_IsFoot)))
        return;

    if (Info::instance()->isShortPlay() && mPlayerNo != 0)
        return;

    if (isNowBgCross(cBgCross_IsUnderwater))
        return;

    setFootSE(mBgAttr);
}

void PlayerBase::setLandSE()
{
    const char* label = "SE_PLY_LAND_PNGN";
    if (mMode != cPlayerMode_Penguin)
        label = cLandSeID[mBgAttr];
    startFootSoundPlayer(label);
}

void PlayerBase::setSlipSE()
{
    if (mBgAttr == cBgAttr_Water1)
        holdSound("SE_PLY_PNGN_SLIP_SEA", (s16)sead::Mathf::abs(mSpeedF));
    else
        holdSound(cSlipSeID[mBgAttr]);
}

void PlayerBase::setTurnSE()
{
    if (mSpeedF == 0.0f)
        return;

    static const GameAudio::SoundID cTurnSeID[] = {
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE_SNOW",
        "SE_PLY_BRAKE_SAND",
        "SE_PLY_BRAKE_ICE",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE_WATER",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE_SAND",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE_SAND",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE",
        "SE_PLY_BRAKE_WATER"
    };
    static_assert((sizeof(cTurnSeID) / sizeof(GameAudio::SoundID)) == PlayerBase::cBgAttr_Num);

    holdSound(cTurnSeID[mBgAttr]);
}
