#include <actor/ProfileInfo.h>
#include <collision/BgCollision.h>
#include <game/SubjectMgr.h>
#include <player/PlayerObject.h>

static const PlayerBgPointHIO cBgPointData_Mame[PlayerObject::cBgPointAnmType_Num] = {
    // cBgPointAnmType_Normal
    {
     // { left,   right, y_offs  } sensor_foot
        { -1.5f,  1.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -0.5f,  0.5f,  7.625f  },
     // { bottom, top,   x_offs  } sensor_wall
        { 3.0f,   4.0f,  5.0f    }
    },

    // cBgPointAnmType_Squat
    {
     // { left,   right, y_offs  } sensor_foot
        { -1.5f,  1.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -1.0f,  0.0f,  7.625f  },
     // { bottom, top,   x_offs  } sensor_wall
        { 2.5f,   3.5f,  5.0f    }
    },

    // cBgPointAnmType_Hang
    {
     // { left,   right, y_offs  } sensor_foot
        { -2.0f,  1.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -1.0f,  0.0f,  1.0f    },
     // { bottom, top,   x_offs  } sensor_wall
        { -4.0f,  -4.0f, 3.0f    }
    },

    // cBgPointAnmType_Swim
    {
     // { left,   right, y_offs  } sensor_foot
        { -1.5f,  1.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -1.0f,  0.0f,  7.5f    },
     // { bottom, top,   x_offs  } sensor_wall
        { 3.0f,   4.0f,  5.0f    }
    },

    // cBgPointAnmType_StarRoll
    {
     // { left,   right, y_offs  } sensor_foot
        { -1.5f,  1.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -1.0f,  0.0f,  7.5f    },
     // { bottom, top,   x_offs  } sensor_wall
        { 2.5f,   3.5f,  5.0f    }
    }
};

static const PlayerBgPointHIO cBgPointData_Normal[PlayerObject::cBgPointAnmType_Num] = {
    // cBgPointAnmType_Normal
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  15.9f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   11.0f, 7.9f    }
    },

    // cBgPointAnmType_Squat
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  12.0f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   8.5f,  7.9f    }
    },

    // cBgPointAnmType_Hang
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  1.0f    },
     // { bottom, top,   x_offs  } sensor_wall
        { -15.0f, -4.0f, 7.9f    }
    },

    // cBgPointAnmType_Swim
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  15.9f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   10.0f, 7.9f    }
    },

    // cBgPointAnmType_StarRoll
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  12.0f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   10.0f, 7.9f    }
    }
};

static const PlayerBgPointHIO cBgPointData_Super[PlayerObject::cBgPointAnmType_Num] = {
    // cBgPointAnmType_Normal
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  27.0f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   19.0f, 7.9f    }
    },

    // cBgPointAnmType_Squat
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  15.9f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   11.0f, 7.9f    }
    },

    // cBgPointAnmType_Hang
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  1.0f    },
     // { bottom, top,   x_offs  } sensor_wall
        { -24.0f, -4.0f, 7.9f    }
    },

    // cBgPointAnmType_Swim
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  27.0f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   19.0f, 7.9f    }
    },

    // cBgPointAnmType_StarRoll
    {
     // { left,   right, y_offs  } sensor_foot
        { -5.0f,  4.0f,  0.0f    },
     // { left,   right, y_offs  } sensor_head
        { -2.0f,  1.0f,  18.0f   },
     // { bottom, top,   x_offs  } sensor_wall
        { 4.0f,   16.0f, 7.9f    }
    }
};

static const PlayerBgPointHIO cBgPointData_PenguinSlide = {
 // { left,   right, y_offs  } sensor_foot
    { -10.0f, 9.0f,  0.0f    },
 // { left,   right, y_offs  } sensor_head
    { -7.0f,  6.0f,  15.9f   },
 // { bottom, top,   x_offs  } sensor_wall
    { 4.0f,   12.0f, 15.9f   }
};

static const PlayerBgPointHIO cBgPointData_PenguinSwim = {
 // { left,   right, y_offs  } sensor_foot
    { -5.0f,  4.0f,  4.0f    },
 // { left,   right, y_offs  } sensor_head
    { -2.0f,  1.0f,  27.0f   },
 // { bottom, top,   x_offs  } sensor_wall
    { 8.0f,   23.0f, 7.9f    }
};

static const PlayerBgPointHIO* const cBgPointData[cTallType_Num] = {
    cBgPointData_Mame,      // cTallType_Mini
    cBgPointData_Normal,    // cTallType_Small
    cBgPointData_Super      // cTallType_Normal
};

