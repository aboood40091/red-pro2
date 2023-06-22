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
}

template <>
void Parameter<f32>::read(ReadStream& stream)
{
    mValue = stream.readF32();
}

template <>
void Parameter<rio::Vector2f>::read(ReadStream& stream)
{
    mValue.x = stream.readF32();
    mValue.y = stream.readF32();
}
