#include <enemy/PataKuribo.h>

PataKuribo::PataKuribo(const ActorCreateParam& param)
    : KuriboBase(param)
    , mpBlendModelWing(nullptr)
    , mWingRootPos(0.0f, 0.0f, 0.0f)
    , _1a98(0)
    , _1a99(0)
    , _1a9a(0)
    , mHasWing(true)
    , mIsNotStartInWalkAnm(false)
{
}
