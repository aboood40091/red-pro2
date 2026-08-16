#include <actor/ActorStatus.h>
#include <actor/ActorUtil.h>
#include <effect/EffectCreateUtil.h>
#include <enemy/Enemy.h>
#include <game/SubjectMgr.h>
#include <input/InputMgr.h>
#include <map/LayerID.h>
#include <map_obj/ActorCoinMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

bool Enemy::isDead() const
{
    if (mDeathInfo.isDead())
        return true;

    return mManualDeletedFlag;
}

void Enemy::setDeadMode(Actor* p_actor)
{
    if (isDead())
        return;

    if (isState(StateID_Ice) && mIceMgr.isDestroy())
        return;

    removeCollisionCheck();

    setDeathInfo_SpinFumi(p_actor);

    static const f32 cs_effect_offset_x[cDirType_NumX] = { -6.0f, 6.0f };
    sead::Vector3f effect_pos = getCenterPos();
    effect_pos.x += cs_effect_offset_x[mDeathInfo.mArg.direction];
    hitdamageEffect(effect_pos);

    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);
}

void Enemy::setDeathInfo_SpinFumi(Actor* p_player)
{
    setDeathInfo_Fall(
        ActorUtil::getTrgToSrcDir(*this, *p_player),
        p_player->getPlayerNo()
    );
}

void Enemy::cancelCarry()
{
    for (s32 i = 0; i < cPlayerNum; i++)
    {
        PlayerObject* p_player_obj = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player_obj != nullptr && p_player_obj->getCarryActorID() == mActorUniqueID)
        {
            p_player_obj->cancelCarry(this);
            break;
        }
    }
}

bool Enemy::hitCallback_Star(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    return setDeathInfo_Star(cc_self, cc_other);
}

bool Enemy::hitCallback_Slip(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    PlayerBase* p_player_other = sead::DynamicCast<PlayerBase>(p_actor_other);
    setDeathSound_Slip(p_player_other);

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getComboScore(Combo::calcPlComboCnt(p_actor_other))
    );
    return true;
}

void Enemy::setDeathSound_Slip(Actor* p_player)
{
    static const GameAudio::SoundID cs_combo_se[] = {
        "SE_EMY_DOWN_COMBO_1",
        "SE_EMY_DOWN_COMBO_2",
        "SE_EMY_DOWN_COMBO_3",
        "SE_EMY_DOWN_COMBO_4",
        "SE_EMY_DOWN_COMBO_5",
        "SE_EMY_DOWN_COMBO_6",
        "SE_EMY_DOWN_COMBO_7",
        "SE_EMY_DOWN_COMBO_7",
        "SE_EMY_DOWN_COMBO_7"
    };
    static_assert((sizeof(cs_combo_se) / sizeof(GameAudio::SoundID)) == ScoreMgr::cScoreType_Base_Num);

    setFumiSound(static_cast<PlayerBase*>(p_player)->getComboCount(), cs_combo_se, ScoreMgr::cScoreType_Base_Num);
}

bool Enemy::hitCallback_Spin(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    setDeathSound_HipAttk();
    hipatkEffect(sead::Vector3f(mPos.x, mPos.y, EFFECT_Z_POS_DEFAULT));

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getComboScore(calcComboPlFumiCnt(p_actor_other))
    );
    return true;
}

bool Enemy::hitCallback_WireNet(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

    static const sead::Vector2f c_die_fall_init_speed[cDirType_NumX] = {
        sead::Vector2f(cDeadNetSpeedX[cDirType_Right], ENEMY_DIE_FALL_INIT_SPEED_Y),
        sead::Vector2f(cDeadNetSpeedX[cDirType_Left ], ENEMY_DIE_FALL_INIT_SPEED_Y)
    };

    setDeathInfo_Fall(c_die_fall_init_speed, kill_dir, kill_player_no);
    return true;
}

void Enemy::setDeathInfo_Fall(const sead::Vector2f* speeds, DirType direction, s32 player_no, ScoreMgr::ScoreType score_type)
{
    ENEMY_MAKE_DEATH_INFO_ARG_FALL(arg);
    arg.speed = speeds[direction];
    arg.max_fall_speed = ENEMY_DEFAULT_MAX_FALL_SPEED;
    arg.gravity = cDieFallGravity;
    arg.score_type = score_type;
    arg.direction = direction;
    arg.player_no = player_no;
    mDeathInfo.kill(arg);
}

