#include <Thread/AsyncMgr.h>
#include <fmt/printf.h>
namespace Uriel {
void AsyncMgr::AsyncCall(const std::string &name, std::function<void()> &&func) {
	if (pollMap_.find(name) == pollMap_.end()) {
		return;
	}
	pollMap_[name]->AddTask(std::move(func));
}

void AsyncMgr::AsyncPost(std::function<void()> &&func) {
	mainPoll_->AddTask(std::move(func));
}

void AsyncMgr::AsyncPoll() {
	mainPoll_->Poll();
}

void AsyncMgr::RegNameWorker(const std::string &name) {
	if (pollMap_.find(name) != pollMap_.end())
		return;
	// pollMap_[name] = std::move( ThreadPoll(2));
	pollMap_[name] = std::make_shared<ThreadPoll>(2);
	pollMap_[name]->Start();
}

AsyncMgr::AsyncMgr() : mainPoll_(std::make_shared<ThreadPoll>()) {
	mainPoll_->Start();
}

AsyncMgr::~AsyncMgr() {
	mainPoll_->Stop();
	for (auto &pair : pollMap_) {
		pair.second->Stop();
	}
}

AsyncMgr &AsyncMgr::Instance() {
	static AsyncMgr inst_;
	return inst_;
}

} // namespace Uriel