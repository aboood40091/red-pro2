#include <actor/ActorMgr.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <effect/EffectCreateUtil.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>

void PlayerBase::initCollision(const ActorCollisionCheck::CollisionData& cc_data_react, const ActorCollisionCheck::CollisionData& cc_data_attack)
{
    mCollisionCheck.set(this, cc_data_react);
    mCollisionCheck2_React.set(this, cc_data_react);
    mCollisionCheck3_React.set(this, cc_data_react);
    mCollisionCheck5_Attack.set(this, cc_data_attack);
    mCollisionCheck4_Attack.set(this, cc_data_attack);
}

void PlayerBase::releaseCcData()
{
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
    {
        mCollisionCheck.setVsKind(
            ActorCollisionCheck::cTargetKind_Enemy |
            ActorCollisionCheck::cTargetKind_Balloon |
            ActorCollisionCheck::cTargetKind_Item |
            ActorCollisionCheck::cTargetKind_Tama |
            ActorCollisionCheck::cTargetKind_Killer |
            ActorCollisionCheck::cTargetKind_GoalPole |
            ActorCollisionCheck::cTargetKind_ChibiYoshi |
            ActorCollisionCheck::cTargetKind_Unk10 |
            ActorCollisionCheck::cTargetKind_DrcTouch
        );

        mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_None);
        mCollisionCheck.setDamage(
            ~(ActorCollisionCheck::cDamageFrom_YoshiMouth |
              ActorCollisionCheck::cDamageFrom_SpinLiftUp)
        );

        mCollisionCheck.setDrcTouchCallback(&mDrcTouchCallback);
    }

    ActorCollisionCheckMgr::instance()->release(mCollisionCheck2_React);
    {
        mCollisionCheck2_React.setVsKind(
            ActorCollisionCheck::cTargetKind_Enemy |
            ActorCollisionCheck::cTargetKind_Balloon |
            ActorCollisionCheck::cTargetKind_Item |
            ActorCollisionCheck::cTargetKind_Tama |
            ActorCollisionCheck::cTargetKind_Killer |
            ActorCollisionCheck::cTargetKind_GoalPole |
            ActorCollisionCheck::cTargetKind_ChibiYoshi |
            ActorCollisionCheck::cTargetKind_Unk10 |
            ActorCollisionCheck::cTargetKind_DrcTouch
        );

        mCollisionCheck2_React.setAttack(ActorCollisionCheck::cAttack_None);
        mCollisionCheck2_React.setDamage(
            ~(ActorCollisionCheck::cDamageFrom_YoshiMouth |
              ActorCollisionCheck::cDamageFrom_SpinLiftUp)
        );

        mCollisionCheck2_React.setDrcTouchCallback(&mDrcTouchCallback);
    }

    ActorCollisionCheckMgr::instance()->release(mCollisionCheck3_React);
    {
        mCollisionCheck3_React.setVsKind(
            ActorCollisionCheck::cTargetKind_Player
        );

        mCollisionCheck3_React.setAttack(ActorCollisionCheck::cAttack_None);
        mCollisionCheck3_React.setDamage(
            ~ActorCollisionCheck::cDamageFrom_YoshiMouth
        );
    }

    ActorCollisionCheckMgr::instance()->release(mCollisionCheck4_Attack);
    {
        mCollisionCheck4_Attack.setVsKind(
            ActorCollisionCheck::cTargetKind_Player
        );

        mCollisionCheck4_Attack.setAttack(ActorCollisionCheck::cAttack_None);
        mCollisionCheck4_Attack.setDamage(
            ActorCollisionCheck::cDamageFrom_PenguinSlip
        );
    }

    ActorCollisionCheckMgr::instance()->release(mCollisionCheck5_Attack);
    {
        mCollisionCheck5_Attack.setVsKind(
            ActorCollisionCheck::cTargetKind_Enemy |
            ActorCollisionCheck::cTargetKind_Balloon |
            ActorCollisionCheck::cTargetKind_Item |
            ActorCollisionCheck::cTargetKind_Tama |
            ActorCollisionCheck::cTargetKind_Killer |
            ActorCollisionCheck::cTargetKind_GoalPole |
            ActorCollisionCheck::cTargetKind_ChibiYoshi |
            ActorCollisionCheck::cTargetKind_Unk10
        );

        mCollisionCheck5_Attack.setAttack(ActorCollisionCheck::cAttack_None);
        mCollisionCheck5_Attack.setDamage(
            ActorCollisionCheck::cDamageFrom_None
        );
    }
}

void PlayerBase::clearCcData()
{
    mCollisionCheck.clear();
    mCollisionCheck2_React.clear();
    mCollisionCheck3_React.clear();
    mCollisionCheck4_Attack.clear();
    mCollisionCheck5_Attack.clear();
}

