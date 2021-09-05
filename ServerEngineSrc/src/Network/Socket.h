#pragma once
#include <Common/NoCopyable.hpp>

namespace Uriel {
class Socket : public NoCopyable {
public:
	Socket(int socketfd);
	~Socket();
	const int GetSocketfd() const;

protected:
	int socketfd_;
};
class TcpSocket : public Socket {
public:
	TcpSocket();
	TcpSocket(bool block);
	~TcpSocket();

private:
};
} // namespace Uriel