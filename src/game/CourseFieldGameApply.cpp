#include <state/StateID.h>
#include <state/StateMethod.h>

#include <actor/ActorCreateParam.h>
#include <actor/ActorMgr.h>
#include <actor/Profile.h>
#include <actor/ProfileInfo.h>
#include <game_info/CourseInfo.h>
#include <map/CourseData.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <course_select/CourseSelectMgr.h>
#include <system/MainGame.h>

bool sub_02918780(PlayerMgr* mgr, s32 player_no);

namespace {

constexpr u32 kCourseInfoSingleton = 0x101D18ECu;
constexpr u32 kPlayerMgrSingleton = 0x101E6994u;
constexpr u32 kStateIdRodata = 0x10221580u;
constexpr u32 kSubEntryName = 0x105FA760u;
constexpr u32 kFieldGameCourseTypeOffset = 0x164u;
constexpr u32 kCourseApplyProfileInitFlag = 0x1022157Cu;
constexpr u32 kCourseApplyProfileTable = 0x10221564u;
constexpr u32 kInputMgrByte = 0x101D2DF8u;

// Address: 0x024D37B0
s32 sub_024D37B0(CourseInfo* info)
{
    u8 course_no = info->getCourseNo();
    return (course_no >= 0xBu) ? 1 : 0;
}

// Address: 0x024D37CC
s32 sub_024D37CC(CourseInfo* info)
{
    return (info->getCourseNo() == 0x13) ? 1 : 0;
}

// Address: 0x024D37E4
s32 sub_024D37E4(CourseInfo* info)
{
    u8 course_no = info->getCourseNo();
    return (course_no == 0x14 || course_no == 0x15) ? 1 : 0;
}

// Address: 0x024D38F8
s32 sub_024D38F8(CourseInfo* info)
{
    return info->isShortPlay() ? 1 : 0;
}

// Address: 0x02699D00
const void* sub_02699D00(const CourseDataFile* file, const NextGoto* next_goto, s32 zero)
{
    u8 match_id = reinterpret_cast<const u8*>(next_goto)[0xD];
    const u8* file_bytes = reinterpret_cast<const u8*>(file);
    u32 count = *reinterpret_cast<const u32*>(file_bytes + 0xA0);
    const u8* entry = *reinterpret_cast<const u8* const*>(file_bytes + 0x28);

    for (u32 i = 0; i < count; ++i)
    {
        if (entry[0xC] == match_id)
        {
            if (zero != 0)
                return nullptr;
            return entry;
        }

        entry += 0x1C;
    }

    return nullptr;
}

// Address: 0x0202AEBC
s32 sub_0202AEBC(const void* shape_obj)
{
    if (shape_obj == nullptr)
        return 0;

    u8 shape_type = reinterpret_cast<const u8*>(shape_obj)[0x16];
    if (shape_type >= 9 && shape_type <= 0xB)
        return 0;

    return 1;
}

bool fieldGameData_isTypeA_(void* game_data)
{
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(game_data) + kFieldGameCourseTypeOffset) == 0xAu;
}

bool fieldGameData_isTypeB_(void* game_data)
{
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(game_data) + kFieldGameCourseTypeOffset) == 0xBu;
}

void initCourseApplyProfileTableOnce_()
{
    u32* flag = reinterpret_cast<u32*>(kCourseApplyProfileInitFlag);
    if (*flag != 0)
        return;

    *flag = 1;
    u32* table = reinterpret_cast<u32*>(kCourseApplyProfileTable);
    table[0] = ProfileInfo::cProfileID_1BF;
    table[1] = ProfileInfo::cProfileID_1C0;
    table[2] = ProfileInfo::cProfileID_1C1;
}

// Address: 0x02742EA0
void sub_02742EA0(s32 entry_index, const char* name, s32 arg5, s32 arg6, s32 arg7, s32 arg8)
{
    initCourseApplyProfileTableOnce_();

    ActorCreateParam param;
    u32* table = reinterpret_cast<u32*>(kCourseApplyProfileTable);
    s32 profile_id = table[entry_index];
    param.p_profile = Profile::get(profile_id);

    u32 packed = static_cast<u32>(entry_index) & 0xFu;
    packed |= (static_cast<u32>(arg5) & 0xFu) << 4;
    packed |= (static_cast<u32>(arg6) & 0xFu) << 8;
    packed |= (static_cast<u32>(arg7) & 0xFFu) << 16;
    packed |= (static_cast<u32>(arg8) & 0xFu) << 28;
    param.param_0 = packed;

    const f32* spawn = reinterpret_cast<const f32*>(name);
    param.position.x = spawn[0];
    param.position.y = spawn[1];
    param.position.z = spawn[2];

    ActorMgr::instance()->createImmediately(param);
}

