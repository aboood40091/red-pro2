#include <graphics/CullViewFrustum.h>
#include <graphics/ModelNW.h>
#include <graphics/ModelNWShadowUtil.h>
#include <graphics/RenderMgr.h>
#include <graphics/ShaderHolder.h>

#include <gfx/seadGraphics.h>
#include <util/aglPrimitiveTexture.h>

ModelNW::ModelNW()
    : Model()
    , mModelEx()
    , mSklAnimBlender()
    , mpSklAnim()
    , mpTexAnim()
    , mpShuAnim()
    , mpVisAnim()
    , mpShaAnim()
    , mpBuffer(NULL)
    , mpBlockBuffer(NULL)
    , mBlockBufferSize(0)
    , mpSklAnimBlenderBuffer(NULL)
    , mSklAnimBlendWeight()
    , mOpaShapeInfo()
    , mXluShapeInfo()
    , mShaderAssign()
    , mpMaterial()
    , mShape()
    , mMtxRT(sead::Matrix34f::ident)
    , mScale(sead::Vector3f::ones)
    , _128(0)
    , mRenderFlag(3)
    , mBoundingEnableFlag(0)
    , mViewShapeShadowFlagBuffer()
    , mBounding(sead::Vector3f::zero, 1.0f)
    , mpSubBounding(NULL)
    , mShapeFlag(1)
    , mBoundingFlagArray() // TODO
    , mSubBoundingFlagArray() // ^^
    , mViewDepthShadowEnableFlag()
    , mDisplayListDirty(false)
{
}

ModelNW::~ModelNW()
{
}

