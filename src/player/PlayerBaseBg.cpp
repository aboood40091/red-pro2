#include <actor/ProfileID.h>
#include <collision/BgCollision.h>
#include <collision/BgCollisionCheckHitResult.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/Ice.h>
#include <game/AreaTask.h>
#include <map_obj/CarryObjBase.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scroll/BgScrollMgr.h>
#include <system/RDashMgr.h>

PlayerBase::BgAttr PlayerBase::getFootBgAttr(BgUnitCode::Attr attr)
{
    switch (attr)
    {
    case BgUnitCode::cIce:
        return cBgAttr_Ice;
    case BgUnitCode::cSnow:
        return cBgAttr_Snow;
    case BgUnitCode::cNuma:
        return cBgAttr_Sand;
    case BgUnitCode::cSand:
        return cBgAttr_Sand;
    case BgUnitCode::cGrass:
        return cBgAttr_Dirt;
    case BgUnitCode::cCloud:
        return cBgAttr_Cloud;
    case BgUnitCode::cBeachSand:
        return cBgAttr_Beach;
    case BgUnitCode::cManta:
        return cBgAttr_Manta;
    case BgUnitCode::cPalmTree:
        return cBgAttr_Leaf;
    case BgUnitCode::cWood:
        return cBgAttr_Wood;
    case BgUnitCode::cWater:
        return cBgAttr_Water2;
    case BgUnitCode::cCarpet:
        return cBgAttr_Carpet;
    case BgUnitCode::cNone:
    default:
        return cBgAttr_Rock;
    }
}

bool PlayerBase::checkLedge_()
{
    if (*mStateMgr.getStateID() != StateID_Walk)
        return false;

    if (sead::Mathf::abs(mSpeedF) < 2.0f)
        return false;

    if (mSpeedSakaAnglePrev < 0)
        return false;

    if (mSpeedSakaAngle >= 0)
        return false;

    BgCollisionCheckResultArea res;
    {
        sead::Vector3f check_pos(mPos.x, mPos.y + 8.0f, mPos.z);
        if (mSpeedF >= 0.0f)
            check_pos.x += 16.0f;
        else
            check_pos.x -= 16.0f;

        if (!mBgCheckPlayer.checkGround(check_pos, 16.0f, &res))
            return false;
    }

    if (res.hit_angle != 0)
        return false;

    if (sead::Mathf::abs(res.hit_pos.y - mPosPrev.y) > 1.0f)
        return false;


    if (mBgCheckPlayer.checkGround(sead::Vector3f(mPos.x, mPos.y + 4.0f, mPos.z), 8.0f))
        return false;

    if (mBgCheckPlayer.checkWall(sead::Vector3f(mPos.x, mPos.y - 4.0f, mPos.z), mSpeedF > 0.0f ? 16.0f : -16.0f))   // TODO: generates fsel
        return false;

    mPos.y = mPosPrev.y;
    mPosPrev2 = mPos;
    mPosPrev = mPos;
    mSpeed.y = 1.0f;
    offNowBgCross(cBgCross_IsFoot);
    mSpeedSakaAngle = 0;
    changeState(StateID_Fall, 1);
    return true;
}

bool PlayerBase::vsPlayerCarryPush_()
{
    static const u32 c_dir_type[cDirType_NumX] = { cDirType_Left, cDirType_Right };

    for (s32 i = 0; i < cDirType_NumX; i++)
    {
        BgCollision* p_bg_collision = mBgCheckPlayer.getHitBgCollisionWall(c_dir_type[i]);
        if (p_bg_collision == nullptr)
            continue;
        if (!p_bg_collision->isFlag(11))
            continue;

        PlayerObject* p_player = nullptr;

        CarryObjBase* p_carry_obj = p_bg_collision->getOwner<CarryObjBase>();
        if (p_carry_obj != nullptr)
            p_player = p_carry_obj->getCarryPlayer();

        Ice* p_ice = p_bg_collision->getOwner<Ice>();
        if (p_ice != nullptr && p_ice->getPlayerNo() != -1)
            p_player = PlayerMgr::instance()->getPlayerObject(p_ice->getPlayerNo());

        if (p_player != nullptr)
        {
            bool applied_other = false;
            f32 dist = mPos.x - p_player->mPos.x;
            f32 other_speed = p_player->mSpeedF;
            if (dist * other_speed > 0.0f)
            {
                static const f32 c_pushback_scale[cTallType_Num] = { 0.9f, 0.7f, 0.5f };
                const sead::Vector3f next_frame_add_speed(-(other_speed * c_pushback_scale[p_player->getTallType()]), 0.0f, 0.0f);
                p_player->mNextFrameSpeed += next_frame_add_speed;
                applied_other = true;
            }
            if (dist * mSpeedF < 0.0f)
            {
                setCcPlayerRevParam(mSpeedF);
                return true;
            }
            if (applied_other)
                return true;
        }
    }

    return false;
}

