#include <agl/aglDisplayList.h>

namespace agl {

DisplayList::DisplayList()
{
    clear();
}

DisplayList::~DisplayList()
{
}

void DisplayList::clear()
{
    mpBuffer = NULL;
    mBufferMaxSize = 0;
    mDLSize = 0;
}

void DisplayList::setBuffer(u8* buffer, size_t size)
{
    if (buffer)
    {
       mpBuffer = buffer;
       mBufferMaxSize = size;
    }
    else
    {
        mpBuffer = NULL;
        mBufferMaxSize = 0;
    }
}

}
