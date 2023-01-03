#include <map/CourseData.h>

const DistantViewData* CourseDataFile::getBg2Data(u8 index) const
{
    const DistantViewData* dv_data = static_cast<const DistantViewData*>(mBlock[cBlock_DistantViewData]);
    s32 dv_data_num = mBlockEntryNum[cBlock_DistantViewData];

    for (s32 i = 0; i < dv_data_num; i++)
        if (dv_data[i].id == index)
            return &(dv_data[i]);

    return nullptr;
}

CourseData* CourseData::sInstance = nullptr;

CourseDataFile* CourseData::getFile(s32 index)
{
    CourseDataFile* p_cd_file = &(mFile[index]);
    if (!p_cd_file->getBlock(CourseDataFile::cBlock_AreaData))
        return nullptr;

    return p_cd_file;
}