void PlayerBase::postBgCrossImpl_()
{
    if (isNowBgCross(cBgCross_IsHead))
    {
        if (_1b9c >= 5 && (mSpeed.y > 0.0f || isStatus(cStatus_119)))
            setHitBlockSE();
    }

    if (isNowBgCross(cBgCross_IsHead))
        _1b9c = 0;
    else
    {
        if (_1b9c < 5)
            _1b9c++;
    }

    if (isNowBgCross(cBgCross_IsHead) && mSpeed.y > 0.0f)
    {
        mSpeed.y = 0.0f;
        mNoGravityTimer = 0;
        onStatus(cStatus_179);
    }

    if (isNowBgCross(cBgCross_IsFoot))
    {
        if (isNowBgCross(cBgCross_IsBeltConveyorL) || isNowBgCross(cBgCross_IsBeltConveyorR))
            mBgSpeed = mBgCheckPlayer.getBgSpeed();

        mSpeed.y = cMaxFallSpeed_Foot;

        if (isNowBgCross(cBgCross_IsUnderwater) || isNowBgCross(cBgCross_IsHold))
            mSpeed.y = 0.0f;

        if (isNowBgCross(cBgCross_IsSlightlyInsideSinkSand) && !isStatus(cStatus_238))
        {
            mSpeed.y = 0.0f;
            mBgSpeed.set(0.0f, mSandSinkRate);
        }

        if (isSaka() || isStatus(cStatus_73))
            mSpeed.y = 0.0f;

        if (isStatus(cStatus_244))
            mSpeedF = 0.0f;

        if (isNowBgCross(cBgCross_IsWater) && !isNowBgCross(cBgCross_IsUnderwater))
            mBgAttr = cBgAttr_Water1;

        if (mLineSpinLiftID.isValid() && !isNowBgCross(cBgCross_IsLineSpinLift))
            mLineSpinLiftID.invalidate();

        checkLedge_();
    }

    if (!isNowBgCross(cBgCross_IsFoot) && isOldBgCross(cBgCross_OnRide))
    {
        mAddAirSpeedFStart = 0.0f;
        f32 delta = mPos.x - mPosPrev.x;
        if (sead::Mathf::abs(delta - mPosDelta.x) >= 0.01f && mPosDelta.x * delta >= 0.0f)
            mAddAirSpeedFStart = mPosDelta.x;
    }

    if (!isNowBgCross(cBgCross_74) &&
        !isStatus(cStatus_46) &&
        !isStatus(cStatus_47) &&
        !vsPlayerCarryPush_() &&
        ((isNowBgCross(cBgCross_IsWallTouchL) && mSpeedF < 0.0f) || (isNowBgCross(cBgCross_IsWallTouchR) && mSpeedF > 0.0f))
    )
    {
        mSpeedF = 0.0f;
        mSpeedFMax = 0.0f;
        mAddSpeedF = 0.0f;
        mAddAirSpeedF = 0.0f;
    }
}

void PlayerBase::setBcSensorFlagsImpl_()
{
    mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_13);
    mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_38);

    mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_13);
    mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_38);

    mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_13);
    mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_38);

    mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_3);
    mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_4);
    mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_13);
    mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_38);

    if (isStatus(cStatus_48))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_8);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
    }

    if (isStatus(cStatus_56) || isStatus(cStatus_52))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
    }

    if (isStatus(cStatus_73) && mSpeedSakaAnglePrev > 0)
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_0);

    if (checkDokanInKeyTrig(cDokanDir_Up))
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_50);

    if (isStatus(cStatus_131))
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_52);

    if (isStar())
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
    }

    if (isStatus(cStatus_119) || isStatus(cStatus_98) || isStatus(cStatus_97))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_22);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_23);
    }
}

void PlayerBase::clearBgSpeed()
{
    mBgSpeedPrev = mBgSpeed;
    mBgSpeed.set(0.0f, 0.0f);
    mAddBgSpeedF = 0.0f;
}

void PlayerBase::clearBgCheckInfo()
{
    mNowBgCross.reset();
    clearBgSpeed();
    mBgAttr = cBgAttr_Rock;
    mWaterDepthType = 0;
}

