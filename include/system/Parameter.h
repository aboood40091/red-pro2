#pragma once

#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace sead {

class ReadStream;

}

class ParameterBase;

class ParameterListBase : public sead::TList<ParameterBase*>
{
public:
    ParameterListBase()
    {
    }

    virtual void read(const void* file, u32 size) = 0;
};

class ParameterBase : public sead::IDisposer
{
public:
    ParameterBase(ParameterListBase* p_list, const char* name);
    virtual ~ParameterBase();

    virtual void read(sead::ReadStream& stream);

    const char* getName() const { return mName; }

protected:
    const char*                     mName;
    sead::TListNode<ParameterBase*> mListNode;
};
static_assert(sizeof(ParameterBase) == 0x24);

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

    void read(sead::ReadStream& stream) override;

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
void Parameter<u32>::read(sead::ReadStream& stream);

template <>
void Parameter<f32>::read(sead::ReadStream& stream);

template <>
void Parameter<sead::Vector2f>::read(sead::ReadStream& stream);

typedef Parameter<u32> ParamU32;
typedef Parameter<f32> ParamF32;
typedef Parameter<sead::Vector2f> ParamVec2;

static_assert(sizeof(ParamU32)  == 0x28);
static_assert(sizeof(ParamF32)  == 0x28);
static_assert(sizeof(ParamVec2) == 0x2C);
