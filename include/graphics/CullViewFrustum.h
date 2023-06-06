#pragma once

#include <container/SafeArray.h>
#include <math/rio_Vector.h>

#include <nw/g3d/g3d_ShapeObj.h>

namespace rio {

class Camera;
class PerspectiveProjection;

}

class CullViewFrustum
{
    struct Sub
    {
        Sub()
            : _0{1.0f, 0.0f, 0.0f}
            , _c(0.0f)
        {
        }

        rio::Vector3f   _0;
        f32             _c;
    };
    static_assert(sizeof(Sub) == 0x10);

public:
    CullViewFrustum();

    nw::g3d::ViewVolume& getViewVolume() { return mViewVolume; }
    const nw::g3d::ViewVolume& getViewVolume() const { return mViewVolume; }

    void update(const rio::Camera& camera, const rio::PerspectiveProjection& projection);

private:
    UnsafeArray<Sub, 4> _0;
    nw::g3d::ViewVolume mViewVolume;
};
static_assert(sizeof(CullViewFrustum) == 0xC0);
