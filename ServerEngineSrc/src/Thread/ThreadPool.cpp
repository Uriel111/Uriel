#include <Common/Logging.h>
#include <Thread/ThreadPool.h>
#include <exception>
#include <iostream>
#include <numeric>
namespace Uriel {
ThreadPool::ThreadPool(unsigned short threadNums, unsigned int maxFuncNums) : threadNums_(threadNums), notEmpty_(), notFull_(), maxFuncNums_(maxFuncNums), isRunning_(false) {}

ThreadPool::ThreadPool() : ThreadPool(0, std::numeric_limits<unsigned int>::max()) {}

ThreadPool::ThreadPool(unsigned short threadNums) : ThreadPool(threadNums, std::numeric_limits<unsigned int>::max()) {}

void ThreadPool::Poll() {
	if (!isRunning_.GetValue() && threads_.empty()) {
		return;
	}
	while (!funcs_.empty()) {
		auto func = funcs_.front();
		funcs_.pop();
		func();
		/* code */
	}
}

ThreadPool::~ThreadPool() {
	for (auto &thread : threads_) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void ThreadPool::SetThreadNums(unsigned short threadNums) {
	threadNums_ = threadNums;
}

const unsigned int ThreadPool::FuncSize() const {
	return funcs_.size();
}

void ThreadPool::AddTask(Function &&func) {
	LockGuard lock(mutex_);
	while (IsFull()) {
		notFull_.Wait(lock);
		/* code */
	}

	funcs_.emplace(func);
	notEmpty_.NotifyOne();
}

ThreadPool::Function ThreadPool::GetTask() {
	LockGuard lock(mutex_);
	while (IsEmpty() && isRunning_.GetValue()) {
		notEmpty_.Wait(lock);
		/* code */
	}
	Function func = []() {};
	if (!IsEmpty()) {
		func = funcs_.front();
		funcs_.pop();
		notFull_.NotifyOne();
	}
	return func;
}

const bool ThreadPool::IsFull() const {
	return funcs_.size() == maxFuncNums_;
}

const bool ThreadPool::IsEmpty() const {
	return funcs_.empty();
}

void ThreadPool::RunInSubThread() {

	while (isRunning_.GetValue()) {
		Function func = GetTask();
		func();
		/* code */
	}
}

void ThreadPool::Start() {
	isRunning_ = true;
	for (unsigned short index = 0; index != threadNums_; ++index) {
		threads_.emplace_back(std::thread(std::bind(&ThreadPool::RunInSubThread, this)));
	}
}

void ThreadPool::Stop() {

	isRunning_ = false;
	notEmpty_.NotifyAll();
	notFull_.NotifyAll();
}

} // namespace Uriel