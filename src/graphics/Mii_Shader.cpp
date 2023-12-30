#include <graphics/LightMapMgr.h>
#include <graphics/Mii_Shader.h>
#include <graphics/ModelFFL.h>
#include <graphics/RenderMgr.h>
#include <graphics/ShaderHolder.h>

#include <environment/aglFog.h>
#include <gfx/cafe/seadGraphicsCafe.h>

namespace Mii {

namespace {

static const sead::SafeString s_uniform_name[Shader::cUniform_Num] = {
    "u_proj",
    "u_mv",
    "u_it",
    "u_mode",
    "u_const0",
    "u_const1",
    "u_const2",
    "u_light_enable",
    "u_light_dir",
    "u_light_ambient",
    "u_light_diffuse",
    "u_light_specular",
    "u_material_ambient",
    "u_material_diffuse",
    "u_material_specular",
    "u_material_specular_power",
    "u_material_specular_mode",
    "u_rim_color",
    "u_rim_power",
    "u_specular_mask",
    "u_is_face_mask",
    "u_ex_light_reg_color",
    "u_ex_dark_reg_color",
    "u_lightmap_enable",
    "u_fog_color",
    "u_fog_start",
    "u_fog_start_end_inv",
    "u_fog_dir"
};

static const sead::SafeString s_sampler_name[Shader::cSampler_Num] = {
    "s_texture",
    "s_lightmap_01p",
    "s_lightmap_02p"
};

static const sead::SafeString s_attrib_name[FFL_ATTRIBUTE_BUFFER_TYPE_MAX] = {
    "a_position",
    "a_texCoord",
    "a_normal",
    "a_tangent",
    "a_color"
};

static const sead::Vector3f cLightDir(0.0f, 0.0f, 1.0f);

static const FFLColor cLightAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
static const FFLColor cLightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
static const FFLColor cLightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };

static const FFLColor cMaterialAmbient = { 0.2f, 0.2f, 0.2f, 1.0f };
static const FFLColor cMaterialDiffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
static const FFLColor cMaterialSpecular = { 0.0f, 0.0f, 0.0f, 0.0f };

static const FFLColor cHairSpecular = { 1.0f, 1.0f, 1.0f, 0.0f };

const sead::Vector4f& getColorUniform(const FFLColor& color);

}

Shader::Shader()
    : mpShaderProgram(nullptr)
    , mpModel(nullptr)
{
}

Shader::~Shader()
{
}