void ModelNW::initialize(nw::g3d::res::ResModel* res_model, const agl::ShaderProgramArchive* shader_archive, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, u32 bounding_mode, sead::Heap* heap)
{
    switch (bounding_mode)
    {
    case 0:
        mBoundingEnableFlag.reset(
            1 << 0 |
            1 << 1 |
            1 << 2
        );
        break;
    case 1:
        mBoundingEnableFlag.set(
            1 << 0 |
            1 << 1 |
            1 << 2
        );
        break;
    case 2:
        mBoundingEnableFlag.set(
            1 << 0 |
            1 << 1 |
            1 << 2 |
            1 << 5
        );
        mpSubBounding = new (heap) sead::BoundBox3f();
        break;
    }

    nw::g3d::ModelObj::InitArg model_arg(res_model);
    model_arg.ViewCount(num_view);

    if (bounding_mode != 0)
        model_arg.EnableBounding();
    else
        model_arg.DisableBounding();

    size_t buffer_size = nw::g3d::ModelObj::CalcBufferSize(model_arg);
    mpBuffer = new (heap, nw::g3d::ModelObj::BUFFER_ALIGNMENT) u8[buffer_size];

    mModelEx.Init(model_arg, mpBuffer, buffer_size);

    mModelEx.createEx(heap);

    mBlockBufferSize = mModelEx.CalcBlockBufferSize();
    mpBlockBuffer = new (heap, nw::g3d::ModelObj::BLOCK_BUFFER_ALIGNMENT) u8[mBlockBufferSize];

    sead::Graphics::instance()->lockDrawContext();
    {
        mModelEx.SetupBlockBuffer(mpBlockBuffer, mBlockBufferSize);
    }
    sead::Graphics::instance()->unlockDrawContext();

    if (num_skl_anim != 0)
    {
        nw::g3d::SkeletalAnimBlender::InitArg blender_arg;
        blender_arg.SetMaxBoneCount(res_model->GetSkeleton()->GetBoneCount());

        size_t buffer_size = nw::g3d::SkeletalAnimBlender::CalcBufferSize(blender_arg);
        mpSklAnimBlenderBuffer = new (heap, nw::g3d::SkeletalAnimBlender::BUFFER_ALIGNMENT) u8[buffer_size];

        mSklAnimBlender.Init(blender_arg, mpSklAnimBlenderBuffer, buffer_size);

        mSklAnimBlendWeight.allocBuffer(num_skl_anim, heap);
        mSklAnimBlendWeight.fill(1.0f);

        mpSklAnim.allocBuffer(num_skl_anim, heap);
        mpSklAnim.fill(NULL);
    }

    if (num_tex_anim != 0)
    {
        mpTexAnim.allocBuffer(num_tex_anim, heap);
        mpTexAnim.fill(NULL);
    }

    if (num_shu_anim != 0)
    {
        mpShuAnim.allocBuffer(num_shu_anim, heap);
        mpShuAnim.fill(NULL);
    }

    if (num_vis_anim != 0)
    {
        mpVisAnim.allocBuffer(num_vis_anim, heap);
        mpVisAnim.fill(NULL);
    }

    if (num_sha_anim != 0)
    {
        mpShaAnim.allocBuffer(num_sha_anim, heap);
        mpShaAnim.fill(NULL);
    }

    sead::Graphics::instance()->lockDrawContext();
    {
        for (s32 idx_material = 0; idx_material < mModelEx.GetMaterialCount(); idx_material++)
        {
            agl::g3d::MaterialEx& material = mModelEx.getMaterialEx(idx_material);
            sead::SafeString shader_archive_name;

            bool name_set = false;

            const nw::g3d::res::ResShaderAssign* res_shader_assign = material.getMaterialObj()->GetResource()->GetShaderAssign();
            if (res_shader_assign)
            {
                const char* p_name = res_shader_assign->GetShaderArchiveName();
                if (p_name)
                {
                    shader_archive_name = p_name;
                    name_set = true;
                }
            }

            if (!name_set)
                shader_archive_name = sead::SafeString::cEmptyString;

            bool is_local = false;

            if (shader_archive)
            {
                if (shader_archive_name.isEmpty() ||
                    shader_archive_name.comparen("nw4f", 4) != 0)
                {
                    is_local = true;
                }
            }

            const nw::g3d::res::ResMaterial* p_res_material = material.getMaterialObj()->GetResource();

            if (is_local)
            {
                material.bindShaderResAssign(shader_archive->searchShaderProgram(p_res_material->GetName()), NULL, NULL);
            }
            else
            {
                const nw::g3d::res::ResShaderAssign* res_shader_assign = p_res_material->GetShaderAssign(); // ??
                if (!shader_archive_name.isEmpty())
                {
                    const agl::ShaderProgramArchive* g_shader_program_archive = ShaderHolder::instance()->getShaderArchive(res_shader_assign->GetShaderArchiveName());
                    if (g_shader_program_archive)
                    {
                        const agl::ShaderProgram* g_shader_program = g_shader_program_archive->searchShaderProgram(res_shader_assign->GetShadingModelName());
                        if (g_shader_program)
                        {
                            static const char* sModelOptionSymbolIDs[] = {
                                "NUM_SKINNING_VTX"
                            };
                            static const char* sModelOptionSymbolValues[][5] = {
                                {
                                    "0",
                                    "1",
                                    "2",
                                    "3",
                                    "4"
                                }
                            };
                            material.bindShaderResAssign(g_shader_program, sModelOptionSymbolIDs[0], sModelOptionSymbolValues[0]);
                            continue;
                        }
                    }
                }

                material.bindShader(ShaderHolder::instance()->getNw4fBasicShaderProgram());
            }
        }
    }
    sead::Graphics::instance()->unlockDrawContext();

    sead::Graphics::instance()->lockDrawContext();
    {
        mpMaterial.allocBuffer(mModelEx.GetMaterialCount(), heap);
        for (sead::Buffer<MaterialNW*>::iterator it = mpMaterial.begin(), it_end = mpMaterial.end(); it != it_end; ++it)
            *it = new (heap) MaterialNW(mModelEx.GetMaterial(it.getIndex()));

        mShape.allocBuffer(mModelEx.GetShapeCount(), heap);
        const agl::UniformBlock* base_uniform_block = NULL;
        for (sead::Buffer<Shape>::iterator it = mShape.begin(), it_end = mShape.end(); it != it_end; ++it)
        {
            s32 idx_shape = it.getIndex();
            const nw::g3d::ShapeObj* shape_obj = mModelEx.GetShape(idx_shape);

            it->light_map.clear();

            if (idx_shape == 0)
            {
                it->uniform_block.startDeclare(2, heap);
                it->uniform_block.declare(agl::UniformBlock::cType_vec4, 3); // vec4 cShpMtx[ 3 ]
                it->uniform_block.declare(agl::UniformBlock::cType_int,  1); // int  cWeightNum

                base_uniform_block = &it->uniform_block;
            }
            else
            {
                it->uniform_block.declare(*base_uniform_block);
            }

            it->uniform_block.create(heap);

            s32 weight_num = shape_obj->GetVtxSkinCount();

            it->uniform_block.dcbz();
            it->uniform_block.setInt(1, weight_num);
            it->uniform_block.flush(true);

            if (num_sha_anim > 0 && shape_obj->GetKeyShapeCount() > 0)
            {
                s32 num_vtx_buffer = shape_obj->GetVertexBufferCount();
                it->vtx_buffer.allocBuffer(num_vtx_buffer, heap);

                for (s32 idx_buffer = 0; idx_buffer < num_vtx_buffer; idx_buffer++)
                {
                    const nw::g3d::fnd::GfxBuffer& buffer = shape_obj->GetVertexBuffer(idx_buffer);

                    void* p_data = new (heap) u8[buffer.GetSize()];
                    sead::MemUtil::copy(p_data, buffer.GetData(), buffer.GetSize());

                    nw::g3d::fnd::GfxBuffer& new_buffer = it->vtx_buffer[idx_buffer];
                    new_buffer.SetData(p_data, buffer.GetSize());
                    new_buffer.SetStride(buffer.GetStride());
                    new_buffer.Setup();
                    new_buffer.DCFlush();

                    agl::g3d::ModelShaderAssign& shader_assign = mModelEx.getShaderAssign(idx_shape);
                    for (s32 idx_attrib = 0; idx_attrib < shader_assign.getAttribute().getVertexBufferNum(); idx_attrib++)
                        if (shader_assign.getAttribute().getVertexBuffer(idx_attrib) == &buffer)
                            shader_assign.getAttribute().setVertexBuffer(&new_buffer, idx_attrib);
                }
            }
        }

        if (mBoundingEnableFlag.isOn(1 << 0))
        {
            createViewShapeShadowFlagBuffer_(num_view, heap);
            calcBounding_();
        }
    }
    sead::Graphics::instance()->unlockDrawContext();

    LightMapMgr::instance()->setModelLightMap(this, false);
    mDisplayListDirty = false;

    mOpaShapeInfo.allocBuffer(mModelEx.GetShapeCount(), heap);
    mXluShapeInfo.allocBuffer(mModelEx.GetShapeCount(), heap);
    mShaderAssign.allocBuffer(mModelEx.GetShapeCount(), heap);

    ShapeRenderInfo* render_info_array = new (heap) ShapeRenderInfo[mModelEx.GetShapeCount()];

    mShapeFlag.makeAllZero();

    sead::Graphics::instance()->lockDrawContext();
    {
        for (s32 idx_shape = 0; idx_shape < mModelEx.GetShapeCount(); idx_shape++)
        {
            ShapeRenderInfo& render_info = render_info_array[idx_shape];
            const nw::g3d::ShapeObj* shape_obj = mModelEx.GetShape(idx_shape);
            s32 idx_material = shape_obj->GetMaterialIndex();
            const nw::g3d::MaterialObj* material_obj = mModelEx.GetMaterial(idx_material);
            const agl::g3d::ModelShaderAssign& shader_assign = mModelEx.getShaderAssign(idx_shape);
            nw::g3d::res::ResRenderState::Mode render_mode = material_obj->GetResRenderState()->GetMode();

            render_info.priority = idx_material;
            render_info.idx_shape = idx_shape;

            mShaderAssign[idx_shape].initialize(shader_assign.getShaderProgram());

            render_info.attrib_dl.beginDisplayListTemporary(0x400);
            {
                shader_assign.getAttribute().activateVertexBuffer();
            }
            render_info.attrib_dl.endDisplayListTemporary(heap);

            render_info.mat_dl.beginDisplayListTemporary(0x400);
            {
                activateMaterial(shader_assign, material_obj, mShape[idx_shape].light_map);
            }
            render_info.mat_dl.endDisplayListTemporary(heap);

            initializeShapeRenderInfo_(render_info, material_obj, shape_obj);

            if (render_mode == nw::g3d::res::ResRenderState::MODE_OPAQUE ||
                render_mode == nw::g3d::res::ResRenderState::MODE_ALPHAMASK)
            {
                mOpaShapeInfo.pushBack(&render_info);
            }
            else
            {
                mXluShapeInfo.pushBack(&render_info);
            }
        }
    }
    sead::Graphics::instance()->unlockDrawContext();

    mOpaShapeInfo.sort(&sortShapeRenderInfoCmp);
    mXluShapeInfo.sort(&sortShapeRenderInfoCmp);
}

void ModelNW::createViewShapeShadowFlagBuffer_(s32 num_view, sead::Heap* heap)
{
    mViewShapeShadowFlagBuffer.allocBuffer(num_view, heap);
    for (s32 i = 0; i < num_view; i++)
    {
        ModelNWShadowUtil::allocBuffer(mViewShapeShadowFlagBuffer[i], mModelEx.GetShapeCount(), heap);
        mViewShapeShadowFlagBuffer[i].fill(sead::BitFlag32(0));
    }
}

s32 ModelNW::sortShapeRenderInfoCmp(const ShapeRenderInfo* a, const ShapeRenderInfo* b)
{
    return a->priority - b->priority;
}

