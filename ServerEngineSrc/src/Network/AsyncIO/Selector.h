#pragma once
#include <Network/AsyncIO/Acceptor.h>
#include <Network/Socket.h>
#include <sys/socket.h>
#include <vector>
namespace Uriel {
class Selector : public Acceptor {
public:
	Selector();
	~Selector();
	void Run();

protected:
	void Select();

private:
	std::vector<int> fds_;
	int maxFd_;
	fd_set fdSet_;
};
} // namespace Uriel