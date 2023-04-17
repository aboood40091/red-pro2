#include <system/Parameter.h>

#include <stream/seadStream.h>

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

void ParameterBase::read(sead::ReadStream& stream)
{
}

template <>
void Parameter<u32>::read(sead::ReadStream& stream)
{
    mValue = stream.readU32();
}

template <>
void Parameter<f32>::read(sead::ReadStream& stream)
{
    mValue = stream.readF32();
}

template <>
void Parameter<sead::Vector2f>::read(sead::ReadStream& stream)
{
    mValue.x = stream.readF32();
    mValue.y = stream.readF32();
}
