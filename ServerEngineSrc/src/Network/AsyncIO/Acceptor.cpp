#include <Network/AsyncIO/Acceptor.h>
#include <Network/NetWorkConfig.hpp>
#include <string.h>
namespace Uriel {
Acceptor::Acceptor() : isRunning_(false) {
	memset(&sockAddr_, 0, sizeof(sockAddr_));
	sockAddr_.sin_port = htons(NetWorkConfig::Instance().port_);
	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_addr.s_addr =
		inet_addr(NetWorkConfig::Instance().ip_.c_str());
}

int Acceptor::Bind() {
	return bind(socket_.GetSocketfd(), (sockaddr *)&sockAddr_,
				sizeof(sockaddr));
}

int Acceptor::Listen() {
	return listen(socket_.GetSocketfd(), 5);
}

int Acceptor::Accept() {
	return accept(socket_.GetSocketfd(), nullptr, nullptr);
}

int Acceptor::Send(int clientId, std::string msg) {
	return send(clientId, msg.c_str(), msg.size(), 0);
}

std::string Acceptor::Recv(int clientId)
{
	recv()
}

} // namespace Uriel