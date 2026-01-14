#include <player/PlayerBase.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectCoinEndWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClearGoalWait)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClear)
CREATE_STATE_VIRTUAL_ID_BASE(PlayerBase, SubjectClearWait)