void ModelNW::initializeShapeRenderInfo_(ShapeRenderInfo& render_info, const nw::g3d::MaterialObj* p_material, const nw::g3d::ShapeObj* p_shape)
{
    bool invisible = false;

    render_info.flag.makeAllZero();

    s32 idx_shadow_cast = p_material->GetResource()->GetRenderInfoIndex("shadow_cast");
    if (idx_shadow_cast >= 0 && !sead::SafeString(p_material->GetResource()->GetRenderInfo(idx_shadow_cast)->GetString(0)).isEqual("yes"))
    {
        if (sead::SafeString(p_material->GetResource()->GetRenderInfo(idx_shadow_cast)->GetString(0)).isEqual("shadow-only"))
        {
            mShapeFlag.set(1 << 2);
            render_info.flag.set(1 << 2);
            invisible = true;
        }
    }
    else
    {
        mShapeFlag.set(1 << 2);
        render_info.flag.set(1 << 2);
    }

    s32 idx_polygon_offset = p_material->GetResource()->GetRenderInfoIndex("polygon_offset");
    if (idx_polygon_offset >= 0)
    {
        sead::SafeString str_polygon_offset = p_material->GetResource()->GetRenderInfo(idx_polygon_offset)->GetString(0);
        if (str_polygon_offset.comparen("yes", 3) == 0)
        {
            char c = str_polygon_offset[3];

            s32 polygon_offset = 0;
            if (c - '0' < 10)
                polygon_offset = c - '0';

            render_info.polygon_offset = polygon_offset;
        }
        else
        {
            render_info.polygon_offset = -1;
        }
    }
    else
    {
        render_info.polygon_offset = -1;
    }

    s32 idx_reflection = p_material->GetResource()->GetRenderInfoIndex("reflection");
    if (idx_reflection >= 0)
    {
        if (sead::SafeString(p_material->GetResource()->GetRenderInfo(idx_reflection)->GetString(0)).isEqual("yes"))
        {
            render_info.flag.set(1 << 1);
            mShapeFlag.set(1 << 1);
        }
        else if (sead::SafeString(p_material->GetResource()->GetRenderInfo(idx_reflection)->GetString(0)).isEqual("reflection-only"))
        {
            render_info.flag.set(1 << 1);
            mShapeFlag.set(1 << 1);
            invisible = true;
        }
    }

    if (!invisible)
    {
        render_info.flag.set(1 << 0);
        mShapeFlag.set(1 << 0);
    }

    s32 idx_priority = p_material->GetResource()->GetRenderInfoIndex("priority");
    if (idx_priority >= 0)
    {
        const s32* p_priority = p_material->GetResource()->GetRenderInfo(idx_priority)->GetInt();
        if (p_priority)
            render_info.priority = *p_priority * 0x10000 + p_shape->GetMaterialIndex();
    }
}

void ModelNW::activateMaterial(const agl::g3d::ModelShaderAssign& shader_assign, const nw::g3d::MaterialObj* p_material, const LightMap& light_map) const
{
    shader_assign.activateMaterialUniformBlock(p_material);
    shader_assign.activateTextureSampler(p_material);

    for (s32 i = 0; i < LightMapMgr::cLightMapNum; i++)
    {
        s32 idx_lghtmap = light_map.idx_lghtmap[i];
        if (idx_lghtmap != -1)
        {
            s32 idx_sampler = light_map.idx_sampler[i];
            if (idx_sampler != -1)
            {
                const agl::SamplerLocation& location = shader_assign.getSamplerLocation(idx_sampler);

                LightMapMgr::instance()->getLightMapMgr()
                    .getLightMap(idx_lghtmap)
                        .getTextureSampler()
                            .activate(location, 12 + i);
            }
        }
    }
}

void ModelNW::calcBounding_()
{
    if (mBoundingEnableFlag.isOn(1 << 4))
        mBoundingEnableFlag.reset(1 << 2);

    if ( mBoundingEnableFlag.isOn(1 << 1) ||
        (mBoundingEnableFlag.isOn(1 << 2) && mBoundingEnableFlag.isOff(1 << 3)) )
    {
        mModelEx.CalcBounding();

        const nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();
        if (p_bounding)
        {
            mBounding.setCenter(reinterpret_cast<const sead::Vector3f&>(p_bounding->center));
            mBounding.setRadius(p_bounding->radius);
        }

        // ???
        sead::MemUtil::fill(mSubBoundingFlagArray, u8(-1), sizeof(u32) * 9);
        // ??????
        mSubBoundingFlagArray[9] = 0xFFFFFFFF;

        mBoundingEnableFlag.reset(
            1 << 1 |
            1 << 2
        );
    }
    else if (mBoundingEnableFlag.isOn(1 << 2) /* && mBoundingEnableFlag.isOn(1 << 3) */)
    {
        bool enable = false;
        nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();

        for (s32 idx_shape = 0; idx_shape < mModelEx.GetShapeCount(); idx_shape++)
        {
            nw::g3d::ShapeObj* p_shape = mModelEx.GetShape(idx_shape);

            if (p_shape->GetVtxSkinCount() != 0 ||
                getBoundingFlag_(p_shape->GetBoneIndex()))
            {
                p_shape->CalcBounding(mModelEx.GetSkeleton());

                if (idx_shape < 32*10)
                    setSubBoundingFlag_(idx_shape);

                p_bounding->Merge(*p_bounding, *p_shape->GetBounding());

                enable = true;
            }
        }

        if (enable && p_bounding)
        {
            mBounding.setCenter(reinterpret_cast<sead::Vector3f&>(p_bounding->center));
            mBounding.setRadius(p_bounding->radius);
        }

        mBoundingEnableFlag.reset(
            1 << 2
        );
    }

    if (mBoundingEnableFlag.isOn(1 << 5))
    {
        u32* p_sub_flag_array = mSubBoundingFlagArray;

        bool has_sub_bounding = false;
        for (s32 i = 0; i < 10; i++)
        {
            if (p_sub_flag_array[i] != 0)
            {
                has_sub_bounding = true;
                break;
            }
        }

        if (has_sub_bounding)
        {
            nw::g3d::AABB aabb;
            aabb.min.Set(sead::Mathf::maxNumber(), sead::Mathf::maxNumber(), sead::Mathf::maxNumber());
            aabb.max.Set(sead::Mathf::minNumber(), sead::Mathf::minNumber(), sead::Mathf::minNumber());

            const nw::g3d::SkeletonObj* p_skeleton = mModelEx.GetSkeleton();

            for (s32 idx_shape = 0; idx_shape < mModelEx.GetShapeCount(); idx_shape++)
            {
                nw::g3d::ShapeObj* p_shape = mModelEx.GetShape(idx_shape);

                if (getSubBoundingFlag_(idx_shape))
                    p_shape->CalcSubBounding(p_skeleton);

                aabb.Merge(aabb, *p_shape->GetSubBoundingArray());
            }

            sead::MemUtil::fillZero(p_sub_flag_array, sizeof(u32) * 10);

            mpSubBounding->setUndef();
            mpSubBounding->setMax(reinterpret_cast<const sead::Vector3f&>(aabb.max));
            mpSubBounding->setMin(reinterpret_cast<const sead::Vector3f&>(aabb.min));
        }
    }
}

