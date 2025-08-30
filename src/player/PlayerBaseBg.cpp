#include <player/PlayerBase.h>

PlayerBase::BgAttr PlayerBase::getFootBgAttr(BgUnitCode::Attr attr)
{
    switch (attr)
    {
    case BgUnitCode::cIce:
        return cBgAttr_Ice;
    case BgUnitCode::cSnow:
        return cBgAttr_Snow;
    case BgUnitCode::cNuma:
        return cBgAttr_Sand;
    case BgUnitCode::cSand:
        return cBgAttr_Sand;
    case BgUnitCode::cGrass:
        return cBgAttr_Dirt;
    case BgUnitCode::cCloud:
        return cBgAttr_Cloud;
    case BgUnitCode::cBeachSand:
        return cBgAttr_Beach;
    case BgUnitCode::cManta:
        return cBgAttr_Manta;
    case BgUnitCode::cPalmTree:
        return cBgAttr_Leaf;
    case BgUnitCode::cWood:
        return cBgAttr_Wood;
    case BgUnitCode::cWater:
        return cBgAttr_Water2;
    case BgUnitCode::cCarpet:
        return cBgAttr_Carpet;
    case BgUnitCode::cNone:
    default:
        return cBgAttr_Rock;
    }
}