void PlayerBase::revSideLimitCommon(f32 x)
{
    if (mPos.x == x)
        return;

    s32 dir = cDirType_Right;
    if (mPos.x >= x)
        dir = cDirType_Left;

    if (!isStatus(cStatus_247))
    {
        Angle angle = mBgCheckPlayer.getSakaAngle(dir);
        if (angle != 0)
        {
            f32 sin_v, cos_v, tan_v;
            sead::Mathf::sinCosIdx(&sin_v, &cos_v, angle);

            if (-sead::Mathf::epsilon() <= cos_v && cos_v <= sead::Mathf::epsilon())
                tan_v = (sin_v > 0.0f) ? sead::Mathf::maxNumber() : -sead::Mathf::maxNumber();
            else
                tan_v = sin_v / cos_v;

            mPos.y += (x - mPos.x) * tan_v;
        }
    }

    mPos.x = x;
}

void PlayerBase::calcSideLimitMultL(f32 x)
{
    revSideLimitCommon(x);

    if (mSpeedF < 0.0f)
        mSpeedF = 0.0f;
}

void PlayerBase::calcSideLimitMultR(f32 x)
{
    revSideLimitCommon(x);

    if (mSpeedF > 0.0f)
        mSpeedF = 0.0f;
}

bool PlayerBase::checkDispSideLemit_()
{
    if (isStatus(cStatus_253))
        return false;

    if (isStatus(cStatus_252))
        return false;

    if (isStatus(cStatus_251))
        return false;

    if (AreaTask::instance()->getLoopType() == 1)
        return false;

    const BgScrollMgr& bg_scroll_mgr = *BgScrollMgr::instance();

    f32 limit_l = bg_scroll_mgr.getScreenLeft () + mDispSideLimitPad;
    f32 limit_r = bg_scroll_mgr.getScreenRight() - mDispSideLimitPad;

    if (mPos.x < limit_l)
    {
        onNowBgCross(cBgCross_DispSideLimitL);
        f32 limit_pos = bg_scroll_mgr.getScrollBound().getMin().x + mDispSideLimitPad;
        f32 pos = mPos.x;
        if (pos < limit_pos)
            pos = limit_pos;
        mPos.x = pos;

        // Cap speed when moving against display left side
        if (mSpeedF < 0.0f)
            mSpeedF = 0.0f;
    }

    switch (_20a4[cDirType_Left])
    {
    case 0:
        {
            if (mPos.x < limit_l)
            {
                if (isOldBgCross(cBgCross_CarryObjBgCarriedR) || !isOldBgCross(cBgCross_IsWallTouchR))
                {
                    calcSideLimitMultL(limit_l);
                    return true;
                }
                _20a4[cDirType_Left] = 1;
                _20ac[cDirType_Left] = mPos.x - limit_l;
            }
        }
        break;
    case 1:
        {
            if (mPos.x > limit_l)
                _20a4[cDirType_Left] = 0;

            f32 dist = mPos.x - limit_l;
            if (_20ac[cDirType_Left] < dist || isOldBgCross(cBgCross_IsWallTouchR))
                _20ac[cDirType_Left] = dist;

            if (mPos.x < limit_l + _20ac[cDirType_Left])
            {
                calcSideLimitMultL(limit_l + _20ac[cDirType_Left]);
                return true;
            }
        }
        break;
    }

    if (mPos.x > limit_r)
    {
        onNowBgCross(cBgCross_DispSideLimitR);
        f32 limit_pos = bg_scroll_mgr.getScrollBound().getMax().x - mDispSideLimitPad;
        f32 pos = mPos.x;
        if (pos > limit_pos)
            pos = limit_pos;
        mPos.x = pos;

        // BUG: Nintendo forgot to cap speed when moving against display right side
        // Fixed in NSLU only
        if (RDashMgr::instance()->isNSLU())
        {
            if (mSpeedF > 0.0f)
                mSpeedF = 0.0f;
        }
    }

    switch (_20a4[cDirType_Right])
    {
    case 0:
        {
            if (mPos.x > limit_r)
            {
                if (isOldBgCross(cBgCross_CarryObjBgCarriedL) || !isOldBgCross(cBgCross_IsWallTouchL))
                {
                    calcSideLimitMultR(limit_r);
                    return true;
                }
                _20a4[cDirType_Right] = 1;
                _20ac[cDirType_Right] = mPosPrev.x - limit_r;
            }
        }
        break;
    case 1:
        {
            if (mPos.x < limit_r)
                _20a4[cDirType_Right] = 0;

            f32 dist = mPos.x - limit_r;
            if (_20ac[cDirType_Right] > dist || isOldBgCross(cBgCross_IsWallTouchL))
                _20ac[cDirType_Right] = dist;

            if (mPos.x > limit_r + _20ac[cDirType_Right])
            {
                calcSideLimitMultR(limit_r + _20ac[cDirType_Right]);
                return true;
            }
        }
        break;
    }

    return false;
}

