#include <actor/Actor.h>
#include <actor/ActorCullUtil.h>
#include <actor/ActorUtil.h>
#include <actor/ChibiYoshiEatData.h>
#include <actor/EatData.h>
#include <actor/Profile.h>
#include <collision/ActorBgCollisionCheckUtil.h>
#include <collision/ActorCollisionCheckMgr.h>
#include <collision/BasicBgCollisionCheck.h>
#include <collision/BgCollision.h>
#include <collision/BgCollisionCheckParam.h>
#include <collision/BgCollisionCheckResult.h>
#include <enemy/Ice.h>
#include <enemy/PentaroIce.h>
#include <enemy/TottenMgr.h>
#include <fragment/FragmentMgr.h>
#include <fukidashi/FukidashiMgr.h>
#include <game/AreaTask.h>
#include <game/CourseTask.h>
#include <game/Info.h>
#include <game/SubjectMgr.h>
#include <map/Bg.h>
#include <map/LayerID.h>
#include <map_obj/ActorBlockMakeDRC.h>
#include <map_obj/BlockCoinBase.h>
#include <map_obj/ChibiYoshiAwaData.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>
#include <player/PlyIce.h>
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
            return cDirType_Left;
        else
            return cDirType_Right;
    }
    else
    {
        if (mPos.x > BgScrollMgr::instance()->getScreenCenterX() + 96.0f)
            return cDirType_Left;
        else if (mPos.x < BgScrollMgr::instance()->getScreenCenterX() - 96.0f)
            return cDirType_Right;
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
            return cDirType_Down;
        else
            return cDirType_Up;
    }
    else
    {
        return cDirType_Up;
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

    if ((flag & 0x10) && calcTottenToSrcDir_(visible_range) == cDirType_Right)
        return false;

    bool out = false;

    if (ActorCullUtil::areaCullCheck(visible_range, mAreaNo))
        out = true;
    else if (!(flag & 4) && ActorCullUtil::screenCullCheck(visible_range, mCullLimit))
        out = true;

    if (out && !(flag & 2))
        deleteActor(mManualDeletedFlag);

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
    if (mCollisionMask.isOn(cCcLineKind_0) && mLayer == cLayerID_Layer1)
    {
        const BgCollisionCheckParam param = {
            0,                              // _0
            false,                          // ignore_quicksand
            cLayerID_Layer1,                // layer
            sead::BitFlag8(                 // collision_mask
                cCcLineKind_0 |
                cCcLineKind_1
            ),
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

void Actor::deleteActor(bool manual_deleted)
{
    deleteRequest();
    if (_270 != nullptr && !manual_deleted)
        *_270 &= ~1;
}

u32 Actor::calcTottenToSrcDir_(const sead::BoundBox2f& src_range) const
{
    if (!MainGame::instance()->isStory() ||
        TottenMgr::instance() == nullptr ||
        TottenMgr::instance()->getTottenActor() == nullptr)
    {
        return cDirType_Left;
    }

    if (TottenMgr::instance()->getTottenActor()->getPos().x > src_range.getMax().x)
        return cDirType_Left;
    else
        return cDirType_Right;
}

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

Actor::Actor(const ActorCreateParam& param)
    : ActorBase(param)
    , mDirection(cDirType_Right)
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
    , mManualDeletedFlag(false)
    , _211(1)
    , mCarryFlag(cCarryFlag_None)
    , mSwitchFlag0(param.param_ex_0.course.switch_flag_0)
    , mSwitchFlag1(param.param_ex_0.course.switch_flag_1)
    , mCreateFlag(param.p_profile->getActorCreateInfo().flag)
    , mBumpDamageTimer(0)
    , mBumpDirection(cDirType_Right)
    , _220(0)
    , mCarryDirection(cDirType_Right)
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
    , mAddSpeedF(0.0f)
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

bool Actor::preExecute_()
{
    mPosPrev = mPosPrev2;

    if (!ActorBase::preExecute_())
        return false;

    if (!mIsExecEnable)
        return false;

    getPos2D() += mPosDelta;

    if (mBumpDamageTimer == 8)
    {
        SubjectMgr::instance()->onAcBlockHit();
        blockHitInit_();
    }

    if (mBumpDamageTimer > 0)
        mBumpDamageTimer--;

    return true;
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

bool Actor::preDraw_()
{
    if (!ActorBase::preDraw_())
        return false;

    if (!mIsDrawEnable)
        return false;

    if (mpEatData != nullptr && mpEatData->getState() == 2)
        return false;

    if (mpChibiYoshiEatData != nullptr && mpChibiYoshiEatData->getState() == 2)
        return false;

    if ((mProfFlag & Profile::cFlag_DrawCullCheck) && drawCullCheck_())
        return false;

    return true;
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
            ? *CourseTask::instance()->getGameData()
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
            ? *CourseTask::instance()->getGameData()
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

void Actor::carryFukidashiCancel_(s32 action, s32 player_no)
{
    for (s32 i = 0; i < 4; i++)
    {
        if (i == player_no)
        {
            FukidashiMgr::instance()->hide(i, action);
            FukidashiMgr::instance()->setComplete(i, action);
        }
        else
        {
            FukidashiMgr::instance()->hideTemp(i, action);
        }
    }

    mControllerLytPlayerNo = -1;
}

bool Actor::isEnablePressLR_(const ActorBgCollisionCheck& bc)
{
    if (bc.checkWall(cDirType_Right) && bc.checkWall(cDirType_Left))
    {
        if (!bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk24) &&
            !bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk31) &&
            !bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk30))
        {
            const BgCollision* p_bg_collision_r = bc.getHitBgCollisionWall(cDirType_Right);
            const BgCollision* p_bg_collision_l = bc.getHitBgCollisionWall(cDirType_Left);
            if (p_bg_collision_r == nullptr || p_bg_collision_l == nullptr ||
                (p_bg_collision_r != p_bg_collision_l && p_bg_collision_r->getOwner() != p_bg_collision_l->getOwner()))
            {
                if (canPress_(p_bg_collision_r) && canPress_(p_bg_collision_l))
                    if (checkPressLR_(bc, cDirType_Left) || checkPressLR_(bc, cDirType_Right))
                        return true;
            }
        }
    }
    return false;
}

bool Actor::isEnablePressUD_(const ActorBgCollisionCheck& bc)
{
    if (bc.checkFoot() && bc.checkHead())
    {
        if (!bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk14) &&
            !bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk17) &&
            !bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk5) &&
            !bc.getOutput().isOnBit(ActorBgCollisionCheck::Output::cBit_Unk9))
        {
            const BgCollision* p_bg_collision_d = bc.getHitBgCollisionFoot();
            const BgCollision* p_bg_collision_u = bc.getHitBgCollisionHead();
            if (p_bg_collision_d == nullptr || p_bg_collision_u == nullptr ||
                (p_bg_collision_d != p_bg_collision_u && p_bg_collision_d->getOwner() != p_bg_collision_u->getOwner()))
            {
                if (canPress_(p_bg_collision_u) && canPress_(p_bg_collision_d))
                    if (p_bg_collision_u == nullptr || p_bg_collision_u->getOwner() == nullptr || p_bg_collision_u->getOwner()->getProfileID() != ProfileInfo::cProfileID_IcicleBig)
                        if (BgUnitCode::getAttr(bc.getBgCheckData(cDirType_Down)) != BgUnitCode::cNuma)
                            if (checkPressD_(bc) || checkPressU_(bc))
                                return true;
            }
        }
    }
    return false;
}