void Shader::initializeShader(agl::ShaderProgramArchive* p_archive, sead::Heap* heap)
{
    s32 program_index = p_archive->searchShaderProgramIndex("mii_custom_shader");
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

    p->createUniform(cUniform_Num, heap);
    for (s32 j = 0; j < cUniform_Num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(cSampler_Num, heap);
    for (s32 j = 0; j < cSampler_Num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);

    p->createAttribute(FFL_ATTRIBUTE_BUFFER_TYPE_MAX, heap);
    for (s32 j = 0; j < FFL_ATTRIBUTE_BUFFER_TYPE_MAX; j++)
        p->setAttributeName(j, s_attrib_name[j]);
}

void Shader::initialize(sead::Heap* heap)
{
    mpShaderArchive = ShaderHolder::instance()->getShaderArchive("mii_custom_shader");
    s32 index = mpShaderArchive->searchShaderProgramIndex("mii_custom_shader");
    mpShaderProgram = mpShaderArchive->searchShaderProgram(index);

    mAttribute.allocBuffer(FFL_ATTRIBUTE_BUFFER_TYPE_MAX, heap);

    GX2InitAttribStream(
        &(mAttribute[FFL_ATTRIBUTE_BUFFER_TYPE_POSITION]),
        mpShaderProgram->getAttributeLocationValidate(FFL_ATTRIBUTE_BUFFER_TYPE_POSITION).getVertexLocation(),
        FFL_ATTRIBUTE_BUFFER_TYPE_POSITION,
        0,
        GX2_ATTRIB_FORMAT_32_32_32_FLOAT
    );
    GX2InitAttribStream(
        &(mAttribute[FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD]),
        mpShaderProgram->getAttributeLocationValidate(FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD).getVertexLocation(),
        FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD,
        0,
        GX2_ATTRIB_FORMAT_32_32_FLOAT
    );
    GX2InitAttribStream(
        &(mAttribute[FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL]),
        mpShaderProgram->getAttributeLocationValidate(FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL).getVertexLocation(),
        FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL,
        0,
        GX2_ATTRIB_FORMAT_10_10_10_2_SNORM
    );
    GX2InitAttribStream(
        &(mAttribute[FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT]),
        mpShaderProgram->getAttributeLocationValidate(FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT).getVertexLocation(),
        FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT,
        0,
        GX2_ATTRIB_FORMAT_8_8_8_8_SNORM
    );
    GX2InitAttribStream(
        &(mAttribute[FFL_ATTRIBUTE_BUFFER_TYPE_COLOR]),
        mpShaderProgram->getAttributeLocationValidate(FFL_ATTRIBUTE_BUFFER_TYPE_COLOR).getVertexLocation(),
        FFL_ATTRIBUTE_BUFFER_TYPE_COLOR,
        0,
        GX2_ATTRIB_FORMAT_8_8_8_8_UNORM
    );

    u32 size = GX2CalcFetchShaderSize(FFL_ATTRIBUTE_BUFFER_TYPE_MAX);
    u8* buffer = new (heap, GX2_SHADER_ALIGNMENT) u8[size];
    GX2InitFetchShader(&mFetchShader, buffer, FFL_ATTRIBUTE_BUFFER_TYPE_MAX, mAttribute.getBufferPtr());

    GX2InitSampler(&mSampler, GX2_TEX_CLAMP_MIRROR, GX2_TEX_XY_FILTER_BILINEAR);

    initializeParam_();

    mCallback.pObj = this;
    mCallback.pContextState = sead::GraphicsCafe::instance()->getGX2ContextState();
    mCallback.pDrawFunc = &Shader::drawCallback_;
    mCallback.pSetMatrixFunc = &Shader::setMatrixCallback_;
}

void Shader::setCallback() const
{
    FFLSetShaderCallback(&mCallback);
}

void Shader::activate() const
{
    mpShaderProgram->activate();
    GX2SetFetchShader(&mFetchShader);
}

void Shader::setViewUniform(const sead::Matrix34f& model_mtx, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx) const
{
    sead::Matrix34f mv;
    mv.setMul(view_mtx, model_mtx);
    sead::Matrix44f mv44(mv);

    const agl::UniformLocation& mv_location = mpShaderProgram->getUniformLocation(cUniform_MV);

    sead::Matrix44f mv44T;
    mv44T.setTranspose(mv44);
    mv_location.setMtx44(mv44T.a);

    const agl::UniformLocation& proj_location = mpShaderProgram->getUniformLocation(cUniform_Proj);

    sead::Matrix44f proj44T;
    proj44T.setTranspose(proj_mtx);
    proj_location.setMtx44(proj44T.a);

    mv44.setInverse(mv44);
    sead::Matrix34f it(mv44);

    mpShaderProgram->getUniformLocation(cUniform_IT).setMtx43(it.a);
}

void Shader::setExRegColorUniform(const sead::Color4f* p_color) const
{
    mpShaderProgram->getUniformLocation(cUniform_ExLightRegColor).setVec4(p_color[0]);
    mpShaderProgram->getUniformLocation(cUniform_ExDarkRegColor).setVec4(p_color[1]);
}

void Shader::setLightmapEnableUniform(bool enable) const
{
    mpShaderProgram->getUniformLocation(cUniform_LightmapEnable).setBool(enable);
}

void Shader::setFogUniform(RenderMgr* p_render_mgr) const
{
    const agl::env::Fog* p_fog = p_render_mgr->getEnvObjMgr().getEnvObj<agl::env::Fog>(1);
    if (p_fog != nullptr)
    {
        const sead::Color4f& color = p_fog->getColor();
        mpShaderProgram->getUniformLocation(cUniform_FogColor).setVec4(color);

        f32 start = p_fog->getStart();
        mpShaderProgram->getUniformLocation(cUniform_FogStart).setFloat(start);

        f32 start_end_inv = p_fog->getStartEndInv();
        mpShaderProgram->getUniformLocation(cUniform_FogStartEndInv).setFloat(start_end_inv);

        const sead::Vector3f& dir = p_fog->getDirection();
        mpShaderProgram->getUniformLocation(cUniform_FogDir).setVec3(dir);
    }
    else
    {
        // Color who?

        mpShaderProgram->getUniformLocation(cUniform_FogStart).setFloat(1000000.0f);

        mpShaderProgram->getUniformLocation(cUniform_FogStartEndInv).setFloat(1000000.0f);

        sead::Vector3f dir = sead::Vector3f(-sead::Vector3f::ez.x, -sead::Vector3f::ez.y, -sead::Vector3f::ez.z);   // TODO: sead::Vector3f::operator-
        mpShaderProgram->getUniformLocation(cUniform_FogDir).setVec3(dir);
    }
}

void Shader::setCulling(FFLCullMode mode)
{
    switch (mode)
    {
    case FFL_CULL_MODE_NONE:
        GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_DISABLE);
        break;
    case FFL_CULL_MODE_BACK:
        GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_ENABLE);
        break;
    case FFL_CULL_MODE_FRONT:
        GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_ENABLE, GX2_DISABLE);
        break;
    }
}

