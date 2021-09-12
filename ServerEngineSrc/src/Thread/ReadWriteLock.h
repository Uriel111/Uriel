#pragma once
#include <Common/NoCopyable.hpp>
#include <Thread/Condition.h>
namespace Uriel {
class ReadWriteLock {
public:
	ReadWriteLock();
	void ReadLock();
	void ReadUnLock();
	void WriteLock();
	void WriteUnLock();

private:
	Mutex mutex_;
	Condition cond_;
	int readNums_;
};

template <typename T> class ReadWriteLockValue : NoCopyable {
public:
	ReadWriteLockValue(T value);
	T GetValue();
	void SetValue(T &&value);
	void operator=(T &&value);

private:
	ReadWriteLock lock_;
	T value_;
};

} // namespace Uriel