void ModelNW::applyBlendWeight_(s32 shape_index)
{
    Shape& shape = mShape[shape_index];
    if (!shape.vtx_buffer.isBufferReady())
        return;

    nw::g3d::ShapeObj* p_shape = mModelEx.GetShape(shape_index);

    f32 blend_weight_array[64];
    const u8* v_data_array[64];

    s32 num_key_shape = p_shape->GetKeyShapeCount();

    for (s32 idx_key_shape = 0; idx_key_shape < num_key_shape; idx_key_shape++)
        blend_weight_array[idx_key_shape] = p_shape->GetBlendWeight(idx_key_shape);

    for (s32 idx_attrib = 0; idx_attrib < p_shape->GetTargetAttribCount(); idx_attrib++)
    {
        const nw::g3d::res::ResKeyShape* p_base_res_key_shape = p_shape->GetResKeyShape(0);
        const nw::g3d::res::ResVtxAttrib* p_base_res_vtx_attrib = p_shape->GetResVtxAttrib(p_base_res_key_shape->ref().targetAttribIndices[idx_attrib]);

        if (p_base_res_vtx_attrib->GetFormat() != GX2_ATTRIB_FORMAT_32_32_32_FLOAT)
            return;

        nw::g3d::fnd::GfxBuffer& base_buffer = shape.vtx_buffer[p_base_res_vtx_attrib->GetBufferIndex()];
        u8* p_data = static_cast<u8*>(base_buffer.GetData()) + p_base_res_vtx_attrib->GetOffset();

        for (s32 idx_key_shape = 0; idx_key_shape < num_key_shape; idx_key_shape++)
        {
            const nw::g3d::res::ResKeyShape* p_res_key_shape = p_shape->GetResKeyShape(idx_key_shape);
            const nw::g3d::res::ResVtxAttrib* p_res_vtx_attrib = p_shape->GetResVtxAttrib(p_res_key_shape->ref().targetAttribIndices[idx_attrib]);

            const nw::g3d::fnd::GfxBuffer& buffer = p_shape->GetVertexBuffer(p_res_vtx_attrib->GetBufferIndex());
            v_data_array[idx_key_shape] = static_cast<const u8*>(buffer.GetData()) + p_res_vtx_attrib->GetOffset();
        }

        u32 stride = base_buffer.GetStride();
        u32 elem_num = base_buffer.GetSize() / stride;
        u32 offset = 0;

        while (elem_num > 0)
        {
            sead::Vector3f* p_dst = (sead::Vector3f*)(p_data + offset);
            p_dst->set(0.0f, 0.0f, 0.0f);

            for (s32 idx_key_shape = 0; idx_key_shape < num_key_shape; idx_key_shape++)
            {
                const sead::Vector3f* p_src = (const sead::Vector3f*)(v_data_array[idx_key_shape] + offset);
                f32 blend_weight = blend_weight_array[idx_key_shape];

                p_dst->x = p_src->x * blend_weight + p_dst->x;
                p_dst->y = p_src->y * blend_weight + p_dst->y;
                p_dst->z = p_src->z * blend_weight + p_dst->z;
            }

            elem_num--;
            offset += stride;
        }
    }

    for (sead::Buffer<nw::g3d::fnd::GfxBuffer>::constIterator it = shape.vtx_buffer.constBegin(), it_end = shape.vtx_buffer.constEnd(); it != it_end; ++it)
        it->DCFlush();
}

void ModelNW::calc()
{
    mModelEx.CalcMtxBlock();
    mModelEx.CalcShape();
    mModelEx.CalcMaterial();

    if (mpShaAnim.isBufferReady())
    {
        for (s32 idx_shape = 0, num_shape = mModelEx.GetShapeCount(); idx_shape < num_shape; idx_shape++)
        {
            nw::g3d::ShapeObj* p_shape = mModelEx.GetShape(idx_shape);
            if (p_shape->GetKeyShapeCount() != 0 && p_shape->HasValidBlendWeight())
                applyBlendWeight_(idx_shape);
        }
    }
}

void ModelNW::calcGPU(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    mModelEx.CalcView(view_index, reinterpret_cast<const nw::g3d::math::Mtx34&>(view_mtx));
}

void ModelNW::drawOpa_(DrawInfo& draw_info, const RenderMgr* p_render_mgr) const
{
    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mOpaShapeInfo.constBegin(), it_end = mOpaShapeInfo.constEnd(); it != it_end; ++it)
        drawShape_(draw_info, *it, p_render_mgr);
}

void ModelNW::drawXlu_(DrawInfo& draw_info, const RenderMgr* p_render_mgr) const
{
    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mXluShapeInfo.constBegin(), it_end = mXluShapeInfo.constEnd(); it != it_end; ++it)
        drawShape_(draw_info, *it, p_render_mgr);
}

