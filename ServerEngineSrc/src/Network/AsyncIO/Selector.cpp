#include "Selector.h"
#include <fmt/printf.h>
#include <sys/select.h>
#include <unistd.h>
namespace Uriel {
Selector::Selector() : Acceptor(), maxFd_(-1) {
	fds_.emplace_back(socket_.GetSocketfd());
}

void Selector::Run() {
	FD_ZERO(&fdSet_);
	for (auto fd : fds_) {
		maxFd_ = std::max(maxFd_, fd);
		FD_SET(fd, &fdSet_);
	}
	Select();
}

void Selector::Select() {
	int res = select(maxFd_ + 1, &fdSet_, nullptr, nullptr, nullptr);
	if (res == -1)
		return;
	if (res == 0)
		fmt::print("time out\n");
	std::vector<int> fdsCache;
	for (auto it = fds_.begin(); it != fds_.end();) {
		if (FD_ISSET(*it, &fdSet_)) {
			if (*it == socket_.GetSocketfd()) {
				int connectId = Accept();
				if (connectId != -1) {

					// fds_.insert(connectId);
					fdsCache.emplace_back(connectId);
					fmt::print("get a new connection{}\n", connectId);
				}
				// get a new connection
			} else {
				// recv a new message
				String msg = Recv(*it);
				;
				if (msg.size() == 0 && msg.errorNo_ != TRY_AGAIN) {

					fmt::print("connection:{} lost \n", *it);
					// close(it);
					close(*it);
					it = fds_.erase(it);
					continue;
				} else {
					fmt::print("get message:{}\n", msg);
				}
			}
		}
		++it;
	}
	fds_.insert(fds_.end(), fdsCache.begin(), fdsCache.end());
}

Selector::~Selector() {}

} // namespace Uriel