bool Enemy::hitCallback_HipAttk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    hipatkEffect(sead::Vector3f(mPos.x, mPos.y, EFFECT_Z_POS_DEFAULT));
    p_actor_other->slideComboSE(static_cast<PlayerBase*>(p_actor_other)->getTreadCount(), mCombo.isComboType2());

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getComboScore(calcComboPlFumiCnt(p_actor_other))
    );
    return true;
}

bool Enemy::hitCallback_YoshiHipAttk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();
    s32 kill_player_no = p_actor_other->getPlayerNo();

    ScoreMgr::ScoreType combo_score = mCombo.getComboScore(calcComboPlFumiCnt(p_actor_other));
    if (combo_score >= 0 && (0 <= kill_player_no && kill_player_no < cPlayerNum))
        ScoreMgr::instance()->ScoreSet(this, combo_score, kill_player_no);

    GameAudio::getAudioObjEmy()->startSound("SE_EMY_YOSHI_HPDP", mPos);

    setDeathInfo_YoshiFumi(p_actor_other);
    return true;
}

void Enemy::setDeathInfo_YoshiFumi(Actor* p_player)
{
    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_player);
    s32 kill_player_no = p_player->getPlayerNo();

    ENEMY_MAKE_DEATH_INFO_ARG_YOSHI_FUMI_NO_SCORE(arg);
    arg.speed.set(0.0f, 0.0f);
    arg.direction = kill_dir;
    arg.player_no = kill_player_no;
    mDeathInfo.kill(arg);
}

bool Enemy::hitCallback_PenguinSlide(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    return hitCallback_Slip(cc_self, cc_other);
}

bool Enemy::hitCallback_Cannon(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    p_actor_other->slideComboSE(static_cast<PlayerBase*>(p_actor_other)->getComboCount(), mCombo.isComboType2());

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getComboScore(Combo::calcPlComboCnt(p_actor_other))
    );
    return true;
}

bool Enemy::hitCallback_AttackUnk25(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    return hitCallback_Slip(cc_self, cc_other);
}

bool Enemy::hitCallback_Shell(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    ScoreMgr::ScoreType combo_score = ScoreMgr::cScoreType_Invalid;
    if (0 <= kill_player_no && kill_player_no < cPlayerNum)
    {
        p_actor_other->slideComboSE(p_actor_other->getComboCnt(), mCombo.isComboType2());

        p_actor_other->incComboCnt();
        combo_score = mCombo.getComboScore(p_actor_other->getComboCnt());
    }
    else
    {
        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);
    }
    setDeathInfo_Fall(kill_dir, kill_player_no, combo_score);
    return true;
}

bool Enemy::hitCallback_Fire(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();
    s32 kill_player_no = p_actor_other->getPlayerNo();

    DirType kill_dir = p_actor_other->getSpeedVec().x < 0.0f ? cDirType_Left : cDirType_Right;

    setDeathSound_Fire();

    createUpCoin(kill_dir);

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getDamageScore()
    );
    return true;
}

void Enemy::createUpCoin(DirType dir)
{
    ActorCoinMgr::UpCoinArg up_coin_arg = {
        getCenterPos(),
        dir,
        1,
        cLayerID_Layer1
    };
    ActorCoinMgr::instance()->createUpCoin(up_coin_arg);
}

bool Enemy::hitCallback_Ice(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (!mIceMgr.hasIce())
    {
        Actor* p_actor_other = cc_other->getOwner();
        mPreIceDirection = p_actor_other->getSpeedVec().x < 0.0f ? cDirType_Left : cDirType_Right;
        cancelCarry();
        mIceMgr.setPlayerNo(p_actor_other->getPlayerNo());
        mStateMgr.changeToSubState(StateID_Ice);
    }
    return true;
}

bool Enemy::hitCallback_YoshiBullet(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    setDeathSound_Fire();

    ActorCoinMgr::UpCoinArg up_coin_arg = {
        getCenterPos(),
        kill_dir,
        1,
        cLayerID_Layer1
    };
    ActorCoinMgr::instance()->createUpCoin(up_coin_arg);

    setDeathInfo_Fall(
        kill_dir, kill_player_no,
        mCombo.getDamageScore()
    );
    return true;
}

