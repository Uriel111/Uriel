#include"test.h"
Test::Test(/* args */)
{
	cout << "Create Test" << endl;
	
}


Test::~Test()
{
	cout << "Release Test" << endl;
}

void Test::Print()
{
	cout << "test print successfully" << endl;	

}