static const ActorBgCollisionCheck::Sensor cBgPointData_VineSuper = {
 // top,   bottom, x_offs
    16.0f, 1.0f,   2.0f
};

static const ActorBgCollisionCheck::Sensor cBgPointData_VineNormal = {
 // top,   bottom, x_offs
    8.0f,  1.0f,   2.0f
};

static const ActorBgCollisionCheck::Sensor cBgPointData_VineMame = {
 // top,   bottom, x_offs
    4.0f,  1.0f,   0.0f
};

static const ActorBgCollisionCheck::Sensor cBgPointData_Vine[cTallType_Num] = {
    cBgPointData_VineMame,      // cTallType_Mini
    cBgPointData_VineNormal,    // cTallType_Small
    cBgPointData_VineSuper      // cTallType_Normal
};

static const f32 cCarryStackOffsetY[cTallType_Num] = {
    8.0f,   // cTallType_Mini
    15.5f,  // cTallType_Small
    31.5f   // cTallType_Normal
};

static const ActorBgCollisionPlayerCheck::PcCheckArea cRopeCheckArea[cTallType_Num] = {
 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Mini
    { 0.0f,     3.0f,     7.0f,         3.0f,         0.0f        },

 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Small
    { 0.0f,     8.0f,     8.0f,         6.0f,         0.0f        },

 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Normal
    { 0.0f,     15.5f,    12.0f,        10.0f,        0.0f       }
};

static const ActorBgCollisionPlayerCheck::PcCheckArea cRopeCheckArea_Kinopio[cTallType_Num] = {
 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Mini
    { 0.0f,     3.0f,     4.0f,         3.0f,         0.0f        },

 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Small
    { 0.0f,     8.0f,     7.0f,         3.0f,         0.0f        },

 // { center_x, center_y, half_size_y1, half_size_y2, half_size_x } cTallType_Normal
    { 0.0f,     15.5f,    7.0f,         4.0f,         0.0f       }
};

static const ActorBgCollisionPlayerCheck::PcCheckArea cRopeCheckArea_Totten = {
 // center_x, center_y, half_size_y1, half_size_y2, half_size_x
    0.0f,     15.5f,    10.0f,        4.0f,         0.0f
};

static const sead::Vector2f cPoleCheckOffset_Totten(2.0f, 20.0f);

static const sead::Vector2f cPoleCheckOffset[cTallType_Num] = {
    sead::Vector2f(0.0f, 13.0f),    // cTallType_Mini
    sead::Vector2f(2.0f, 17.0f),    // cTallType_Small
    sead::Vector2f(2.0f, 30.0f)     // cTallType_Normal
};

static const sead::Vector2f cPoleCheckOffset_Kinopio[cTallType_Num] = {
    sead::Vector2f(0.0f, 11.0f),    // cTallType_Mini
    sead::Vector2f(2.0f, 15.0f),    // cTallType_Small
    sead::Vector2f(2.0f, 20.0f)     // cTallType_Normal
};

static const f32 cHangBcOffsetY[cTallType_Num] = {
    10.0f,  // cTallType_Mini
    16.0f,  // cTallType_Small
    27.0f   // cTallType_Normal
};

static const f32 cHangBcOffsetY_Kinopio[cTallType_Num] = {
    9.0f,   // cTallType_Mini
    13.0f,  // cTallType_Small
    21.0f   // cTallType_Normal
};

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

PlayerObject::BgPointType PlayerObject::getBgPointType()
{
    if (isStatus(cStatus_PenguinSlide) && !isStatus(cStatus_InitialSlip))
        return cBgPointType_PenguinSlide;

    if (isStatus(cStatus_PenguinSwim))
        return cBgPointType_PenguinSwim;

    return cBgPointType_Normal;
}

void PlayerObject::setBcSensorFlagsPlayer()
{
    s32 head_flag_type = 2;

    if (isChange())
        head_flag_type = 0;

    if (mSpeed.y > 0.0f || isStatus(cStatus_ControlledMove))
    {
        switch (getBgPointType())
        {
        default:
            break;
        case cBgPointType_Normal:
            if (isStatus(cStatus_142))
            {
                head_flag_type = 1;
            }
            else if (mMode == cPlayerMode_Mini || mMode == cPlayerMode_Small)
            {
                head_flag_type = 1;

                PlayerObject* p_carry_player = getCarryPlayer();
                if (p_carry_player != nullptr && (!isMameAction() || !p_carry_player->isMameAction()))
                    head_flag_type = 0;

                CarryObjBase* p_carry_hard_block = getCarryHardBlock();
                if (p_carry_hard_block != nullptr)
                    head_flag_type = 0;
            }
            else
            {
                head_flag_type = 0;
            }
            break;
        case cBgPointType_PenguinSlide:
        case cBgPointType_PenguinSwim:
            head_flag_type = 0;
            break;
        }
    }

    switch (head_flag_type)
    {
    default:
        break;
    case 1:
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_8);
        break;
    case 0:
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        break;
    }

    if (getBgPointType() == cBgPointType_PenguinSlide)
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);

        mSlideAttackBgTimer = 3;
    }

    if (isStatus(cStatus_CannonJump))
    {
        mSlideAttackBgTimer = 5;

        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);

        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);

        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_5);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_6);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_24);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_9);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_26);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_10);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_27);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);
    }
    else if (mSlideAttackBgTimer != 0)
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_54);
    }

    if (isStatus(cStatus_NoBgCrossUpdate))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_Inactive);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_Inactive);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_Inactive);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_Inactive);
    }
}

