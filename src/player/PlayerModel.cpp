#include <game/CourseTask.h>
#include <game_info/CourseInfo.h>
#include <graphics/AnimModel.h>
#include <graphics/ModelG3d.h>
#include <graphics/ModelResource.h>
#include <graphics/Renderer.h>
#include <player/MiiModel.h>
#include <player/PlayerHIO_Anm.h>
#include <player/PlayerHIO_General.h>
#include <player/PlayerObjectResData.h>
#include <utility/Direction.h>
#include <utility/MathUtil.h>
#include <utility/Mtx.h>

const Angle PlayerModel::cPropelRollBaseSpeed = 0x4000000; // 5.625 degrees

static const s32 cCarryDirBodyAnm[][cDirType_NumX] = {
    { PlayerAnmID::carry_waitR,       PlayerAnmID::carry_waitL },
    { PlayerAnmID::carryP_waitR,      PlayerAnmID::carryP_waitL },
    { PlayerAnmID::carry_shake_waitR, PlayerAnmID::carry_shake_waitL }
};
static_assert(sizeof(cCarryDirBodyAnm) / sizeof(s32) == 3 * cDirType_NumX);

static const PlayerModel::BodyType cPlayerModelData[] = {
    PlayerModel::cBodyType_Small,
    PlayerModel::cBodyType_Normal,
    PlayerModel::cBodyType_Normal,
    PlayerModel::cBodyType_Small,
    PlayerModel::cBodyType_Propeller,
    PlayerModel::cBodyType_Penguin,
    PlayerModel::cBodyType_Normal,
    PlayerModel::cBodyType_Squirrel,
    PlayerModel::cBodyType_Squirrel
};
static_assert(sizeof(cPlayerModelData) / sizeof(cPlayerModelData[0]) == cPlayerMode_Num);

static const sead::SafeString cJointNameTbl[] = {
    "mario_all_root",
    "skl_root",
    "leg_l1",
    "leg_l2",
    "ankle_l1",
    "leg_r1",
    "leg_r2",
    "ankle_r1",
    "spin",
    "arm_l1",
    "arm_l2",
    "wrist_l1",
    "arm_r1",
    "arm_r2",
    "wrist_r1",
    "CapPosition",
    "face_1",
    "wing_legL",
    "wing_legR",
    "wing_armL",
    "wing_armR",
    "wing",
    "wing_tail1",
    "wing_tail2"
};
static_assert(sizeof(cJointNameTbl) / sizeof(sead::SafeString) == PlayerModel::cJointID_Num);

static const PlayerModel::JointID cWingJointTbl[] = {
    PlayerModel::cJointID_WingLegL,
    PlayerModel::cJointID_WingLegR,
    PlayerModel::cJointID_WingArmL,
    PlayerModel::cJointID_WingArmR,
    PlayerModel::cJointID_Wing,
    PlayerModel::cJointID_WingTail1,
    PlayerModel::cJointID_WingTail2
};
static_assert(sizeof(cWingJointTbl) / sizeof(cWingJointTbl[0]) == PlayerModel::cJointID_NumWing);

const PlayerModel::TexAnmData PlayerModel::cTexAnmData[] = {
    { "PH_wait", FrameCtrl::cMode_Repeat, 0.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_goal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_PL_goal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_P_goal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_M_goal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_P_Rgoal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_M_Rgoal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_goal_puton_cap", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dam", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_jump", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_jumped", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_throw", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_courese_in", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_coin_comp", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_glad", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_glad2", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_glad2_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_glad3", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_glad3_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_glad4_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_sad", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_balloon_wait_disconnect", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_course_in", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_sad2", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "KH_dm_thanksgift", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_escort", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_escort_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_ending1", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f },
    { "PH_dm_ending1_wait", FrameCtrl::cMode_Repeat, 1.0f, 0.0f },
    { "PH_dm_ending2", FrameCtrl::cMode_NoRepeat, 1.0f, 0.0f }
};

static const sead::SafeString cDefaultTailAnm = "M_TAIL_wait";

static const sead::SafeString cLowWalkAnmName[] = {
    "low_walk_start",
    "low_walk",
    "carry_low_walk_start",
    "carry_low_walk"
};
static_assert(sizeof(cLowWalkAnmName) / sizeof(sead::SafeString) == 2 * 2);

static const sead::SafeString cLowWalkAnmName_Propeller[] = {
    "PL_low_walk_start",
    "PL_low_walk",
    "PL_carry_low_walk_start",
    "PL_carry_low_walk"
};
static_assert(sizeof(cLowWalkAnmName_Propeller) / sizeof(sead::SafeString) == 2 * 2);

static const sead::SafeString cLowWalkAnmName_Penguin[] = {
    "low_walk_start",
    "P_low_walk",
    "carry_low_walk_start",
    "P_carry_low_walk"
};
static_assert(sizeof(cLowWalkAnmName_Penguin) / sizeof(sead::SafeString) == 2 * 2);

static const sead::SafeString cLowWalkAnmName_Musa[] = {
    "low_walk_start",
    "M_low_walk",
    "M_carry_low_walk_start",
    "M_carry_low_walk"
};
static_assert(sizeof(cLowWalkAnmName_Musa) / sizeof(sead::SafeString) == 2 * 2);

static const sead::SafeString cEnvTexName[] = {
    "lm_02p",
    "star_env",
    "p_env"
};
static_assert(sizeof(cEnvTexName) / sizeof(sead::SafeString) == PlayerModel::cEnvType_Num);

static const sead::Matrix34f cMusaGlideLcarryFaceMtxRT(
     0.497535f, -0.866197f, -0.046491f, 7.697888f,
     0.834151f,  0.463046f,  0.299633f, 0.0f,
    -0.238013f, -0.187859f,  0.952921f, 0.0f
);
static const sead::Matrix34f cMusaGlideRcarryFaceMtxRT(
    0.497535f, -0.866197f,  0.046491f, 7.697888f,
    0.834151f,  0.463046f, -0.299633f, 0.0f,
    0.238013f,  0.187859f,  0.952921f, 0.0f
);

static const s32 cCarryBodyAnm[] = {
    PlayerAnmID::carry_wait,
    PlayerAnmID::carryP_wait,
    PlayerAnmID::carry_shake
};
static_assert(sizeof(cCarryBodyAnm) / sizeof(s32) == 3);

PlayerModel::PlayerModel(const PlayerObjectResHIO& res_hio, Type type, PlayerMode mode, SceneType scene_type, bool override_lightmap)
    : PlayerModelBase(res_hio.model_res_key, res_hio.anm_res_key)
    , mResHio(res_hio)
    , mpHeadModel(nullptr)
    , mOldBodyID()
    , mNowBodyID()
    , mModelLoadFlag()
    , mPlayerNo(0)
    , mCalcRatio(cJointID_Num)
    , mPlayerMode()
    , mPlayerModeOverride(mode)
    , mColorType()
    , mFaceAngle()
    , mFaceAngleTarget()
    , mFaceRotTimer(0)
    , mFaceRotFrameCnt(0)
    , mClampFaceRotTimer(false)
    , mPropelRollAngle()
    , mPropelRollSpeed(cPropelRollBaseSpeed)
    , mPropelScale(1.0f)
    , mAimMotionScale(1.0f)
    , mAimMotionScaleTarget(1.0f)
    , mAimMotionScaleBase(1.0f)
    , mDarkTargetType()
    , mDarkColorValue(0.0f)
    , mEnvTypeFlag()
    , mOverrideLightMap(override_lightmap)
{
    mModelArray.fill(nullptr);
    mHeadModelArray.fill(nullptr);

    mType = type;
    mSceneType = scene_type;

    setModelLoadFlag();

    if (mode == cPlayerMode_Invalid)
        mode = cPlayerMode_Small;
    mPlayerMode = mode;
}

