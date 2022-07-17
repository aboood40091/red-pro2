#pragma once

#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>

class ModelEnvView
{
public:
    ModelEnvView();

    s32 getViewNum() const { return mViewNum; }
    const agl::UniformBlock& getUniformBlock(s32 view_index) const { return mUniformBlock[view_index]; }

private:
    s32 mViewNum;
    sead::Buffer<agl::UniformBlock> mUniformBlock;
};
