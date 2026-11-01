#include <game/CourseTask.h>

#include <game/BalloonMgr.h>
#include <game/CoinBattleScoreMgr.h>
#include <game/CommonWindowMgr.h>
#include <game/CourseTimer.h>
#include <game/FieldGame.h>
#include <game/FlagCtrl.h>
#include <game/SelectCursor.h>
#include <game/SmallScoreMgr.h>
#include <game/SubjectMgr.h>
#include <game_info/CourseInfo.h>
#include <input/InputMgr.h>
#include <map/CoinOrigin.h>
#include <map_obj/ActorCoinMgr.h>
#include <system/CommentMgr.h>
#include <system/MainGame.h>
#include <system/ResMgr.h>

#include <actor/ActorMgr.h>
#include <actor/ActorStatus.h>
#include <player/PlayerMgr.h>
#include <enemy/TottenMgr.h>
#include <event/EventMgr.h>
#include <fukidashi/FukidashiMgr.h>
#include <layout/GamesceneBase.h>

#include <actor/ScoreMgr.h>

#include <prim/seadSafeString.h>

#include <cstring>

namespace {

// Address: 0x02742F9C
void sub_02742F9C(void* course_owner, void* game_data);

// Address: 0x02A0A2FC
extern void sub_02A0A2FC(void* self);

// Address: 0x02A04D54
extern void sub_02A04D54(void* self);

// Address: 0x02A04DE8
extern void sub_02A04DE8(void* self, s32 mode);

// Address: 0x02A06518
extern void sub_02A06518(void* self);

// Address: 0x02A067C4
extern void sub_02A067C4(void* self, s32 mode);

// Address: 0x02A0A384
extern void sub_02A0A384(void* self, s32 mode);

// Address: 0x02A3760C
extern void sub_02A3760C(void* self, s32 mode);

// Address: 0x02536454
extern void f_02536454(void* self);

// Address: 0x024CEA10
extern s32 sub_024CEA10(SubjectMgr* self);

template<typename T>
T& fieldAt(u8* base, u32 offset)
{
    return *reinterpret_cast<T*>(base + offset);
}

u8& courseInfoByte(CourseInfo* course_info, u32 offset)
{
    return reinterpret_cast<u8*>(course_info)[offset];
}

u8& taskByte(CourseTask* task, u32 offset)
{
    return reinterpret_cast<u8*>(task)[offset];
}

u32& taskWord(CourseTask* task, u32 offset)
{
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(task) + offset);
}

FieldGameMode& taskGameMode(CourseTask* task)
{
    return *reinterpret_cast<FieldGameMode*>(reinterpret_cast<u8*>(task) + 0x280);
}

CommentMgr* loadCommentMgrFromData()
{
    return *reinterpret_cast<CommentMgr**>(reinterpret_cast<uintptr_t>(0x101E7D5C));
}

u8* mainGameStoryBytes(MainGame* main_game)
{
    return reinterpret_cast<u8*>(main_game) + 0x2001DFA;
}

void* loadSingletonAt(u32 address)
{
    return *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(address));
}

struct GamesceneAllocPair
{
    u32 vtable;
    u32 type_info;
};

struct CourseResNodeRef
{
    void* node;
    u32 type_info;
};

void constructCourseTaskSlot(u8* object, CourseTask* owner)
{
    sub_02A0A2FC(object);

    fieldAt<u32>(object, 0x0C) = 0x100B71C4;
    fieldAt<u32>(object, 0x10) = 0;
    fieldAt<u32>(object, 0x14) = 0;
    fieldAt<u32>(object, 0x18) = reinterpret_cast<u32>(owner);
    fieldAt<u32>(object, 0x1C) = 0;
    fieldAt<u32>(object, 0x20) = reinterpret_cast<u32>(object + 0x24);
    fieldAt<u32>(object, 0x24) = 0x100B71EC;
    fieldAt<u32>(object, 0x28) = reinterpret_cast<u32>(owner);
    fieldAt<u16>(object, 0x2C) = 0;
    fieldAt<u16>(object, 0x2E) = 0xFFFF;
    fieldAt<u32>(object, 0x30) = 0x024C0B70;
    fieldAt<u8>(object, 0x38) = 0;
}