void PlayerModel::setModelLoadFlag()
{
    if (mPlayerModeOverride == cPlayerMode_Invalid)
    {
        for (s32 i = 0; i < cPlayerMode_Num; i++)
            mModelLoadFlag.setBit(cPlayerModelData[i]);
    }
    else
    {
        mModelLoadFlag.setBit(cPlayerModelData[mPlayerModeOverride]);
    }
}

void PlayerModel::createPlayerModel(const sead::PtrArray<ModelResource>* p_anim_mdl_res_array)
{
    for (s32 i = 0; i < cBodyType_Num; i++)
    {
        if (mModelLoadFlag.isOnBit(i))
        {
            if (isCourseSelectScene())
                mModelArray[i] = AnimModel::create(
                    mpModelRes,
                    mResHio.body_mdl_name[i],
                    6,
                    cSklAnm_Num, cTexAnm_Num, cShuAnm_Num, 0, 0,
                    Model::cBoundingMode_Enable,
                    nullptr,
                    p_anim_mdl_res_array
                );
            else
                mModelArray[i] = AnimModel::create(
                    mpModelRes,
                    mResHio.body_mdl_name[i],
                    cSklAnm_Num, cTexAnm_Num, cShuAnm_Num, 0, 0,
                    Model::cBoundingMode_Disable,
                    nullptr,
                    p_anim_mdl_res_array
                );

            if (!mResHio.head_mdl_name[i].isEmpty())
            {
                if (isCourseSelectScene())
                    mHeadModelArray[i] = AnimModel::create(
                        mpModelRes,
                        mResHio.head_mdl_name[i],
                        6,
                        0, cTexAnm_Num, cShuAnm_Num, 0, 0,
                        Model::cBoundingMode_Enable,
                        nullptr,
                        p_anim_mdl_res_array
                    );
                else
                    mHeadModelArray[i] = AnimModel::create(
                        mpModelRes,
                        mResHio.head_mdl_name[i],
                        0, cTexAnm_Num, cShuAnm_Num, 0, 0,
                        Model::cBoundingMode_Disable,
                        nullptr,
                        p_anim_mdl_res_array
                    );
            }
        }
    }
}

f32 PlayerModel::getBaseScale()
{
    if (mPlayerMode == cPlayerMode_Mini)
        return 0.6f;
    return 1.0f;
}

void PlayerModel::setModelRenderPass(s32 idx_opa, s32 idx_xlu)
{
    for (s32 i = 0; i < cBodyType_Num; i++)
    {
        if (mModelLoadFlag.isOnBit(i))
        {
            mModelArray[i]->getModel()->setOpaRenderPass(idx_opa);
            mModelArray[i]->getModel()->setXluRenderPass(idx_xlu);
            if (mHeadModelArray[i])
            {
                mHeadModelArray[i]->getModel()->setOpaRenderPass(idx_opa);
                mHeadModelArray[i]->getModel()->setXluRenderPass(idx_xlu);
            }
        }
    }
}

void PlayerModel::setModelG3dRenderFlag(u32 flag)
{
    for (s32 i = 0; i < cBodyType_Num; i++)
    {
        if (mModelLoadFlag.isOnBit(i))
        {
            ModelG3d* p_body_model = sead::DynamicCast<ModelG3d>(mModelArray[i]->getModel());
            if (p_body_model)
                p_body_model->getRenderFlag().setDirect(flag);

            // They don't check if mHeadModelArray[i] is null first...
            ModelG3d* p_head_model = sead::DynamicCast<ModelG3d>(mHeadModelArray[i]->getModel());
            if (p_head_model)
                p_head_model->getRenderFlag().setDirect(flag);
        }
    }
}

void PlayerModel::setJointMap()
{
    Model* p_model = mpModel->getModel();
    for (s32 i = 0; i < cJointID_Num; i++)
        mJointMap[i] = p_model->searchBoneIndex(cJointNameTbl[i]);
}

PlayerModel::JointID PlayerModel::getJointID(const sead::SafeString& name) const
{
    for (s32 i = 0; i < cJointID_Num; i++)
    {
        if (name == cJointNameTbl[i])
            return static_cast<JointID>(i);
    }

    return cJointID_AllRoot;
}

void PlayerModel::getJointMtx(sead::Matrixf* p_mtx, const sead::SafeString& name)
{
    getJointMtx(p_mtx, getJointID(name));
}

void PlayerModel::setDark(DarkTargetType type, f32 value)
{
    if (mDarkTargetType != type || mDarkColorValue != value)
    {
        mDarkTargetType = type;
        mDarkColorValue = value;
        applyDark(type, value);
    }
}

void PlayerModel::applyDark(DarkTargetType type, f32 value)
{
    if (type == cDarkTargetType_InvTevColor0)
    {
        setInvTevColor0(value);
        setTevKColor3(0.0f);
    }
    else
    {
        setTevKColor3(value);
        setInvTevColor0(0.0f);
    }
}

void PlayerModel::setInvTevColor0(f32 value)
{
    f32 color_value = 1.0f - value;
    sead::Color4f color(color_value, color_value, color_value, color_value);
    if (mpHeadModel)
    {
        Model* p_head_model = mpHeadModel->getModel();
        if (p_head_model)
        {
            s32 material_num = p_head_model->getMaterialNum();
            for (s32 i = 0; i < material_num; i++)
            {
                Material* p_material = p_head_model->getMaterial(i);
                if (p_material)
                {
                    p_material->setTevColor(0, color);
                    sead::Color4f color_1;
                    p_material->getTevColor(1, color_1);
                    color_1.a = getTevColor0Alpha(i) * color_value;
                    p_material->setTevColor(1, color_1);
                }
            }
        }
    }
    Model* p_body_model = mpModel->getModel();
    if (p_body_model)
    {
        s32 material_num = p_body_model->getMaterialNum();
        for (s32 i = 0; i < material_num; i++)
        {
            Material* p_material = p_body_model->getMaterial(i);
            if (p_material)
                p_material->setTevColor(0, color);
        }
    }
}

void PlayerModel::setTevKColor3(f32 value)
{
    if (mpHeadModel)
    {
        Model* p_head_model = mpHeadModel->getModel();
        if (p_head_model)
        {
            s32 material_num = p_head_model->getMaterialNum();
            for (s32 i = 0; i < material_num; i++)
            {
                Material* p_material = p_head_model->getMaterial(i);
                if (p_material)
                {
                    sead::Color4f color;
                    p_material->getTevKColor(3, color);
                    color.r = value;
                    color.g = value;
                    color.b = value;
                    p_material->setTevKColor(3, color);
                }
            }
        }
    }
    Model* p_body_model = mpModel->getModel();
    if (p_body_model)
    {
        s32 material_num = p_body_model->getMaterialNum();
        for (s32 i = 0; i < material_num; i++)
        {
            Material* p_material = p_body_model->getMaterial(i);
            if (p_material)
            {
                sead::Color4f color;
                p_material->getTevKColor(3, color);
                color.r = value;
                color.g = value;
                color.b = value;
                p_material->setTevKColor(3, color);
            }
        }
    }
}

void PlayerModel::playBody()
{
    calcStoopOffset();
    mpModel->playAnmFrameCtrl();
    mCalcRatio.calc();
}

