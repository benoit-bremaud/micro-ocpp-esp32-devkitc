#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

class FileLogger {
public:
    FileLogger();
    ~FileLogger();

    bool begin();
    void end();
    void log(const char* message);

private:
    File currentLogFile;
    int currentLogIndex;

    // Internal helpers
    void openLatestLogFile();
    void rotateLogFileIfNeeded();
    void deleteOldestLogFileIfNeeded();
    String getLogFileName(int index) const;
    size_t getLogFileSize(File& file) const;

    // Constants
    static constexpr size_t MAX_LOG_FILE_SIZE = 8192;         // bytes
    static constexpr int MAX_LOG_FILES = 5;
    static constexpr const char* LOG_FILE_PREFIX = "/log_";
    static constexpr const char* LOG_FILE_SUFFIX = ".txt";
};

#endif // FILE_LOGGER_H
