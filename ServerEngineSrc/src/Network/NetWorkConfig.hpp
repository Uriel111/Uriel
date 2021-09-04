#pragma once
#include <string>
namespace Uriel
{
class NetWorkConfig
{
	public:
	static NetWorkConfig& Instance()
	{
		static NetWorkConfig inst_;
		return inst_;
	}
	std::string ip_;
	unsigned short port_;
	private:
	NetWorkConfig(): ip_("127.0.0.1"), port_(6666)
	{

	}
	~NetWorkConfig()
	{

	}


};
}