void PlayerModel::playHead()
{
    calcBlinkFrame();
    if (mpHeadModel)
        mpHeadModel->playAnmFrameCtrl();
    mPropelRollAngle -= mPropelRollSpeed;
}

void PlayerModel::calcBlinkFrame()
{
    if (mTexAnmType != cTexAnmType_Wait)
        return;

    MathUtil::calcTimer(&mDefaultExpressionTimer);
    if (mpHeadModel)
    {
        TexturePatternAnimation* p_tex_anm = mpHeadModel->getTexAnim(cTexAnm_Head);
        if (mDefaultExpressionTimer)
        {
            p_tex_anm->getFrameCtrl().setRate(0.0f);
            p_tex_anm->getFrameCtrl().reset();
        }
        else
        {
            p_tex_anm->getFrameCtrl().setRate(1.0f);
            if (p_tex_anm->getFrameCtrl().isLoopFrame() || p_tex_anm->getFrameCtrl().isStop())
                mDefaultExpressionTimer = rndInt(60) + 30;
        }
    }
}

void PlayerModel::calcBody()
{
    calcFaceAngle();

    calcBlendRate();

    Model* p_body_model = mpModel->getModel();
    p_body_model->setMtxRT(mMtxSrt); // Umm... I don't think this is right

    calcMusaWing();

    p_body_model->calcAnm();
    {
        // NSMBW: dPlayerMdl_c::nodeCallback_c::timingA (post animation apply to bone local matrix)

        calcFaceAngleOverride();
        calcJointLocalMtxPostAnm();
        mCalcRatio.applyTo(p_body_model);
    }

    p_body_model->calcMdl();

    calcHeadPos();
}

void PlayerModel::calcFaceAngle()
{
    bool clamp_timer_short = mClampFaceRotTimer;
    mClampFaceRotTimer = false;

    if (CourseInfo::instance()->isStaffCredit())
    {
        mFaceAngle.addCalcAngle(0, 0.5f, PlayerHIO_General::cFaceAngleRevertMaxStep, 0x100000);
        return;
    }

    MathUtil::calcTimer(&mFaceRotTimer);

    s32 target = 0;
    bool target_set = false;

    if (mFaceAngleOverrideFlag.isZero())
    {
        if (isRideCloudWait())
        {
            if (isWaitL())
            {
                target = PlayerHIO_General::cFaceAngleDefaultTargetCloud;
                target_set = true;
            }
            else if (isWaitR())
            {
                target = -PlayerHIO_General::cFaceAngleDefaultTargetCloud;
                target_set = true;
            }
        }
        else
        {
            if (isWaitL())
            {
                target = PlayerHIO_General::cFaceAngleDefaultTarget;
                target_set = true;
            }
            else if (isWaitR())
            {
                target = -PlayerHIO_General::cFaceAngleDefaultTarget;
                target_set = true;
            }
        }
    }

    if (!target_set)
    {
        mFaceRotFrameCnt = 0;
        mFaceRotTimer = PlayerHIO_General::cFaceAngleTurnTimeDefault;
        if (CourseTask::instance() && CourseTask::instance()->isMiniGame())
            mFaceRotTimer = PlayerHIO_General::cFaceAngleTurnTimeShort;
        mFaceRotTimer = sead::Mathi::clampMin(mFaceRotTimer + ((s32)rndInt(30) - 30), 0);
        if (mFlag.isOn(cFlag_Bit4))
            mFaceRotTimer += 40;
    }

    if (clamp_timer_short)
    {
        if (mFaceRotTimer > PlayerHIO_General::cFaceAngleTurnTimeShort)
            mFaceRotTimer = PlayerHIO_General::cFaceAngleTurnTimeShort;
    }

    mFaceAngleTarget = target;

    if (mFaceRotTimer || mFaceRotFrameCnt >= 60 || target == 0)
    {
        mFaceAngle.addCalcAngle(0, 0.5f, PlayerHIO_General::cFaceAngleRevertMaxStep, 0x100000);
        return;
    }

    mFaceAngle.addCalcAngle(mFaceAngleTarget, 0.5f, PlayerHIO_General::cFaceAngleMaxStep, 0x100000);

    if (isRideLiftWait() && mFaceRotFrameCnt < 60)
        mFaceRotFrameCnt++;
}

void PlayerModel::calcBlendRate()
{
    const f32 ratio = /* mCalcRatio.ratio() */ 1.0f; // NSMBU completely disables blending here...
    const f32 scale = getAimMotionShareScale();
    if (ratio == 1.0f) // Arrived at target
    {
        mAimMotionScale = scale;
        mAimMotionScaleTarget = scale;
        mAimMotionScaleBase = scale;
    }
    else
    {
        if (mAimMotionScaleTarget != scale)
        {
            mAimMotionScaleBase = mAimMotionScaleTarget;
            mAimMotionScaleTarget = scale;
        }
        mAimMotionScale = sead::Mathf::lerp(mAimMotionScaleBase, mAimMotionScaleTarget, ratio);
    }
}

void PlayerModel::calcMusaWing()
{
    // Called before any animations are applied

    if (mNowBodyID != cBodyType_Squirrel)
        return;

    s32 idx_model = mpModelRes->getResFile()->GetModelIndex(mResHio.body_mdl_name[mNowBodyID].cstr());
    nw::g3d::res::ResModel* p_res_model = mpModelRes->getResFile()->GetModel(idx_model);
    nw::g3d::res::ResSkeleton* p_res_skeleton = p_res_model->GetSkeleton();

    for (s32 i = 0; i < cJointID_NumWing; i++)
    {
        s32 idx_bone = mJointMap[cWingJointTbl[i]];
        if (idx_bone == -1)
            continue;

        nw::g3d::res::ResBone* p_res_bone = p_res_skeleton->GetBone(idx_bone);

        sead::Quatf quat(
            p_res_bone->GetRotateQuat().w,
            p_res_bone->GetRotateQuat().x,
            p_res_bone->GetRotateQuat().y,
            p_res_bone->GetRotateQuat().z
        );
        sead::Vector3f trans(
            p_res_bone->GetTranslate().x,
            p_res_bone->GetTranslate().y,
            p_res_bone->GetTranslate().z
        );
        sead::Vector3f scale(
            p_res_bone->GetScale().x,
            p_res_bone->GetScale().y,
            p_res_bone->GetScale().z
        );

        Model* p_model = mpModel->getModel();

        sead::Matrixf rt;
        rt.makeQT(quat, trans);

        p_model->setBoneLocalMatrix(idx_bone, rt, scale);
    }
}

void PlayerModel::calcFaceAngleOverride()
{
    // NSMBW: dPlayerMdl_c::nodeCallback_c::timingB (post bone world matrix calculation)
    // However, NSMBU transforms it to work in local space (timingA) instead

    s32 idx_bone_face = mJointMap[cJointID_Face1];
    // if (idx_bone_face == -1) // Checked in NSMBUDX, not in NSMBU
    //     return;

    Model* p_model = mpModel->getModel();

    Mtxf rt;
    sead::Vector3f scale;
    p_model->getBoneLocalMatrix(idx_bone_face, &rt, &scale);

    if (mPlayerMode == cPlayerMode_Squirrel || mPlayerMode == cPlayerMode_PSquirrel)
    {
        if (mAnm == PlayerAnmID::M_glideL_carry)
            static_cast<sead::Matrixf&>(rt) = cMusaGlideLcarryFaceMtxRT;
        else if (mAnm == PlayerAnmID::M_glideR_carry)
            static_cast<sead::Matrixf&>(rt) = cMusaGlideRcarryFaceMtxRT;
    }

    if (!mFaceAngleOverrideFlag.isZero())
    {
        if (mFaceAngleOverrideFlag.isOn(cFaceAngleOverrideFlag_Y))
            rt.YrotM(mFaceAngleOverride.y());

        if (mFaceAngleOverrideFlag.isOn(cFaceAngleOverrideFlag_Z))
            rt.ZrotM(mFaceAngleOverride.z());
    }

    p_model->setBoneLocalMatrix(idx_bone_face, rt, scale);
}

