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
