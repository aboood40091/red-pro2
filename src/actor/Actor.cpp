#include <actor/Actor.h>
#include <actor/ActorCullUtil.h>
#include <actor/ActorUtil.h>
#include <actor/ChibiYoshiEatData.h>
#include <actor/EatData.h>
#include <actor/Profile.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BasicBgCollisionCheck.h>
#include <collision/BgCollisionCheckParam.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/TottenMgr.h>
#include <fragment/FragmentMgr.h>
#include <fukidashi/FukidashiMgr.h>
#include <game/AreaTask.h>
#include <game/CourseTask.h>
#include <game/Info.h>
#include <game/SubjectMgr.h>
#include <map/Bg.h>
#include <map/LayerID.h>
#include <map_obj/ChibiYoshiAwaData.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <scroll/BgScrollMgr.h>
#include <system/MainGame.h>

#define COMBO_CNT_MAX 9

const f32 Actor::cCullXLimit = 80.0f;
const f32 Actor::cCullYLimit = 256.0f;

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

    const f32 l = mPos.x + mVisibleAreaOffset.x - mVisibleAreaSize.x * 0.5f;
    const f32 r = l + mVisibleAreaSize.x;

    const f32 b = mPos.y + mVisibleAreaOffset.y - mVisibleAreaSize.y * 0.5f;
    const f32 t = b + mVisibleAreaSize.y;

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
                if (BgUnitCode::getType(res.bg_check_data) != BgUnitCode::cType_None || BgUnitCode::getHitType(res.bg_check_data) != BgUnitCode::cHitType_None)
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

Actor::Actor(const ActorCreateParam& param)
    : ActorBase(param)
    , mDirection(DIRECTION_RIGHT)
    , mPlayerNo(-1)
    , mControllerLytPlayerNo(-1)
    , mLayer(param.param_ex_0.course.layer)
    , mCollisionMask(cCcLineKind_0)
    , mSpeedF(0.0f)
    , mSpeedFMax(0.0f)
    , mFallSpeedMax(0.0f)
    , mAccelY(0.0f)
    , mAccelF(0.0f)
    , mPos(param.position)
    , mSpeed(0.0f, 0.0f, 0.0f)
    , mSpeedMax(0.0f, 0.0f, 0.0f)
    , mScale(1.0f, 1.0f, 1.0f)
    , mAngle()
    , mAnglePrev()
    , mPosDelta(0.0f, 0.0f)
    , mCollisionCheck()
    , mVisibleAreaOffset(
        param.p_profile->getActorCreateInfo().spawn_range.offset_x,
        param.p_profile->getActorCreateInfo().spawn_range.offset_y)
    , mVisibleAreaSize(
        param.p_profile->getActorCreateInfo().spawn_range.half_size_x * 2.0f,
        param.p_profile->getActorCreateInfo().spawn_range.half_size_y * 2.0f)
    , mSize(mVisibleAreaSize)
    , mAreaNo(Info::instance()->getAreaNo())
    , mActorType(cActorType_Generic)
    , mIsExecEnable(true)
    , mIsDrawEnable(true)
    , mIsNoRespawn(false)
    , _211(1)
    , mCarryFlag(0)
    , mSwitchFlag0(param.param_ex_0.course.switch_flag_0)
    , mSwitchFlag1(param.param_ex_0.course.switch_flag_1)
    , mCreateFlag(param.p_profile->getActorCreateInfo().flag)
    , mBumpDamageTimer(0)
    , mBumpDirection(DIRECTION_RIGHT)
    , _220(0)
    , mCarryDirection(DIRECTION_RIGHT)
    , mThrowPlayerNo(0)
    , mComboCnt(0)
    , mProfFlag(param.p_profile->getFlag())
    , mCenterOffset(0.0f, 0.0f, 0.0f)
    , mPosPrev(param.position)
    , mPosPrevPostExec(param.position)
    , mPosPrev2(param.position)
    , mpEatData(nullptr)
    , mpChibiYoshiEatData(nullptr)
    , mpPropelParts(nullptr)
    , _270(param._28)
    , mThrowSpeed(0.0f)
    , mpChibiYoshiAwaData(nullptr)
{
    const ActorCreateInfo& info = param.p_profile->getActorCreateInfo();
    const f32 cull_range_up = info.cull_range.up;
    const f32 cull_range_down = info.cull_range.down;
    const f32 cull_range_left = info.cull_range.left;
    const f32 cull_range_right = info.cull_range.right;

    mCullLimit.up = cCullYLimit;
    mCullLimit.down = cCullYLimit;
    mCullLimit.left = cCullXLimit;
    mCullLimit.right = cCullXLimit;

    mCullLimit.up += cull_range_up;
    mCullLimit.down += cull_range_down;
    mCullLimit.left += cull_range_left;
    mCullLimit.right += cull_range_right;

    mCollisionCheck.setLayer(mLayer);
}