void PlayerObject::setBcSensorFlags()
{
    mBgCheckPlayer.getSensorFlag(cDirType_Down).reset();
    mBgCheckPlayer.getSensorFlag(cDirType_Up).reset();
    mBgCheckPlayer.getSensorFlag(cDirType_Right).reset();
    mBgCheckPlayer.getSensorFlag(cDirType_Left).reset();

    setBcSensorFlagsBase();
    setBcSensorFlagsPlayer();

    if (!SubjectMgr::instance()->isDisableKaniAction())
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_14);

    if (!isMameAction() && !isStatus(cStatus_RideCloud))
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_1);

    if (isStatus(cStatus_Hang))
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_Inactive);

    if (isStatus(cStatus_Vine))
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_55);

    if (!isNowBgCross(cBgCross_IsSlightlyInsideSinkSand))
    {
        if (isStatus(cStatus_37) || isStatus(cStatus_38) || isStatus(cStatus_60))
        {
            mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_18);
            mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_18);
            if (isStatus(cStatus_39))
                mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_22);
        }
    }

    if (mMode == cPlayerMode_Penguin)
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_51);

    if (mMode == cPlayerMode_PSquirrel)
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Down).setBit(ActorBgCollisionCheck::SensorFlag::cBit_46);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_46);
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_46);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_46);
    }

    if (isStatus(cStatus_Vine) || isStatus(cStatus_PoleRope) || isStatus(cStatus_Pole))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_28);
        mBgCheckPlayer.getSensorFlag(cDirType_Up).setBit(ActorBgCollisionCheck::SensorFlag::cBit_15);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_28);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_28);

        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_15);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_15);
    }

    if (isStatus(cStatus_PenguinSwim))
    {
        mBgCheckPlayer.getSensorFlag(cDirType_Right).setBit(ActorBgCollisionCheck::SensorFlag::cBit_16);
        mBgCheckPlayer.getSensorFlag(cDirType_Left).setBit(ActorBgCollisionCheck::SensorFlag::cBit_16);
    }
}

void PlayerObject::reviseBgPointDataCarryUnk(ActorBgCollisionCheck::Sensor& foot, ActorBgCollisionCheck::Sensor& head, ActorBgCollisionCheck::Sensor& wall)
{
    if (isStatus(cStatus_142) && isCarry())
    {
        onStatus(cStatus_BgPointDataCarryRev);

        sead::Vector3f carry_pos;
        getCarryPos(&carry_pos);
        f32 carry_offset_y = carry_pos.y - mPos.y;

        if (wall.center_offset < 7.9f)
            wall.center_offset = 7.9f;

        f32 wall_top = carry_offset_y + 20.0f;
        if (wall_top < wall.p2)
            wall_top = wall.p2;
        wall.p2 = wall_top;

        head.p1 = -2.0f;
        head.p2 = 1.0f;
        f32 head_top = carry_offset_y + 24.0f;
        if (head_top < head.center_offset)
            head_top = head.center_offset;
        head.center_offset = head_top;

        foot.p1 = -5.0f;
        foot.p2 = 4.0f;
        foot.center_offset = 0.0f;
    }
}

const PlayerBgPointHIO* PlayerObject::getBgPointDataBase(PlayerMode mode, BgPointAnmType anm_type)
{
    return &(cBgPointData[getTallType(mode)][anm_type]);
}