bool PlayerBase::entryCollision()
{
    if (!isStatus(cStatus_OutOfPlay) && !isStatus(cStatus_Stunned))
    {
        mCollisionCheck.setLayer(mLayer);
        mCollisionCheck3_React.setLayer(mLayer);
        mCollisionCheck4_Attack.setLayer(mLayer);
        mCollisionCheck5_Attack.setLayer(mLayer);

        if (mCollisionCheck4_Attack.getAttack() != ActorCollisionCheck::cAttack_None)
            ActorCollisionCheckMgr::instance()->entry(mCollisionCheck4_Attack);

        if (mCollisionCheck5_Attack.getAttack() != ActorCollisionCheck::cAttack_None)
            ActorCollisionCheckMgr::instance()->entry(mCollisionCheck5_Attack);

        if (!isStatus(cStatus_266))
        {
            if (isStatus(cStatus_264))
                ActorCollisionCheckMgr::instance()->entry(mCollisionCheck2_React);

            ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
            ActorCollisionCheckMgr::instance()->entry(mCollisionCheck3_React);
        }
        else if (isStatus(cStatus_267))
        {
            ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
        }
        return true;
    }
    return false;
}

void PlayerBase::setCcAt(const ActorCollisionCheck::Vec2& center_offset, const ActorCollisionCheck::Vec2& half_size, const ActorCollisionCheck::Attack& attack)
{
    mCollisionCheck4_Attack.setCenterOffset(center_offset);
    mCollisionCheck4_Attack.setHalfSize(half_size);
    mCollisionCheck4_Attack.setAttack(attack);

    mCollisionCheck5_Attack.setCenterOffset(center_offset);
    mCollisionCheck5_Attack.setHalfSize(half_size);
    mCollisionCheck5_Attack.setAttack(attack);
}

void PlayerBase::setCcAtBody(const ActorCollisionCheck::Attack& attack)
{
    setCcAt(
        mCollisionCheck.getCenterOffset(),
        mCollisionCheck.getHalfSize(),
        attack
    );
}

void PlayerBase::setCcAtSlip()
{
    setCcAtBody(ActorCollisionCheck::cAttack_Slip);
}

void PlayerBase::setCcAtPenguinSlip()
{
    if (isStatus(cStatus_99))
    {
        setCcAtBody(ActorCollisionCheck::cAttack_PenguinSlip);
        mCollisionCheck4_Attack.setDamage(
            ActorCollisionCheck::cDamageFrom_PenguinSlip
        );
        mCollisionCheck5_Attack.setDamage(
            ActorCollisionCheck::cDamageFrom_PenguinSlip
        );
    }
}

void PlayerBase::setCcAtHipAttack()
{
    setCcAtBody(ActorCollisionCheck::cAttack_HipAttack);
    mCollisionCheck4_Attack.setDamage(
        ActorCollisionCheck::cDamageFrom_None
    );
    mCollisionCheck5_Attack.setDamage(
        ActorCollisionCheck::cDamageFrom_None
    );
}

void PlayerBase::setCcAtCannon()
{
    setCcAtBody(ActorCollisionCheck::cAttack_Cannon);
    mCollisionCheck4_Attack.setDamage(
        ActorCollisionCheck::cDamageFrom_None
    );
    mCollisionCheck5_Attack.setDamage(
        ActorCollisionCheck::cDamageFrom_None
    );
}

void PlayerBase::setCcAtStar()
{
    mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_Star);
    switch (mCollisionCheck5_Attack.getAttack())
    {
    case ActorCollisionCheck::cAttack_None:
    case ActorCollisionCheck::cAttack_SpinLiftUp:
    case ActorCollisionCheck::cAttack_YoshiEat:
        break;
    default:
        mCollisionCheck5_Attack.setAttack(ActorCollisionCheck::cAttack_Star);
        break;
    }
    onStatus(cStatus_270);
}

bool PlayerBase::isActionRevisionY()
{
    if (isStatus(cStatus_Pole) || isStatus(cStatus_PoleRope))
        return true;
    return false;
}

