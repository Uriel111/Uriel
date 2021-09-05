#include <Network/AsyncIO/Epollor.h>
#include <fmt/printf.h>
#include <sys/unistd.h>
namespace Uriel {
Epollor::Epollor() : epollFd_(epoll_create(1024)) {
	AddReadEvent(socket_.GetSocketfd());
}
Epollor::~Epollor() {
	close(epollFd_);
}

void Epollor::Run() {
	int n = epoll_wait(epollFd_, events_.data(), events_.size(), -1);
	if (n == -1) {
		perror("epoll wait error");
		return;
	}
	for (int i = 0; i != n; ++i) {
		if (events_[i].events && EPOLLIN) {
			if (events_[i].data.fd == socket_.GetSocketfd()) {
				int connectId = Accept();
				AddReadEvent(connectId);
				fmt::print("Get a new connection:{}\n", connectId);
			}
			else {
				String msg = Recv(events_[i].data.fd);
				if (msg.errorNo_ == TRY_AGAIN) {
					fmt::print("get msg:{}\n", msg);
				}
				else if (msg.errorNo_ == LOST_CONNECTION) {
					fmt::print("lose connection:{}\n", static_cast<int>(events_[i].data.fd));
					DelWriteEvent(events_[i].data.fd);
					DelReadEvent(events_[i].data.fd);
					close(events_[i].data.fd);
				}
				else {
					perror("recv error occur\n");
				}
			}
		}
	}
}

bool Epollor::AddReadEvent(int sockfd) {
	if (eventMap_.find(sockfd) == eventMap_.end()) {
		eventMap_[sockfd] = epoll_event();
		eventMap_[sockfd].events = EPOLLIN | EPOLL_METHOD;
		eventMap_[sockfd].data.fd = sockfd;
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_ADD, sockfd, &eventMap_[sockfd])) {
			events_.resize(eventMap_.size());
			return true;
		}
		eventMap_.erase(sockfd);
		perror("FailedToAddReadEvent");
		return false;
	}
	else {
		if (eventMap_[sockfd].events & EPOLLIN) {
			return false;
		}
		eventMap_[sockfd].events |= EPOLLIN | EPOLL_METHOD;
		auto temp = eventMap_[sockfd];
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_MOD, sockfd, &temp)) {
			return true;
		}
		eventMap_[sockfd].events &= ~EPOLLIN;
		perror("FailedToAddReadEvent");
		return false;
	}
}

bool Epollor::AddWriteEvent(int sockfd) {
	if (eventMap_.find(sockfd) == eventMap_.end()) {
		eventMap_[sockfd] = epoll_event();
		eventMap_[sockfd].events = EPOLLOUT | EPOLL_METHOD;
		eventMap_[sockfd].data.fd = sockfd;
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_ADD, sockfd, &eventMap_[sockfd])) {
			events_.resize(eventMap_.size());
			return true;
		}
		eventMap_.erase(sockfd);
		perror("FailedToAddWriteEvent");
		return false;
	}
	else {
		if (eventMap_[sockfd].events & EPOLLOUT) {
			return false;
		}
		eventMap_[sockfd].events |= EPOLLOUT | EPOLL_METHOD;
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_MOD, sockfd, &eventMap_[sockfd])) {
			return true;
		}
		eventMap_[sockfd].events &= ~EPOLLOUT;
		perror("FailedToAddWriteEvent");
		return false;
	}
}

bool Epollor::DelReadEvent(int sockfd) {
	if (eventMap_.find(sockfd) == eventMap_.end())
		return false;
	if (!(eventMap_[sockfd].events & EPOLLIN)) {
		return false;
	}
	eventMap_[sockfd].events &= ~EPOLLIN;
	if ((eventMap_[sockfd].events & ~EPOLL_METHOD) == 0) {
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_DEL, sockfd, nullptr)) {

			eventMap_.erase(sockfd);
			events_.resize(eventMap_.size());
			fmt::print("clear read\n");

			return true;
		}
	}
	else if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_MOD, sockfd, &eventMap_[sockfd])) {
		return true;
	}
	eventMap_[sockfd].events |= EPOLLIN;
	perror("FailedToDelReadEvent");
	return false;
}

bool Epollor::DelWriteEvent(int sockfd) {
	if (eventMap_.find(sockfd) == eventMap_.end())
		return false;
	if (!(eventMap_[sockfd].events & EPOLLOUT)) {
		return false;
	}

	eventMap_[sockfd].events &= ~EPOLLOUT;
	if ((eventMap_[sockfd].events & ~EPOLL_METHOD) == 0) {
		if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_DEL, sockfd, nullptr)) {

			eventMap_.erase(sockfd);
			events_.resize(eventMap_.size());
			fmt::print("clear write\n");

			return true;
		}
	}
	else if (-1 != epoll_ctl(epollFd_, EPOLL_CTL_MOD, sockfd, &eventMap_[sockfd])) {
		return true;
	}
	eventMap_[sockfd].events |= EPOLLOUT;
	perror("FailedToDelReadEvent");
	return false;
}

} // namespace Uriel