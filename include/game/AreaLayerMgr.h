#pragma once

#include <graphics/LayerMgr.h>

class AreaLayerMgr
{
public:
    enum Layer
    {
        cLayer_DistantView      = LayerMgr::cLayer_User_0,      // AreaTask
        cLayer_BGUpdate         = LayerMgr::cLayer_User_1,      // ^^^
        cLayer_FinalKoopaShadow = LayerMgr::cLayer_User_2,      // ^^^
        cLayer_FinalKoopa       = LayerMgr::cLayer_User_3,      // ^^^
        cLayer_3D               = LayerMgr::cLayer_User_4,      // ^^^
        cLayer_2D               = LayerMgr::cLayer_User_5,      // ^^^

        cLayer_3D_DRC           = LayerMgr::cLayer_DRC_User_0,  // ^^^
        cLayer_Menu2D_DRC       = LayerMgr::cLayer_DRC_User_1,  // CourseTask
        cLayer_Menu3D_DRC       = LayerMgr::cLayer_DRC_User_2   // ^^^
    };
};
