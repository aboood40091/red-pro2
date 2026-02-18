#include <actor/ActorMgr.h>
#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>

static s32 sPlayerJumpDaiReductionScaleNumFrame = 5;

void PlayerBase::initializeState_JumpDai()
{
    onStatus(cStatus_40);
    onStatus(cStatus_145);
    mPlayerKey.onStatus(PlayerKey::cStatus_NoCross);

    mJumpDaiSpeedFReserve = mSpeedF * 0.7f;

    f32 speed = mSpeedF;
    if (speed < -0.5f)
        speed = -0.5f;
    else if (speed > 0.5f)
        speed = 0.5f;
    mSpeedF = speed;

    if (mpModelBaseMgr->getAnmID() == PlayerAnmID::stoop)
        mAction = cJumpDaiAction_1;
    else
        mpModelBaseMgr->setAnm(PlayerAnmID::jumped, 0.0f);
}

void PlayerBase::executeState_JumpDai()
{
    if (!isStatus(cStatus_145))
    {
        setFallAction();
        return;
    }

    turnAngle();

    if (mAction == cJumpDaiAction_0)
    {
        if (mpModelBaseMgr->isAnmStop())
        {
            setWaitActionAnm(cAnmBlend_Enable);
            mAction = cJumpDaiAction_1;
        }
    }
}

void PlayerBase::finalizeState_JumpDai()
{
    offStatus(cStatus_40);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoCross);
    mSpeedF = mJumpDaiSpeedFReserve;
}

PlayerBase* PlayerBase::getPlayerJumpDai()
{
    if (isStatus(cStatus_41))
    {
        PlayerBase* p_player_other = sead::DynamicCast<PlayerBase>(ActorMgr::instance()->getActorPtr(mRideActorID));
        if (p_player_other != nullptr && !p_player_other->isDemoMode() && !p_player_other->isStatus(cStatus_NoEntryReactCc))
            return p_player_other;
    }

    return nullptr;
}

void PlayerBase::initializeState_PlayerJumpDai()
{
    mRidePlayerPosDelta.set(0.0f, 0.0f, 0.0f);
    onStatus(cStatus_41);
    PlayerBase* p_player_other = getPlayerJumpDai();
    if (p_player_other != nullptr)
    {
        p_player_other->initStampReduction();
        setNoHitPlayer(p_player_other, 5);
        mRidePlayerPosDelta = mPos - p_player_other->mPos;
    }
    mJumpDaiSpeedFReserve = mSpeedF;
    mSpeedF = 0.0f;
    mSpeed.y = 0.0f;
    if (mpModelBaseMgr->getAnmID() != PlayerAnmID::stoop)
        mpModelBaseMgr->setAnm(PlayerAnmID::jumped, 0.0f);
    mAction = mPlayerKey.triggerJumpBuf(5) ? cPlayerJumpDaiAction_1 : cPlayerJumpDaiAction_0;
    mActionSubTimer = 0;
}

void PlayerBase::executeState_PlayerJumpDai()
{
    PlayerBase* p_player_other = getPlayerJumpDai();
    if (p_player_other == nullptr)
    {
        setFallAction();
        return;
    }

    if (isNowBgCross(cBgCross_IsHead))
    {
        setFallAction();
        _21e0 = 30;
        return;
    }

    f32 roof_pos;
    if (mBgCheckPlayer.checkTenjou(mPos, 32.0f, &roof_pos))
    {
        f32 max_pos = roof_pos - (sead::Mathf::abs(getHeadBgPointData()->center_offset) + 1.0f);
        if (mPos.y > max_pos)
        {
            mPos.y = max_pos;
            setFallAction();
            _21e0 = 30;
            return;
        }
    }

    setNoHitPlayer(p_player_other, 5);

    turnAngle();

    if (mpModelBaseMgr->getAnmID() == PlayerAnmID::jumped && mpModelBaseMgr->isAnmStop())
        setWaitActionAnm(cAnmBlend_Enable);

    switch (mAction)
    {
    default:
        break;
    case cPlayerJumpDaiAction_0:
        if (mActionSubTimer < sPlayerJumpDaiReductionScaleNumFrame)
        {
            if (mPlayerKey.triggerJump())
                mAction = cPlayerJumpDaiAction_1;
        }
        else
        {
            if (isMameAction())
                bouncePlayer1(cJumpSpeed - 0.35f, mJumpDaiSpeedFReserve, true, cBounceType_Normal, cJumpSe_None);
            else if (mChangeStateParam == 1)
                bouncePlayer1(cJumpSpeed + 0.2f, mJumpDaiSpeedFReserve, true, cBounceType_1, cJumpSe_None);
            else if (mPlayerKey.buttonJump())
                bouncePlayer1(cJumpSpeed + 0.2f, mJumpDaiSpeedFReserve, true, cBounceType_Normal, cJumpSe_High);
            else
                bouncePlayer1(cJumpSpeed + 1.0f, mJumpDaiSpeedFReserve, true, cBounceType_2, cJumpSe_None);
            setHopAirDrift();
            return;
        }
        break;
    case cPlayerJumpDaiAction_1:
        if (mActionSubTimer > sPlayerJumpDaiReductionScaleNumFrame)
        {
            f32 jump_speed = cJumpSpeed + 0.8f;
            if (isMameAction())
                jump_speed = cJumpSpeed + 0.2f;
            bouncePlayer1(jump_speed, 0.0f, true, cBounceType_1, cJumpSe_High);
            setHopAirDrift();
            return;
        }
        break;
    }

    p_player_other->calcJumpDaiReductionScale(mActionSubTimer, sPlayerJumpDaiReductionScaleNumFrame);
    mActionSubTimer++;
}

void PlayerBase::finalizeState_PlayerJumpDai()
{
    offStatus(cStatus_41);
    mRideActorID.invalidate();
}

bool PlayerBase::setJumpDaiRide()
{
    if (isStatus(cStatus_RidePlayer))
        return false;

    if (isNowBgCross(cBgCross_IsHead))
        return false;

    changeState(StateID_JumpDai, 0);
    return true;
}

bool PlayerBase::setPlayerJumpDai(PlayerBase* p_player_other)
{
    if (!mPlayerJumpDaiID.isValid())
    {
        f32 head_y = p_player_other->getHeadTopPosP()->y - 4.0f;
        sead::Vector3f check_pos(mPos.x, head_y, mPos.z);
        f32 roof_pos;
        if (!mBgCheckPlayer.checkTenjou(check_pos, 32.0f, &roof_pos) || roof_pos >= head_y + mHeight)
        {
            u32 param = 0;
            if (isStatus(cStatus_48) || isStatus(cStatus_52))
                param = 1;
            mRideActorID = p_player_other->getActorUniqueID();
            changeState(StateID_PlayerJumpDai, param);
            return true;
        }
    }
    return false;
}

void PlayerBase::setPlayerJumoDaiPos()
{
    PlayerBase* p_player_other = getPlayerJumpDai();
    if (p_player_other != nullptr)
    {
        sead::Vector3f head_top_pos;
        if (p_player_other->getHeadTopPos(head_top_pos))
        {
            mPos.set(
                head_top_pos.x + mRidePlayerPosDelta.x,
                head_top_pos.y,
                head_top_pos.z + mRidePlayerPosDelta.z
            );
        }
    }
}
