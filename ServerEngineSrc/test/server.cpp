#include <Network/AsyncIO/Selector.h>
#include <Network/TcpServer.h>
#include <fmt/printf.h>

int main() {
	Uriel::Selector selector;
	while (1) {
		selector.Run();
	}
	// Uriel::TcpServer server;
}