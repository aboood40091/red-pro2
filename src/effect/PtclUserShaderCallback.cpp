#include <effect/PtclUserShaderCallback.h>

#include <mc/seadCoreInfo.h>

static s32 s_area_loop_rep_num[nw::eft::EFT_CPU_CORE_MAX];

void PtclUserShaderCallback::setAreaLoopRepeatNum_(s32 data_idx, s32 rep_num)
{
    s_area_loop_rep_num[data_idx] = rep_num;
}

s32 PtclUserShaderCallback::getAreaLoopRepeatNum_(s32 data_idx)
{
    return s_area_loop_rep_num[data_idx];
}

f32 PtclUserShaderCallback::getRand_(u32& seed)
{
    seed = 1664525 * seed + 1013904223;
    seed = 1664521 * seed + 1013904223;
    seed = 1664525 * seed + 1013904221;
    f32 ret = (f32)seed / (f32)0xffffffff;
    return ret;
}

void PtclUserShaderCallback::areaLoopDrawOverrideCallback(nw::eft::ShaderDrawOverrideArg& arg)
{
    const nw::eft::EmitterInstance* emitter = arg.emitter;
    nw::eft::Renderer* renderer = arg.renderer;

    s32 loopNum = static_cast<s32>(renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_RepeatNum)) + 1;
    for (s32 i = 0; i < loopNum; ++i)
    {
        setAreaLoopRepeatNum_(sead::CoreInfo::getCurrentCoreId(), i);
        renderer->EntryParticleFromCallback(emitter, arg.cacheFlush, arg.userParam);
    }
}

void PtclUserShaderCallback::areaLoopRenderStateSetCallback(nw::eft::RenderStateSetArg& arg)
{
    s32 coreId = sead::CoreInfo::getCurrentCoreId();
    const nw::eft::EmitterInstance* emitter = arg.emitter;
    nw::eft::Renderer* renderer = arg.renderer;

    nw::eft::ParticleShader* shader = renderer->GetShader(emitter);
    if (shader == nullptr)
        return;

    AreaLoopShaderVtxUniform* uniform = static_cast<AreaLoopShaderVtxUniform*>(renderer->AllocFromDoubleBuffer(sizeof(AreaLoopShaderVtxUniform)));
    if (uniform == nullptr)
        return;

    f32 box_size_x  = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxScaleX);
    f32 box_size_y  = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxScaleY);
    f32 box_size_z  = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxScaleZ);
    f32 box_alpha_x = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxAlphaRatioX);
    f32 box_alpha_y = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxAlphaRatioY);
    f32 box_alpha_z = renderer->GetUserShaderParam(emitter, cAreaLoopShaderParam_BoxAlphaRatioZ);

    if (box_size_x  <= 0.0f) box_size_x  = 0.0001f;
    if (box_size_y  <= 0.0f) box_size_y  = 0.0001f;
    if (box_size_z  <= 0.0f) box_size_z  = 0.0001f;
    if (box_alpha_x <= 0.0f) box_alpha_x = 0.00001f;
    if (box_alpha_y <= 0.0f) box_alpha_y = 0.00001f;
    if (box_alpha_z <= 0.0f) box_alpha_z = 0.00001f;

    uniform->vec0.x = emitter->emitterSRT.m[0][3];
    uniform->vec0.y = emitter->emitterSRT.m[1][3];
    uniform->vec0.z = emitter->emitterSRT.m[2][3];
    uniform->vec0.w = 0.0f;

    uniform->vec1.x = box_size_x;
    uniform->vec1.y = box_size_y;
    uniform->vec1.z = box_size_z;
    uniform->vec1.w = 0.0f;

    uniform->vec2.x = 1.0f / box_size_x;
    uniform->vec2.y = 1.0f / box_size_y;
    uniform->vec2.z = 1.0f / box_size_z;
    uniform->vec2.w = 0.0f;

    f32 range = box_size_x * 1333.0f;
    u32 seed = 1664525 * ((16384 + getAreaLoopRepeatNum_(coreId)) * 3) + 1013904223;
    getRand_(seed);
    getRand_(seed);
    uniform->vec3.x = range * (0.2f + getRand_(seed));
    uniform->vec3.y = range * (0.2f + getRand_(seed));
    uniform->vec3.z = range * (0.2f + getRand_(seed));
    uniform->vec3.w = 0.0f;

    uniform->vec4.x = box_alpha_x;
    uniform->vec4.y = box_alpha_y;
    uniform->vec4.z = box_alpha_z;
    uniform->vec4.w = 0.0f;

    GX2EndianSwap(uniform, sizeof(AreaLoopShaderVtxUniform));
    if (arg.cacheFlush)
        GX2Invalidate(GX2_INVALIDATE_CPU_UNIFORM_BLOCK, uniform, sizeof(AreaLoopShaderVtxUniform));

    shader->SetUserVertexUniformBlock(nw::eft::ParticleShader::UNIFORM_BLOCK_USER_VERTEX_ID_0 , "AreaLoopShaderVtxUniform" , uniform);
}
