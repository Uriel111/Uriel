#include <Thread/Condition.h>
#include <fmt/printf.h>
namespace Uriel {

Condition::Condition(Mutex &mutex) : mutex_(mutex) {
	if (pthread_cond_init(&cond_, nullptr)) {
		fmt::print("failed to cond init\n");
	}
}

Condition::~Condition() {
	if (pthread_cond_destroy(&cond_)) {
		fmt::print("failed to cond destroy\n");
	}
}

void Condition::Wait() {

	if (pthread_cond_wait(&cond_, mutex_.GetRawMutex())) {
		fmt::print("failed to wait cond\n");
	}
}

void Condition::Notify() {
	if (pthread_cond_signal(&cond_)) {
		fmt::print("failed to notify\n ");
	}
}

void Condition::NotifyAll() {
	if (pthread_cond_broadcast(&cond_)) {
		fmt::print("failed to notify all\n");
	}
}
} // namespace Uriel