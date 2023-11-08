//#include <graphics/LightMapMgr.h>
#include <graphics/Mii_Shader.h>
#include <graphics/ModelFFL.h>
#include <graphics/RenderMgr.h>
#include <graphics/ShaderHolder.h>

#include <gfx/rio_Window.h>
#include <gpu/rio_RenderState.h>

namespace Mii {

namespace {

static const char* const s_uniform_name[Shader::cUniform_Num] = {
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

static const char* const s_sampler_name[Shader::cSampler_Num] = {
    "s_texture",
    "s_lightmap_01p",
    "s_lightmap_02p"
};

static const char* const s_attrib_name[FFL_ATTRIBUTE_BUFFER_TYPE_MAX] = {
    "a_position",
    "a_texCoord",
    "a_normal",
    "a_tangent",
    "a_color"
};

static const rio::BaseVec3f cLightDir { 0.0f, 0.0f, 1.0f };

static const FFLColor cLightAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
static const FFLColor cLightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
static const FFLColor cLightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };

static const FFLColor cMaterialAmbient = { 0.2f, 0.2f, 0.2f, 1.0f };
static const FFLColor cMaterialDiffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
static const FFLColor cMaterialSpecular = { 0.0f, 0.0f, 0.0f, 0.0f };

static const FFLColor cHairSpecular = { 1.0f, 1.0f, 1.0f, 0.0f };

const rio::BaseVec4f& getColorUniform(const FFLColor& color);

}

Shader::Shader()
    : mpShaderProgram(nullptr)
#if RIO_IS_CAFE
    , mFetchShader()
#elif RIO_IS_WIN
    , mVBOHandle()
    , mVAOHandle()
#endif
    , mpModel(nullptr)
{
}

Shader::~Shader()
{
#if RIO_IS_CAFE
    if (mFetchShader.shaderPtr != nullptr)
    {
        rio::MemUtil::free(mFetchShader.shaderPtr);
        mFetchShader.shaderPtr = nullptr;
    }

    if (mAttribute.isBufferReady())
        mAttribute.freeBuffer();
#elif RIO_IS_WIN
    if (mVAOHandle != GL_NONE)
    {
        RIO_GL_CALL(glDeleteVertexArrays(1, &mVAOHandle));
        mVAOHandle = GL_NONE;
    }

    if (mVBOHandle[0] != GL_NONE)
    {
        RIO_GL_CALL(glDeleteBuffers(FFL_ATTRIBUTE_BUFFER_TYPE_MAX, mVBOHandle));
        rio::MemUtil::set(mVBOHandle, 0, sizeof(mVBOHandle));
    }
#endif
}

void Shader::initializeShader(agl::ShaderProgramArchive* p_archive)
{
    s32 program_index = p_archive->searchShaderProgramIndex("mii_custom_shader");
    agl::ShaderProgram* p = const_cast<agl::ShaderProgram*>(p_archive->searchShaderProgram(program_index));

    p->createUniform(cUniform_Num);
    for (s32 j = 0; j < cUniform_Num; j++)
        p->setUniformName(j, s_uniform_name[j]);

    p->createSamplerLocation(cSampler_Num);
    for (s32 j = 0; j < cSampler_Num; j++)
        p->setSamplerLocationName(j, s_sampler_name[j]);

    p->createAttribute(FFL_ATTRIBUTE_BUFFER_TYPE_MAX);
    for (s32 j = 0; j < FFL_ATTRIBUTE_BUFFER_TYPE_MAX; j++)
        p->setAttributeName(j, s_attrib_name[j]);
}

void Shader::initialize()
{
    mpShaderArchive = ShaderHolder::instance()->getShaderArchive("mii_custom_shader");
    s32 index = mpShaderArchive->searchShaderProgramIndex("mii_custom_shader");
    mpShaderProgram = mpShaderArchive->searchShaderProgram(index);

#if RIO_IS_CAFE
    mAttribute.allocBuffer(FFL_ATTRIBUTE_BUFFER_TYPE_MAX);

    for (u32 i = 0; i < FFL_ATTRIBUTE_BUFFER_TYPE_MAX; i++)
    {
        RIO_LOG("Attribute (%s) location (%d)\n", mpShaderProgram->getAttributeLocationValidate(i).getName(), mpShaderProgram->getAttributeLocationValidate(i).getVertexLocation());
    }

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
    void* buffer = rio::MemUtil::alloc(size, GX2_SHADER_ALIGNMENT);
    GX2InitFetchShader(&mFetchShader, buffer, FFL_ATTRIBUTE_BUFFER_TYPE_MAX, mAttribute.getBufferPtr());
#elif RIO_IS_WIN
    RIO_GL_CALL(glCreateBuffers(FFL_ATTRIBUTE_BUFFER_TYPE_MAX, mVBOHandle));

    for (u32 i = 0; i < FFL_ATTRIBUTE_BUFFER_TYPE_MAX; i++)
    {
        mAttributeLocation[i] = mpShaderProgram->getAttributeLocationValidate(i).getVertexLocation();
        RIO_LOG("Attribute (%s) location (%d)\n", mpShaderProgram->getAttributeLocationValidate(i).getName(), mAttributeLocation[i]);
    }

    RIO_ASSERT(mVAOHandle == GL_NONE);
    RIO_GL_CALL(glCreateVertexArrays(1, &mVAOHandle));
    RIO_ASSERT(mVAOHandle != GL_NONE);
#endif

    mSampler.setWrap(rio::TEX_WRAP_MODE_MIRROR, rio::TEX_WRAP_MODE_MIRROR, rio::TEX_WRAP_MODE_MIRROR);
  //mSampler.setFilterMin(rio::TEX_XY_FILTER_MODE_LINEAR); // <-- Already set
  //mSampler.setFilterMag(rio::TEX_XY_FILTER_MODE_LINEAR); // ^^^

    initializeParam_();

    mCallback.pObj = this;
#if RIO_IS_CAFE
  //mCallback.pContextState = rio::Window::instance()->getNativeWindow().getContextState();
#endif // RIO_IS_CAFE
    mCallback.pApplyAlphaTestFunc = &Shader::applyAlphaTestCallback_;
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
#if RIO_IS_CAFE
    GX2SetFetchShader(&mFetchShader);
#elif RIO_IS_WIN
    RIO_GL_CALL(glBindVertexArray(mVAOHandle));
    for (u32 i = 0; i < FFL_ATTRIBUTE_BUFFER_TYPE_MAX; i++)
        RIO_GL_CALL(glDisableVertexAttribArray(i));
#endif
}

void Shader::setViewUniform(const rio::BaseMtx34f& model_mtx, const rio::BaseMtx34f& view_mtx, const rio::BaseMtx44f& proj_mtx) const
{
    rio::Matrix34f mv;
    mv.setMul(static_cast<const rio::Matrix34f&>(view_mtx), static_cast<const rio::Matrix34f&>(model_mtx));
    rio::Matrix44f mv44;
    mv44.fromMatrix34(mv);

    const agl::UniformLocation& mv_location = mpShaderProgram->getUniformLocation(cUniform_MV);

    rio::Matrix44f mv44T;
    mv44T.setTranspose(mv44);
    mv_location.setMtx44(mv44T.a);

    const agl::UniformLocation& proj_location = mpShaderProgram->getUniformLocation(cUniform_Proj);

    rio::Matrix44f proj44T;
    proj44T.setTranspose(static_cast<const rio::Matrix44f&>(proj_mtx));
    proj_location.setMtx44(proj44T.a);

    rio::Matrix44f it44;
    it44.setInverse(mv44);
    mpShaderProgram->getUniformLocation(cUniform_IT).setMtx43(it44.a);
}

void Shader::setExRegColorUniform(const rio::Color4f* p_color) const
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
    // Color who?

