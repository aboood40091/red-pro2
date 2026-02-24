#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>
#include <utility/MathUtil.h>

f32 PlayerBase::getSlipMaxSpeedF()
{
    if (isNowBgCross(cBgCross_IsSaka))
        return 4.0f * cDirSpeed[mBgCheckPlayer.getSakaDir()];

    return 0.0f;
}

void PlayerBase::initializeState_Slip()
{
    mAction = cSlipAction_Move;
    mpModelBaseMgr->setAnm(PlayerAnmID::slip, 0.0f);
    mMaxSpeedF = getSlipMaxSpeedF();
    mActionTimer = 8;
    _21e4 = 0;
    onStatus(cStatus_73);
    onStatus(cStatus_196);
    onStatus(cStatus_135);
}

bool PlayerBase::checkSlipEndKey()
{
    if (isNowBgCross(cBgCross_IsFoot))
    {
        if (!mPlayerKey.buttonDown())
        {
            if (mSakaType == ActorBgCollisionCheck::cSakaType_None)
            {
                if (mPlayerKey.buttonCross())
                    return true;
            }
            else if (mSakaType != ActorBgCollisionCheck::cSakaType_VerySteep)
            {
                if (mPlayerKey.buttonLeft() && mBgCheckPlayer.getSakaDir() == ActorBgCollisionCheck::cSakaDir_Right)
                    return true;
                if (mPlayerKey.buttonRight() && mBgCheckPlayer.getSakaDir() == ActorBgCollisionCheck::cSakaDir_Left)
                    return true;
            }
        }
        if (mPlayerKey.buttonUp())
            return true;
    }
    return false;
}

void PlayerBase::changeActionSlipEnd(AnmBlend blend)
{
    if ((mPlayerKey.buttonLeft() && mDirection == cDirType_Right && mSpeedF > 0.0f) ||
        (mPlayerKey.buttonRight() && mDirection == cDirType_Left && mSpeedF < 0.0f))
    {
        mAngle.y() = getMukiAngle();
        mDirection = InvDirX(mDirection);
        changeState(StateID_Turn, 0);
    }
    else
    {
        if ((mPlayerKey.buttonLeft() && mDirection == cDirType_Right && mSpeedF < 0.0f) ||
            (mPlayerKey.buttonRight() && mDirection == cDirType_Left && mSpeedF > 0.0f))
        {
            mAngle.y() = getMukiAngle();
            mDirection = InvDirX(mDirection);
        }
        changeState(StateID_Walk, blend);
    }
}

bool PlayerBase::setSlipAction_ToEnd(AnmBlend blend)
{
    if (checkStandUpRoof())
        return false;

    offStatus(cStatus_73);
    if (isStatus(cStatus_PenguinSlide))
        offStatus(cStatus_PenguinSlide);

    mAction = cSlipAction_ToEnd;
    mSpeedF = 0.0f;
    mMaxSpeedF = 0.0f;

    if (blend != cAnmBlend_Disable)
        mpModelBaseMgr->setAnm(PlayerAnmID::sliped, 0.0f);
    else
        mpModelBaseMgr->setAnm(PlayerAnmID::sliped, 0.0f, 0.0f);

    return true;
}

void PlayerBase::setSlipActionViewLimitEnd()
{
    offStatus(cStatus_73);
    if (!mPlayerKey.buttonCrouch())
        setSlipAction_ToEnd();
    else
    {
        // Hardcode for NSMBW 1-6 (removed in NSMBU)
        // ...
    }
}

bool PlayerBase::checkSakaReverse()
{
    if (sead::Mathf::abs(mSpeedF) < 0.5f && mBgCheckPlayer.isSakaReverse())
        return true;
    return false;
}

void PlayerBase::setSlipActionEnd()
{
    offStatus(cStatus_73);
    if (!mPlayerKey.buttonCrouch())
        setSlipAction_ToEnd();
}