void PlayerBase::checkSideViewLemit()
{
    if (isStatus(cStatus_122))
        return;

    if (isStatus(cStatus_227))
        return;

    if (isStatus(cStatus_153))
        return;

    checkDispSideLemit_();
}

Angle PlayerBase::getSakaAngleBySpeed(f32 speed_F)
{
    Angle angle = mBgCheckPlayer.getSakaBaseAngle();
    if (speed_F < 0.0f)
        angle = -angle;
    return angle;
}

bool PlayerBase::checkOnHDokan(const u64& bc_data)
{
    if (BgUnitCode::getType(bc_data) == BgUnitCode::cType_Dokan)
    {
        switch (BgUnitCode::getTypeInfo(bc_data))
        {
        case BgUnitCode::cTypeInfo_Dokan_4:
        case BgUnitCode::cTypeInfo_Dokan_6:
        case BgUnitCode::cTypeInfo_Dokan_Pipe4:
            return true;
        }
    }
    return false;
}

bool PlayerBase::checkSinkSand()
{
    f32 surface_pos_y = 0.0f;
    sead::Vector3f check_pos(mPos.x, mPos.y + 32.0f, mPos.z);
    if (mBgCheckPlayer.checkQuicksand(check_pos, &surface_pos_y))
    {
        onNowBgCross(cBgCross_IsSinkSand);

        mSinkSandSurfacePosY = surface_pos_y;

        if (mSinkSandSurfacePosY > mPos.y)
            onNowBgCross(cBgCross_IsSlightlyInsideSinkSand);

        if (mSinkSandSurfacePosY > getCenterPos().y)
            onNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand);

        if (mSinkSandSurfacePosY > mPos.y + mCenterOffsetY)
            onNowBgCross(cBgCross_IsCompletelySubmergedInSinkSand);

        return true;
    }
    else
    {
        return false;
    }
}

bool PlayerBase::checkBgWall(u8 dir)
{
    if (!mBgCheckPlayer.checkWall(dir))
        return false;

    BgCollision* p_bg_collision = mBgCheckPlayer.getHitBgCollisionWall(dir);
    if (p_bg_collision != nullptr && p_bg_collision->isFlag(17))
        return false;

    return true;
}

namespace {

struct DirBits
{
    u32 bits[cDirType_NumX];

    u32 get(s32 dir) const
    {
        return bits[dir];
    }
};

}

