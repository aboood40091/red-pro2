#include <game/AreaTask.h>
#include <scroll/BgScrollMgr.h>

BgScrollMgr* BgScrollMgr::sInstance = nullptr;

f32 BgScrollMgr::getBgCenterYPos() const
{
    // This makes it so that the BG Center Y position is always at the center of the screen when the player is standing at the bottom of the area
    // (Respecting the initial zoom)

    f32 zoom = mTrackingMgr->getZoomTargetMin();
    return AreaTask::instance()->getBound().getMin().y + zoom * 224 - zoom * 224 * 0.5f;
}
