#pragma once

#include <misc/rio_Types.h>

struct FFLStoreData;

namespace Mii {

class DataSource;

class SlotMgr
{
public:
    static bool getStoreData(FFLStoreData* p_store_data, const DataSource& source);
};

}
