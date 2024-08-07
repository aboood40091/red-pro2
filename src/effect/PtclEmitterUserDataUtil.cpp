#include <course_select/CourseSelectTask.h>
#include <effect/PtclEmitterUserDataUtil.h>
#include <event/EventMgr.h>
#include <player/PlayerMgr.h>
#include <player/PlayerObject.h>

bool PtclEmitterUserDataUtil::isCalcGroup(s32 group_id)
{
    if (group_id != -1)
    {
        if (CourseSelectTask::instance() != nullptr && CourseSelectTask::instance()->_dc9)
        {
            if (group_id != 3)
                return false;
        }

        if ((0 <= group_id && group_id < 8) && EventMgr::instance() != nullptr)
        {
            switch (group_id)
            {
            case 0:
                if (EventMgr::instance()->getCurrentEvent() != nullptr)
                    return false;
                break;
            case 2:
                if (EventMgr::instance()->getCurrentEvent() != nullptr)
                    return EventMgr::instance()->isNormal();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                if (EventMgr::instance()->getCurrentEvent() != nullptr)
                {
                    if (PlayerMgr::instance() != nullptr)
                    {
                        PlayerObject* player = PlayerMgr::instance()->getPlayerObject2(group_id - 4);
                        if (player != nullptr && !EventMgr::instance()->isJoin(player))
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

bool PtclEmitterUserDataUtil::isForceCalcEmitterSet(u16 user_data_bit)
{
    return user_data_bit & 0x2000;
}

s32 PtclEmitterUserDataUtil::getEmitterSetGroupID(u16 user_data_bit, s32 player_no)
{
    if (user_data_bit & 0x1000)
        return 3;

    if (0 <= player_no && player_no < 4)
        return 4 + player_no;

    if (user_data_bit & 0x4000)
        return 1;

    if (user_data_bit & 0x8000)
        return 2;

    return 0;
}

u32 PtclEmitterUserDataUtil::getEmitterUserType(u16 user_data_bit)
{
    if (user_data_bit & 0x0200)
    {
        if (user_data_bit & 0x0800)
            return 14;

        if (user_data_bit & 0x0400)
            return 13;

        return 15;
    }

    if (user_data_bit & 0x0800)
        return 16;

    if (user_data_bit & 0x0100)
    {
        if (user_data_bit & 0x0400)
            return 10;

        return 11;
    }

    if (user_data_bit & 0x0400)
        return 12;

    if (user_data_bit & 1)
        return 0;

    if (user_data_bit & 0x0080)
        return 7;

    if (user_data_bit & 0x0040)
        return 6;

    if (user_data_bit & 0x0020)
        return 5;

    if (user_data_bit & 0x0010)
        return 4;

    if (user_data_bit & 0x0008)
        return 3;

    if (user_data_bit & 0x0002)
        return 1;

    if (user_data_bit & 0x0004)
        return 2;

    if (user_data_bit & 0x1000)
        return 8;

    return 9;
}

s32 PtclEmitterUserDataUtil::getEmitterColorType(u16 user_data_bit)
{
    if (user_data_bit & 0x2000)
        return 1;

    if (user_data_bit & 0x4000)
        return 2;

    if (user_data_bit & 0x8000)
        return 3;

    return 0;
}
