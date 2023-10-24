#include <graphics/CaptureRenderBuffer.h>

void CaptureRenderBuffer::initColor(sead::Heap* heap)
{
    mColorTexture.initialize(mInfo.format, mInfo.width, mInfo.height, 1);
    mpColorImage = new (heap, mColorTexture.getAlignment()) u8[mColorTexture.getImageByteSize()];
    DCFlushRange(mpColorImage, mColorTexture.getImageByteSize());
    mColorTexture.setImagePtr(mpColorImage);
    mColorTarget.applyTextureData(mColorTexture);
    mRenderBuffer.setRenderTargetColor(&mColorTarget);
}

void CaptureRenderBuffer::initDepth(sead::Heap* heap)
{
    mDepthTexture.initialize(agl::cTextureFormat_Depth_32, mInfo.width, mInfo.height, 1);
    mpDepthImage = new (heap, mDepthTexture.getAlignment()) u8[mDepthTexture.getImageByteSize()];
    DCFlushRange(mpDepthImage, mDepthTexture.getImageByteSize());
    mDepthTexture.setImagePtr(mpDepthImage);
    mDepthTarget.applyTextureData(mDepthTexture);
    mRenderBuffer.setRenderTargetDepth(&mDepthTarget);
}
