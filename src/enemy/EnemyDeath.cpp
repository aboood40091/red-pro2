#include <enemy/Enemy.h>

const f32 Enemy::cDieFallInitSpeedY = 3.9f;
const f32 Enemy::cDieFallMaxFallSpeed = ENEMY_DEFAULT_MAX_FALL_SPEED;
const f32 Enemy::cDieFallGravity = 1.3f * Enemy::cDefaultGravity;

CREATE_STATE_VIRTUAL_ID_BASE(Enemy, DieFall)
