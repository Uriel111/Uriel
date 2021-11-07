#include <Common/Logging.h>
#include <Thread/Condition.h>
namespace Uriel {

Condition::Condition(Mutex &mutex) : mutex_(mutex) {
	if (pthread_cond_init(&cond_, nullptr)) {
		LogError("failed to cond init");
	}
}

Condition::~Condition() {
	if (pthread_cond_destroy(&cond_)) {
		LogError("failed to cond destroy");
	}
}

void Condition::Wait() {

	if (pthread_cond_wait(&cond_, mutex_.GetRawMutex())) {
		LogError("failed to wait cond");
	}
}

void Condition::Notify() {
	if (pthread_cond_signal(&cond_)) {
		LogError("failed to notify");
	}
}

void Condition::NotifyAll() {
	if (pthread_cond_broadcast(&cond_)) {
		LogError("failed to notify all");
	}
}
} // namespace Uriel