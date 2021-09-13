#pragma once
#include <Thread/ThreadPoll.h>
#include <string>
#include <unordered_map>

namespace Uriel {
#define AsyncMgrInst (AsyncMgr::Instance())
class AsyncMgr {
public:
	using ThreadPollPtr = std::shared_ptr<ThreadPoll>;
	static AsyncMgr &Instance();
	void RegNameWorker(const std::string &name);
	void AsyncCall(const std::string &name, std::function<void()> &&func);
	void AsyncPost(std::function<void()> &&func);
	void AsyncPoll();
	~AsyncMgr();

private:
	AsyncMgr();

	ThreadPollPtr mainPoll_;
	std::unordered_map<std::string, ThreadPollPtr> pollMap_;
};
} // namespace Uriel