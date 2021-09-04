#include "TcpServer.h"
#include "NetWorkConfig.hpp"
#include <arpa/inet.h>
#include <fmt/printf.h>
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
	sockAddr_.sin_addr.s_addr =
		inet_addr(NetWorkConfig::Instance().ip_.c_str());
	if (Bind() == -1)
		fmt::print("Failed to bind!\n");

	if (Listen() == -1)
		fmt::print("Failed to listen\n");
	while (1) {
		int clientId = Accept();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (clientId == -1) {
			fmt::print("there is no connection\n");
			continue;
		} else {
			fmt::print("get client{}! \n", clientId);
		}
		for (auto clientId : clientIds) {
			fmt::print("try to get mesg\n");
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
	fmt::print("recv msg n = {}\n", n);
	readString += std::string(readBuffer, readBuffer + n);
	fmt::print("get msg {}, size  is {}\n", readString, n);
	return readString;
}

int TcpServer::Bind() {
	return bind(tcpSocket_.GetSocketfd(), (sockaddr *)&sockAddr_,
				sizeof(sockAddr_));
}

int TcpServer::Listen() {
	return listen(tcpSocket_.GetSocketfd(), 5);
}

int TcpServer::Accept() {
	return accept(tcpSocket_.GetSocketfd(), nullptr, nullptr);
}

} // namespace Uriel