void Shader::initializeParam_()
{
    mLightParam.enable = true;
    mLightParam.dir.set(cLightDir);
    mLightParam.ambient = cLightAmbient;
    mLightParam.diffuse = cLightDiffuse;
    mLightParam.specular = cLightSpecular;

    for (s32 i = 0; i < FFL_MODULATE_TYPE_SHAPE_MAX; i++)
    {
        mMaterial[i].ambient = cMaterialAmbient;
        mMaterial[i].diffuse = cMaterialDiffuse;
        mMaterial[i].specular = cMaterialSpecular;
        mMaterial[i].specular_power = 0.0f;
        mMaterial[i].specular_mode = 0;
    }

    mRimParam.color_r = 0;
    mRimParam.color_g = 0;
    mRimParam.color_b = 0;
    mRimParam.color_a = 0;
    mRimParam.power = 10.0f;

    mSpecularParam.mask = 0.5f;
    mSpecularParam.hair_specular = cHairSpecular;
}

void Shader::setLightUniform_() const
{
    mpShaderProgram->getUniformLocation(cUniform_LightEnable).setBool(mLightParam.enable);
    mpShaderProgram->getUniformLocation(cUniform_LightDir).setVec3(mLightParam.dir);
    mpShaderProgram->getUniformLocation(cUniform_LightAmbient).setVec4(getColorUniform(mLightParam.ambient));
    mpShaderProgram->getUniformLocation(cUniform_LightDiffuse).setVec4(getColorUniform(mLightParam.diffuse));
    mpShaderProgram->getUniformLocation(cUniform_LightSpecular).setVec4(getColorUniform(mLightParam.specular));
}

void Shader::setMaterialUniform_(const FFLDrawParam& draw_param) const
{
    FFLModulateType type = draw_param.modulateParam.type;
    if (type >= FFL_MODULATE_TYPE_SHAPE_MAX)
        return;

    FFLColor specular;
    specular.r = mMaterial[type].specular.r;
    specular.g = mMaterial[type].specular.g;
    specular.b = mMaterial[type].specular.b;
    specular.a = mMaterial[type].specular.a;
    if (type == FFL_MODULATE_TYPE_SHAPE_HAIR)
    {
        specular.r *= mSpecularParam.hair_specular.r;
        specular.g *= mSpecularParam.hair_specular.g;
        specular.b *= mSpecularParam.hair_specular.b;
        specular.a *= mSpecularParam.hair_specular.a;
    }

    mpShaderProgram->getUniformLocation(cUniform_MaterialAmbient).setVec4(getColorUniform(mMaterial[type].ambient));
    mpShaderProgram->getUniformLocation(cUniform_MaterialDiffuse).setVec4(getColorUniform(mMaterial[type].diffuse));
    mpShaderProgram->getUniformLocation(cUniform_MaterialSpecular).setVec4(getColorUniform(specular));
    mpShaderProgram->getUniformLocation(cUniform_MaterialSpecularPower).setFloat(mMaterial[type].specular_power);
    mpShaderProgram->getUniformLocation(cUniform_MaterialSpecularMode).setInt(draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT].ptr ? mMaterial[type].specular_mode : 0);
    mpShaderProgram->getUniformLocation(cUniform_IsFaceMask).setBool(type == FFL_MODULATE_TYPE_SHAPE_MASK);
    mpShaderProgram->getUniformLocation(cUniform_SpecularMask).setFloat(mSpecularParam.mask);
}

void Shader::setRimUniform_() const
{
    mpShaderProgram->getUniformLocation(cUniform_RimColor).setVec4(getColorUniform(mRimParam.color));
    mpShaderProgram->getUniformLocation(cUniform_MaterialSpecularPower).setFloat(mRimParam.power);       // Nintendo set cUniform_MaterialSpecularPower instead of cUniform_RimPower
}