    mpShaderProgram->getUniformLocation(cUniform_FogStart).setFloat(1000000.0f);

    mpShaderProgram->getUniformLocation(cUniform_FogStartEndInv).setFloat(1000000.0f);

    rio::BaseVec3f dir { 0.0f, 0.0f, -1.0f };
    mpShaderProgram->getUniformLocation(cUniform_FogDir).setVec3(dir);
}

void Shader::applyAlphaTest(bool enable, rio::Graphics::CompareFunc func, f32 ref) const
{
#if RIO_IS_CAFE
    GX2SetAlphaTest(GX2Boolean(enable), GX2CompareFunction(func), ref);
#elif RIO_IS_WIN
    const rio::Shader* p_shader_rio = mpShaderProgram->getShaderRIO();
    RIO_ASSERT(p_shader_rio);

    p_shader_rio->setUniform(u32(func - GL_NEVER), u32(-1), p_shader_rio->getFragmentUniformLocation("PS_PUSH.alphaFunc"));
    p_shader_rio->setUniform(ref,                  u32(-1), p_shader_rio->getFragmentUniformLocation("PS_PUSH.alphaRef"));
#endif
}

void Shader::setCulling(FFLCullMode mode)
{
    if (mode > FFL_CULL_MODE_FRONT)
        return;

    rio::RenderState render_state;

    switch (mode)
    {
    case FFL_CULL_MODE_NONE:
        render_state.setCullingMode(rio::Graphics::CULLING_MODE_NONE);
        break;
    case FFL_CULL_MODE_BACK:
        render_state.setCullingMode(rio::Graphics::CULLING_MODE_BACK);
        break;
    case FFL_CULL_MODE_FRONT:
        render_state.setCullingMode(rio::Graphics::CULLING_MODE_FRONT);
        break;
    default:
        break;
    }

    render_state.applyCullingAndPolygonModeAndPolygonOffset();
}

