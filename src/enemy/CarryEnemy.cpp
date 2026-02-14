#include <actor/Profile.h>
#include <actor/ActorUtil.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/CarryEnemy.h>
#include <game/AreaTask.h>
#include <player/PlayerDemoMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);
static const sead::Vector3f cCarryBaseOffset_Carry(0.0f, -5.0f, 6.0f);
static const sead::Vector3f cCarryBaseOffset_LiftUp(0.0f, 0.0f, 0.0f);
static const sead::Vector3f cCarryStepOffset(0.0f, 5.0f, 5.0f);

CREATE_STATE_VIRTUAL_ID_BASE(CarryEnemy, Carry)
CREATE_STATE_VIRTUAL_ID_BASE(CarryEnemy, Sleep)
CREATE_STATE_VIRTUAL_ID_BASE(CarryEnemy, Slide)

CarryEnemy::CarryEnemy(const ActorCreateParam& param)
    : Enemy(param)
    , mCarryBaseOffset(0.0f, 0.0f, 0.0f)
    , mPreCarryCcCenterOffset()
    , mPreCarryCcHalfSize()
    , mCarryChangePosZ(0.0f)
    , _18a0(0)
    , _18a4(0)
    , mCarryPlayerNo(0)
    , mCarryPlayerID()
    , mForceSetShellDamageEffect(false)
    , mIsLiftUp(false)
{
    mPreCarryCcCenterOffset.x = 0.0f;
    mPreCarryCcCenterOffset.y = 0.0f;
    mPreCarryCcHalfSize.x = 0.0f;
    mPreCarryCcHalfSize.y = 0.0f;
}

bool CarryEnemy::preExecute_()
{
    return Enemy::preExecute_();    // Useless much?
}

PlayerObject* CarryEnemy::getCarryPlayerObject_() const
{
    if (0 <= mCarryPlayerNo && mCarryPlayerNo < 4)
        return PlayerMgr::instance()->getPlayerObject(mCarryPlayerNo);

    return nullptr;
}

void CarryEnemy::cancelCarry()
{
    PlayerObject* p_player_obj = getCarryPlayerObject_();
    if (p_player_obj != nullptr)
        p_player_obj->cancelCarry(this);

    mCarryPlayerNo = -1;
    mCarryPlayerID.invalidate();
}

ActorBase::Result CarryEnemy::doDelete_()
{
    cancelCarry();
    return cResult_Success;
}

void CarryEnemy::setCarryImpl_(Actor* p_player, CarryType type)
{
    switch (type)
    {
    default:
        break;
    case cCarryType_LiftUp:
    case cCarryType_LiftUp_2:
        mCarryBaseOffset = cCarryBaseOffset_LiftUp;
        mIsLiftUp = true;
        break;
    case cCarryType_Carry:
    case cCarryType_Carry_2:
        mCarryBaseOffset = cCarryBaseOffset_Carry;
        mIsLiftUp = false;
        break;
    }
    mCarryPlayerNo = p_player->getPlayerNo();
    setPlayerNo(p_player->getPlayerNo());
    mCarryPlayerID = p_player->getActorUniqueID();
    changeState(StateID_Carry);
}

void CarryEnemy::setSpinLiftUpActor(Actor* p_player)
{
    setCarryImpl_(p_player, cCarryType_LiftUp);
}

void CarryEnemy::reviseCarryBgPosX_(ActorBgCollisionCheck& bc, const sead::Vector3f& player_pos)
{
    BgCollisionCheckResultArea res;

    bc.initBgCheck();
    bc.getBgCheck().setIgnoreQuicksand(true);

    const ActorBgCollisionCheck::Sensor* p_sensor = bc.getSensorEffective(cDirType_Right);

    f32 wall_base_offs = p_sensor != nullptr ? p_sensor->center_offset : 0.0f;

    f32 wall_offs = sead::Mathf::abs(wall_base_offs) * cEnMuki[mDirection];

    sead::Vector2f p0(player_pos.x, player_pos.y);
    sead::Vector2f p1(mPos.x + wall_offs, player_pos.y);

    if (bc.getBgCheck().checkArea(&res, p0, p1, 1 << mDirection))
        mPos.x = res.hit_pos.x - wall_offs;
}

