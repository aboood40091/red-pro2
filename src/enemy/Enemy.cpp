#include <effect/EffectCreateUtil.h>
#include <enemy/Enemy.h>
#include <game/CourseTask.h>
#include <game/Quake.h>
#include <game/SubjectMgr.h>
#include <map_obj/ChibiYoshiAwa.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scroll/BgScrollMgr.h>

Enemy::Enemy(const ActorCreateParam& param)
    : ActorMultiState(param)
    , mIceMgr(this)
    , mChibiYoshiAwaData(this)
    , mFumiProc(this, NonUniqueFumiCheck::instance())
    , mStateTimer(0)
    , mStateSubTimer(0)
    , _1870(0)
    , mDieFallDirection(0)
    , mPreIceDirection(0)
    , mIsDamageFrame(false)
    , mIsSpinFumiFrame(false)
    , _187e(8)
{
    mGravity = ENEMY_DEFAULT_GRAVITY;
    mSpeedMax.set(0.0f, ENEMY_DEFAULT_MAX_FALL_SPEED, 0.0f);

    setKind(cActorKind_Enemy);

    mpChibiYoshiAwaData = &mChibiYoshiAwaData;
}

bool Enemy::preExecute_()
{
    if (!ActorCollision::preExecute_())
        return false;

    if (!mManualDeletedFlag && !isState(StateID_Ice) && isQuakeDamage())
    {
        if (Quake::instance()->getFlag() & Quake::cTypeFlag_Normal)
        {
            if (checkDispIn())
                setDeathInfo_Quake(cQuakeDeathType_NormalQuake);
        }
        else if (Quake::instance()->getFlag() & Quake::cTypeFlag_Big)
        {
            if (checkDispIn())
                setDeathInfo_Quake(cQuakeDeathType_BigQuake);
        }
        else if (Quake::instance()->getFlag() & Quake::cTypeFlag_Small)
        {
            setQuakeJump();
        }
    }

    if (mIsDamageFrame)
    {
        if (mIsSpinFumiFrame)
            SubjectMgr::instance()->onEnSpinFumi();

        SubjectMgr::instance()->onAcDamage();
    }
    mIsDamageFrame = false;
    mIsSpinFumiFrame = false;

    if (mDeathInfo.mIsDead)
    {
        if (!mManualDeletedFlag)
        {
            mManualDeletedFlag = true;
            setNicePoint_Death();
            changeState(*mDeathInfo.mArg.p_state_id);
        }

        SubjectMgr::instance()->onEnDeath(_187e);

        mDeathInfo.mIsDead = false;
    }
    else
    {
        if (mStateTimer)
            mStateTimer--;

        if (mStateSubTimer)
            mStateSubTimer--;

        mPlayerNoHitTimer.update();
    }
    return true;
}

void Enemy::setNicePoint_Death()
{
    s32 player_no = mDeathInfo.mArg.player_no;
    if (0 <= player_no && player_no < cPlayerNum)
        CourseTask::instance()->incEnemyDown(player_no);
}

void Enemy::blockHitInit_()
{
    hitdamageEffect(getPos2D());
    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

    static const f32 c_die_fall_init_speed_y = 3.0f;

    static const sead::Vector2f c_die_fall_init_speed[cDirType_NumX] = {
        sead::Vector2f( ENEMY_DIE_FALL_INIT_SPEED_X, c_die_fall_init_speed_y),
        sead::Vector2f(-ENEMY_DIE_FALL_INIT_SPEED_X, c_die_fall_init_speed_y)
    };

    ENEMY_MAKE_DEATH_INFO_ARG_FALL(arg);
    arg.speed = c_die_fall_init_speed[mBlockHitDirection];
    arg.max_fall_speed = ENEMY_DEFAULT_MAX_FALL_SPEED;
    arg.gravity = ENEMY_DEFAULT_GRAVITY;
    arg.direction = mBlockHitDirection;
    arg.player_no = mPlayerNo;
    mDeathInfo.kill(arg);
}

bool Enemy::area_XY_check(f32 x, f32 y)
{
    for (s32 i = 0; i < cPlayerNum; i++)
    {
        PlayerObject* p_player_obj = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player_obj != nullptr && PlayerMgr::instance()->isPlayerActive(i))
        {
            const sead::Vector3f& player_pos = p_player_obj->getPos();
            if (sead::Mathf::abs(player_pos.x - mPos.x) < x && sead::Mathf::abs(player_pos.y - mPos.y) < y)
                return true;
        }
    }
    return false;
}

