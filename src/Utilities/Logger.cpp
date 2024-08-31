#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "Logger.h"

Logger &Logger::instance() {
	static Logger instance;
	return instance;
}

void Logger::log(const std::string &message) {
	std::cout << "[" << Logger::getCurrentTime() << "] [INFO] " << message << std::endl;
}

void Logger::warn(const std::string &message) {
	std::cout << "[" << Logger::getCurrentTime() << "] [WARNING] " << message << std::endl;
}

void Logger::error(const std::string &message) {
	std::cerr << "[" << Logger::getCurrentTime() << "] [ERROR] " << message << std::endl;
}

Logger::Logger() = default;

std::string Logger::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto now_time_t = std::chrono::system_clock::to_time_t(now);
	auto now_tm = *std::localtime(&now_time_t);

	std::ostringstream oss;
	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