void PlayerBase::setCcPlayerRevY(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other, f32 scale, ActorCollisionCheck::Kind kind)
{
    PlayerBase* p_player_other = cc_other->getOwner<PlayerBase>();
    if (p_player_other == nullptr)
        return;

    f32 player_speed = p_player_other->mSpeedF;
    f32 rev_x = cc_self->getRevisionX(kind);
    f32 rev_y = cc_self->getRevisionY(kind);

    if (isActionRevisionY())
    {
        if (p_player_other->isActionRevisionY())
        {
            if (_2085)
                _2080 = rev_y + _2080;
            else
            {
                _2085 = true;
                _2080 = rev_y * scale;
            }
        }
    }
    else
    {
        if (sead::Mathf::abs(rev_y) >= 1.0f && !p_player_other->isActionRevisionY())
        {
            f32 rev_speed = rev_x * scale;
            if (_2084)
            {
                f32 current_speed = mCcPlayerRevSpeedF;
                if (sead::Mathf::abs(current_speed) < sead::Mathf::abs(rev_speed))
                {
                    mCcPlayerRevSpeedFStart = player_speed;
                }
                else
                {
                    scale = mCcPlayerRevSpeedFScale + scale;
                    if (scale < 0.0f)
                        scale = 0.0f;
                    else if (scale > 1.0f)
                        scale = 1.0f;
                }
                mCcPlayerRevSpeedFScale = scale;
                mCcPlayerRevSpeedF = current_speed + rev_speed;
            }
            else
            {
                mCcPlayerRevSpeedFScale = scale;
                mCcPlayerRevSpeedFStart = player_speed;
                mCcPlayerRevSpeedF = rev_speed;
                _2084 = true;
            }
        }
    }
}

void PlayerBase::setCcPlayerRevParam(f32 param)
{
    _2084 = true;
    mCcPlayerRevSpeedFScale = 1.0f;
    mCcPlayerRevSpeedFStart = param;
    mCcPlayerRevSpeedF = param * 0.5f;
}

void PlayerBase::clearCcPlayerRev()
{
    mCcPlayerRevSpeedFScale = 0.0f;
    mCcPlayerRevSpeedFStart = 0.0f;
    mCcPlayerRevSpeedF = 0.0f;
    _2080 = 0.0f;
    _2084 = false;
    _2085 = false;
}

