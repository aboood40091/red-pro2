#include <boss/Boss.h>

Boss::Boss(const ActorCreateParam& param)
    : Enemy(param)
    , mLifeHP(1)
    , _1884(1)
    , _1888(0)
    , mIsShock(false)
    , mIsDemoWait(false)
    , mAudioObjSeqVar(0)
    , mAttentionLookat(mActorUniqueID)
    , mBoyoMgr(this)
    , mIcePos(0.0f, 0.0f, 0.0f)
    , mIceScale(0.0f, 0.0f, 0.0f)
    , mPos_PreIce(0.0f, 0.0f, 0.0f)
    , mSpeed_PreIce(0.0f, 0.0f, 0.0f)
    , mAccelY_PreIce(0.0f)
    , mAccelF_PreIce(0.0f)
    , _186c_PreIce(0)
    , _186e_PreIce(0)
{
    _1890.fill(0);
}
