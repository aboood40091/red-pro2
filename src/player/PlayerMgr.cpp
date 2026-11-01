#include <player/PlayerMgr.h>

#include <actor/ActorCreateParam.h>
#include <actor/ActorMgr.h>
#include <actor/Profile.h>
#include <actor/ProfileInfo.h>
#include <game/FieldGame.h>
#include <game/CourseTask.h>
#include <game_info/CourseInfo.h>
#include <player/PlayerBase.h>
#include <player/PlayerObject.h>
#include <player/Yoshi.h>

namespace
{

constexpr uintptr_t kPlayerMgrService = 0x101E1E14u;
constexpr uintptr_t kSaveApplyMgr = 0x101E7D9Cu;
constexpr uintptr_t kDefaultPlayerCreateName = 0x105FA760u;

// Address: 0x02A0EF58
s32 sub_02A0EF58(s32 value)
{
    u32 x = static_cast<u32>(value);
    x = (x & (~x + 1u)) - 1u;
    x = (x & 0x55555555u) + ((x >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = (x & 0x0f0f0f0fu) + ((x >> 4) & 0x0f0f0f0fu);
    x = (x & 0x00ff00ffu) + ((x >> 8) & 0x00ff00ffu);
    return static_cast<s32>((x + (x >> 16)) & 0x3fu);
}

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

// Address: 0x02916B6C
FieldGameData* sub_02916B6C(PlayerMgr* mgr)
{
    if (mgr != nullptr)
        return mgr->getGameData();

    CourseTask* course_task = CourseTask::instance();
    if (course_task != nullptr)
        return course_task->getGameData();

    return &FieldGame::instance()->getGameData();
}

// Address: 0x02916B94
void sub_02916B94(PlayerMgr* mgr)
{
    FieldGameData* game_data = sub_02916B6C(mgr);
    u8* player_base = reinterpret_cast<u8*>(game_data) + 0x14;

    for (s32 i = 0; i < 4; ++i)
    {
        u8* entry = player_base + i * 0x48;
        if (entry != nullptr)
            entry[0x1D] = 0;
    }
}

// Address: 0x02916BF8
void sub_02916BF8(s32 player_no, const char* name, s32 arg5, s32 character, s32 arg7, u8* player_entry)
{
    (void)name;

    ActorCreateParam param;
    const f32* spawn_src = reinterpret_cast<const f32*>(name);

    s32 profile_id = ProfileInfo::cProfileID_PlayerObject;
    if (character == 4)
        profile_id = ProfileInfo::cProfileID_TottenPlayer;

    param.p_profile = Profile::get(profile_id);

    u32 packed = static_cast<u32>(player_no) & 0xFu;
    packed |= (static_cast<u32>(arg5) & 0xFu) << 4;
    packed |= (static_cast<u32>(character) & 0xFu) << 8;
    packed |= (static_cast<u32>(arg7) & 0xFFu) << 16;
    packed |= (reinterpret_cast<uintptr_t>(player_entry) & 0xFu) << 24;
    param.param_0 = packed;

    param.position.x = spawn_src[0];
    param.position.y = spawn_src[1];
    param.position.z = spawn_src[2];
    param._28 = player_entry;

    ActorMgr::instance()->createImmediately(param);
}

// Address: 0x02916CB8
s32 sub_02916CB8(PlayerMgr* mgr, FieldGameData* game_data)
{
    (void)mgr;

    if (!CourseInfo::instance()->isStaffCredit())
        return 0;

    u8 save_apply_flag = reinterpret_cast<u8*>(kSaveApplyMgr)[0x11];
    u32 character_mask = (save_apply_flag != 0) ? 0x1Eu : 0xFu;

    u8* player_base = reinterpret_cast<u8*>(game_data) + 0x14;
    u32 slot_mask = 0;

    for (s32 slot = 0; slot < 4; ++slot)
    {
        u8* entry = player_base + slot * 0x48;
        if (entry[0] == 0)
            continue;

        slot_mask |= (1u << slot);
        u32 character = *reinterpret_cast<u32*>(entry + 0xC);
        if (character < 32)
            character_mask &= ~(1u << character);
    }

    s32 spawn_characters[4] = {};
    for (s32 slot = 0; slot < 4; ++slot)
    {
        if ((slot_mask & (1u << slot)) == 0)
            continue;

        u32 lowest = character_mask & (~character_mask + 1u);
        if (lowest == 0)
            continue;

        s32 encoded = sub_02A0EF58(static_cast<s32>(lowest - 1u));
        spawn_characters[slot] = encoded;
        character_mask &= ~(1u << encoded);
    }

    const char* name = reinterpret_cast<const char*>(kDefaultPlayerCreateName);
    for (s32 slot = 0; slot < 4; ++slot)
        sub_02916BF8(slot, name, 1, spawn_characters[slot], 0, nullptr);

    if (spawn_characters[0] != 0)
        sub_02916BF8(4, name, 1, spawn_characters[0], 0, nullptr);

    for (s32 slot = 0; slot < 4; ++slot)
    {
        u8* entry = player_base + slot * 0x48;
        if (entry[0] == 0)
            continue;

        entry[0x1D] = 1;
    }

    return 1;
}

// Address: 0x02916EDC
s32 sub_02916EDC(PlayerMgr* mgr, FieldGameData* game_data)
{
    (void)mgr;
    (void)game_data;

    if (!CourseInfo::instance()->isTitle())
        return 0;

    const char* name = reinterpret_cast<const char*>(kDefaultPlayerCreateName);
    for (s32 i = 0; i < 4; ++i)
        sub_02916BF8(i, name, 1, 0, 0, nullptr);

    return 1;
}

// Address: 0x02917040
s32 sub_02917040()
{
    CourseInfo* course_info = CourseInfo::instance();
    if (course_info->getCourseNo() == 0x39)
        return 0;

    u8 course_no = course_info->getCourseNo();
    if (course_no - 0x1f <= 3)
        return 0;
    if (course_no - 0xca <= 3)
        return 0;

    if (course_no >= 0x26 && course_no <= 0x28)
        return 1;

    return 0;
}

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
        game_data = mgr->getGameData();

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
