#include <graphics/FrameCtrl.h>

FrameCtrl::FrameCtrl()
    : mFrameStart(0.0f)
    , mFrameEnd(1.0f)
    , mFrameMin(0.0f)
    , mFrameMax(1.0f)
    , mFrame(0.0f)
    , mRate(1.0f)
    , mFlag(cFlag_Repeat | cFlag_StartFrame)
{
}

void FrameCtrl::reset()
{
    if (mRate >= 0.0f)
        mFrame = mFrameStart;
    else
        mFrame = mFrameEnd;

    mFlag.reset(cFlag_LoopFrame | cFlag_HasLooped | cFlag_EndFrame | cFlag_IsStop);
    mFlag.set(cFlag_StartFrame);
}

void FrameCtrl::setPlayMode(PlayMode mode)
{
    switch (mode)
    {
    case cMode_NoRepeat:
        mFlag.reset(cFlag_Repeat);
        return;
    case cMode_Repeat:
        mFlag.set(cFlag_Repeat);
        return;
    }
}

void FrameCtrl::play()
{
    {
        f32 frame = mFrame;
        if (frame < mFrameStart)
            frame = mFrameStart;
        else if (frame > mFrameEnd)
            frame = mFrameEnd;

        mFrame = frame;
    }
    mFlag.reset(cFlag_LoopFrame | cFlag_EndFrame);

    if (mFlag.isOn(cFlag_StartFrame))
    {
        mFlag.reset(cFlag_StartFrame);
        return;
    }

    if (mFlag.isOff(cFlag_Repeat) && mFlag.isOn(cFlag_IsStop))
        return;

    if (mFrameStart == mFrameEnd)
    {
        if (mFlag.isOn(cFlag_Repeat))
            mFlag.set(cFlag_LoopFrame | cFlag_HasLooped);

        else
            mFlag.set(cFlag_EndFrame | cFlag_IsStop);

        return;
    }

    if (mRate == 0.0f)
        return;

    mFrame += mRate;

    if (mFlag.isOn(cFlag_Repeat))
    {
        if (mRate >= 0.0f)
        {
            if (mFrame >= mFrameEnd)
            {
                f32 frame_end = mFrameEnd;
                f32 frame_step = frame_end - mFrameMin;
                mFlag.set(cFlag_LoopFrame | cFlag_HasLooped);

                if (frame_step <= 0.0f)
                    mFrame = frame_end;

                else
                {
                    f32 frame = mFrame;
                    do
                    {
                        frame -= frame_step;
                    } while (frame >= frame_end);
                    mFrame = frame;
                }
            }
        }
        else
        {
            if (mFrame <= mFrameStart)
            {
                f32 frame_start = mFrameStart;
                f32 frame_step = mFrameMax - frame_start;
                mFlag.set(cFlag_LoopFrame | cFlag_HasLooped);

                if (frame_step <= 0.0f)
                    mFrame = frame_start;

                else
                {
                    f32 frame = mFrame;
                    do
                    {
                        frame += frame_step;
                    } while (frame <= frame_start);
                    mFrame = frame;
                }
            }
        }
    }
    else
    {
        if (mFrame >= mFrameEnd)
        {
            mFrame = mFrameEnd;
            mFlag.set(cFlag_EndFrame | cFlag_IsStop);
        }
        else if (mFrame <= mFrameStart)
        {
            mFrame = mFrameStart;
            mFlag.set(cFlag_EndFrame | cFlag_IsStop);
        }
    }
}
