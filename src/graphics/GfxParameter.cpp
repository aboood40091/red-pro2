#include <graphics/GfxParameter.h>

GfxParameter* GfxParameter::sInstance = nullptr;

void GfxParameter::setDelegateForParameter(agl::utl::IParameterIO* p_param)
{
    p_param->setDelegate(mDelegateData);
}