void PlayerObject::reviseBgPointDataCarryHardBlock(ActorBgCollisionCheck::Sensor& wall, ActorBgCollisionCheck::Sensor& head)
{
    CarryObjBase* p_carry_hard_block = getCarryHardBlock();
    if (p_carry_hard_block != nullptr)
    {
        onStatus(cStatus_BgPointDataCarryRev);

        const PlayerBgPointHIO* p_bg_point_data = getBgPointDataBase();

        if (wall.center_offset < p_bg_point_data->sensor_wall.center_offset)
            wall.center_offset = p_bg_point_data->sensor_wall.center_offset;

        wall.p2 += 12.0f;

        head.p1 = p_bg_point_data->sensor_head.p1;
        head.p2 = p_bg_point_data->sensor_head.p2;
        head.center_offset += 12.0f;
    }
}

PlayerObject::CarryPlayerType PlayerObject::checkCarryPlayerRoof(const ActorBgCollisionCheck::Sensor& wall, const ActorBgCollisionCheck::Sensor& head)
{
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
    {
        f32 head_y = mPos.y + head.center_offset;

        sead::Vector3f check_pos(
            mPos.x,
            head_y - 10.0f,
            mPos.z
        );

        PlayerMode carry_player_mode = p_carry_player->mMode;

        f32 carry_player_head_top_normal = getBgPointDataBase(carry_player_mode, cBgPointAnmType_Normal)->sensor_head.center_offset;
        f32 carry_player_head_top_squat = getBgPointDataBase(carry_player_mode, cBgPointAnmType_Squat)->sensor_head.center_offset;

        f32 force_crouch_min_y = head_y + (carry_player_head_top_normal - carry_player_head_top_squat) + 2.0f;

        CarryPlayerType type = cCarryPlayerType_Normal;

        f32 check_x_offset = wall.p1 - 1.0f; // NSMBU Bug: typo, should be wall.center_offset - 1.0f instead. Correct in NSMBW.

        f32 hit_pos_y_right;
        check_pos.x = mPos.x + check_x_offset;
        if (mBgCheckPlayer.checkTenjou(check_pos, 32.0f, &hit_pos_y_right, true))
        {
            if (hit_pos_y_right <= force_crouch_min_y)
            {
                type = cCarryPlayerType_ForceCrouch;
                if (hit_pos_y_right <= head_y)
                    type = cCarryPlayerType_Blocked;
            }
        }

        f32 hit_pos_y_left;
        check_pos.x = mPos.x - (check_x_offset + 1.0f);
        if (mBgCheckPlayer.checkTenjou(check_pos, 32.0f, &hit_pos_y_left, true))
        {
            if (hit_pos_y_left <= force_crouch_min_y)
            {
                type = cCarryPlayerType_ForceCrouch;
                if (hit_pos_y_left <= head_y)
                    type = cCarryPlayerType_Blocked;
            }
        }

        if (type == cCarryPlayerType_Blocked)
            return cCarryPlayerType_Blocked;

        if (type == cCarryPlayerType_ForceCrouch)
            return cCarryPlayerType_ForceCrouch;
    }
    return cCarryPlayerType_Normal;
}

void PlayerObject::reviseBgPointDataCarryPlayerBase(ActorBgCollisionCheck::Sensor& wall, ActorBgCollisionCheck::Sensor& head, bool carry_force_crouch)
{
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
    {
        const PlayerBgPointHIO* p_carry_player_bg_point_data;
        if (carry_force_crouch)
            p_carry_player_bg_point_data = getBgPointDataBase(p_carry_player->mMode, cBgPointAnmType_Squat);
        else
            p_carry_player_bg_point_data = getBgPointDataBase(p_carry_player->mMode, cBgPointAnmType_Normal);

        const ActorBgCollisionCheck::Sensor& carry_player_wall_sensor = p_carry_player_bg_point_data->sensor_wall;
        const ActorBgCollisionCheck::Sensor& carry_player_head_sensor = p_carry_player_bg_point_data->sensor_head;

        if (wall.center_offset < carry_player_wall_sensor.center_offset)
            wall.center_offset = carry_player_wall_sensor.center_offset;

        f32 head_top = carry_player_head_sensor.center_offset + cCarryStackOffsetY[getTallType()]; // Carried player head height + own height
        f32 wall_top = carry_player_wall_sensor.p2            + cCarryStackOffsetY[getTallType()]; // Carried player wall height + own height

        if (isStatus(cStatus_LiftUp))
        {
            f32 current_stack_distance = p_carry_player->mPos.y - mPos.y;

            f32 current_head_top = carry_player_head_sensor.center_offset + current_stack_distance;
            if (head_top > current_head_top)
                head_top = current_head_top;
            if (head_top < head.center_offset)
                head_top = head.center_offset;

            f32 current_wall_top = carry_player_wall_sensor.p2 + current_stack_distance;
            if (wall_top > current_wall_top)
                wall_top = current_wall_top;
            if (wall_top < wall.p2)
                wall_top = wall.p2;
        }

        head.p1 = carry_player_head_sensor.p1;
        head.p2 = carry_player_head_sensor.p2;
        head.center_offset = head_top;

        wall.p2 = wall_top;
    }
}

