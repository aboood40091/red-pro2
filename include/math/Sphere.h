#pragma once

#include <math/rio_Vector.h>

template <typename VectorType>
class Sphere
{
public:
    typedef typename VectorType::ValueType T;

public:
    Sphere()
        : mCenter(VectorType::zero)
        , mRadius(0.0f)
    {
    }

    Sphere(const VectorType& center, T radius)
        : mCenter(center)
        , mRadius(radius)
    {
    }

    const VectorType& getCenter() const { return mCenter; }
    T getRadius() const { return mRadius; }

    void setCenter(const VectorType& center)
    {
        mCenter = center;
    }

    void setRadius(T radius)
    {
        mRadius = radius;
    }

private:
    VectorType mCenter;
    T mRadius;
};

typedef Sphere<rio::Vector2f> Sphere2f;
typedef Sphere<rio::Vector3f> Sphere3f;

static_assert(sizeof(Sphere2f) == 0xC, "Sphere<T> size mismatch");
static_assert(sizeof(Sphere3f) == 0x10, "Sphere<T> size mismatch");