bool Actor::canPress_(const BgCollision* p_bg_collision)
{
    if (p_bg_collision != nullptr)
    {
        if (p_bg_collision->isFlag(12) ||
            (p_bg_collision->isFlag(11) && p_bg_collision->getType() != BgCollision::cType_BreakableIce))
        {
            return false;
        }
    }
    return true;
}

bool Actor::checkPressLR_(const ActorBgCollisionCheck& bc, u32 direction)
{
    static const u32 c_hit_dir_bit[cDirType_NumX] = { ActorBgCollisionCheck::cHitDirBit_Right, ActorBgCollisionCheck::cHitDirBit_Left };
    static const f32 c_dir_sign[cDirType_NumX] = { 1.0f, -1.0f };
    static const u32 c_dir_type[cDirType_NumX] = { cDirType_Right, cDirType_Left };

    if (bc.isHit(1 << c_hit_dir_bit[direction])) // If has been actively hit on this specific frame
        return true;

    if (canPressIfApproaching_(bc.getHitBgCollisionWall(direction), bc.getHitBgCollisionWall(InvDirX(direction))))
    {
        for (s32 i = 0; i < cDirType_NumX; i++)
        {
            u32 direction = c_dir_type[i];
            const BgCollision* p_bg_collision = bc.getHitBgCollisionWall(direction);
            if (p_bg_collision != nullptr &&
                (p_bg_collision->getTypePos().x - p_bg_collision->getTypePosPrev().x) * c_dir_sign[direction] < 0.0f)
            {
                return true;
            }
        }
    }

    return false;
}

