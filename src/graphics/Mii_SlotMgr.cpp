#include <graphics/Mii_DataSource.h>
#include <graphics/Mii_SlotMgr.h>
#include <system/SaveMgr.h>

#include <nn/act.h>
#include <nn/ffl.h>

namespace Mii {

bool SlotMgr::getStoreData(FFLStoreData* p_store_data, const DataSource& source)
{
    bool ret = true;

    DataSource::Type type = source.getType();
    s32 index = source.getIndex();

    switch (type)
    {
    case DataSource::cType_Database_Default:
        {
            FFLResult result = FFLiGetStoreData(p_store_data, FFL_DATA_SOURCE_DEFAULT, index);
            if (result != FFL_RESULT_OK)
                ret = false;
        }
        break;
    case DataSource::cType_Database_Official:
        {
            FFLResult result = FFLiGetStoreData(p_store_data, FFL_DATA_SOURCE_OFFICIAL, index);
            if (result != FFL_RESULT_OK)
                ret = false;
        }
        break;
    case DataSource::cType_StoreData_Save:
        *p_store_data = SaveMgr::instance()->getStoreData(index);
        break;
    case DataSource::cType_StoreData_Account:
        ret = false;
        if (nn::act::IsSlotOccupied(index) && nn::act::GetMiiEx(p_store_data, index).IsSuccess())
            ret = true;
        break;
    }

    return ret;
}

}
