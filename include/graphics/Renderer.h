#pragma once

#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>

class Model;
class BasicModel;
class RenderObjLayerBase;

class Renderer
{
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    Renderer();
    ~Renderer();

    void setTargetLayer(RenderObjLayerBase* p_layer, u32 obj_buffer_type = 0);
    void resetTargetLayer();

    void drawModel(Model* p_model);
    void drawModel(BasicModel* p_bmdl);
  //void drawModel(ModelFFL* p_model);
    void drawUnit(u16 unit_no, const sead::Vector3f& trans, const u32& rotat, const sead::Vector3f& scale);

private:
    sead::BoundBox2f        _10;
    sead::OrthoProjection   mProjection;
    sead::LookAtCamera      mCamera;        // Actually sead::OrthoCamera
    RenderObjLayerBase*     mpLayer;
    s32                     mOpaBufferIdx;
    s32                     mXluBufferIdx;
    sead::OrthoProjection   _130;
    sead::LookAtCamera      _1dc;           // Actually sead::OrthoCamera
};
static_assert(sizeof(Renderer) == 0x234);
