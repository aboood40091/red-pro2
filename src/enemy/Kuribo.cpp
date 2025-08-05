#include <enemy/Kuribo.h>

Kuribo::Kuribo(const ActorCreateParam& param)
    : KuriboBase(param)
    , mKuriboType(0)
    , mKakiboAnmType(0)
    , _1a96(0)
    , _1a97(0)
    , _1a98(false)
    , _1a9c(0.0f, 0.0f, 0.0f)
    , _1aa8(0)
    , _1aac(0)
    , mIsFunsui(false)
    , mPreFunsuiSpeedX(0.0f)
    , mGroundPosY(0.0f)
    , _1abc(0)
{
}
