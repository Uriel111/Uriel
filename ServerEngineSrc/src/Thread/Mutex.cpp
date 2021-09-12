#include <Thread/Mutex.h>
#include <fmt/printf.h>
namespace Uriel {
Mutex::Mutex() {
	if (pthread_mutex_init(&mutex_, nullptr)) {
		fmt::print("failed to mutex init \n");
	}
}
Mutex::~Mutex() {
	if (pthread_mutex_destroy(&mutex_)) {
		fmt::print("failed to destroy mutex\n");
	}
}
void Mutex::Lock() {
	// fmt::print("lock!\n");
	if (pthread_mutex_lock(&mutex_)) {
		fmt::print("failed to lock mutex\n");
	}
}

void Mutex::UnLock() {
	if (pthread_mutex_unlock(&mutex_)) {
		fmt::print("failed to unlock mutex");
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