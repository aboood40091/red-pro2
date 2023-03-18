#pragma once

#include <sound/AudAudioMgr.h>

#include <heap/seadDisposer.h>

class SndAudioMgr : public AudAudioMgr
{
    SEAD_SINGLETON_DISPOSER(SndAudioMgr)
};
