#include "Logger.h"
#include <stdarg.h>
#include <Arduino.h>

// --- Timestamp ISO 8601 uptime ---
String getTimestampISO8601() {
    unsigned long ms = millis();
    unsigned long seconds = ms / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    seconds = seconds % 60;
    minutes = minutes % 60;
    char buf[32];
    snprintf(buf, sizeof(buf), "0000-00-00T%02lu:%02lu:%02luZ", hours, minutes, seconds);
    return String(buf);
}

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

    String ts = getTimestampISO8601();

    Serial.printf("[%s] [%d] %s:%d (%s): %s\n", ts.c_str(), level, file, line, function, buffer);
}
