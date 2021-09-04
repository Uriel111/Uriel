#pragma once
#include <sys/socket.h>
#include <Network/Socket.h>
#include <vector>
namespace Uriel {
class Selector {
public:
	Selector();
	~Selector();

protected:
	void AddFds(int fd);
	void DelFds(int fd);

private:
	TcpSocket socket_;
	std::vector<int> fds_;
};
} // namespace Uriel