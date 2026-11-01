#include <input/InputMgr.h>

#include <game/CourseTask.h>
#include <game/FieldGame.h>
#include <game/SubjectMgr.h>
#include <game_info/CourseInfo.h>
#include <system/MainGame.h>

namespace {

constexpr uintptr_t kSaveEntryOffset   = 0x55Cu;
constexpr uintptr_t kSaveApplyMgr      = 0x101E7D9Cu;
constexpr uintptr_t kSaveApplyFlagOff  = 0x11u;
constexpr uintptr_t kQuakeMgrInstance  = 0x101D1858u;
constexpr u32       kMaxPlaySeconds    = 999999999u;
constexpr u32       kMaxQuakePower     = 0x13u;

constexpr u32 kSavePlayerBase     = 0x3C;
constexpr u32 kSavePlayerStride   = 0x10;
constexpr u32 kSaveBannerBase     = 0x7C;
constexpr u32 kSaveCheckPoint     = 0x43;
constexpr u32 kSaveCheckPointSet0c = 0x44;
constexpr u32 kSaveCheckPointSet08 = 0x45;
constexpr u32 kSaveNextGoto       = 0x46;
constexpr u32 kSaveFlags8         = 0x47;
constexpr u32 kSaveGameMode       = 0x48;
constexpr u32 kSaveCoinNum        = 0x49;
constexpr u32 kSaveFlags16        = 0x4A;
constexpr u32 kSavePlaySeconds    = 0x4C;
constexpr u32 kSaveTimeNo         = 0x50;
constexpr u32 kSaveCourseType     = 0x51;
constexpr u32 kSaveBossFlags      = 0x52;
constexpr u32 kSaveAreaParam      = 0x53;
constexpr u32 kSaveQuakeValue     = 0x54;
constexpr u32 kSaveQuakePower     = 0x58;

// Address: 0x024CC370
void sub_024CC370(void* quake_mgr, s32 type, u8 power, f32 value);

// Address: 0x025141B0
extern void inputMgrInitControllerSlot_(void* controller, s32 slot_index);

// Address: 0x0250C3C8
u8 sub_0250C3C8(u8 character_color)
{
    static const u8 cColorTable[6] = { 0, 1, 2, 3, 5, 4 };

    if (character_color < 1 || character_color > 5)
        return 0;

    return cColorTable[character_color];
}

// Address: 0x0250C3EC
void sub_0250C3EC(InputMgr* mgr)
{
    const u8* save_entry = *reinterpret_cast<const u8**>(reinterpret_cast<u8*>(mgr) + kSaveEntryOffset);
    u8* main = reinterpret_cast<u8*>(MainGame::instance());
    FieldGameData& game_data = *CourseTask::instance()->getGameData();
    u8* game_data_bytes = reinterpret_cast<u8*>(&game_data);
    FieldGameMode& game_mode = *reinterpret_cast<FieldGameMode*>(game_data_bytes + 0x15C);

    u32 cap_slot_no = 0;
    u32 normal_slot_no = 0;

    const u8* player = save_entry + kSavePlayerBase;

    for (s32 i = 0; i < cPlayerNum; ++i)
    {
        FieldPlayerData& entry = game_data.getPlayerData(i);

        entry.is_entry = player[0] == 1;

        u8 life_cnt = player[1];
        if (life_cnt > 99)
            life_cnt = 5;
        entry.life_cnt = life_cnt;

        entry.character = static_cast<PlayerCharacter>(
            player[2] < cPlayerCharacter_NumGame ? player[2] : 0);
        entry.character_color = static_cast<PlayerCharacter>(
            player[3] < cPlayerCharacter_NumGame ? sub_0250C3C8(player[3]) : 0);
        entry.player_mode = static_cast<PlayerMode>(
            player[4] < cPlayerMode_Num ? player[4] : 0);
        entry.mii_cap_visible = (player[6] & 1) != 0;

        if (entry.character_color == cPlayerCharacter_Mii)
        {
            if ((*reinterpret_cast<const u32*>(main + 0x2C) & 0x10) != 0)
            {
                u8 mii_no = *reinterpret_cast<const u8*>(reinterpret_cast<const u8*>(SubjectMgr::instance()) + 0x1E7E);
                entry.mii_slot.setValue(0x02000000u | mii_no);
            }
            else if (entry.mii_cap_visible)
            {
                entry.mii_slot.setValue((cap_slot_no % 3) + 3);
                ++cap_slot_no;
            }
            else
            {
                entry.mii_slot.setValue(normal_slot_no % 3);
                ++normal_slot_no;
            }
        }

        entry.has_star = player[5] == 1;
        entry.coin_cnt = *reinterpret_cast<const u32*>(player + 8);

        player += kSavePlayerStride;
    }

    for (s32 i = 0; i < 3; ++i)
    {
        s8 digit = static_cast<s8>(save_entry[kSaveBannerBase + i]);
        if (digit + 1 >= 6)
            digit = -1;
        game_data_bytes[0x13D + i] = static_cast<u8>(digit);
    }

    u8 banner_digit[3];
    banner_digit[0] = game_data_bytes[0x13D];
    banner_digit[1] = game_data_bytes[0x13E];
    banner_digit[2] = game_data_bytes[0x13F];

    s32 checkpoint_index = static_cast<s8>(save_entry[kSaveCheckPoint]);
    if (checkpoint_index < 0 || checkpoint_index >= 3)
    {
        game_data.clearCheckPoint();
    }
    else
    {
        u8 set_0c = static_cast<u8>(static_cast<s8>(save_entry[kSaveCheckPointSet0c]));
        if (set_0c >= 4)
            set_0c = 0;

        u8 set_08 = save_entry[kSaveCheckPointSet08];
        if (set_08 != 0 && set_08 != 1)
            set_08 = 0;

        CourseInfo* course_info = CourseInfo::instance();
        game_data.setCheckPoint(checkpoint_index, set_0c, 0, set_08,
                                course_info->getWorldNo(), course_info->getCourseNo(),
                                course_info->getFileNo(), save_entry[kSaveNextGoto],
                                banner_digit);
    }

    u8 flags8 = save_entry[kSaveFlags8];
    main[0x21DFA] = flags8 & 1;
    main[0x21DFB] = (flags8 >> 1) & 1;

    if ((flags8 & 1) != 0)
        main[0x1E0] = (flags8 >> 1) & 1;

    game_mode.setMode(static_cast<FieldGameMode::Mode>(save_entry[kSaveGameMode]));

    u8 coin_num = save_entry[kSaveCoinNum];
    if (coin_num > 99)
        coin_num = 0;
    game_data.setCoinNum(coin_num);

    u32 play_seconds = *reinterpret_cast<const u32*>(save_entry + kSavePlaySeconds);
    if (static_cast<s32>(play_seconds) < 0 || play_seconds > kMaxPlaySeconds)
        play_seconds = 0;
    *reinterpret_cast<u32*>(game_data_bytes + 0x138) = play_seconds;

    u16 flags16 = *reinterpret_cast<const u16*>(save_entry + kSaveFlags16);

    game_data_bytes[0x169] = flags16 & 1;
    game_data_bytes[0x13C] = (flags16 >> 1) & 1;

    bool quake_short = ((flags16 >> 2) & 1) != 0;
    bool quake_long = ((flags16 >> 3) & 1) != 0;

    if (quake_short && quake_long)
    {
        quake_short = false;
        quake_long = false;
    }

    if (game_mode.getMode() == FieldGameMode::cBoostRush)
    {
        s32 quake_type = 0;

        if (quake_short)
            quake_type = 6;
        else if (quake_long)
            quake_type = 4;

        u8 quake_power = save_entry[kSaveQuakePower];
        if (quake_power > kMaxQuakePower)
            quake_power = kMaxQuakePower;

        sub_024CC370(*reinterpret_cast<void**>(kQuakeMgrInstance), quake_type, quake_power,
                     *reinterpret_cast<const f32*>(save_entry + kSaveQuakeValue));
    }

    *reinterpret_cast<u8*>(*reinterpret_cast<u8**>(kSaveApplyMgr) + kSaveApplyFlagOff) =
        (flags16 >> 4) & 1;
    game_data_bytes[0x160] = (flags16 >> 5) & 1;

    game_data_bytes[0x168] = save_entry[kSaveTimeNo];

    u8 course_type = save_entry[kSaveCourseType];
    if (course_type != 10 && course_type != 11 && course_type != 14)
        course_type = 0xE;
    *reinterpret_cast<u32*>(game_data_bytes + 0x164) = course_type;

    u8 boss_flags = save_entry[kSaveBossFlags];
    if ((boss_flags & 0x80) != 0)
    {
        game_data_bytes[0x1A5] = boss_flags & 0x7F;
        game_data_bytes[0x1A4] = 0;
    }
    else
    {
        game_data_bytes[0x1A4] = boss_flags;
        game_data_bytes[0x1A5] = 0;
    }

    game_data_bytes[0x140] = save_entry[kSaveAreaParam];
}

// Address: 0x0250F9BC
void sub_0250F9BC(void* dst, sead::Heap* heap);

// Address: 0x0250F878
void sub_0250F878(void* obj);

// Address: 0x02514150
void sub_02514150(void* obj);

// Address: 0x029F1858
void* sub_029F1858(u32 size, u32 align, sead::Heap* heap);

}

