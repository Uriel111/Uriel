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
	TcpSocket(bool block);
	TcpSocket();
	~TcpSocket();

private:
};
} // namespace Uriel