#include "Logger.h"
#include <stdarg.h>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : currentLevel(LOG_LEVEL_INFO) {}

void Logger::setLevel(LogLevel level) { currentLevel = level; }
LogLevel Logger::getLevel() const { return currentLevel; }

void Logger::log(LogLevel level, const char* file, const char* function, int line, const char* format, ...) {
    if (level < currentLevel) return;

    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Serial.printf("[%d] %s:%d (%s): %s\n", level, file, line, function, buffer);
}
