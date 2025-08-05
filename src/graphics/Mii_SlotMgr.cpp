#include <graphics/Mii_SlotID.h>
#include <graphics/Mii_SlotMgr.h>
#include <system/SaveMgr.h>

#include <nn/act.h>
#include <nn/ffl.h>

namespace Mii {

bool SlotMgr::getStoreData(FFLStoreData* p_store_data, const SlotID& slot_id)
{
    bool ret = true;

    SlotID::Source source = slot_id.getSource();
    s32 index = slot_id.getIndex();

    switch (source)
    {
    case SlotID::cSource_Database_Default:
        {
            FFLResult result = FFLiGetStoreData(p_store_data, FFL_DATA_SOURCE_DEFAULT, index);
            if (result != FFL_RESULT_OK)
                ret = false;
        }
        break;
    case SlotID::cSource_Database_Official:
        {
            FFLResult result = FFLiGetStoreData(p_store_data, FFL_DATA_SOURCE_OFFICIAL, index);
            if (result != FFL_RESULT_OK)
                ret = false;
        }
        break;
    case SlotID::cSource_StoreData_Save:
        *p_store_data = SaveMgr::instance()->getStoreData(index);
        break;
    case SlotID::cSource_StoreData_Account:
        ret = false;
        if (nn::act::IsSlotOccupied(index) && nn::act::GetMiiEx(p_store_data, index).IsSuccess())
            ret = true;
        break;
    }

    return ret;
}

}
