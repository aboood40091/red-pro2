#include <player/PlayerMgr.h>

#include <game/FieldGame.h>
#include <game/CourseTask.h>
#include <player/PlayerBase.h>
#include <player/PlayerObject.h>
#include <player/Yoshi.h>

namespace
{

constexpr uintptr_t kPlayerMgrService = 0x101E1E14u;

// Address: 0x028F2188
void sub_028F2188(void* mgr, s32 player_no, PlayerObject* p_player_obj);

// Address: 0x028F21DC
void sub_028F21DC(void* mgr, s32 player_no);

// Address: 0x02918780
bool sub_02918780(PlayerMgr* mgr, s32 player_no);

// Address: 0x029167BC
void sub_029167BC(PlayerMgr* mgr)
{
    u8* bytes = reinterpret_cast<u8*>(mgr);
    u32* ring_a = reinterpret_cast<u32*>(bytes + 0x1C);
    for (s32 i = 0; i < 4; ++i)
        ring_a[i] = 0;

    u32* ring_b = reinterpret_cast<u32*>(bytes + 0x2C);
    for (s32 i = 0; i < 4; ++i)
        ring_b[i] = 0;

    *reinterpret_cast<u32*>(bytes + 0x50) = 0;
    *reinterpret_cast<u32*>(bytes + 0x6C) = 0;
    *reinterpret_cast<u32*>(bytes + 0x4C) = 0;
    *reinterpret_cast<u32*>(bytes + 0x70) = 0;
}

// Address: 0x02916B94
void sub_02916B94(PlayerMgr* mgr);

// Address: 0x02916CB8
s32 sub_02916CB8(PlayerMgr* mgr, FieldGameData* game_data);

// Address: 0x02916EDC
s32 sub_02916EDC(PlayerMgr* mgr, FieldGameData* game_data);

// Address: 0x02916BF8
void sub_02916BF8(s32 player_no, const char* name, s32 arg2, s32 arg3, s32 arg4, u8* player_entry);

// Address: 0x02917040
s32 sub_02917040();

// Address: 0x02916B6C
FieldGameData* sub_02916B6C(PlayerMgr* mgr);

// Address: 0x02916F7C
void sub_02916F7C(PlayerMgr* mgr, FieldGameData* game_data)
{
    sub_02916B94(mgr);
    if (sub_02916CB8(mgr, game_data) != 0)
        return;
    if (sub_02916EDC(mgr, game_data) != 0)
        return;

    u8* player_base = reinterpret_cast<u8*>(game_data) + 0x14;
    const char* name = reinterpret_cast<const char*>(0x105FA760u);

    for (s32 i = 0; i < 4; ++i)
    {
        u8* entry = player_base + i * 0x48;
        if (entry[0] == 0)
            continue;

        sub_02916BF8(i, name, 0, 0, 0, entry);
        entry[0x1D] = 1;
    }
}

// Address: 0x029170BC
void sub_029170BC(PlayerMgr* mgr)
{
    if (sub_02917040() == 0)
        return;

    FieldGameData* game_data = sub_02916B6C(mgr);
    if (game_data == nullptr)
        game_data = getGameData();

    u8* player_base = reinterpret_cast<u8*>(game_data) + 0x14;
    for (s32 i = 0; i < 4; ++i)
    {
        u8* entry = player_base + i * 0x48;
        entry[0x1E] = 0;
    }
}

}

// Address: 0x0291713C
void PlayerMgr::initializeForCourseSetup()
{
    u32 zero = 0;
    _84 = zero;
    sub_029167BC(this);
    _88 = 0;
    _a8 = zero;
    sub_02916F7C(this, getGameData());
    sub_029170BC(this);
    _a8 = zero;
}

// Address: 0x02917D58
PlayerBase* PlayerMgr::getCtrlPlayer(s32 player_no)
{
    PlayerObject* p_player_obj = mPlayerObject[player_no];
    if (p_player_obj == nullptr)
        return nullptr;

    Yoshi* p_yoshi = p_player_obj->getRideYoshi();
    if (p_yoshi != nullptr)
        return p_yoshi;

    return p_player_obj;
}

// Address: 0x02917FD8
void PlayerMgr::setPlayer(s32 player_no, PlayerObject* p_player_obj)
{
    mPlayerObject[player_no] = p_player_obj;
    mPlayerObject2[player_no] = p_player_obj;
    mActPlayerInfo.setBit(player_no);

    sub_028F2188(*reinterpret_cast<void**>(kPlayerMgrService), player_no, p_player_obj);
}

// Address: 0x02918028
void PlayerMgr::resetPlayer(s32 player_no)
{
    mPlayerObject[player_no] = nullptr;
    mPlayerObject2[player_no] = nullptr;
    mActPlayerInfo.resetBit(player_no);

    sub_028F21DC(*reinterpret_cast<void**>(kPlayerMgrService), player_no);
}

// Address: 0x02918144
s32 PlayerMgr::getYoshiNum()
{
    return mYoshi.size();
}

// Address: 0x02918758
FieldGameData* PlayerMgr::getGameData()
{
    CourseTask* course_task = CourseTask::instance();
    if (course_task != nullptr)
        return course_task->getGameData();

    return &FieldGame::instance()->getGameData();
}

// Address: 0x02918780
bool sub_02918780(PlayerMgr* mgr, s32 player_no)
{
    return mgr->getGameData()->getPlayerData(player_no).is_entry;
}

// Address: 0x029187B8
s32 PlayerMgr::getCoinNumMin()
{
    FieldGameData* game_data = getGameData();
    s32 coin_num = 0;

    for (s32 i = 0; i < cPlayerNum; ++i)
    {
        if (!sub_02918780(this, i))
            continue;

        s32 player_coin_num = game_data->getPlayerData(i).coin_cnt;
        if (coin_num < player_coin_num)
            coin_num = player_coin_num;
    }

    return coin_num;
}

// Address: 0x0291892C
bool PlayerMgr::isAcceptQuake(s32 player_no)
{
    if (!isPlayerActive(player_no))
        return false;

    PlayerObject* p_player_obj = mPlayerObject[player_no];
    if (p_player_obj == nullptr)
        return false;

    if (!p_player_obj->isDemoMode())
        return true;

    if (p_player_obj->isDemoType(PlayerBase::cDemoType_3))
        return false;

    if (p_player_obj->isDemoType(PlayerBase::cDemoType_5))
        return false;

    return true;
}

// Address: 0x02919064
s32 PlayerMgr::getEntryNum()
{
    s32 entry_num = 0;

    for (s32 i = 0; i < cPlayerNum; ++i)
    {
        if (sub_02918780(this, i))
            ++entry_num;
    }

    return entry_num;
}
