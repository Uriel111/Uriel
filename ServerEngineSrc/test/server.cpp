#include <Network/AsyncIO/Epollor.h>
#include <Network/TcpServer.h>
#include <fmt/printf.h>

int main() {
	Uriel::Epollor selector;
	while (1) {
		selector.Run();
	}
	// Uriel::TcpServer server;
}