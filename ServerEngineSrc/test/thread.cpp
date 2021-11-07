#include <Common/Logging.h>
#include <Thread/AsyncMgr.h>
#include <Thread/ThreadPoll.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <thread>
using namespace Uriel;
void print(int a, int b) {
	std::cout << a << " " << b << std::endl;
}
template <typename... T> void test(T... args) {
	print(args...);
}

int main() {
	// AsyncMgrInst.RegNameWorker("Test");
	// AsyncMgrInst.AsyncCall("Test", []() { fmt::print("hello workd\n"); });
	// // AsyncMgr::Instance().AsyncCall();
	// AsyncMgrInst.AsyncCall("test", []() { fmt::print("hello workd\n"); });
	// AsyncMgrInst.AsyncCall("Test", []() { AsyncMgrInst.AsyncPost([]() { fmt::print("hello world 2\n"); }); });
	// //fmt::printf
	// test(1, 2, 3, 5);
	char test[3];
	LogWarn("1111%s", "hello");
	// std::this_thread::sleep_for(std::chrono::seconds(1));
	// AsyncMgrInst.AsyncPoll();
	// fmt::print("end!\n");

	// while (1) {
	// }
}