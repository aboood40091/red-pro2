#include <agl/aglDisplayList.h>

#ifdef cafe
#include <cafe.h>
#endif // cafe

namespace agl {

DisplayList::DisplayList()
{
    clear();
}

DisplayList::~DisplayList()
{
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

void DisplayList::clear()
{
    mpBuffer = NULL;
    mBufferMaxSize = 0;
    mDLSize = 0;
}

bool DisplayList::beginDisplayList()
{
    mDLSize = 0;

#ifdef cafe
    GX2BeginDisplayListEx(mpBuffer, mBufferMaxSize, GX2_DISABLE);
    return true;
#else
    return false;
#endif
}

size_t DisplayList::endDisplayList()
{
#ifdef cafe
    void* dl;
    size_t size;
    GX2GetCurrentDisplayList(&dl, &size);

    size_t dl_size = GX2EndDisplayList(dl);
    dl = (void*)((uintptr_t)dl + dl_size);

    mDLSize = (uintptr_t)dl - (uintptr_t)mpBuffer;
    return mDLSize;
#else
    return 0;
#endif
}

size_t DisplayList::suspend(void** p_dl)
{
    // SEAD_ASSERT(p_dl != nullptr);

    *p_dl = NULL;
    size_t size = 0;

#ifdef cafe
    if (GX2GetCurrentDisplayList(p_dl, &size) == GX2_TRUE)
    {
        size_t dl_size = GX2EndDisplayList(*p_dl);

        size -= dl_size;
        *p_dl = (void*)((uintptr_t)*p_dl + dl_size);
    }
#endif //cafe

    return size;
}
void DisplayList::resume(void* dl, size_t size)
{
#ifdef cafe
    if (dl != NULL)
        GX2BeginDisplayListEx(dl, size, GX2_DISABLE);
#endif // cafe
}

}
