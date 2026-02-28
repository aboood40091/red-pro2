#include <enemy/Enemy.h>
#include <scroll/BgScrollMgr.h>

bool Enemy::ceilCheck(f32 pos_y, ActorCollisionCheck* p_cc)
{
    // true: The enemy is completely above the screen

    const f32 screen_top_world_pos = BgScrollMgr::instance()->getScreenTop(); // The World-space position of the screen top edge in this frame
    return screen_top_world_pos < pos_y + p_cc->getCenterOffsetY() - p_cc->getHalfSizeY();
}

void Enemy::normal_collcheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Enemy* p_en_self = sead::DynamicCast<Enemy>(cc_self->getOwner());
    if (p_en_self->mDeathInfo.isDead())
    {
        cc_self->disableCallback();
        return;
    }

    Actor* p_actor_other = sead::DynamicCast<Actor>(cc_other->getOwner());

    switch (p_actor_other->getActorType())
    {
    default:
        {
            if (!p_en_self->etcDamageCheck(cc_self, cc_other))
                return;
        }
        break;
    case cActorType_Enemy:
        {
            bool dead = false;
            if (p_en_self->enemyPreDamageCheck(&dead, cc_self, cc_other))
            {
                if (dead)
                    cc_self->disableCallback();
                return;
            }
            else if (!p_en_self->enemyDamageCheck(cc_self, cc_other))
            {
                p_en_self->vsEnemyHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorType_Player:
        {
            if (!p_en_self->mEnFlag.isOn(cEnFlag_NoCeilCheckPlayer) && ceilCheck(p_en_self->mPos.y, cc_self))
                return;

            if (!p_en_self->playerDamageCheck(cc_self, cc_other))
            {
                if (cc_other->getKind() == ActorCollisionCheck::cKind_PlayerAttack)
                    return;

                s32 player_no = p_actor_other->getPlayerNo();
                if (!(0 <= player_no && player_no < 4))
                    return;

                if (p_en_self->mNoHitPlayerTimer[player_no] != 0)
                    return;

                p_en_self->mNoHitPlayerTimer[player_no] = cNoHitPlayerTimerDefault;

                p_en_self->vsPlayerHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorType_Yoshi:
        {
            s32 player_no = p_actor_other->getPlayerNo();
            if (!(0 <= player_no && player_no < 4))
                return;

            if (cc_other->getAttack() == ActorCollisionCheck::cAttack_YoshiEat)
            {
                p_en_self->hitYoshiEat(cc_self, cc_other);
                return;
            }

            if (ceilCheck(p_en_self->mPos.y, cc_self))
                return;

            if (!p_en_self->yoshiDamageCheck(cc_self, cc_other))
            {
                if (p_en_self->mNoHitPlayerTimer[player_no] != 0)
                    return;

                p_en_self->mNoHitPlayerTimer[player_no] = cNoHitPlayerTimerDefault;

                p_en_self->vsYoshiHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorType_ChibiYoshi:
        {
            if (ceilCheck(p_en_self->mPos.y, cc_self))
                return;

            if (!p_en_self->chibiYoshiDamageCheck(cc_self, cc_other))
            {
                if (cc_other->getAttack() != ActorCollisionCheck::cAttack_None)
                    return;

                p_en_self->vsChibiYoshiHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorType_Generic:
        {
            if (!p_en_self->etcDamageCheck(cc_self, cc_other))
                return;
        }
        break;
    }

    p_en_self->_187c = 1;
    cc_self->disableCallback();
}

void Enemy::changeState(const StateID& state_id)
{
    if (mStateMgr.isSubState())
    {
        mStateMgr.returnState();
        mStateMgr.replaceState(state_id);
    }
    else
    {
        mStateMgr.changeState(state_id);
    }
}

const f32 Enemy::cDieFallInitSpeedX[] = { 1.5f, -1.5f };
const f32 Enemy::cFumiJumpSpeed = 0.2815f;
const f32 Enemy::cDefaultGravity = -0.1875f;
const f32 Enemy::cDefaultMaxFallSpeed = -4.0f;
const Angle Enemy::cBaseAngleY[] = { 0x20000000, -0x20000000 };
const s8 Enemy::cEnMuki[] = { 1, -1 };
