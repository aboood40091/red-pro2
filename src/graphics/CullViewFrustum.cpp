#include <graphics/CullViewFrustum.h>

#include <gfx/rio_Camera.h>
#include <gfx/rio_Projection.h>
#include <math/rio_Matrix.h>

CullViewFrustum::CullViewFrustum()
{
}

namespace {

static inline void C_MTXMultVec(const rio::BaseMtx34f& m, const rio::BaseVec3f& src, rio::BaseVec3f* dst)
{
    RIO_ASSERT(dst != nullptr);

    rio::BaseVec3f tmp = {
        m.m[0][0] * src.x + m.m[0][1] * src.y + m.m[0][2] * src.z + m.m[0][3],
        m.m[1][0] * src.x + m.m[1][1] * src.y + m.m[1][2] * src.z + m.m[1][3],
        m.m[2][0] * src.x + m.m[2][1] * src.y + m.m[2][2] * src.z + m.m[2][3]
    };

    *dst = tmp;
}

}

void CullViewFrustum::update(const rio::Camera& camera, const rio::PerspectiveProjection& projection)
{
    rio::Matrix34f view_mtx;
    camera.getMatrix(&view_mtx);

    rio::Matrix34f inv_view_mtx;
    inv_view_mtx.setInverse(view_mtx);

    mViewVolume.SetFrustum(
        projection.getTop(), projection.getBottom(),
        projection.getLeft(), projection.getRight(),
        projection.getNear(), projection.getFar(),
        *nw::g3d::math::Mtx34::Cast(inv_view_mtx.a)
    );

    rio::Matrix34f billboard_mtx;
    billboard_mtx.setTranspose(view_mtx);

    billboard_mtx.m[0][3] = -(billboard_mtx.m[0][0] * view_mtx.m[0][3] +
                              billboard_mtx.m[0][1] * view_mtx.m[1][3] +
                              billboard_mtx.m[0][2] * view_mtx.m[2][3]);

    billboard_mtx.m[1][3] = -(billboard_mtx.m[1][0] * view_mtx.m[0][3] +
                              billboard_mtx.m[1][1] * view_mtx.m[1][3] +
                              billboard_mtx.m[1][2] * view_mtx.m[2][3]);

    billboard_mtx.m[2][3] = -(billboard_mtx.m[2][0] * view_mtx.m[0][3] +
                              billboard_mtx.m[2][1] * view_mtx.m[1][3] +
                              billboard_mtx.m[2][2] * view_mtx.m[2][3]);

    billboard_mtx.m[0][2] *= -1;
    billboard_mtx.m[1][2] *= -1;
    billboard_mtx.m[2][2] *= -1;

    rio::Vector3f pos = {
        billboard_mtx.m[0][3],
        billboard_mtx.m[1][3],
        billboard_mtx.m[2][3]
    };

    f32 fovy_tan = std::tan(projection.fovy() * 0.5f);
    f32 fovx_tan = projection.aspect() * fovy_tan;

    rio::Vector3f v0[4];

    v0[2].z = fovy_tan + fovy_tan * projection.offset().y * 2;
    f32 v1 = rio::Mathf::sqrt(rio::Mathf::square(v0[2].z) + 1.0f);
    f32 inv_v1 = 1.0f / v1;
    v0[2].y = -inv_v1;
    v0[2].z *= inv_v1;

    v0[3].z = fovy_tan - fovy_tan * projection.offset().y * 2;
    f32 v2 = rio::Mathf::sqrt(rio::Mathf::square(v0[3].z) + 1.0f);
    f32 inv_v2 = 1.0f / v2;
    v0[3].y =  inv_v2;
    v0[3].z *= inv_v2;

    v0[1].z = fovx_tan - fovx_tan * projection.offset().x * 2;
    f32 v3 = rio::Mathf::sqrt(rio::Mathf::square(v0[1].z) + 1.0f);
    f32 inv_v3 = 1.0f / v3;
    v0[1].x =  inv_v3;
    v0[1].z *= inv_v3;

    v0[0].z = fovx_tan + fovx_tan * projection.offset().x * 2;
    f32 v4 = rio::Mathf::sqrt(rio::Mathf::square(v0[0].z) + 1.0f);
    f32 inv_v4 = 1.0f / v4;
    v0[0].x = -inv_v4;
    v0[0].z *= inv_v4;

    v0[0].y = 0.0f;
    v0[1].y = 0.0f;
    v0[2].x = 0.0f;
    v0[3].x = 0.0f;

    billboard_mtx.m[0][3] = 0.0f;
    billboard_mtx.m[1][3] = 0.0f;
    billboard_mtx.m[2][3] = 0.0f;

    for (s32 i = 0; i < 4; i++)
    {
        C_MTXMultVec(billboard_mtx, v0[i], &(v0[i]));
        _0[i]._0 = v0[i];
        _0[i]._c = _0[i]._0.dot(pos);
    }
}