bool PlayerBase::calcCcPlayerRev(f32* p_speed_rev)
{
    if (_2084)
    {
        f32 scale = mCcPlayerRevSpeedFScale;
        if (isStatus(cStatus_150) || _206c != 0)
            scale = 0.0f;

        f32 base_speed_rev = mCcPlayerRevSpeedF;

        if (isStatus(cStatus_DemoControl) && isNowBgCross(cBgCross_IsFoot))
            scale = 0.0f;

        mCcPlayerRevSpeedF = 0.0f;

        if (base_speed_rev != 0.0f)
        {
            f32 speed_rev = base_speed_rev * scale;
            if (speed_rev > 3.0f)
                speed_rev = 3.0f;
            else if (speed_rev < -3.0f)
                speed_rev = -3.0f;
            if (mSpeedF * base_speed_rev <= 0.0f)
            {
                *p_speed_rev = speed_rev;
                if (!isStatus(cStatus_DemoControl) && !isStatus(cStatus_DemoOnLandStop))
                {
                    f32 speed = mSpeedF;
                    f32 speed_rev_start = mCcPlayerRevSpeedFStart;
                    if (speed * speed_rev_start <= 0.0f && sead::Mathf::abs(speed) + sead::Mathf::abs(speed_rev_start) > 2.5f)
                    {
                        mSpeedF = speed_rev_start * 0.4f;
                        return true;
                    }
                    if (sead::Mathf::abs(speed) > sead::Mathf::abs(speed_rev_start))
                    {
                        if (speed < -1.3f)
                            mSpeedF = -1.3f;
                        else
                        {
                            if (speed > 1.3f)
                                speed = 1.3f;
                            mSpeedF = speed;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void PlayerBase::setNoHitPlayer(const PlayerBase* p_player_other, s32 time)
{
    mNoHitPlayerID = p_player_other->getActorUniqueID();
    mNoHitPlayerTimer = time;
}

void PlayerBase::updateNoHitPlayer()
{
    if (mNoHitPlayerTimer != 0)
    {
        mNoHitPlayerTimer--;
        if (mNoHitPlayerTimer == 0)
            mNoHitPlayerID = ActorUniqueID::cInvalidID;
    }
}

const PlayerBase* PlayerBase::getNoHitPlayer()
{
    return sead::DynamicCast<const PlayerBase>(ActorMgr::instance()->getActorPtr(mNoHitPlayerID));
}

bool PlayerBase::isEnableStamp(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    f32 other_top = cc_other->getTopPos() - 16.0;
    if (other_top < cc_other->getCenterPosY())
        other_top = cc_other->getCenterPosY();

    f32 self_under = cc_self->getUnderPos();
    return self_under > other_top;
}

bool PlayerBase::isEnableStampPlayerJump(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (isNowBgCross(cBgCross_IsFoot)) // On ground
        return false;

    if (mSpeed.y >= 0.0f) // Jumping
        return false;

    if (isStatus(cStatus_48) || isStatus(cStatus_52))
        return false;

    PlayerBase* p_player_other = cc_other->getOwner<PlayerBase>();
    if (p_player_other == nullptr)
        return false;

    if (p_player_other->isLiftUp())
        return false;

    if (p_player_other->mNoStampPlayerJumpTimer != 0)
        return false;

    if (p_player_other->isStatus(cStatus_82))
        return false;

    if (isStatus(cStatus_DemoControl) || p_player_other->isStatus(cStatus_DemoControl))
        return false;

    if (isEnableStamp(cc_self, cc_other))
        return true;
    else
        return false;
}

void PlayerBase::setReductionScale()
{
    setReductionBoyon();
    initStampReduction();
}

void PlayerBase::setStampReduction(PlayerBase* p_player_other)
{
    if (!isStatus(cStatus_Swim))
    {
        if (mSpeed.y > 0.0f)
            mSpeed.y = 0.0f;

        setReductionScale();

        if (p_player_other->isNowBgCross(cBgCross_IsHead))
            onStatus(cStatus_282);
    }
    else
    {
        mSpeed.y = -1.0f;
    }
}

void PlayerBase::setStampPlayerJump(bool allow_high_jump, f32 rev_y)
{
    if (!isStatus(cStatus_Swim))
    {
        f32 jump_speed = cJumpSpeed;
        if (isMameAction())
            jump_speed = cJumpSpeed - 0.35f;

        f32 move_speed = mSpeedF;

        if (allow_high_jump)
        {
            Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_PlayerImpact);

            if (mPlayerKey.buttonJump())
                jump_speed = cJumpSpeed + 0.5f;

            bouncePlayer1(jump_speed, move_speed, true, cBounceType_1, cJumpSe_None);
        }
        else
        {
            bouncePlayer1(jump_speed, move_speed, true, cBounceType_Normal, cJumpSe_None);
        }

        mPos.y += rev_y;
        setHopAirDrift();
    }
    else
    {
        mSpeed.y = 1.0f;
    }
}

void PlayerBase::setStomped()
{
    startVoiceSound(STOMPED);
    Quake::instance()->shockMotor(mPlayerNo, Quake::cShockType_PlayerImpact);

    sead::Vector3f face_pos;
    mpModelBaseMgr->getJointPos(&face_pos, "face_1");
    EffectCreateUtil::createPlayerEffect(mPlayerNo, RP_Npc_Hit, &face_pos);

    coinJumpOnStampCB(1);
}

void PlayerBase::initStampReduction()
{
    onStatus(cStatus_118);

    mNoStampPlayerJumpTimer = 10;

    if (!isStatus(cStatus_Jump) || mReductionStep == 0)
        mReductionSimpleMoveTimer = 4;

    setStomped();
}

void PlayerBase::calcJumpDaiReductionScale(s32 t, s32 max_t)
{
    if (t > max_t)
        t = max_t;

    mReductionScale = 0.6f * (f32)t / (f32)max_t;
    mReductionMode = cReductionMode_JumpDai;
}

void PlayerBase::setReductionBoyon()
{
    mReductionMode = cReductionMode_Boyon;
    mReductionStep = 4;
}

bool PlayerBase::getHeadTopPos(sead::Vector3f& pos)
{
    f32 center_y = getCenterPos().y;
    f32 head_top_y = getHeadTopPosP()->y - 4.0f;
    if (head_top_y < center_y)
        head_top_y = center_y;
    pos.set(mPos.x, head_top_y, mPos.z);
    return true;
}

void PlayerBase::calcReductionScale()
{
    switch (mReductionMode)
    {
    default:
        break;
    case cReductionMode_JumpDai:
        mReductionMode = cReductionMode_2;
        break;
    case cReductionMode_2:
        setReductionBoyon();
        break;
    case cReductionMode_Boyon:
        if (mReductionStep != 0)
        {
            static const f32 c_target[] = { 0.0f, 0.2f, 0.0f, 0.4f };
            static const f32 c_step[] = { 0.02f, 0.025f, 0.04f, 0.06f };
            u32 idx = mReductionStep - 1;
            if (sead::Mathf::chase(&mReductionScale, c_target[idx], c_step[idx]))
                mReductionStep--;
        }
        if (mReductionStep == 0)
            mReductionMode = cReductionMode_None;
        break;
    }
}

void PlayerBase::getReductionModelScale(sead::Vector3f* p_scale)
{
    if (p_scale == nullptr)
        return;

    p_scale->set(
        mReductionScale + 1.0f,
        1.0f - mReductionScale,
        mReductionScale + 1.0f
    );
}