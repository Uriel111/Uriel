#pragma once
#include <Network/AsyncIO/Acceptor.h>
#include <sys/poll.h>
#include <vector>
namespace Uriel {
class Poller : public Acceptor {
public:
	Poller();
	~Poller();
	void Run();
	void ClearEventFlag();


private:
	std::vector<pollfd> pollFds_;
};
} // namespace Uriel