#include <graphics/AnimModel.h>
#include <graphics/ModelG3d.h>
#include <graphics/Renderer.h>
#include <player/MarioModel.h>
#include <player/PlayerObjectResData.h>

static const PlayerObjectResHIO cArcDt[] = {
    {
        "MarioMdl",
        "CommonAnm",
        {
            "MB_model",
            "SMB_model",
            "PLMB_model",
            "PMB_model",
            "MMB_model"
        },
        {
            "MH_model",
            "SMH_model",
            "PLMH_model",
            "PMH_model",
            "MMH_model"
        },
        {
            13.0f,
            10.0f,
            13.0f,
            13.0f,
            13.0f
        }
    },
    {
        "LuigiMdl",
        "CommonAnm",
        {
            "LB_model",
            "SLB_model",
            "PLLB_model",
            "PLB_model",
            "MLB_model"
        },
        {
            "LH_model",
            "SLH_model",
            "PLLH_model",
            "PLH_model",
            "MLH_model"
        },
        {
            14.0f,
            11.0f,
            14.0f,
            14.0f,
            14.0f
        }
    }
};
static_assert(sizeof(cArcDt) / sizeof(PlayerObjectResHIO) == PlayerModelBase::cType_NumMario);

static const sead::SafeString cArcCapDt[][MarioModel::cBonusCap_Num] = {
    { "MC_model", "SMC_model" },
    { "LC_model", "SLC_model" }
};
static_assert(sizeof(cArcCapDt) / sizeof(sead::SafeString) == PlayerModelBase::cType_NumMario * MarioModel::cBonusCap_Num);

static const sead::SafeString cHeadSwitchAnm_Mario[] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MMH_model_switch"
};
static_assert(sizeof(cHeadSwitchAnm_Mario) / sizeof(sead::SafeString) == PlayerModel::cBodyType_Num);

static const sead::SafeString cBodySwitchAnm_Mario[] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MMB_model_switch"
};
static_assert(sizeof(cBodySwitchAnm_Mario) / sizeof(sead::SafeString) == PlayerModel::cBodyType_Num);

static const sead::SafeString cHeadSwitchAnm_Luigi[] = {
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "PH_switch",
    "MLH_model_switch"
};
static_assert(sizeof(cHeadSwitchAnm_Luigi) / sizeof(sead::SafeString) == PlayerModel::cBodyType_Num);

static const sead::SafeString cBodySwitchAnm_Luigi[] = {
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "PB_switch",
    "MLB_model_switch"
};
static_assert(sizeof(cBodySwitchAnm_Luigi) / sizeof(sead::SafeString) == PlayerModel::cBodyType_Num);

static const f32 cMarioHipScale_Default = 1.0f;
static const f32 cMarioHipScale_Small = 0.546f;
static const f32 cMarioHipScale_Penguin = 0.72f;

static const f32 cMarioHipScale[] = { cMarioHipScale_Default, cMarioHipScale_Small, cMarioHipScale_Default, cMarioHipScale_Penguin, cMarioHipScale_Default };
static_assert(sizeof(cMarioHipScale) / sizeof(f32) == PlayerModel::cBodyType_Num);

static const f32 cMarioHangCliffScale[] = { 0.0f, 0.0f, 0.0f, 0.55f, 0.0f };
static_assert(sizeof(cMarioHangCliffScale) / sizeof(f32) == PlayerModel::cBodyType_Num);

static const f32 cLuigiHipScale_Default = 1.15f;
static const f32 cLuigiHipScale_Small = 0.628f;     // Different from NSMBW
static const f32 cLuigiHipScale_Penguin = 0.81f;    // ^^^

static const f32 cLuigiHipScale[] = { cLuigiHipScale_Default, cLuigiHipScale_Small, cLuigiHipScale_Default, cLuigiHipScale_Penguin, cLuigiHipScale_Default };
static_assert(sizeof(cLuigiHipScale) / sizeof(f32) == PlayerModel::cBodyType_Num);

static const f32 cLuigiOrgHipScale_Default = 1.0f;
static const f32 cLuigiOrgHipScale_Small = 0.546f;      // Different from NSMBW
static const f32 cLuigiOrgHipScale_Penguin = 0.723f;    // ^^^

