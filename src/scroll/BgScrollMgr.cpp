#include <game/AreaTask.h>
#include <scroll/BgScrollMgr.h>

BgScrollMgr* BgScrollMgr::sInstance = nullptr;

f32 BgScrollMgr::getBgCenterYPos() const
{
    // This makes it so that the BG Center Y position is always at the center of the screen when the player is standing at the bottom of the area
    // (Respecting the initial zoom)

    f32 zoom_multiplier = mTrackingMgr->getCurrentZoomMultiplier();
    return AreaTask::instance()->getBound().getMin().y + zoom_multiplier * 224 - zoom_multiplier * 224 * 0.5f;
}
