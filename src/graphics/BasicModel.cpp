#include <graphics/BasicModel.h>
#include <graphics/ModelNW.h>

BasicModel::BasicModel(ModelNW* p_model, u32 skl_anim_num, u32 tex_anim_num, u32 shu_anim_num, u32 vis_anim_num, u32 sha_anim_num)
    : mpModel(p_model)
    , mpModelResource(nullptr)
{
    if (skl_anim_num > 0)
        mpSklAnim.setBuffer(skl_anim_num, p_model->getSklAnimBuffer());

    if (tex_anim_num > 0)
        mpTexAnim.setBuffer(tex_anim_num, p_model->getTexAnimBuffer());

    if (shu_anim_num > 0)
        mpShuAnim.setBuffer(shu_anim_num, p_model->getShuAnimBuffer());

    if (vis_anim_num > 0)
        mpVisAnim.setBuffer(vis_anim_num, p_model->getVisAnimBuffer());

    if (sha_anim_num > 0)
        mpShaAnim.setBuffer(sha_anim_num, p_model->getShaAnimBuffer());
}

void BasicModel::init(ModelResource* p_mdl_res, const sead::PtrArray<ModelResource>* p_anim_mdl_res_array, sead::Heap* heap)
{
    mpModelResource = p_mdl_res;

    if (mpSklAnim.isBufferReady())
    {
        for (sead::Buffer<SkeletalAnimation*>::iterator itr_anim = mpSklAnim.begin(), itr_anim_end = mpSklAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            SkeletalAnimation* anim = new (heap) SkeletalAnimation();
            anim->init(mpModel, p_mdl_res, p_anim_mdl_res_array, heap);
            mpModel->setSklAnim(itr_anim.getIndex(), anim);
            mpModel->setSklAnimBlendWeight(itr_anim.getIndex(), 1.0f);
            *itr_anim = anim;
        }
    }

    if (mpTexAnim.isBufferReady())
    {
        for (sead::Buffer<TexturePatternAnimation*>::iterator itr_anim = mpTexAnim.begin(), itr_anim_end = mpTexAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            TexturePatternAnimation* anim = new (heap) TexturePatternAnimation();
            anim->init(mpModel, p_mdl_res, p_anim_mdl_res_array, heap);
            mpModel->setTexAnim(itr_anim.getIndex(), anim);
            *itr_anim = anim;
        }
    }

    if (mpShuAnim.isBufferReady())
    {
        for (sead::Buffer<ShaderParamAnimation*>::iterator itr_anim = mpShuAnim.begin(), itr_anim_end = mpShuAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            ShaderParamAnimation* anim = new (heap) ShaderParamAnimation();
            anim->init(mpModel, p_mdl_res, p_anim_mdl_res_array, heap);
            mpModel->setShuAnim(itr_anim.getIndex(), anim);
            *itr_anim = anim;
        }
    }

    if (mpVisAnim.isBufferReady())
    {
        for (sead::Buffer<VisibilityAnimation*>::iterator itr_anim = mpVisAnim.begin(), itr_anim_end = mpVisAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            VisibilityAnimation* anim = new (heap) VisibilityAnimation();
            anim->init(mpModel, p_mdl_res, p_anim_mdl_res_array, heap);
            mpModel->setVisAnim(itr_anim.getIndex(), anim);
            *itr_anim = anim;
        }
    }

    if (mpShaAnim.isBufferReady())
    {
        for (sead::Buffer<ShapeAnimation*>::iterator itr_anim = mpShaAnim.begin(), itr_anim_end = mpShaAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            ShapeAnimation* anim = new (heap) ShapeAnimation();
            anim->init(mpModel, p_mdl_res, p_anim_mdl_res_array, heap);
            mpModel->setShaAnim(itr_anim.getIndex(), anim);
            *itr_anim = anim;
        }
    }
}

void BasicModel::playAnmFrameCtrl()
{
    if (mpSklAnim.isBufferReady())
    {
        for (sead::Buffer<SkeletalAnimation*>::iterator itr_anim = mpSklAnim.begin(), itr_anim_end = mpSklAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            (*itr_anim)->playFrameCtrl();
        }
    }

    if (mpTexAnim.isBufferReady())
    {
        for (sead::Buffer<TexturePatternAnimation*>::iterator itr_anim = mpTexAnim.begin(), itr_anim_end = mpTexAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            (*itr_anim)->playFrameCtrl();
        }
    }

    if (mpShuAnim.isBufferReady())
    {
        for (sead::Buffer<ShaderParamAnimation*>::iterator itr_anim = mpShuAnim.begin(), itr_anim_end = mpShuAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            (*itr_anim)->playFrameCtrl();
        }
    }

    if (mpVisAnim.isBufferReady())
    {
        for (sead::Buffer<VisibilityAnimation*>::iterator itr_anim = mpVisAnim.begin(), itr_anim_end = mpVisAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            (*itr_anim)->playFrameCtrl();
        }
    }

    if (mpShaAnim.isBufferReady())
    {
        for (sead::Buffer<ShapeAnimation*>::iterator itr_anim = mpShaAnim.begin(), itr_anim_end = mpShaAnim.end(); itr_anim != itr_anim_end; ++itr_anim)
        {
            (*itr_anim)->playFrameCtrl();
        }
    }
}

void BasicModel::calcMdl()
{
    mpModel->calcAnm();
    mpModel->calcMdl();
}
