#include "WheelTimer.h"
namespace Uriel {
WheelTimerMgr &WheelTimerMgr::Instance() {
	static WheelTimerMgr inst_;
	return inst_;
}

WheelTimerMgr::WheelTimerMgr() {}

WheelTimerMgr::~WheelTimerMgr() {}
} // namespace Uriel