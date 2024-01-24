#include <graphics/GfxParameter.h>

GfxParameter* GfxParameter::sInstance = nullptr;

void GfxParameter::setDelegateForParameter(agl::utl::IParameterIO* p_param)
{
    p_param->setDelegate(mDelegateData);
}

void* GfxParameter::getAglEnvBinary(const sead::SafeString& name, sead::Heap* heap) const
{
    return getFileFromPack_(
        sead::FormatFixedSafeString<260>(
            "%s.baglenv",
            name.cstr()
        ),
        heap
    );
}

void* GfxParameter::getAglLmapBinary(const sead::SafeString& name, sead::Heap* heap) const
{
    return getFileFromPack_(
        sead::FormatFixedSafeString<260>(
            "%s.bagllmap",
            name.cstr()
        ),
        heap
    );
}

void* GfxParameter::getFileFromPack_(const sead::SafeString& filename, sead::Heap* heap) const
{
    return mpPackArc->getFile(filename);
}
