#include <graphics/BasicModel.h>
#include <graphics/Renderer.h>
#include <graphics/RenderMgr.h>
#include <graphics/RenderObjLayer.h>

Renderer* Renderer::sInstance = nullptr;

bool Renderer::createSingleton()
{
    if (sInstance)
        return false;

    sInstance = new Renderer();
    return true;
}

void Renderer::destroySingleton()
{
    if (!sInstance)
        return;

    delete sInstance;
    sInstance = nullptr;
}

Renderer::Renderer()
    : mpLayer(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::drawModel(Model* p_model, bool draw_opa, bool draw_xlu)
{
    RIO_ASSERT(p_model != nullptr);

    const rio::Matrix34f& mtx_rt = p_model->getMtxRT();

    p_model->getOrderPos().x = mtx_rt.m[0][3];
    p_model->getOrderPos().y = mtx_rt.m[1][3];
    p_model->getOrderPos().z = mtx_rt.m[2][3];

    RIO_ASSERT(mpLayer != nullptr);
    RIO_ASSERT(mpLayer->getRenderMgr() != nullptr);

    mpLayer->getRenderMgr()->pushBackRenderObj(p_model, draw_opa, draw_xlu);
}

void Renderer::drawModel(const BasicModel& model, bool draw_opa, bool draw_xlu)
{
    drawModel(model.getModel(), draw_opa, draw_xlu);
}