void constructCourseTaskEvent(u8* object)
{
    sub_02A0A2FC(object);

    fieldAt<u32>(object, 0x0C) = 0x101B8054;
    fieldAt<u32>(object, 0x10) = 0x100B720C;
    fieldAt<u32>(object, 0x14) = 0x100B703C;
    fieldAt<u32>(object, 0x18) = 0;
    fieldAt<u32>(object, 0x1C) = 0;
    fieldAt<u32>(object, 0x20) = 0x100B7024;
    fieldAt<u32>(object, 0x24) = 0;
    fieldAt<u16>(object, 0x28) = 0;
    fieldAt<u16>(object, 0x2A) = 0;
    fieldAt<u32>(object, 0x2C) = 0;
    fieldAt<u32>(object, 0x20) = 0x100B711C;
}

} // namespace

SEAD_TASK_SINGLETON_DISPOSER_IMPL(CourseTask)

// Address: 0x024BCAA0
CourseTask::CourseTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "CourseTask")
{
    u8* self = reinterpret_cast<u8*>(this);

    mCourseRestart = false;
    fieldAt<u8>(self, 0xC9) = 0;
    mpGamescene = nullptr;

    for (u32 i = 0; i < (0x124 - 0xD0) / sizeof(u32); ++i)
        fieldAt<u32>(self, 0xD0 + i * 4) = 0;

    taskWord(this, 0x308) = 0;

    for (u32 i = 0; i < 5; ++i)
        constructCourseTaskEvent(self + 0x30C + i * 0x40);

    constructCourseTaskSlot(self + 0x450, this);
    sub_02A06518(self + 0x48C);
    sub_02A04D54(self + 0x538);

    taskWord(this, 0x590) = 0;
    fieldAt<u8>(self, 0x594) = 0;
    taskWord(this, 0x598) = 0xFFFFFFFF;
    fieldAt<u8>(self, 0x59C) = 0;
    taskWord(this, 0x5A0) = 0;
}

// Address: 0x024BC950
CourseTask::~CourseTask()
{
    u8* self = reinterpret_cast<u8*>(this);

    sub_02A04DE8(self + 0x538, 2);
    sub_02A067C4(self + 0x48C, 2);
    sub_02A0A384(self + 0x450, 0);

    for (u32 i = 0; i < 5; ++i)
        sub_02A3760C(self + 0x40C - i * 0x40, 2);
}

// Address: 0x024C01DC
void CourseTask::setSubjectClear()
{
    u8* gamescene = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(this) + 0xDC);
    if (gamescene == nullptr)
        return;

    gamescene[0xED8] = 1;
}

// Address: 0x024C01F4
void CourseTask::setSubjectFail()
{
    u8* gamescene = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(this) + 0xE0);
    if (gamescene == nullptr)
        return;

    gamescene[0xED8] = 1;
}

// Address: 0x024C0D20
void CourseTask::doBonusTime()
{
    u8* gamescene = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(this) + 0xCC);
    if (gamescene == nullptr)
        return;

    if (getGamesceneUnkBool())
        return;

    f_02536454(gamescene + 0x580);
    gamescene[0x149C] = 1;
}

// Address: 0x024C0D6C
bool CourseTask::getGamesceneUnkBool() const
{
    const u8* gamescene = *reinterpret_cast<const u8* const*>(reinterpret_cast<const u8*>(this) + 0xCC);
    if (gamescene == nullptr)
        return false;

    return gamescene[0x149C] != 0;
}

// Address: 0x024D29A4
void CourseInfo_applyNextWorldCourseToNow(CourseInfo* course_info)
{
    courseInfoByte(course_info, 0x10) = course_info->getNextWorldNo();
    courseInfoByte(course_info, 0x11) = course_info->getNextCourseNo();
}

