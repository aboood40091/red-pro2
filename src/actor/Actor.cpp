#include <actor/Actor.h>
#include <actor/ActorUtil.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <enemy/TottenMgr.h>
#include <game/SubjectMgr.h>
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
