#include "Socket.h"
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
namespace Uriel {
class TcpClient {
public:
	TcpClient();
	int Send(std::string msg);
	int Connect(std::string ip, int port);
private:
	TcpSocket tcpSocket_;
	sockaddr_in sockAddr_;

	
};
} // namespace Uriel