bool Enemy::hitCallback_YoshiFire(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    p_actor_other->slideComboSE(p_actor_other->getComboCnt(), mCombo.isComboType2());

    p_actor_other->incComboCnt();
    ScoreMgr::ScoreType combo_score = mCombo.getComboScore(p_actor_other->getComboCnt());

    setDeathInfo_Fall(kill_dir, kill_player_no, combo_score);
    return true;
}

bool Enemy::hitCallback_ChibiYoshiUnk(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
    return false;
}

bool Enemy::hitCallback_ChibiYoshiLight(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
    return false;
}

bool Enemy::hitCallback_ChibiYoshiStar(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    return setDeathInfo_Star(cc_self, cc_other);
}

bool Enemy::hitCallback_AttackUnk27(bool* p_dead, ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    (void)cc_self;
    (void)cc_other;
    *p_dead = false;
    return true; // 
}

void Enemy::setDeathInfo_Fall(DirType direction, s32 player_no, ScoreMgr::ScoreType score_type)
{
    static const sead::Vector2f c_die_fall_init_speed[cDirType_NumX] = {
        sead::Vector2f(cDieFallInitSpeedX[cDirType_Right], ENEMY_DIE_FALL_INIT_SPEED_Y),
        sead::Vector2f(cDieFallInitSpeedX[cDirType_Left ], ENEMY_DIE_FALL_INIT_SPEED_Y)
    };

    setDeathInfo_Fall(c_die_fall_init_speed, direction, player_no, score_type);
}

void Enemy::setDeathInfo_Fumi(Actor* p_player, const sead::Vector2f& speed, const StateID& state_id)
{
    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_player);
    s32 kill_player_no = p_player->getPlayerNo();

    ENEMY_MAKE_DEATH_INFO_ARG_CUSTOM_NO_SCORE(arg);
    arg.speed = speed;
    arg.max_fall_speed = ENEMY_DEFAULT_MAX_FALL_SPEED;
    arg.gravity = cDieFallGravity;
    arg.p_state_id = &state_id;
    arg.direction = kill_dir;
    arg.player_no = kill_player_no;
    mDeathInfo.kill(arg);
}

void Enemy::setDeathInfo_Quake(QuakeDeathType type)
{
    static const sead::Vector2f c_die_fall_init_speed[cQuakeDeathType_Num] = {
        sead::Vector2f(0.0f, 2.0f),
        sead::Vector2f(0.0f, 3.5f)
    };

    sead::Vector3f effect_pos(getCenterPos2D(), EFFECT_Z_POS_DEFAULT);
    EffectCreateUtil::createEffect(RP_Cmn_HitEX, &effect_pos);

    GameAudio::breakdownSE(ActorStatus::instance()->getQuakeComboCount(), mPos);

    ActorStatus::instance()->incQuakeComboCount();
    ScoreMgr::ScoreType combo_score = mCombo.getComboScore(ActorStatus::instance()->getQuakeComboCount());

    ENEMY_MAKE_DEATH_INFO_ARG_FALL_ALL_PLAYER(arg);
    arg.speed = c_die_fall_init_speed[type];
    arg.max_fall_speed = ENEMY_DEFAULT_MAX_FALL_SPEED;
    arg.gravity = cDieFallGravity;
    arg.score_type = combo_score;
    arg.direction = mDirection;
    mDeathInfo.kill(arg);
}

void Enemy::setSmokeDamage_(Actor* p_actor)
{
    s32 kill_player_no = p_actor != nullptr ? p_actor->getPlayerNo() : mPlayerNo;

    ENEMY_MAKE_DEATH_INFO_ARG_SMOKE_NO_SCORE(arg);
    arg.speed.set(0.0f, 0.0f);
    arg.player_no = kill_player_no;
    mDeathInfo.kill(arg);
}

void Enemy::setDeathInfo_IceBreak()
{
    mIceMgr.removeIce();
    setDeathInfo_Fall(DirType(mDieDirection), mPlayerNo);
}