void Shader::initializeParam_()
{
    mLightParam.enable = true;
    mLightParam.dir = cLightDir;
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

void Shader::applyAlphaTestCallback_(void* p_obj, bool enable, rio::Graphics::CompareFunc func, f32 ref)
{
    static_cast<Shader*>(p_obj)->applyAlphaTest(enable, func, ref);
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
    default:
        break;
    }

    setMaterialUniform_(draw_param);
    setLightUniform_();
    setRimUniform_();

    if (draw_param.modulateParam.pTexture2D != nullptr)
    {
        mSampler.linkTexture2D(draw_param.modulateParam.pTexture2D);
        const agl::SamplerLocation& location = mpShaderProgram->getSamplerLocationValidate(cSampler_Texture);
        mSampler.tryBind(location.getVertexLocation(), location.getFragmentLocation(), cSampler_Texture);
    }

  //s32 lightmap_index = 4;
  //if (mpModel != nullptr && mpModel->getLightMapType() == ModelFFL::cLightmapType_LightMapMgr_Index_0)
  //    lightmap_index = 0;

    if (mpModel != nullptr)
    {
        switch (mpModel->getLightMapType())
        {
        case ModelFFL::cLightmapType_Custom:
            mLightmap01p.applyTextureData(*mpModel->getLightmap01p());
            mLightmap01p.activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap01p), cSampler_Lightmap01p);
            mLightmap02p.applyTextureData(*mpModel->getLightmap02p());
            mLightmap02p.activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p), cSampler_Lightmap02p);
            break;
        default:
          //LightMapMgr::instance()->getLightmap01p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap01p), cSampler_Lightmap01p);
          //LightMapMgr::instance()->getLightmap02p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p), cSampler_Lightmap02p);
            break;
        }
    }
    else
    {
      //LightMapMgr::instance()->getLightmap01p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap01p), cSampler_Lightmap01p);
      //LightMapMgr::instance()->getLightmap02p(lightmap_index).activate(mpShaderProgram->getSamplerLocationValidate(cSampler_Lightmap02p), cSampler_Lightmap02p);
    }

    if (draw_param.primitiveParam.pIndexBuffer != nullptr)
    {
#if RIO_IS_CAFE
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
#elif RIO_IS_WIN
        {
            FFLAttributeBufferType type = FFL_ATTRIBUTE_BUFFER_TYPE_POSITION;

            const FFLAttributeBuffer& buffer = draw_param.attributeBufferParam.attributeBuffers[type];
            s32 location = mAttributeLocation[type];

            void* ptr = buffer.ptr;

            if (ptr && location != -1)
            {
              //RIO_LOG("Enable position (%d)\n", location);

                u32 stride = buffer.stride;

                if (stride == 0)
                {
                    RIO_GL_CALL(glVertexAttrib3fv(location, static_cast<f32*>(ptr)));
                }
                else
                {
                    u32 vbo_handle = mVBOHandle[type];
                    u32 size = buffer.size;

                    RIO_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_handle));
                    RIO_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW));

                    RIO_GL_CALL(glEnableVertexAttribArray(location));
                    RIO_GL_CALL(glVertexAttribPointer(
                        location,
                        3,
                        GL_FLOAT,
                        false,
                        stride,
                        nullptr
                    ));
                }
            }
        }
        {
            FFLAttributeBufferType type = FFL_ATTRIBUTE_BUFFER_TYPE_TEXCOORD;

            const FFLAttributeBuffer& buffer = draw_param.attributeBufferParam.attributeBuffers[type];
            s32 location = mAttributeLocation[type];

            void* ptr = buffer.ptr;

            if (ptr && location != -1)
            {
              //RIO_LOG("Enable texCoord (%d)\n", location);

                u32 stride = buffer.stride;

                if (stride == 0)
                {
                    RIO_GL_CALL(glVertexAttrib2fv(location, static_cast<f32*>(ptr)));
                }
                else
                {
                    u32 vbo_handle = mVBOHandle[type];
                    u32 size = buffer.size;

                    RIO_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_handle));
                    RIO_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW));

                    RIO_GL_CALL(glEnableVertexAttribArray(location));
                    RIO_GL_CALL(glVertexAttribPointer(
                        location,
                        2,
                        GL_FLOAT,
                        false,
                        stride,
                        nullptr
                    ));
                }
            }
        }
        {
            FFLAttributeBufferType type = FFL_ATTRIBUTE_BUFFER_TYPE_NORMAL;

            const FFLAttributeBuffer& buffer = draw_param.attributeBufferParam.attributeBuffers[type];
            s32 location = mAttributeLocation[type];

            void* ptr = buffer.ptr;

            if (ptr && location != -1)
            {
              //RIO_LOG("Enable normal (%d)\n", location);

                u32 stride = buffer.stride;

                if (stride == 0)
                {
                    RIO_GL_CALL(glVertexAttribP4ui(location, GL_INT_2_10_10_10_REV, true, *static_cast<u32*>(ptr)));
                }
                else
                {
                    u32 vbo_handle = mVBOHandle[type];
                    u32 size = buffer.size;

                    RIO_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_handle));
                    RIO_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW));

                    RIO_GL_CALL(glEnableVertexAttribArray(location));
                    RIO_GL_CALL(glVertexAttribPointer(
                        location,
                        4,
                        GL_INT_2_10_10_10_REV,
                        true,
                        stride,
                        nullptr
                    ));
                }
            }
        }
        {
            FFLAttributeBufferType type = FFL_ATTRIBUTE_BUFFER_TYPE_TANGENT;

            const FFLAttributeBuffer& buffer = draw_param.attributeBufferParam.attributeBuffers[type];
            s32 location = mAttributeLocation[type];

            void* ptr = buffer.ptr;

            if (ptr && location != -1)
            {
              //RIO_LOG("Enable tangent (%d)\n", location);

                u32 stride = buffer.stride;

                if (stride == 0)
                {
                    RIO_GL_CALL(glVertexAttrib4Nbv(location, static_cast<s8*>(ptr)));
                }
                else
                {
                    u32 vbo_handle = mVBOHandle[type];
                    u32 size = buffer.size;

                    RIO_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_handle));
                    RIO_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW));

                    RIO_GL_CALL(glEnableVertexAttribArray(location));
                    RIO_GL_CALL(glVertexAttribPointer(
                        location,
                        4,
                        GL_BYTE,
                        true,
                        stride,
                        nullptr
                    ));
                }
            }
        }
        {
            FFLAttributeBufferType type = FFL_ATTRIBUTE_BUFFER_TYPE_COLOR;

            const FFLAttributeBuffer& buffer = draw_param.attributeBufferParam.attributeBuffers[type];
            s32 location = mAttributeLocation[type];

            void* ptr = buffer.ptr;

            if (ptr && location != -1)
            {
              //RIO_LOG("Enable color (%d)\n", location);

                u32 stride = buffer.stride;

                if (stride == 0)
                {
                    RIO_GL_CALL(glVertexAttrib4Nubv(location, static_cast<u8*>(ptr)));
                }
                else
                {
                    u32 vbo_handle = mVBOHandle[type];
                    u32 size = buffer.size;

                    RIO_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_handle));
                    RIO_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW));

                    RIO_GL_CALL(glEnableVertexAttribArray(location));
                    RIO_GL_CALL(glVertexAttribPointer(
                        location,
                        4,
                        GL_UNSIGNED_BYTE,
                        true,
                        stride,
                        nullptr
                    ));
                }
            }
        }
