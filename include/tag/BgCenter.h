#pragma once

#include <actor/ActorBase.h>

class BgCenter : public ActorBase
{
    SEAD_RTTI_OVERRIDE(BgCenter, ActorBase)

public:
    BgCenter(const ActorInitArg& arg);
    virtual ~BgCenter() { }

    const sead::Vector3f& getPosition() const
    {
        return mPosition;
    }

private:
    sead::Vector3f  mPosition;
};
static_assert(sizeof(BgCenter) == 0x5C);
