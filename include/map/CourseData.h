#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadBoundBox.h>

struct Options
{
    // Official name not known, but is called area options by the modding community.

    u32 course_default_events;
    u32 file_default_events;
    u16 loop;
    u16 time_0;
    u8  _unused0[4];
    u8  start_next_goto;
    u8  _unused1[2];
    u8  start_next_goto_coin_boost;
    u16 time_1;
    u16 time_2;
};
static_assert(sizeof(Options) == 0x18);

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

struct MapActorData
{
    // Speculated official name.

    u16 id;
    struct
    {
        u16 x;
        u16 y;
    }   offset;
    u16 event_id;   // Lower byte: event id 2, higher byte: event id 1.
    u32 param_0;
    u32 param_1;
    u8  area;
    u8  layer;
    u8  movement_id;
    u8  link_id;
    u8  init_state;
    u8  _pad[3];
};
static_assert(sizeof(MapActorData) == 0x18);

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

struct Location
{
    // Official name not known.

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
    u8  id;
    u8  _pad[3];
};
static_assert(sizeof(Location) == 0xC);

struct RailInfo
{
    // Not certain if official name.

    u8  id;
    s8  _1;
    struct
    {
        u16 start;
        u16 num;
    }   point;
    u16 flag;
    u32 _8;
};
static_assert(sizeof(RailInfo) == 0xC);

struct RailPoint
{
    // Official name not known.

    struct
    {
        u16 x;
        u16 y;
    }   offset;
    f32 speed;
    f32 accel;
    s16 delay;

    // Nabbit-related
    u16 _e;
    u8  _10;
    u8  _11;
    u8  _12;
    u8  _pad[1];
};
static_assert(sizeof(RailPoint) == 0x14);

class CourseDataFile
{
    // Is the official name. Called "area" by the modding community.

public:
    enum Block
    {
        cBlock_Environment      =   1 - 1,
        cBlock_Options          =   2 - 1,
        cBlock_ScrollData       =   3 - 1,
                                //  4
        cBlock_DistantViewData  =   5 - 1,
                                //  6
        cBlock_NextGoto         =   7 - 1,
        cBlock_MapActor         =   8 - 1,
        cBlock_MapActorLoadRes  =   9 - 1,
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

    const void* getBlock(Block block)
    {
        return mBlock[block];
    }

    const DistantViewData* getBg2Data(u8 index) const;
    const MapActorData* getMapActor(u8 index, void*) const;
    const AreaData* getAreaData(u8 index, sead::BoundBox2f* p_box = nullptr) const;
    const Location* getLocation(sead::BoundBox2f* p_box, u8 index) const;
    const RailInfo* getRailInfo(u8 index) const;
    const RailPoint* getRailPoint(u8 index) const;

private:
    void getAreaBox_(sead::BoundBox2f* p_box, const AreaData& area_data, f32 delta = 0.0f) const;

private:
    u32                                         mIndex;
    sead::SafeArray<const void*,    cBlock_Num> mBlock;
    sead::SafeArray<u32,            cBlock_Num> mBlockSize;
    sead::SafeArray<u32,            cBlock_Num> mBlockEntryNum;
    sead::SafeArray<MapActorData*,  64>         _b8;
    sead::SafeArray<u32,            64>         _1b8;
    sead::SafeArray<u32,            64>         _2b8;
};
static_assert(sizeof(CourseDataFile) == 0x3B8);

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
static_assert(sizeof(CourseData) == 0xEF0);
