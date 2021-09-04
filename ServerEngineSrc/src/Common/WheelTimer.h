#pragma once
namespace Uriel
{
class WheelTimerMgr{
	static WheelTimerMgr& Instance();
	~WheelTimerMgr();

	private:
	WheelTimerMgr();
};
}