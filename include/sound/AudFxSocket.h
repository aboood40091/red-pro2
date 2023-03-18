#pragma once

#include <basis/seadTypes.h>

#include <nw/snd.h>

class AudFxSocket
{
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam&    getDelayParam();
};
