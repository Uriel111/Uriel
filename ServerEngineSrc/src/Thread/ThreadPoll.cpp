#include <Thread/ThreadPoll.h>
#include <exception>
#include <fmt/printf.h>
#include <iostream>
namespace Uriel {
ThreadPoll::ThreadPoll(unsigned short threadNums, unsigned int maxFuncNums) : threadNums_(threadNums), notEmpty_(mutex_), notFull_(mutex_), maxFuncNums_(maxFuncNums), isRunning_(false) {}

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
	MutualLock lock(mutex_);
	while (IsFull()) {
		notFull_.Wait();
		/* code */
	}

	funcs_.emplace(func);
	notEmpty_.Notify();
}

ThreadPoll::Function ThreadPoll::GetTask() {
	MutualLock lock(mutex_);
	while (IsEmpty()) {
		notEmpty_.Wait();
		/* code */
	}
	Function func = funcs_.front();
	funcs_.pop();
	// fmt::print("cur func num2:{}\n", funcs_.size());
	notFull_.Notify();
	return func;
}

const bool ThreadPoll::IsFull() const {
	return funcs_.size() == maxFuncNums_;
}

const bool ThreadPoll::IsEmpty() const {
	return funcs_.empty();
}

void ThreadPoll::RunInSubThread() {
	fmt::print("run is subthread\n");
	while (isRunning_.GetValue()) {
		Function func = GetTask();
		// fmt::print("get task\n");
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
}

} // namespace Uriel