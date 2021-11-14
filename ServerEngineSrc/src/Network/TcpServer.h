#pragma once
#include "Socket.h"
#include <Common/NoCopyable.hpp>
#include <netinet/in.h>
#include <string>
#include <unordered_set>

namespace Uriel {
class TcpServer : public NoCopyable {
public:
	TcpServer();

	void Run();
	void Close();
	int Send(int clientId, std::string msg);

protected:
	int Accept();
	std::string Recv(int clientId);
	int Listen();
	int Bind();

private:
	std::unordered_set<int> clientIds;
	TcpSocket tcpSocket_;
	sockaddr_in sockAddr_;
	bool isRuning_;
};
} // namespace Uriel
