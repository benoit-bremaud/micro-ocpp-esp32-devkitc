#pragma once
#include <Arduino.h>
#include "FileLogger.h"


enum LogLevel { LOG_LEVEL_DEBUG = 0, LOG_LEVEL_INFO, LOG_LEVEL_WARNING, LOG_LEVEL_ERROR, LOG_LEVEL_NONE };

const char* logLevelToString(LogLevel level);

struct LogEntry {
    String timestamp;
    LogLevel level;
    String file;
    String function;
    int line;
    String message;
};

class Logger {
public:
    static Logger& getInstance();
    void setLevel(LogLevel level);

    void begin(bool enableSPIFFS = false);
    void end();

    LogLevel getLevel() const;
    void log(LogLevel level, const char* file, const char* function, int line, const char* format, ...);

    // Historique circulaire/logging API
    void printLogHistory(Stream& out, size_t maxEntries = 0) const;

    // --- Test support (getters for buffer inspection) ---
    static const size_t LOG_HISTORY_SIZE = 64; // <-- public constant

    const LogEntry& getHistoryEntry(size_t idx) const { return history[idx]; }
    size_t getHistoryHead() const { return historyHead; }
    size_t getHistoryCount() const { return historyCount; }

    void clearHistory() {
        historyHead = 0;
        historyCount = 0;
    }

private:
    Logger();
    LogLevel currentLevel;

    // --- Circular buffer members ---
    LogEntry history[LOG_HISTORY_SIZE];
    size_t historyHead = 0;    // Points to oldest
    size_t historyCount = 0;   // Number of stored entries (<= LOG_HISTORY_SIZE)
};
