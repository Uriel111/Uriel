#pragma once
#include <Network/AsyncIO/Acceptor.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <vector>
namespace Uriel {
#define EPOLL_METHOD EPOLLET
class Epollor : Acceptor {
public:
	Epollor();
	~Epollor();
	void Run();
	bool AddReadEvent(int sockfd);
	bool AddWriteEvent(int sockfd);
	bool DelReadEvent(int sockfd);
	bool DelWriteEvent(int sockfd);
	epoll_event *GetEvents() const;

protected:
	std::unordered_map<int, epoll_event> eventMap_;
	std::vector<epoll_event> events_;
	int epollFd_;
};
} // namespace Uriel