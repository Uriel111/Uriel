#include <Common/Logging.h>
#include <Thread/ThreadPoll.h>
#include <exception>
#include <iostream>
#include <numeric>
namespace Uriel {
ThreadPoll::ThreadPoll(unsigned short threadNums, unsigned int maxFuncNums) : threadNums_(threadNums), notEmpty_(), notFull_(), maxFuncNums_(maxFuncNums), isRunning_(false) {}

ThreadPoll::ThreadPoll() : ThreadPoll(0, std::numeric_limits<unsigned int>::max()) {}

ThreadPoll::ThreadPoll(unsigned short threadNums) : ThreadPoll(threadNums, std::numeric_limits<unsigned int>::max()) {}

void ThreadPoll::Poll() {
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

ThreadPoll::~ThreadPoll() {
	for (auto &thread : threads_) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void ThreadPoll::SetThreadNums(unsigned short threadNums) {
	threadNums_ = threadNums;
}

const unsigned int ThreadPoll::FuncSize() const {
	return funcs_.size();
}

void ThreadPoll::AddTask(Function &&func) {
	LockGuard lock(mutex_);
	while (IsFull()) {
		notFull_.Wait(lock);
		/* code */
	}

	funcs_.emplace(func);
	notEmpty_.NotifyOne();
}

ThreadPoll::Function ThreadPoll::GetTask() {
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

const bool ThreadPoll::IsFull() const {
	return funcs_.size() == maxFuncNums_;
}

const bool ThreadPoll::IsEmpty() const {
	return funcs_.empty();
}

void ThreadPoll::RunInSubThread() {

	while (isRunning_.GetValue()) {
		Function func = GetTask();
		func();
		/* code */
	}
}

void ThreadPoll::Start() {
	isRunning_ = true;
	for (unsigned short index = 0; index != threadNums_; ++index) {
		threads_.emplace_back(std::thread(std::bind(&ThreadPoll::RunInSubThread, this)));
	}
}

void ThreadPoll::Stop() {

	isRunning_ = false;
	notEmpty_.NotifyAll();
	notFull_.NotifyAll();
}

} // namespace Uriel