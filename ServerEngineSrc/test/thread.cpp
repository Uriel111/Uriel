#include <Thread/AsyncMgr.h>
#include <Thread/ThreadPoll.h>
#include <fmt/printf.h>
#include <iostream>
#include <memory>
#include <thread>
using namespace Uriel;

int main() {
	AsyncMgrInst.RegNameWorker("Test");
	AsyncMgrInst.AsyncCall("Test", []() { fmt::print("hello workd\n"); });
	// AsyncMgr::Instance().AsyncCall();
	AsyncMgrInst.AsyncCall("test", []() { fmt::print("hello workd\n"); });
	AsyncMgrInst.AsyncCall("Test", []() { AsyncMgrInst.AsyncPost([]() { fmt::print("hello world 2\n"); }); });
	std::this_thread::sleep_for(std::chrono::seconds(1));
	AsyncMgrInst.AsyncPoll();
	// fmt::print("end!\n");

	// while (1) {
	// }
}