void PlayerObject::reviseBgPointDataCarryPlayer(ActorBgCollisionCheck::Sensor& wall, ActorBgCollisionCheck::Sensor& head)
{
    mBgCheckPlayer.setCarryPlayerNo(-1);
    offStatus(cStatus_109);
    offStatus(cStatus_110);
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
    {
        onStatus(cStatus_BgPointDataCarryRev);
        mBgCheckPlayer.setCarryPlayerNo(p_carry_player->getPlayerNo());
        if (isStatus(cStatus_Jump) && !isStatus(cStatus_111))
            reviseBgPointDataCarryPlayerBase(wall, head, false);
        else
        {
            reviseBgPointDataCarryPlayerBase(wall, head, true);
            CarryPlayerType type = checkCarryPlayerRoof(wall, head);
            if (type == cCarryPlayerType_ForceCrouch)
                onStatus(cStatus_109);
            else if (type == cCarryPlayerType_Blocked)
            {
                onStatus(cStatus_109);
                onStatus(cStatus_110);
            }
        }
    }
}

const ActorBgCollisionPlayerCheck::PcCheckArea& PlayerObject::getRopeCheckArea()
{
    if (isKinopio())
        return cRopeCheckArea_Kinopio[getTallType()];
    else if (isTotten())
        return cRopeCheckArea_Totten;
    else
        return cRopeCheckArea[getTallType()];
}

void PlayerObject::setBcData(BcMode mode)
{
    const PlayerBgPointHIO* p_bg_point_data = getBgPointData();

    ActorBgCollisionCheck::Sensor foot = p_bg_point_data->sensor_foot;
    ActorBgCollisionCheck::Sensor head = p_bg_point_data->sensor_head;
    ActorBgCollisionCheck::Sensor wall = p_bg_point_data->sensor_wall;
    if (isStatus(cStatus_Vine))
        wall.p2 = head.center_offset - 2.0f;

    bool is_carry_rev_old = isStatus(cStatus_BgPointDataCarryRev);

    offStatus(cStatus_BgPointDataCarryRev);
    reviseBgPointDataCarryUnk(foot, head, wall);
    reviseBgPointDataCarryHardBlock(wall, head);
    reviseBgPointDataCarryPlayer(wall, head);

    ActorBgCollisionCheck::Sensor vine = cBgPointData_Vine[getTallType()];

    if (mode == cBcMode_Direct || (is_carry_rev_old && !isStatus(cStatus_BgPointDataCarryRev)))
    {
        mBcSensorFoot = foot;
        mBcSensorHead = head;
        mBcSensorWall = wall;
        mBcSensorVine = vine;
    }
    else
    {
        sead::Mathf::chase(&mBcSensorFoot.p1,            foot.p1,            2.0f);
        sead::Mathf::chase(&mBcSensorFoot.p2,            foot.p2,            2.0f);
        sead::Mathf::chase(&mBcSensorFoot.center_offset, foot.center_offset, 2.0f);
        sead::Mathf::chase(&mBcSensorHead.p1,            head.p1,            2.0f);
        sead::Mathf::chase(&mBcSensorHead.p2,            head.p2,            2.0f);
      //sead::Mathf::chase(&mBcSensorHead.center_offset, head.center_offset, 2.0f);
        sead::Mathf::chase(&mBcSensorWall.p1,            wall.p1,            2.0f);
        sead::Mathf::chase(&mBcSensorWall.p2,            wall.p2,            2.0f);
        sead::Mathf::chase(&mBcSensorWall.center_offset, wall.center_offset, 2.0f);
        sead::Mathf::chase(&mBcSensorVine.p1,            vine.p1,            2.0f);
        sead::Mathf::chase(&mBcSensorVine.p2,            vine.p2,            2.0f);
        sead::Mathf::chase(&mBcSensorVine.center_offset, vine.center_offset, 2.0f);

        if (mBcSensorHead.center_offset < head.center_offset)
        {
            sead::Vector3f check_pos(
                mPos.x,
                mPos.y + mBcSensorHead.center_offset + 1.0f,
                mPos.z
            );
            f32 hit_pos_y;
            if (mBgCheckPlayer.checkTenjou(check_pos, 16.0f, &hit_pos_y))
                if (hit_pos_y < mPos.y + head.center_offset)
                    head.center_offset = sead::Mathf::clampMin(hit_pos_y - mPos.y, 0.0f);
        }
        sead::Mathf::chase(&mBcSensorHead.center_offset, head.center_offset, 2.0f);
    }

    mBgCheckPlayer.setSensorFoot(&mBcSensorFoot);
    mBgCheckPlayer.setSensorHead(&mBcSensorHead);
    mBgCheckPlayer.setSensorWall(&mBcSensorWall);

    setBcSensorFlags();

    mBgCheckPlayer.setPcCheckArea(getRopeCheckArea());
}

