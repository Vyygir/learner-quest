#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    static Logger& instance();
    static void log(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

private:
    Logger();

    [[nodiscard]] static std::string getCurrentTime() ;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H
