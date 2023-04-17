#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>

#include <nw/g3d/g3d_ShapeObj.h>

namespace sead {

class Camera;
class PerspectiveProjection;

}

class CullViewFrustum
{
    struct Sub
    {
        Sub()
            : _0(sead::Vector3f::ex)
            , _c(0.0f)
        {
        }

        sead::Vector3f  _0;
        f32             _c;
    };
    static_assert(sizeof(Sub) == 0x10);

public:
    CullViewFrustum();

    nw::g3d::ViewVolume& getViewVolume() { return mViewVolume; }
    const nw::g3d::ViewVolume& getViewVolume() const { return mViewVolume; }

    void update(const sead::Camera& camera, const sead::PerspectiveProjection& projection);

private:
    sead::UnsafeArray<Sub, 4>   _0;
    nw::g3d::ViewVolume         mViewVolume;
};
static_assert(sizeof(CullViewFrustum) == 0xC0);
