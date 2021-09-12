#pragma once
#include <pthread.h>
#include <thread>
namespace Uriel {

class Mutex {
public:
	Mutex();

	~Mutex();
	void Lock();
	void UnLock();
	pthread_mutex_t *GetRawMutex();

private:
	pthread_mutex_t mutex_;

private:
};

class MutualLock {
public:
	MutualLock(Mutex &mutex);
	~MutualLock();

private:
	Mutex &mutex_;
};
} // namespace Uriel