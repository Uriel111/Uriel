#include <Thread/ReadWriteLock.h>
#include <fmt/printf.h>
#include <numeric>
namespace Uriel {
ReadWriteLock::ReadWriteLock() : cond_(mutex_), readNums_(0) {}
template class ReadWriteLockValue<bool>;
void ReadWriteLock::ReadLock() {
	MutualLock lock(mutex_);
	while (readNums_ < 0) {
		cond_.Wait();
		/* code */
	}
	readNums_++;
}

void ReadWriteLock::ReadUnLock() {
	MutualLock lock(mutex_);
	if (--readNums_ == 0)
		cond_.Notify();
}

void ReadWriteLock::WriteLock() {
	MutualLock lock(mutex_);
	while (readNums_ > 0) {
		cond_.Wait();
		/* code */
	}
	readNums_ = -1;
}

void ReadWriteLock::WriteUnLock() {
	MutualLock lock(mutex_);
	readNums_ = 0;
	cond_.NotifyAll();
}
template <typename T> ReadWriteLockValue<T>::ReadWriteLockValue(T value) : value_(value) {}

template <typename T> void ReadWriteLockValue<T>::SetValue(T &&value) {
	lock_.WriteLock();
	value_ = value;
	lock_.WriteUnLock();
}

template <typename T> T ReadWriteLockValue<T>::GetValue() {
	lock_.ReadLock();
	T value = value_;
	lock_.ReadUnLock();
	return std::move(value);
}
template <typename T> void ReadWriteLockValue<T>::operator=(T &&value) {
	lock_.WriteLock();
	value_ = value;
	lock_.WriteUnLock();
}

} // namespace Uriel