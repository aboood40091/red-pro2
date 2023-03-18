#pragma once

#include <basis/seadTypes.h>

class DVEnvTagMgr
{
public:
    DVEnvTagMgr();

    void initialize(const void* p_file);

private:
    u8  _0;
};
static_assert(sizeof(DVEnvTagMgr) == 1);