bool Actor::checkPressU_(const ActorBgCollisionCheck& bc)
{
    if (bc.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Up)) // If has been actively hit on this specific frame
        return true;

    if (canPressIfApproaching_(bc.getHitBgCollisionFoot(), bc.getHitBgCollisionHead()))
    {
        if (bc.getHitBgCollisionFoot() != nullptr && mPosDelta.y > 0.0f)
            return true;

        const BgCollision* p_bg_collision = bc.getHitBgCollisionHead();
        if (p_bg_collision != nullptr &&
            (p_bg_collision->getTypePos().y - p_bg_collision->getTypePosPrev().y) < 0.0f)
        {
            return true;
        }
    }

    return false;
}

bool Actor::checkPressD_(const ActorBgCollisionCheck& bc)
{
    if (bc.isHit(1 << ActorBgCollisionCheck::cHitDirBit_Down)) // If has been actively hit on this specific frame
        return true;

    if (canPressIfApproaching_(bc.getHitBgCollisionHead(), bc.getHitBgCollisionFoot()))
    {
        if (bc.getHitBgCollisionFoot() != nullptr && mPosDelta.y > 0.0f)
            return true;

        const BgCollision* p_bg_collision = bc.getHitBgCollisionHead();
        if (p_bg_collision != nullptr &&
            (p_bg_collision->getTypePos().y - p_bg_collision->getTypePosPrev().y) < 0.0f)
        {
            return true;
        }
    }

    return false;
}

bool Actor::canPressIfApproaching_(const BgCollision* p_bgcol_approaching_side, const BgCollision* p_bgcol_fixed_side)
{
    if (p_bgcol_fixed_side != nullptr)
    {
        BlockCoinBase* p_block = p_bgcol_fixed_side->getOwner<BlockCoinBase>(); // "const BlockCoinBase*" does not match, what a joke of a compiler
        if (p_block != nullptr && p_block->getMoveType() != BlockCoinBase::cMoveType_None)
            return false;
    }

    if (p_bgcol_approaching_side != nullptr && (p_bgcol_approaching_side->getType() == BgCollision::cType_BoostBlock || p_bgcol_approaching_side->getType() == BgCollision::cType_BreakableIce))
        return true;

    return false;
}

bool Actor::setPressBreakLR_(const ActorBgCollisionCheck& bc)
{
    const BgCollision* p_bg_collision_r = bc.getHitBgCollisionWall(cDirType_Right);
    const BgCollision* p_bg_collision_l = bc.getHitBgCollisionWall(cDirType_Left);

    if (setPressBreakIce_(p_bg_collision_l))
        return true;

    if (setPressBreakIce_(p_bg_collision_r))
        return true;

    if (setPressBreakBlockDRC_(p_bg_collision_l))
        return true;

    if (setPressBreakBlockDRC_(p_bg_collision_r))
        return true;

    return false;
}

bool Actor::setPressBreakUD_(const ActorBgCollisionCheck& bc)
{
    const BgCollision* p_bg_collision_d = bc.getHitBgCollisionFoot();
    const BgCollision* p_bg_collision_u = bc.getHitBgCollisionHead();

    if (setPressBreakIce_(p_bg_collision_u))
        return true;

    if (setPressBreakBlockDRC_(p_bg_collision_u))
        return true;

    if (setPressBreakIce_(p_bg_collision_d))
        return true;

    if (setPressBreakBlockDRC_(p_bg_collision_d))
        return true;

    return false;
}

