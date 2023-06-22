#include <distant_view/DVCameraParamList.h>

#include <stream/RamStream.h>

void DVCameraParamList::read(const void* file, u32 size)
{
    if (size == 0)
        return;

    RamReadStream stream(file, size, Stream::cBinary);
    stream.setBinaryEndian(false);

    read_(stream);
}

void DVCameraParamList::read_(ReadStream& stream)
{
    while (!stream.isEOF())
    {
        std::string param_name;
        param_name.reserve(128);

        stream.readString(&param_name, stream.readU32());

        ParameterBase* parameter = getParam(param_name);
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

ParameterBase* DVCameraParamList::getParam(const std::string& name) const
{
    for (iterator itr = begin(), itr_end = end(); itr != itr_end; ++itr)
    {
        ParameterBase* parameter = *itr;
        if (parameter->getName() == name)
            return parameter;
    }

    return nullptr;
}