// Address: 0x024D3888
bool CourseInfo_isCourseNo0x39(CourseInfo* course_info)
{
    return course_info->getCourseNo() == 0x39;
}

// Address: 0x024D38B4
bool CourseInfo_isSpecialCourseNo(CourseInfo* course_info)
{
    u8 course_no = course_info->getCourseNo();
    if (course_no - 0x1f <= 3)
        return true;
    if (course_no - 0xca <= 3)
        return true;
    return false;
}

// Address: 0x024D29B8
void CourseInfo_commitNextFromCourseData(CourseInfo* course_info)
{
    void* course_data = CourseData_getFile(courseInfoByte(course_info, 0x1e));
    if (courseInfoByte(course_info, 0x1f) == 0xff)
    {
        CourseTask* course_task = CourseTask::instance();
        if (course_task != nullptr)
        {
            FieldGameMode::Mode mode = taskGameMode(course_task).getMode();
            if (mode == FieldGameMode::cBoostRush || mode == FieldGameMode::cCoinBattle)
            {
                u8* file = reinterpret_cast<u8*>(course_data);
                void** chain = reinterpret_cast<void**>(file + 8);
                u8 file_no = reinterpret_cast<u8*>(chain[0])[0x13];
                if (file_no != 0)
                {
                    if (chain[0] != chain[1])
                        file_no = reinterpret_cast<u8*>(chain[1])[0x13];
                }
                courseInfoByte(course_info, 0x1f) = file_no;
            }
        }
    }
    u8* raw = reinterpret_cast<u8*>(course_info);
    u32 next_scene = *reinterpret_cast<u32*>(raw + 0x20);
    *reinterpret_cast<u32*>(raw + 0x20) = 0;
    *reinterpret_cast<u32*>(raw + 0x18) = next_scene;
    raw[0x13] = raw[0x1f];
    raw[0x12] = raw[0x1e];
    raw[0x14] = reinterpret_cast<u8*>(course_data)[0xd];
}

