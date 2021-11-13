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
	ThreadPoll poll(3);
	poll.Start();
	for (int i = 0; i != 200; ++i)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
		for (int j = 0; j != 10; ++j)
			poll.AddTask([]() { LogInfo("111"); });
	}

	// poll.AddTask([]() { LogInfo("111"); });

	// std::this_thread::sleep_for(std::chrono::seconds(1));
	// AsyncMgrInst.AsyncPoll();
	// fmt::print("end!\n");

	// while (1) {
	// }
}