#pragma once

#include <input/SeadController.h>

#include <controller/seadControllerWrapper.h>

class SeadControllerWrapper : public sead::ControllerWrapper
{
public:
    static const u8 cPadConfig[18];

public:
    SeadControllerWrapper();
    virtual ~SeadControllerWrapper();

    virtual void calc(u32, bool);

    void registerWith(GameController::Id id);
};
static_assert(sizeof(SeadControllerWrapper) == sizeof(sead::ControllerWrapper));
