#include <Network/TcpClient.h>
#include <fmt/printf.h>

int main() {
	Uriel::TcpClient client;
	fmt::print("connect res:{}", client.Connect("127.0.0.1", 6666));
	fmt::print("send res:{}\n", client.Send("hello !"));
	while (1) {

		/* code */
	}
}