#include <graphics/Model.h>

Model::Model()
    : RenderObj()
    , sead::IDisposer()
    , mOpaBufferIdx(-2)
    , mXluBufferIdx(-2)
{
}

Model::~Model()
{
}