void PlayerModel::calcJointLocalMtxPostAnm()
{
    // NSMBW: dPlayerMdl_c::callbackTimingA

    Model* p_model = mpModel->getModel();

    s32 num_bone = p_model->getBoneNum();
    for (s32 idx_bone = 0; idx_bone < num_bone; idx_bone++)
    {
        sead::Matrixf rt;
        sead::Vector3f scale;
        p_model->getBoneLocalMatrix(idx_bone, &rt, &scale);

        if (idx_bone == mJointMap[cJointID_SklRoot])
        {
            sead::Vector3f trans;
            rt.getTranslation(trans);
            trans *= mAimMotionScale;
            rt.setTranslation(trans);
        }
        else
        {
            // NSMBW would reset the translation back to the resource value, but NSMBU no longer does that:
            // s32 idx_model = mpModelRes->getResFile()->GetModelIndex(mResHio.body_mdl_name[mNowBodyID].cstr());
            // nw::g3d::res::ResModel* p_res_model = mpModelRes->getResFile()->GetModel(idx_model);
            // nw::g3d::res::ResSkeleton* p_res_skeleton = p_res_model->GetSkeleton();
            // nw::g3d::res::ResBone* p_res_bone = p_res_skeleton->GetBone(idx_bone);
            // sead::Vector3f trans(
            //     p_res_bone->GetTranslate().x,
            //     p_res_bone->GetTranslate().y,
            //     p_res_bone->GetTranslate().z
            // );
            // rt.setTranslation(trans);

            if (
                (idx_bone == mJointMap[cJointID_WristL1] || idx_bone == mJointMap[cJointID_WristR1]) &&
                mNowBodyID == cBodyType_Penguin &&
                !isPenguinPersonalBodyAnm()
            )
            {
                sead::Vector3f trans;
                rt.getTranslation(trans);

                s32 idx_model = mpModelRes->getResFile()->GetModelIndex(mResHio.body_mdl_name[mNowBodyID].cstr());
                nw::g3d::res::ResModel* p_res_model = mpModelRes->getResFile()->GetModel(idx_model);
                nw::g3d::res::ResSkeleton* p_res_skeleton = p_res_model->GetSkeleton();
                nw::g3d::res::ResBone* p_res_bone = p_res_skeleton->GetBone(idx_bone);

                sead::Quatf quat(
                    p_res_bone->GetRotateQuat().w,
                    p_res_bone->GetRotateQuat().x,
                    p_res_bone->GetRotateQuat().y,
                    p_res_bone->GetRotateQuat().z
                );
                rt.makeQT(quat, trans);

                // NSMBW would reset the scale back to the resource value:
                // scale.set(
                //     p_res_bone->GetScale().x,
                //     p_res_bone->GetScale().y,
                //     p_res_bone->GetScale().z
                // );
                // Instead, NSMBU hardcodes it to 1.0:
                scale.set(1.0f, 1.0f, 1.0f);
            }

            p_model->setBoneLocalMatrix(idx_bone, rt, scale);
        }
    }
}

void PlayerModel::calcHeadPos()
{
    sead::Matrixf mtx;
    getJointMtx(&mtx, "face_1");

    sead::Vector3f bone_pos;
    mtx.getTranslation(bone_pos);

    sead::Vector3f model_pos;
    mMtxSrt.getTranslation(model_pos);

    mHeadPos.set(
        model_pos.x,
        bone_pos.y,
        bone_pos.z
    );

    mtx.multTranslationLocal(sead::Vector3f(0.0f, -mResHio.head_top_offs[mNowBodyID], 0.0f));
    mtx.getTranslation(mHeadTopPos);
}

void PlayerModel::calcHead()
{
    if (!mpHeadModel)
        return;

    Model* p_head_model = mpHeadModel->getModel();

    {
        sead::Matrixf mtx;
        getFaceMtx(&mtx);
        p_head_model->setMtxRT(mtx);
    }

    p_head_model->calcAnm();

    p_head_model->calcMdl();
    if (mNowBodyID == cBodyType_Propeller)
    {
        // NSMBW: dPlayerMdl_c::nodeCallbackPLH_c::timingB (post bone world matrix calculation)

        const s32 bone_index_player_plp = 1; // Hardcoded bone index... (changed to virtual func in NSMBUDX)

        Mtxf propel_mtx;
        p_head_model->getBoneWorldMatrix(bone_index_player_plp, &propel_mtx);

        propel_mtx.YrotM(mPropelRollAngle);
        propel_mtx.multScaleLocal(sead::Vector3f(mPropelScale, mPropelScale, mPropelScale));

        p_head_model->setBoneWorldMatrix(bone_index_player_plp, propel_mtx);
    }
}

void PlayerModel::getFaceMtx(sead::Matrixf* p_mtx)
{
    Mtxf& mtx = *static_cast<Mtxf*>(p_mtx);
    getJointMtx(&mtx, "face_1");

    mtx.ZrotM(MathUtil::absAngle(mFaceAngle) * PlayerHIO_General::cFaceAngleYtoZRatio);
    mtx.XrotM(MathUtil::absAngle(mFaceAngle) * PlayerHIO_General::cFaceAngleYtoXRatio);
    mtx.YrotM(mFaceAngle);
}

void PlayerModel::calc2Impl()
{
}

void PlayerModel::draw()
{
    PlayerModelBase::draw();
    if (mpHeadModel)
        Renderer::instance()->drawModel(mpHeadModel->getModel());
}

void PlayerModel::setPlayerModel(PlayerMode mode)
{
    mPlayerMode = mode;
    setBodyID(cPlayerModelData[mode]);
    mpModel = mModelArray[mNowBodyID];
    mpHeadModel = mHeadModelArray[mNowBodyID];
    setJointMap();
}

void PlayerModel::setPlayerMode(PlayerMode mode)
{
    if (mPlayerModeOverride != cPlayerMode_Invalid)
        mode = mPlayerModeOverride;
    setPlayerModel(mode);
    copyAnm();
    calcBlendRate();
    mColorType = cColorType_Invalid;
    switch (mPlayerMode)
    {
    default:
        setColorType(cColorType_Normal, false);
        break;
    case cPlayerMode_Fire:
        setColorType(cColorType_Fire, false);
        break;
    case cPlayerMode_Ice:
        setColorType(cColorType_Ice, false);
        break;
    }
    onPMusaChange();
    resetTexAnmType();
    resetTevColor0Alpha();
    applyDark(mDarkTargetType, mDarkColorValue);
    calcImpl();
}

void PlayerModel::copyAnm()
{
    SkeletalAnimation* p_skl_anm = mModelArray[mOldBodyID]->getSklAnim(cSklAnm_Main);
    if (mRideAnm != PlayerAnmID::cInvalid)
    {
        s32 prev_anm = mRideAnm;
        mRideAnm = PlayerAnmID::cInvalid;
        setRideAnm(prev_anm, p_skl_anm->getFrameCtrl().getRate(), 0.0f, p_skl_anm->getFrameCtrl().getFrame());
    }
    else
    {
        s32 prev_anm = mAnm;
        if (prev_anm == PlayerAnmID::cInvalid)
            prev_anm = PlayerAnmID::wait;
        mAnm = PlayerAnmID::cInvalid;
        setAnm(prev_anm, p_skl_anm->getFrameCtrl().getRate(), 0.0f, p_skl_anm->getFrameCtrl().getFrame());
    }
    if (isStarAnm())
    {
        removeStarAnm_OldBodyID();
        setStarAnm();
    }
}

