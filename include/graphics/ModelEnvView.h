#pragma once

#include <common/aglUniformBlock.h>
#include <container/Buffer.h>
#include <math/rio_Matrix.h>

class ModelEnvView
{
public:
    struct Member
    {
        agl::UniformBlock::Type type;
        s32                     num;
    };
    static_assert(sizeof(Member) == 8);

    enum MemberIndex
    {
        cMemberIndex_View = 0,
        cMemberIndex_ViewProj,
        cMemberIndex_LightDiffDir,
        cMemberIndex_LightDiffColor,
        cMemberIndex_AmbColor,
        cMemberIndex_FogColor,
        cMemberIndex_FogStart,
        cMemberIndex_FogStartEndInv,
        cMemberIndex_Unk_8,
        cMemberIndex_Unk_9,
        cMemberIndex_Unk_10,
        cMemberNum
    };
    static_assert(cMemberNum == 11);

    static const Member cMember[cMemberNum];

    static constexpr s32 cLightObjMax = 8;
    static constexpr s32 cChannelMax = 2;
    static constexpr s32 cFogMax = 8;

public:
    ModelEnvView(u32 num_view);
    ~ModelEnvView();

    void setUniformData(s32 view_index, const rio::Matrix34f& view_mtx, const rio::Matrix44f& proj_mtx);

    s32 getViewNum() const { return mUniformBlock.size(); }
    const agl::UniformBlock& getUniformBlock(s32 view_index) const { return mUniformBlock[view_index]; }

private:
    Buffer<agl::UniformBlock>   mUniformBlock;
};
//static_assert(sizeof(ModelEnvView) == 0xC);