// Address: 0x024BD86C
void CourseTask::setupCourse()
{
    CommentMgr* comment_mgr = loadCommentMgrFromData();
    u32 comment_state = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(comment_mgr) + 0x10);
    if (comment_state == 2 || comment_state == 1)
        CommentMgr_onCourseSetup(comment_mgr);

    CourseTask_allocCourseHeap(0);
    CourseSetupStack_pushSentinels();

    CourseInfo* course_info = CourseInfo::instance();
    CourseInfo_applyNextWorldCourseToNow(course_info);

    std::memcpy(&mGameData, &FieldGame::instance()->getGameData(), sizeof(FieldGameData));
    mGameData.resetEntriesUnk30();
    setupNabbitEntry();

    MainGame* main_game = MainGame::instance();
    u8* story_bytes = mainGameStoryBytes(main_game);
    story_bytes[0x12] = 0;

    if (!CourseInfo_isCourseNo0x39(course_info) && !CourseInfo_isSpecialCourseNo(course_info))
    {
        if (mGameData.checkEnterCourse(course_info->getWorldNo(), course_info->getCourseNo()) == -1 ||
            (courseInfoByte(course_info, 0x1e) == 2 && course_info->getNextSceneEnterType() != 2))
        {
            mGameData.clearCheckPoint();
        }
    }

    for (s32 glyph_index = 0; glyph_index < 3; ++glyph_index)
    {
        s8 glyph = static_cast<s8>(taskByte(this, 0x134 + glyph_index));
        setGlyph(glyph_index, glyph);
    }

    u8 picture_glyph = PicturePaneMgr_lookupGlyph(reinterpret_cast<u8*>(main_game) + 0x34,
        course_info->getWorldNo(), course_info->getCourseNo());
    taskByte(this, 0x264) = picture_glyph;

    s32 game_mode = taskGameMode(this).getMode();
    bool flag_28d = false;
    if (game_mode == FieldGameMode::cStory)
    {
        u32 main_flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(main_game) + 0x2c);
        if ((main_flags & 1) == 0 && (main_flags & 2) == 0 && !CourseInfo_isCourseNo0x39(course_info))
            flag_28d = !course_info->isTitle();
    }
    else if (game_mode <= FieldGameMode::cCoinBattle)
    {
        if (!CourseInfo_isCourseNo0x39(course_info))
            flag_28d = !course_info->isTitle();
    }
    else if (game_mode == FieldGameMode::cChallenge)
    {
        if (sub_024CEA10(SubjectMgr::instance()) == 4)
            flag_28d = true;
    }
    else
    {
        taskByte(this, 0x28d) = 0;
    }

    taskByte(this, 0x28d) = flag_28d ? 1 : 0;

    if (game_mode == FieldGameMode::cCoinEdit ||
        course_info->isStaffCredit() ||
        CourseInfo_isSpecialCourseNo(course_info))
    {
        taskByte(this, 0x260) = 0;
    }

    if (story_bytes[0] != 0)
    {
        u8 world_no = course_info->getWorldNo();
        if (world_no < 7)
        {
            u8 bit = static_cast<u8>(1 << world_no);
            u8 story_byte = story_bytes[2];
            taskByte(this, 0x304) = static_cast<u8>(((story_byte & bit) - 1) >> 31);
        }
        else
            taskByte(this, 0x304) = 0;
    }
    else
        taskByte(this, 0x304) = 0;

    GamesceneAllocPair gamescene_pair = {};
    gamescene_pair.vtable = 0x100B7240;
    gamescene_pair.type_info = 0x100B703C;
    GamesceneBase* gamescene = GamesceneFactory_create(nullptr, &gamescene_pair, 0, 1, 0);
    s32 gamescene_heap_id = 1;
    if (gamescene != nullptr)
        gamescene_heap_id = GamesceneFactory_release(gamescene);

    InputMgr::createInstance(nullptr);

    InputMgr* input_mgr = InputMgr::instance();
    u8* save_entry_field = reinterpret_cast<u8*>(main_game) + 0x88;
    u8* save_entry = *reinterpret_cast<u8**>(save_entry_field);
    alignas(4) u32 apply_mode = 0;
    if (save_entry[0] != 0)
    {
        apply_mode = 2;
        InputMgr_applySaveEntry_(input_mgr, &apply_mode, save_entry_field, 0);
    }
    else if (taskGameMode(this).getMode() == FieldGameMode::cChallenge)
    {
        apply_mode = 1;
        InputMgr_applySaveEntry_(input_mgr, &apply_mode, save_entry_field, 0);
    }
    else
    {
        apply_mode = 0;
        InputMgr_applySaveEntry_(input_mgr, &apply_mode, save_entry_field, 0);
    }

    if (gamescene != nullptr)
        gamescene->vf2C();
    if (gamescene_heap_id != 1)
        GamesceneFactory_release(reinterpret_cast<void*>(static_cast<uintptr_t>(gamescene_heap_id)));

    EventMgr::createInstance(nullptr);
    ActorMgr::createInstance(nullptr);
    ActorStatus::createInstance(nullptr);
    f_0269B0D8(0);
    f_0268E0EC(0);

    GamesceneAllocPair gamescene_b_pair = {};
    gamescene_b_pair.vtable = 0x100B724C;
    gamescene_b_pair.type_info = 0x100B703C;
    GamesceneBase* gamescene_b = GamesceneFactory_create(nullptr, &gamescene_b_pair, 0, 1, 0);
    s32 gamescene_b_heap_id = 1;
    if (gamescene_b != nullptr)
        gamescene_b_heap_id = GamesceneFactory_release(gamescene_b);
    f_0268F428(0);
    if (gamescene_b != nullptr)
        gamescene_b->vf2C();
    if (gamescene_b_heap_id != 1)
        GamesceneFactory_release(reinterpret_cast<void*>(static_cast<uintptr_t>(gamescene_b_heap_id)));

    f_0268BE54(0);
    f_02916AF0(0);
    sub_02742D2C(0);
    CoinBattleScoreMgr::createInstance(nullptr);
    ActorCollisionCheckMgr_createInstance(0);
    f_0269BB7C(0);
    TouchDrcMgr_createInstance(0);
    f_020043F0(0);
    ActorCoinMgr::createInstance(nullptr);
    BlockMgr_createInstance(0);
    ScoreMgr::createInstance(nullptr);
    CourseTimer::createInstance(nullptr);
    ActorBgCollisionMgr_createInstance(0);
    UnitBgCollisionHolder_createInstance(0);
    f_024C1838(0);
    f_022C9288(0);
    FlagCtrl::createInstance(nullptr);
    CoinOrigin::createInstance(nullptr);
    SmallScoreMgr::createInstance(nullptr);
    CommonWindowMgr::createInstance(nullptr);
    SelectCursor::createInstance(nullptr);
    createGamesceneByMode();
    FukidashiMgr::createInstance(nullptr);
    f_0250A698(0);
    f_02816A7C(0);
    BalloonMgr::createInstance(nullptr);
    f_02891458(0);
    f_028914EC(loadSingletonAt(0x101E10A8));
    f_024D967C(0);
    f_024D9744(loadSingletonAt(0x101D2B3C), 0);
    f_028D3A60(0);
    f_028D3B40(loadSingletonAt(0x101E18E8));
    f_024ED434(0);

    if (taskGameMode(this).isWmMode())
    {
        GamesceneAllocPair wm_pair = {};
        wm_pair.vtable = 0x100B7258;
        wm_pair.type_info = 0x100B703C;
        GamesceneBase* wm_hud = GamesceneFactory_create(nullptr, &wm_pair, 0, 1, 0);
        s32 wm_heap_id = 1;
        if (wm_hud != nullptr)
            wm_heap_id = GamesceneFactory_release(wm_hud);
        f_024EDAA0(loadSingletonAt(0x101D2D18), 0);
        if (wm_hud != nullptr)
            wm_hud->vf2C();
        if (wm_heap_id != 1)
            GamesceneFactory_release(reinterpret_cast<void*>(static_cast<uintptr_t>(wm_heap_id)));
    }

    CoinOrigin::initialize(loadSingletonAt(0x101EB040), 0);
    f_024C18B8(loadSingletonAt(0x101D15FC));

    GamesceneAllocPair pack_pair = {};
    pack_pair.vtable = 0x100B7264;
    pack_pair.type_info = 0x100B703C;
    GamesceneBase* pack_hud = GamesceneFactory_create(nullptr, &pack_pair, 0, 1, 0);
    s32 pack_heap_id = 1;
    if (pack_hud != nullptr)
        pack_heap_id = GamesceneFactory_release(pack_hud);

    comment_mgr = loadCommentMgrFromData();
    comment_state = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(comment_mgr) + 0x10);
    if (comment_state != 2 && comment_state != 1)
    {
        alignas(4) u8 course_pack_name[0x18] = {};
        *reinterpret_cast<u32*>(course_pack_name + 0x00) = 0x100B7104;
        *reinterpret_cast<u32*>(course_pack_name + 0x08) = 8;
        CourseResPackNameBuilder_build(course_info->getWorldNo(), course_info->getCourseNo(), course_pack_name);
        ResMgr::instance()->loadCourseResPack(*reinterpret_cast<sead::SafeString*>(course_pack_name), nullptr);
        CourseResPackNameBuilder_teardown(0);
        CourseData_releaseFileRef(loadSingletonAt(0x101EB048));
    }

    for (s32 file_index = 0; file_index < 4; ++file_index)
    {
        void* file = CourseData_getFile(file_index);
        if (file != nullptr)
        {
            void* base = *reinterpret_cast<void**>(reinterpret_cast<u8*>(file) + 4);
            CourseResNodeRef node = {};
            node.type_info = 0x100B703C;
            node.node = base;
            CourseTask_bindCourseResNode(&node);
            node.node = reinterpret_cast<u8*>(base) + 0x20;
            CourseTask_bindCourseResNode(&node);
            node.node = reinterpret_cast<u8*>(base) + 0x40;
            CourseTask_bindCourseResNode(&node);
            node.node = reinterpret_cast<u8*>(base) + 0x60;
            CourseTask_bindCourseResNode(&node);
        }
    }

    if (pack_hud != nullptr)
        pack_hud->vf2C();
    if (pack_heap_id != 1)
        GamesceneFactory_release(reinterpret_cast<void*>(static_cast<uintptr_t>(pack_heap_id)));

    CourseInfo_commitNextFromCourseData(course_info);
    course_info->setNextSceneEnterType(course_info->getSceneEnterType());

    u32 scene_enter_type = course_info->getNextSceneEnterType();
    taskByte(this, 0xca) = static_cast<u8>(scene_enter_type == 2);
    taskByte(this, 0xcb) = 0;
    MainGame_setCourseBanner(loadSingletonAt(0x101E7D58), course_info->getWorldNo(),
        course_info->getCourseNo(), scene_enter_type == 2);
    f_026CA03C(loadSingletonAt(0x101EB43C));

    if (taskGameMode(this).getMode() == FieldGameMode::cCoinEdit)
        taskWord(this, 0x308) = CourseTask_selectEntryCharacter(this);

    f_0202ADC4();
    ActorResLoader_load(1, 0);
    if (taskGameMode(this).isDvMiiMode())
    {
        u32 entry_index = taskWord(this, 0x58);
        f_022A6048(taskWord(this, 0x44 + entry_index * 4),
            reinterpret_cast<u8*>(this) + entry_index * 4);
    }

    FlagCtrl::initialize(loadSingletonAt(0x101D160C));

    if (taskGameMode(this).getMode() == FieldGameMode::cChallenge)
    {
        SubjectMgr* subject_mgr = SubjectMgr::instance();
        subject_mgr->selectSaveFile(subject_mgr->getSelectedFile());
    }

    if (ChallengeMgr_isActive())
    {
        u8 file_no = courseInfoByte(course_info, 0x12);
        u8* course_file = reinterpret_cast<u8*>(CourseData_getFile(file_no));
        u16 timer_a = 0x1f4;
        u16 timer_b = 0x12c;
        u16 timer_c = 0xc8;
        if (course_file != nullptr)
        {
            u16* header = reinterpret_cast<u16*>(*reinterpret_cast<void**>(course_file + 8));
            if (header[5] != 0)
                timer_a = header[5];
            if (header[10] != 0)
                timer_b = header[10];
            if (header[11] != 0)
                timer_c = header[11];
        }
        if (story_bytes[0] != 0)
        {
            timer_a = 0x64;
            timer_b = 0x64;
            timer_c = 0x64;
        }
        u8 world_digit = courseInfoByte(course_info, 0x13);
        u8* entry = reinterpret_cast<u8*>(*reinterpret_cast<void**>(course_file + 8));
        if (world_digit != entry[0x10])
        {
            u8* alt = reinterpret_cast<u8*>(*reinterpret_cast<void**>(course_file + 0));
            if (world_digit != alt[0x13])
            {
                u32 list_count = *reinterpret_cast<u32*>(course_file + 0x98);
                u8* list_base = reinterpret_cast<u8*>(*reinterpret_cast<void**>(course_file + 0x20));
                bool set = false;
                for (u32 i = 0; i < list_count; ++i)
                {
                    u8* node = list_base + i * 0x18;
                    if (*reinterpret_cast<u16*>(node) != 0x19)
                        continue;
                    u32 packed = *reinterpret_cast<u32*>(node + 8);
                    if (static_cast<u8>(packed >> 16) != courseInfoByte(course_info, 0x13))
                        continue;
                    u8 sub = static_cast<u8>(packed & 0xf);
                    if (sub < 1)
                        CourseTimer::instance()->setTimer(timer_b);
                    else if (sub == 1)
                        CourseTimer::instance()->setTimer(timer_c);
                    else
                        CourseTimer::instance()->setTimer(timer_a);
                    set = true;
                    break;
                }
                if (!set)
                    CourseTimer::instance()->setTimer(timer_a);
            }
        }
    }

    ActorMgr::initialize(loadSingletonAt(0x101C30C8), 0);
    PlayerMgr::instance()->initializeForCourseSetup();
    sub_02742F9C(loadSingletonAt(0x101EC398), &mGameData);
    f_0269BC94(loadSingletonAt(0x101EB06C));
    f_0268E888(loadSingletonAt(0x101EAFC0), 0);
    f_0268F7F0(loadSingletonAt(0x101EAFE8), 0);
    f_0250A840(loadSingletonAt(0x101D2DB0));

    if (mpGamescene != nullptr)
    {
        void* renderer = *reinterpret_cast<void**>(reinterpret_cast<u8*>(mpGamescene) + 0x14A0);
        using VFunc = void(*)(GamesceneBase*);
        VFunc fn = reinterpret_cast<VFunc>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(renderer) + 0xC));
        fn(mpGamescene);
    }

    if (taskWord(this, 0xD0) != 0)
        f_02657CA4();
    if (loadSingletonAt(0x101D7284) != nullptr)
        f_025CE934();
    if (loadSingletonAt(0x101D31F8) != nullptr)
        f_0252E6C4();
    if (loadSingletonAt(0x101D5224) != nullptr)
        f_0258B084();
    if (loadSingletonAt(0x101D3728) != nullptr)
        f_0253B5CC();
    if (taskWord(this, 0x120) != 0)
        f_02532D14();
    if (taskWord(this, 0xD4) != 0)
        f_02666DA8();
    if (taskWord(this, 0xD8) != 0)
        f_0258C1F0();
    if (taskWord(this, 0xE4) != 0)
        f_02650F7C();
    if (taskWord(this, 0xE8) != 0)
        f_02650344();
    if (taskWord(this, 0xEC) != 0)
        f_0264E25C();
    if (taskWord(this, 0xDC) != 0)
        f_02537290();
    if (taskWord(this, 0xE0) != 0)
        f_025396C4();
    if (taskWord(this, 0xF4) != 0)
    {
        LightMapMgr_initialize(loadSingletonAt(0x101D2C60), 0);
        f_02551B04();
    }
    if (taskWord(this, 0xF8) != 0)
        f_025F4B24();
    if (taskWord(this, 0xFC) != 0)
        f_025BE710();
    if (taskWord(this, 0x100) != 0)
        f_02646F58();
    if (taskWord(this, 0x10C) != 0)
    {
        f_02627FF4();
        f_026287BC();
    }
    if (taskWord(this, 0x104) != 0)
        f_02614CD0();
    if (taskWord(this, 0x108) != 0)
        f_02534138();
    if (taskWord(this, 0x110) != 0)
        f_02667C9C();
    if (taskWord(this, 0x114) != 0)
        f_026533B0();
    if (taskWord(this, 0x118) != 0)
        f_02657278();
    if (taskWord(this, 0x11C) != 0)
        f_025846D4();
    if (taskWord(this, 0xF0) != 0)
        f_025F281C();

    f_024CC8E8(loadSingletonAt(0x101D1860));
    f_024BC4C4(loadSingletonAt(0x101D15E8));
    SelectCursor::create(loadSingletonAt(0x101D17A8));
    if (loadSingletonAt(0x101E830C) != nullptr)
        f_025FBCF0();
    f_025F2F50(loadSingletonAt(0x101D7FE0));
    f_024B3544(loadSingletonAt(0x101D157C));
    if (loadSingletonAt(0x101D4264) != nullptr)
        f_0255B524();
    f_026444A8(loadSingletonAt(0x101E9AB0));
    if (loadSingletonAt(0x101EA700) != nullptr)
        f_026661D8();

    TottenMgr::createInstance(nullptr);
    f_024230A8(loadSingletonAt(0x101D0264));
    AreaTask_createFromCourseTask(Scene::instance(), this);
    CourseTask_onSetupComplete();
}