bool Actor::setPressIceHeadBreak_(const ActorBgCollisionCheck& bc)
{
    if (!bc.checkFoot())
        return false;

    if (!(bc.checkWall(cDirType_Right) && bc.checkWall(cDirType_Left)))
        return false;

    Ice* p_ice_u = nullptr;

    const BgCollision* p_bg_collision_u = bc.getHitBgCollisionHead();
    if (p_bg_collision_u != nullptr)
        p_ice_u = p_bg_collision_u->getOwner<Ice>();

    if (p_ice_u == nullptr)
    {
        sead::Vector2f pos = mPos;

        const ActorBgCollisionCheck::Sensor* p_head_sensor;
        bool sensor_valid = false;
        if (bc.isSensor1Set(cDirType_Up))
        {
            if (!bc.isSensor1Null(cDirType_Up))
            {
                const ActorBgCollisionCheck::SensorArray& sensors = bc.getSensorArray1();
                p_head_sensor = &(sensors[cDirType_Up]);
                sensor_valid = true;
            }
        }
        else if (bc.isSensor2Set(cDirType_Up))
        {
            const ActorBgCollisionCheck::SensorArray& sensors = bc.getSensorArray2();
            p_head_sensor = &(sensors[cDirType_Up]);
            sensor_valid = true;
        }
        if (sensor_valid && p_head_sensor != nullptr)
        {
            sead::Vector2f center_offset;
            ActorBgCollisionCheckUtil::getHSensorCenterOffset(*p_head_sensor, center_offset);
            pos.x += center_offset.x;
            pos.y += center_offset.y * 0.75f;
        }

        BgCollisionCheckResultPoint res;
        BasicBgCollisionCheck bg_check;
        if (!bg_check.checkPointActor(&res, pos))
            return false;

        p_bg_collision_u = res.p_bg_collision;
        if (p_bg_collision_u == nullptr)
            return false;

        if (p_bg_collision_u->getType() != BgCollision::cType_BreakableIce)
            return false;

        p_ice_u = p_bg_collision_u->getOwner<Ice>();
    }

    Ice* p_ice_r = nullptr;

    const BgCollision* p_bg_collision_r = bc.getHitBgCollisionWall(cDirType_Right);
    if (p_bg_collision_r != nullptr)
        p_ice_r = p_bg_collision_r->getOwner<Ice>();

    Ice* p_ice_l = nullptr;

    const BgCollision* p_bg_collision_l = bc.getHitBgCollisionWall(cDirType_Left);
    if (p_bg_collision_l != nullptr)
        p_ice_l = p_bg_collision_l->getOwner<Ice>();

    if (p_ice_u == p_ice_r || p_ice_u == p_ice_l)
    {
        setPressBreakIce_(p_bg_collision_u);
        return true;
    }
    else
    {
        return false;
    }
}

bool Actor::setPressBreakIce_(const BgCollision* p_bg_collision)
{
    if (p_bg_collision != nullptr)
    {
        Actor* p_actor = p_bg_collision->getOwner();
        if (p_actor != nullptr)
        {
            if (p_actor->getProfileID() == ProfileInfo::cProfileID_PentaroIce)
            {
                static_cast<PentaroIce*>(p_actor)->breakReq(this);
                return true;
            }
            else if (p_actor->getProfileID() == ProfileInfo::cProfileID_PlyIce)
            {
                static_cast<PlyIce*>(p_actor)->breakReq();
                return true;
            }
            else
            {
                Ice* p_ice = sead::DynamicCast<Ice>(p_actor);
                if (p_ice != nullptr)
                {
                    p_ice->breakReq(*this);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Actor::setPressBreakBlockDRC_(const BgCollision* p_bg_collision)
{
    if (p_bg_collision != nullptr)
    {
        ActorBlockMakeDRC* p_block_drc = p_bg_collision->getOwner<ActorBlockMakeDRC>();
        if (p_block_drc != nullptr)
        {
            p_block_drc->destroy();
            return true;
        }
    }
    return false;
}