static const f32 cLuigiOrgHipScale[] = { cLuigiOrgHipScale_Default, cLuigiOrgHipScale_Small, cLuigiOrgHipScale_Default, cLuigiOrgHipScale_Penguin, cLuigiOrgHipScale_Default };
static_assert(sizeof(cLuigiOrgHipScale) / sizeof(f32) == PlayerModel::cBodyType_Num);

static const f32 cLuigiHangCliffScale[] = { -0.25f, -0.05f, -0.25f, 0.4f, -0.25f };
static_assert(sizeof(cLuigiHangCliffScale) / sizeof(f32) == PlayerModel::cBodyType_Num);

MarioModel::MarioModel(Type type, PlayerMode mode, SceneType scene_type, bool override_lightmap)
    : PlayerModel(cArcDt[type], type, mode, scene_type, override_lightmap)
    , mpLuigiAnmRes(ModelResourceMgr::instance()->getResource("LuigiAnm"))
    , mHeadID(cHeadType_Normal)
    , mBonusCapType(cBonusCap_Normal)
    , mIsBonusCap(false)
{
    // type must be < cType_NumMario

    LightMapMgr::instance()->setOverrideModelLightMap(mOverrideLightMap);

    sead::FixedPtrArray<ModelResource, 2> anm_res_array;
    anm_res_array.pushBack(mpAnmRes);
    anm_res_array.pushBack(mpLuigiAnmRes);

    createPlayerModel(&anm_res_array);

    for (s32 i = 0; i < cBonusCap_Num; i++)
    {
        if (isCourseSelectScene())
            mBonusCap[i] = AnimModel::create(
                mpModelRes,
                cArcCapDt[type][i],
                6,
                0, cBonusCapTexAnm_Num, 0, 0, 0,
                Model::cBoundingMode_Enable,
                nullptr,
                &anm_res_array
            );
        else
            mBonusCap[i] = AnimModel::create(
                mpModelRes,
                cArcCapDt[type][i],
                0, cBonusCapTexAnm_Num, 0, 0, 0,
                Model::cBoundingMode_Disable,
                nullptr,
                &anm_res_array
            );
    }

    LightMapMgr::instance()->setOverrideModelLightMap(true);

    setPlayerModel(mPlayerMode);
}

void MarioModel::setModelRenderPass(s32 idx_opa, s32 idx_xlu)
{
    PlayerModel::setModelRenderPass(idx_opa, idx_xlu);

    for (s32 i = 0; i < cBonusCap_Num; i++)
    {
        mBonusCap[i]->getModel()->setOpaRenderPass(idx_opa);
        mBonusCap[i]->getModel()->setXluRenderPass(idx_xlu);
    }
}

void MarioModel::setModelG3dRenderFlag(u32 flag)
{
    PlayerModel::setModelG3dRenderFlag(flag);

    for (s32 i = 0; i < cBonusCap_Num; i++)
    {
        ModelG3d* p_model = sead::DynamicCast<ModelG3d>(mBonusCap[i]->getModel());
        if (p_model)
            p_model->getRenderFlag().setDirect(flag);
    }
}

void MarioModel::play()
{
    playBody();
    playHead();

    mBonusCap[mBonusCapType]->playAnmFrameCtrl();
}

void MarioModel::calcImpl()
{
    calcBody();
    calcHead();

    switch (mNowBodyID)
    {
    default:
        break;
    case cBodyType_Normal:
    case cBodyType_Small:
        if (mHeadID == cHeadType_Normal)
        {
            mpHeadModel->getModel()->setMaterialVisible(cHeadMaterial_Hat, true);
            mpHeadModel->getModel()->setMaterialVisible(cHeadMaterial_Hair, false);
        }
        else
        {
            mpHeadModel->getModel()->setMaterialVisible(cHeadMaterial_Hat, false);
            mpHeadModel->getModel()->setMaterialVisible(cHeadMaterial_Hair, true);
        }
        break;
    }

    if (mIsBonusCap)
    {
        Model* p_bonus_cap_model = mBonusCap[mBonusCapType]->getModel();

        sead::Matrixf mtx;
        mpModel->getModel()->getBoneWorldMatrix(mJointMap[cJointID_CapPosition], &mtx);
        p_bonus_cap_model->setMtxRT(mtx); // This function is not intended to account for scale, but they use it anyway

        p_bonus_cap_model->calcAnm();
        p_bonus_cap_model->calcMdl();
    }
}

