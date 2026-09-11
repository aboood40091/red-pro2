#include <game/CourseTask.h>
#include <player/KinopioModel.h>
#include <player/MarioModel.h>
#include <player/MiiModel.h>
#include <player/PlayerModelMgr.h>
#include <player/TottenPlayerModel.h>

PlayerModelMgr::PlayerModelMgr(PlayerModelBase::Type type, PlayerModelBase::SceneType scene_type, s32 player_no, bool override_lightmap)
    : PlayerModelBaseMgr()
{
    construct_(type, cPlayerMode_Invalid, scene_type, player_no, override_lightmap);
    setModelBase(mpModel);
    setColorType(PlayerModel::cColorType_Normal, false);
    mpModel->setPlayerNo(player_no);
}

void PlayerModelMgr::construct_(PlayerModelBase::Type type, PlayerMode mode, PlayerModelBase::SceneType scene_type, s32 player_no, bool override_lightmap)
{
    // clang fails to inline this function (NSMBUDX), but GHS does (NSMBU)

    switch (type)
    {
    case PlayerModelBase::cType_Mario:
    case PlayerModelBase::cType_Luigi:
        mpModel = new MarioModel(type, mode, scene_type, override_lightmap);
        break;
    case PlayerModelBase::cType_BlueToad:
    case PlayerModelBase::cType_YellowToad:
    case PlayerModelBase::cType_NpcToad:
        mpModel = new KinopioModel(type, mode, scene_type, override_lightmap);
        break;
    case PlayerModelBase::cType_Nabbit:
        mpModel = new TottenPlayerModel(type, mode, scene_type, override_lightmap);
        break;
    case PlayerModelBase::cType_Mii:
        {
            const FieldPlayerData& player_data = CourseTask::getActiveGameData().getPlayerData(player_no);
            mpModel = new MiiModel(type, mode, scene_type, player_data.character_color, player_data.mii_slot, nullptr, override_lightmap);
        }
        break;
    default:
        // ERROR!!!
        mpModel = nullptr;
        break;
    }
}

PlayerModelMgr::PlayerModelMgr(PlayerModelBase::Type type, PlayerMode mode, PlayerModelBase::SceneType scene_type, bool override_lightmap)
    : PlayerModelBaseMgr()
{
    construct_(type, mode, scene_type, -1, override_lightmap);
    setModelBase(mpModel);
    setColorType(PlayerModel::cColorType_Normal, false);
}

PlayerModelMgr::PlayerModelMgr(PlayerMode mode, PlayerCharacter mii_color, Mii::SlotID slot_id, sead::Heap* p_ffl_tmp_heap, bool override_lightmap)
    : PlayerModelBaseMgr()
{
    mpModel = new MiiModel(PlayerModelBase::cType_Mii, mode, PlayerModelBase::cSceneType_2D, mii_color, slot_id, p_ffl_tmp_heap, override_lightmap);
    setModelBase(mpModel);
    setColorType(PlayerModel::cColorType_Normal, false);
}
