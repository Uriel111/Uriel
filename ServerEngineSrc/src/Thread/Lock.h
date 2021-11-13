#pragma once
#include <Common/NoCopyable.hpp>
#include <condition_variable>
#include <mutex>
#include <thread>
namespace Uriel {
using Mutex = std::mutex;
using SpinLock = std::unique_lock<std::mutex>;

class LockGuard : public NoCopyable {
public:
	LockGuard(Mutex &mutex) : mutex_(mutex), spinLock_(SpinLock(mutex_)) {}
	~LockGuard() {
		spinLock_.unlock();
	}

	SpinLock &GetSpinLock() {
		return spinLock_;
	}

private:
	Mutex &mutex_;
	SpinLock spinLock_;
};
} // namespace Uriel