void PlayerBase::checkBgCross_()
{
    static const DirBits c_bg_check_out_bit_wall = { { ActorBgCollisionCheck::Output::cBit_WallRCollision, ActorBgCollisionCheck::Output::cBit_WallLCollision } };

    onStatus(cStatus_250);

    onStatus(cStatus_CheckBg);
    mBgCheckPlayer.checkBg();
    offStatus(cStatus_CheckBg);

    if (isStatus(cStatus_248))
        return;

    mSpeedSakaAnglePrev = mSpeedSakaAngle;
    mSpeedSakaAngle = 0;
    mBaseSakaAnglePrev = mBaseSakaAngle;
    mBaseSakaAngle = 0;

    ActorBgCollisionCheck::Output& output = mBgCheckPlayer.getOutput();

    if (output.checkHeadEx())
    {
        onNowBgCross(cBgCross_IsHead);

        if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk14))
            onNowBgCross(cBgCross_76);

        if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk15))
            onNowBgCross(cBgCross_66);

        if (BgUnitCode::getType(mBgCheckPlayer.getBgCheckData(cDirType_Up)) == BgUnitCode::cType_Hold)
            onNowBgCross(cBgCross_IsHold);

        if (!output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk13))
            onNowBgCross(cBgCross_68);
        else
        {
            onNowBgCross(cBgCross_69);
            const BgCollision* p_bg_collision_head = mBgCheckPlayer.getHitBgCollisionHead();
            if (p_bg_collision_head != nullptr)
            {
                const Actor* p_actor_head = p_bg_collision_head->getOwner();
                if (p_actor_head != nullptr && p_actor_head->getProfileID() == ProfileID::cBgActorYukaMario)
                    onNowBgCross(cBgCross_HitBgActorYuka);
            }
        }
    }

    if (output.checkFoot())
    {
        mSpeedSakaAngle = getSakaAngleBySpeed(mSpeedF);
        mBaseSakaAngle = mBgCheckPlayer.getSakaBaseAngle();
        mSakaType = mBgCheckPlayer.getSakaType(mBgCheckPlayer.getSakaBaseAngle());

        bool is_saka = mBgCheckPlayer.isSaka();
        if (is_saka)
            onNowBgCross(cBgCross_IsSaka);

        if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk5))
            onNowBgCross(cBgCross_75);

        if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk6))
            onNowBgCross(cBgCross_67);

        if (mSpeedSakaAngle > 0 && isNowBgCross(cBgCross_IsHead))
        {
            sead::Vector3f check_pos(mPos.x, mPos.y + getHeadBgPointData()->center_offset, mPos.z);
            if (mBgCheckPlayer.checkRoof(check_pos, 8.0f))
                onNowBgCross(cBgCross_OnSakaUnderRoof);
        }

        const u64& bc_data_foot = mBgCheckPlayer.getBgCheckData(cDirType_Down);

        if (BgUnitCode::getType(bc_data_foot) == BgUnitCode::cType_BeltConveyor)
        {
            switch (BgUnitCode::getTypeInfo(bc_data_foot))
            {
            case BgUnitCode::cTypeInfo_BeltConveyor_Left:
            case BgUnitCode::cTypeInfo_BeltConveyor_Left_High:
                onNowBgCross(cBgCross_IsBeltConveyorL);
                break;
            case BgUnitCode::cTypeInfo_BeltConveyor_Right:
            case BgUnitCode::cTypeInfo_BeltConveyor_Right_High:
                onNowBgCross(cBgCross_IsBeltConveyorR);
                break;
            }
        }

        if (checkOnHDokan(bc_data_foot))
            onNowBgCross(cBgCross_IsOnHDokan);

        if (BgUnitCode::getType(bc_data_foot) == BgUnitCode::cType_Chikuwa)
        {
            onNowBgCross(cBgCross_IsChikuwa);

            const BgCollision* p_bg_collision_foot = mBgCheckPlayer.getHitBgCollisionFoot();
            if (p_bg_collision_foot != nullptr && p_bg_collision_foot->getType() == BgCollision::cType_DonutBlock)
                onNowBgCross(cBgCross_IsChikuwaActor);
        }

        switch (BgUnitCode::getSlipAttr(bc_data_foot))
        {
        case BgUnitCode::cSlipAttr_Slip:
            onNowBgCross(cBgCross_Slip);
            break;
        case BgUnitCode::cSlipAttr_SlideSlope:
            if (mSakaType == ActorBgCollisionCheck::cSakaType_None)
            {
                mSakaType = ActorBgCollisionCheck::cSakaType_Gentle;
                onNowBgCross(cBgCross_IsSaka);
            }
            onNowBgCross(cBgCross_Slip);
            break;
        case BgUnitCode::cSlipAttr_Unk6:
            onNowBgCross(cBgCross_SlipAttr6);
            break;
        }

        if (mSpeed.y <= 0.0f)
        {
            onNowBgCross(cBgCross_IsFoot);

            if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_OnHalf))
                onNowBgCross(cBgCross_OnHalf);

            if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_OnRide))
            {
                onNowBgCross(cBgCross_OnRide);

                if (mPosDelta.y > 0.0f)
                    onNowBgCross(cBgCross_32);

                BgCollision* p_bg_collision_foot = mBgCheckPlayer.getHitBgCollisionFoot();
                if (p_bg_collision_foot != nullptr)
                {
                    Actor* p_actor_foot = p_bg_collision_foot->getOwner();
                    if (p_actor_foot != nullptr)
                    {
                        if (p_actor_foot->getProfileID() == ProfileID::cLineSpinLift ||
                            p_actor_foot->getProfileID() == ProfileID::cLineSpinLiftParentRDash ||
                            p_actor_foot->getProfileID() == ProfileID::cLineSpinLiftChildRDash)
                        {
                            onNowBgCross(cBgCross_IsLineSpinLift);
                            mLineSpinLiftID = p_actor_foot->getActorUniqueID();
                        }
                        else if (p_actor_foot->getProfileID() == ProfileID::cActorBlockMakeDRC)
                        {
                            onNowBgCross(cBgCross_IsBlockDRC);
                        }
                        else if (p_actor_foot->getProfileID() == ProfileID::cLiftZenStar)
                        {
                            onNowBgCross(cBgCross_IsLiftZenStar);
                        }
                        else if (p_actor_foot->getProfileID() == ProfileID::cFloorGyration)
                        {
                            onNowBgCross(cBgCross_IsFloorGyration);
                        }
                        else if (p_actor_foot->getProfileID() == ProfileID::cIntermittent ||
                                 p_actor_foot->getProfileID() == ProfileID::cIntermittentPermanent ||
                                 p_actor_foot->getProfileID() == ProfileID::cWaterIntermittent ||
                                 p_actor_foot->getProfileID() == ProfileID::cWaterIntermittentPermanent ||
                                 p_actor_foot->getProfileID() == ProfileID::cWaterIntermittentBossChild ||
                                 p_actor_foot->getProfileID() == ProfileID::cWaterIntermittentPermanentRD3_3)
                        {
                            onNowBgCross(cBgCross_IsFunsui);
                        }
                    }
                }
            }

            if (BgUnitCode::getType(bc_data_foot) == BgUnitCode::cType_Kani)
            {
                if (isStatus(cStatus_99))
                {
                    BgCollisionCheckResultArea res;
                    sead::Vector3f check_pos(mPos.x, mPos.y + 2.0f, mPos.z);
                    if (mBgCheckPlayer.checkGround(check_pos, 4.0f, &res) && BgUnitCode::getType(res.bg_check_data) == BgUnitCode::cType_Kani)
                        onNowBgCross(cBgCross_IsKani);
                }
                else
                {
                    onNowBgCross(cBgCross_IsKani);
                }
            }

            BgUnitCode::Attr foot_attr = BgUnitCode::getAttr(bc_data_foot);
            if (isNowBgCross(cBgCross_IsSlightlyInsideSinkSand))
                foot_attr = BgUnitCode::cNuma;

            mBgAttr = getFootBgAttr(foot_attr);

            bool sand = false;
            switch (foot_attr)
            {
            case BgUnitCode::cSand:
                onNowBgCross(cBgCross_IsSand);
                sand = true;
                break;
            case BgUnitCode::cSnow:
                onNowBgCross(cBgCross_IsSnow);
                break;
            case BgUnitCode::cNuma:
                onNowBgCross(cBgCross_IsSand);
                onNowBgCross(cBgCross_IsSlightlyInsideSinkSand);
                sand = true;
                break;
            case BgUnitCode::cBeachSand:
                onNowBgCross(cBgCross_IsSand);
                break;
            case BgUnitCode::cIce:
                if (BgUnitCode::getSlipAttr(bc_data_foot) == BgUnitCode::cSlipAttr_IceLowSlip)
                    onNowBgCross(cBgCross_IsIceLowSlip);
                else
                    onNowBgCross(cBgCross_IsIce);
                break;
            case BgUnitCode::cWater:
                onNowBgCross(cBgCross_IsWaterAttr);
                break;
            }
            if (sand)
            {
                if (isNowBgCross(cBgCross_OnRide))
                    mBgAttr = cBgAttr_SandFunsui;
                else
                    mBgAttr = cBgAttr_Sand;
            }
        }
    }
    else
    {
        if (isStatus(cStatus_RideNatDone))
        {
            mPos.y = mRideNatPosY;
            mSpeedSakaAngle = 0;
            onNowBgCross(cBgCross_IsFoot);
        }

        s32 kani_type = 0;
        const f32 check_distance = 8.0f;
        sead::Vector3f check_pos(mPos.x, mPos.y + mCenterOffsetY + check_distance, mPos.z);
        if (mBgCheckPlayer.checkKani(&kani_type, &mKaniPosY, check_pos, check_distance))
        {
            if (kani_type != 0) // Fun fact, this is never true (ActorBgCollisionPlayerCheck::checkKani does not modify the parameter)
                onNowBgCross(cBgCross_IsKani3);
            else
                onNowBgCross(cBgCross_IsKani2);
        }
    }

    if (mSpeed.y < 0.0f && (isStatus(cStatus_40) || isStatus(cStatus_41) || isStatus(cStatus_119)))
    {
        onNowBgCross(cBgCross_IsFoot);
        onNowBgCross(cBgCross_OnRide);
        onNowBgCross(cBgCross_47);
    }

    if (output.checkFoot())
        onNowBgCross(cBgCross_47);
    else
    {
        if (mBgCheckPlayer.checkGround(mPos, 16.0f))
            onNowBgCross(cBgCross_47);
    }

    checkSinkSand();

    if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk24))
        onNowBgCross(cBgCross_74);

    if (output.checkLeftWallEx() || isStatus(cStatus_46))
        onNowBgCross(cBgCross_IsWallTouchL);

    if (output.checkRightWallEx() || isStatus(cStatus_47))
        onNowBgCross(cBgCross_IsWallTouchR);

    if (isNowBgCross(cBgCross_IsWallTouchL) || isNowBgCross(cBgCross_IsWallTouchR))
    {
        mWallAngle = mBgCheckPlayer.getWallAngle(mDirection);

        if (mSpeed.x < 0.0f)
        {
            if (isNowBgCross(cBgCross_IsWallTouchL))
                onNowBgCross(cBgCross_IsWall);
        }
        else if (mSpeed.x > 0.0f)
        {
            if (isNowBgCross(cBgCross_IsWallTouchR))
                onNowBgCross(cBgCross_IsWall);
        }
        else
        {
            if (output.isOnBit(c_bg_check_out_bit_wall.get(mDirection)))
                onNowBgCross(cBgCross_IsWall);
        }
    }

    checkCarryObjBgCarried_(output, cDirType_Left);
    checkCarryObjBgCarried_(output, cDirType_Right);

    if (checkBgWall(cDirType_Right))
        onNowBgCross(cBgCross_IsWallPressR);

    if (checkBgWall(cDirType_Left))
        onNowBgCross(cBgCross_IsWallPressL);

    if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk26))
        onNowBgCross(cBgCross_16);

    if (output.isOnBit(ActorBgCollisionCheck::Output::cBit_Unk27))
        onNowBgCross(cBgCross_17);

    if (!isNowBgCross(cBgCross_IsFoot))
    {
        if (isOldBgCross(cBgCross_IsFoot))
            _4e4 = mPos.y;
        else
        {
            if (_4e4 < mPos.y)
                _4e4 = mPos.y;
        }
    }
}