void MarioModel::draw()
{
    PlayerModel::draw();

    if (mIsBonusCap)
        Renderer::instance()->drawModel(mBonusCap[mBonusCapType]->getModel());
}

void MarioModel::setBodyID(BodyType id)
{
    PlayerModel::setBodyID(id);
    mBonusCapType = mNowBodyID == cBodyType_Small ? cBonusCap_Small : cBonusCap_Normal;
}

void MarioModel::setHeadID(HeadType id)
{
    mHeadID = id;
    mIsBonusCap = id == cHeadType_BonusCap;
}

void MarioModel::setColorType(ColorType color_type, bool keep_head_konst3)
{
    if (mColorType == color_type)
        return;

    mColorType = color_type;

    f32 frame = 0.0f;

    switch (mNowBodyID)
    {
    default:
        break;
    case cBodyType_Normal:
    case cBodyType_Small:
        switch (color_type)
        {
        default:
            break;
        case cColorType_Ice:
            frame = 2.0f;
            break;
        case cColorType_Fire:
            frame = 1.0f;
            break;
        }
        break;
    case cBodyType_Propeller:
    case cBodyType_Penguin:
        return;
    case cBodyType_Squirrel:
        if (mPlayerMode == cPlayerMode_PSquirrel)
            frame = 1.0f;
        break;
    }

    TexturePatternAnimation* p_tex_anm_color_head = mpHeadModel->getTexAnim(cTexAnm_Color);
    p_tex_anm_color_head->play(mpModelRes, (mType == cType_Luigi ? cHeadSwitchAnm_Luigi : cHeadSwitchAnm_Mario)[mNowBodyID]);
    p_tex_anm_color_head->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    p_tex_anm_color_head->getFrameCtrl().setRate(0.0f);
    p_tex_anm_color_head->getFrameCtrl().setFrame(frame);

    TexturePatternAnimation* p_tex_anm_color_body = mpModel->getTexAnim(cTexAnm_Color);
    p_tex_anm_color_body->play(mpModelRes, (mType == cType_Luigi ? cBodySwitchAnm_Luigi : cBodySwitchAnm_Mario)[mNowBodyID]);
    p_tex_anm_color_body->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    p_tex_anm_color_body->getFrameCtrl().setRate(0.0f);
    p_tex_anm_color_body->getFrameCtrl().setFrame(frame);

    TexturePatternAnimation* p_tex_anm_cap = mBonusCap[cBonusCap_Normal]->getTexAnim(cBonusCapTexAnm_Color);
    p_tex_anm_cap->play(mpModelRes, "PC_switch");
    p_tex_anm_cap->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    p_tex_anm_cap->getFrameCtrl().setRate(0.0f);
    p_tex_anm_cap->getFrameCtrl().setFrame(frame);

    if (!keep_head_konst3)
        resetTevKColor3Alpha(mpHeadModel->getModel());
}

void MarioModel::setTexAnmTypeImpl(TexAnmType type)
{
    setHeadTexAnm(type);
}