void CarryEnemy::reviseCarryBgPosY_(ActorBgCollisionCheck& bc)
{
    BgCollisionCheckResultArea res;

    bc.initBgCheck();
    bc.getBgCheck().setIgnoreQuicksand(true);

    const ActorBgCollisionCheck::Sensor* p_sensor = bc.getSensorEffective(cDirType_Up);

    f32 ceil_offs = p_sensor != nullptr ? p_sensor->center_offset : 0.0f;

    sead::Vector2f p0(mPos.x, mPos.y + 1.0f);
    sead::Vector2f p1(p0.x, p0.y + ceil_offs + 1.0f);

    if (bc.getBgCheck().checkArea(&res, p0, p1, 1 << cDirType_Up))
        mPos.y = res.hit_pos.y - ceil_offs;
}

bool CarryEnemy::carryCheckBg(Actor* p_player)
{
    // bg check
    if (p_player != nullptr)
    {
        if (AreaTask::instance()->getLoopType() != 0)
        {
            sead::Vector3f delta;
            delta.setSub(mPos, mPosPrev);

            f32 player_pos_x = p_player->getPos().x;
            f32 pos_x = mPos.x;
            f32 area_width = AreaTask::instance()->getBound().getSizeX();
            if (sead::Mathf::abs(player_pos_x - pos_x) > area_width * 0.5f)
            {
                if (player_pos_x < pos_x)
                    pos_x -= area_width;
                else
                    pos_x += area_width;
            }
            mPos.x = pos_x;

            mPos += delta;
        }

        const sead::Vector3f& player_center_pos = p_player->getCenterPos();

        reviseCarryBgPosX_(mBgCheckObj, player_center_pos);
        reviseCarryBgPosY_(mBgCheckObj);

        mPosPrev = player_center_pos;
    }

    // bg in check (stripped in NSMBU)
    return false;
}

void CarryEnemy::setDeathInfo_CarryBgIn(Actor* p_player, bool eff_set)
{
    if (eff_set)
    {
        hitdamageEffect(mPos);
        GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);
    }

    static const sead::Vector2f c_dead_speed[cDirType_NumX] = {
        sead::Vector2f::zero,
        sead::Vector2f::zero
    };
    setDeathInfo_Fall(c_dead_speed, mDirection, mPlayerNo);
}

PlayerObject* CarryEnemy::getCarryPlayerObject() const
{
    if (0 <= mCarryPlayerNo && mCarryPlayerNo < 4)
        return PlayerMgr::instance()->getPlayerObject(mCarryPlayerNo);

    return nullptr;
}

PlayerObject* CarryEnemy::getCarryPlayerObject2() const
{
    if (0 <= mCarryPlayerNo && mCarryPlayerNo < 4)
        return PlayerMgr::instance()->getPlayerObject2(mCarryPlayerNo);

    return nullptr;
}

void CarryEnemy::setCarryActor_(Actor* p_player)
{
    setCarryImpl_(p_player, cCarryType_Carry);
}

bool CarryEnemy::carryCheck(Actor* p_player)
{
    if (isSpinLiftUpEnable())
    {
        PlayerObject* p_player_obj = sead::DynamicCast<PlayerObject>(p_player);
        if (p_player_obj != nullptr)
        {
            if (!p_player_obj->isStatus(PlayerObject::cStatus_Spin) && p_player_obj->setCarry(this, cCarryType_Carry))
            {
                setCarryActor_(p_player_obj);
                return true;
            }
        }
    }
    return false;
}

bool CarryEnemy::checkSleepEnd() const
{
    if (isDead())
        return false;

    if (*mStateMgr.getStateID() == StateID_Ice)
        return false;

    if (checkEat())
        return false;

    if (PlayerDemoMgr::instance()->isPlayerGameStop())
        return false;

    PlayerObject* p_player_obj = getCarryPlayerObject();
    if (p_player_obj != nullptr)
    {
        if (p_player_obj->isStatus(PlayerObject::cStatus_129))
            return false;

        if (p_player_obj->isDemoType(PlayerObject::cDemoType_3))
            return false;
    }

    return true;
}

void CarryEnemy::setSlideCc()
{
    mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_Shell);
    mCollisionCheck.onVsKind(
        ActorCollisionCheck::cTargetKind_Balloon |
        ActorCollisionCheck::cTargetKind_Item |
        ActorCollisionCheck::cTargetKind_Killer
    );
    mCollisionCheck.onStatus(ActorCollisionCheck::cStatus_MoveKill);
}

void CarryEnemy::setSlideBc()
{
    mBgCheckObj.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);

    mBgCheckObj.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);

    mBgCheckObj.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);

    mBgCheckObj.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckObj.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
}

void CarryEnemy::startSlide()
{
    setSlideCc();
    setSlideBc();
    clrComboCnt();
}

