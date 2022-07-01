#pragma once

#include <graphics/Animation.h>

#include <prim/seadSafeString.h>

class ResArchive;

class TexPatternAnimation : public Animation
{
public:
    TexPatternAnimation();
    void calc() override;

    void play(ResArchive* archive, const sead::SafeString& name);
};