void PlayerBase::slipActionMove(bool turned)
{
    if (isNowBgCross(cBgCross_IsFoot) &&
        (sead::Mathf::abs(mSpeedF) > 0.1f ||
         (isSlipSaka() && sead::Mathf::abs(mPosDelta.x) > 0.1f)))
    {
        setSlipEffect();
    }

    onStatus(cStatus_73);

    if (isOldBgCross(cBgCross_IsFoot) &&
        sead::Mathf::idx2deg(mBaseSakaAngle) * sead::Mathf::idx2deg(mBaseSakaAnglePrev) <= 0.0f)
    {
        Angle angle = mSpeedSakaAnglePrev;
        if (angle > 0 || !isNowBgCross(cBgCross_IsFoot))
        {
            if (angle <= 0) // ???
                angle = angle * 0.5f; // Dear Nintendo, why not just angle / 2?

            offNowBgCross(cBgCross_IsFoot);

            f32 sin_v, cos_v;
            sead::Mathf::sinCosIdx(&sin_v, &cos_v, (u32)angle);

            f32 base_speed = mSpeedF;

            mSpeedF = base_speed * cos_v;
            mMaxSpeedF = mSpeedF;

            mSpeed.y = sead::Mathf::abs(base_speed) * sin_v;
        }
    }

    if (isNowBgCross(cBgCross_IsFoot))
    {
        if (isNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand))
            setSlipAction_ToEnd();
        else if (mSpeedF <= 0.0f && isNowBgCross(cBgCross_DispSideLimitL))
            setSlipActionViewLimitEnd();
        else if (checkSakaReverse())
            setSlipActionEnd();
        else
        {
            if (isNowBgCross(cBgCross_IsSaka)) // TODO: Decomp reloads int (due to non-inline call to checkSakaReverse), but original doesn't
            {
                _21e8 = 3;
                mActionTimer = 8;
                mMaxSpeedF = getSlipMaxSpeedF();
                if (getSakaUpDown() == cSakaUpDown_Downhill)
                {
                    if (!turned)
                        mAccelF *= 0.5f;
                    if (sead::Mathf::abs(mSpeedF) < 1.0f &&
                        ((mCollisionCheck3_React.getRevisionX(ActorCollisionCheck::cKind_PlayerBody) < 0.0f && mSpeedF >= 0.0f) ||
                         (mCollisionCheck3_React.getRevisionX(ActorCollisionCheck::cKind_PlayerBody) > 0.0f && mSpeedF <= 0.0f)))
                    {
                        setSlipActionEnd();
                    }
                    bool cross_wall = false;
                    if (mBgCheckPlayer.getSakaDir() == ActorBgCollisionCheck::cSakaDir_Right)
                    {
                        if (checkBGCrossWall(cDirType_Right))
                            cross_wall = true;
                    }
                    else
                    {
                        if (checkBGCrossWall(cDirType_Left))
                            cross_wall = true;
                    }
                    if (cross_wall)
                        setSlipActionEnd();
                }
            }
            else
            {
                mActionTimer = 0;
                mMaxSpeedF = 0.0f;
                // Remaining code has been moved to checkSlipMoveEnd in NSMBU
            }
        }
    }
    else
    {
        if (mActionTimer != 0)
        {
            mAccelY = 0.0f;
            onStatus(cStatus_197);
        }
        else
        {
            offStatus(cStatus_197);
        }
    }
}

void PlayerBase::executeState_Slip()
{
    gravitySet();
    maxFallSpeedSet();
    moveSpeedSet();
    powerSet();

    MathUtil::calcTimer(&_21e4);

    Angle base_angle = 0;
    if (isNowBgCross(cBgCross_IsFoot))
        base_angle = getSakaAngle() * 0.3f;

    mAngle.x().addCalcAngle(-base_angle, 1.0f / 4, 0x20000000, 0x1000000);

    bool turned = turnAngle();

    if (isNowBgCross(cBgCross_Slip))
        _21e4 = 9;
    else
    {
        if (checkJumpTrigger())
            return;

        if (turned && _21e4 == 0 && checkSlipEndKey())
        {
            changeActionSlipEnd(cAnmBlend_Disable);
            return;
        }
    }

    switch (mAction)
    {
    default:
        break;
    case cSlipAction_Move:
        if (!isNowBgCross(cBgCross_IsFoot) && (mPlayerKey.triggerJump() || mPlayerKey.triggerCross()))
            changeState(StateID_Fall, cAnmBlend_Enable);
        else
        {
            setCcAtSlip();
            slipActionMove(turned);
            checkSlipMoveEnd();
        }
        break;
    case cSlipAction_1:
        // Does nothing
        break;
    case cSlipAction_ToStoop:
        mMaxSpeedF = 0.0f;
        if (mpModelBaseMgr->isAnmStop() || isTotten())
            changeState(StateID_Crouch, 1);
        break;
    case cSlipAction_ToEnd:
        mMaxSpeedF = 0.0f;
        if (mpModelBaseMgr->isAnmStop())
            changeActionSlipEnd(cAnmBlend_Enable);
        break;
    }
}

void PlayerBase::finalizeState_Slip()
{
    offStatus(cStatus_73);
    offStatus(cStatus_196);
    offStatus(cStatus_135);
    mAngle.x() = 0;
}

bool PlayerBase::checkSlip()
{
    if (mPenguinSlideCooldown != 0)
        return false;

    if (mSpeedF > 0.0f || !isNowBgCross(cBgCross_DispSideLimitL))
    {
        if (isNowBgCross(cBgCross_Slip) && isSlipSaka())
        {
            setSlipAction();
            return true;
        }
    }
    return false;
}

bool PlayerBase::checkCrouchSlip()
{
    if (isNowBgCross(cBgCross_IsUnderwater))
        return false;

    if (mPenguinSlideCooldown != 0)
        return false;

    if (mSpeedF > 0.0f || !isNowBgCross(cBgCross_DispSideLimitL))
    {
        if (isNowBgCross(cBgCross_Slip) && isSlipSaka())
        {
            setSlipAction();
            return true;
        }
    }
    return false;
}

void PlayerBase::setSlipAction_ToStoop()
{
    offStatus(cStatus_73);
    if (isStatus(cStatus_PenguinSlide))
        offStatus(cStatus_PenguinSlide);
    mAction = cSlipAction_ToStoop;
    mpModelBaseMgr->setAnm(PlayerAnmID::slip_to_stoop, 0.0f);
}

void PlayerBase::forceSlipToStoop()
{
    mPenguinSlideCooldown = 30;
    setSlipAction_ToStoop();
}
