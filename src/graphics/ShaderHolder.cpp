#include <graphics/DynamicLightRenderer.h>
#include <graphics/Mii_IconFaceline.h>
#include <graphics/Mii_Shader.h>
#include <graphics/MosaicFilter.h>
#include <graphics/ShaderHolder.h>
#include <graphics/TexQuadMgr.h>
#include <map/BgRenderer.h>
#include <map/LightMaskRenderer.h>
#include <system/ResMgr.h>

#include <gfx/seadGraphics.h>

SEAD_SINGLETON_DISPOSER_IMPL(ShaderHolder)

ShaderHolder::ShaderHolder()
{
}

void ShaderHolder::initialize(sead::Heap* heap)
{
    ResMgr::instance()->loadArchiveRes("shaderfb", "shader/shaderfb.szs", heap, true);

    // bg_renderer
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("bg_renderer", heap);
        BgRenderer::initializeShader(p_archive, heap);
        pushBackShaderArchive_("bg_renderer", p_archive, heap);
    }
    // dynamic_light_renderer
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("dynamic_light_renderer", heap);
        DynamicLightRenderer::initializeShader(p_archive, heap);
        pushBackShaderArchive_("dynamic_light_renderer", p_archive, heap);
    }
    // light_mask_shader
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("light_mask_shader", heap);
        LightMaskRenderer::initializeShader(p_archive, heap);
        pushBackShaderArchive_("light_mask_shader", p_archive, heap);
    }
    // nw4f_cs_shader
    {
        createAndPushBackShaderArchive_("nw4f_cs_shader", heap);
    }
    // nw4f_cs_water_shader
    {
        createAndPushBackShaderArchive_("nw4f_cs_water_shader", heap);
    }
    // nw4f_dv_shader
    {
        createAndPushBackShaderArchive_("nw4f_dv_shader", heap);
    }
    // nw4f_koopa_shader
    {
        createAndPushBackShaderArchive_("nw4f_koopa_shader", heap);
    }
    // nw4f_shader
    {
        createAndPushBackShaderArchive_("nw4f_shader", heap);
    }
    // quad_cloud_shader
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("quad_cloud_shader", heap);
        TexQuadMgr::initializeShader(p_archive, heap);
        pushBackShaderArchive_("quad_cloud_shader", p_archive, heap);
    }
    // mii_custom_shader
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("mii_custom_shader", heap);
        Mii::Shader::initialize(p_archive, heap);
        pushBackShaderArchive_("mii_custom_shader", p_archive, heap);
    }
    // mii_icon_faceline_shader
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("mii_icon_faceline_shader", heap);
        Mii::IconFaceline::initializeShader(p_archive, heap);
        pushBackShaderArchive_("mii_icon_faceline_shader", p_archive, heap);
    }
    // mosaic_filter
    {
        agl::ShaderProgramArchive* p_archive = createShaderArchive_("mosaic_filter", heap);
        MosaicFilter::initializeShader(p_archive, heap);
        pushBackShaderArchive_("mosaic_filter", p_archive, heap);
    }
}

agl::ShaderProgramArchive* ShaderHolder::createShaderArchive_(const sead::SafeString& filename, sead::Heap* heap) const
{
    const agl::ResBinaryShaderArchiveData* res_binary_shader_archive = static_cast<agl::ResBinaryShaderArchiveData*>(
        ResMgr::instance()->getFileFromArchiveRes(
            "shaderfb", sead::FormatFixedSafeString<48>("%s.sharcfb", filename.cstr())
        )
    );

    agl::ShaderProgramArchive* p_archive = new (heap) agl::ShaderProgramArchive();
    p_archive->createWithOption(res_binary_shader_archive, nullptr, 2, heap);
    return p_archive;
}

void ShaderHolder::pushBackShaderArchive_(const sead::SafeString& filename, agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    sead::Graphics::instance()->lockDrawContext();
    {
        p_archive->setUp();
    }
    sead::Graphics::instance()->unlockDrawContext();

    mShaderArchiveTreeMap.insert(filename, p_archive);
}

void ShaderHolder::createAndPushBackShaderArchive_(const sead::SafeString& filename, sead::Heap* heap)
{
    agl::ShaderProgramArchive* p_archive = createShaderArchive_(filename, heap);
    pushBackShaderArchive_(filename, p_archive, heap);
}

const agl::ShaderProgramArchive* ShaderHolder::getShaderArchive(const sead::SafeString& filename) const
{
    agl::ShaderProgramArchive** pp_archive = mShaderArchiveTreeMap.find(filename);
    if (!pp_archive)
        return nullptr;

    return *pp_archive;
}

const agl::ShaderProgramArchive* ShaderHolder::getNw4fShaderArchive() const
{
    return getShaderArchive("nw4f_shader");
}

const agl::ShaderProgram* ShaderHolder::getNw4fBasicShaderProgram() const
{
    const agl::ShaderProgramArchive* p_archive = getNw4fShaderArchive();
    return p_archive->searchShaderProgram("nw4f_basic_shader");
}
