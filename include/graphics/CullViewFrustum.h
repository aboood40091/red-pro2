#pragma once

#include <math/rio_Vector.h>

#include <nw/g3d/g3d_ShapeObj.h>

class CullViewFrustum
{
    struct Sub
    {
        Sub()
            : _0{1.0f, 0.0f, 0.0f}
            , _c(0.0f)
        {
        }

        rio::Vector3f _0;
        f32 _c;
    };

public:
    nw::g3d::ViewVolume& getViewVolume() { return mViewVolume; }
    const nw::g3d::ViewVolume& getViewVolume() const { return mViewVolume; }

private:
    Sub _0[4];
    nw::g3d::ViewVolume mViewVolume;
};
static_assert(sizeof(CullViewFrustum) == 0xC0, "CullViewFrustum size mismatch");
