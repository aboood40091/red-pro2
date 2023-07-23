#pragma once

#include <common/aglShaderProgramArchive.h>
#include <heap/seadHeap.h>
#include <math/seadVector.h>

enum LayerID;
enum UnitID;

class BgRenderer
{
    SEAD_SINGLETON_DISPOSER(BgRenderer)

public:
    static void initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap);

public:
    BgRenderer();
    ~BgRenderer();

    void drawActorBgUnit(LayerID layer, UnitID unit, const sead::Vector3f& pos, const sead::Vector3u& rot, const sead::Vector3f& scale);
};
