#pragma once

#include <graphics/Layer.h>

#include <math/seadMatrix.h>
#include <math/seadVector.h>

class ObjLayerRenderer;

class ObjLayer /* : public Layer // size: 0x42C */
{
    // SEAD_RTTI_OVERRIDE(ObjLayer, Layer)

public:
    class Node : public Layer::Node
    {
        SEAD_RTTI_OVERRIDE(Node, Layer::Node)

    public:
        Node()
            : Layer::Node()
        {
        }

        virtual void calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) = 0;
        virtual void updateView(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) = 0;
        virtual void drawShadowOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) { }
        virtual void drawReflectionXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, ObjLayerRenderer* renderer) { }
        virtual bool hasShadow() const { return false; }

    protected:
        sead::Vector3f mOrderPos; // I think. Precisely used for z ordering.
    };

public:
    // ...
};
// static_assert(sizeof(ObjLayer) == 0x42C, "ObjLayer size mismatch");
