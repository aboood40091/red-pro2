#include <state/StateID.h>
#include <state/StateMethod.h>

#include <player/PlayerMgr.h>

namespace {

constexpr u32 kCourseSelectMgrSingleton = 0x101D18ECu;
constexpr u32 kPlayerMgrSingleton = 0x101E6994u;
constexpr u32 kStateIdRodata = 0x10221580u;
constexpr u32 kSubEntryName = 0x105FA760u;
constexpr u32 kGlobalWord101E0000 = 0x101E0000u;

// Address: 0x02742DD0
s32 sub_02742DD0();

// Address: 0x024C21DC
s32 sub_024C21DC(void* game_data);

// Address: 0x024C2198
void sub_024C2198(void* game_data);

// Address: 0x02742DA8
s32 sub_02742DA8(void* game_data);

// Address: 0x02742F88
void sub_02742F88(s32 entry_index, s32 arg1, s32 arg2, s32 arg3, const char* name);

// Address: 0x02918F34
s32 sub_02918F34(PlayerMgr* mgr);

// Address: 0x029190B4
s32 sub_029190B4(void* arg);

} // namespace

// Address: 0x02742F9C
void sub_02742F9C(void* course_owner, void* game_data)
{
    if (sub_02742DD0() == 0)
        return;

    u8* owner = reinterpret_cast<u8*>(course_owner);
    u8* data = reinterpret_cast<u8*>(game_data);
    u32 zero = 0;
    *reinterpret_cast<u32*>(owner + 0x24) = zero;
    *reinterpret_cast<u32*>(owner + 0x20) = zero;

    StateMethod* state_method = reinterpret_cast<StateMethod*>(owner + 0x148);
    const StateID* state_id = reinterpret_cast<const StateID*>(kStateIdRodata);
    state_method->changeStateMethod(*state_id);
    owner[0x135] = 0;

    if (*reinterpret_cast<u32*>(data + 0x15C) == 1)
    {
        u8* select_mgr = *reinterpret_cast<u8**>(kCourseSelectMgrSingleton);
        if (select_mgr[0x10] == 0 && select_mgr[0x11] == 3)
        {
            owner[0x135] = 1;
            *reinterpret_cast<u32*>(data + 0x164) = 0xBu;
        }
    }

    if (sub_024C21DC(game_data) == 0)
        return;

    sub_024C2198(game_data);
    s32 entry_index = sub_02742DA8(game_data);
    *reinterpret_cast<s32*>(owner + 0x130) = entry_index;
    if (entry_index == -1)
        return;

    PlayerMgr* player_mgr = *reinterpret_cast<PlayerMgr**>(kPlayerMgrSingleton);
    s32 player_count = sub_02918F34(player_mgr);
    if (player_mgr != nullptr)
    {
        void* global_word = *reinterpret_cast<void**>(kGlobalWord101E0000);
        if (sub_029190B4(global_word) != 0)
            player_count -= 1;
    }

    if (player_count <= 0)
    {
        *reinterpret_cast<u32*>(data + 0x164) = 0xEu;
        return;
    }

    for (s32 i = 0; i < player_count; ++i)
        sub_02742F88(entry_index, i, i, i, reinterpret_cast<const char*>(kSubEntryName));

    *reinterpret_cast<u32*>(data + 0x164) = 0xEu;
}