void PlayerBase::checkCarryObjBgCarried_(const ActorBgCollisionCheck::Output& output, u8 dir)
{
    static const DirBits c_bg_check_out_bit_carry_related = { { ActorBgCollisionCheck::Output::cBit_CarryRelatedR, ActorBgCollisionCheck::Output::cBit_CarryRelatedL } };
    static const DirBits c_bg_cross_bit_carry_related = { { PlayerBase::cBgCross_CarryRelatedR, PlayerBase::cBgCross_CarryRelatedL } };
    static const DirBits c_bg_cross_bit_carry_obj_bg_carried = { { PlayerBase::cBgCross_CarryObjBgCarriedR, PlayerBase::cBgCross_CarryObjBgCarriedL } };

    if (!output.isOnBit(c_bg_check_out_bit_carry_related.get(dir)))
        return;

    if (c_bg_cross_bit_carry_related.get(dir) < cBgCross_BitNum)
        onNowBgCross(c_bg_cross_bit_carry_related.get(dir));

    BgCollision* p_bg_collision_wall = mBgCheckPlayer.getHitBgCollisionWall(dir);
    if (p_bg_collision_wall == nullptr)
        return;

    Actor* p_actor_wall = p_bg_collision_wall->getOwner();
    if (p_actor_wall == nullptr)
        return;

    CarryObjBase* p_carry_obj_wall = sead::DynamicCast<CarryObjBase>(p_actor_wall);
    if (p_carry_obj_wall != nullptr && p_carry_obj_wall->checkCarried())
    {
        /* Code execution in NSMBW reaches here if daPlBase_c::isCarryObjBgCarried(u8 dir) returns true */
    
        if (c_bg_cross_bit_carry_obj_bg_carried.get(dir) < cBgCross_BitNum)
            onNowBgCross(c_bg_cross_bit_carry_obj_bg_carried.get(dir));
    }

    if (p_actor_wall->getProfileID() == ProfileID::cActorBlockMakeDRC)
        onNowBgCross(cBgCross_15);
}

