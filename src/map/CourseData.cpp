#include <map/CourseData.h>

CourseData* CourseData::sInstance = nullptr;

CourseDataFile* CourseData::getFile(s32 index)
{
    CourseDataFile* p_cd_file = &(mFile[index]);
    if (!p_cd_file->getBlock(CourseDataFile::cBlock_AreaData))
        return nullptr;

    return p_cd_file;
}