void CarryEnemy::resetSlideCc()
{
    mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_None);
    mCollisionCheck.offVsKind(
        ActorCollisionCheck::cTargetKind_Balloon |
        ActorCollisionCheck::cTargetKind_Item |
        ActorCollisionCheck::cTargetKind_Killer
    );
    mCollisionCheck.offStatus(ActorCollisionCheck::cStatus_MoveKill);
}

void CarryEnemy::resetSlideBc()
{
    mBgCheckObj.getSensorFlag(cDirType_Down).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Down).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_4);

    mBgCheckObj.getSensorFlag(cDirType_Up).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Up).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_4);

    mBgCheckObj.getSensorFlag(cDirType_Right).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckObj.getSensorFlag(cDirType_Left).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_3);

    mBgCheckObj.getSensorFlag(cDirType_Right).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckObj.getSensorFlag(cDirType_Left).resetBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
}

void CarryEnemy::endSlide()
{
    resetSlideCc();
    resetSlideBc();
    clrComboCnt();
}

DirType CarryEnemy::getRevisionDir(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    return cc_self->getRevisionX(cc_other->getKind()) <= 0.0f ? cDirType_Left : cDirType_Right;
}

void CarryEnemy::vsPlayerHitCheck_Normal(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (*mStateMgr.getStateID() == StateID_Sleep)
        return playerHitCheck_Sleep(cc_self, cc_other);

    if (*mStateMgr.getStateID() == StateID_Carry)
        return playerHitCheck_Carry(cc_self, cc_other);

    return playerHitCheck_Awake(cc_self, cc_other);
}

void CarryEnemy::reactFumiProc(Actor* p_player)
{
    if (p_player != nullptr)
    {
    }
}

void CarryEnemy::reactMameFumiProc(Actor* p_player)
{
    if (p_player != nullptr)
    {
    }
}

void CarryEnemy::reactSpinFumiProc(Actor* p_player)
{
    setDeathInfo_SpinFumi(p_player);
}

bool CarryEnemy::fumiProcCheck(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    switch (fumiCheck(cc_self, cc_other, cFumiSeType_Normal))
    {
    default:
        break;
    case cFumiType_Fumi:
        reactFumiProc(cc_other->getOwner());
        return true;
    case cFumiType_MameFumi:
        reactMameFumiProc(cc_other->getOwner());
        return true;
    case cFumiType_SpinFumi:
        reactSpinFumiProc(cc_other->getOwner());
        return true;
    }
    return false;
}

void CarryEnemy::playerHitCheck_Awake(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (fumiProcCheck(cc_self, cc_other))
        return;

    Enemy::vsPlayerHitCheck_Normal(cc_self, cc_other);
}

bool CarryEnemy::sleepSpinFumiProcCheck_(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_player = cc_other->getOwner();

    if (!sead::DynamicCast<PlayerObject>(p_player)->isStatus(PlayerObject::cStatus_Spin))
        return false;

    if (fumiCheck(cc_self, cc_other, cFumiSeType_Normal) != cFumiType_SpinFumi)
        return false;

    reactSpinFumiProc(p_player);
    return true;
}

void CarryEnemy::playerHitCheck_Sleep(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (sleepSpinFumiProcCheck_(cc_self, cc_other))
        return;

    if (carryCheck(cc_other->getOwner()))
        return;

    playerHitCheck_Sleep_Base(cc_self, cc_other);
}

void CarryEnemy::playerHitCheck_Carry_Base(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    fumiProcCheck(cc_self, cc_other);
}

void CarryEnemy::playerHitCheck_Carry(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    PlayerObject* p_player_obj = cc_other->getOwner<PlayerObject>();
    if (p_player_obj == nullptr)
        return;

    if (p_player_obj->getCarryActorID() == mActorUniqueID)
        return;

    playerHitCheck_Carry_Base(cc_self, cc_other);
}

void CarryEnemy::playerHitCheck_Sleep_Base(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
}

bool CarryEnemy::hitCallback_Ice(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    cancelCarry();
    mPlayerNo = -1;
    return Enemy::hitCallback_Ice(cc_self, cc_other);
}

