#include <enemy/Enemy.h>

void Enemy::changeState(const StateID& state_id)
{
    if (mStateMgr.getStateMethod().isSubStateMethod())
    {
        mStateMgr.getStateMethod().returnToMainStateMethod();
        mStateMgr.getStateMethod().replaceStateMethod(state_id);
    }
    else
    {
        mStateMgr.changeState(state_id);
    }
}
