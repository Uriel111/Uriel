#pragma once
#include <Common/NoCopyable.hpp>
#include <condition_variable>
#include <Thread/Lock.h>
#include <functional>
namespace Uriel {
class Condition : public NoCopyable {
public:
	Condition();
	~Condition();
	void Wait(SpinLock& spinLock,  std::function<bool()>&& func);
	void Wait(SpinLock& spinLock);
	void Wait(LockGuard& lockGuard);
	void NotifyOne();
	void NotifyAll();

private:
	std::condition_variable condition_;
};
} // namespace Uriel