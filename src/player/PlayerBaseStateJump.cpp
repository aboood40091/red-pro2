#include <player/PlayerBase.h>
#include <player/PlayerModelBaseMgr.h>

bool PlayerBase::setWaitJumpAction()
{
    if (isDemo())
        return false;

    changeState(StateID_WaitJump, 0);
    return true;
}

void PlayerBase::initializeState_Jump()
{
    onStatus(cStatus_166);
    onStatus(cStatus_172);
    offStatus(cStatus_147);
    if (_21e0 != 0)
        onStatus(cStatus_116);

    if (isOnSinkSand())
    {
        setJumpSandSinkRate();
        if (!isNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand))
        {
            mPlayerKey.onStatus(PlayerKey::cStatus_ForceJump);
            onStatus(cStatus_200);
        }
    }
}

void PlayerBase::executeState_Jump()
{
    if (_21e0 == 0)
        offStatus(cStatus_116);

    if (isStatus(cStatus_172))
    {
        if (!mPlayerKey.buttonJump() || isNowBgCross(cBgCross_IsHead))
        {
            mAudioObj.stopPlyJumpSound();
            offStatus(cStatus_172);
        }
        if (mSpeed.y <= 1.0f)
            offStatus(cStatus_172);
    }

    onStatus(cStatus_Jump);
}

void PlayerBase::finalizeState_Jump()
{
    mAngle.x() = 0;

    if (isStatus(cStatus_172))
        mAudioObj.stopPlyJumpSound();

    offStatus(cStatus_Jump);
    offStatus(cStatus_UnkJumpGravity);
    offStatus(cStatus_147);
    offStatus(cStatus_172);
    offStatus(cStatus_200);
    offStatus(cStatus_204);
    offStatus(cStatus_166);
    offStatus(cStatus_116);

    _21e0 = 0;

    mPlayerKey.offStatus(PlayerKey::cStatus_ForceJump);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoCross);
}

void PlayerBase::initializeState_Fall()
{
    onStatus(cStatus_Fall);
    onStatus(cStatus_166);
    if (_21e0 != 0)
        onStatus(cStatus_116);

    if (mChangeStateParam == cAnmBlend_Enable)
        mpModelBaseMgr->setAnm(PlayerAnmID::jump2, 10.0f, 0.0f);
    else
        mpModelBaseMgr->setAnm(PlayerAnmID::jump2, 0.0f, 0.0f);

    initAirDriftSpeedF(mAirDriftSpeedFStart, 10.0f);
}

void PlayerBase::executeState_Fall()
{
    if (_21e0 == 0)
        offStatus(cStatus_116);
}

void PlayerBase::finalizeState_Fall()
{
    offStatus(cStatus_Fall);
    offStatus(cStatus_147);
    offStatus(cStatus_166);
    offStatus(cStatus_116);

    _21e0 = 0;
}

void PlayerBase::initializeState_Land()
{
}

void PlayerBase::executeState_Land()
{
}

void PlayerBase::finalizeState_Land()
{
}

void PlayerBase::initializeState_SitJump()
{
}

void PlayerBase::executeState_SitJump()
{
}

void PlayerBase::finalizeState_SitJump()
{
}

void PlayerBase::initializeState_WaitJump()
{
    onStatus(cStatus_WaitJump);
    mPlayerKey.onStatus(PlayerKey::cStatus_NoJump);
    mpModelBaseMgr->setAnm(PlayerAnmID::wait, 0.0f);
    mAngle.y() = getMukiAngle();
}

void PlayerBase::executeState_WaitJump()
{
    gravitySet();
    maxFallSpeedSet();
    moveSpeedSet();
    airPowerSet();

    if (mSpeed.y <= 0.0f)
        changeState(StateID_Fall, cAnmBlend_Enable);
}

void PlayerBase::finalizeState_WaitJump()
{
    offStatus(cStatus_WaitJump);
    mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);
}

bool PlayerBase::setWaitJump_(f32 speed_y)
{
    if (!setWaitJumpAction())
        return false;

    mSpeedF = 0.0f;
    mSpeed.y = speed_y;
    startQuakeShock(Quake::cShockType_5);
    return true;
}

bool PlayerBase::setWaitJump()
{
    if (isNowBgCross(cBgCross_IsFoot))
        if (setWaitJump_(4.0f))
            return true;

    return false;
}

void PlayerBase::setJumpSpeed()
{
    mSpeed.y = getJumpSpeed();
}

// From NSMBW:
#define JUMP_SPEED_NUMA_1 3.5f
#define JUMP_SPEED_NUMA_2 2.3f
// New in NSMBU:
#define JUMP_SPEED_NUMA_3 2.65f
#define JUMP_SPEED_NUMA_4 2.6f

f32 PlayerBase::getJumpSpeedBase()
{
    f32 speed = cJumpSpeed;
    if (isOnSinkSand())
    {
        if (mPos.y >= mSinkSandSurfacePosY - 7.0f)
            speed = JUMP_SPEED_NUMA_1;
        else
        {
            if (mMode == cPlayerMode_Mini)
                speed = JUMP_SPEED_NUMA_2;
            else
            {
                if (isNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand))
                    speed = JUMP_SPEED_NUMA_3;
                else
                    speed = JUMP_SPEED_NUMA_4;
            }
        }
    }
    else
    {
        speed += getMoveJumpSpeed();
    }
    return speed;
}
