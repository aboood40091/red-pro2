#pragma once

#include <prim/seadBitFlag.h>

class FrameCtrl
{
public:
    enum PlayMode
    {
        cMode_NoRepeat  = 0,
        cMode_Repeat    = 1
    };

public:
    FrameCtrl();

    void reset();
    void setPlayMode(PlayMode mode);
    void play();

    f32 getFrameStart() const { return mFrameStart; }
    void setFrameStart(f32 frame) { mFrameStart = frame; }

    f32 getFrameEnd() const { return mFrameEnd; }
    void setFrameEnd(f32 frame) { mFrameEnd = frame; }

    f32 getFrameMin() const { return mFrameMin; }
    void setFrameMin(f32 frame) { mFrameMin = frame; }

    f32 getFrameMax() const { return mFrameMax; }
    void setFrameMax(f32 frame) { mFrameMax = frame; }

    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; mFlag.set(cFlag_Unk1); }

    f32 getRate() const { return mRate; }
    void setRate(f32 rate) { mRate = rate; }

    void set(PlayMode mode, f32 rate, f32 frame)
    {
        setPlayMode(mode);
        setRate(rate);
        setFrame(frame);
    }

    bool isStop() const
    {
        return mFlag.isOn(cFlag_IsStop);
    }

    bool checkFrame(f32) const;

protected:
    enum Flag
    {
        cFlag_Repeat    = 1 << 0,
        cFlag_Unk1      = 1 << 1,
        cFlag_Unk2      = 1 << 2,
        cFlag_Unk3      = 1 << 3,
        cFlag_Unk4      = 1 << 4,
        cFlag_IsStop    = 1 << 5
    };

    f32             mFrameStart;
    f32             mFrameEnd;
    f32             mFrameMin;
    f32             mFrameMax;
    f32             mFrame;
    f32             mRate;
    sead::BitFlag32 mFlag;
};
static_assert(sizeof(FrameCtrl) == 0x1C);
