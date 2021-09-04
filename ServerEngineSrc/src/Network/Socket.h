#pragma once
#include <Common/NoCopyable.hpp>
namespace Uriel
{
class Socket: public NoCopyable
{
	Socket();
	~Socket();
};
class TcpSocket
{
	TcpSocket(int socketfd);
	~TcpSocket();
	private:
	int socketfd_;


};
}