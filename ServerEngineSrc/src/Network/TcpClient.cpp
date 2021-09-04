#include "TcpClient.h"

#include <string.h>

namespace Uriel {
TcpClient::TcpClient() : tcpSocket_(true) {}

int TcpClient::Connect(std::string ip, int port) {
	memset(&sockAddr_, 0, sizeof(sockAddr_));
	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_addr.s_addr = inet_addr(ip.c_str());
	sockAddr_.sin_port = htons(port);
	return connect(tcpSocket_.GetSocketfd(), (sockaddr *)&sockAddr_,
				   sizeof(sockaddr));
}

int TcpClient::Send(std::string msg) {
	return send(tcpSocket_.GetSocketfd(), msg.c_str(), msg.size(), 0);
}

} // namespace Uriel
