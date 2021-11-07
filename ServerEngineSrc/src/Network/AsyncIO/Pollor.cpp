#include <Common/Logging.h>
#include <Network/AsyncIO/Pollor.h>
namespace Uriel {
Poller::Poller() {
	pollfd pollFd;
	pollFd.fd = socket_.GetSocketfd();
	pollFd.events = POLLIN;
	pollFd.revents = 0;
	pollFds_.emplace_back(pollFd);
}

Poller::~Poller() {}

void Poller::Run() {
	int n = poll(pollFds_.data(), pollFds_.size(), -1);
	if (n == -1) {
		perror(" poll error");
		return;
	}
	std::vector<pollfd> pollFdCaches;
	for (auto it = pollFds_.begin(); it != pollFds_.end();) {
		if (it->revents & POLLIN) {
			if (it->fd == socket_.GetSocketfd()) {
				int connectId = Accept();
				LogDebug("get new connection:%d\n", connectId);
				pollfd pollfdCache;
				pollfdCache.fd = connectId;
				pollfdCache.events = POLLIN;
				pollfdCache.revents = 0;
				pollFdCaches.emplace_back(pollfdCache);
			}
			else {
				// GetMsg
				String msg = Recv(it->fd);
				if (msg.errorNo_ == TRY_AGAIN) {
					LogDebug("get msg:%s", msg);
				}
				else {
					LogDebug("lose conncection:%d", it->fd);
					it = pollFds_.erase(it);
					continue;
				}
			}
		}
		++it;
	}
	pollFds_.insert(pollFds_.end(), pollFdCaches.begin(), pollFdCaches.end());
	ClearEventFlag();
}

void Poller::ClearEventFlag() {
	for (auto &pollFd : pollFds_) {
		pollFd.revents = 0;
	}
}

} // namespace Uriel