void PlayerModel::resetTexAnmType()
{
    TexAnmType prev_tex_anm_type = mTexAnmType;
    if (prev_tex_anm_type == cTexAnmType_WaitStatic)
    {
        //setInitTexAnm();
    }
    else
    {
        mTexAnmType = cTexAnmType_WaitStatic;
        setTexAnmType(prev_tex_anm_type);
    }
}

void PlayerModel::resetTevColor0Alpha()
{
    if (!mpHeadModel)
        return;

    Model* p_head_model = mpHeadModel->getModel();
    if (!p_head_model)
        return;

    s32 material_num = p_head_model->getMaterialNum();
    for (s32 i = 0; i < material_num; i++)
    {
        Material* p_material = p_head_model->getMaterial(i);
        if (p_material)
        {
            sead::Color4f color;
            p_material->getTevColor(0, color);
            setTevColor0Alpha(i, color.a);
        }
    }
}

void PlayerModel::setBodyID(BodyType id)
{
    mOldBodyID = mNowBodyID;
    mNowBodyID = id;
}

void PlayerModel::onPMusaChange()
{
    mEnvTypeFlag.change(cEnvTypeFlag_P, mPlayerMode == cPlayerMode_PSquirrel);
    changeLightTexture(*mpModel);
    // if (mpHeadModel) // They do not check this in NSMBU, but they do in NSMBUDX
        changeLightTexture(*mpHeadModel);
}

void PlayerModel::changeLightTexture(AnimModel& anim_model)
{
    ModelG3d* p_model = sead::DynamicCast<ModelG3d>(anim_model.getModel());
    if (!p_model)
        return;

    agl::g3d::ModelEx* p_model_ex = p_model->getModelEx();
    if (!p_model_ex)
        return;

    nw::g3d::res::ResModel* p_res_model = p_model_ex->GetResource();
    if (!p_res_model)
        return;

    EnvType type = getEnvType();

    nw::g3d::res::ResMaterial* p_res_material = p_res_model->GetMaterial(0); // Find texture based on material 0
    if (p_res_material)
    {
        u32 num_sampler = p_res_material->GetSamplerCount();
        for (u32 i_sampler = 0; i_sampler < num_sampler; i_sampler++)
        {
            nw::g3d::res::ResTextureRef* p_res_tex_ref = p_res_material->GetTextureRef(i_sampler);
            bool match = false;
            if (p_res_tex_ref)
            {
                sead::SafeString tex_name = p_res_tex_ref->GetName();
                if (tex_name == cEnvTexName[type])
                    match = true;
            }
            if (match)
            {
                u32 num_material = p_model_ex->GetMaterialCount();
                nw::g3d::res::ResTexture* p_res_tex = p_res_tex_ref->Get();
                for (u32 i_material = 0; i_material < num_material; i_material++)
                {
                    nw::g3d::MaterialObj* p_material_obj = p_model_ex->GetMaterial(i_material);
                    p_material_obj->SetResTexture(2, p_res_tex); // Great... Hardcoded texture index
                                                                 // In other words, player models are NOT allowed
                                                                 // to have any materials that do not at least use
                                                                 // the specular light map... (same in NSMBUDX)
                }
                break;
            }
        }
    }

    LightMapMgr::instance()->setOverrideModelLightMap(mOverrideLightMap);
    LightMapMgr::instance()->setModelLightMap(p_model, true);
    LightMapMgr::instance()->setOverrideModelLightMap(true);
}

void PlayerModel::setStarAnm()
{
    mEnvTypeFlag.set(cEnvTypeFlag_Star);
    changeLightTexture(*mpModel);
    // if (mpHeadModel) // They do not check this in NSMBU, but they do in NSMBUDX
        changeLightTexture(*mpHeadModel);

    setStarAnm(mpModel, mpAnmRes, "PB_star_color", 0.0f);
    setStarAnm(mpHeadModel, mpAnmRes, "PH_star_color", 0.0f);
}

void PlayerModel::setStarAnm(AnimModel* p_anim_model, const ModelResource* p_mdl_res, const sead::SafeString& name, f32 frame)
{
    if (!p_anim_model)
        return;

    ShaderParamAnimation* p_color_anm = p_anim_model->getShuAnim(cShuAnm_Color_Star);
    p_color_anm->playColorAnim(p_mdl_res, name);
    p_color_anm->getFrameCtrl().setPlayMode(FrameCtrl::cMode_Repeat);
    p_color_anm->getFrameCtrl().setFrame(frame);
}

void PlayerModel::removeStarAnm_NowBodyID()
{
    removeStarAnm(mpHeadModel, mpModel);
}

void PlayerModel::removeStarAnm(AnimModel* p_head_anim_model, AnimModel* p_body_anim_model)
{
    mEnvTypeFlag.reset(cEnvTypeFlag_Star);
    if (p_head_anim_model)
        changeLightTexture(*p_head_anim_model);
    if (p_body_anim_model)
        changeLightTexture(*p_body_anim_model);

    if (p_head_anim_model)
        removeStarAnm(p_head_anim_model);
    if (p_body_anim_model)
        removeStarAnm(p_body_anim_model);

    // if (mpHeadModel) // They do not check this in NSMBU, but they do in NSMBUDX
        resetTevKColor3Alpha(mpHeadModel->getModel());
}

void PlayerModel::removeStarAnm_OldBodyID()
{
    removeStarAnm(mHeadModelArray[mOldBodyID], mModelArray[mOldBodyID]);
}

void PlayerModel::removeStarAnm(AnimModel* p_anim_model)
{
    if (!p_anim_model)
        return;

    static const sead::Color4f c_def_tev_color_0(1.0f, 1.0f, 1.0f, 1.0f);
    static const sead::Color4f c_def_k_color_3(0.0f, 0.0f, 0.0f, 0.328f);

    s32 material_num = p_anim_model->getModel()->getMaterialNum();
    for (s32 i = 0; i < material_num; i++)
    {
        Material* p_material = p_anim_model->getModel()->getMaterial(i);
        p_material->setTevColor(0, c_def_tev_color_0);
        p_material->setTevKColor(3, c_def_k_color_3);
    }

    ShaderParamAnimation* p_color_anm = p_anim_model->getShuAnim(cShuAnm_Color_Star);
    p_color_anm->unbind();
}

void PlayerModel::resetTevKColor3Alpha(Model* p_model)
{
    if (!p_model)
        return;

    Material* p_material = p_model->getMaterial(0);
    if (!p_material)
        return;

    sead::Color4f color;
    p_material->getTevKColor(3, color);
    if (mPlayerMode == cPlayerMode_PSquirrel)
        color.a = 1.0f;
    else
        color.a = 0.0f;
    p_material->setTevKColor(3, color);
}

void PlayerModel::onStarAnm()
{
    if (!isStarAnm())
    {
        PlayerModelBase::onStarAnm();
        setStarAnm();
    }
}

void PlayerModel::offStarAnm()
{
    if (isStarAnm())
    {
        PlayerModelBase::offStarAnm();
        removeStarAnm_NowBodyID();
    }
}

