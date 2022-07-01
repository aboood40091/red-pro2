#include <graphics/RenderObj.h>

RenderObj::RenderObj()
    : ObjLayer::Node()
    , sead::IDisposer()
    , mOpaBufferIdx(-2)
    , mXluBufferIdx(-2)
{
}

RenderObj::~RenderObj()
{
}