bool Enemy::lineBoundaryCheck()
{
    // Content stripped in NSMBU
    return false;
}

bool Enemy::setDamage(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    PlayerBase* p_player_other = cc_other->getOwner<PlayerBase>();

    // NSMBUDX addition:
  //if (cc_other->getKind() == ActorCollisionCheck::cKind_PlayerUnk)
  //    return false;

    return p_player_other->setNormalDamage(cc_self);
}

void Enemy::normal_collcheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Enemy* p_en_self = cc_self->getOwner<Enemy>();
    if (p_en_self->mDeathInfo.isDead())
    {
        cc_self->disableCallback();
        return;
    }

    Actor* p_actor_other = cc_other->getOwner<Actor>();

    switch (p_actor_other->getKind())
    {
    default:
        {
            if (!p_en_self->etcDamageCheck(cc_self, cc_other))
                return;
        }
        break;
    case cActorKind_Enemy:
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
    case cActorKind_Player:
        {
            if (!p_en_self->mEnFlag.isOn(cEnFlag_NoCeilCheckPlayer) && ceilCheck(p_en_self->mPos.y, cc_self))
                return;

            if (!p_en_self->playerDamageCheck(cc_self, cc_other))
            {
                if (cc_other->getKind() == ActorCollisionCheck::cKind_PlayerAttack)
                    return;

                s32 player_no = p_actor_other->getPlayerNo();
                if (!(0 <= player_no && player_no < cPlayerNum))
                    return;

                if (!p_en_self->mPlayerNoHitTimer.isOver(player_no))
                    return;

                p_en_self->mPlayerNoHitTimer.reset(player_no, cNoHitPlayerTimerDefault);

                p_en_self->vsPlayerHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorKind_Yoshi:
        {
            s32 player_no = p_actor_other->getPlayerNo();
            if (!(0 <= player_no && player_no < cPlayerNum))
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
                if (!p_en_self->mPlayerNoHitTimer.isOver(player_no))
                    return;

                p_en_self->mPlayerNoHitTimer.reset(player_no, cNoHitPlayerTimerDefault);

                p_en_self->vsYoshiHitCheck_Normal(cc_self, cc_other);
                return;
            }
        }
        break;
    case cActorKind_ChibiYoshi:
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
    case cActorKind_Generic:
        {
            if (!p_en_self->etcDamageCheck(cc_self, cc_other))
                return;
        }
        break;
    }

    p_en_self->mIsDamageFrame = true;
    cc_self->disableCallback();
}

bool Enemy::ceilCheck(f32 pos_y, ActorCollisionCheck* p_cc)
{
    // true: The enemy is completely above the screen

    const f32 screen_top_world_pos = BgScrollMgr::instance()->getScreenTop(); // The World-space position of the screen top edge in this frame
    return screen_top_world_pos < pos_y + p_cc->getCenterOffsetY() - p_cc->getHalfSizeY();
}

void Enemy::bound(f32 eps_y, f32 scale_x, f32 scale_y)
{
    static const f32 eps_x = 1.0f / 16;

    if (!mBgCheckObj.checkFoot())
        return;

    if (scale_x < 1.0f)
    {
        mSpeed.x *= scale_x;
        if (sead::Mathf::abs(mSpeed.x) < eps_x)
            mSpeed.x = 0.0f;
    }

    if (mSpeed.y < 0.0f)
    {
        mSpeed.y = -mSpeed.y;
        mSpeed.y *= scale_y;
        if (mSpeed.y < eps_y)
            mSpeed.y = 0.0f;
    }
}

bool Enemy::enemyDamageCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Shell)
        if (hitCallback_Shell(cc_self, cc_other))
            return true;

    return false;
}