Actor::~Actor()
{
    ActorCollisionCheckMgr::instance()->release(mCollisionCheck);
}

void Actor::postCreate_(MainState state)
{
    if (state == cState_Success)
    {
        mPosPrev = mPos;
        mPosPrev2 = mPos;
    }
    ActorBase::postCreate_(state);
}

s32 Actor::preExecute_()
{
    mPosPrev = mPosPrev2;

    if (ActorBase::preExecute_() == 0)
        return 0;

    if (!mIsExecEnable)
        return 0;

    getPos2D() += mPosDelta;

    if (mBumpDamageTimer == 8)
    {
        SubjectMgr::instance()->onAcBlockHit();
        blockHitInit_();
    }

    if (mBumpDamageTimer > 0)
        mBumpDamageTimer--;

    return 1;
}

void Actor::postExecute_(MainState state)
{
    if (state == cState_Success)
    {
        mPosPrevPostExec = mPos;

        if (!(mProfFlag & Profile::cFlag_NoLoopPosX))
        {
            f32 pos_x_loop = AreaTask::instance()->getLoopPosX(mPosPrevPostExec.x);
            f32 pos_x_prev = mPosPrevPostExec.x;
            f32 delta = pos_x_prev - pos_x_loop;
            mPos.x = pos_x_loop;
            if (!(-0.0001f <= delta && delta <= 0.0001f))
                mPosPrev.x += pos_x_loop - pos_x_prev;
        }
    }
    mPosPrev2 = mPos;
    mPosDelta = sead::Vector2f::zero;
    ActorBase::postExecute_(state);
}

s32 Actor::preDraw_()
{
    if (ActorBase::preDraw_() == 0)
        return 0;

    if (!mIsDrawEnable)
        return 0;

    if (mpEatData != nullptr && mpEatData->getState() == 2)
        return 0;

    if (mpChibiYoshiEatData != nullptr && mpChibiYoshiEatData->getState() == 2)
        return 0;

    if ((mProfFlag & Profile::cFlag_DrawCullCheck) && drawCullCheck_())
        return 0;

    return 1;
}

bool Actor::drawCullCheck_()
{
    const f32 size_x = mSize.x + 32.0f;
    const f32 size_y = mSize.y + 32.0f;
    
    const f32 l = mPos.x + mVisibleAreaOffset.x - size_x * 0.5f;
    const f32 r = l + size_x;

    const f32 b = mPos.y + mVisibleAreaOffset.y - size_y * 0.5f;
    const f32 t = b + size_y;

    const sead::BoundBox2f visible_range(l, b, r, t);
    return ActorCullUtil::screenCullCheck(visible_range);
}

void Actor::splashEffect_(const sead::Vector3f& pos, EffectID effect_id, u8 wave_scale, const char* sound_label)
{
    const sead::Vector3f eff_pos(getPos2D(), 6500.0f);
    FragmentMgr::instance()->createWaterSplashEff(eff_pos, mLayer, effect_id);
    Bg::instance()->setWaterInWave(mPos, wave_scale);
    GameAudio::getAudioObjMap()->startSound(sound_label, eff_pos);
}

void Actor::setAreaNo_()
{
    mAreaNo = Info::instance()->getAreaNo();
}

void Actor::calcSpeedX_()
{
    f32 speed_x = mSpeed.x;
    f32 speed_max_x = mSpeedMax.x;

    if (speed_x < speed_max_x)
    {
        speed_x += mAccelF;
        if (speed_x > speed_max_x)
            speed_x = speed_max_x;
    }
    else if (speed_x > speed_max_x)
    {
        speed_x -= mAccelF;
        if (speed_x < speed_max_x)
            speed_x = speed_max_x;
    }

    mSpeed.x = speed_x;
}

void Actor::calcSpeedY_(f32 accel_y, f32 speed_max_y)
{
    mSpeed.y += accel_y;
    if (mSpeed.y < speed_max_y)
        mSpeed.y = speed_max_y;
}

void Actor::calcFallSpeed_(f32 accel_y, f32 fall_speed_max)
{
    if (mSpeed.y < fall_speed_max)
    {
        mSpeed.y -= accel_y;
        if (mSpeed.y > fall_speed_max)
            mSpeed.y = fall_speed_max;
    }
    else if (mSpeed.y > fall_speed_max)
    {
        mSpeed.y += accel_y;
        if (mSpeed.y < fall_speed_max)
            mSpeed.y = fall_speed_max;
    }
}

void Actor::carryFukidashiCheck_(s32 action)
{
    static const sead::Vector2f c_range(
        9.0f,
        12.0f
    );
    carryFukidashiCheck_(action, c_range);
}

