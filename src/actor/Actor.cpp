#include <actor/Actor.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <game/SubjectMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

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