void ModelNW::drawShape_(DrawInfo& draw_info, const ShapeRenderInfo& render_info, const RenderMgr* p_render_mgr) const
{
    s32 idx_shape = render_info.idx_shape;
    const nw::g3d::ShapeObj* p_shape = mModelEx.GetShape(idx_shape);

    s32 idx_material = p_shape->GetMaterialIndex();
    const nw::g3d::MaterialObj* p_material = mModelEx.getMaterialEx(idx_material).getMaterialObj();

    const agl::g3d::ModelShaderAssign& shader_assign = mModelEx.getShaderAssign(idx_shape);

    s32 idx_bone = p_shape->GetBoneIndex();

    if (!mModelEx.IsMatVisible(idx_material) ||
        !mModelEx.IsBoneVisible(idx_bone) ||
        !mModelEx.getMaterialEx(idx_material).get_20())
    {
        return;
    }

    if (draw_info.draw_reflection)
    {
        if (render_info.flag.isOff(1 << 1))
            return;
    }
    else if (draw_info.draw_shape)
    {
        if (render_info.flag.isOff(1 << 0))
            return;
    }

    s32 bounding_intersect = 1;
    if (mBoundingEnableFlag.isOn(1 << 0) && draw_info.p_cull)
        if (bounding_intersect = draw_info.p_cull->getViewVolume().TestIntersectionEx(*p_shape->GetBounding()), bounding_intersect < 0)
            return;

    const agl::ShaderProgram* p_shader_program = shader_assign.getShaderProgram();
    if (draw_info.p_shader_program != p_shader_program)
    {
        draw_info.p_shader_program = p_shader_program;
        draw_info.p_shader_assign = const_cast<ShaderAssign*>(&mShaderAssign[idx_shape]);
        draw_info.shader_mode = p_shader_program->activate(draw_info.shader_mode);
        draw_info.material_index = -1;

        if (draw_info.p_shader_program != draw_info.p_shader_assign->p_shader_program)
        {
            draw_info.p_shader_assign->p_shader_program = draw_info.p_shader_program;
            draw_info.p_shader_assign->updateLocation();

            render_info.attrib_dl.clear();
            render_info.mat_dl.clear();
        }

        p_render_mgr->getModelEnvView().getUniformBlock(draw_info.view_index).setUniform(draw_info.p_shader_assign->env_location);

        if (draw_info.p_shader_assign->sdw_location.isValid())
        {
            const agl::TextureSampler& tex_sampler = p_render_mgr->getShadowMap()
                                                        ? *p_render_mgr->getShadowMap()
                                                        : agl::utl::PrimitiveTexture::instance()->getTextureSampler(9);

            tex_sampler.activate(draw_info.p_shader_assign->sdw_location, 15);
        }

        if (draw_info.p_shader_assign->rfl_location.isValid())
        {
            const agl::TextureSampler& tex_sampler = p_render_mgr->getReflectionMap()
                                                        ? *p_render_mgr->getReflectionMap()
                                                        : agl::utl::PrimitiveTexture::instance()->getTextureSampler(2);

            tex_sampler.activate(draw_info.p_shader_assign->rfl_location, 14);
        }
    }

    s32 shp_vtx_location = draw_info.p_shader_assign->shp_location.getVertexLocation();
    if (shp_vtx_location != -1)
        p_shape->GetShpBlock(draw_info.view_index).LoadVertexUniforms(shp_vtx_location);

    s32 shp_frg_location = draw_info.p_shader_assign->shp_location.getFragmentLocation();
    if (shp_frg_location != -1)
        p_shape->GetShpBlock(draw_info.view_index).LoadFragmentUniforms(shp_frg_location);

    s32 mtx_vtx_location = draw_info.p_shader_assign->mtx_location.getVertexLocation();
    if (mtx_vtx_location != -1)
    {
        if (p_shape->IsRigidBody())
            p_shape->GetShpBlock(draw_info.view_index).LoadVertexUniforms(mtx_vtx_location);

        else
            mModelEx.GetSkeleton()->GetMtxBlock().LoadVertexUniforms(mtx_vtx_location);
    }

    if (draw_info.material_index != idx_material)
    {
        draw_info.material_index = idx_material;

        if (!render_info.mat_dl.isEmpty() && !mDisplayListDirty)
            render_info.mat_dl.call();

        else
            activateMaterial(shader_assign, p_material, mShape[idx_shape].light_map);

        if (_128 == 0)
        {
            if (draw_info.draw_shape)
            {
                p_material->GetResRenderState()->Load();

                if (render_info.polygon_offset >= 0)
                {
                    nw::g3d::fnd::GfxPolygonCtrl polygon_ctrl = p_material->GetResRenderState()->GetPolygonCtrl();
                    polygon_ctrl.SetPolygonOffsetFrontEnable(GX2_ENABLE);
                    polygon_ctrl.Load();

                    if (draw_info.polygon_offset != render_info.polygon_offset)
                    {
                        draw_info.polygon_offset = render_info.polygon_offset;
                        p_render_mgr->getViewInfo(draw_info.view_index).layer->setPolygonOffset(draw_info.polygon_offset);
                    }
                }
            }
            else
            {
                nw::g3d::fnd::GfxPolygonCtrl polygon_ctrl = p_material->GetResRenderState()->GetPolygonCtrl();
                polygon_ctrl.SetPolygonOffsetFrontEnable(GX2_ENABLE);
                polygon_ctrl.Load();

                p_material->GetResRenderState()->GetDepthCtrl().Load();

                nw::g3d::fnd::GfxAlphaTest alpha_test = p_material->GetResRenderState()->GetAlphaTest();
                alpha_test.SetRefValue(0.5f);
                alpha_test.Load();
            }
        }
    }

    if (!render_info.attrib_dl.isEmpty())
        render_info.attrib_dl.call();

    else
        shader_assign.getAttribute().activateVertexBuffer();

    const CullViewFrustum* p_cull = draw_info.p_cull;
    const nw::g3d::res::ResMesh* p_res_mesh = p_shape->GetResMesh();

    if (bounding_intersect == 0 && mBoundingEnableFlag.isOn(1 << 0) && p_cull && p_res_mesh->GetSubMeshCount() > 1)
    {
        if (getSubBoundingFlag_(idx_shape))
        {
            const_cast<nw::g3d::ShapeObj*>(p_shape)->CalcSubBounding(mModelEx.GetSkeleton());

            if (idx_shape < 32*10)
                const_cast<ModelNW*>(this)->resetSubBoundingFlag_(idx_shape);
        }

        nw::g3d::CullingContext ctx;
        while (p_shape->TestSubMeshIntersection(&ctx, p_cull->getViewVolume()))
            p_res_mesh->DrawSubMesh(ctx.submeshIndex, ctx.submeshCount);
    }
    else
    {
        p_res_mesh->DrawSubMesh(0, p_shape->GetSubMeshCount());
    }
}

void ModelNW::drawOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mShapeFlag.isOff(1 << 0))
        return;

    const nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();
    const CullViewFrustum* p_cull = p_render_mgr->getViewInfo(view_index).p_cull;
    if (p_bounding && p_cull)
        if (!p_cull->getViewVolume().TestIntersection(*p_bounding))
            return;

    DrawInfo draw_info;
    draw_info.view_index = view_index;
    draw_info.p_view_mtx = &view_mtx;
    draw_info.p_proj_mtx = &proj_mtx;
    draw_info.p_shader_program = NULL;
    draw_info.p_shader_assign = NULL;
    draw_info.material_index = -1;
    draw_info.draw_shape = true;
    draw_info.draw_reflection = false;
    draw_info.shader_mode = agl::cShaderMode_Invalid;
    draw_info.polygon_offset = -1;
    draw_info.p_cull = p_cull;

    if (mRenderFlag.isOn(1 << 0))
        drawOpa_(draw_info, p_render_mgr);

    if (mRenderFlag.isOn(1 << 3))
        drawXlu_(draw_info, p_render_mgr);

    agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
}

