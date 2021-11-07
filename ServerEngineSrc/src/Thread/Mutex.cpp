#include <Common/Logging.h>
#include <Thread/Mutex.h>
namespace Uriel {
Mutex::Mutex() {
	if (pthread_mutex_init(&mutex_, nullptr)) {
		LogError("failed to mutex init ");
	}
}
Mutex::~Mutex() {
	if (pthread_mutex_destroy(&mutex_)) {
		LogError("failed to destroy mutex");
	}
}
void Mutex::Lock() {
	if (pthread_mutex_lock(&mutex_)) {
		LogError("failed to lock mutex");
	}
}

void Mutex::UnLock() {
	if (pthread_mutex_unlock(&mutex_)) {
		LogError("failed to unlock mutex");
	}
}

pthread_mutex_t *Mutex::GetRawMutex() {
	return &mutex_;
}

MutualLock::MutualLock(Mutex &mutex) : mutex_(mutex) {
	mutex_.Lock();
}

MutualLock::~MutualLock() {
	mutex_.UnLock();
}

} // namespace Uriel