bool Enemy::playerDamageCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Star && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Star))
        if (hitCallback_Star(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_HipAttack && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_HipAttack))
    {
        if (cc_other->getOwner<PlayerBase>()->isMameAction())
            return false;

        if (hitCallback_HipAttk(cc_self, cc_other))
            return true;
    }

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Slip && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Slip))
        if (hitCallback_Slip(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_PenguinSlip && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_PenguinSlip))
    {
        if (mEnFlag.isOn(cEnFlag_9))
            return false;

        if (hitCallback_PenguinSlide(cc_self, cc_other))
            return true;
    }

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_SpinFall && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_SpinFall))
        if (hitCallback_Spin(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Cannon && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Cannon))
        if (hitCallback_Cannon(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_NetPunch && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_NetPunch))
        if (hitCallback_WireNet(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Unk25 && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Unk25))
        if (hitCallback_AttackUnk25(cc_self, cc_other))
            return true;

    return false;
}

bool Enemy::enemyPreDamageCheck(bool* p_dead, ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Unk27)
        if (hitCallback_AttackUnk27(p_dead, cc_self, cc_other))
            return true;

    return false;
}

void Enemy::hitYoshiEat(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
}

bool Enemy::yoshiDamageCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Star && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Star))
        if (hitCallback_Star(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_HipAttack && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_HipAttack))
    {
        if (hitCallback_YoshiHipAttk(cc_self, cc_other))
        {
            s32 player_no = cc_other->getOwner()->getPlayerNo();
            Enemy* p_en_self = static_cast<Enemy*>(cc_self->getOwner());
            p_en_self->mPlayerNoHitTimer.reset(player_no, cNoHitPlayerTimerDefault);
            return true;
        }
    }

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Slip && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Slip))
        if (hitCallback_Slip(cc_self, cc_other))
            return true;

    return false;
}

bool Enemy::chibiYoshiDamageCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Star && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Star))
        if (hitCallback_ChibiYoshiStar(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Unk24 && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_Unk24))
        if (hitCallback_ChibiYoshiUnk(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_ChibiYoshiLight && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_ChibiYoshiLight))
        if (hitCallback_ChibiYoshiLight(cc_self, cc_other))
            return true;

    return false;
}

bool Enemy::etcDamageCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Shell)
        if (hitCallback_Shell(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_FireBall && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_FireBall))
        if (hitCallback_Fire(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_YoshiFire && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_YoshiFire))
        if (hitCallback_YoshiFire(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Explode)
        if (hitCallback_Fire(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_IceBall && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_IceBall))
        if (hitCallback_Ice(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_YoshiIce && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_YoshiIce))
        if (hitCallback_Ice(cc_self, cc_other))
            return true;

    if (cc_other->getAttack() == ActorCollisionCheck::cAttack_YoshiBullet && cc_self->hasDamage(ActorCollisionCheck::cDamageFrom_YoshiBullet))
        if (hitCallback_YoshiBullet(cc_self, cc_other))
            return true;

    return false;
}

void Enemy::vsEnemyHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
}

void Enemy::vsPlayerHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    // NSMBUDX addition:
  //if (cc_other->getKind() == ActorCollisionCheck::cKind_PlayerUnk)
  //    return;

    setDamage(cc_self, cc_other);
}

void Enemy::vsYoshiHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Enemy::vsPlayerHitCheck_Normal(cc_self, cc_other);
}

void Enemy::vsChibiYoshiHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
}

void Enemy::iceballInvalid(ActorCollisionCheck* cc_other)
{
    Actor* p_iceball = cc_other->getOwner();

    GameAudio::getAudioObjMap()->startSound("SE_OBJ_PNGN_ICEBALL_DISAPP", p_iceball->getPos());

    sead::Vector3f effect_pos(p_iceball->getPos2D(), EFFECT_Z_POS_DEFAULT);
    EffectCreateUtil::createEffect(RP_Cmn_IceballHit, &effect_pos);
}

