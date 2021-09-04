#include <fmt/printf.h>
int main()
{
	FMT_ASSERT(0, "ERROR");
	fmt::print("hello world!!\n");
	return 0;
}