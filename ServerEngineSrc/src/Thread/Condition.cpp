#include <Common/Logging.h>
#include <Thread/Condition.h>
namespace Uriel {

Condition::Condition() {
	
}

Condition::~Condition() {
}

void Condition::Wait(SpinLock& spinLock,  std::function<bool()>&& func) {

	condition_.wait(spinLock, func);
}

void Condition::Wait(SpinLock& spinLock)
{
	condition_.wait(spinLock);
}

void Condition::Wait(LockGuard& lockGuard)
{
	condition_.wait(lockGuard.GetSpinLock());
}

void Condition::NotifyOne() {
	condition_.notify_one();
}

void Condition::NotifyAll() {
	condition_.notify_all();
}
} // namespace Uriel