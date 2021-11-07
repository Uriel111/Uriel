#pragma once
#include <Common/NoCopyable.hpp>
#include <Network/Socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <unordered_set>
namespace Uriel {
enum ERROR_NO
{
	LOST_CONNECTION,
	TRY_AGAIN,
	ERROR_CONNECTION
};
class String : public std::string {
public:
	ERROR_NO errorNo_;
};

class Acceptor {
public:
	Acceptor();
	void Run();
	void Close();

	int Accept();
	int Send(int clientId, std::string msg);

protected:
	String Recv(int clientId);
	int Listen();
	int Bind();
	TcpSocket socket_;
	sockaddr_in sockAddr_;
	bool isRunning_;
	char readBuffer_[128];
};
} // namespace Uriel