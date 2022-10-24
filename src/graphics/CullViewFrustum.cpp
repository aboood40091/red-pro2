#include <graphics/CullViewFrustum.h>

#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <math/seadMatrix.h>

void CullViewFrustum::update(const sead::Camera& camera, const sead::PerspectiveProjection& projection)
{
    sead::Matrix34f inv_view_mtx;
    inv_view_mtx.setInverse(camera.getViewMatrix());

    mViewVolume.SetFrustum(
        projection.getTop(), projection.getBottom(),
        projection.getLeft(), projection.getRight(),
        projection.getNear(), projection.getFar(),
        reinterpret_cast<const nw::g3d::math::Mtx34&>(inv_view_mtx)
    );

    sead::Matrix34f billboard_mtx;
    billboard_mtx.setTranspose(camera.getViewMatrix());

    billboard_mtx.m[0][3] = -(billboard_mtx.m[0][0] * camera.getViewMatrix()(0, 3) +
                              billboard_mtx.m[0][1] * camera.getViewMatrix()(1, 3) +
                              billboard_mtx.m[0][2] * camera.getViewMatrix()(2, 3));

    billboard_mtx.m[1][3] = -(billboard_mtx.m[1][0] * camera.getViewMatrix()(0, 3) +
                              billboard_mtx.m[1][1] * camera.getViewMatrix()(1, 3) +
                              billboard_mtx.m[1][2] * camera.getViewMatrix()(2, 3));

    billboard_mtx.m[2][3] = -(billboard_mtx.m[2][0] * camera.getViewMatrix()(0, 3) +
                              billboard_mtx.m[2][1] * camera.getViewMatrix()(1, 3) +
                              billboard_mtx.m[2][2] * camera.getViewMatrix()(2, 3));

    sead::Vector3f col_2;
    billboard_mtx.getBase(col_2, 2);
    col_2.x *= -1;
    col_2.y *= -1;
    col_2.z *= -1;
    billboard_mtx.setBase(2, col_2);

    sead::Vector3f pos;
    billboard_mtx.getTranslation(pos);

    f32 fovy_tan = sead::Mathf::tan(projection.getFovy() * 0.5f);
    f32 fovx_tan = projection.getAspect() * fovy_tan;

    sead::Vector3f v0[4];

    v0[2].z = fovy_tan + fovy_tan * projection.getOffset().y * 2;
    f32 v1 = sead::Mathf::sqrt(sead::Mathf::square(v0[2].z) + 1.0f);
    f32 inv_v1 = 1.0f / v1;
    v0[2].y = -inv_v1;
    v0[2].z *= inv_v1;

    v0[3].z = fovy_tan - fovy_tan * projection.getOffset().y * 2;
    f32 v2 = sead::Mathf::sqrt(sead::Mathf::square(v0[3].z) + 1.0f);
    f32 inv_v2 = 1.0f / v2;
    v0[3].y =  inv_v2;
    v0[3].z *= inv_v2;

    v0[1].z = fovx_tan - fovx_tan * projection.getOffset().x * 2;
    f32 v3 = sead::Mathf::sqrt(sead::Mathf::square(v0[1].z) + 1.0f);
    f32 inv_v3 = 1.0f / v3;
    v0[1].x =  inv_v3;
    v0[1].z *= inv_v3;

    v0[0].z = fovx_tan + fovx_tan * projection.getOffset().x * 2;
    f32 v4 = sead::Mathf::sqrt(sead::Mathf::square(v0[0].z) + 1.0f);
    f32 inv_v4 = 1.0f / v4;
    v0[0].x = -inv_v4;
    v0[0].z *= inv_v4;

    v0[0].y = 0.0f;
    v0[1].y = 0.0f;
    v0[2].x = 0.0f;
    v0[3].x = 0.0f;

    billboard_mtx.setTranslation(0.0f, 0.0f, 0.0f);

    for (s32 i = 0; i < 4; i++)
    {
        v0[i].setMul(billboard_mtx, v0[i]);
        _0[i]._0 = v0[i];
        _0[i]._c = _0[i]._0.dot(pos);
    }
}
