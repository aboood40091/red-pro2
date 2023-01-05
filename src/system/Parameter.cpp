#define override
#include <system/Parameter.h>

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
Parameter<u32>::~Parameter()
{
}

template <>
Parameter<f32>::~Parameter()
{
}

template <>
Parameter<sead::Vector2f>::~Parameter()
{
}
