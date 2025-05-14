#include "logger.h"
#include <fstream>
#include <ctime>
#include <iomanip>

void Logger::log(LogLevel level, const std::string& message) {
    std::ofstream out("logs/log.txt", std::ios::app);
    if (!out) return;

    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    // Format log level
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO: levelStr = "INFO"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR: levelStr = "ERROR"; break;
    }

    // Write to log
    out << "[" << std::put_time(t, "%Y-%m-%d %H:%M:%S") << "] "
        << levelStr << ": " << message << "\n";
}
