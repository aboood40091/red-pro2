#include <graphics/ModelEnvView.h>

const ModelEnvView::Member ModelEnvView::cMember[] = {
    { agl::UniformBlock::cType_vec4,    3 },            // vec4     cView[ 3 ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     cViewProj[ 4 ];
    { agl::UniformBlock::cType_vec3,    cLightObjMax }, // vec3     cLightDiffDir[ LIGHT_OBJ_MAX ];
    { agl::UniformBlock::cType_vec4,    cLightObjMax }, // vec4     cLightDiffColor[ LIGHT_OBJ_MAX ];
    { agl::UniformBlock::cType_vec4,    cChannelMax },  // vec4     cAmbColor[ CHANNEL_MAX ];
    { agl::UniformBlock::cType_vec3,    cFogMax },      // vec3     cFogColor[ FOG_MAX ];
    { agl::UniformBlock::cType_float,   cFogMax },      // float    cFogStart[ FOG_MAX ];
    { agl::UniformBlock::cType_float,   cFogMax },      // float    cFogStartEndInv[ FOG_MAX ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     cShadowMtx[ 4 ];
    { agl::UniformBlock::cType_vec3,    cFogMax },      // vec3     cFogDir[ FOG_MAX ];
    { agl::UniformBlock::cType_vec4,    4 },            // vec4     cTexProjMtx[ 4 ];
};
