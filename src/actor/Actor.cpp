#include <actor/Actor.h>
#include <actor/ActorCullUtil.h>
#include <actor/ActorUtil.h>
#include <actor/ChibiYoshiEatData.h>
#include <actor/EatData.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BasicBgCollisionCheck.h>
#include <collision/BgCollisionCheckParam.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/TottenMgr.h>
#include <game/SubjectMgr.h>
#include <map/LayerID.h>
#include <map_obj/ChibiYoshiAwaData.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scroll/BgScrollMgr.h>
#include <system/MainGame.h>

#define COMBO_CNT_MAX 9

void Actor::removeCollisionCheck()
{
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
}

void Actor::reviveCollisionCheck()
{
    ActorCollisionCheckMgr::instance()->entry(mCollisionCheck);
}

bool Actor::checkCarried(s32* p_player_no)
{
    for (s32 i = 0; i < 4; i++)
    {
        PlayerObject* p_player = PlayerMgr::instance()->getPlayerObject(i);
        if (p_player != nullptr && p_player->getCarryActorID() == mActorUniqueID)
        {
            if (p_player_no != nullptr)
                *p_player_no = p_player->getPlayerNo();
            return true;
        }
    }
    if (p_player_no != nullptr)
        *p_player_no = -1;
    return false;
}

void Actor::clrComboCnt()
{
    mComboCnt = 0;
    SubjectMgr::instance()->onAcComboCntClr();
}

void Actor::incComboCnt()
{
    mComboCnt = sead::Mathi::min(mComboCnt + 1, COMBO_CNT_MAX - 1);
    SubjectMgr::instance()->onComboCntInc(mComboCnt, SubjectMgr::cComoType_AcCombo);
}

void Actor::slideComboSE(s32 combo_cnt, bool combo_type_2)
{
    static const GameAudio::SoundID cs_combo_se[] = {
        "SE_EMY_KAME_HIT_1",
        "SE_EMY_KAME_HIT_2",
        "SE_EMY_KAME_HIT_3",
        "SE_EMY_KAME_HIT_4",
        "SE_EMY_KAME_HIT_5",
        "SE_EMY_KAME_HIT_6",
        "SE_EMY_KAME_HIT_7",
        "SE_EMY_KAME_HIT_7",
        "SE_EMY_KAME_HIT_7"
    };
    static_assert((sizeof(cs_combo_se) / sizeof(GameAudio::SoundID)) == COMBO_CNT_MAX);

    if (!(0 <= mPlayerNo && mPlayerNo < 4))
        return;

    if (combo_cnt >= COMBO_CNT_MAX)
        combo_cnt = COMBO_CNT_MAX - 1;

    s32 clap_combo = combo_type_2 ? 4 : 7;
    if (combo_cnt >= clap_combo)
        GameAudio::setClapSE();

    cs_combo_se[combo_cnt].startSoundEmy(getCenterPos(), GameAudio::getRemotePlayer(mPlayerNo));
}

s32 Actor::searchNearPlayer(sead::Vector2f& out)
{
    return ActorUtil::searchNearPlayer_Main(out, getCenterPos());
}

u32 Actor::directionToPlayerH(const sead::Vector3f& position)
{
    sead::Vector2f pl_position;
    s32 player_no = ActorUtil::searchNearPlayer_Main(pl_position, position);

    if (0 <= player_no && player_no < 4)
    {
        if (pl_position.x < 0.0)
            return DIRECTION_LEFT;
        else
            return DIRECTION_RIGHT;
    }
    else
    {
        if (mPos.x > BgScrollMgr::instance()->getScreenCenterX() + 96.0f)
            return DIRECTION_LEFT;
        else if (mPos.x < BgScrollMgr::instance()->getScreenCenterX() - 96.0f)
            return DIRECTION_RIGHT;
        else
            return mDirection;
    }
}

u32 Actor::directionToPlayerV(const sead::Vector3f& position)
{
    sead::Vector2f pl_position;
    s32 player_no = ActorUtil::searchNearPlayer_Main(pl_position, position);

    if (0 <= player_no && player_no < 4)
    {
        if (pl_position.y < 0.0)
            return DIRECTION_DOWN;
        else
            return DIRECTION_UP;
    }
    else
    {
        return DIRECTION_UP;
    }
}