// Address: 0x02742F88
void sub_02742F88(s32 entry_index, s32 arg1, s32 arg2, s32 arg3, const char* name)
{
    sub_02742EA0(entry_index, name, 1, arg1, arg2, arg3);
}

// Address: 0x02742DD0
s32 sub_02742DD0()
{
    CourseInfo* info = *reinterpret_cast<CourseInfo**>(kCourseInfoSingleton);

    if (sub_024D37B0(info) == 0 && sub_024D37CC(info) == 0 && sub_024D37E4(info) == 0
        && sub_024D38F8(info) == 0)
    {
        return 0;
    }

    u8 world = info->getWorldNo();
    u8 course = info->getCourseNo();
    const CourseDataFile* file = CourseData::instance()->getFile(world);
    const NextGoto* next_goto = file->getNextGoto(course);
    const void* shape = sub_02699D00(file, next_goto, 0);
    if (sub_0202AEBC(shape) == 0)
        return 0;

    return 1;
}

// Address: 0x024C21DC
s32 sub_024C21DC(void* game_data)
{
    if (fieldGameData_isTypeA_(game_data))
        return 1;
    if (fieldGameData_isTypeB_(game_data))
        return 1;
    return 0;
}

// Address: 0x024C2198
void sub_024C2198(void* game_data)
{
    u32& course_type = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(game_data) + kFieldGameCourseTypeOffset);
    if (course_type == 0xAu || course_type == 0xBu)
        return;
    course_type = 0xEu;
}

// Address: 0x02742DA8
s32 sub_02742DA8(void* game_data)
{
    u32 course_type = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(game_data) + kFieldGameCourseTypeOffset);
    if (course_type == 0xAu)
        return 0;
    if (course_type == 0xBu)
        return 1;
    return -1;
}

// Address: 0x02918E88
s32 sub_02918E88(PlayerMgr* mgr, s32 player_no)
{
    if (!sub_02918780(mgr, player_no))
        return 0;

    FieldPlayerData& entry = mgr->getGameData()->getPlayerData(player_no);
    if (entry.life_cnt <= 0)
        return 0;

    u8 controller_mask = reinterpret_cast<u8*>(kInputMgrByte)[0x56C];
    if (((controller_mask >> player_no) & 1) == 0)
        return 0;

    PlayerObject* obj = mgr->getPlayerObject(player_no);
    if (obj != nullptr)
    {
        u32 flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + 0x49C);
        if ((flags >> 6) & 1)
            return 0;
    }

    return 1;
}

// Address: 0x02918F34
s32 sub_02918F34(PlayerMgr* mgr)
{
    s32 count = 0;
    for (s32 i = 0; i < 4; ++i)
    {
        if (sub_02918E88(mgr, i) != 0)
            ++count;
    }
    return count;
}

// Address: 0x029190B4
s32 sub_029190B4(void* main_game)
{
    (void)main_game;

    PlayerMgr* mgr = PlayerMgr::instance();
    for (s32 i = 0; i < 4; ++i)
    {
        if (!sub_02918780(mgr, i))
            continue;

        PlayerObject* obj = mgr->getPlayerObject(i);
        if (obj == nullptr)
            continue;

        u32 flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(obj) + 0x49C);
        if ((flags >> 6) & 1)
            return 1;
    }

    return 0;
}

constexpr u32 kChallengeEntryTypeOffset = 0x1860u;
constexpr u32 kChallengeEntryIndexOffset = 0x185cu;
constexpr u32 kChallengeEntryFlagsOffset = 0x1868u;

void* courseOwner_listEntry_(u8* owner, s32 logical_index)
{
    u8* list = owner + 0x18;
    void** data = *reinterpret_cast<void***>(list);
    u32 end = *reinterpret_cast<u32*>(list + 4);
    u32 start = *reinterpret_cast<u32*>(list + 8);
    u32 physical = start + static_cast<u32>(logical_index);
    if (physical >= end)
        physical -= end;
    return data[physical];
}