FumiType Enemy::fumiCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other, FumiSeType se_type)
{
    PlayerBase* p_player_other = static_cast<PlayerBase*>(cc_other->getOwner());

    const FumiType type = mFumiProc.operate(cc_self, cc_other);
    if (type == cFumiType_Fumi)
    {
        if (!p_player_other->setFumiSubjectCoinEndClear())
        {
            if (p_player_other->getKind() == cActorKind_Player)
            {
                if (se_type == cFumiSeType_Normal)
                {
                    fumiSE(p_player_other);
                    fumiEffect(p_player_other);
                }
                else if (se_type == cFumiSeType_Step)
                {
                    fumistepSE();
                }
                fumiJumpSet(p_player_other);
                fumiScoreSet(p_player_other);
            }
            else
            {
                if (se_type == cFumiSeType_Normal)
                {
                    yoshifumiSE(p_player_other);
                //yoshifumiEffect(p_player_other);
                }
                else if (se_type == cFumiSeType_Step)
                {
                    yoshifumistepSE();
                }
                yoshiFumiJumpSet(p_player_other);
                yoshiFumiScoreSet(p_player_other);
            }
        }
    }
    else if (type == cFumiType_MameFumi)
    {
        if (!p_player_other->setFumiSubjectCoinEndClear())
        {
            mameFumiJumpSet(p_player_other);
            mamefumiSE();
            mamefumiEffect(p_player_other);
        }
    }
    else if (type == cFumiType_SpinFumi)
    {
        if (!p_player_other->setFumiSubjectCoinEndClear())
        {
            if (se_type == cFumiSeType_Normal)
            {
                spinfumiSE(p_player_other);
                spinfumiEffect(p_player_other);
            }
            else if (se_type == cFumiSeType_Step)
            {
                spinfumistepSE();
            }
            spinFumiJumpSet(p_player_other);
            spinFumiScoreSet(p_player_other);
        }
    }
    return type;
}

void Enemy::spinfumiEffect(Actor* p_player)
{
    sead::Vector3f effect_pos(p_player->getPos2D(), EFFECT_Z_POS_DEFAULT);
    EffectCreateUtil::createEffect(RP_Cmn_HitNormal, &effect_pos);
}

void Enemy::spinFumiScoreSet(Actor* p_player)
{
    mIsDamageFrame = true;
    mIsSpinFumiFrame = true;
    fumiScoreSet(p_player);
}

void Enemy::playerFumiJump(Actor* p_player, f32 speed_y)
{
    PlayerBase* p_player_other = static_cast<PlayerBase*>(p_player);
    p_player_other->bouncePlayer1(speed_y, p_player_other->getSpeedF(), true, PlayerBase::cBounceType_Normal, PlayerBase::cJumpSe_High);
    p_player_other->setCcEnemyFumiRevExtend();
}

#define FUMI_JUMP_SPEED (PlayerObject::cJumpSpeed + ENEMY_FUMI_JUMP_SPEED)

void Enemy::fumiJumpSet(Actor* p_player)
{
    f32 speed_y = FUMI_JUMP_SPEED;

    // NSMBUDX addition:
  //PlayerBase* p_player_other = static_cast<PlayerBase*>(p_player);
  //if (p_player_other->getPlayerMode() == cPlayerMode_Penguin ||
  //    p_player_other->isKinopico() ||
  //    p_player_other->isTotten())
  //{
  //    if (p_player_other->isStatus(PlayerBase::cStatus_???))
  //        speed_y *= 0.5f;
  //}

    playerFumiJump(p_player, speed_y);
}

void Enemy::setFumiComboScore(Actor* p_player)
{
    s32 fumi_cnt = calcComboPlFumiCnt(p_player);
    if (fumi_cnt < 0)
        return;

    ScoreMgr::ScoreType fumi_score = ScoreMgr::ScoreType(fumi_cnt);

    sead::Vector3f score_pos = getCenterPos();
    score_pos.y = mPos.y + ScoreMgr::cScoreY;

    switch (mCombo.getType())
    {
    default:
        break;
    case Combo::cType_1:
        ScoreMgr::instance()->ScoreSet(score_pos, fumi_score, p_player->getPlayerNo());
        break;
    case Combo::cType_2:
        ScoreMgr::instance()->ScoreSet2(score_pos, fumi_score, p_player->getPlayerNo());
        break;
    }
}

s32 Enemy::calcComboPlFumiCnt(Actor* p_player)
{
    mIsDamageFrame = true;

    if (SubjectMgr::instance()->isFumiScoreBySpinOnly() && !mIsSpinFumiFrame)
        return -1;

    return mCombo.calcPlFumiCnt(p_player);
}

void Enemy::fumiScoreSet(Actor* p_player)
{
    setFumiComboScore(p_player);
}

void Enemy::calcMdl_Base()
{
}

