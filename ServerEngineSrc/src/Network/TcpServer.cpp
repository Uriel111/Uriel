#include "TcpServer.h"
#include "NetWorkConfig.hpp"
#include <Common/Logging.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
namespace Uriel {
TcpServer::TcpServer() : tcpSocket_(false) {
	int socketfd = tcpSocket_.GetSocketfd();
	memset(&sockAddr_, 0, sizeof(sockAddr_));
	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_port = htons(NetWorkConfig::Instance().port_);
	sockAddr_.sin_addr.s_addr = inet_addr(NetWorkConfig::Instance().ip_.c_str());
	if (Bind() == -1)
		LogError("Failed to bind!\n");

	if (Listen() == -1)
		LogError("Failed to listen");
	while (1) {
		int clientId = Accept();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (clientId == -1) {
			LogError("there is no connection\n");
			continue;
		}
		else {
			LogDebug("get client%d!", clientId);
		}
		for (auto clientId : clientIds) {
			LogError("try to get mesg");
			Recv(clientId);
		}
	}
}

int TcpServer::Send(int clientId, std::string msg) {
	return send(clientId, msg.c_str(), msg.size(), 0);
}

std::string TcpServer::Recv(int clientId) {
	std::string readString;
	char readBuffer[128];
	int n = recv(clientId, readBuffer, 128, 0);
	if (n <= 0) {
		return readString;
	}
	LogDebug("recv msg n = %d\n", n);
	readString += std::string(readBuffer, readBuffer + n);
	LogDebug("get msg %s, size  is %d\n", readString, n);
	return readString;
}

int TcpServer::Bind() {
	return bind(tcpSocket_.GetSocketfd(), (sockaddr *)&sockAddr_, sizeof(sockAddr_));
}

int TcpServer::Listen() {
	return listen(tcpSocket_.GetSocketfd(), 5);
}

int TcpServer::Accept() {
	return accept(tcpSocket_.GetSocketfd(), nullptr, nullptr);
}

} // namespace Uriel