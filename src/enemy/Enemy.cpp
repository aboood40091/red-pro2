#include <enemy/Enemy.h>

void Enemy::changeState(const StateID& state_id)
{
    if (mStateMgr.isSubState())
    {
        mStateMgr.returnState();
        mStateMgr.replaceState(state_id);
    }
    else
    {
        mStateMgr.changeState(state_id);
    }
}
