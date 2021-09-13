#pragma once
#include <Thread/Condition.h>
#include <Thread/Mutex.h>
#include <Thread/ReadWriteLock.h>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
namespace Uriel {
class ThreadPoll : public NoCopyable {
public:
	using Function = std::function<void()>;
	ThreadPoll(unsigned short threadNums, unsigned int maxFuncNums);
	ThreadPoll(); // main thread poll, run in main thread
	ThreadPoll(unsigned short threadNums);
	// ThreadPoll(ThreadPoll &&threadPoll);
	~ThreadPoll();
	void Start();
	void Stop();
	void Poll();
	void AddTask(Function &&func_);
	void SetThreadNums(unsigned short threadNums);
	const unsigned int FuncSize() const;

private:
	const bool IsFull() const;
	const bool IsEmpty() const;
	Function GetTask();
	void RunInSubThread();
	unsigned short threadNums_;
	unsigned int maxFuncNums_;
	ReadWriteLockValue<bool> isRunning_;
	Condition notEmpty_;
	Condition notFull_;
	Mutex mutex_;
	std::vector<std::thread> threads_;
	std::queue<Function> funcs_;
};
} // namespace Uriel