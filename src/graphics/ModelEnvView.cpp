#include <graphics/ModelEnvView.h>

#include <gfx/rio_Color.h>

const ModelEnvView::Member ModelEnvView::cMember[] = {
    { agl::UniformBlock::cType_vec4,    3 },            // vec4     cView[ 3 ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     cViewProj[ 4 ];
    { agl::UniformBlock::cType_vec3,    cLightObjMax }, // vec3     cLightDiffDir[ LIGHT_OBJ_MAX ];
    { agl::UniformBlock::cType_vec4,    cLightObjMax }, // vec4     cLightDiffColor[ LIGHT_OBJ_MAX ];
    { agl::UniformBlock::cType_vec4,    cChannelMax },  // vec4     cAmbColor[ CHANNEL_MAX ];
    { agl::UniformBlock::cType_vec3,    cFogMax },      // vec3     cFogColor[ FOG_MAX ];
    { agl::UniformBlock::cType_float,   cFogMax },      // float    cFogStart[ FOG_MAX ];
    { agl::UniformBlock::cType_float,   cFogMax },      // float    cFogStartEndInv[ FOG_MAX ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     ??? [ 4 ];
    { agl::UniformBlock::cType_vec3,    cFogMax },      // vec3     ??? [ FOG_MAX ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     ??? [ 4 ];
};

ModelEnvView::ModelEnvView(u32 view_num)
{
    mUniformBlock.allocBuffer(view_num);
    for (Buffer<agl::UniformBlock>::iterator itr = mUniformBlock.begin(), itr_end = mUniformBlock.end(); itr != itr_end; ++itr)
    {
        if (itr.getIndex() == 0)
        {
            itr->startDeclare(cMemberNum);
            for (s32 i = 0; i < cMemberNum; i++)
                itr->declare(cMember[i].type, cMember[i].num);
        }
        else
        {
            itr->declare(*mUniformBlock.getBufferPtr());
        }

        itr->create();
    }
}

ModelEnvView::~ModelEnvView()
{
    mUniformBlock.freeBuffer();
}

void ModelEnvView::setUniformData(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx)
{
    agl::UniformBlock& uniform_block = mUniformBlock[view_index];

    uniform_block.dcbz();

    rio::Matrix44f vp_mtx;
    vp_mtx.setMul(proj_mtx, view_mtx);

    uniform_block.setVector4f(
        cMemberIndex_View,
        &static_cast<const rio::Vector4f&>(view_mtx.v[0]),
        3
    );

    uniform_block.setVector4f(
        cMemberIndex_ViewProj,
        &static_cast<const rio::Vector4f&>(vp_mtx.v[0]),
        4
    );

    // TODO

    uniform_block.setVector4f(
        cMemberIndex_Unk_8,
        &static_cast<const rio::Vector4f&>(rio::Matrix44f::ident.v[0]),
        4
    );

    for (s32 i = 0; i < cLightObjMax; i++)
    {
        uniform_block.setVector4f(
            cMemberIndex_LightDiffColor,
            static_cast<const rio::Vector4f&>(rio::Color4f::cBlack.v),
            i
        );
    }

    for (s32 i = 0; i < cChannelMax; i++)
    {
        uniform_block.setVector4f(
            cMemberIndex_AmbColor,
            static_cast<const rio::Vector4f&>(rio::Color4f::cBlack.v),
            i
        );
    }

    for (s32 i = 0; i < cFogMax; i++)
    {
        uniform_block.setFloat(
            cMemberIndex_FogStart,
            1000000.0f,
            i
        );

        uniform_block.setFloat(
            cMemberIndex_FogStartEndInv,
            1000000.0f,
            i
        );

        const rio::Vector3f n_ez{ 0.0f, 0.0f, -1.0f };

        uniform_block.setVector3f(
            cMemberIndex_Unk_9,
            n_ez,
            i
        );
    }

    uniform_block.flush(false);
}