static inline bool CheckBoxOverlap(const sead::BoundBox2f& a, const sead::BoundBox2f& b)
{
    const sead::Vector2f& min_a = a.getMin();
    const sead::Vector2f& min_b = b.getMin();

    const sead::Vector2f& max_a = a.getMax();
    const sead::Vector2f& max_b = b.getMax();

    return min_a.x <= max_b.x && min_b.x <= max_a.x &&
           min_a.y <= max_b.y && min_b.y <= max_a.y;
}

Actor* Actor::searchCarryFukidashiPlayer_(s32 action)
{
    const sead::Vector2f& center_pos = getCenterPos();

    const FieldGameData& game_data = 
        (CourseTask::instance() != nullptr)
            ? CourseTask::instance()->getGameData()
            : FieldGame::instance()->getGameData();

    Actor* p_actor_player = nullptr;
    f32 dist = sead::Mathf::maxNumber();

    for (s32 i = 0; i < 4; i++)
    {
        if (!PlayerMgr::instance()->isPlayerActive(i))
            continue;

        if (game_data.getPlayerData(mControllerLytPlayerNo).fukidashi_flag.isOnBit(action))
            continue;

        PlayerObject* p_player_current = PlayerMgr::instance()->getPlayerObject2(i);
        if (p_player_current == nullptr)
            continue;

        f32 dist_current = p_player_current->getCenterPos2D().squaredDistance(center_pos);
        if (dist_current < dist)
        {
            p_actor_player = p_player_current;
            dist = dist_current;
        }
    }

    return p_actor_player;
}

void Actor::carryFukidashiCheck_(s32 action, const sead::Vector2f& range)
{
    const sead::Vector2f& center_pos = getCenterPos();
    const sead::BoundBox2f check_range(
        center_pos.x - range.x, center_pos.y - range.y,
        center_pos.x + range.x, center_pos.y + range.y
    );

    const FieldGameData& game_data = 
        (CourseTask::instance() != nullptr)
            ? CourseTask::instance()->getGameData()
            : FieldGame::instance()->getGameData();

    if ((0 <= mControllerLytPlayerNo && mControllerLytPlayerNo < 4) &&
        game_data.getPlayerData(mControllerLytPlayerNo).fukidashi_flag.isOnBit(action))
    {
        mControllerLytPlayerNo = -1;
    }

    if (0 <= mControllerLytPlayerNo && mControllerLytPlayerNo < 4)
    {
        PlayerObject* p_player = PlayerMgr::instance()->getPlayerObject(mControllerLytPlayerNo);
        if (p_player == nullptr)
            return;

        if (!FukidashiMgr::instance()->isVisible(mControllerLytPlayerNo))
            FukidashiMgr::instance()->show(mControllerLytPlayerNo, action);

        bool hide = true;
        if (p_player->isDrawingCarryFukidashi())
        {
            sead::Vector2f center_offset, half_size;
            p_player->getSpinLiftUpCcSizeInfo(&center_offset, &half_size);

            f32 center_pos_x = AreaTask::instance()->getLoopPosX(p_player->getPos().x + center_offset.x) ;
            f32 center_pos_y = p_player->getPos().y + center_offset.y;

            const sead::BoundBox2f check_range_player(
                center_pos_x - half_size.x - 2.0f, center_pos_y - half_size.y,
                center_pos_x + half_size.x + 2.0f, center_pos_y + half_size.y
            );

            if (CheckBoxOverlap(check_range, check_range_player))
                hide = false;
        }
        if (hide)
        {
            FukidashiMgr::instance()->hideTemp(mControllerLytPlayerNo, action);
            mControllerLytPlayerNo = -1;
        }
    }
    else
    {
        Actor* p_actor_player = searchCarryFukidashiPlayer_(action);
        if (p_actor_player == nullptr)
            return;

        PlayerObject* p_player = sead::DynamicCast<PlayerObject>(p_actor_player);
        if (p_player == nullptr)
            return;

        if (p_player->isDrawingCarryFukidashi())
        {
            sead::Vector2f center_offset, half_size;
            p_player->getSpinLiftUpCcSizeInfo(&center_offset, &half_size);

            f32 center_pos_x = AreaTask::instance()->getLoopPosX(p_player->getPos().x + center_offset.x) ;
            f32 center_pos_y = p_player->getPos().y + center_offset.y;

            const sead::BoundBox2f check_range_player(
                center_pos_x - half_size.x, center_pos_y - half_size.y,
                center_pos_x + half_size.x, center_pos_y + half_size.y
            );

            if (CheckBoxOverlap(check_range, check_range_player))
                mControllerLytPlayerNo = p_player->getPlayerNo();
        }
    }
}