f32 PlayerBase::getWaterOffsetY()
{
    static const f32 c_water_offset_y[cTallType_Num] = { 4.f, 8.f, 16.f };
    return c_water_offset_y[getTallType()];
}

f32 PlayerBase::getWaterCheckPosY()
{
    return mPos.x + getWaterOffsetY();
}

void PlayerBase::checkWater()
{
    mWaterType = cWaterType_None;
    mWaterSurfacePosYPrev = mWaterSurfacePosY;
    // mWaterSurfacePosY = Bg::instance()->getWaterSurfacePosY();

    sead::Vector3f check_pos = mPos;
    if (isStatus(cStatus_258))
        check_pos.y += 8.0f;
    WaterType water_type = ActorBgCollisionCheck::checkWater(&mWaterSurfacePosY, check_pos, mLayer);

    if (water_type != cWaterType_None && check_pos.y <= mWaterSurfacePosY)
    {
        onNowBgCross(cBgCross_IsWater);
        if (water_type == cWaterType_AirWater)
            onNowBgCross(cBgCross_IsAirWater);
    }

    BgCollisionCheckHitResult air_water_hit_res;
    if (water_type == cWaterType_None || water_type == cWaterType_AirWater)
    {
        check_pos.set(mPos.x, getWaterCheckPosY(), mPos.z);
        water_type = ActorBgCollisionCheck::checkWater(&mWaterSurfacePosY, &air_water_hit_res, check_pos, mLayer);
        if (water_type != cWaterType_AirWater)
            return;
        onNowBgCross(cBgCross_IsUnderwater);
        onNowBgCross(cBgCross_IsCompletelyUnderwater);
        water_type = cWaterType_AirWater;
    }

    mWaterType = water_type;

    switch (mWaterType)
    {
    default:
        break;
    case cWaterType_Water:
        if (getWaterCheckPosY() <= mWaterSurfacePosY)
            onNowBgCross(cBgCross_IsUnderwater);
        if (mPos.y + getHeadBgPointData()->center_offset <= mWaterSurfacePosY)
            onNowBgCross(cBgCross_IsCompletelyUnderwater);
        mWaterDepthType = ActorBgCollisionCheck::checkWaterDepth(mPos.x, mWaterSurfacePosY, mLayer);
        break;
    case cWaterType_AirWater:
        if (air_water_hit_res.is_hit)
        {
            onNowBgCross(cBgCross_IsAirWater);
            sead::Vector2f air_water_hit_pos = air_water_hit_res.hit_pos;
            mAirWaterHitPos.set(air_water_hit_pos.x, air_water_hit_pos.y, mPos.z);
            Angle air_water_hit_angle = air_water_hit_res.hit_angle;
            mAirWaterHitAngle = air_water_hit_angle;
        }
        break;
    case cWaterType_Lava:
    case cWaterType_LavaWave:
    case cWaterType_Poison:
    case cWaterType_Quicksand:
        if (RDashMgr::instance()->isNSLU())
            onNowBgCross(cBgCross_RDash_IsNonWaterLiquid);
        break;
    }
}

