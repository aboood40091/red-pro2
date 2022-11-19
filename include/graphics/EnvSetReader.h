#pragma once

#include <prim/seadSafeString.h>

namespace sead {

class ReadStream;

}

class EnvSetReader
{
public:
    static void read(const sead::SafeString& path, sead::Heap* heap = NULL);

private:
    static void read(sead::ReadStream& stream, sead::Heap* heap);
};
