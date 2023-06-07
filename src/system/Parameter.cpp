#include <system/Parameter.h>

#include <stream/Stream.h>

ParameterBase::ParameterBase(ParameterListBase* p_list, const char* name)
    : mName(name)
    , mListNode(this)
{
    if (p_list != nullptr)
        p_list->pushBack(&mListNode);
}

ParameterBase::~ParameterBase()
{
    mListNode.erase();
}

void ParameterBase::read(ReadStream& stream)
{
}

template <>
void Parameter<u32>::read(ReadStream& stream)
{
    mValue = stream.readU32();
    RIO_LOG("u32: %u\n", mValue);
}

template <>
void Parameter<f32>::read(ReadStream& stream)
{
    mValue = stream.readF32();
    RIO_LOG("f32: %f\n", mValue);
}

template <>
void Parameter<rio::Vector2f>::read(ReadStream& stream)
{
    mValue.x = stream.readF32();
    mValue.y = stream.readF32();
    RIO_LOG("rio::Vector2f: x: %f, y: %f\n", mValue.x, mValue.y);
}
