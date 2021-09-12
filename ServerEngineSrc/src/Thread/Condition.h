#pragma once
#include <Common/NoCopyable.hpp>
#include <Thread/Mutex.h>
#include <pthread.h>
namespace Uriel {
class Condition : public NoCopyable {
public:
	Condition(Mutex& mutex);
	~Condition();
	void Wait();
	void Notify();
	void NotifyAll();

private:
	pthread_cond_t cond_;
	Mutex &mutex_;
};
} // namespace Uriel