void PlayerObject::initBcData()
{
    setBcData(cBcMode_Direct);
    mNowBgCross.reset();
    mOldBgCross.reset();
}

bool PlayerObject::checkChibiYoshiLiftUpBlocked()
{
    f32 head_y = mPos.y + getHeadBgPointData()->center_offset;

    sead::Vector3f carry_pos;
    getCarryPos(&carry_pos);
    f32 carry_top_y = carry_pos.y + 24.0f;

    if (carry_top_y > head_y)
    {
        f32 check_distance = carry_top_y - head_y;
        const f32 check_x_offset = 3.0f;
        sead::Vector3f check_pos;
        {
            check_pos.set(
                mPos.x + check_x_offset,
                head_y,
                mPos.z
            );
            if (mBgCheckPlayer.checkTenjou(check_pos, check_distance))
                return true;
        }
        {
            check_pos.set(
                mPos.x - (check_x_offset + 1.0f),
                head_y,
                mPos.z
            );
            if (mBgCheckPlayer.checkTenjou(check_pos, check_distance))
                return true;
        }
    }
    return false;
}

bool PlayerObject::checkCancelTarzanRopeLR(u8 dir)
{
    if (mBgCheckPlayer.checkWall(dir))
    {
        const BgCollision* p_bg_collision = mBgCheckPlayer.getHitBgCollisionWall(dir);
        if (p_bg_collision != nullptr)
        {
            const Actor* p_hit_actor = p_bg_collision->getOwner();
            if (p_hit_actor == nullptr) // Hit a wall tile
                return true;
            if (p_hit_actor->getProfileID() != ProfileInfo::cProfileID_ActorBlockMakeDRC)
                return true;
        }
    }
    return false;
}

bool PlayerObject::checkCancelTarzanRopeUp()
{
    if (mBgCheckPlayer.checkHead())
    {
        const BgCollision* p_bg_collision = mBgCheckPlayer.getHitBgCollisionHead();
        if (p_bg_collision != nullptr)
        {
            const Actor* p_hit_actor = p_bg_collision->getOwner();
            if (p_hit_actor == nullptr) // Hit a ceiling tile
                return true;
            if (p_hit_actor->getProfileID() != ProfileInfo::cProfileID_ActorBlockMakeDRC)
                return true;
        }
    }
    return false;
}

bool PlayerObject::checkCancelTarzanRopeUpRDash()
{
    if (mBgCheckPlayer.checkHead())
    {
        const BgCollision* p_bg_collision = mBgCheckPlayer.getHitBgCollisionHead();
        if (p_bg_collision != nullptr)
        {
            const Actor* p_hit_actor = p_bg_collision->getOwner();
            if (p_hit_actor == nullptr) // Hit a ceiling tile
                return true;
            if (p_hit_actor->getProfileID() != ProfileInfo::cProfileID_ObjPipeDown &&
                p_hit_actor->getProfileID() != ProfileInfo::cProfileID_ObjPipeDownNG &&
                p_hit_actor->getProfileID() != ProfileInfo::cProfileID_ObjPipeDownGroup)
                return true;
        }
    }
    return false;
}

const PlayerBgPointHIO* PlayerObject::getBgPointData()
{
    BgPointType type = getBgPointType();
    if (type == cBgPointType_PenguinSlide)
        return &cBgPointData_PenguinSlide;
    else if (type == cBgPointType_PenguinSwim)
        return &cBgPointData_PenguinSwim;
    else
    {
        BgPointAnmType anm_type = cBgPointAnmType_Normal;
        if (mModelMgr.isSitAnm())
        {
            if (mMode != cPlayerMode_Mini)
                anm_type = cBgPointAnmType_Squat;
        }
        else if (mModelMgr.isHangAnm())
        {
            anm_type = cBgPointAnmType_Hang;
        }
        else if (mModelMgr.isSwimAnm())
        {
            anm_type = cBgPointAnmType_Swim;
        }
        else if (mModelMgr.getAnmID() == PlayerAnmID::star_roll)
        {
            anm_type = cBgPointAnmType_StarRoll;
        }
        return getBgPointDataBase(mMode, anm_type);
    }
}