void ModelNW::drawXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mShapeFlag.isOff(1 << 0))
        return;

    const nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();
    const CullViewFrustum* p_cull = p_render_mgr->getViewInfo(view_index).p_cull;
    if (p_bounding && p_cull)
        if (!p_cull->getViewVolume().TestIntersection(*p_bounding))
            return;

    DrawInfo draw_info;
    draw_info.view_index = view_index;
    draw_info.p_view_mtx = &view_mtx;
    draw_info.p_proj_mtx = &proj_mtx;
    draw_info.p_shader_program = NULL;
    draw_info.p_shader_assign = NULL;
    draw_info.material_index = -1;
    draw_info.draw_shape = true;
    draw_info.draw_reflection = false;
    draw_info.shader_mode = agl::cShaderMode_Invalid;
    draw_info.polygon_offset = -1;
    draw_info.p_cull = p_cull;

    if (mRenderFlag.isOn(1 << 2))
        drawOpa_(draw_info, p_render_mgr);

    if (mRenderFlag.isOn(1 << 1))
        drawXlu_(draw_info, p_render_mgr);

    agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
}

void ModelNW::drawShadowOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mShapeFlag.isOff(1 << 2) || mViewDepthShadowEnableFlag.isOff(1 << view_index))
        return;

    const CullViewFrustum* p_cull = p_render_mgr->getViewInfo(view_index).p_cull;

    bool bounding_enable = mBoundingEnableFlag.isOn(1 << 0);
    mBoundingEnableFlag.reset(1 << 0);

    DrawInfo draw_info;
    draw_info.view_index = view_index;
    draw_info.p_view_mtx = &view_mtx;
    draw_info.p_proj_mtx = &proj_mtx;
    draw_info.p_shader_program = NULL;
    draw_info.p_shader_assign = NULL;
    draw_info.material_index = -1;
    draw_info.draw_shape = false;
    draw_info.draw_reflection = false;
    draw_info.shader_mode = agl::cShaderMode_Invalid;
    draw_info.polygon_offset = -1;
    draw_info.p_cull = p_cull;

    sead::Buffer<sead::BitFlag32>& shape_shadow_flag_buffer = mViewShapeShadowFlagBuffer[view_index];

    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mOpaShapeInfo.constBegin(), it_end = mOpaShapeInfo.constEnd(); it != it_end; ++it)
    {
        const ShapeRenderInfo& render_info = *it;
        s32 idx_shape = render_info.idx_shape;
        const nw::g3d::ShapeObj* p_shape;

        bool has_shadow = true;
        if (render_info.flag.isOff(1 << 2))
            has_shadow = false;

        else
        {
            p_shape = mModelEx.GetShape(idx_shape);
            s32 idx_material = p_shape->GetMaterialIndex();
            s32 idx_bone = p_shape->GetBoneIndex();

            if (!mModelEx.IsMatVisible(idx_material) ||
                !mModelEx.IsBoneVisible(idx_bone) ||
                !mModelEx.getMaterialEx(idx_material).get_20())
            {
                has_shadow = false;
            }
        }

        if (!has_shadow || shape_shadow_flag_buffer[idx_shape].isOff(1 << 0))
        {
            continue;
        }
        else
        {
            drawShape_(draw_info, render_info, p_render_mgr);
        }
    }

    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mXluShapeInfo.constBegin(), it_end = mXluShapeInfo.constEnd(); it != it_end; ++it)
    {
        const ShapeRenderInfo& render_info = *it;
        s32 idx_shape = render_info.idx_shape;
        const nw::g3d::ShapeObj* p_shape;

        bool has_shadow = true;
        if (render_info.flag.isOff(1 << 2))
            has_shadow = false;

        else
        {
            p_shape = mModelEx.GetShape(idx_shape);
            s32 idx_material = p_shape->GetMaterialIndex();
            s32 idx_bone = p_shape->GetBoneIndex();

            if (!mModelEx.IsMatVisible(idx_material) ||
                !mModelEx.IsBoneVisible(idx_bone) ||
                !mModelEx.getMaterialEx(idx_material).get_20())
            {
                has_shadow = false;
            }
        }

        if (!has_shadow || shape_shadow_flag_buffer[idx_shape].isOff(1 << 0))
        {
            continue;
        }
        else
        {
            drawShape_(draw_info, render_info, p_render_mgr);
        }
    }

    mBoundingEnableFlag.change(1 << 0, bounding_enable);

    agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
}

void ModelNW::drawReflectionOpa(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mShapeFlag.isOff(1 << 1))
        return;

    const nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();
    const CullViewFrustum* p_cull = p_render_mgr->getViewInfo(view_index).p_cull;
    if (p_bounding && p_cull)
        if (!p_cull->getViewVolume().TestIntersection(*p_bounding))
            return;

    DrawInfo draw_info;
    draw_info.view_index = view_index;
    draw_info.p_view_mtx = &view_mtx;
    draw_info.p_proj_mtx = &proj_mtx;
    draw_info.p_shader_program = NULL;
    draw_info.p_shader_assign = NULL;
    draw_info.material_index = -1;
    draw_info.draw_shape = true;
    draw_info.draw_reflection = true;
    draw_info.shader_mode = agl::cShaderMode_Invalid;
    draw_info.polygon_offset = -1;
    draw_info.p_cull = p_cull;

    if (mRenderFlag.isOn(1 << 0))
        drawOpa_(draw_info, p_render_mgr);

    if (mRenderFlag.isOn(1 << 3))
        drawXlu_(draw_info, p_render_mgr);

    agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
}

void ModelNW::drawReflectionXlu(s32 view_index, const sead::Matrix34f& view_mtx, const sead::Matrix44f& proj_mtx, RenderMgr* p_render_mgr)
{
    if (mShapeFlag.isOff(1 << 1))
        return;

    const nw::g3d::Sphere* p_bounding = mModelEx.GetBounding();
    const CullViewFrustum* p_cull = p_render_mgr->getViewInfo(view_index).p_cull;
    if (p_bounding && p_cull)
        if (!p_cull->getViewVolume().TestIntersection(*p_bounding))
            return;

    DrawInfo draw_info;
    draw_info.view_index = view_index;
    draw_info.p_view_mtx = &view_mtx;
    draw_info.p_proj_mtx = &proj_mtx;
    draw_info.p_shader_program = NULL;
    draw_info.p_shader_assign = NULL;
    draw_info.material_index = -1;
    draw_info.draw_shape = true;
    draw_info.draw_reflection = true;
    draw_info.shader_mode = agl::cShaderMode_Invalid;
    draw_info.polygon_offset = -1;
    draw_info.p_cull = p_cull;

    if (mRenderFlag.isOn(1 << 1))
        drawXlu_(draw_info, p_render_mgr);

    if (mRenderFlag.isOn(1 << 2))
        drawOpa_(draw_info, p_render_mgr);

    agl::ShaderProgram::changeShaderMode(agl::cShaderMode_UniformRegister);
}

// -------- Non-matching, but I think I implemented these better --------

bool ModelNW::hasOpa() const
{
    return (mRenderFlag.isOn(1 << 0) && !mOpaShapeInfo.isEmpty()) ||
           (mRenderFlag.isOn(1 << 3) && !mXluShapeInfo.isEmpty());
}

