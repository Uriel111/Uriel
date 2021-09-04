#pragma once
#include <Common/NoCopyable.hpp>
#include <Network/Socket.h>
#include <netinet/in.h>
#include <string>
#include <unordered_set>
#include <arpa/inet.h>
namespace Uriel {
class Acceptor {
public:
	Acceptor();
	void Run();
	void Close();
	int Send(int clientId, std::string msg);

protected:
	int Accept();
	std::string Recv(int clientId);
	int Listen();
	int Bind();
	TcpSocket socket_;
	sockaddr_in sockAddr_;
	bool isRunning_;
};
} // namespace Uriel