bool CarryEnemy::hitCallback_Shell(ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    Actor* p_actor_other = cc_other->getOwner();
    if (p_actor_other == nullptr)
        return false;

    if (cc_self->getAttack() == ActorCollisionCheck::cAttack_Shell &&
        !cc_other->hasStatus(ActorCollisionCheck::cStatus_SlideKill) &&
        (p_actor_other->getActorType() != cActorType_Generic || (p_actor_other->getProfFlag() & Profile::cFlag_Unk7)))
    {
        u32 fall_dir = ActorUtil::getTrgToSrcDir(*this, *p_actor_other);

        s32 kill_player_no = -1;
        bool carried = checkCarried(&kill_player_no);
        if (!carried)
            kill_player_no = p_actor_other->getPlayerNo();

        ScoreMgr::ScoreType combo_score = ScoreMgr::cScoreType_Invalid;
        if (0 <= kill_player_no && kill_player_no < 4)
        {
            p_actor_other->incComboCnt();
            combo_score = mCombo.getComboScore(p_actor_other->getComboCnt());
        }

        f32 fall_speed_x_factor = carried ? 0.7f : 1.0f;

        const sead::Vector2f c_dead_speed[cDirType_NumX] = {
            sead::Vector2f(
                cDieFallInitSpeedX[cDirType_Right] * fall_speed_x_factor,
                cDieFallInitSpeedY
            ),
            sead::Vector2f(
                cDieFallInitSpeedX[cDirType_Left] * fall_speed_x_factor,
                cDieFallInitSpeedY
            )
        };
        setDeathInfo_Fall(c_dead_speed, fall_dir, kill_player_no, combo_score);

        bool eff_set = true;
        if (cc_other->getAttack() == ActorCollisionCheck::cAttack_Shell)
        {
            if (!mForceSetShellDamageEffect)
            {
                CarryEnemy* p_carry_en_other = sead::DynamicCast<CarryEnemy>(p_actor_other);
                if (p_carry_en_other != nullptr)
                {
                    p_carry_en_other->mForceSetShellDamageEffect = true;
                    return true;
                }
            }
        }
        else if (carried)
        {
            eff_set = false;
        }
        if (eff_set)
        {
            sead::Vector2f center_point = (cc_self->getCenterPos() + cc_other->getCenterPos()) * 0.5f;
            hitdamageEffect(sead::Vector3f(center_point, 0.0f));

            if ((0 <= kill_player_no && kill_player_no < 4) &&
                (0 <= p_actor_other->getPlayerNo() && p_actor_other->getPlayerNo() < 4))
            {
                p_actor_other->slideComboSE(p_actor_other->getComboCnt() - 1, false);
                return true;
            }

            GameAudio::getAudioObjEmy()->startSound("SE_EMY_DOWN", mPos);
        }
        return true;
    }
    else
    {
        return Enemy::hitCallback_Shell(cc_self, cc_other);
    }
}

bool CarryEnemy::hitCallback_AttackUnk27(bool* p_dead, ActorCollisionCheck* cc_self, ActorCollisionCheck* cc_other)
{
    if (cc_self->getAttack() == ActorCollisionCheck::cAttack_Shell && *mStateMgr.getStateID() == StateID_Carry)
        *p_dead = hitCallback_Shell(cc_self, cc_other);
    return true;
}

void CarryEnemy::setSlidePlayerParam(Actor* p_player)
{
    s32 player_no = p_player->getPlayerNo();
    if (mPlayerNo != player_no)
        clrComboCnt();
    mPlayerNo = player_no;
    mDirection = ActorUtil::getTrgToSrcDir(*this, *p_player);
}

void CarryEnemy::calcCarryPos(sead::Vector3f* p_pos, PlayerObject* p_player_obj)
{
    if (p_pos != nullptr)
    {
        sead::Matrixf carry_mtx;
        if (p_player_obj->getCarryMtx(&carry_mtx))
        {
            sead::Vector3f carry_add_offset = sead::Vector3f::zero;
            if (p_player_obj->getCarryStep() == PlayerObject::cCarryStep_Carry)
            {
                f32 t = 1.0f - p_player_obj->getCarryStepRatio();
                if (t < 0.0f)
                    t = 0.0f;
                else if (t > 1.0f)
                    t = 1.0f;

                carry_add_offset = cCarryStepOffset * t * sead::Mathf::sinIdx(p_player_obj->getAngle().x());
            }
            sead::Vector3f carry_offset =
                (p_player_obj->getPlayerMode() == cPlayerMode_Penguin)
                    ? (mCarryBaseOffset + carry_add_offset + sead::Vector3f(0.0f, -2.0f, -2.0f))
                    : (mCarryBaseOffset + carry_add_offset);
            carry_mtx.multTranslationLocal(carry_offset);
            carry_mtx.getTranslation(*p_pos);
        }
        else
        {
            *p_pos = mPos;
        }
    }
}