f32 PlayerObject::getStandHeadBgPointY()
{
    const ActorBgCollisionCheck::Sensor& wall = getBgPointDataBase()->sensor_wall;
    f32 wall_top = wall.p1;
    if (wall_top < wall.p2)
        wall_top = wall.p2;

    const ActorBgCollisionCheck::Sensor& head = getBgPointDataBase()->sensor_head;
    f32 head_top = head.center_offset;

    f32 top = wall_top + 5.0f;
    if (top > head_top)
        top = head_top;

    return top;
}

void PlayerObject::checkBgCrossSub()
{
    checkWalkWallBgCross();

    // checkPole();

    ActorBgCollisionPlayerCheck::VineResult vine_res = mBgCheckPlayer.checkVine(mBcSensorVine);
    if (vine_res.flag != 0)
    {
        onNowBgCross(cBgCross_IsVine);

        if ((vine_res.flag & 1) || (vine_res.flag >> 1 & 1))
            onNowBgCross(cBgCross_60);

        if ((vine_res.flag >> 2 & 1) || (vine_res.flag >> 3 & 1))
            onNowBgCross(cBgCross_61);

        if ((vine_res.flag >> 4 & 1) || (vine_res.flag >> 5 & 1))
            onNowBgCross(cBgCross_62);

        if (isAmiRollAction())
            onNowBgCross(cBgCross_65);
        else
        {
            if ((vine_res.flag >> 6 & 1) || (vine_res.flag >> 8 & 1))
            {
                onNowBgCross(cBgCross_65);
                onNowBgCross(cBgCross_63);
            }
            if ((vine_res.flag >> 7 & 1) || (vine_res.flag >> 9 & 1))
            {
                onNowBgCross(cBgCross_65);
                onNowBgCross(cBgCross_64);
            }
        }
    }
}