bool challengeEntry_matchesCourseIndex_(void* entry, s32 entry_index)
{
    u8* bytes = reinterpret_cast<u8*>(entry);
    if (*reinterpret_cast<u32*>(bytes + kChallengeEntryTypeOffset) != 1)
        return false;
    return *reinterpret_cast<u32*>(bytes + kChallengeEntryIndexOffset) == static_cast<u32>(entry_index);
}

// Address: 0x027430C0
s32 sub_027430C0(void* course_owner)
{
    u8* owner = reinterpret_cast<u8*>(course_owner);
    s32 entry_index = *reinterpret_cast<s32*>(owner + 0x130);
    if (entry_index == -1)
        return 0;

    bool short_play = sub_024D38F8(CourseInfo::instance()) != 0;
    u8 main_flag = 0;
    if (MainGame::instance() != nullptr)
        main_flag = reinterpret_cast<u8*>(MainGame::instance())[0x21DFA];

    u32 count = *reinterpret_cast<u32*>(owner + 0x24);
    for (u32 i = 0; i < count; ++i)
    {
        void* entry = courseOwner_listEntry_(owner, static_cast<s32>(i));
        if (!challengeEntry_matchesCourseIndex_(entry, entry_index))
            continue;

        u32 flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + kChallengeEntryFlagsOffset);
        if ((flags >> 15) & 1)
            continue;

        if (short_play)
        {
            if (main_flag == 0)
                continue;
            if (((flags >> 5) & 1) == 0)
                continue;
        }

        return 1;
    }

    return 0;
}

// Address: 0x027431C8
s32 sub_027431C8(void* course_owner)
{
    u8* owner = reinterpret_cast<u8*>(course_owner);
    s32 entry_index = *reinterpret_cast<s32*>(owner + 0x130);
    if (entry_index == -1)
        return 0;

    MainGame* main_game = MainGame::instance();
    if (main_game == nullptr)
        return 0;
    if (reinterpret_cast<u8*>(main_game)[0x21DFA] == 0)
        return 0;

    u32 count = *reinterpret_cast<u32*>(owner + 0x24);
    for (u32 i = 0; i < count; ++i)
    {
        void* entry = courseOwner_listEntry_(owner, static_cast<s32>(i));
        if (!challengeEntry_matchesCourseIndex_(entry, entry_index))
            continue;

        u32 flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + kChallengeEntryFlagsOffset);
        if (((flags >> 4) & 1) == 0)
            continue;

        return 1;
    }

    return 0;
}

// Address: 0x02743270
s32 sub_02743270(s32 value)
{
    if (value > 1)
        return 0xE;
    if (value < 1)
        return 0xA;
    return 0xB;
}

// Address: 0x02743294
void sub_02743294(void* course_owner, u8* game_data)
{
    u8* owner = reinterpret_cast<u8*>(course_owner);
    s32 entry_index = *reinterpret_cast<s32*>(owner + 0x130);
    if (entry_index == -1)
        return;
    if (owner[0x135] != 0)
        return;

    MainGame* main_game = MainGame::instance();
    u32 mode = 0;
    if (main_game != nullptr)
        mode = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(main_game) + 0x20);

    s32 probe = 0;
    if (mode == 2)
        probe = sub_027430C0(course_owner);
    else if (mode == 3)
        probe = sub_027431C8(course_owner);

    CourseSelectMgr* select_mgr = CourseSelectMgr::instance();
    u8 on_course_select = 0;
    if (select_mgr != nullptr)
        on_course_select = reinterpret_cast<u8*>(select_mgr)[0x59C];

    bool apply = false;
    if (mode == 2 || mode == 3)
    {
        if (on_course_select != 0)
            apply = true;
        else if (probe != 0)
            apply = true;
    }
    else if (on_course_select != 0)
    {
        apply = true;
    }

    if (!apply)
        return;

    s32 mapped = sub_02743270(entry_index);
    *reinterpret_cast<u32*>(game_data + kFieldGameCourseTypeOffset) = static_cast<u32>(mapped);
}

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
        CourseInfo* course_info = CourseInfo::instance();
        if (course_info->getWorldNo() == 0 && course_info->getCourseNo() == 3)
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
    if (player_mgr != nullptr && MainGame::instance() != nullptr)
    {
        if (sub_029190B4(MainGame::instance()) != 0)
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