// Address: 0x0250CDBC
void InputMgr::applySaveEntry_(const u32* p_mode_word, void* p_arg, sead::Heap* heap)
{
    u8* self = reinterpret_cast<u8*>(this);
    u32* disable_stride_a = reinterpret_cast<u32*>(self + 0x4F4);
    u32* disable_stride_b = reinterpret_cast<u32*>(self + 0x504);
    u32 zero = 0;

    for (s32 i = 0; i < 4; ++i)
    {
        disable_stride_a[i] = zero;
        disable_stride_b[i] = zero;
    }

    self[0x53C] = 0;
    u32 mode = p_mode_word != nullptr ? *p_mode_word : 0;
    *reinterpret_cast<u32*>(self + 0x514) = mode;

    u8** working_save = reinterpret_cast<u8**>(self + 0x55C);

    if (mode == 1)
    {
        *working_save = nullptr;
    }
    else if (mode == 2)
    {
        u8* buffer = static_cast<u8*>(sub_029F1858(0xE8, 4, heap));
        if (buffer != nullptr)
        {
            sub_0250F878(buffer);
            *working_save = buffer;
            sub_0250F9BC(buffer, heap);
        }
        else
        {
            *working_save = nullptr;
        }
    }

    u32* controller_table = reinterpret_cast<u32*>(self + 0x4E0);
    for (s32 slot = 0; slot < 4; ++slot)
    {
        void* controller = sub_029F1858(0x194, 4, heap);
        if (controller != nullptr)
            sub_02514150(controller);
        controller_table[slot] = reinterpret_cast<u32>(controller);
    }

    void* extra = sub_029F1858(0x194, 4, heap);
    if (extra != nullptr)
        sub_02514150(extra);
    *reinterpret_cast<u32*>(self + 0x4F0) = reinterpret_cast<u32>(extra);

    if (mode == 1 || mode == 2)
        sub_0250C3EC(this);
}

// Address: 0x0250D1EC
void InputMgr::setupCourseControllers_()
{
    u8* self = reinterpret_cast<u8*>(this);
    void** table = reinterpret_cast<void**>(self + 0x4E0u);
    for (s32 index = 0; index < 4; index++)
        inputMgrInitControllerSlot_(table[index], index);
    void* extra = *reinterpret_cast<void**>(self + 0x4F0u);
    inputMgrInitControllerSlot_(extra, 4);
    mControllersRegistered = true;
}
