#include "Logger.h"
#include <stdarg.h>
#include <Arduino.h>
#include "FileLogger.h"

const char* logLevelToString(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:   return "DEBUG";
        case LOG_LEVEL_INFO:    return "INFO";
        case LOG_LEVEL_WARNING: return "WARN";
        case LOG_LEVEL_ERROR:   return "ERROR";
        case LOG_LEVEL_NONE:    return "NONE";
        default:                return "UNK";
    }
}

static FileLogger fileLogger;

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

void Logger::begin(bool enableSPIFFS) {
    // Prérequis : SPIFFS doit être monté (SPIFFS.begin()) avant d'appeler cette méthode.
    if (enableSPIFFS) {
        fileLogger.begin();
    }
    Serial.println("[Logger] Initialized");
}

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

    Serial.printf("[%s] [%s] %s:%d (%s): %s\n", ts.c_str(), logLevelToString(level), file, line, function, buffer);

    // --- Add to circular buffer history ---
    size_t pos;
    if (historyCount < LOG_HISTORY_SIZE) {
        pos = (historyHead + historyCount) % LOG_HISTORY_SIZE;
        historyCount++;
    } else {
        pos = historyHead;
        historyHead = (historyHead + 1) % LOG_HISTORY_SIZE;
    }

    history[pos].timestamp = ts;
    history[pos].level = level;
    history[pos].file = String(file);
    history[pos].function = String(function);
    history[pos].line = line;
    history[pos].message = String(buffer);
}

void Logger::printLogHistory(Stream& out, size_t maxEntries) const {
    size_t n = (maxEntries == 0 || maxEntries > historyCount) ? historyCount : maxEntries;
    for (size_t i = 0; i < n; ++i) {
        size_t idx = (historyHead + i) % LOG_HISTORY_SIZE;
        const LogEntry& e = history[idx];
        out.printf("[%s] [%s] %s:%d (%s): %s\n",
           e.timestamp.c_str(), logLevelToString(e.level), e.file.c_str(), e.line, e.function.c_str(), e.message.c_str());
    }
}
