#include <iostream>
class ConstructTest
{
public:
    ConstructTest(int a) : _a(a) { std::cout << "调用构造函数" << std::endl; }
    ConstructTest() = delete;
    ConstructTest(const ConstructTest &cTest)
    {
        _a = cTest._a;
        std::cout << "调用拷贝构造函数" << std::endl;
    }
    ConstructTest &operator=(const ConstructTest &cTest)
    {
        _a = cTest._a;
        std::cout << "调用赋值函数" << std::endl;
        return *this;
    }

private:
    int _a;
};
int main()
{

    auto cT1 = ConstructTest(5);
    auto cT2 = ConstructTest(5);
    auto cT3 = ConstructTest(5);
    cT3 = cT2;
    auto cT4(cT3);
}