bool ModelNW::hasXlu() const
{
    return (mRenderFlag.isOn(1 << 2) && !mOpaShapeInfo.isEmpty()) ||
           (mRenderFlag.isOn(1 << 1) && !mXluShapeInfo.isEmpty());
}

// ----------------------------------------------------------------------

void ModelNW::setBoundingFlagArray_(u32 flag_array[], const SkeletalAnimation& anim)
{
    const nw::g3d::AnimBindTable& bind_table = anim.getAnimObj().GetBindTable();
    for (s32 idx_anim = 0; idx_anim < bind_table.GetAnimCount(); idx_anim++)
    {
        if (bind_table.IsEnabled(idx_anim))
        {
            s32 index = bind_table.GetTargetIndex(idx_anim);
            if (index < 32*10)
                flag_array[index >> 5] |= 1 << (index & 0x1F);
        }
    }
}

void ModelNW::updateAnimations()
{
    if (mpSklAnim.isBufferReady())
    {
        SkeletalAnimation* p_blend_start_anim = NULL;
        bool blend = false;

        sead::Buffer<SkeletalAnimation*>::constIterator it_end = mpSklAnim.constEnd();

        for (sead::Buffer<SkeletalAnimation*>::constIterator it = mpSklAnim.constBegin(); it != it_end; ++it)
        {
            SkeletalAnimation* p_anim = *it;
            if (p_anim && p_anim->isValid())
            {
                if (sead::Mathf::abs(mSklAnimBlendWeight[it.getIndex()]) > 0.001f)
                {
                    if (p_blend_start_anim == NULL)
                    {
                        p_blend_start_anim = p_anim;
                    }
                    else
                    {
                        blend = true;
                        break;
                    }
                }
            }
        }

        if (mBoundingEnableFlag.isOn(1 << 3))
            sead::MemUtil::fillZero(mBoundingFlagArray, sizeof(mBoundingFlagArray));

        if (blend)
        {
            mSklAnimBlender.ClearResult();

            for (sead::Buffer<SkeletalAnimation*>::constIterator it = mpSklAnim.constBegin(); it != it_end; ++it)
            {
                SkeletalAnimation* p_anim = *it;
                if (p_anim && p_anim->isValid())
                {
                    p_anim->calc();
                    mSklAnimBlender.Blend(&p_anim->getAnimObj(), mSklAnimBlendWeight[it.getIndex()]);

                    if (mBoundingEnableFlag.isOn(1 << 3))
                        setBoundingFlagArray_(mBoundingFlagArray, *p_anim);
                }
            }

            mSklAnimBlender.ApplyTo(mModelEx.GetSkeleton());
        }
        else if (p_blend_start_anim != NULL)
        {
            p_blend_start_anim->calc();
            p_blend_start_anim->getAnimObj().ApplyTo(mModelEx.GetSkeleton());

            if (mBoundingEnableFlag.isOn(1 << 3))
                setBoundingFlagArray_(mBoundingFlagArray, *p_blend_start_anim);
        }
    }

    if (mpTexAnim.isBufferReady())
    {
        for (s32 i = 0; i < mpTexAnim.size(); i++)
        {
            TexturePatternAnimation* p_anim = mpTexAnim[i];
            if (p_anim && p_anim->isValid())
            {
                p_anim->calc();
                p_anim->getAnimObj().ApplyTo(&mModelEx);
            }
        }
    }

    if (mpShuAnim.isBufferReady())
    {
        for (s32 i = 0; i < mpShuAnim.size(); i++)
        {
            ShaderParamAnimation* p_anim = mpShuAnim[i];
            if (p_anim && p_anim->isValid())
            {
                p_anim->calc();
                p_anim->getAnimObj().ApplyTo(&mModelEx);
            }
        }
    }

    if (mpVisAnim.isBufferReady())
    {
        for (s32 i = 0; i < mpVisAnim.size(); i++)
        {
            VisibilityAnimation* p_anim = mpVisAnim[i];
            if (p_anim && p_anim->isValid())
            {
                p_anim->calc();
                p_anim->getAnimObj().ApplyTo(&mModelEx);
            }
        }
    }

    if (mpShaAnim.isBufferReady())
    {
        for (s32 i = 0; i < mpShaAnim.size(); i++)
        {
            ShapeAnimation* p_anim = mpShaAnim[i];
            if (p_anim && p_anim->isValid())
            {
                p_anim->calc();
                p_anim->getAnimObj().ApplyTo(&mModelEx);
            }
        }
    }

    mBoundingEnableFlag.set(1 << 2);
}

void ModelNW::updateModel()
{
    sead::Matrix34f world_mtx = getMtxRT();
    world_mtx.scaleBases(getScale().x, getScale().y, getScale().z);

    mModelEx.CalcWorld(reinterpret_cast<const nw::g3d::math::Mtx34&>(world_mtx));

    if (mBoundingEnableFlag.isOn(1 << 0))
        calcBounding_();
}

void ModelNW::setBoneLocalMatrix(s32 index, const sead::Matrix34f& rt, const sead::Vector3f& scale)
{
    nw::g3d::LocalMtx& local_mtx = mModelEx.GetSkeleton()->GetLocalMtxArray()[index];
    reinterpret_cast<sead::Matrix34f&>(local_mtx.mtxRT) = rt;
    reinterpret_cast<sead::Vector3f&>(local_mtx.scale) = scale;
    local_mtx.EndEdit();
}

void ModelNW::getBoneLocalMatrix(s32 index, sead::Matrix34f* rt, sead::Vector3f* scale) const
{
    const nw::g3d::LocalMtx& local_mtx = mModelEx.GetSkeleton()->GetLocalMtxArray()[index];
    if (rt)    *rt    = reinterpret_cast<const sead::Matrix34f&>(local_mtx.mtxRT);
    if (scale) *scale = reinterpret_cast<const sead::Vector3f&>(local_mtx.scale);
}

void ModelNW::setBoneWorldMatrix(s32 index, const sead::Matrix34f& mtx)
{
    nw::g3d::math::Mtx34& world_mtx = mModelEx.GetSkeleton()->GetWorldMtxArray()[index];
    reinterpret_cast<sead::Matrix34f&>(world_mtx) = mtx;
}

void ModelNW::getBoneWorldMatrix(s32 index, sead::Matrix34f* mtx) const
{
    const nw::g3d::math::Mtx34& world_mtx = mModelEx.GetSkeleton()->GetWorldMtxArray()[index];
    *mtx = reinterpret_cast<const sead::Matrix34f&>(world_mtx);
}

s32 ModelNW::searchBoneIndex(const sead::SafeString& name) const
{
    return mModelEx.GetSkeleton()->GetResource()->GetBoneIndex(name.cstr());
}