void Shader::draw_(const FFLDrawParam& draw_param)
{
    setCulling(draw_param.cullMode);

    mpShaderProgram->getUniformLocation(cUniform_Mode).setInt(draw_param.modulateParam.mode);

    switch (draw_param.modulateParam.mode)
    {
    case FFL_MODULATE_MODE_0:
    case FFL_MODULATE_MODE_3:
    case FFL_MODULATE_MODE_4:
    case FFL_MODULATE_MODE_5:
        mpShaderProgram->getUniformLocation(cUniform_Const0).setVec4(getColorUniform(*draw_param.modulateParam.pColorR));
        break;
    case FFL_MODULATE_MODE_2:
        mpShaderProgram->getUniformLocation(cUniform_Const0).setVec4(getColorUniform(*draw_param.modulateParam.pColorR));
        mpShaderProgram->getUniformLocation(cUniform_Const1).setVec4(getColorUniform(*draw_param.modulateParam.pColorG));
        mpShaderProgram->getUniformLocation(cUniform_Const2).setVec4(getColorUniform(*draw_param.modulateParam.pColorB));
        break;
    }

    setMaterialUniform_(draw_param);
    setLightUniform_();
    setRimUniform_();

    if (draw_param.modulateParam.pGX2Texture != nullptr)
    {
        const agl::SamplerLocation& location = mpShaderProgram->getSamplerLocationValidate(cSampler_Texture);
        if (location.getVertexLocation() != -1)
        {
            GX2SetVertexTexture(draw_param.modulateParam.pGX2Texture, location.getVertexLocation());
            GX2SetVertexSampler(&mSampler, location.getVertexLocation());
        }
        if (location.getFragmentLocation() != -1)
        {
            GX2SetPixelTexture(draw_param.modulateParam.pGX2Texture, location.getFragmentLocation());
            GX2SetPixelSampler(&mSampler, location.getFragmentLocation());
        }
    }

    s32 lightmap_index = 4;
    if (mpModel != nullptr && mpModel->getLightMapType() == ModelFFL::cLightmapType_LightMapMgr_Index_0)
        lightmap_index = 0;

    LightMapMgr::instance()->getLightmap01p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap01p));

    if (mpModel != nullptr)
    {
        switch (mpModel->getLightmap02pType())
        {
        case ModelFFL::cLightmap02pType_0:
            mLightmap02p_0.applyTextureData(*mpModel->getLightmap02p_0());
            mLightmap02p_0.activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p));
            break;
        case ModelFFL::cLightmap02pType_1:
            mLightmap02p_1.applyTextureData(*mpModel->getLightmap02p_1());
            mLightmap02p_1.activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p));
            break;
        default:
            LightMapMgr::instance()->getLightmap02p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p));
            break;
        }
    }
    else
    {
        LightMapMgr::instance()->getLightmap02p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p));
    }

    if (draw_param.primitiveParam.pIndexBuffer != nullptr)
    {
        GX2SetAttribBuffer(
            FFL_ATTRIBUTE_BUFFER_TYPE_POSITION,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_POSITION].size,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_POSITION].stride,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_POSITION].ptr
        );
        GX2SetAttribBuffer(
            FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD].size,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD].stride,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD].ptr
        );
        GX2SetAttribBuffer(
            FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL].size,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL].stride,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL].ptr
        );
        GX2SetAttribBuffer(
            FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT].size,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT].stride,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT].ptr
        );
        GX2SetAttribBuffer(
            FFL_ATTRIBUTE_BUFFER_TYPE_COLOR,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_COLOR].size,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_COLOR].stride,
            draw_param.attributeBufferParam.attributeBuffers[FFL_ATTRIBUTE_BUFFER_TYPE_COLOR].ptr
        );

        GX2DrawIndexed(
            draw_param.primitiveParam.primitiveType,
            draw_param.primitiveParam.indexCount,
            draw_param.primitiveParam.indexFormat,
            draw_param.primitiveParam.pIndexBuffer
        );
    }
}

void Shader::drawCallback_(void* p_obj, const FFLDrawParam& draw_param)
{
    static_cast<Shader*>(p_obj)->draw_(draw_param);
}

void Shader::setMatrix_(const Mat44& matrix)
{
    Mat44 ident44;
    MAT44Identity(&ident44);

    mpShaderProgram->getUniformLocationValidate(cUniform_MV).setMtx44(ident44.a);

    mpShaderProgram->getUniformLocationValidate(cUniform_IT).setMtx43(ident44.a);

    Mat44 proj;
    MAT44Transpose(&matrix, &proj);

    mpShaderProgram->getUniformLocationValidate(cUniform_Proj).setMtx44(proj.a);
}

void Shader::setMatrixCallback_(void* p_obj, const Mat44& matrix)
{
    static_cast<Shader*>(p_obj)->setMatrix_(matrix);
}

namespace {

const sead::Vector4f& getColorUniform(const FFLColor& color)
{
    return reinterpret_cast<const sead::Vector4f&>(color.r);
}

}

}
