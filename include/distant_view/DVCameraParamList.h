#pragma once

#include <system/Parameter.h>

#include <string>

class DVCameraParamList : public ParameterListBase
{
public:
    DVCameraParamList()
    {
    }

    void read(const void* file, u32 size) override;

    ParameterBase* getParam(const std::string& name) const;

private:
    void read_(ReadStream& stream);
};
static_assert(sizeof(DVCameraParamList) == sizeof(ParameterListBase));
