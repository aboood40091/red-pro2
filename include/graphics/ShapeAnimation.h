#pragma once

#include <graphics/Animation.h>

#include <prim/seadSafeString.h>

class ResArchive;

class ShapeAnimation : public Animation
{
public:
    ShapeAnimation();
    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& name);
};
