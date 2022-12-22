#pragma once

#include <prim/seadSafeString.h>

namespace sead {

class ReadStream;

}

class EnvSetReader
{
public:
    static void read(const sead::SafeString& path, sead::Heap* heap = nullptr);

private:
    static void read_(sead::ReadStream& stream, sead::Heap* heap);
};
