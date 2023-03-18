#pragma once

#include <effect/EffectID.h>

#include <math/seadMatrix.h>
#include <math/seadVector.h>

class FollowEffect;
class LevelEffect;

class EffectCreateUtil
{
    // NSMBW: mEf + dEf

public:
    static bool createEffect(EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
    static bool createEffect(EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);

  //static bool createEffect_level(LevelEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                              // Deleted
  //static bool createEffect_level(LevelEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                       // Deleted

  //static bool createEffect_follow(FollowEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                            // Deleted
  //static bool createEffect_follow(FollowEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                     // Deleted

  //static bool createEffect_change(EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                                                    // Deleted
  //static bool createEffect_change(EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                                             // Deleted

  //static bool createEffect_level_change(LevelEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                       // Deleted
  //static bool createEffect_level_change(LevelEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                // Deleted

  //static bool createEffect_follow_change(FollowEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                     // Deleted
  //static bool createEffect_follow_change(FollowEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                              // Deleted

    static bool createPlayerEffect(s32 player_no, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
  //static bool createPlayerEffect(s32 player_no, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                               // Deleted

    static bool createPlayerEffect(s32 player_no, LevelEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
    static bool createPlayerEffect(s32 player_no, LevelEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);

    static bool createPlayerEffect(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);
  //static bool createPlayerEffect(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                       // Deleted

  //static bool createPlayerEffect_change(s32 player_no, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);                               // Deleted
  //static bool createPlayerEffect_change(s32 player_no, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                                        // Deleted

  //static bool createPlayerEffect_change(s32 player_no, LevelEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);        // Deleted
  //static bool createPlayerEffect_change(s32 player_no, LevelEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                 // Deleted

  //static bool createPlayerEffect_change(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Vector3f& trans, const sead::Vector3u& rotat, const sead::Vector3f& scale);       // Deleted
  //static bool createPlayerEffect_change(s32 player_no, FollowEffect* p_effect, EffectID id, const sead::Matrixf& mtx, bool mtx_has_scale);                                                // Deleted
};
