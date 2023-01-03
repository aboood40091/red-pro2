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

const AreaData* CourseDataFile::getAreaData(u8 index, sead::BoundBox2f* p_box) const
{
    const AreaData* area_data = static_cast<const AreaData*>(mBlock[cBlock_AreaData]);

    for (u32 i = 0; i < mBlockEntryNum[cBlock_AreaData]; i++)
    {
        if (area_data[i].id == index)
        {
            if (p_box != nullptr)
                getAreaBox_(p_box, area_data[i]);

            return &(area_data[i]);
        }
    }

    return nullptr;
}

void CourseDataFile::getAreaBox_(sead::BoundBox2f* p_box, const AreaData& area_data, f32 delta) const
{
    s32 min_y = area_data.offset.y + area_data.size.y;

    sead::Vector2f min(
         f32(area_data.offset.x) - delta,
        -f32(             min_y) - delta
    );

    sead::Vector2f max(
        min.x + area_data.size.x + delta + delta,
        min.y + area_data.size.y + delta + delta
    );

    p_box->set(min, max);
}

CourseData* CourseData::sInstance = nullptr;

CourseDataFile* CourseData::getFile(s32 index)
{
    CourseDataFile* p_cd_file = &(mFile[index]);
    if (!p_cd_file->getBlock(CourseDataFile::cBlock_AreaData))
        return nullptr;

    return p_cd_file;
}
