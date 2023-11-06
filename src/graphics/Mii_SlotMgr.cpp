#include <graphics/Mii_DataSource.h>
#include <graphics/Mii_SlotMgr.h>
//#include <system/SaveMgr.h>

#if RIO_IS_CAFE
#include <nn/act.h>
#endif // RIO_IS_CAFE
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
      //*p_store_data = SaveMgr::instance()->getStoreData(index);
        ret = false;
        break;
    case DataSource::cType_StoreData_Custom:
        break;
    case DataSource::cType_StoreData_Account:
        ret = false;
#if RIO_IS_CAFE
        RIO_LOG("Trying to get store data for account: %d\n", index);
        {
            FFLStoreData store_data;
            if (nn::act::IsSlotOccupied(index) && nn::act::GetMiiEx(&store_data, index).IsSuccess())
            {
                *p_store_data = store_data;
                ret = true;
                RIO_LOG("Success!\n");
            }
            else
            {
                RIO_LOG("Failure...\n");
            }
        }
#endif // RIO_IS_CAFE
        break;
    default:
        ret = false;
    }

    RIO_LOG("Returning: %d\n", s32(ret));
    return ret;
}

}
