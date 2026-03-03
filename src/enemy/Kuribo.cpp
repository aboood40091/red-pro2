#include <enemy/Kuribo.h>

Kuribo::Kuribo(const ActorCreateParam& param)
    : KuriboBase(param)
    , mKuriboType(0)
    , mKakiboAnm(0)
    , _1a96(0)
    , _1a97(0)
    , mIsKakiboWalk1(false)
    , mWakiTargetPos(0.0f, 0.0f, 0.0f)
    , mWakiDir(cWakiDir_Up)
    , mKakiboBgmHoldTimer(0)
    , mIsFunsui(false)
    , mPreFunsuiSpeedX(0.0f)
    , mGroundDistance(0.0f)
    , mpBalloon(nullptr)
{
}
