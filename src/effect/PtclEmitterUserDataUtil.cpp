#include <effect/PtclEmitterUserDataUtil.h>

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