#endif

        rio::Drawer::DrawElements(
            draw_param.primitiveParam.primitiveType,
            draw_param.primitiveParam.indexCount,
            (const u16*)draw_param.primitiveParam.pIndexBuffer
        );
    }
}

void Shader::drawCallback_(void* p_obj, const FFLDrawParam& draw_param)
{
    static_cast<Shader*>(p_obj)->draw_(draw_param);
}

void Shader::setMatrix_(const rio::BaseMtx44f& matrix)
{
    mpShaderProgram->getUniformLocationValidate(cUniform_MV).setMtx44(rio::Matrix44f::ident.a);

    mpShaderProgram->getUniformLocationValidate(cUniform_IT).setMtx43(rio::Matrix44f::ident.a);

    rio::Matrix44f proj;
    proj.setTranspose(static_cast<const rio::Matrix44f&>(matrix));

    mpShaderProgram->getUniformLocationValidate(cUniform_Proj).setMtx44(proj.a);
}

void Shader::setMatrixCallback_(void* p_obj, const rio::BaseMtx44f& matrix)
{
    static_cast<Shader*>(p_obj)->setMatrix_(matrix);
}

namespace {

const rio::BaseVec4f& getColorUniform(const FFLColor& color)
{
    return reinterpret_cast<const rio::BaseVec4f&>(color.r);
}

}

}
