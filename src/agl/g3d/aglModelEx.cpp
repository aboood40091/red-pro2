#include <g3d/aglModelEx.h>

namespace agl { namespace g3d {

MaterialEx::MaterialEx()
    : mpModelEx(NULL)
    , mpMaterialObj(NULL)
    , mpProgram(NULL)
    , mMatBlock()
    , _20(true)
{
}

MaterialEx::~MaterialEx()
{
    fixUpUBO();
}

void MaterialEx::init(agl::g3d::ModelEx* p_model, u32 index, sead::Heap* heap)
{
    mpModelEx = p_model;
    mpMaterialObj = p_model->GetMaterial(index);
    mMatBlock = static_cast<nw::g3d::fnd::GfxBuffer_t&>(mpMaterialObj->GetMatBlock());
}

void MaterialEx::bindShader(const ShaderProgram* p_program)
{
    mpProgram = p_program;

    for (s32 idx_shape = 0; idx_shape < mpModelEx->GetShapeCount(); idx_shape++)
    {
        if (&mpModelEx->getMaterialEx(mpModelEx->GetShape(idx_shape)->GetMaterialIndex()) == this)
        {
            mpModelEx->getShaderAssign(idx_shape).bindShader(
                mpMaterialObj->GetResource(),
                mpModelEx->GetShape(idx_shape)->GetResource(),
                p_program
            );
        }
    }
}

void MaterialEx::replaceUBO(const nw::g3d::fnd::GfxBuffer_t& buffer)
{
    static_cast<nw::g3d::fnd::GfxBuffer_t&>(mpMaterialObj->GetMatBlock()) = buffer;
}

void MaterialEx::fixUpUBO()
{
    replaceUBO(mMatBlock);
}

ModelEx::ModelEx()
    : nw::g3d::ModelObj()
    , mpShaderAssign(NULL)
    , mpMaterialEx(NULL)
{
}

ModelEx::~ModelEx()
{
    destroyEx();
}

void ModelEx::createEx(sead::Heap* heap)
{
    const nw::g3d::res::ResModel* p_res_mdl = GetResource();
    s32 shape_num = p_res_mdl->GetShapeCount();
    s32 material_num = p_res_mdl->GetMaterialCount();

    mpShaderAssign = new (heap) ModelShaderAssign[shape_num];
    mpMaterialEx = new (heap) MaterialEx[material_num];

    for (s32 idx_material = 0; idx_material < material_num; idx_material++)
        mpMaterialEx[idx_material].init(this, idx_material, heap);

    for (s32 idx_shape = 0; idx_shape < shape_num; idx_shape++)
        mpShaderAssign[idx_shape].create(heap);
}

void ModelEx::destroyEx()
{
    if (mpShaderAssign)
    {
        delete[] mpShaderAssign;
        mpShaderAssign = NULL;
    }
    if (mpMaterialEx)
    {
        delete[] mpMaterialEx;
        mpMaterialEx = NULL;
    }
}

} }