void PlayerObject::postBgCross()
{
    if (!isMameAction())
        offStatus(cStatus_CanWaterWalk);

    if (isNowBgCross(cBgCross_IsWater) && !isNowBgCross(cBgCross_RDash_IsNonWaterLiquid) && !isNowBgCross(cBgCross_IsAirWater))
    {
        if (isNowBgCross(cBgCross_IsHead))
        {
            _2a10 = 10;
            offStatus(cStatus_CanWaterWalk);
        }
        else if (isStatus(cStatus_CanWaterWalk) || isStatus(cStatus_182))
        {
            if (mSpeed.y < 0.0f && _2a10 == 0)
            {
                mPos.y = mWaterSurfacePosY;
                onNowBgCross(cBgCross_IsWaterShallow);
                onNowBgCross(cBgCross_IsFoot);
                // if (isStatus(cStatus_PenguinSlide))
                //     onNowBgCross(cBgCross_IsIce);
                offNowBgCross(cBgCross_IsUnderwater);
                offNowBgCross(cBgCross_IsCompletelyUnderwater);
                mWaterDepthType = 0;
            }
        }
    }

    if (isNowBgCross(cBgCross_IsFoot))
    {
        if (isNowBgCross(cBgCross_IsWaterShallow))
            onStatus(cStatus_IsWaterWalk);
        else
            offStatus(cStatus_IsWaterWalk);
    }

    if (isNowBgCross(cBgCross_IsSlightlyInsideSinkSand))
    {
        if (isStatus(cStatus_PenguinSlide) && mSpeed.y < 0.0f)
        {
            mPos.y = mSinkSandSurfacePosY;
            onNowBgCross(cBgCross_IsFoot);
            offNowBgCross(cBgCross_IsSlightlyInsideSinkSand);
            offNowBgCross(cBgCross_IsPartiallySubmergedInSinkSand);
            offNowBgCross(cBgCross_IsCompletelySubmergedInSinkSand);
        }
    }

    if (isNowBgCross(cBgCross_IsSlightlyInsideSinkSand))
    {
        if (isNowBgCross(cBgCross_IsUnderwater))
            sead::Mathf::chase(&mSandSinkRate, -0.3f, 0.02f);
        else
            sead::Mathf::chase(&mSandSinkRate, -1.26f, 0.08f);
    }
    else
    {
        setJumpSandSinkRate();
    }

    postBgCrossBase();

    if (!isNowBgCross(cBgCross_74) && !isStatus(cStatus_46) && !isStatus(cStatus_47))
    {
        // if (isNowBgCross(cBgCross_IsWallTouchL) && mSpeedF < 0.0f ||
        //     isNowBgCross(cBgCross_IsWallTouchR) && mSpeedF > 0.0f)
        // {
        //     mSpeedF = 0.0f;
        //     mMaxSpeedF = 0.0f;
        //     mAddSpeedF = 0.0f;
        //     mAirDriftSpeedF = 0.0f;
        // }
        if (isNowBgCross(cBgCross_IsFoot) && isNowBgCross(cBgCross_IsIce))
        {
            const BgCollision* p_bg_collision_r = mBgCheckPlayer.getHitBgCollisionWall(cDirType_Right);
            if (p_bg_collision_r != nullptr)
            {
                f32 delta_x = p_bg_collision_r->getTypePos().x - p_bg_collision_r->getTypePosPrev().x;
                if (delta_x < -1.0f)
                    delta_x = -1.0f;
                else if (delta_x > 1.0f)
                    delta_x = 1.0f;
                if (delta_x != 0.0f)
                {
                    f32 speed = mSpeedF;
                    if (speed > delta_x)
                        speed = delta_x;
                    mSpeedF = speed;
                }
            }
            const BgCollision* p_bg_collision_l = mBgCheckPlayer.getHitBgCollisionWall(cDirType_Left);
            if (p_bg_collision_l != nullptr)
            {
                f32 delta_x = p_bg_collision_l->getTypePos().x - p_bg_collision_l->getTypePosPrev().x;
                if (delta_x < -1.0f)
                    delta_x = -1.0f;
                else if (delta_x > 1.0f)
                    delta_x = 1.0f;
                if (delta_x != 0.0f)
                {
                    f32 speed = mSpeedF;
                    if (speed > delta_x)
                        speed = delta_x;
                    mSpeedF = speed;
                }
            }
        }
    }

    if (isNowBgCross(cBgCross_IsFunsui) && isNowBgCross(cBgCross_IsHead))
    {
        PlayerObject* p_carry_player = getCarryPlayer();
        if (p_carry_player != nullptr)
            releaseCarryActorBase();
    }

    if (isNowBgCross(cBgCross_IsFoot) ||
        isNowBgCross(cBgCross_IsUnderwater) ||
        // (isStatus(cStatus_Vine) && mBgCheckPlayer.getVineType() == ActorBgCollisionPlayerCheck::cVineType_Rock) ||
        isStatus(cStatus_RideBalloon) || isStatus(cStatus_Stunned) || isStatus(cStatus_OutOfPlay) ||
        isStatus(cStatus_RidePlayer) || isStatus(cStatus_RideYoshi))
    {
        if (!isNowBgCross(cBgCross_75))
            clearTreadCount();
    }

    if (isNowBgCross(cBgCross_IsFoot) ||
        isNowBgCross(cBgCross_IsUnderwater) ||
        isStatus(cStatus_RideYoshi) || isStatus(cStatus_RideCloud) ||
        isStatus(cStatus_Vine) || isStatus(cStatus_Hang) || isStatus(cStatus_Pole) || isStatus(cStatus_KaniHang) || isStatus(cStatus_PoleRope))
    {
        // setEnemyStageClearDemo();
        clearJumpActionInfo();
        resetPropelFlyTime();
        mPlayerKey.offStatus(PlayerKey::cStatus_ForceJump);
        mPlayerKey.offStatus(PlayerKey::cStatus_NoJump);
    }
}

void PlayerObject::clearJumpActionInfo()
{
    // offStatus(cStatus_199);
    offStatus(cStatus_SinkSandSurfJump);
    offStatus(cStatus_116);

    _2d4c = 0;
    mMusaCanDoJump = true;
    _2d4a = 1;
    PlayerObject* p_carry_player = getCarryPlayer();
    if (p_carry_player != nullptr)
        p_carry_player->_2d4a = 1;
    _2d50 = 0;

    if (mScrollMode == cScrollMode_4 || mScrollMode == cScrollMode_2)
        setScrollMode(cScrollMode_0);

    resetMissSpin();
}

bool PlayerObject::checkPole()
{
    sead::Vector2f offset = cPoleCheckOffset[getTallType()];
    if (isKinopio())
        offset.y = cPoleCheckOffset_Kinopio[getTallType()].y;
    else if (isTotten())
        offset = cPoleCheckOffset_Totten;
    if (mBgCheckPlayer.checkPole(offset))
    {
        onNowBgCross(cBgCross_IsPole);
        return true;
    }
    return false;
}

f32 PlayerObject::getHangBcOffsetY()
{
    if (isKinopio())
        return cHangBcOffsetY_Kinopio[getTallType()];
    return cHangBcOffsetY[getTallType()];
}

f32 PlayerObject::getTarzanRopeCenterY()
{
    return getRopeCheckArea().center_y;
}

f32 PlayerObject::getTarzanRopeBcOffsetY()
{
    return getRopeCheckArea().center_y + getRopeCheckArea().half_size_y1;
}
