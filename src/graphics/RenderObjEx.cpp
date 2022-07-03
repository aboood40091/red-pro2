#include <graphics/LightMapMgr.h>
#include <graphics/RenderObjEx.h>

#include <gfx/seadGraphics.h>

RenderObjEx::RenderObjEx()
    : RenderObj()
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
    , _12c(3)
    , mBoundingFlag(0)
    , mpViewShapeBuffer()
    , mBounding()
    , mpAABB(NULL)
    , mShapeFlag(1)
    , _154() // TODO
    , _17c() // ^^
    , _1a4()
    , mMaterialNoDL(false)
{
}

RenderObjEx::~RenderObjEx()
{
}

void RenderObjEx::create(nw::g3d::res::ResModel* res_model, const agl::ShaderProgramArchive* shader_archive, s32 num_view, s32 num_skl_anim, s32 num_tex_anim, s32 num_shu_anim, s32 num_vis_anim, s32 num_sha_anim, u32 bounding_mode, sead::Heap* heap)
{
    switch (bounding_mode)
    {
    case 0:
        mBoundingFlag.reset(7);
        break;
    case 1:
        mBoundingFlag.set(7);
        break;
    case 2:
        mBoundingFlag.set(7 | 0x20);
        mpAABB = new (heap) nw::g3d::AABB;
        break;
    }

    nw::g3d::ModelObj::InitArg model_arg(res_model);
    if (bounding_mode != 0)
        model_arg.EnableBounding();
    model_arg.ViewCount(num_view);

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

            nw::g3d::res::ResShaderAssign* res_shader_assign = material.getMaterialObj()->GetResource()->GetShaderAssign();
            sead::SafeString shader_archive_name = (res_shader_assign && res_shader_assign->GetShaderArchiveName())
                                                        ? res_shader_assign->GetShaderArchiveName()
                                                        : sead::SafeString::cEmptyString;

            // TODO

            if (shader_archive)
            {
                // ...
            }

            // ...
        }
    }
    sead::Graphics::instance()->unlockDrawContext();

    sead::Graphics::instance()->lockDrawContext();
    {
        mpMaterial.allocBuffer(mModelEx.GetMaterialCount(), heap);
        for (sead::Buffer<MaterialEx*>::iterator it = mpMaterial.begin(), it_end = mpMaterial.end(); it != it_end; ++it)
            *it = new (heap) MaterialEx(mModelEx.GetMaterial(it.getIndex()));

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

        if (mBoundingFlag.isOn(1))
        {
            createViewShapes_(num_view, heap);
            updateBounding_();
        }
    }
    sead::Graphics::instance()->unlockDrawContext();

    LightMapMgr::instance()->setRenderObjLightMap(*this, false);
    mMaterialNoDL = false;

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

s32 RenderObjEx::sortShapeRenderInfoCmp(const ShapeRenderInfo* a, const ShapeRenderInfo* b)
{
    return a->priority - b->priority;
}

void RenderObjEx::activateMaterial(const agl::g3d::ModelShaderAssign& shader_assign, const nw::g3d::MaterialObj* p_material, const LightMap& light_map) const
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
                LightMapMgr::instance()->getLightMapMgr()
                    .getLightMap(idx_lghtmap)
                        .getTextureSampler()
                            .activate(shader_assign.getSamplerLocation(idx_sampler), 12 + i);
            }
        }
    }
}

void RenderObjEx::disableMaterialDL()
{
    mMaterialNoDL = true;
}
