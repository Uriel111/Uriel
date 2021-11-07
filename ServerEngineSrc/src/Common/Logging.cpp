#include <Common/Logging.h>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
namespace Uriel {

Logger &Logger::Instance() {
	static Logger logger;
	return logger;
}

std::string Logger::LogPrefix;

#define __DIR__ (std::filesystem::path(__FILE__).parent_path().string())

Logger::Logger() {
	std::cout << LogPrefix << std::endl;
	infoFile_.open(__DIR__ + "/../../Log/" + LogPrefix + "Info.log");
	warnFile_.open(__DIR__ + "/../../Log/" + LogPrefix + "Warn.log");
	errorFile_.open(__DIR__ + "/../../Log/" + LogPrefix + "Error.log");
	debugFile_.open(__DIR__ + "/../../Log/" + LogPrefix + "Debug.log");
}

Logger::~Logger() {
	infoFile_.close();
	warnFile_.close();
	errorFile_.close();
	debugFile_.close();
}

std::string Logger::FormatTime() {
	auto now = std::chrono::system_clock::now();
	auto timeStamp = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	std::tm timeBuff;
#if defined(WIN32) || defined(_WIN64)
	localtime_s(&timeBuff, &timeStamp);
#else
	localtime_r(&timeStamp, &timeBuff);

#endif
	std::ostringstream oss;
	oss << std::put_time(&timeBuff, "%Y-%m-%d-%X");
	oss << "." << std::setfill('0') << std::setw(3) << ms.count() << ":";
	return oss.str();
}

void Logger::Write(LogRank logRank, char *buffer, std::size_t size) {
	switch (logRank) {
	case ERROR:
		errorFile_.write(buffer, size);
	case WARN:
		warnFile_.write(buffer, size);

	case /* constant-expression */ INFO:
		/* code */
		infoFile_.write(buffer, size);

	default:
		debugFile_.write(buffer, size);
		break;
	}
}

// template <typename... T> void Logger::LogInfo(const std::string &formatStr, const T &...args) {

// 	Write(INFO, fmt::format(formatStr, args...));
// }
} // namespace Uriel