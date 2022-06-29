#pragma once
#include <Thread/Condition.h>
#include <Thread/ReadWriteLock.h>
#include <functional>
#include <queue>
#include <thread>
#include <vector>
namespace Uriel {
class ThreadPool : public NoCopyable {
public:
	using Function = std::function<void()>;
	ThreadPool(unsigned short threadNums, unsigned int maxFuncNums);
	ThreadPool(); // main thread poll, run in main thread
	ThreadPool(unsigned short threadNums);
	// ThreadPoll(ThreadPoll &&threadPoll);
	~ThreadPool();
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