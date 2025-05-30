#pragma once
#include <Arduino.h>

enum LogLevel { LOG_LEVEL_DEBUG = 0, LOG_LEVEL_INFO, LOG_LEVEL_WARNING, LOG_LEVEL_ERROR, LOG_LEVEL_NONE };

class Logger {
public:
    static Logger& getInstance();
    void setLevel(LogLevel level);
    LogLevel getLevel() const;
    void log(LogLevel level, const char* file, const char* function, int line, const char* format, ...);

private:
    Logger();
    LogLevel currentLevel;
};