void Enemy::calcMdl_Normal()
{
    if (mIceMgr.hasIce())
        return;

    calcMdl_Base();
}

bool Enemy::vf1CC()
{
    return true;
}

void Enemy::yoshiFumiJumpSet(Actor* p_player)
{
    Enemy::fumiJumpSet(p_player);
}

void Enemy::yoshiFumiScoreSet(Actor* p_player)
{
    fumiScoreSet(p_player);
}

void Enemy::mameFumiJumpSet(Actor* p_player)
{
    f32 speed_y = FUMI_JUMP_SPEED * 0.8125f;
    if (mSpeed.y > 0.0f)
        speed_y += mSpeed.y * 0.2f;
    playerFumiJump(p_player, speed_y);
}

bool Enemy::checkComboClap(s32 combo_cnt)
{
    static const u8 c_clap_combo[Combo::cType_Num] = {
        ScoreMgr::cScoreType_Point_Num - 1,
        ScoreMgr::cScoreType_Point_Num - 1,
        ScoreMgr::cScoreType2_Point_Num - 1
    };
    return combo_cnt >= c_clap_combo[mCombo.getType()];
}

void Enemy::setFumiSound(const char* label)
{
    GameAudio::getAudioObjEmy()->startSound(label, getCenterPos());
}

void Enemy::setFumiSound(s32 combo_cnt, const GameAudio::SoundID combo_se[], u32 combo_max)
{
    if ((u32)combo_cnt >= combo_max)
        combo_cnt = combo_max - 1;

    if (checkComboClap(combo_cnt))
        GameAudio::setClapSE();

    setFumiSound(combo_se[combo_cnt]);
}

void Enemy::setFumiSound(Actor* p_player, const GameAudio::SoundID combo_se[], u32 combo_max)
{
    setFumiSound(static_cast<PlayerBase*>(p_player)->getTreadCount(), combo_se, combo_max);
}

void Enemy::fumiSE(Actor* p_player)
{
    static const GameAudio::SoundID cs_combo_se[] = {
        "SE_EMY_FUMU_1",
        "SE_EMY_FUMU_2",
        "SE_EMY_FUMU_3",
        "SE_EMY_FUMU_4",
        "SE_EMY_FUMU_5",
        "SE_EMY_FUMU_6",
        "SE_EMY_FUMU_7",
        "SE_EMY_FUMU_7",
        "SE_EMY_FUMU_7"
    };
    static_assert((sizeof(cs_combo_se) / sizeof(GameAudio::SoundID)) == ScoreMgr::cScoreType_Base_Num);

    setFumiSound(p_player, cs_combo_se, ScoreMgr::cScoreType_Base_Num);
}

void Enemy::fumiEffect(Actor* p_player)
{
    PlayerBase* p_player_other = sead::DynamicCast<PlayerBase>(p_player);
    if (p_player_other != nullptr)
    {
        sead::Vector3f pos;
        p_player_other->getAnkleCenterPos(&pos);
        hitdamageEffect(pos);
    }
}

void Enemy::hitdamageEffect(const sead::Vector3f& pos)
{
    sead::Vector3f effect_pos = pos;
    effect_pos.z = EFFECT_Z_POS_DEFAULT;
    EffectCreateUtil::createEffect(RP_Cmn_HitNormal, &effect_pos);
}

void Enemy::spinfumiSE(Actor* p_player)
{
    static const GameAudio::SoundID cs_combo_se[] = {
        "SE_EMY_DOWN_SPIN_1",
        "SE_EMY_DOWN_SPIN_2",
        "SE_EMY_DOWN_SPIN_3",
        "SE_EMY_DOWN_SPIN_4",
        "SE_EMY_DOWN_SPIN_5",
        "SE_EMY_DOWN_SPIN_6",
        "SE_EMY_DOWN_SPIN_7",
        "SE_EMY_DOWN_SPIN_7",
        "SE_EMY_DOWN_SPIN_7"
    };
    static_assert((sizeof(cs_combo_se) / sizeof(GameAudio::SoundID)) == ScoreMgr::cScoreType_Base_Num);

    setFumiSound(p_player, cs_combo_se, ScoreMgr::cScoreType_Base_Num);
}

void Enemy::mamefumiSE()
{
    mamefumistepSE();
}