void CarryEnemy::adjustCarryCc(ActorCollisionCheck* p_cc, PlayerObject* p_player_obj)
{
    if (p_cc != nullptr)
    {
        sead::Vector2f center_offset(mPreCarryCcCenterOffset.x, mPreCarryCcCenterOffset.y);
        sead::Vector2f half_size(mPreCarryCcHalfSize.x, mPreCarryCcCenterOffset.y); // Is the Y value a mistake?
        if (p_player_obj->getTallType() == cTallType_Normal)
        {
            center_offset.x += -1.0f;
            center_offset.y += 1.0f;
            half_size.x += -1.0f;
            half_size.y += 1.0f;
        }
        if (!p_player_obj->isStatus(PlayerObject::cStatus_IgnoreBgCross) && p_player_obj->isNowBgCross(PlayerObject::cBgCross_IsFoot))
        {
            ActorBgCollisionCheck* p_bc_pl = p_player_obj->getBgCheck();
            if (p_bc_pl != nullptr && p_bc_pl->isSaka())
            {
                Angle angle = p_bc_pl->getSakaAngle(p_player_obj->getDirection());
                if (angle < 0)
                {
                    f32 y_offset = sead::Mathf::sinIdx(angle) * 5.0f;
                    half_size.y += sead::Mathf::abs(y_offset) * 0.5f;
                    center_offset.y += y_offset;
                }
            }
        }
        if (p_player_obj->isStatus(PlayerObject::cStatus_62))
        {
            center_offset.x += sead::Mathf::sinIdx(p_player_obj->getAngle().y()) * 3.0f;
            center_offset.y += 5.0f;
        }
        p_cc->setCenterOffset(center_offset);
        p_cc->setHalfSize(half_size);
    }
}

void CarryEnemy::initializeState_Carry()
{
    mPreCarryCcCenterOffset = mCollisionCheck.getCenterOffset();
    mPreCarryCcHalfSize = mCollisionCheck.getHalfSize();

    mCarryChangePosZ = mPos.z;

    mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Killer);
    mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Unk10);
    mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_Shell);

    mProfFlag &= ~Profile::cFlag_DrawCullCheck;

    mBgCheckObj.clearBg();

    mNoWaterCalc = true;
}

void CarryEnemy::executeState_Carry()
{
    PlayerObject* p_player_obj = getCarryPlayerObject();
    if (p_player_obj == nullptr)
    {
        setPutOnChangeState(nullptr);
        return;
    }

    if (mCarryFlag & cCarryFlag_Release)
    {
        mDirection = mCarryDirection;
        mAngle.y() = cBaseAngleY[mDirection];

        if (mCarryFlag & cCarryFlag_Throw)
            mPos.x += cEnMuki[mDirection] * 6.0f;

        if (carryCheckBg(p_player_obj))
        {
            setDeathInfo_CarryBgIn(p_player_obj, true);
            return;
        }

        mBgCheckObj.checkBg();

        if (mCarryFlag & cCarryFlag_Throw)
            return setThrowChangeState(p_player_obj, mCarryFlag & cCarryFlag_ThrowHard);
        else
            return setPutOnChangeState(p_player_obj);
    }

    Angle miss_spin_angle = p_player_obj->getMissSpinAngle();
    mAngle.y() = p_player_obj->getAngle().y() + miss_spin_angle;

    sead::Vector3f carry_pos;
    calcCarryPos(&carry_pos, p_player_obj);
    mPos = carry_pos;
    mPosPrev = carry_pos;
    mPosPrev2 = carry_pos;

    adjustCarryCc(&mCollisionCheck, p_player_obj);
}

void CarryEnemy::finalizeState_Carry()
{
    mCollisionCheck.setCenterOffset(mPreCarryCcCenterOffset);
    mCollisionCheck.setHalfSize(mPreCarryCcHalfSize);

    mCarryChangePosZ = mPos.z;

    mIsLiftUp = false;

    mCollisionCheck.offVsKind(ActorCollisionCheck::cTargetKind_Killer);
    mCollisionCheck.onVsKind(ActorCollisionCheck::cTargetKind_Unk10);
    mCollisionCheck.setAttack(ActorCollisionCheck::cAttack_None);

    cancelCarry();

    mBgCheckObj.clearBg();

    mProfFlag |= Profile::cFlag_DrawCullCheck;
    mNoWaterCalc = false;
    mCarryFlag &= ~cCarryFlag_All;
}

void CarryEnemy::initializeState_Sleep()
{
}

void CarryEnemy::executeState_Sleep()
{
}

void CarryEnemy::finalizeState_Sleep()
{
}

void CarryEnemy::initializeState_Slide()
{
    startSlide();
    mNoHitPlayerTimer[mPlayerNo] = cShellSlideNoHitTimer;
}

void CarryEnemy::executeState_Slide()
{
}

void CarryEnemy::finalizeState_Slide()
{
    endSlide();
}
