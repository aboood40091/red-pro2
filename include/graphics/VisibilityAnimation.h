#pragma once

#include <graphics/Animation.h>

#include <prim/seadSafeString.h>

class ResArchive;

class VisibilityAnimation : public Animation
{
public:
    VisibilityAnimation();
    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& name);
};