void PlayerBase::checkDamageBg()
{
    if (isStatus(cStatus_247))
        return;

    if (isStatus(cStatus_122))
        return;

    if (isStatus(cStatus_227))
        return;

    if (isDemoAll())
        return;

    switch (mWaterType)
    {
    default:
        break;
    case cWaterType_Lava:
    case cWaterType_LavaWave:
        mIsBgDamageEnable = true;
        mDamageBgTypeInfo = BgUnitCode::cTypeInfo_Damage_Lava;
        return;
    case cWaterType_Poison:
        mIsBgDamageEnable = true;
        mDamageBgTypeInfo = BgUnitCode::cTypeInfo_Damage_Doku;
        return;
    }

    for (s32 i = 0; i < cDirType_Num; i++)
    {
        DirType dir = DirType(i);

        if (isStatus(cStatus_193) && dir == cDirType_Down)
            continue;

        if (mBgCheckPlayer.getBgCheckDataPrev(dir) == 0)
            continue;

        mIsBgDamageEnable = true;
        mDamageBgTypeInfo = BgUnitCode::TypeInfo_Damage(BgUnitCode::getTypeInfo(mBgCheckPlayer.getBgCheckDataPrev(dir)));
    }
}

void PlayerBase::bgCheck(bool side_view_check)
{
    offStatus(cStatus_131);
    offStatus(cStatus_145);
    offStatus(cStatus_146);

    mOldBgCross = mNowBgCross;

    _1b28 = mPos;
    if (isNowBgCross(cBgCross_IsFoot))
        _1b0c = mPos.y;

    clearBgCheckInfo();

    if (side_view_check)
        checkSideViewLemit();

    if (!isStatus(cStatus_247))
    {
        checkBgCross_();
        checkBgCrossSub();
    }

    checkWater();
    checkDamageBg();
    postBgCross();
}
