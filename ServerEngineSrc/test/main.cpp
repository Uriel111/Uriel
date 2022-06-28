#include <Common/Singleton.hpp>
#include <assert.h>
#include <fmt/printf.h>
class Test{

};

int main() {
	Test &t = Singleton<Test>::Instance();
	t = Singleton<Test>::Instance();
	fmt::print("111");
}