bool Actor::screenOutCheck(u16 flag)
{
    if (mpEatData != nullptr && mpEatData->getState() == 2)
        return false;

    if (mpChibiYoshiEatData != nullptr && mpChibiYoshiEatData->getState() == 2)
        return false;

    if (mpChibiYoshiAwaData != nullptr && mpChibiYoshiAwaData->getState() != 0)
        return false;

    if (!(flag & 8))
    {
        ActorBgCollisionCheck* p_bc = getBgCheck();
        if (p_bc != nullptr && p_bc->checkRide())
            return false;
    }

    const f32 l = mPos.x + mVisibleArea.offset.x - mVisibleArea.size.x * 0.5f;
    const f32 r = l + mVisibleArea.size.x;

    const f32 b = mPos.y + mVisibleArea.offset.y - mVisibleArea.size.y * 0.5f;
    const f32 t = b + mVisibleArea.size.y;

    const sead::BoundBox2f visible_range(l, b, r, t);

    if ((flag & 0x10) && calcTottenToSrcDir_(visible_range) == DIRECTION_RIGHT)
        return false;

    bool out = false;

    if (ActorCullUtil::areaCullCheck(visible_range, mAreaNo))
        out = true;
    else if (!(flag & 4) && ActorCullUtil::screenCullCheck(visible_range, mCullLimit))
        out = true;

    if (out && !(flag & 2))
        deleteActor(mIsNoRespawn);

    return out;
}

void Actor::allEnemyDeathEffSet()
{
}

void Actor::waterSplashEffect(const sead::Vector3f& pos)
{
}

void Actor::yoganSplashEffect(const sead::Vector3f& pos)
{
}

void Actor::yoganWaveSplashEffect(const sead::Vector3f& pos)
{
    yoganSplashEffect(pos);
}

void Actor::poisonSplashEffect(const sead::Vector3f& pos)
{
}

f32 Actor::getEffectZPos() const
{
    if (mCollisionMask.isOnBit(0) && mLayer == cLayerID_Layer1)
    {
        const BgCollisionCheckParam param = {
            0,                              // _0
            false,                          // ignore_quicksand
            cLayerID_Layer1,                // layer
            sead::BitFlag8(3),              // collision_mask
            cBgCollisionCheckType_Solid,    // type
            nullptr                         // callback
        };
        const sead::Vector2f check_pos(
            mPos.x,
            mPos.y + 2.0f
        );
        BgCollisionCheckResultPoint res;
        BasicBgCollisionCheck bg_check(param);
        if (!bg_check.checkPointUnit(&res, check_pos))
        {
            bg_check.setLayer(cLayerID_Layer0);
            if (bg_check.checkPointUnit(&res, check_pos))
            {
                if (res.bg_check_data.getUnitKind() != BgCheckUnitInfo::cKind_Normal || res.bg_check_data.getUnitSolidType() != BgCheckUnitInfo::cSolidType_None)
                    return 3300.0f;
            }
        }
        return 4500.0f;
    }
    else
    {
        return mPos.z;
    }
}

bool Actor::checkEat() const
{
    if (mpEatData != nullptr && (mpEatData->getState() == 1 || mpEatData->getState() == 2))
        return true;

    if (mpChibiYoshiEatData != nullptr && (mpChibiYoshiEatData->getState() == 1 || mpChibiYoshiEatData->getState() == 2))
        return true;

    return false;
}

void Actor::deleteActor(bool no_respawn)
{
    requestDelete();
    if (_270 != nullptr && !no_respawn)
        *_270 &= ~1;
}

u32 Actor::calcTottenToSrcDir_(const sead::BoundBox2f& src_range) const
{
    if (!MainGame::instance()->isStory() ||
        TottenMgr::instance() == nullptr ||
        TottenMgr::instance()->getTottenActor() == nullptr)
    {
        return DIRECTION_LEFT;
    }

    if (TottenMgr::instance()->getTottenActor()->getPos().x > src_range.getMax().x)
        return DIRECTION_LEFT;
    else
        return DIRECTION_RIGHT;
}
