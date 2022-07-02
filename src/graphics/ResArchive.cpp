#include <graphics/ResArchive.h>
#include <graphics/ShaderHolder.h>
#include <root/ResMgr.h>

#include <g3d/aglShaderUtilG3D.h>
#include <gfx/seadGraphics.h>
#include <math/seadMathCalcCommon.h>

ResArchive::ResArchive()
    : mResFile(NULL)
    , mShaderArchive()
    , _1c(0)
{
}

ResArchive::~ResArchive()
{
    if (mResFile)
        destroy();
}

void ResArchive::destroy()
{
    for (s32 i = 0; i < mResFile->GetModelCount(); i++)
        if (mShaderArchive[i].obj)
            mShaderArchive[i].obj->destroy();

    mResFile->Cleanup();
    mResFile = NULL;
}

void ResArchive::load(
    sead::ArchiveRes* archive, const sead::SafeString& filename,
    const nw::g3d::res::ResFile* tex_res_file, sead::Heap* heap
)
{
    mResFile = nw::g3d::res::ResFile::ResCast(
        ResMgr::instance()->getFileFromArchiveRes(
            archive, sead::FormatFixedSafeString<260>("%s.bfres", filename.cstr())
        )
    );

    sead::Graphics::instance()->lockDrawContext();
    {
        mResFile->Setup();
    }
    sead::Graphics::instance()->unlockDrawContext();

    if (tex_res_file)
        mResFile->Bind(tex_res_file, 1);

    s32 num_model = mResFile->GetModelCount();
    if (!mShaderArchive.tryAllocBuffer(num_model, heap))
        return;

    for (s32 idx_model = 0; idx_model < num_model; idx_model++)
    {
        agl::ShaderProgramArchive* shader_program_archive = new (heap) agl::ShaderProgramArchive;

        nw::g3d::res::ResModel* res_model = mResFile->GetModel(idx_model);
        sead::SafeString model_name(res_model->GetName());

        bool is_local = false;

        for (s32 idx_material = 0; idx_material < res_model->GetMaterialCount(); idx_material++)
        {
            nw::g3d::res::ResMaterial* res_material = res_model->GetMaterial(idx_material);
            sead::SafeString material_name(res_material->GetName());
            sead::SafeString shader_archive_name(res_material->GetShaderAssign()->GetShaderArchiveName());

            bool match = shader_archive_name.isEmpty() ||
                         shader_archive_name.isEqual(model_name) ||
                         shader_archive_name.isEqual(material_name); // Why material name?? It literally uses the model name below tho????

            if (match)
            {
                is_local = true;
            }
            else
            {
                agl::ShaderProgramArchive* g_shader_program_archive = ShaderHolder::instance()->getGlobalShaderArchive(shader_archive_name);
                agl::g3d::ShaderUtilG3D::setMatBlockAndShaderParamOffs(mResFile, g_shader_program_archive, "Mat");
            }
        }

        if (!is_local)
        {
            mShaderArchive[idx_model].obj = NULL;
            // They forgot to free "shader_program_archive"...
        }
        else
        {
            const agl::ResBinaryShaderArchiveData* res_binary_shader_archive = static_cast<agl::ResBinaryShaderArchiveData*>(
                ResMgr::instance()->getFileFromArchiveRes(
                    archive, sead::FormatFixedSafeString<260>("%s.sharcfb", model_name.cstr()) // <---- Uses model name
                )
            );

            mShaderArchive[idx_model].obj = shader_program_archive;
            mShaderArchive[idx_model].res_binary_archive = res_binary_shader_archive;
            mShaderArchive[idx_model].res_archive = NULL;

            shader_program_archive->createWithOption(res_binary_shader_archive, NULL, 0, heap);

            sead::Graphics::instance()->lockDrawContext();
            {
                shader_program_archive->setUp();
            }
            sead::Graphics::instance()->unlockDrawContext();

            mShaderArchive[idx_model].initialized = true;

            agl::g3d::ShaderUtilG3D::setMatBlockAndShaderParamOffs(mResFile, shader_program_archive, "Mat");
        }
    }
}

agl::ShaderProgramArchive* ResArchive::getShaderProgramArchive(s32 idx_model) const
{
    return mShaderArchive[idx_model].obj;
}
