#pragma once

#include <graphics/Animation.h>

#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

class Model;
class ResArchive;

class SkeletalAnimation : public Animation
{
public:
    SkeletalAnimation();
    void calc() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& name);

    // nw::g3d::SkeletalAnimObj at 0x20
};
