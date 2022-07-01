#pragma once

#include <graphics/Animation.h>

#include <prim/seadSafeString.h>

class ResArchive;

class ShaderParamAnimation : public Animation
{
public:
    ShaderParamAnimation();
    void calc() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& name);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& name);
};
