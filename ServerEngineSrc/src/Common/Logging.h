#pragma once
#include <fstream>

namespace Uriel {
enum LogRank
{
	INFO,
	WARN,
	ERROR
};

class Logger {
public:
	static Logger &Instance();

	template <typename... T> void Log(LogRank logRank, const std::string &formatStr, const char *codeFile, int codeLine, const char *codeFunc, const T &...args) {
		std::string realFormatStr = FormatTime() + "%s:%d:%s:" + formatStr + "\n";
		int size = snprintf(nullptr, 0, realFormatStr.data(), codeFile, codeLine, codeFunc, args...);
		if (size <= 0) {
			return;
		}
		char *buffer = new char[size + 1];
		snprintf(buffer, size + 1, realFormatStr.data(), codeFile, codeLine, codeFunc, args...);

		Write(logRank, buffer, size);
		delete[] buffer;
	}
	~Logger();

protected:
	std::string FormatTime();
	void Write(LogRank logRank, char *buffer, std::size_t size);

private:
	Logger();
	std::ofstream infoFile_;
	std::ofstream warnFile_;
	std::ofstream errorFile_;
};

#define LogInfo(formatStr, ...) (Logger::Instance().Log(INFO, "INFO->" formatStr, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__));
#define LogWarn(formatStr, ...) (Logger::Instance().Log(WARN, "WARN->" formatStr, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__));
#define LogError(formatStr, ...) (Logger::Instance().Log(ERROR, "ERROR->" formatStr, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__));
} // namespace Uriel