void Enemy::mamefumiEffect(Actor* p_player)
{
    (void)p_player;
}

void Enemy::yoshifumiSE(Actor* p_player)
{
    static const GameAudio::SoundID cs_combo_se[] = {
        "SE_EMY_YOSHI_FUMU_1",
        "SE_EMY_YOSHI_FUMU_2",
        "SE_EMY_YOSHI_FUMU_3",
        "SE_EMY_YOSHI_FUMU_4",
        "SE_EMY_YOSHI_FUMU_5",
        "SE_EMY_YOSHI_FUMU_6",
        "SE_EMY_YOSHI_FUMU_7",
        "SE_EMY_YOSHI_FUMU_7",
        "SE_EMY_YOSHI_FUMU_7"
    };
    static_assert((sizeof(cs_combo_se) / sizeof(GameAudio::SoundID)) == ScoreMgr::cScoreType_Base_Num);

    setFumiSound(p_player, cs_combo_se, ScoreMgr::cScoreType_Base_Num);
}

void Enemy::hipatkEffect(const sead::Vector3f& effect_pos)
{
    EffectCreateUtil::createEffect(RP_HipDropHit_0, &effect_pos);
}

void Enemy::setQuakeJump()
{
    mSpeed.y += 2.0f;
}

bool Enemy::checkDispIn()
{
    const BgScrollMgr& bg_scroll_mgr = *BgScrollMgr::instance();

    const f32 center_x = getCenterX();
    const f32 screen_left = bg_scroll_mgr.getScreenLeft();
    if (center_x < screen_left)
        return false;
    if (center_x > screen_left + bg_scroll_mgr.getScreenWidth())
        return false;

    const f32 center_y = getCenterY();
    const f32 screen_top = bg_scroll_mgr.getScreenTop();
    if (center_y > screen_top)
        return false;
    if (center_y < screen_top - bg_scroll_mgr.getScreenHeight())
        return false;

    return true;
}

void Enemy::setAwaHit(Actor* p_awa)
{
    if (isDead() || isState(StateID_Ice) || checkEat())
        static_cast<ChibiYoshiAwa*>(p_awa)->setBreak();
}

void Enemy::awaCatchMove(Actor* p_awa)
{
    if (isDead() || isState(StateID_Ice) || checkEat())
        static_cast<ChibiYoshiAwa*>(p_awa)->setBreak();
}

void Enemy::setAwaCatchEnd(Actor* p_awa)
{
    if (isDead() || isState(StateID_Ice) || checkEat())
        static_cast<ChibiYoshiAwa*>(p_awa)->setBreak();
    else
        setDeathInfo_Awa(p_awa);
}

void Enemy::setAwaInvalid(Actor* p_awa)
{
}

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

const f32 Enemy::cDieFallInitSpeedX[] = { ENEMY_DIE_FALL_INIT_SPEED_X, -ENEMY_DIE_FALL_INIT_SPEED_X };
const f32 Enemy::cFumiJumpSpeed = ENEMY_FUMI_JUMP_SPEED;
const f32 Enemy::cDefaultGravity = ENEMY_DEFAULT_GRAVITY;
const f32 Enemy::cDieFallBoundSpeedY = 3.0f;
const f32 Enemy::cDefaultMaxFallSpeed = ENEMY_DEFAULT_MAX_FALL_SPEED;
const f32 Enemy::cDefaultMaxSpeedF = 4.0f;
const f32 Enemy::cDefaultMaxSpeedY = ENEMY_DEFAULT_MAX_FALL_SPEED;
const f32 Enemy::cWaterGravity = ENEMY_DEFAULT_GRAVITY / 3;
const f32 Enemy::cWaterBoundSpeedY = 1.5f;
const f32 Enemy::cWaterMaxFallSpeed = -1.5f;
const f32 Enemy::cWaterRollDecRate = 0.5f;

const Angle Enemy::cBaseAngleY[] = { 0x20000000, -0x20000000 };
const Angle Enemy::cBaseAngleYAdd[] = { 0x4000000, -0x4000000 };
const f32 Enemy::cDeadNetSpeedX[] = { getDeadNetSpeedX(), -getDeadNetSpeedX() };
const s8 Enemy::cEnMuki[] = { 1, -1 };