void Enemy::setDeathInfo_IceVanish()
{
    mIceMgr.removeIce();

    DirType up_coin_dir = (s32(GAME_RANDOM.getU32()) < 0) ? cDirType_Left : cDirType_Right;

    ActorCoinMgr::UpCoinArg up_coin_arg = {
        getCenterPos(),
        up_coin_dir,
        1,
        cLayerID_Layer1
    };
    ActorCoinMgr::instance()->createUpCoin(up_coin_arg);

    ENEMY_MAKE_DEATH_INFO_ARG_ICE_VANISH_NO_SCORE(arg);
    arg.speed.set(0.0f, 0.0f);
    arg.direction = mDieDirection;
    arg.player_no = mPlayerNo;
    mDeathInfo.kill(arg);
}

void Enemy::setDeathInfo_Other(Actor* p_actor)
{
    s32 kill_player_no = p_actor != nullptr ? p_actor->getPlayerNo() : -1;

    ENEMY_MAKE_DEATH_INFO_ARG_OTHER_NO_SCORE(arg);
    arg.speed.set(0.0f, 0.0f);
    arg.player_no = kill_player_no;
    mDeathInfo.kill(arg);
}

void Enemy::setDeathInfo_Hasami()
{
    /*
    if (
        !mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Right) &&
        (
            mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Left) ||
            (
                (
                    mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Up) ||
                    mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Down)
                ) &&
                mSpeed.x < 0.0
            )
        )
    )
    {
        hitdamageEffect(mPos);

        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

        setDeathInfo_Fall(cDirType_Left);
    }
    else
    {
        hitdamageEffect(mPos);

        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

        setDeathInfo_Fall(cDirType_Right);
    }
    */
    DirType kill_dir;
    if (
        !mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Right) &&
        (
            mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Left) ||
            (
                (
                    mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Up) ||
                    mBgCheckObj.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Down)
                ) &&
                mSpeed.x < 0.0
            )
        )
    )
        kill_dir = cDirType_Left;
    else
        kill_dir = cDirType_Right;

    hitdamageEffect(mPos);

    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);

    setDeathInfo_Fall(kill_dir);
}

bool Enemy::setDeathInfo_Star(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    hitdamageEffect(cc_self->getHitPos());

    Actor* p_actor_other = cc_other->getOwner();

    DirType kill_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);
    s32 kill_player_no = p_actor_other->getPlayerNo();

    ScoreMgr::ScoreType combo_score = ScoreMgr::cScoreType_Invalid;
    if (0 <= kill_player_no && kill_player_no < cPlayerNum)
    {
        PlayerObject* p_player_other = PlayerMgr::instance()->getPlayerObject(kill_player_no);
        if (p_player_other != nullptr)
        {
            p_actor_other->slideComboSE(p_player_other->getStarCount(), mCombo.isComboType2());

            combo_score = mCombo.getComboScore(Combo::calcPlStarCnt(p_player_other));
        }
    }
    setDeathInfo_Fall(kill_dir, kill_player_no, combo_score);
    return true;
}

bool Enemy::setTouchDrcDamage_(const sead::Vector3f& pos)
{
    if (isDead())
        return false;

    if (isState(StateID_Ice))
        return false;

    removeCollisionCheck();

    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", pos);

    DirType kill_dir = cDirType_Right;
    if (mPos.x < pos.x)
        kill_dir = cDirType_Left;

    createUpCoin(kill_dir);

    setDeathInfo_Fall(kill_dir);
    return true;
}

Angle Enemy::applyWaterRollDec(Angle ang)
{
    if (mIsSubmerged)
        ang = ang * cWaterRollDecRate;
    return ang;
}

bool Enemy::isQuakeDamage()
{
    return mBgCheckObj.checkFoot();
}

void Enemy::setDeathSound_Fire()
{
    GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);
}

void Enemy::setDeathSound_HipAttk()
{
    if (mEnFlag.isOn(cEnFlag_Carry))
        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN_HPDP_H", mPos);
    else
        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN_HPDP_S", mPos);
}

void Enemy::initDieState()
{
    removeCollisionCheck();

    s32 kill_player_no = mDeathInfo.mArg.player_no;

    ScoreMgr::ScoreType score_type = ScoreMgr::ScoreType(mDeathInfo.mArg.score_type);
    if (score_type >= 0)
    {
        if (0 <= kill_player_no && kill_player_no < cPlayerNum)
            ScoreMgr::instance()->ScoreSet(this, score_type, kill_player_no);
        else if (kill_player_no == cPlayerNum)
            ScoreMgr::instance()->UnKnownScoreSet(this, score_type);
    }
}

