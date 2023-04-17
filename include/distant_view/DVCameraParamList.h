#pragma once

#include <system/Parameter.h>

class DVCameraParamList : public ParameterListBase
{
public:
    DVCameraParamList()
    {
    }

    void read(const void* file, u32 size) override;

    ParameterBase* getParam(const char* name) const;

private:
    void read_(sead::ReadStream& stream);
};
static_assert(sizeof(DVCameraParamList) == sizeof(ParameterListBase));
