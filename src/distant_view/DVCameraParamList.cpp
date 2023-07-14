#include <distant_view/DVCameraParamList.h>

#include <stream/seadRamStream.h>

void DVCameraParamList::read(const void* file, u32 size)
{
    if (size == 0)
        return;

    sead::RamReadStream stream(file, size, sead::Stream::cBinary);
    stream.setBinaryEndian(sead::Endian::cLittle);

    read_(stream);
}

void DVCameraParamList::read_(sead::ReadStream& stream)
{
    while (!stream.isEOF())
    {
        sead::FixedSafeString<128> param_name;

        stream.readString(&param_name, stream.readU32());

        ParameterBase* parameter = getParam(param_name.cstr());
        if (parameter != nullptr)
        {
            stream.skip(4);
            parameter->read(stream);
        }
        else
        {
            stream.skip(stream.readS32());
        }
    }
}

ParameterBase* DVCameraParamList::getParam(const char* name) const
{
    for (iterator itr = begin(), itr_end = end(); itr != itr_end; ++itr)
    {
        ParameterBase* parameter = *itr;
        if (parameter->getName() == name)
            return parameter;
    }

    return nullptr;
}