void Enemy::initializeState_DieFumi()
{
    cancelCarry();
    initDieState();
    mBgCheckObj.clearBg();
    mSpeed.set(
        mDeathInfo.mArg.speed.x,
        mDeathInfo.mArg.speed.y,
        0.0f
    );
    mSpeedMax.set(
        0.0f,
        mDeathInfo.mArg.max_fall_speed,
        0.0f
    );
    mDieDirection = mDeathInfo.mArg.direction;
    mPow = 0.0f;
    mGravity = mDeathInfo.mArg.gravity;
    mDirection = mAngle.y() < 0 ? cDirType_Left : cDirType_Right;
    mAngle.y() = cBaseAngleY[mDirection];
    mPos.z = mCollisionMask.isOn(cCcLineKind_1) ? -384.0f : 5000.0f;
    mWaterCalcType = cWaterCalcType_EnablePreCheck;
}

void Enemy::finalizeState_DieFumi()
{
}

void Enemy::executeState_DieFumi()
{
    mAngle.x() += applyWaterRollDec(cDieFallSpinSpeed / 4);

    calcSpeedY_();
    posMove_();
}

void Enemy::initializeState_DieFall()
{
    Enemy::initializeState_DieFumi();
}

void Enemy::finalizeState_DieFall()
{
}

void Enemy::executeState_DieFall()
{
    static const Angle cs_spin_speed[cDirType_NumX] = { 0x1000000, -0x1000000 };

    s32 spin_speed_x;
    s32 spin_speed_y;
    if (mDirection == mDieDirection)
    {
        spin_speed_x = cDieFallSpinSpeed;
        spin_speed_y = -cs_spin_speed[mDieDirection];
    }
    else
    {
        spin_speed_x = -cDieFallSpinSpeed;
        spin_speed_y = cs_spin_speed[mDieDirection];
    }
    mAngle.x() += applyWaterRollDec(spin_speed_x);
    mAngle.y() += spin_speed_y;

    calcSpeedY_();
    posMove_();
}

void Enemy::initializeState_DieYoshiFumi()
{
    sead::Vector3f effect_pos = getCenterPos();
    EffectCreateUtil::createEffect(RP_Yoshi_Stamp, &effect_pos);

    removeCollisionCheck();
}

void Enemy::finalizeState_DieYoshiFumi()
{
}

void Enemy::executeState_DieYoshiFumi()
{
    deleteRequest();
}

void Enemy::initializeState_DieSmoke()
{
    removeCollisionCheck();
}

void Enemy::finalizeState_DieSmoke()
{
}

void Enemy::executeState_DieSmoke()
{
    deleteRequest();
}

void Enemy::initializeState_DieIceVanish()
{
    initDieState();
}

void Enemy::finalizeState_DieIceVanish()
{
}

void Enemy::executeState_DieIceVanish()
{
    deleteRequest();
}

void Enemy::initializeState_DieOther()
{
    deleteRequest();
}

void Enemy::finalizeState_DieOther()
{
}

void Enemy::executeState_DieOther()
{
}

void Enemy::setDeathInfo_Awa(Actor* p_awa)
{
    ENEMY_MAKE_DEATH_INFO_ARG_AWA_NO_SCORE_NO_PLAYER(arg);
    arg.speed.set(0.0f, 0.0f);
    mDeathInfo.kill(arg);
}

void Enemy::initializeState_DieAwa()
{
    SubjectMgr::instance()->incEnDieAwa();
    removeCollisionCheck();
    deleteRequest();
}

void Enemy::finalizeState_DieAwa()
{
}

void Enemy::executeState_DieAwa()
{
}

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

const f32 Enemy::cDieFallGravity = 1.3f * Enemy::cDefaultGravity;
const f32 Enemy::cDieFallInitSpeedY = ENEMY_DIE_FALL_INIT_SPEED_Y;
const f32 Enemy::cDieFallMaxFallSpeed = ENEMY_DEFAULT_MAX_FALL_SPEED;

CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieFumi)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieFall)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieYoshiFumi)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieSmoke)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieIceVanish)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieOther)
CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieAwa)