bool MarioModel::setPersonalAnm(ModelResource** pp_anm_res, sead::BufferedSafeString* p_anm_name, s32 anm_id, bool body)
{
    if (PlayerModel::setPersonalAnm(pp_anm_res, p_anm_name, anm_id, body))
        return true;

    if (mType == cType_Luigi)
    {
        bool personal_anm_set;
        switch (anm_id)
        {
        case PlayerAnmID::wait:
            p_anm_name->copy("LB_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::walk:
            p_anm_name->copy("LB_walk");
            personal_anm_set = true;
            break;
        case PlayerAnmID::run:
            p_anm_name->copy("LB_run");
            personal_anm_set = true;
            break;
        case PlayerAnmID::waitL:
        case PlayerAnmID::waitL__2:
            p_anm_name->copy("LB_waitL");
            personal_anm_set = true;
            break;
        case PlayerAnmID::waitR:
        case PlayerAnmID::waitR__2:
            p_anm_name->copy("LB_waitR");
            personal_anm_set = true;
            break;
        case PlayerAnmID::waitR3:
            p_anm_name->copy("LB_waitR3");
            personal_anm_set = true;
            break;
        case PlayerAnmID::waitL3:
            p_anm_name->copy("LB_waitL3");
            personal_anm_set = true;
            break;
        case PlayerAnmID::slope_waitL2:
            p_anm_name->copy("LB_slope_waitL2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::slope_waitR2:
            p_anm_name->copy("LB_slope_waitR2");
            personal_anm_set = true;
            break;
        case PlayerAnmID::ending_wait:
            p_anm_name->copy("LB_ending_wait");
            personal_anm_set = true;
            break;
        case PlayerAnmID::jump_stoop:
            p_anm_name->copy("LB_jump_stoop");
            personal_anm_set = true;
            break;
        default:
            personal_anm_set = false;
        }
        if (personal_anm_set)
        {
            *pp_anm_res = mpLuigiAnmRes;
            if (!body)
                mAnmFlag[cAnmFlagType_Main] |= 1 << cAnmFlagBit_Personal_Luigi;
            mAnmFlag[cAnmFlagType_Body] |= 1 << cAnmFlagBit_Personal_Luigi;
            return true;
        }
    }

    return false;
}

f32 MarioModel::getAimMotionShareScale()
{
    BodyType id = mNowBodyID;

    if (
        // isMusaPersonalAnm() || // They forgot to account for this
        isPenguinPersonalAnm() ||
        isPropellerPersonalAnm()
    ) {
        id = cBodyType_Normal;
    }

    if (mType == cType_Mario)
    {
        f32 scale = cMarioHipScale[id];
        if (!isHangCliffAnm())
            return scale;
        return scale + cMarioHangCliffScale[id];
    }
    else
    {
        f32 scale;
        if (isLuigiPersonalAnm())
            scale = cLuigiOrgHipScale[id];
        else
            scale = cLuigiHipScale[id];
        if (!isHangCliffAnm())
            return scale;
        return scale + cLuigiHangCliffScale[id];
    }
}

void MarioModel::updateBonusCap()
{
    setHeadID(cHeadType_Normal);
}

f32 MarioModel::getStoopOffsetTarget()
{
    const f32 c_luigi_stoop_offset_target[] = {
        1.0f,
        0.8f,
        1.0f,
        0.0f,
        1.0f
    };
    static_assert(sizeof(c_luigi_stoop_offset_target) / sizeof(f32) == cBodyType_Num);

    if (mType == cType_Luigi && isSitAnm())
        return c_luigi_stoop_offset_target[mNowBodyID];

    return 0.0f;
}

void MarioModel::setMusaPtoNmlAnm()
{
    ShaderParamAnimation* p_color_anm_head = mpHeadModel->getShuAnim(cShuAnm_Color_PtoNml);
    if (mType == cType_Luigi)
        p_color_anm_head->playColorAnim(mpModelRes, "MLH_PtoNml");
    else
        p_color_anm_head->playColorAnim(mpModelRes, "MMH_PtoNml");
    p_color_anm_head->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    p_color_anm_head->getFrameCtrl().setRate(1.0f);
    p_color_anm_head->getFrameCtrl().setFrame(0.0f);

    ShaderParamAnimation* p_color_anm_body = mpModel->getShuAnim(cShuAnm_Color_PtoNml);
    if (mType == cType_Luigi)
        p_color_anm_body->playColorAnim(mpModelRes, "MLB_PtoNml");
    else
        p_color_anm_body->playColorAnim(mpModelRes, "MMB_PtoNml");
    p_color_anm_body->getFrameCtrl().setPlayMode(FrameCtrl::cMode_NoRepeat);
    p_color_anm_body->getFrameCtrl().setRate(1.0f);
    p_color_anm_body->getFrameCtrl().setFrame(0.0f);
}
