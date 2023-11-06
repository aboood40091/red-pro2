#pragma once

#include <misc/rio_Types.h>

class BasicModel;
class Model;
class ModelFFL;
class RenderObjLayer;

class Renderer
{
public:
    static bool createSingleton();
    static void destroySingleton();
    static Renderer* instance() { return sInstance; }

private:
    static Renderer* sInstance;

    Renderer();
    ~Renderer();

    Renderer(const Renderer&);
    Renderer& operator=(const Renderer&);

public:
    void setLayer(RenderObjLayer* p_layer)
    {
        RIO_ASSERT(p_layer != nullptr);
        mpLayer = p_layer;
    }

    void resetLayer()
    {
        mpLayer = nullptr;
    }

    void drawModel(Model* p_model, bool draw_opa = true, bool draw_xlu = true);
    void drawModel(const BasicModel& model, bool draw_opa = true, bool draw_xlu = true);
    void drawModel(ModelFFL* p_model, bool draw_opa = true, bool draw_xlu = true);

    // TODO
  //void drawActorBgUnit(UnitID unit, const sead::Vector3f& pos, u32 angle, const sead::Vector3f& scale);
  //void drawActorBgUnitLayer0(UnitID unit, const sead::Vector3f& pos, u32 angle, const sead::Vector3f& scale);

private:
    RenderObjLayer* mpLayer;
};