PlayerModel::EnvType PlayerModel::getEnvType() const
{
    // Star takes priority over P effect

    if (mEnvTypeFlag.isOn(cEnvTypeFlag_Star))
        return cEnvType_Star;

    if (mEnvTypeFlag.isOn(cEnvTypeFlag_P))
        return cEnvType_P;

    return cEnvType_Normal;
}

bool PlayerModel::checkChange_MusaPtoNml()
{
    ShaderParamAnimation* p_shu_anm = mpModel->getShuAnim(cShuAnm_Color_PtoNml);
    if (mPlayerMode != cPlayerMode_PSquirrel && mPlayerMode != cPlayerMode_Squirrel)
        return true;
    if (p_shu_anm->getFrameCtrl().checkFrame(30.0f))
    {
        setPlayerModel(cPlayerMode_Squirrel);
        mColorType = cColorType_Invalid;
        setColorType(cColorType_Normal, true);
        onPMusaChange();
    }
    if (p_shu_anm->getFrameCtrl().isStop())
    {
        mpHeadModel->getShuAnim(cShuAnm_Color_PtoNml)->unbind();
        mpModel->getShuAnim(cShuAnm_Color_PtoNml)->unbind();
        return true;
    }
    return false;
}

void PlayerModel::setHeadTexAnm_(AnimModel& head_anim_model, const TexAnmData& tex_anm_data)
{
    TexturePatternAnimation* p_tex_anm = head_anim_model.getTexAnim(cTexAnm_Head);
    p_tex_anm->play(mpModelRes, tex_anm_data.name);
    p_tex_anm->getFrameCtrl().setPlayMode(tex_anm_data.play_mode);
    p_tex_anm->getFrameCtrl().setRate(tex_anm_data.rate);
    // p_tex_anm->getFrameCtrl().setFrame(tex_anm_data.frame); // <-- Nintendo forgot to do this
}

void PlayerModel::setHeadTexAnm(TexAnmType type)
{
    if (mpHeadModel)
        setHeadTexAnm_(*mpHeadModel, getTexAnmData(type));
}

const PlayerModel::TexAnmData& PlayerModel::getTexAnmData(TexAnmType type) const
{
    static_assert(sizeof(cTexAnmData) / sizeof(TexAnmData) == cTexAnmType_Num);
    return cTexAnmData[type];
}

void PlayerModel::postChange_MusaPtoNml()
{
    if (mpHeadModel)
    {
        TexturePatternAnimation* p_tex_anm = mpHeadModel->getTexAnim(cTexAnm_Head);
        p_tex_anm->getFrameCtrl().setFrame(p_tex_anm->getFrameCtrl().getFrameEnd() - 1);
    }
}

void PlayerModel::setTexAnmType(TexAnmType type)
{
    if (mTexAnmType == type)
        return;

    mTexAnmType = type;
    setTexAnmTypeImpl(type);
    if (mTexAnmType == cTexAnmType_WaitStatic)
        mDefaultExpressionTimer = 0;
}

