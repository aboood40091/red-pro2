#pragma once

#include <graphics/FrameCtrl.h>

class Animation
{
public:
    Animation();
    virtual void calc() = 0;

    FrameCtrl& getFrameCtrl() { return mFrameCtrl; }
    const FrameCtrl& getFrameCtrl() const { return mFrameCtrl; }

protected:
    FrameCtrl mFrameCtrl;
};