const char* ModelNW::getBoneName(s32 index) const
{
    return mModelEx.GetSkeleton()->GetResource()->GetBoneName(index);
}

u32 ModelNW::getBoneNum() const
{
    return mModelEx.GetSkeleton()->GetResource()->GetBoneCount();
}

void ModelNW::setSklAnim(s32 index, Animation* anim)
{
    SkeletalAnimation* p_skl_anim = static_cast<SkeletalAnimation*>(anim);
    p_skl_anim->bindModel(this, index);
    mpSklAnim[index] = p_skl_anim;
}

void ModelNW::setTexAnim(s32 index, Animation* anim)
{
    TexturePatternAnimation* p_tex_anim = static_cast<TexturePatternAnimation*>(anim);
    p_tex_anim->bindModel(this, index);
    mpTexAnim[index] = p_tex_anim;

    mDisplayListDirty = true;
}

void ModelNW::setShuAnim(s32 index, Animation* anim)
{
    ShaderParamAnimation* p_shu_anim = static_cast<ShaderParamAnimation*>(anim);
    p_shu_anim->bindModel(this, index);
    mpShuAnim[index] = p_shu_anim;
}

void ModelNW::setVisAnim(s32 index, Animation* anim)
{
    VisibilityAnimation* p_vis_anim = static_cast<VisibilityAnimation*>(anim);
    p_vis_anim->bindModel(this, index);
    mpVisAnim[index] = p_vis_anim;
}

void ModelNW::setShaAnim(s32 index, Animation* anim)
{
    ShapeAnimation* p_sha_anim = static_cast<ShapeAnimation*>(anim);
    p_sha_anim->bindModel(this, index);
    mpShaAnim[index] = p_sha_anim;
}

u32 ModelNW::getMaterialNum() const
{
    return mModelEx.GetMaterialCount();
}

s32 ModelNW::searchMaterialIndex(const sead::SafeString& name) const
{
    return mModelEx.GetMaterialIndex(name.cstr());
}

const char* ModelNW::getMaterialName(s32 index) const
{
    return mModelEx.GetMaterialName(index);
}

void ModelNW::setMaterialVisible(s32 index, bool visible)
{
    mModelEx.SetMatVisibility(index, visible);
}

bool ModelNW::isMaterialVisible(s32 index) const
{
    return mModelEx.IsMatVisible(index);
}

void ModelNW::setBoneVisible(s32 index, bool visible)
{
    mModelEx.SetBoneVisibility(index, visible);
}

bool ModelNW::isBoneVisible(s32 index) const
{
    return mModelEx.IsBoneVisible(index);
}

void ModelNW::calcViewShapeShadowFlags(agl::sdw::DepthShadow* p_depth_shadow, RenderObjBaseLayer* p_shadow_layer, RenderMgr* p_render_mgr)
{
    if (!isBoundingEnable())
        return;

    s32 view_index = p_shadow_layer->getViewIndex();
    sead::Buffer<sead::BitFlag32>& shape_shadow_flag_buffer = mViewShapeShadowFlagBuffer[view_index];

    u32 view_mask = sead::BitFlag32::makeMask(view_index);
    mViewDepthShadowEnableFlag.reset(view_mask);

    DCZeroRange(shape_shadow_flag_buffer.getBufferPtr(), sizeof(sead::BitFlag32) * shape_shadow_flag_buffer.size());

    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mOpaShapeInfo.constBegin(), it_end = mOpaShapeInfo.constEnd(); it != it_end; ++it)
    {
        const ShapeRenderInfo& render_info = *it;
        s32 idx_shape = render_info.idx_shape;
        const nw::g3d::ShapeObj* p_shape;

        bool has_shadow = true;
        if (render_info.flag.isOff(1 << 2))
            has_shadow = false;

        else
        {
            p_shape = mModelEx.GetShape(idx_shape);
            s32 idx_material = p_shape->GetMaterialIndex();
            s32 idx_bone = p_shape->GetBoneIndex();

            if (!mModelEx.IsMatVisible(idx_material) ||
                !mModelEx.IsBoneVisible(idx_bone) ||
                !mModelEx.getMaterialEx(idx_material).get_20())
            {
                has_shadow = false;
            }
        }

        if (!has_shadow)
        {
            shape_shadow_flag_buffer[idx_shape].makeAllZero();
        }
        else if (!mBoundingEnableFlag.isOn(1 << 1))
        {
            const nw::g3d::Sphere* p_bounding = p_shape->GetBounding();
            if (p_bounding)
            {
                sead::Sphere3f bounding;
                bounding.setCenter(reinterpret_cast<const sead::Vector3f&>(p_bounding->center));
                bounding.setRadius(p_bounding->radius);

                sead::BitFlag32* p_shadow_flag = &shape_shadow_flag_buffer[idx_shape];
                *p_shadow_flag = p_depth_shadow->checkAndUpdate(bounding);
                if (!p_shadow_flag->isZero())
                    mViewDepthShadowEnableFlag.set(view_mask);
            }
        }
    }

    for (sead::PtrArray<ShapeRenderInfo>::constIterator it = mXluShapeInfo.constBegin(), it_end = mXluShapeInfo.constEnd(); it != it_end; ++it)
    {
        const ShapeRenderInfo& render_info = *it;
        s32 idx_shape = render_info.idx_shape;
        const nw::g3d::ShapeObj* p_shape;

        bool has_shadow = true;
        if (render_info.flag.isOff(1 << 2))
            has_shadow = false;

        else
        {
            p_shape = mModelEx.GetShape(idx_shape);
            s32 idx_material = p_shape->GetMaterialIndex();
            s32 idx_bone = p_shape->GetBoneIndex();

            if (!mModelEx.IsMatVisible(idx_material) ||
                !mModelEx.IsBoneVisible(idx_bone) ||
                !mModelEx.getMaterialEx(idx_material).get_20())
            {
                has_shadow = false;
            }
        }

        if (!has_shadow)
        {
            shape_shadow_flag_buffer[idx_shape].makeAllZero();
        }
        else // if (!mBoundingEnableFlag.isOn(1 << 1))
        {
            const nw::g3d::Sphere* p_bounding = p_shape->GetBounding();
            if (p_bounding)
            {
                sead::Sphere3f bounding;
                bounding.setCenter(reinterpret_cast<const sead::Vector3f&>(p_bounding->center));
                bounding.setRadius(p_bounding->radius);

                sead::BitFlag32* p_shadow_flag = &shape_shadow_flag_buffer[idx_shape];
                *p_shadow_flag = p_depth_shadow->checkAndUpdate(bounding);
                if (!p_shadow_flag->isZero())
                    mViewDepthShadowEnableFlag.set(view_mask);
            }
        }
    }
}

void ModelNW::setDisplayListDirty()
{
    mDisplayListDirty = true;
}
