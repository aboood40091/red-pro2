#include <graphics/Mii_CentralMgr.h>
#include <graphics/Mii_IconFacelineObj.h>
#include <graphics/Mii_IconRenderBuffer.h>

#include <gfx/seadGraphicsContext.h>

namespace Mii {

IconFacelineObj::IconFacelineObj()
    : _398(0)
    , _39c(0)
{
    clearVertex_();
}

void IconFacelineObj::calc()
{
}

void IconFacelineObj::updateView(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void IconFacelineObj::calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void IconFacelineObj::drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
}

void IconFacelineObj::drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    sead::GraphicsContext context;
    context.setDepthEnable(true, false);
    context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    context.setCullingMode(sead::Graphics::cCullingMode_None);
    context.setBlendEnable(true);
    context.setBlendFactorSrcAlpha(sead::Graphics::cBlendFactor_SrcAlpha);
    context.setBlendFactorDstAlpha(sead::Graphics::cBlendFactor_InvSrcAlpha);
    context.setAlphaTestEnable(true);
    context.apply();

    IconFacelineShader& shader = CentralMgr::instance()->getIconFacelineShader();
    shader.activate();

    shader.setViewUniform(view_mtx, proj_mtx, mWorldMtx);

    u32 width = mpRenderBuffer->getInfo().width;
    u32 height = mpRenderBuffer->getInfo().height;

    shader.setResolutionUniform(width, height);
    shader.setLineWidthUniform(width * height > 0x1000 ? 6 : 3);

    shader.activateTexture(mpRenderBuffer->getDepthTexture(), IconFacelineShader::cSampler_Depth);
    shader.activateTexture(mpRenderBuffer->getColorTexture(), IconFacelineShader::cSampler_Color);

    mVertexBuffer.flushCPUCacheNoSync();
    mVertexAttribute.activate();

    mIndexStream.draw(0, 6);
}

bool IconFacelineObj::initialize(const IconRenderBuffer* p_render_buffer)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        setupIndex_();
        setupVertex_();
        mpRenderBuffer = p_render_buffer;
    }
    sead::Graphics::instance()->unlockDrawContext();
    return true;
}

void IconFacelineObj::destroy()
{
}

void IconFacelineObj::setPosition(const sead::Vector3f& position)
{
    mWorldMtx.makeT(position);
    getOrderPos().set(position);
}

void IconFacelineObj::setVertex(const Vertex* p_vertex, u32 num)
{
    if (num >= 4)
    {
        for (u32 i = 0; i < 4; i++)
        {
            mVertex[i].position.set(p_vertex[i].position);
            mVertex[i].tex_coord.set(p_vertex[i].tex_coord);
            mVertex[i].vertex_color.set(p_vertex[i].vertex_color);
        }
    }
}

void IconFacelineObj::clearVertex_()
{
    for (sead::UnsafeArray<Vertex, 4>::iterator itr = mVertex.begin(), itr_end = mVertex.end(); itr != itr_end; ++itr)
    {
        itr->position.set(sead::Vector3f::zero);
        itr->tex_coord.set(sead::Vector2f::zero);
        itr->vertex_color.set(sead::Vector4f::zero);
    }
}

void IconFacelineObj::setupVertex_()
{
    mVertexBuffer.setUpBuffer(mVertex.getBufferPtr(), sizeof(Vertex), 4 * sizeof(Vertex));
    mVertexBuffer.setUpStream(0, agl::cVertexStreamFormat_32_32_32_float,       offsetof(Vertex, position));
    mVertexBuffer.setUpStream(1, agl::cVertexStreamFormat_32_32_float,          offsetof(Vertex, tex_coord));
    mVertexBuffer.setUpStream(2, agl::cVertexStreamFormat_32_32_32_32_float,    offsetof(Vertex, vertex_color));

    mVertexAttribute.create(1);
    mVertexAttribute.setVertexStream(0, &mVertexBuffer, 0);
    mVertexAttribute.setVertexStream(2, &mVertexBuffer, 1);
    mVertexAttribute.setVertexStream(6, &mVertexBuffer, 2);
    mVertexAttribute.setUp();

    mVertexBuffer.flushCPUCacheNoSync();
}

void IconFacelineObj::setupIndex_()
{
    static const u32 cIndex[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    for (s32 i = 0; i < 6; i++)
        mIndex[i] = cIndex[i];

    mIndexStream.setUpStream(mIndex.getBufferPtr(), 6, GX2_PRIMITIVE_TRIANGLES);
}

}
