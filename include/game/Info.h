#pragma once

#include <heap/seadDisposer.h>

class Info
{
    SEAD_SINGLETON_DISPOSER(Info)

public:
    u8 getWorldNo() const { return mCourseNow.world_no; }
    u8 getCourseNo() const { return mCourseNow.course_no; }
    u8 getFileNo() const { return mCourseNow.file_no; }
    u8 getNextGotoNo() const { return mCourseNow.next_goto_no; }
    u32 getAreaNo() const { return mCourseNow.area_no; }
    u32 getSceneEnterType() const { return mCourseNow.scene_enter_type; }

    void setNextWorldNo(u8);
    void setNextCourseNo(u8);
    void setNextFileNo(u8);
    void setNextNextGotoNo(u8);
    void setNextSceneEnterType(u32);

private:
    struct
    {
        u8  world_no;
        u8  course_no;
        u8  file_no;
        u8  next_goto_no;
        u32 area_no;
        u32 scene_enter_type;
    }   mCourseNow;
    struct
    {
        u8  world_no;
        u8  course_no;
        u8  file_no;
        u8  next_goto_no;
        u32 scene_enter_type;
    }   mCourseNext;
};
static_assert(sizeof(Info) == 0x28);
