#include <actor/ActorMgr.h>
#include <actor/AttentionLookat.h>
#include <actor/AttentionMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerFaceAngleUtil.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <utility/MathUtil.h>

PlayerBase* PlayerBase::searchPlayerAttention_(const sead::Vector2f& src_pos)
{
    PlayerBase* p_player_ret = nullptr;
    f32 dist_sq_min = sead::MathCalcCommon<u16>::maxNumber();

    for (s32 i = 0; i < 4; i++)
    {
        if (!PlayerMgr::instance()->isAcceptQuake(i))
            continue;

        PlayerObject* p_player = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player == nullptr)
            continue;

        f32 target_x = p_player->getLookatPos().x;
        f32 target_y = p_player->getLookatPos().y;

        f32 dist_sq = sead::Vector2f(target_x, target_y).squaredDistance(src_pos);
        if (dist_sq < dist_sq_min)
        {
            p_player_ret = p_player;
            dist_sq_min = dist_sq;
        }
    }

    return p_player_ret;
}

static const Angle cMaxStep_1   = 0x08000000;
static const Angle cMaxStep_2   = 0x06000000;
static const Angle cMaxStep_3   = 0x01800000;
static const Angle cMinStep     = 0x00400000;

bool PlayerBase::calcHeadAttentionAngle_(const sead::Vector2f& target_pos, sead::BitFlag32 flag, Angle max_angle_y)
{
    bool ret = false;

    Angle target_z = 0;
    Angle target_y = 0;

    f32 src_x = getLookatPos().x;
    f32 src_y = getLookatPos().y;

    const sead::Vector3f distance(
        target_pos.x - src_x,
        target_pos.y - src_y,
        8.0f
    );

    Angle angle_z = -sead::Mathf::atan2Idx(
        distance.y,
        sead::Mathf::sqrt(
            sead::Mathf::square(distance.x) +
            sead::Mathf::square(distance.z)
        )
    );

    Angle max_angle_z = PlayerFaceAngleUtil::cMaxAngleZ_1;
    Angle min_angle_z = PlayerFaceAngleUtil::cMinAngleZ_1;
    if (flag.isOnBit(3))
    {
        max_angle_z = PlayerFaceAngleUtil::cMaxAngleZ_2;
        min_angle_z = PlayerFaceAngleUtil::cMinAngleZ_2;
    }

    if (angle_z < min_angle_z)
        angle_z = min_angle_z;
    else if (angle_z > max_angle_z)
        angle_z = max_angle_z;

    Angle angle_y = -(sead::Mathf::atan2Idx(
        distance.x,
        distance.z
    ) - mAngle.y());

    if (flag.isOnBit(0))
    {
        mpModelBaseMgr->changeFaceAngleOverrideFlag(PlayerModelBase::cFaceAngleOverrideFlag_Y, true);
        mpModelBaseMgr->changeFaceAngleOverrideFlag(PlayerModelBase::cFaceAngleOverrideFlag_Z, true);

        ret = true;

        Angle min_angle_y = -max_angle_y;

        target_y = angle_y;
        if (target_y < min_angle_y)
            target_y = min_angle_y;
        else if (target_y > max_angle_y)
            target_y = max_angle_y;

        target_z = angle_z * sead::Mathf::cosIdx(s32(MathUtil::absAngle(angle_y) * 0.5f));
    }
    else
    {
        if (MathUtil::absAngle(angle_y) < sead::Mathf::deg2idx(90))
        {
            mpModelBaseMgr->changeFaceAngleOverrideFlag(PlayerModelBase::cFaceAngleOverrideFlag_Y, false);
            mpModelBaseMgr->changeFaceAngleOverrideFlag(PlayerModelBase::cFaceAngleOverrideFlag_Z, true);

            ret = true;

            target_z = angle_z;
        }
    }
    if (ret)
    {
        Angle3 head_angle(
            0,
            mpModelBaseMgr->getFaceAngleOverride().y(),
            mpModelBaseMgr->getFaceAngleOverride().z()
        );
        head_angle.y().chaseAngle(target_y, 0.2f, cMaxStep_2, cMinStep);
        if (flag.isOnBit(1))
            head_angle.z().chaseAngle(target_z, 0.2f, cMaxStep_3, cMinStep);
        else if (flag.isOnBit(2))
            head_angle.z().chaseAngle(target_z, 0.5f, cMaxStep_1, cMinStep);
        else
            head_angle.z().chaseAngle(target_z, 0.2f, cMaxStep_2, cMinStep);
        mpModelBaseMgr->setFaceAngleOverride(head_angle);
    }
    return ret;
}

void PlayerBase::calcHeadAttentionAngle()
{
    if (isStatus(cStatus_3))
        return;

    if (isChange())
        return;

    bool reset = false;
    if (isLiftUp() || isStatus(cStatus_71))
        reset = true;

    if (!reset && !((mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Body) >> PlayerModelBase::cAnmFlagBit_7 & 1) ||
                    (mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Body) >> PlayerModelBase::cAnmFlagBit_8 & 1) ||
                    (mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Body) >> PlayerModelBase::cAnmFlagBit_9 & 1)))
        reset = true;

    if (!reset)
    {
        if (!isStatus(cStatus_155))
        {
            f32 src_x = getLookatPos().x;
            f32 src_y = getLookatPos().y;
            sead::Vector2f src_pos(src_x, src_y);
            if (mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Body) >> PlayerModelBase::cAnmFlagBit_8 & 1)
            {
                if (isStatus(cStatus_156))
                {
                    PlayerBase* p_player_lookat = searchPlayerAttention_(src_pos);
                    if (p_player_lookat != nullptr)
                    {
                        f32 target_x = p_player_lookat->getLookatPos().x;
                        f32 target_y = p_player_lookat->getLookatPos().y;
                        sead::Vector2f target_pos(target_x, target_y);
                        sead::BitFlag32 attention_flag(1 << 0);
                        if (calcHeadAttentionAngle_(target_pos, attention_flag, 0x20000000))
                            return;
                    }
                }
            }
            else if (mpModelBaseMgr->getAnmFlag(PlayerModelBase::cAnmFlagType_Body) >> PlayerModelBase::cAnmFlagBit_7 & 1)
            {
                const AttentionLookat* p_attention_lookat = AttentionMgr::instance()->search(*this, src_pos);
                if (p_attention_lookat != nullptr)
                {
                    ActorBase* p_actor_lookat = ActorMgr::instance()->getActorPtr(p_attention_lookat->getOwnerID());
                    if (p_actor_lookat != nullptr)
                    {
                        if (calcHeadAttentionAngle_(p_attention_lookat->getPos(), p_attention_lookat->getFlag(), PlayerFaceAngleUtil::cMaxAngleY))
                            return;
                    }
                }
            }
        }

        Angle3 head_angle(
            0,
            mpModelBaseMgr->getFaceAngleOverride().y(),
            mpModelBaseMgr->getFaceAngleOverride().z()
        );
        head_angle.y().chaseAngle(0, 0.2f, cMaxStep_2, cMinStep);
        head_angle.z().chaseAngle(0, 0.2f, cMaxStep_2, cMinStep);
        mpModelBaseMgr->setFaceAngleOverride(head_angle);

        if (head_angle.z() == 0 && head_angle.y() == 0)
        {
            mpModelBaseMgr->resetFaceAngleOverride();
            mpModelBaseMgr->resetFaceAngleOverrideFlag();
        }
    }
    else
    {
        mpModelBaseMgr->resetFaceAngleOverride();
        mpModelBaseMgr->resetFaceAngleOverrideFlag();
    }
}