bool PlayerModel::setPersonalAnm(ModelResource** pp_anm_res, sead::BufferedSafeString* p_anm_name, s32 anm_id, bool body)
{
    if (getJumpAnmName(p_anm_name, anm_id, body))
        return true;

    if (getLowWalkAnmName(p_anm_name, anm_id, body))
        return true;

    if (mNowBodyID == cBodyType_Penguin)
    {
        if (!PlayerHIO_Anm::cData[anm_id].penguin.isEmpty())
        {
            p_anm_name->copy(PlayerHIO_Anm::cData[anm_id].penguin);
            if (!body)
                mAnmFlag[cAnmFlagType_Main] |= 1 << cAnmFlagBit_Personal_Penguin;
            mAnmFlag[cAnmFlagType_Body] |= 1 << cAnmFlagBit_Personal_Penguin;
            return true;
        }
    }
    else if (mNowBodyID == cBodyType_Squirrel)
    {
        bool personal_anm_set;
        switch (anm_id)
        {
        case PlayerAnmID::stoop:
            p_anm_name->copy("M_stoop");
            personal_anm_set = true;
            break;
        case PlayerAnmID::stoop_start:
            p_anm_name->copy("M_stoop_start");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjump:
            p_anm_name->copy("M_Sjump");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjump2:
            p_anm_name->copy("M_Sjump2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjumped:
            p_anm_name->copy("M_Sjumped");
            personal_anm_set = true;
            break;
        case PlayerAnmID::net_wait:
            p_anm_name->copy("M_net_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::net_walk1:
            p_anm_name->copy("M_net_walk1");
            personal_anm_set = true;
            break;
        case PlayerAnmID::net_walk2:
            p_anm_name->copy("M_net_walk2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::net_attack:
            p_anm_name->copy("M_net_attack");
            personal_anm_set = true;
            break;
        case PlayerAnmID::slip:
            p_anm_name->copy("M_slip");
            personal_anm_set = true;
            break;
        case PlayerAnmID::sliped:
            p_anm_name->copy("M_sliped");
            personal_anm_set = true;
            break;
        case PlayerAnmID::slip_to_stoop:
            p_anm_name->copy("M_slip_to_stoop");
            personal_anm_set = true;
            break;
        case PlayerAnmID::pea_plant:
            p_anm_name->copy("M_pea_plant");
            personal_anm_set = true;
            break;
        case PlayerAnmID::pea_plant_st:
            p_anm_name->copy("M_pea_plant_st");
            personal_anm_set = true;
            break;
        case PlayerAnmID::pea_plant_wait:
            p_anm_name->copy("M_pea_plant_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::tree_start:
            p_anm_name->copy("M_tree_start");
            personal_anm_set = true;
            break;
        case PlayerAnmID::tree_wait:
            p_anm_name->copy("M_tree_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::tree_climb:
            p_anm_name->copy("M_tree_climb");
            personal_anm_set = true;
            break;
        case PlayerAnmID::tree_pose:
            p_anm_name->copy("M_tree_pose");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hang_start:
            p_anm_name->copy("M_hang_start");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hang_up:
            p_anm_name->copy("M_hang_up");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hang_wait:
            p_anm_name->copy("M_hang_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hang_walk_l:
            p_anm_name->copy("M_hang_walk_l");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hang_walk_r:
            p_anm_name->copy("M_hang_walk_r");
            personal_anm_set = true;
            break;
        case PlayerAnmID::jump_hang:
            p_anm_name->copy("M_jump_hang");
            personal_anm_set = true;
            break;
        case PlayerAnmID::swim_wait:
            p_anm_name->copy("M_swim_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::swim_walk:
            p_anm_name->copy("M_swim_walk");
            personal_anm_set = true;
            break;
        case PlayerAnmID::swim_standing:
            p_anm_name->copy("M_swim_standing");
            personal_anm_set = true;
            break;
        case PlayerAnmID::paddle_1:
            p_anm_name->copy("M_paddle_1");
            personal_anm_set = true;
            break;
        case PlayerAnmID::paddle_2:
            p_anm_name->copy("M_paddle_2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carry_walk:
            p_anm_name->copy("M_carry_walk");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carry_throw:
            p_anm_name->copy("M_carry_throw");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carry_wait:
            p_anm_name->copy("M_carry_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carry_waitL:
            p_anm_name->copy("M_carry_waitL");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carry_waitR:
            p_anm_name->copy("M_carry_waitR");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_start:
            p_anm_name->copy("M_carryP_start");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_walk:
            p_anm_name->copy("M_carryP_walk");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_throw:
            p_anm_name->copy("M_carryP_throw");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_wait:
            p_anm_name->copy("M_carryP_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_waitL:
            p_anm_name->copy("M_carryP_waitL");
            personal_anm_set = true;
            break;
        case PlayerAnmID::carryP_waitR:
            p_anm_name->copy("M_carryP_waitR");
            personal_anm_set = true;
            break;
        case PlayerAnmID::hip_to_stoop:
            p_anm_name->copy("M_hip_to_stoop");
            personal_anm_set = true;
            break;
        default:
            personal_anm_set = false;
        }
        if (personal_anm_set)
        {
            if (!body)
                mAnmFlag[cAnmFlagType_Main] |= 1 << cAnmFlagBit_Personal_Musa;
            mAnmFlag[cAnmFlagType_Body] |= 1 << cAnmFlagBit_Personal_Musa;
            return true;
        }
    }

    return false;
}

bool PlayerModel::getLowWalkAnmName(sead::BufferedSafeString* p_anm_name, s32 anm_id, bool body)
{
    if (anm_id == PlayerAnmID::low_walk_start || anm_id == PlayerAnmID::low_walk)
    {
        s32 name_index = 0 * 2 + 0;
        if (anm_id == PlayerAnmID::low_walk)
        {
            name_index = 0 * 2 + 1;
            if (isCarry())
                name_index = 1 * 2 + 1;
        }
        else
        {
            if (isCarry())
                name_index = 1 * 2 + 0;
        }
        u32 personal_anm_flag;
        switch (mNowBodyID)
        {
        case cBodyType_Penguin:
            p_anm_name->copy(cLowWalkAnmName_Penguin[name_index]);
            personal_anm_flag = 1 << cAnmFlagBit_Personal_Penguin;
            break;
        case cBodyType_Propeller:
            p_anm_name->copy(cLowWalkAnmName_Propeller[name_index]);
            personal_anm_flag = 1 << cAnmFlagBit_Personal_Propeller;
            break;
        case cBodyType_Squirrel:
            p_anm_name->copy(cLowWalkAnmName_Musa[name_index]);
            personal_anm_flag = 1 << cAnmFlagBit_Personal_Musa;
            break;
        default:
            if (sead::DynamicCast<MiiModel>(this))
                p_anm_name->copy(cLowWalkAnmName_Propeller[name_index]);
            else
                p_anm_name->copy(cLowWalkAnmName[name_index]);
            personal_anm_flag = 0;
        }
        if (personal_anm_flag != 0)
        {
            if (!body)
                mAnmFlag[cAnmFlagType_Main] |= personal_anm_flag;
            mAnmFlag[cAnmFlagType_Body] |= personal_anm_flag;
        }
        if (isCarry())
        {
            if (!body)
                mAnmFlag[cAnmFlagType_Main] |= 1 << cAnmFlagBit_Carry;
            mAnmFlag[cAnmFlagType_Body] |= 1 << cAnmFlagBit_Carry;
        }
        return true;
    }
    return false;
}

bool PlayerModel::setPersonalRideAnm(ModelResource** pp_anm_res, sead::BufferedSafeString* p_anm_name, s32 anm_id)
{
    if (mNowBodyID == cBodyType_Penguin)
    {
        bool personal_anm_set;
        switch (anm_id)
        {
        case PlayerAnmID::hip_to_stoop:
            p_anm_name->copy("P_Rhip_to_stoop");
            personal_anm_set = true;
            break;
        case PlayerAnmID::stoop:
            p_anm_name->copy("P_Rstoop");
            personal_anm_set = true;
            break;
        case PlayerAnmID::stoop_start:
            p_anm_name->copy("P_Rstoop_start");
            personal_anm_set = true;
            break;
        case PlayerAnmID::slip_to_stoop:
            p_anm_name->copy("P_Rslip_to_stoop");
            personal_anm_set = true;
            break;
        case PlayerAnmID::RSeat:
            p_anm_name->copy("P_RSeat");
            personal_anm_set = true;
            break;
        case PlayerAnmID::RSeat_out:
            p_anm_name->copy("P_RSeat_out");
            personal_anm_set = true;
            break;
        case PlayerAnmID::RSeat_success:
            p_anm_name->copy("P_RSeat_success");
            personal_anm_set = true;
            break;
        case PlayerAnmID::RSeat_fail:
            p_anm_name->copy("P_RSeat_fail");
            personal_anm_set = true;
            break;
        case PlayerAnmID::RSeat_successB:
            p_anm_name->copy("P_RSeat_successB");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjump:
            p_anm_name->copy("P_Rsjump");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjump2:
            p_anm_name->copy("P_RSjump2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::Sjumped:
            p_anm_name->copy("P_RSjumped");
            personal_anm_set = true;
            break;
        default:
            personal_anm_set = false;
        }
        if (personal_anm_set)
        {
            mAnmFlag[cAnmFlagType_Main] |= 1 << cAnmFlagBit_Personal_Penguin;
            mAnmFlag[cAnmFlagType_Body] |= 1 << cAnmFlagBit_Personal_Penguin;
            return true;
        }
    }
    return false;
}

void PlayerModel::setAnm(s32 anm_id, f32 rate, f32 blend_duration, f32 frame)
{
    if (mPlayerMode == cPlayerMode_Mini && anm_id == PlayerAnmID::jump2)
        return setAnm(PlayerAnmID::mame_jump2, rate, blend_duration, frame);

    return PlayerModelBase::setAnm(anm_id, rate, blend_duration, frame);
}

void PlayerModel::setFootAnmImpl(const ModelResource* p_anm_res, const sead::SafeString& anm_name, FrameCtrl::PlayMode mode, f32 rate, f32 frame, f32 blend_duration)
{
    SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(cSklAnm_Main);
    p_skl_anm->play(p_anm_res, anm_name);
    p_skl_anm->getFrameCtrl().setPlayMode(mode);
    p_skl_anm->getFrameCtrl().setRate(rate);
    if (p_skl_anm->getFrameCtrl().getFrameEnd() - frame < 0.0f)
        frame = 0.0f;
    p_skl_anm->getFrameCtrl().setFrame(frame);
    if (isMusaPersonalAnm())
        setTailAnm(p_anm_res, anm_name, mode, rate, frame);
    else
        setTailAnm(p_anm_res, cDefaultTailAnm, mode, sead::Mathf::clampMin(1.0f, rate), frame);
    mCalcRatio.set(blend_duration);
    mStoopOffsetBlendFramesRemaining = blend_duration;
    mStoopOffsetTarget = getStoopOffsetTarget();
    calcStoopOffset();
}

void PlayerModel::setTailAnm(const ModelResource* p_anm_res, const sead::SafeString& anm_name, FrameCtrl::PlayMode mode, f32 rate, f32 frame)
{
    SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(cSklAnm_Tail);
    p_skl_anm->play(p_anm_res, anm_name);
    p_skl_anm->getFrameCtrl().setPlayMode(mode);
    p_skl_anm->getFrameCtrl().setRate(rate);
    if (p_skl_anm->getFrameCtrl().getFrameEnd() - frame < 0.0f)
        frame = 0.0f;
    p_skl_anm->getFrameCtrl().setFrame(frame);
}

void PlayerModel::setBodyAnmImpl(const ModelResource* p_anm_res, const sead::SafeString& anm_name, FrameCtrl::PlayMode mode, f32 rate, f32 frame, f32 blend_duration)
{
    mCarryStateChanged = false;

    SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(cSklAnm_Body);
    p_skl_anm->play(p_anm_res, anm_name);
    p_skl_anm->getFrameCtrl().setPlayMode(mode);
    p_skl_anm->getFrameCtrl().setRate(rate);
    if (p_skl_anm->getFrameCtrl().getFrameEnd() - frame < 0.0f)
        frame = 0.0f;
    p_skl_anm->getFrameCtrl().setFrame(frame);
    mCalcRatio.set(blend_duration);
}

bool PlayerModel::releaseMusaGlideCarryAnm(f32 blend_duration)
{
    if (mBodyAnm == PlayerAnmID::cInvalid &&
        (mAnm == PlayerAnmID::M_glideL_carry || mAnm == PlayerAnmID::M_glideR_carry))
    {
        s32 anm_id =
            mAnm == PlayerAnmID::M_glideL_carry
                ? PlayerAnmID::M_glideL
                : PlayerAnmID::M_glideR;
        setAnm(anm_id, getRate(), 0.0f, blend_duration); // Bug: Nintendo accidentally passes blend_duration as the frame instead
        return true;
    }
    return false;
}

void PlayerModel::releaseBodyAnm(f32 blend_duration)
{
    mCarryStateChanged = false;

    if (releaseMusaGlideCarryAnm(blend_duration))
        return;

    mBodyAnm = PlayerAnmID::cInvalid;

    const PlayerAnmData& anm_data = PlayerHIO_Anm::cData[mAnm];

    mAnmFlag[cAnmFlagType_Body] = anm_data.flag;

    ModelResource* p_anm_res = mpAnmRes;
    sead::FixedSafeString<32> anm_name(anm_data.normal);
    setPersonalAnm(&p_anm_res, &anm_name, mAnm, true);

    if (isCarry() && !isCarryBodyAnm())
        setCarryBodyAnm(blend_duration, false);
    else if (isSlopeBodyAnm())
        setSlopeBodyAnm(blend_duration);
    else
    {
        SkeletalAnimation* p_skl_anm = mpModel->getSklAnim(cSklAnm_Main);
        f32 frame = getFrame();
        const f32 frame_end = p_skl_anm->getFrameCtrl().getFrameEnd();
        if (frame >= frame_end)
            frame = frame_end - 1;
        setBodyAnmImpl(p_anm_res, anm_name, p_skl_anm->getFrameCtrl().getPlayMode(), getRate(), frame, blend_duration);
    }
}

void PlayerModel::setCarryBodyAnm(f32 blend_duration, bool bubble_reset_frame)
{
    s32 type = 0;
    if (isLiftUp())
        type = 1;
    if (isBubbleChibiYoshiShake())
        type = 2;

    f32 _rate = 1.0f;
    f32 _frame = 0.0;
    f32 _blend_duration = 0.0f;

    switch (type)
    {
    default:
        break;
    case 0:
        if (PlayerHIO_Anm::cData[mAnm].flag & 1 << cAnmFlagBit_Carry)
        {
            releaseBodyAnm(3.0f);
            return;
        }
        // fallthrough
    case 1:
        _rate = 1.2f;
        if (isDirAnm())
            _frame = getFrame();
        _blend_duration = blend_duration;
        break;
    case 2:
        if (!bubble_reset_frame)
            _frame = getBodyFrame();
        _blend_duration = blend_duration;
        break;
    }

    if (isDirAnm())
    {
        DirType dir = isDirAnmL() ? cDirType_Left : cDirType_Right;
        setBodyAnm(cCarryDirBodyAnm[type][dir], _rate, _frame, _blend_duration);
    }
    else
    {
        setBodyAnm(cCarryBodyAnm[type], _rate, _frame, _blend_duration);
    }
}

void PlayerModel::setAnmBind()
{
    /*
     * This function determines, for each bone in the skeleton, which animation
     * object (main, body, or tail) will control it by unbinding the others:
     * - The wing/tail bones are unbound from the body and main animations,
     *   leaving them controlled by the tail animation.
     * - The root, leg, ankle, and skeleton root bones are unbound from the
     *   body and tail animations, leaving them controlled by the main animation.
     * - The spine bone's control depends on the current state: if the player
     *   is shaking a Bubble Baby Yoshi and a specific animation flag
     *   is set, it's unbound from the body and tail animations, leaving it
     *   controlled by the main animation; otherwise, it's unbound from the main and
     *   tail animations, leaving it controlled by the body animation.
     * - All other bones are unbound from the main and tail animations, leaving them
     *   controlled by the body animation.
     *
     * The net effect is that different parts of the skeleton are driven by different
     * animation objects (main, body, or tail) depending on their role, allowing
     * independent blending of body poses, foot/leg movement, and tail/wing movement.
     */

    mpModel->getModel()->setSklAnimBlendWeight(cSklAnm_Body, 1.0f);
    mpModel->getModel()->setSklAnimBlendWeight(cSklAnm_Main, 1.0f);
    mpModel->getModel()->setSklAnimBlendWeight(cSklAnm_Tail, 1.0f);

    s32 num_bone = mpModel->getModel()->getBoneNum();

    SkeletalAnimation* p_skl_anm_body = mpModel->getSklAnim(cSklAnm_Body);
    SkeletalAnimation* p_skl_anm_main = mpModel->getSklAnim(cSklAnm_Main);
    SkeletalAnimation* p_skl_anm_tail = mpModel->getSklAnim(cSklAnm_Tail);

    for (s32 idx_bone = 0; idx_bone < num_bone; idx_bone++)
    {
        if (idx_bone == mJointMap[cJointID_WingTail1] ||
            idx_bone == mJointMap[cJointID_WingTail2])
        {
            p_skl_anm_body->unbindTarget(idx_bone);
            p_skl_anm_main->unbindTarget(idx_bone);
        }
        else if (
            idx_bone == mJointMap[cJointID_AllRoot] ||
            idx_bone == mJointMap[cJointID_LegL1] ||
            idx_bone == mJointMap[cJointID_LegL2] ||
            idx_bone == mJointMap[cJointID_AnkleL1] ||
            idx_bone == mJointMap[cJointID_WingLegL] ||
            idx_bone == mJointMap[cJointID_LegR1] ||
            idx_bone == mJointMap[cJointID_LegR2] ||
            idx_bone == mJointMap[cJointID_AnkleR1] ||
            idx_bone == mJointMap[cJointID_WingLegR] ||
            idx_bone == mJointMap[cJointID_SklRoot]
        )
        {
            p_skl_anm_body->unbindTarget(idx_bone);
            p_skl_anm_tail->unbindTarget(idx_bone);
        }
        else if (idx_bone == mJointMap[cJointID_Spin])
        {
            if (isBubbleChibiYoshiShake() && isAnmFlagBit(cAnmFlagBit_16))
            {
                p_skl_anm_body->unbindTarget(idx_bone);
                p_skl_anm_tail->unbindTarget(idx_bone);
            }
            else
            {
                p_skl_anm_main->unbindTarget(idx_bone);
                p_skl_anm_tail->unbindTarget(idx_bone);
            }
        }
        else
        {
            p_skl_anm_main->unbindTarget(idx_bone);
            p_skl_anm_tail->unbindTarget(idx_bone);
        }
    }
}

bool PlayerModel::isFaceRot()
{
    return mFaceAngle != 0;
}

void PlayerModel::setClampFaceRot()
{
    mClampFaceRotTimer = true;
}

bool PlayerModel::getHeadPropelJointMtx(sead::Matrixf* p_mtx)
{
    if (mNowBodyID == cBodyType_Propeller && mpHeadModel)
    {
        Model* p_head_model = mpHeadModel->getModel();
        const s32 bone_index_player_plp = 1; // Hardcoded bone index... (changed to virtual func in NSMBUDX)
        p_head_model->getBoneWorldMatrix(bone_index_player_plp, p_mtx);
        return true;
    }
    return false;
}
