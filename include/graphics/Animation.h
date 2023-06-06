#pragma once

#include <graphics/FrameCtrl.h>

class Animation
{
public:
    Animation();
    virtual void calc() = 0;

    void update();

    FrameCtrl& getFrameCtrl() { return mFrameCtrl; }
    const FrameCtrl& getFrameCtrl() const { return mFrameCtrl; }

protected:
    FrameCtrl   mFrameCtrl;
};
static_assert(sizeof(Animation) == 0x20);
