#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>

struct DistantViewData
{
    // Not certain if official name, but official name in NSMBW is Bg2 (which is conflicting with tile layers)

    u16     id;
    struct
    {
        s16 x;
        s16 y;
        s16 z;
    }       offset;         // Unused
    char    name[16 + 1];
    u8      parallax_mode;  // Unused
    u8      _pad[2];
};
static_assert(sizeof(DistantViewData) == 0x1C);


struct AreaData
{
    // Is the official name. Called "zone" by the modding community.

    // NSMBW
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    struct
    {
        u16 x;
        u16 y;
    }   size;
    u16 color_obj;      // "Theme", unused.
    u16 color_bg;       // "Terrain", unused.
    u8  id;
    u8  scroll;
    u8  zoom_type;
    u8  zoom_id;
    u8  zoom_change;
    u8  mask;
    u8  bg2;            // 1st BG id in NSMBW, DV ID in NSMBU.
    u8  bg3;            // 2nd BG id in NSMBW, unused.
    u8  direction;
    u8  _15;
    u8  bgm;
    u8  bgm_mode;

    // NSMB2
    u8  dv;             // DV ID in NSMB2, unused.

    // NSMBU
    u8  flag;
    u8  _pad[2];
};
static_assert(sizeof(AreaData) == 0x1C);

struct Sprite;

class CourseDataFile
{
    // Is the official name. Called "area" by the modding community.

public:
    enum BlockId
    {
        cBlock_Environment      =   1 - 1,
        cBlock_Options          =   2 - 1,
        cBlock_ScrollData       =   3 - 1,
                                //  4
        cBlock_DistantViewData  =   5 - 1,
                                //  6
        cBlock_NextGoto         =   7 - 1,
        cBlock_Sprite           =   8 - 1,
        cBlock_SpriteLoadRes    =   9 - 1,
        cBlock_AreaData         =  10 - 1,
        cBlock_Location         =  11 - 1,
                                // 12
                                // 13
        cBlock_RailInfo         =  14 - 1,
        cBlock_RailPoint        =  15 - 1,
        cBlock_Num
    };

public:
    CourseDataFile();

    const void* getBlock(BlockId block)
    {
        return mBlock[block];
    }

    const DistantViewData* getBg2Data(u8 index) const;
    const AreaData* getAreaData(u8 index, sead::BoundBox2f* p_box = nullptr) const;

private:
    u32 mIndex;
    sead::SafeArray<const void*, cBlock_Num> mBlock;
    sead::SafeArray<u32, cBlock_Num> mBlockSize;
    sead::SafeArray<u32, cBlock_Num> mBlockEntryNum;
    sead::SafeArray<Sprite*, 64> _b8;
    sead::SafeArray<u32, 64> _1b8;
    sead::SafeArray<u32, 64> _2b8;
};
static_assert(sizeof(CourseDataFile) == 0x3B8, "CourseDataFile size mismatch");

class CourseData
{
    SEAD_SINGLETON_DISPOSER(CourseData)

public:
    CourseData();
    ~CourseData();

    CourseDataFile* getFile(s32 index);

private:
    sead::SafeArray<CourseDataFile, 4> mFile;
};
static_assert(sizeof(CourseData) == 0xEF0, "CourseData size mismatch");
