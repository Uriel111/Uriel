#include <Thread/ThreadPoll.h>
#include <fmt/printf.h>
#include <iostream>
#include <memory>
#include <thread>
using namespace Uriel;

int main() {
	ThreadPoll poll(5, 10);
	poll.AddTask(std::move([]() {
		fmt::print("1111\n");
		std::cout << "this thread is:" << std::this_thread::get_id() << std::endl;
	}));
	poll.AddTask([]() {
		fmt::print("1111\n");
		std::cout << "this thread is:" << std::this_thread::get_id() << std::endl;
	});
	poll.AddTask([]() {
		fmt::print("1111\n");
		std::cout << "this thread is:" << std::this_thread::get_id() << std::endl;
	});
	poll.AddTask([]() {
		fmt::print("1111\n");
		std::cout << "this thread is:" << std::this_thread::get_id() << std::endl;
	});
	poll.Start();
	poll.AddTask([]() {
		fmt::print("2222\n");
		std::cout << "this thread is:" << std::this_thread::get_id() << std::endl;
	});

	// while (1) {
	// }
}