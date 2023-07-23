#pragma once

#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <heap/seadDisposer.h>
#include <layer/aglLayer.h>
#include <math/seadBoundBox.h>

class   BasicModel;
class   Model;
class   ModelFFL;
class   RenderObjLayerBase;
enum    UnitID;

class Angle
{
public:
    Angle(u32 angle)
        : value(angle)
    {
    }

    operator u32() const
    {
        return value;
    }

private:
    u32 value;
};

class Renderer
{
    SEAD_SINGLETON_DISPOSER(Renderer)

public:
    enum GatherType
    {
        cGatherType_0 = 0,  // AreaTask
        cGatherType_1,      // CourseSelectTask, DarkCloudDemoScene, GameSetupScene, MultiPlayCourseSelectScene, ResultScene
        cGatherType_2,      // DemoTestScene
        cGatherType_3       // CourseTask, ChallengeResultScene, WithMiiPackSelectScene
    };

public:
    Renderer();
    ~Renderer();

    void setViewBoundBox(const sead::BoundBox2f& box);

    void calcForAreaTask();

    void setLayer(agl::lyr::Layer* p_layer, GatherType type);
    void resetLayer();

    void drawModel(Model* p_model);
    void drawModel(const BasicModel& model);
    void drawModel(ModelFFL* p_model);

    void drawActorBgUnit(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale);
    void drawActorBgUnitLayer0(UnitID unit, const sead::Vector3f& pos, Angle angle, const sead::Vector3f& scale);

private:
    sead::BoundBox2f        mViewBoundBox;
    sead::OrthoProjection   mProjection3D;
    sead::OrthoCamera       mCamera3D;
    RenderObjLayerBase*     mpLayer;
    s32                     mDefaultOpaBufferIdx;
    s32                     mDefaultXluBufferIdx;
    sead::OrthoProjection   mProjectionFinalKoopa;
    sead::OrthoCamera       mCameraFinalKoopa;
};
static_assert(sizeof(Renderer) == 0x234);
