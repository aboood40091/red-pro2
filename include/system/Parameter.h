#pragma once

#include <container/rio_TList.h>
#include <math/rio_Vector.h>

class ParameterBase;
class ReadStream;

class ParameterListBase : public rio::TList<ParameterBase*>
{
public:
    ParameterListBase()
    {
    }

    virtual void read(const void* file, u32 size) = 0;
};

class ParameterBase
{
public:
    ParameterBase(ParameterListBase* p_list, const char* name);
    virtual ~ParameterBase();

    virtual void read(ReadStream& stream);

    const char* getName() const { return mName; }

protected:
    const char*                     mName;
    rio::TListNode<ParameterBase*>  mListNode;
};
//static_assert(sizeof(ParameterBase) == 0x24);

template <typename T>
class Parameter : public ParameterBase
{
public:
    Parameter(const T& default_value, ParameterListBase* p_list, const char* name)
        : ParameterBase(p_list, name)
    {
        mValue = default_value;
    }

    virtual ~Parameter()
    {
    }

    void read(ReadStream& stream) override;

    void setValue(const T& value) { mValue = value; }
    const T& getValue() const { return mValue; }

    T& operator*() { return mValue; }
    const T& operator*() const { return mValue; }

    T* operator->() { return &mValue; }
    const T* operator->() const { return &mValue; }

private:
    T   mValue;
};

template <>
void Parameter<u32>::read(ReadStream& stream);

template <>
void Parameter<f32>::read(ReadStream& stream);

template <>
void Parameter<rio::Vector2f>::read(ReadStream& stream);

typedef Parameter<u32> ParamU32;
typedef Parameter<f32> ParamF32;
typedef Parameter<rio::Vector2f> ParamVec2;

//static_assert(sizeof(ParamU32)  == 0x28);
//static_assert(sizeof(ParamF32)  == 0x28);
//static_assert(sizeof(ParamVec2) == 0x2C);
